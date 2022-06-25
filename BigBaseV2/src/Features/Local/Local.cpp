#include "common.hpp"
#include "Local.h"
#include "logger.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "gta/enums.hpp"

namespace big
{
	void Local::UpdateLoop()
	{
		god ? God(true) : NULL;

		invisibility ? Invisibility(true) : NULL;

		playersuperjump ? SuperJump(true) : NULL;

		mobileRadio ? mobilevoid(true) : NULL;

		betiny ? TinyPlayer(true) : NULL;
	}

	bool Local::god = false;
	void Local::God(bool enable)
	{
		if (enable == true)
		{
			ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), true);
		}
		else {
			ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false);
		}

		//Memory::set_value<bool>({ 0x08, 0x189 }, enable);
	}

	bool Local::invisibility = false;
	void Local::Invisibility(bool enable)
	{
		if (enable == true)
		{
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false, 0);
		}
		else
		{
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, 0);
		}
	}

	bool Local::playersuperjump = false;
	void Local::SuperJump(bool toggle)
	{
		Player playerPed = PLAYER::PLAYER_PED_ID();
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(playerPed);
	}

	bool Local::mobileRadio = false;
	void Local::mobilevoid(bool toggle) {
		int station = AUDIO::GET_PLAYER_RADIO_STATION_INDEX();
		if (toggle == false)
		{
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(0);

		}
		else
		{
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(1);
			AUDIO::SET_RADIO_TO_STATION_INDEX(station);

		}
	}

	bool Local::betiny = false;
	void Local::TinyPlayer(bool toggle)
	{
		PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, toggle);
	}
}