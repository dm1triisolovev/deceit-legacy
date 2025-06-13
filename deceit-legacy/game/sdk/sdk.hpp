#pragma once

#include "../../memory/memory.hpp"

#define FUNCTION_TYPE( type, name, address, ... ) \
		using fn = type(*)( __VA_ARGS__ ); \
		const auto fn_##name = reinterpret_cast<fn>( address )

namespace sdk
{
	struct u_class_t{};
	struct u_object_t
	{
		__forceinline static __int64* u_class_find_object( void* _outer, const wchar_t* _name )
		{
			const auto base = reinterpret_cast< uintptr_t >( GetModuleHandleA( nullptr ) );

			FUNCTION_TYPE( __int64*, u_class_find_object_ptr, base + 0x12af2f0, void*, const wchar_t* );
			if ( !memory_utils_t::is_address_valid( fn_u_class_find_object_ptr ) )
				return nullptr;

			return fn_u_class_find_object_ptr( _outer, _name );
		}

		template<typename T>
		__forceinline static T find_object( const wchar_t* _name, u_object_t* _outer = nullptr )
		{
			return static_find_object<T>( nullptr, _outer, _name );
		}

		template<typename T>
		__forceinline static T static_find_object(u_object_t* _this, u_object_t* _outer, const wchar_t* _name )
		{
			const auto base = reinterpret_cast< uintptr_t >( GetModuleHandleA( nullptr ) );

			FUNCTION_TYPE( T, static_find_object_ptr, base + 0x1472910, u_object_t*, u_object_t*, const wchar_t* );
			if ( !memory_utils_t::is_address_valid( fn_static_find_object_ptr ) )
				return nullptr;

			return fn_static_find_object_ptr( _this, _outer, _name );
		}

		__forceinline void process_event(u_object_t* _func, void* _args )
		{
			const auto base = reinterpret_cast< uintptr_t >( GetModuleHandleA( nullptr ) );

			FUNCTION_TYPE( void, process_event_ptr, base + 0x14685c0, u_object_t*, u_object_t*, void* );
			if ( !memory_utils_t::is_address_valid( fn_process_event_ptr ) )
				return;

			return fn_process_event_ptr( this, _func, _args );
		}
	};

	struct u_world_t : u_object_t
	{
		static u_world_t* get( )
		{
			const auto base = reinterpret_cast< uintptr_t >( GetModuleHandleA( nullptr ) );
			return memory_utils_t::read<u_world_t*>( base + 0x9dbf848 );
		}
	};
}