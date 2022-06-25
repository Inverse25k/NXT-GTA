#include "common.hpp"
#include "features.hpp"
#include "logger.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big
{
	HANDLE features::mainFiber;
	DWORD features::wakeAt;

	int features::TimePD;
	int features::TimePD1;
	int features::TimePD2;
	int features::TimePD3;
	int features::TimePD4;
	int features::TimePD5;
	int features::TimePD6;
	int features::TimePD7;
	int features::TimePD8;

	void features::run_tick()
	{
		Car::UpdateLoop();
		Gun::UpdateLoop();
		Local::UpdateLoop();
		Misc::UpdateLoop();
		Online::UpdateLoop();
		//Protections::UpdateLoop();
	}

	void features::script_func()
	{
		while (true)
		{
			run_tick();
			script::get_current()->yield();
		}
	}

	void features::RequestControlOfid(Entity netid)
	{
		int tick = 0;

		while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
			tick++;
		}
	}

	void features::RequestControlOfEnt(Entity entity)
	{
		int tick = 0;
		while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
			tick++;
		}
		if (NETWORK::NETWORK_IS_SESSION_STARTED())
		{
			int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
			RequestControlOfid(netID);
			NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
		}
	}

	void features::WAIT(DWORD ms)
	{
		wakeAt = timeGetTime() + ms;
		SwitchToFiber(mainFiber);
	}

	bool features::RequestNetworkControl(uint vehID)
	{
		int Tries = 0;
		bool
			hasControl = false,
			giveUp = false;
		do
		{
			hasControl = NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehID);
			Tries++;
			if (Tries > 300)
				giveUp = true;
		} while (!hasControl && !giveUp);

		if (giveUp)
			return false;
		else return true;
	}

	void features::ApplyForceToEntity(Entity e, float x, float y, float z)
	{
		if (e != PLAYER::PLAYER_PED_ID() && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(e) == FALSE)
		{
			RequestControlOfEnt(e);
		}

		ENTITY::APPLY_FORCE_TO_ENTITY(e, 1, x, y, z, 0, 0, 0, 0, 1, 1, 1, 0, 1);

	}

	bool features::cstrcmp(const char* s1, const char* s2)
	{
		while (*s1 && (*s1 == *s2))
			s1++, s2++;
		if (*(const unsigned char*)s1 - *(const unsigned char*)s2 == 0)
			return true;
		else
			return false;
	}

	float features::degToRad(float degs)
	{
		return degs * 3.141592653589793f / 180.f;
	}

	float features::Get3DDistance(Vector3 a, Vector3 b) 
	{
		float x = pow((a.x - b.x), 2);
		float y = pow((a.y - b.y), 2);
		float z = pow((a.z - b.z), 2);
		return sqrt(x + y + z);
	}

	Hash features::$(std::string str) {
		return GAMEPLAY::GET_HASH_KEY(&str[0u]);
	}
}
