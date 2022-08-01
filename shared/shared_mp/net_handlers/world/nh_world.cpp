#include <defs/standard.h>

#include "nh_world.h"

#include <mp/net.h>

#ifdef JC_CLIENT
#include <game/sys/day_cycle.h>
#endif

enet::PacketResult nh::world::day_time(const enet::Packet& p)
{
#ifdef JC_CLIENT
	g_day_cycle->set_enabled(p.get_bool());
	g_day_cycle->set_time(p.get_float());
#endif

	return enet::PacketRes_Ok;
}

enet::PacketResult nh::world::spawn_object(const enet::Packet& p)
{
#ifdef JC_CLIENT
	const auto [nid, net_type] = p.get_nid_and_type();
#else
	const auto pc = p.get_pc();
	const auto player = pc->get_player();

	const auto net_type = p.get_integral<NetObjectType>();
#endif

	const auto transform = p.get_raw<TransformTR>();

#ifdef JC_CLIENT
	g_net->spawn_net_object(nid, net_type, transform);
#else
	g_net->spawn_net_object(net_type, transform);
#endif

	return enet::PacketRes_Ok;
}

enet::PacketResult nh::world::set_ownership(const enet::Packet& p)
{
#ifdef JC_CLIENT
	const auto new_streamer = p.get_net_object<Player>();
	const auto net_obj = p.get_net_object();

	if (!net_obj)
		return enet::PacketRes_BadArgs;

	net_obj->set_streamer(new_streamer);

	return enet::PacketRes_Ok;
#endif

	return enet::PacketRes_NotSupported;
}

enet::PacketResult nh::world::sync_object(const enet::Packet& p)
{
	const auto net_obj = p.get_net_object();

	if (!net_obj)
		return enet::PacketRes_BadArgs;

#ifdef JC_SERVER
	const auto pc = p.get_pc();
	const auto player = pc->get_player();

	// check if the player sending this packet is actually streaming
	// the object

	if (net_obj->get_type() != NetObject_Player)
	{
		if (!net_obj->is_owned_by(player))
			return enet::PacketRes_NotAllowed;
	}
	else if (net_obj != player)
		return enet::PacketRes_NotAllowed;
#endif

	switch (const auto var_type = p.get_u8())
	{
	case NetObjectVar_Transform:
	{
		const auto transform = p.get_raw<TransformPackedTR>();

		net_obj->set_transform(transform);

#ifdef JC_SERVER
		g_net->send_broadcast_joined_unreliable<ChannelID_World>(pc, WorldPID_SyncObject, net_obj, NetObjectVar_Transform, transform);
#endif

		break;
	}
	case NetObjectVar_Health:
	{
		const auto hp = p.get_float();

		net_obj->set_hp(hp);

#ifdef JC_SERVER
		g_net->send_broadcast_joined_reliable<ChannelID_World>(pc, WorldPID_SyncObject, net_obj, NetObjectVar_Health, hp);
#endif

		break;
	}
	case NetObjectVar_MaxHealth:
	{
		const auto max_hp = p.get_float();

		net_obj->set_max_hp(max_hp);

#ifdef JC_SERVER
		g_net->send_broadcast_joined_reliable<ChannelID_World>(pc, WorldPID_SyncObject, net_obj, NetObjectVar_MaxHealth, max_hp);
#endif

		break;
	}
	default: log(RED, "Unknown net object var type: {}", var_type);
	}

	return enet::PacketRes_Ok;
}