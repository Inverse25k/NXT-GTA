#pragma once
#include "common.hpp"

namespace big::features
{
	void run_tick();
	void script_func();

	extern HANDLE mainFiber;
	extern DWORD wakeAt;

	extern int TimePD;
	extern int TimePD1;
	extern int TimePD2;
	extern int TimePD3;
	extern int TimePD4;
	extern int TimePD5;
	extern int TimePD6;
	extern int TimePD7;
	extern int TimePD8;

	void RequestControlOfid(Entity netid);
	void RequestControlOfEnt(Entity entity);
	void ApplyForceToEntity(Entity e, float x, float y, float z);
	void WAIT(DWORD ms);
	bool RequestNetworkControl(uint vehID);
	bool cstrcmp(const char* s1, const char* s2);
	float degToRad(float degs);
	float Get3DDistance(Vector3 a, Vector3 b);
	Hash $(std::string str);
}
