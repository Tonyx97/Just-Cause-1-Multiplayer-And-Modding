#include <defs/standard.h>

#include "weapon.h"
#include "weapon_belt.h"

#include <game/sys/weapon/weapon_system.h>

void WeaponBelt::set_weapon_ammo(int32_t bullet_type, int32_t v)
{
	jc::write(v, this, jc::weapon_belt::AMMO_BEGIN + (bullet_type * 0x4));
}

void WeaponBelt::remove_weapon(int32_t slot)
{
	jc::this_call(jc::weapon_belt::fn::REMOVE_WEAPON, REF(ptr, this, jc::weapon_belt::WEAPON_LIST + slot * 0x10));
}

void WeaponBelt::clear()
{
	jc::this_call(jc::weapon_belt::fn::CLEAR, this);
}

bool WeaponBelt::has_weapon(int32_t id)
{
    return false;
}

ref<Weapon> WeaponBelt::get_weapon_from_slot(int32_t slot)
{
	if (const auto entry = jc::read<ptr>(this, jc::weapon_belt::WEAPON_LIST + 0x4 + slot * 0x10))
		return ref<Weapon>(entry);

	return {};
}

ref<Weapon> WeaponBelt::get_weapon_from_type(uint8_t type)
{
	const auto slot = get_weapon_slot(type);

	if (auto weapon = get_weapon_from_slot(slot))
		return weapon;

	return {};
}

int16_t WeaponBelt::get_current_weapon_slot_id() const
{
	return jc::read<int16_t>(this, jc::weapon_belt::CURRENT_WEAPON_SLOT_ID);
}

int16_t WeaponBelt::get_draw_weapon_slot_id() const
{
	return jc::read<int16_t>(this, jc::weapon_belt::DRAW_WEAPON_ID);
}

int32_t WeaponBelt::get_weapon_slot(Weapon* weapon) const
{
	return get_weapon_slot(weapon->get_info()->get_type_id());
}

int32_t WeaponBelt::get_weapon_slot(int32_t type) const
{
	return static_cast<int32_t>(jc::this_call<int16_t>(jc::weapon_belt::fn::GET_SLOT_BY_TYPE_ID, this, type));
}

int32_t WeaponBelt::get_weapon_ammo(int32_t slot) const
{
	return jc::read<int32_t>(this, jc::weapon_belt::AMMO_BEGIN + (slot * 0x4));
}

ref<Weapon> WeaponBelt::get_current_weapon()
{
	ref<Weapon> r;

	jc::this_call(jc::weapon_belt::fn::GET_CURRENT_WEAPON, this, &r);

	return r;
}

ref<Weapon> WeaponBelt::add_weapon(ref<Weapon>& r)
{
	jc::this_call(jc::weapon_belt::fn::ADD_WEAPON, this, r.obj, r.counter);

	return std::move(r);
}

ref<Weapon> WeaponBelt::add_weapon(uint8_t weapon_id)
{
	if (auto r = g_weapon->create_weapon_instance(weapon_id))
	{
		r.inc_ref();

		return add_weapon(r);
	}

	return {};
}