#include "common.hpp"
#include "Misc.h"
#include "logger.hpp"
#include "natives.hpp"
#include "script.hpp"

#define PROP_MONEY_BAG_01 0x113FD533
#define PICKUP_MONEY_CASE 0x1E9A99F8

namespace big
{
	void Misc::UpdateLoop()
	{
		if (killpedsbool)
		{
			killpeds();
		}
		if (explodepedsbool)
		{
			explodepeds();
		}
		if (explodenearbyvehiclesbool)
		{
			explodenearbyvehicles();
		}
		if (deletenearbyvehiclesbool)
		{
			deletenearbyvehicles();
		}

		savenewdrop ? cashdrop(true) : NULL;

		playertenkped ? TenKPedMoney(true) : NULL;
	}

	void Misc::trapall() {
		for (int i = 1; i <= 32; i++) {
			if (PLAYER::PLAYER_ID() != i) {
				Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0);
				Object obj = OBJECT::CREATE_OBJECT(features::$("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1.f, true, false, false);
			}
		}
	}

	void Misc::teleporttocoords(Player player, Vector3 target)
	{
		for (int iz = 0; iz < 2; iz++)
		{
			Ped destPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			Vector3 ourLoc = target;
			AI::CLEAR_PED_TASKS_IMMEDIATELY(destPed);
			int netScene = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(ourLoc.x, ourLoc.y, ourLoc.z, 0.f, 0.f, 0.f, 0, 0, 0, 0.f);
			NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(destPed, netScene, "amb@code_human_cower@female@base", "base", 8.f, -8.f, 2, 0, 100.f, 0);
			NETWORK::NETWORK_START_SYNCHRONISED_SCENE(netScene);
			features::WAIT(150);
			AI::CLEAR_PED_TASKS_IMMEDIATELY(destPed);
			NETWORK::NETWORK_STOP_SYNCHRONISED_SCENE(netScene);
		}
	}

	void Misc::teleportallcoords(Vector3 target)
	{
		for (int i2 = 0; i2 < 2; i2++)
		{
			Vector3 targetCoords = target;
			for (int i = 0; i < 32; i++)
			{
				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
				{
					AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
					int netScene = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(targetCoords.x, targetCoords.y, targetCoords.z, 0.f, 0.f, 0.f, 0, 0, 0, 0.f);
					NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), netScene, "amb@code_human_cower@female@base", "base", 8.f, -8.f, 2, 0, 100.f, 0);
					NETWORK::NETWORK_START_SYNCHRONISED_SCENE(netScene);
				}
			}
			features::WAIT(150);
			for (int i = 0; i < 32; i++)
			{
				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
				{
					AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
				}
			}
		}
	}

	void Misc::teleportallcoordsns(Vector3 target)
	{
		for (int i2 = 0; i2 < 2; i2++)
		{

			Vector3 targetCoords = target;
			for (int i = 0; i < 32; i++)
			{
				if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) == PLAYER::PLAYER_PED_ID()) continue;
				{
					if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
					{
						AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
						int netScene = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(targetCoords.x, targetCoords.y, targetCoords.z, 0.f, 0.f, 0.f, 0, 0, 0, 0.f);
						NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), netScene, "amb@code_human_cower@female@base", "base", 8.f, -8.f, 2, 0, 100.f, 0);
						NETWORK::NETWORK_START_SYNCHRONISED_SCENE(netScene);
					}
				}
			}
			features::WAIT(150);
			for (int i = 0; i < 32; i++)
			{
				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
				{
					AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
				}
			}
		}
	}

	void Misc::clearanim()
	{
		AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
	}

	void Misc::doAnimation(char* anim, char* animid)
	{
		int pPlayer = PLAYER::PLAYER_PED_ID();
		features::RequestNetworkControl(pPlayer);
		STREAMING::REQUEST_ANIM_DICT(anim);
		if (STREAMING::HAS_ANIM_DICT_LOADED((anim)))
		{
			AI::TASK_PLAY_ANIM(pPlayer, anim, animid, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
		}
	}

	void Misc::animatePlayer(Player target, char* dict, char* anim)
	{
		Ped targ_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);//seleted player
		STREAMING::REQUEST_ANIM_DICT(dict);
		if (STREAMING::HAS_ANIM_DICT_LOADED(dict))
		{
			Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(targ_ped, 0.0, 0.0, 0.0);//since get_coord is patched i found this native
			int sceneID = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(coords.x, coords.y, coords.z, 0, 0, 0, 2, 0, 1, 1.0f);
			NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(targ_ped, sceneID, dict, anim, 8.0f, -8.0f, 120, 0, 100, 0);/*i changed any to char* i provide the native below(modificated)*/
			NETWORK::NETWORK_START_SYNCHRONISED_SCENE(sceneID);//will start the animation
		}
	}

	int Misc::attachobj[100];
	int Misc::nuattach = 1;
	void Misc::attachobjects2(char* object)
	{
		bool custom = false;
		int hash = 0;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer), true);
		hash = GAMEPLAY::GET_HASH_KEY(object);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(hash))
		{
			if (STREAMING::IS_MODEL_VALID(hash))
			{
				STREAMING::REQUEST_MODEL(hash);
				if (STREAMING::HAS_MODEL_LOADED(hash))
				{
					Misc::attachobj[Misc::nuattach] = OBJECT::CREATE_OBJECT(hash, pos.x, pos.y, pos.z, 1, 1, 1);
					if (ENTITY::DOES_ENTITY_EXIST(Misc::attachobj[Misc::nuattach]))
					{
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Misc::attachobj[Misc::nuattach], PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Online::selectedPlayer), 31086, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
						nuattach++;
						if (nuattach >= 101) { nuattach = 1; }
					}
				}
			}
		}
	}

	bool Misc::killpedsbool = false;
	void Misc::killpeds()
	{
		const int ElementAmount = 10;
		const int ArrSize = ElementAmount * 2 + 2;

		Ped* peds = new Ped[ArrSize];
		peds[0] = ElementAmount;

		int PedFound = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, -1);

		for (int i = 0; i < PedFound; i++)
		{
			int OffsetID = i * 2 + 2;
			features::RequestControlOfEnt(peds[OffsetID]);
			if (ENTITY::DOES_ENTITY_EXIST(peds[OffsetID]) && PLAYER::PLAYER_PED_ID() != peds[OffsetID])
			{
				PED::APPLY_DAMAGE_TO_PED(peds[OffsetID], 1000, false);
			}
		}
	}

	bool Misc::explodepedsbool = false;
	void Misc::explodepeds()
	{
		const int ElementAmount = 10;
		const int ArrSize = ElementAmount * 2 + 2;

		Ped* peds = new Ped[ArrSize];
		peds[0] = ElementAmount;

		int PedFound = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, -1);

		for (int i = 0; i < PedFound; i++)
		{
			int OffsetID = i * 2 + 2;
			features::RequestControlOfEnt(peds[OffsetID]);
			if (ENTITY::DOES_ENTITY_EXIST(peds[OffsetID]) && PLAYER::PLAYER_PED_ID() != peds[OffsetID])
			{
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(peds[OffsetID], false);
				FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 0, 1000.f, true, false, 0.f);
			}
		}
	}

	bool Misc::explodenearbyvehiclesbool = false;
	void Misc::explodenearbyvehicles()
	{
		const int ElementAmount = 10;
		const int ArrSize = ElementAmount * 2 + 2;

		Vehicle* vehs = new Vehicle[ArrSize];
		vehs[0] = ElementAmount;
		int VehFound = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehs);

		for (int i = 0; i < VehFound; i++)
		{
			int OffsetID = i * 2 + 2;
			if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))
			{
				features::RequestControlOfEnt(vehs[OffsetID]);
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(vehs[OffsetID], false);
				FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 0, 1000.f, true, false, 0.f);
			}
		}
		delete vehs;
	}

	bool Misc::deletenearbyvehiclesbool = false;
	void Misc::deletenearbyvehicles()
	{
		const int ElementAmount = 10;
		const int ArrSize = ElementAmount * 2 + 2;

		Vehicle* vehs = new Vehicle[ArrSize];
		vehs[0] = ElementAmount;
		int VehFound = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehs);

		for (int i = 0; i < VehFound; i++)
		{
			int OffsetID = i * 2 + 2;
			if (vehs[OffsetID] != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))
			{
				features::RequestControlOfEnt(vehs[OffsetID]);
				ENTITY::SET_ENTITY_COORDS(vehs[OffsetID], 6400.f, 6400.f, 0.f, false, false, false, false);
			}
		}
		delete vehs;
	}

	bool Misc::playertenkped = false;
	void Misc::TenKPedMoney(bool toggle)
	{
		features::TimePD = timeGetTime();
		if ((timeGetTime() - features::TimePD) > 1000) {
			Player playerPed = PLAYER::PLAYER_PED_ID();
			int TenK = 10000;
			Ped ClonedPedMoney = PED::CLONE_PED(playerPed, ENTITY::GET_ENTITY_HEADING(playerPed), 1, 1);
			ENTITY::SET_ENTITY_VISIBLE(ClonedPedMoney, false, false);
			PED::SET_PED_MONEY(ClonedPedMoney, TenK);
			ENTITY::SET_ENTITY_HEALTH(ClonedPedMoney, 0);
			PED::DELETE_PED(&ClonedPedMoney);
			features::TimePD = timeGetTime();
		}
	}

	int Misc::amount = 0;
	bool Misc::banked = false;
	bool Misc::giver = false;

	void Misc::deposit(long amount)
	{
		int iVar0;
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("mpply_last_mp_char"), &iVar0, -1);
		UNK3::_NETWORK_TRANSFER_WALLET_TO_BANK(iVar0, amount);
		UNK3::_NETWORK_SHOP_CASH_TRANSFER_SET_TELEMETRY_NONCE_SEED();
	}

	void Misc::withdraw(long amount)
	{
		int iVar0;
		STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("mpply_last_mp_char"), &iVar0, -1);
		UNK3::_NETWORK_TRANSFER_BANK_TO_WALLET(iVar0, amount);
		UNK3::_NETWORK_SHOP_CASH_TRANSFER_SET_TELEMETRY_NONCE_SEED();
	}

	bool Misc::savenewdrop = false;
	void Misc::cashdrop(bool toggle)
	{
		Ped iPed = PLAYER::PLAYER_PED_ID();

		int amount = 39999;

		if ((timeGetTime() - features::TimePD1) > 1000) // Time between drops
		{
			STREAMING::REQUEST_MODEL(PROP_MONEY_BAG_01);
			if (!STREAMING::HAS_MODEL_LOADED(PROP_MONEY_BAG_01)) {
				features::WAIT(0);
			}
			else {
				Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(iPed, FALSE);
				OBJECT::CREATE_AMBIENT_PICKUP(PICKUP_MONEY_CASE, playerPosition.x, playerPosition.y, playerPosition.z + 0.5f, 0, amount, PROP_MONEY_BAG_01, FALSE, TRUE);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PROP_MONEY_BAG_01);

				features::TimePD1 = timeGetTime();

			}
		}
	}
}
