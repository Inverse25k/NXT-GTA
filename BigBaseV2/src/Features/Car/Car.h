#pragma once
#include "common.hpp"
#include "logger.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "pointers.hpp"

namespace big
{
	namespace Car
	{
		void UpdateLoop();

		extern bool boostbool;
		void carboost(bool toggle);

		extern bool spawnincar;
		extern bool spawnmaxed;
		void spawn_vehicle(char* toSpawn);

		Vehicle SpawnVehicle(char* modelg, Vector3 coords, bool tpinto, float heading);

		extern bool dowbool;
		void DriveOnWater(bool toggle);

		extern bool cargodmodebool;
		void cargodmode();

		extern bool enginealwaysonbool;
		void enginealwayson(bool toggle);

		void flipup();

		void maxvehicle();
	}
}