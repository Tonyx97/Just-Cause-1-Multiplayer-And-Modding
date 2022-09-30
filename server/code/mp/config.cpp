#include <defs/standard.h>

#include <timer/timer.h>

#include "config.h"
#include "net.h"

#include <tcp_client.h>

#include <shared_mp/player_client/player_client.h>

bool Config::init()
{
	// open server config

	auto config_file = std::ifstream(CONFIG_FILE());
	if (!config_file)
		return false;

	try
	{
		config_file >> j_server_config;

		bool ok = false;

		if (std::tie(server_info.masterserver_ip, ok) = jc_json::get_field<std::string>(j_server_config, "masterserver_ip"); !ok)
			server_info.masterserver_ip.clear();

		if (std::tie(server_info.ip, ok) = jc_json::get_field<std::string>(j_server_config, "ip"); !ok)
			server_info.ip.clear();

		if (std::tie(server_info.name, ok) = jc_json::get_field<std::string>(j_server_config, "server_name"); !ok)
			server_info.name = "Default JC1:MP Server";

		if (std::tie(server_info.discord, ok) = jc_json::get_field<std::string>(j_server_config, "discord"); !ok)
			server_info.discord.clear();

		if (std::tie(server_info.community, ok) = jc_json::get_field<std::string>(j_server_config, "community"); !ok)
			server_info.community.clear();

		if (std::tie(server_info.password, ok) = jc_json::get_field<std::string>(j_server_config, "password"); !ok)
			server_info.ip.clear();

		if (std::tie(server_info.gamemode, ok) = jc_json::get_field<std::string>(j_server_config, "gamemode"); !ok)
			server_info.gamemode.clear();

		if (std::tie(server_info.refresh_rate, ok) = jc_json::get_field<int>(j_server_config, "refresh_rate"); !ok)
			server_info.refresh_rate = 60;

		const auto [startup_resources_key, rsrc_list_ok] = jc_json::get_field<json>(j_server_config, "startup_resources");

		if (rsrc_list_ok)
			for (const std::string& rsrc_name : startup_resources_key)
				server_info.startup_rsrcs.push_back(rsrc_name);
	}
	catch (...)
	{
		return logbt(RED, "Could not parse {}", CONFIG_FILE());
	}

	if (auto default_server_files_config = std::ifstream(DEFAULT_FILES_CONFIG_FILE()))
	{
		try
		{
			default_server_files_config >> j_server_files;

			for (const auto [src_path, dst_path] : j_server_files.items())
				default_files.emplace_back(std::move(util::fs::read_bin_file(src_path)), src_path, dst_path);
		}
		catch (...)
		{
			logt(RED, "Could not parse {}", DEFAULT_FILES_CONFIG_FILE());
		}
	}

	// initialize masterserver connection

	ms_conn = JC_ALLOC(netcp::tcp_client, [](netcp::client_interface* _cl, const netcp::packet_header& header, serialization_ctx& data)
	{
		switch (header.id)
		{
		case ServerToMsPacket_Verify:
		{
			logt(YELLOW, "Message from masterserver: {}", _deserialize<std::string>(data));
			break;
		}
		}
	});

	check(ms_conn, "Could not create master server connection");
	check(ms_conn->connect(server_info.masterserver_ip, netcp::SERVER_TO_MS_PORT), "Could not establish connection to the master server");

	ms_conn->send_packet(SharedMsPacket_Type, netcp::ServerClientType_Server);
	ms_conn->send_packet(ServerToMsPacket_Verify, std::string("todo - pending key"));

	return true;
}

void Config::destroy()
{
	// close masterserver connection

	JC_FREE(ms_conn);
}

void Config::update()
{
	static TimerRaw update_ms_info(2500);

	if (update_ms_info.ready())
	{
		serialization_ctx data;

		_serialize(data,
			server_info.ip,
			server_info.name,
			server_info.discord,
			server_info.community,
			server_info.gamemode,
			server_info.refresh_rate,
			!server_info.password.empty());

		int players_count = 0;

		g_net->for_each_player_client([&](NID, PlayerClient* pc)
		{
			_serialize(data, pc->get_nick(), pc->get_roles());
			
			++players_count;
		});

		// send this server's info to the masterserver

		ms_conn->send_packet(ServerToMsPacket_Info, data);
	}
}