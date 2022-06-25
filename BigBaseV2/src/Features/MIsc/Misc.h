#pragma once
#include "common.hpp"

namespace big
{
	namespace Misc
	{
		void UpdateLoop();

		void trapall();
		void teleporttocoords(Player player, Vector3 target);
		void teleportallcoords(Vector3 target);
		void teleportallcoordsns(Vector3 target);
		void clearanim();
		void doAnimation(char* anim, char* animid);
		void animatePlayer(Player target, char* dict, char* anim);

		extern int attachobj[100];
		extern int nuattach;
		void attachobjects2(char* object);

		extern bool killpedsbool;
		void killpeds();

		extern bool explodepedsbool;
		void explodepeds();

		extern bool explodenearbyvehiclesbool;
		void explodenearbyvehicles();

		extern bool deletenearbyvehiclesbool;
		void deletenearbyvehicles();

		extern int amount;
		extern bool banked;
		extern bool giver;
		void deposit(long amount);
		void withdraw(long amount);

		extern bool savenewdrop;
		void cashdrop(bool toggle);

		extern bool playertenkped;
		void TenKPedMoney(bool toggle);
	}
}