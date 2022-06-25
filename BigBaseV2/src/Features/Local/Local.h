#pragma once
#include "common.hpp"

namespace big
{
	namespace Local
	{
		void UpdateLoop();

		extern bool god;
		void God(bool enable);

		extern bool invisibility;
		void Invisibility(bool enable);

		extern bool playersuperjump;
		void SuperJump(bool toggle);

		extern bool mobileRadio;
		void mobilevoid(bool toggle);

		extern bool betiny;
		void TinyPlayer(bool toggle);
	}
}