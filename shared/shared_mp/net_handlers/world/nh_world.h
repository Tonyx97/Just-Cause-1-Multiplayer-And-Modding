#pragma once

namespace nh::world
{
	PacketResult time_scale(const Packet& p);
	PacketResult day_time(const Packet& p);
	PacketResult punch_force(const Packet& p);
	PacketResult spawn_object(const Packet& p, bool with_pfx);
	PacketResult destroy_object(const Packet& p);
	PacketResult set_ownership(const Packet& p);
	PacketResult sync_object(const Packet& p);
}