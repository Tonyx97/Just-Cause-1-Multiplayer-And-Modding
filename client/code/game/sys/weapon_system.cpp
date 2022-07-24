#include <defs/standard.h>

#include "weapon_system.h"

uint32_t WeaponTemplate::get_id() const
{
	return jc::read<uint32_t>(this, jc::weapon_system::weapon_template::ID);
}

std::string WeaponTemplate::get_model() const
{
	return jc::read<std::string>(this, jc::weapon_system::weapon_template::MODEL_NAME);
}

std::string WeaponTemplate::get_type_name() const
{
	return jc::read<std::string>(this, jc::weapon_system::weapon_template::TYPE_NAME);
}

std::string WeaponTemplate::get_name() const
{
	return jc::read<std::string>(this, jc::weapon_system::weapon_template::NAME);
}

void WeaponSystem::init()
{
}

void WeaponSystem::destroy()
{
}

void WeaponSystem::dump()
{
	// enum

	log(RED, "enum WeaponID");
	log(RED, "{{");
	log(GREEN, "Weapon_None,");

	std::unordered_map<uint32_t, std::string> fixed_names;

	for_each_weapon_template([&](int, WeaponTemplate* t)
	{
		auto name = t->get_type_name();
		auto id = t->get_id();

		std::replace(name.begin(), name.end(), ' ', '_');
		
		std::erase(name, '(');
		std::erase(name, ')');

		fixed_names.insert({ id, "Weapon_" + name });

		log(GREEN, "Weapon_{} = {}, // {} | {}", name, id, t->get_name(), t->get_type_name());
	});

	log(RED, "}};");

	// weapons id to type name

	log(RED, "inline const std::unordered_map<uint32_t, std::string> weapons_id_to_type_name =");
	log(RED, "{{");

	for_each_weapon_template([&](int, WeaponTemplate* t)
	{
		auto name = t->get_type_name();
		auto id = t->get_id();

		log(GREEN, "{{ {}, R\"{}\" }},", fixed_names[id], name);
	});

	log(RED, "}};");

	// weapons id to model name

	log(RED, "inline const std::unordered_map<uint32_t, std::string> weapons_id_to_model_name =");
	log(RED, "{{");

	for_each_weapon_template([&](int, WeaponTemplate* t)
	{
		auto name = t->get_model();
		auto id = t->get_id();

		if (!name.empty())
			log(GREEN, "{{ {}, R\"({})\" }},", fixed_names[id], name);
	});

	log(RED, "}};");
}

int WeaponSystem::for_each_weapon_template(const weapon_template_iteration_t& fn)
{
	const auto template_list = REF(std::vector<WeaponTemplate*>*, this, jc::weapon_system::TEMPLATE_LIST);

	int32_t count = 0;

	for (auto weapon_template : *template_list)
		fn(count++, weapon_template);

	return count;
}

std::string WeaponSystem::get_weapon_typename(int32_t id)
{
	auto it = jc::vars::weapons_id_to_type_name.find(id);
	return it != jc::vars::weapons_id_to_type_name.end() ? it->second : "";
}

std::string WeaponSystem::get_weapon_model(int32_t id)
{
	auto it = jc::vars::weapons_id_to_model_name.find(id);
	return it != jc::vars::weapons_id_to_model_name.end() ? it->second : "";
}

ref<Weapon> WeaponSystem::create_weapon_instance(const std::string& name)
{
	ref<Weapon> p;

	jc::this_call(jc::weapon_system::fn::ALLOC_WEAPON_BY_NAME, this, &p, &name);

	return p;
}

ref<Weapon> WeaponSystem::create_weapon_instance(int32_t id)
{
	ref<Weapon> p;

	jc::this_call(jc::weapon_system::fn::ALLOC_WEAPON_BY_ID, this, &p, id);

	return p;
}