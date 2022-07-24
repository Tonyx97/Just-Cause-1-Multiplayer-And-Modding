#pragma once

namespace jc::weapon
{
	static constexpr uint32_t GRIP_TRANSFORM		  = 0x38; // Transform
	static constexpr uint32_t CHARACTER_OWNER		  = 0x78; // Character*
	static constexpr uint32_t LAST_MUZZLE_TRANSFORM	  = 0xC0; // Transform
	static constexpr uint32_t MUZZLE_TRANSFORM		  = 0x100; // Transform
	static constexpr uint32_t LAST_EJECTOR_TRANSFORM  = 0x140; // Transform
	static constexpr uint32_t AMMO					  = 0x184; // int32_t
	static constexpr uint32_t LAST_SHOT_TIME		  = 0x19C; // float
	static constexpr uint32_t AIM_HIT_POSITION		  = 0x1A0; // vec3
	static constexpr uint32_t WEAPON_INFO			  = 0x1AC; // WeaponInfo*
	static constexpr uint32_t TOTAL_BULLETS_FIRED	  = 0x1C4; // int32_t
	static constexpr uint32_t TOTAL_BULLETS_FIRED_NOW = 0x1C8; // int32_t
	static constexpr uint32_t FIRING				  = 0x1CC; // bool
}

namespace jc::weapon_info
{
	static constexpr uint32_t ID				= 0x0; // int32_t
	static constexpr uint32_t TYPE_ID			= 0xC; // int32_t
	static constexpr uint32_t BULLET_TYPE		= 0x10; // int
	static constexpr uint32_t MAX_MAG_AMMO		= 0x38; // int
	static constexpr uint32_t BULLETS_TO_FIRE	= 0x44; // int
	static constexpr uint32_t TYPE_NAME			= 0x54; // char[28]
	static constexpr uint32_t NAME				= 0x54; // char[28]
	static constexpr uint32_t MUZZLE_OFFSET		= 0xA4; // vec3
	static constexpr uint32_t FIRE_SOUND_ID		= 0x118; // int
	static constexpr uint32_t BULLET_FORCE1		= 0x130; // float
	static constexpr uint32_t BULLET_FORCE2		= 0x134; // float
	static constexpr uint32_t CAN_CREATE_SHELLS = 0x176; // bool
}

class Character;
class Transform;

class WeaponInfo
{
public:
	void set_max_mag_ammo(int32_t v);
	void set_bullets_to_fire(int32_t v);
	void set_muzzle_offset(const vec3& v);
	void set_fire_sound_id(int32_t v);
	void set_bullet_force1(float v);
	void set_bullet_force2(float v);
	void set_can_create_shells(bool v);

	bool can_create_shells();

	int32_t get_id() const;
	int32_t get_type_id() const;
	int32_t get_max_mag_ammo();
	int32_t get_bullets_to_fire();
	int32_t get_fire_sound_id();

	float get_bullet_force1();
	float get_bullet_force2();

	vec3 get_muzzle_offset();

	const char* get_type_name();
	const char* get_name();
};

class Weapon
{
public:
	void set_ammo(int32_t v);

	bool is_firing();

	int32_t get_ammo();
	int32_t get_bullets_fired();
	int32_t get_bullets_fired_now();

	float get_last_shot_time();

	WeaponInfo* get_info();
	Character*	get_owner();

	vec3 get_aim_hit_position();

	Transform* get_grip_transform();
	Transform* get_last_muzzle_transform();
	Transform* get_muzzle_transform();
	Transform* get_last_ejector_transform();
};