#pragma once

#include <cstdint>

struct memory_utils_t
{
	static constexpr uintptr_t minimum_user_address = 0x0000000000010000;
	static constexpr uintptr_t maximum_user_address = 0x00007fffffffffff;

	template<typename T>
	static uintptr_t to_address( T address )
	{
		return reinterpret_cast< uintptr_t >( address );
	}

	template<typename T> static bool is_address_valid( T address )
	{
		return to_address( address ) >= minimum_user_address && to_address( address ) <= maximum_user_address;
	}

	template< typename Type, typename PointerType >
	static Type& dereference( const PointerType _address )
	{
		return *reinterpret_cast< Type* >( _address );
	}

	template< typename Type, typename PointerType >
	static Type read( const PointerType _address )
	{
		return dereference< Type, PointerType >( _address );
	}
};