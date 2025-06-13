#include <Windows.h>
#include <cstdint>

#include "game/sdk/sdk.hpp"

void entry( )
{
	auto u_world = sdk::u_world_t::get( );
	if ( !memory_utils_t::is_address_valid( u_world ) )
		return;

	auto subsystem = reinterpret_cast< sdk::u_subsystem_blueprint_library_t* >( sdk::u_gameplay_statics_t::static_class( ) );
	if ( !memory_utils_t::is_address_valid( subsystem ) )
		return;

	auto game_instance_subsystem = subsystem->get_game_instance_subsystem( u_world, sdk::u_deceit_cloud_subsystem_t::static_class( ) );
	if ( !memory_utils_t::is_address_valid( game_instance_subsystem ) )
		return;

	auto deceit_cloud_subsystem = reinterpret_cast< sdk::u_deceit_cloud_subsystem_t* >( game_instance_subsystem );
	if ( !memory_utils_t::is_address_valid( deceit_cloud_subsystem ) )
		return;

	auto social_client = deceit_cloud_subsystem->social_client( );
	if ( !memory_utils_t::is_address_valid( social_client ) )
		return;

	social_client->set_legacy_enabled( true );

	MessageBoxA( nullptr, "done", "status", MB_OK );
}

bool __stdcall DllMain( [[maybe_unused]] void* _instance, const uint32_t _call_reason, [[maybe_unused]] void* _reserved )
{
	if ( _call_reason != 1 )
		return false;

	entry( );

	return true;
}