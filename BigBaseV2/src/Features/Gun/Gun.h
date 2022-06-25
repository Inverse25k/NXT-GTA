#pragma once
#include "common.hpp"

namespace big
{
	namespace Gun
	{
		void UpdateLoop();

		extern bool inf;
		void noreloadv(bool toggle);

		extern bool rapidfire;
		void rapidmaker();

		extern bool expmeel;
		extern bool fireammo;
		extern bool expammo;
		extern bool rbgun;
		void Expmeels(bool toggle);
		void Fireammos(bool toggle);
		void Expammos(bool toggle);
		void RBGuner(bool toggle);
	}
}