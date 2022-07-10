#pragma once

namespace jc::vars
{
	inline std::unordered_map<uint32_t, std::string> exported_entities =
	{
		// key characters

		{ 0,	"key_caramicas.ee" },
		{ 1,	"key_carmona.ee" },
		{ 2,	"key_chiefvelasco.ee" },
		{ 3,	"key_ezperanza.ee" },
		{ 4,	"key_immaculada.ee" },
		{ 5,	"key_immaculada_dress.ee" },
		{ 6,	"key_kane.ee" },
		{ 7,	"key_kane_bikini.ee" },
		{ 8,	"key_kleiner.ee" },
		{ 9,	"key_montalban.ee" },
		{ 10,	"key_sheldon.ee" },
		{ 11,	"key_benito.ee" },
		{ 12,	"key_coloneldurango_woman.ee" },
		{ 13,	"key_presidents_son1.ee" },
		{ 14,	"key_presidents_son2.ee" },
		{ 15,	"key_roberto.ee" },

		// factions

		{ 16,	"blk_pilot.ee" },
		{ 17,	"blk_specialforce.ee" },
		{ 18,	"blk_squadleader.ee" },
		{ 19,	"blk_tankdriver.ee" },
		{ 20,	"blk_trooper.ee" },
		{ 21,	"blk_trooper2.ee" },
		{ 21,	"blk_bosstank.ee" },
		{ 22,	"gur_leader.ee" },
		{ 23,	"gur_pilot.ee" },
		{ 24,	"gur_sniper.ee" },
		{ 25,	"gur_soldier.ee" },
		{ 26,	"lib_gur_grenadier.ee" },
		{ 27,	"lib_gur_leader.ee" },
		{ 28,	"lib_gur_soldier.ee" },
		{ 29,	"lib_gur_veteran.ee" },
		{ 30,	"mil_drunk_soldier.ee" },
		{ 31,	"mil_elitesoldier.ee" },
		{ 32,	"mil_heavysoldier.ee" },
		{ 33,	"mil_lightsoldier.ee" },
		{ 34,	"mil_mountedgunner.ee" },
		{ 35,	"mil_sniper.ee" },
		{ 36,	"mil_supersoldier.ee" },
		{ 37,	"mon_bodyguard.ee" },
		{ 38,	"mon_cleaner.ee" },
		{ 39,	"mon_druglord.ee" },
		{ 40,	"mon_hitman.ee" },
		{ 41,	"mon_member.ee" },
		{ 42,	"mon_quarterboss.ee" },
		{ 43,	"mon_rpg.ee" },
		{ 44,	"mon_supertroop.ee" },
		{ 45,	"mon_biketrooper.ee" },
		{ 46,	"pol_policeman.ee" },
		{ 47,	"pol_motorcycle_police.ee" },
		{ 48,	"pol_pilot.ee" },
		{ 49,	"pol_prisonguard.ee" },
		{ 50,	"pol_rangercommissioner.ee" },
		{ 51,	"pol_rangerpolice.ee" },
		{ 52,	"pol_swatpolice.ee" },
		{ 53,	"rio_bodyguard.ee" },
		{ 54,	"rio_hitman.ee" },
		{ 55,	"rio_quarterboss.ee" },
		{ 56,	"rio_cleaner.ee" },

		// civilians

		{ 57,	"civ_beachgirlprostitute.ee" },
		{ 58,	"civ_beachgirlprostitute2.ee" },
		{ 59,	"civ_beachman.ee" },
		{ 60,	"civ_beachshowoff.ee" },
		{ 61,	"civ_bigmoderncivilian.ee" },
		{ 62,	"civ_bigtownlationocivilian.ee" },
		{ 63,	"civ_bikinigirl.ee" },
		{ 64,	"civ_bikinigirl2.ee" },
		{ 65,	"civ_bum.ee" },
		{ 66,	"civ_drunk.ee" },
		{ 67,	"civ_fisherman.ee" },
		{ 68,	"civ_guerillacivilian.ee" },
		{ 69,	"civ_indian.ee" },
		{ 70,	"civ_jogger.ee" },
		{ 71,	"civ_limodriver.ee" },
		{ 72,	"civ_mariachi.ee" },
		{ 73,	"civ_mecanic.ee" },
		{ 74,	"civ_medic.ee" },
		{ 75,	"civ_military_prostitute.ee" },
		{ 76,	"civ_moderncivilianagent.ee" },
		{ 77,	"civ_motorbiker.ee" },
		{ 78,	"civ_nun.ee" },
		{ 79,	"civ_oldcivilianfemale.ee" },
		{ 80,	"civ_oldcivilianmale.ee" },
		{ 81,	"civ_party1.ee" },
		{ 82,	"civ_party2.ee" },
		{ 83,	"civ_party3.ee" },
		{ 84,	"civ_party4.ee" },
		{ 85,	"civ_party5.ee" },
		{ 86,	"civ_party6.ee" },
		{ 87,	"civ_pilot.ee" },
		{ 88,	"civ_redneck1.ee" },
		{ 89,	"civ_redneck2.ee" },
		{ 90,	"civ_redneck3.ee" },
		{ 91,	"civ_redneck4.ee" },
		{ 92,	"civ_redneck5.ee" },
		{ 93,	"civ_redneck6.ee" },
		{ 94,	"civ_redneck7.ee" },
		{ 95,	"civ_riot1.ee" },
		{ 96,	"civ_riot2.ee" },
		{ 97,	"civ_robber.ee" },
		{ 98,	"civ_salesman.ee" },
		{ 99,	"civ_tourist.ee" },
		{ 100,	"civ_towncivilian.ee" },
		{ 101,	"civ_towncivilian2.ee" },
		{ 102,	"civ_urbancivilian.ee" },
		{ 103,	"civ_villagecivilian.ee" },
		{ 104,	"civ_villagecivilian2.ee" },
		{ 105,	"civ_waiter.ee" },
		{ 106,	"civ_worker.ee" },
		{ 107,	"civ_busdriver.ee" },
		{ 108,	"civ_harvester_coca.ee" },
		{ 109,	"civ_prisoner.ee" },
		{ 110,	"civ_mopeder.ee" },

		// missions

		{ 111,	"m04_mon_gunner.ee" },
		{ 112,	"m05_boathunters_captain.ee" },
		{ 113,	"m09_helicopter_mon.ee" },
		{ 114,	"m1_cia_fighterpilot.ee" },
		{ 115,	"m1_mil_mountedgunner.ee" },
		{ 116,	"m1_truckDriver.ee" },
		{ 117,	"m1_truckDriver2.ee" },
		{ 118,	"m1_boatdriver_mil_heavysoldier.ee" },
		{ 119,	"m1_helicopter_mil_heavysoldier.ee" },
		{ 121,	"m1_jeepdriver_mil_heavysoldier.ee" },
		{ 121,	"a1m06_convoy_driver_limo.ee" },
		{ 123,	"a1m06_convoy_firstcar_driver.ee" },
		{ 124,	"a1m06_convoy_lastcar_driver.ee" },
		{ 125,	"a2m07_chaser.ee" },
		{ 126,	"a2m07_ezperanza.ee" },
		{ 127,	"a2m07_gunrunners_driver.ee" },
		{ 128,	"a2m07_mountedgunner.ee" },
		{ 129,	"a2m08_blk_pilot_bad_shooter.ee" },
		{ 130,	"a2m14_driver_first.ee" },
		{ 131,	"a2m14_driver_last.ee" },
		{ 132,	"a2m14_mg_first.ee" },
		{ 133,	"a2m14_mg_last.ee" },
		{ 134,	"m08_blk_boatcaptain.ee" },
		{ 135,	"m08_boatchaser_blk_heavysoldier.ee" },
		{ 136,	"m08_boatgunner_blk_heavysoldier.ee" },
		{ 137,	"m10_lightsoldier_driver.ee" },
		{ 138,	"m11_boat_captain.ee" },
		{ 139,	"m12_mil_pilot_bad.ee" },
		{ 140,	"a2m07_ezperanza_crossroads.ee" },
		{ 141,	"a2m07_gunrunners_grenadier.ee" },
		{ 142,	"a2m07_gunrunners_grenadier2.ee" },
		{ 143,	"a2m07_gunrunners_shooter.ee" },
		{ 144,	"a2m07_sanchez.ee" },
		{ 145,	"a2m07_shitface.ee" },
		{ 146,	"a2m08_mon_cleaner.ee" },
		{ 147,	"m17_engineer.ee" },
		{ 148,	"m19_blk_fighterpilot.ee" },

		// races

		{ 149,	"rac_bookmaker_01.ee" },
		{ 150,	"rac_bookmaker_02.ee" },
		{ 151,	"rac_bookmaker_03.ee" },
		{ 152,	"rac_bookmaker_04.ee" },
		{ 153,	"rac_bookmaker_05.ee" },
	};

	inline std::unordered_map<uint32_t, std::string> exported_entities_vehicles =
	{
		{ 0, "" },
	};
}