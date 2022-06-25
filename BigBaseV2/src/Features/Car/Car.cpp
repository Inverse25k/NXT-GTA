#include "Car.h"

namespace big
{
	void Car::UpdateLoop()
	{
		boostbool ? carboost(true) : NULL;

		dowbool ? DriveOnWater(true) : NULL;

		enginealwaysonbool ? enginealwayson(true) : NULL;

		if (cargodmodebool)
		{
			cargodmode();
		}
	}

	bool Car::boostbool = false;
	void Car::carboost(bool toggle) {
		if (PLAYER::IS_PLAYER_PRESSING_HORN(PLAYER::PLAYER_ID()))
		{
			Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), false);
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Veh);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Veh))
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, 50);
			}
		}
	}

	bool Car::spawnincar = true;
	bool Car::spawnmaxed = false;

	void Car::spawn_vehicle(char* toSpawn) {
		Hash model = GAMEPLAY::GET_HASH_KEY(toSpawn);
		if (STREAMING::IS_MODEL_VALID(model))
		{
			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model)) features::WAIT(0);
			Vector3 ourCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			float forward = 5.f;
			float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
			float xVector = forward * sin(features::degToRad(heading)) * -1.f;
			float yVector = forward * cos(features::degToRad(heading));
			Vehicle veh = VEHICLE::CREATE_VEHICLE(model, ourCoords.x + xVector, ourCoords.y + yVector, ourCoords.z, heading, true, true);
			features::RequestControlOfEnt(veh);
			VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, true);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
			DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
			auto networkId = NETWORK::VEH_TO_NET(veh);
			ENTITY::_SET_ENTITY_NOT_HAVE_ADVANCED_PHYSICS(veh, true);
			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
			if (Car::spawnincar)
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
			}
			if (Car::spawnmaxed)
			{
				VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
				for (int i = 0; i < 50; i++)
				{
					VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, false);
				}
			}
			features::WAIT(150);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		}
	}

	Vehicle Car::SpawnVehicle(char* modelg, Vector3 coords, bool tpinto = 0, float heading = 0.0f) {
		DWORD model = GAMEPLAY::GET_HASH_KEY(modelg);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model)) {
			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model)); Sleep(0);
			Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, heading, 1, 1);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
			VEHICLE::SET_VEHICLE_IS_STOLEN(veh, 0);
			return veh;
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		}

	}

	bool Car::dowbool = false;
	void Car::DriveOnWater(bool toggle) {
		Player player = PLAYER::PLAYER_ID();
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		DWORD model = ENTITY::GET_ENTITY_MODEL(veh);
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
		float height = 0;
		WATER::_SET_CURRENT_INTENSITY(height);
		if ((!(VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(veh)))) && WATER::GET_WATER_HEIGHT_NO_WAVES(pos.x, pos.y, pos.z, &height)) {
			Object container = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pos.x, pos.y, pos.z, 4.0, GAMEPLAY::GET_HASH_KEY("prop_container_ld2"), 0, 0, 1);
			if (ENTITY::DOES_ENTITY_EXIST(container) && height > -50.0f) {
				Vector3 pRot = ENTITY::GET_ENTITY_ROTATION(playerPed, 0);
				if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1)) pRot = ENTITY::GET_ENTITY_ROTATION(veh, 0);
				features::RequestControlOfEnt(container);
				ENTITY::SET_ENTITY_COORDS(container, pos.x, pos.y, height - 1.5f, 0, 0, 0, 1);
				ENTITY::SET_ENTITY_ROTATION(container, 0, 0, pRot.z, 0, 1);
				Vector3 containerCoords = ENTITY::GET_ENTITY_COORDS(container, 1);
				if (pos.z < containerCoords.z) {
					if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
						ENTITY::SET_ENTITY_COORDS(playerPed, pos.x, pos.y, containerCoords.z + 2.0f, 0, 0, 0, 1);
					}
					else {
						features::RequestControlOfEnt(veh);
						Vector3 vehc = ENTITY::GET_ENTITY_COORDS(veh, 1);
						ENTITY::SET_ENTITY_COORDS(veh, vehc.x, vehc.y, containerCoords.z + 2.0f, 0, 0, 0, 1);
					}
				}
			}
			else {
				Hash model = GAMEPLAY::GET_HASH_KEY("prop_container_ld2");
				STREAMING::REQUEST_MODEL(model);
				while (!STREAMING::HAS_MODEL_LOADED(model)) features::WAIT(0);
				container = OBJECT::CREATE_OBJECT(model, pos.x, pos.y, pos.z, 1, 1, 0);
				features::RequestControlOfEnt(container);
				ENTITY::FREEZE_ENTITY_POSITION(container, 1);
				ENTITY::SET_ENTITY_ALPHA(container, 0, 1);
				ENTITY::SET_ENTITY_VISIBLE(container, 0, 0);
			}
		}
		else {
			Object container = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pos.x, pos.y, pos.z, 4.0, GAMEPLAY::GET_HASH_KEY("prop_container_ld2"), 0, 0, 1);
			if (ENTITY::DOES_ENTITY_EXIST(container)) {
				features::RequestControlOfEnt(container);
				ENTITY::SET_ENTITY_COORDS(container, 0, 0, -1000.0f, 0, 0, 0, 1);
				features::WAIT(10);
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&container);
				ENTITY::DELETE_ENTITY(&container);
				WATER::_RESET_CURRENT_INTENSITY();
			}
		}
	}

	bool Car::cargodmodebool = false;
	void Car::cargodmode()
	{

		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
		{
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			ENTITY::SET_ENTITY_INVINCIBLE(vehicle, Car::cargodmodebool);
			ENTITY::SET_ENTITY_PROOFS(vehicle, Car::cargodmodebool, Car::cargodmodebool, Car::cargodmodebool, Car::cargodmodebool, Car::cargodmodebool, Car::cargodmodebool, Car::cargodmodebool, Car::cargodmodebool);
			VEHICLE::SET_VEHICLE_DAMAGE(vehicle, 0.f, 0.f, 0.f, 0.f, 200.f, false);
			VEHICLE::SET_VEHICLE_ENVEFF_SCALE(vehicle, 0.f);
			VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(vehicle, Car::cargodmodebool);
			VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(vehicle, Car::cargodmodebool);
			VEHICLE::SET_VEHICLE_BODY_HEALTH(vehicle, 1000.f);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehicle, !Car::cargodmodebool);
			VEHICLE::SET_VEHICLE_CAN_BREAK(vehicle, !Car::cargodmodebool);
			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(vehicle, 1000.f);
			VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(vehicle, !Car::cargodmodebool);
			VEHICLE::SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(vehicle, !Car::cargodmodebool);
			VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(vehicle, 1000.f);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, !Car::cargodmodebool);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(vehicle, !Car::cargodmodebool);
			VEHICLE::SET_VEHICLE_FIXED(vehicle);
			VEHICLE::SET_VEHICLE_DAMAGE(vehicle, 0.f, 0.f, 0.f, 0.f, 200.f, true);
			VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(vehicle);
			VEHICLE::SET_VEHICLE_ENVEFF_SCALE(vehicle, 0.f);
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.f);
			VEHICLE::SET_VEHICLE_BODY_HEALTH(vehicle, 1000.f);
			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(vehicle, 1000.f);
			VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(vehicle, 1000.f);
			if (VEHICLE::_IS_VEHICLE_DAMAGED(vehicle))
			{
				for (int i = 0; i < 10; i++)
				{
					try {
						VEHICLE::SET_VEHICLE_TYRE_FIXED(vehicle, i);
					}
					catch (...) {
						return;
					}
				}
			}
		}
	}

	bool Car::enginealwaysonbool = false;
	void Car::enginealwayson(bool toggle)
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		VEHICLE::SET_VEHICLE_ENGINE_ON(veh, Car::enginealwaysonbool, Car::enginealwaysonbool, Car::enginealwaysonbool);
		VEHICLE::SET_VEHICLE_LIGHTS(veh, 0);
		VEHICLE::_SET_VEHICLE_LIGHTS_MODE(veh, 2);
	}

	void Car::flipup()
	{
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
	}

	void Car::maxvehicle()
	{
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
		for (int i = 0; i < 50; i++)
		{
			VEHICLE::SET_VEHICLE_MOD(vehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1, false);
		}
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, "NXT-G3N");
	}
}