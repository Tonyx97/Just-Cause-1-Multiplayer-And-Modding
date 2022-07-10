#pragma once

namespace jc::sound_system
{
	static constexpr uint32_t SINGLETON = 0xD32ADC; // SoundSystem*

	static constexpr uint32_t HUD_BANK		 = 0x40; // SoundBank*
	static constexpr uint32_t AMBIENCE_BANK	 = 0x50; // SoundBank*
	static constexpr uint32_t EXPLOSION_BANK = 0x54; // SoundBank*
	static constexpr uint32_t WEAPON_BANK	 = 0x58; // SoundBank*
}

class SoundBank;
class SoundGameObject;

class SoundSystem
{
public:
	void init();
	void destroy();

	SoundGameObject* create_sound(const vec3& position, const std::string& bank_name, uint32_t sound_id);

	SoundBank* get_hud_bank();
	SoundBank* get_ambience_bank();
	SoundBank* get_explosion_bank();
	SoundBank* get_weapon_bank();
	SoundBank* get_sound_bank_by_index(int i);
};

inline SoundSystem* g_sound = nullptr;