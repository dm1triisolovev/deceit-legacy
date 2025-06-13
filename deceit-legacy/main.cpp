#include <Windows.h>
#include <cstdint>

#include "game/sdk/sdk.hpp"

bool __stdcall DllMain( [[maybe_unused]] void* _instance, const uint32_t _call_reason, [[maybe_unused]] void* _reserved )
{
	if ( _call_reason != 1 )
		return false;

	auto u_world = sdk::u_world_t::get( );
	if ( !memory_utils_t::is_address_valid( u_world ) )
		return false;

	auto m_local_player = u_world->owning_game_instance( )->local_players( )[0];
	if ( !memory_utils_t::is_address_valid( m_local_player ) )
		return false;

	auto player_controller = m_local_player->player_controller( );
	if ( !memory_utils_t::is_address_valid( player_controller ) )
		return false;

	auto pawn = player_controller->pawn( );
	if ( !memory_utils_t::is_address_valid( pawn ) )
		return false;

	return true;
}