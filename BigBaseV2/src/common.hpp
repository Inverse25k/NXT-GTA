#pragma once

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Winmm.lib")

#include <SDKDDKVer.h>
#include <Windows.h>
#include <D3D11.h>
#include <wrl/client.h>
#include <cinttypes>
#include <cstddef>
#include <cstdint>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <atomic>
#include <mutex>
#include <thread>
#include <memory>
#include <new>
#include <sstream>
#include <string>
#include <string_view>
#include <algorithm>
#include <functional>
#include <utility>
#include <stack>
#include <vector>
#include <typeinfo>
#include <type_traits>
#include <exception>
#include <stdexcept>
#include <any>
#include <optional>
#include <variant>
#include <time.h>
#include <timeapi.h>

#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <StackWalker.h>

#include "logger.hpp"

#include "Features/Car/Car.h"
#include "Features/Gun/Gun.h"
#include "Features/Local/Local.h"
#include "Features/Misc/Misc.h"
#include "Features/Online/Online.h"

#define NAME "NXT-G3N"

#define keypushed(key) GetAsyncKeyState(key) & 0x8000
namespace big
{
	using namespace std::chrono_literals;
	
	template <typename T>
	using comptr = Microsoft::WRL::ComPtr<T>;

	inline HMODULE g_hmodule{};
	inline HANDLE g_main_thread{};
	inline DWORD g_main_thread_id{};
	inline std::atomic_bool g_running{ true };
	
	struct stackwalker : public StackWalker
	{
		using StackWalker::StackWalker;

		void OnOutput(LPCSTR szText) override
		{
			g_logger->raw(log_color::red, szText);
		}
	};

	inline stackwalker g_stackwalker;
}
