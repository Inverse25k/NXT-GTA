#pragma once
#include "common.hpp"
#include "logger.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "NativeUI/NativeUI.hpp"
#include "features.hpp"

namespace big
{
	namespace Online
	{
		void UpdateLoop();

		extern int selectedPlayer;
		void TeleportToPlayer(Player player);

		void LoadPlayerInfo(char* playerName, Player p);

		void trapcage(Ped ped);

		extern bool playerfireloop[35];
		void FireLoop(Player target);

		extern bool playerwaterloop[35];
		void WaterLoop(Player target);

		void Freezer(Player target);
		extern bool freezed[35];

		extern bool fuckedhandling[32];
		void fuckhandling(Player player);

		extern bool camshaker[32];
		void shakecam(Player target);

		extern bool exploder[32];
		void explodeloop(Player target);

		extern bool spectate[32];
		void specter(Player target);

		extern bool esper;
		void esp(Player target);

		extern int Levels[8000];
		void SetRank(int rpvalue);
	}
}