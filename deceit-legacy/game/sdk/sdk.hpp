#pragma once

#include "../../memory/memory.hpp"

#include "basic_types/basic_types.hpp"

#define FUNCTION_TYPE( type, name, address, ... ) \
		using fn = type(*)( __VA_ARGS__ ); \
		const auto fn_##name = reinterpret_cast<fn>( address )

namespace sdk
{
	struct u_class_t{};
	struct u_object_t
	{
		static u_class_t* find_class( const wchar_t* _name )
		{
			return reinterpret_cast< u_class_t* >( u_class_find_object( reinterpret_cast< void* >( -1 ), _name ) );
		}

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

	struct a_actor_t : u_object_t {};
	struct a_controller_t : a_actor_t
	{
		struct a_pawn_t* pawn( ) {
			if ( !memory_utils_t::is_address_valid( this ) )
				return nullptr;

			return memory_utils_t::read<struct a_pawn_t*>( this + 0x2E8 );
		}
	};

	struct a_player_controller_t : a_controller_t
	{
		struct a_pawn_t* acknowledged_pawn( ) {
			if ( !memory_utils_t::is_address_valid( this ) )
				return nullptr;

			return memory_utils_t::read<struct a_pawn_t*>( this + 0x350 );
		}
	};

	struct u_player_t : u_object_t
	{
		struct a_player_controller_t* player_controller( ) {
			if ( !memory_utils_t::is_address_valid( this ) )
				return nullptr;

			return memory_utils_t::read<a_player_controller_t*>( this + 30 );
		}
	};

	struct u_local_player_t : u_player_t {};
	struct u_game_instance_t
	{
		TArray<struct u_local_player_t*> local_players( ) {
			if ( !memory_utils_t::is_address_valid( this ) )
				return {};

			return memory_utils_t::read<TArray<struct u_local_player_t*>>( this + 0x38 );
		}
	};

	struct u_world_t : u_object_t
	{
		struct u_game_instance_t* owning_game_instance( ) {
			if ( !memory_utils_t::is_address_valid( this ) )
				return nullptr;

			return memory_utils_t::read<u_game_instance_t*>( this + 0x1D8 );
		}

		static u_world_t* get( )
		{
			const auto base = reinterpret_cast< uintptr_t >( GetModuleHandleA( nullptr ) );
			return memory_utils_t::read<u_world_t*>( base + 0x9dbf848 );
		}
	};

	struct u_blueprint_function_library_t : u_object_t{};
	struct u_gameplay_statics_t : u_blueprint_function_library_t
	{
		static u_class_t* static_class( )
		{
			static u_class_t* ptr = nullptr;
			if ( !ptr )
				ptr = find_class( L"Engine.GameplayStatics" );

			return ptr;
		}
	};

	struct u_subsystem : u_object_t
	{
		static u_class_t* static_class( )
		{
			static u_class_t* ptr = nullptr;
			if ( !ptr )
				ptr = u_object_t::find_class( L"Engine.Subsystem" );

			return ptr;
		}
	};

	struct u_game_instance_subsystem_t : u_subsystem
	{
		static u_class_t* static_class( )
		{
			static u_class_t* ptr = nullptr;
			if ( !ptr )
				ptr = u_object_t::find_class( L"Engine.GameInstanceSubsystem" );

			return ptr;
		}
	};

	struct u_subsystem_blueprint_library_t : u_blueprint_function_library_t
	{
		u_game_instance_subsystem_t* get_game_instance_subsystem( u_object_t* _ctx, u_class_t* _class )
		{
			static u_object_t* function = nullptr;
			if ( !function )
				function = find_object<u_object_t*>( L"Engine.SubsystemBlueprintLibrary.GetGameInstanceSubsystem" );

			struct {
				u_object_t* ctx_;
				u_class_t* class_;
				u_game_instance_subsystem_t* res_;
			}params;

			params.ctx_ = _ctx;
			params.class_ = _class;

			this->process_event( function, &params );

			return params.res_;
		}
	};

	struct u_social_client_t : u_object_t
	{
		void set_legacy_enabled( bool _enabled )
		{
			static u_object_t* function = nullptr;
			if ( !function )
				function = u_object_t::find_object<u_object_t*>( L"DeceitCloud.SocialClient.SetLegacyEnabled" );

			struct
			{
				bool enabled;
			}params;

			params.enabled = _enabled;

			this->process_event( function, &params );
		}
	};

	struct u_deceit_cloud_subsystem_t : u_game_instance_subsystem_t
	{
		struct u_social_client_t* social_client( ) {
			if ( !memory_utils_t::is_address_valid( this ) )
				return nullptr;

			return memory_utils_t::read<struct u_social_client_t*>( this + 0xE8 );
		}

		static u_class_t* static_class( ) {
			static u_class_t* ptr = nullptr;
			if ( !ptr )
				ptr = u_object_t::find_class( L"DeceitCloud.DeceitCloudSubsystem" );

			return ptr;
		}
	};
}