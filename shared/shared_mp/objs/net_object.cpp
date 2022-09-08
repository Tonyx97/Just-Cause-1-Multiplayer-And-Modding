#include <defs/standard.h>

#include "net_object.h"

#include <shared_mp/objs/player.h>

#ifdef JC_CLIENT
#include <game/object/base/comps/physical.h>
#include <game/object/damageable_object/damageable_object.h>
#include <game/object/ui/map_icon.h>
#include <game/sys/core/factory_system.h>
#else
#include <rg/rg.h>
#endif

#include <mp/net.h>

NetObject::NetObject()
{
#ifdef JC_CLIENT
	vars.transform_timer(16 * 3);
	vars.velocity_timer(0);
#else
	nid = enet::GET_FREE_NID();
	rg = g_net->get_rg()->add_entity(this, static_cast<int64_t>(nid));
#endif
}

NetObject::~NetObject()
{
#ifdef JC_CLIENT
#else
	g_net->get_rg()->remove_entity(rg);

	enet::FREE_NID(nid);
#endif
}

#ifdef JC_CLIENT
bool NetObject::sync()
{
	if (!is_owned())
		return false;

	// base sync

	// todojc - check for actual alive objects instances

	TransformTR real_transform;

	const auto object_base = BITCAST(AliveObject*, get_object_base());
	const auto physical = object_base->get_physical();

	real_transform.t = object_base->get_position();
	real_transform.r = object_base->get_rotation();

	const float real_hp = object_base->get_real_hp(),
				real_max_hp = object_base->get_max_hp();

	if ((real_transform.t != get_position() || real_transform.r != get_rotation()) && vars.transform_timer.ready())
		g_net->send(Packet(WorldPID_SyncObject, ChannelID_World, this, NetObjectVar_Transform, (vars.transform = real_transform).pack()).set_unreliable());

	switch (get_type())
	{
	case NetObject_Player: break;
	default:
	{
		if (vars.velocity_timer.get_interval() > 0 && vars.velocity_timer.ready())
			g_net->send(Packet(WorldPID_SyncObject, ChannelID_World, this, NetObjectVar_Velocity, vars.velocity = physical->get_velocity()));
	}
	}

	const auto hp = get_hp(),
			   max_hp = get_max_hp();

	if (real_hp != get_hp() || hp == jc::nums::MAXF)
		g_net->send(Packet(WorldPID_SyncObject, ChannelID_World, this, NetObjectVar_Health, vars.hp = real_hp));

	if (real_max_hp != get_max_hp() || max_hp == jc::nums::MAXF)
		g_net->send(Packet(WorldPID_SyncObject, ChannelID_World, this, NetObjectVar_MaxHealth, vars.max_hp = real_max_hp));

	// parent object sync

	on_sync();

	return true;
}

void NetObject::set_transform_timer(int64_t v)
{
	vars.transform_timer(v);
}

void NetObject::set_velocity_timer(int64_t v)
{
	vars.velocity_timer(v);
}

bool NetObject::is_owned() const
{
	if (const auto player = cast<Player>())
		return player->is_local();
	else return streamer && streamer->is_local();
}
#else
namespace enet
{
	std::unordered_set<NID> free_nids,
							used_nids;

	void INIT_NIDS_POOL()
	{
		// create a total of 65534 possible nids (1-65534)

		for (NID i = 1ui16; i < 65535ui16; ++i)
			free_nids.insert(free_nids.end(), i);
	}

	NID GET_FREE_NID()
	{
		check(!free_nids.empty(), "No more free NIDs available");

		const auto it = free_nids.begin();
		const auto nid = *it;

		free_nids.erase(it);
		used_nids.insert(nid);

		return nid;
	}

	void FREE_NID(NID nid)
	{
		auto it = used_nids.find(nid);

		check(it != used_nids.end(), "NID {} not used", nid);

		used_nids.erase(it);
		free_nids.insert(nid);
	}
}

bool NetObject::sync()
{
	log(RED, "server wants to sync this object");

	on_sync();
	
	return true;
}
#endif

void NetObject::set_streamer(Player* v)
{
#ifdef JC_SERVER
	if (streamer && v != streamer)
	{
		// if the object has a streamer, then we want to know if we have to transfer it to another
		// player or simply remove any ownership
		
		if (v)
			streamer->transfer_net_object_ownership_to(this, v);
		else streamer->remove_net_object_ownership(this);
	}
	else if (!streamer && v)
	{
		// if the object had no streamer but we want to set one then simply
		// set the object's ownership to the player
		
		v->set_net_object_ownership_of(this);
	}
#endif

	streamer = v;
}

void NetObject::set_spawned(bool v)
{
	spawned = v;

	// if we just spawned the object then let the parent
	// class know so they can set the basic vars

	on_net_var_change(NetObjectVar_Transform);
}

void NetObject::set_sync_type_and_streamer(SyncType _sync_type, Player* _streamer)
{
	set_sync_type(_sync_type);
	set_streamer(_streamer);
}

void NetObject::set_transform(const TransformTR& transform)
{
	vars.transform.t = transform.t;
	vars.transform.r = transform.r;

	if (spawned)
		on_net_var_change(NetObjectVar_Transform);
}

void NetObject::set_transform(const TransformPackedTR& packed_transform)
{
	set_transform(TransformTR(packed_transform));
}

void NetObject::set_position(const vec3& v)
{
	vars.transform.t = v;

	if (spawned)
		on_net_var_change(NetObjectVar_Position);
}

void NetObject::set_rotation(const quat& v)
{
	vars.transform.r = v;

	if (spawned)
		on_net_var_change(NetObjectVar_Rotation);
}

void NetObject::set_hp(float v)
{
	vars.hp = v;

	if (spawned)
		on_net_var_change(NetObjectVar_Health);
}

void NetObject::set_max_hp(float v)
{
	vars.max_hp = v;

	if (spawned)
		on_net_var_change(NetObjectVar_MaxHealth);
}

void NetObject::set_velocity(const vec3& v)
{
	vars.velocity = v;

	if (spawned)
		on_net_var_change(NetObjectVar_Velocity);
}

void NetObject::set_pending_velocity(const vec3& v)
{
	vars.pending_velocity = v;
}

bool NetObject::is_valid_type() const
{
	const auto type = get_type();

	return type > NetObject_Invalid && type < NetObject_Max;
}