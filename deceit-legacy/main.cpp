#include <Windows.h>
#include <cstdint>

#include "game/sdk/sdk.hpp"

bool __stdcall DllMain( [[maybe_unused]] void* _instance, const uint32_t _call_reason, [[maybe_unused]] void* _reserved )
{
	if ( _call_reason != 1 )
		return false;

	

	return true;
}