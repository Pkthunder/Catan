#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "Gui.h"
#include "Player.h"

using namespace std;

cPlayer::cPlayer( Gui& the_Gui, const int playerId ) : 
	m_guiPtr( the_Gui.getPlayerGui(playerId) ), playerId(playerId)
{
	unsigned int knightCount = 0;
	unsigned int victoryCount = 0;
	unsigned int clayCount = 0;
	unsigned int shepCount = 0;
	unsigned int stoneCount = 0;
	unsigned int whetCount  = 0;
	unsigned int woodCount = 0;
}

void cPlayer::trade( const int opponentId )
{
	return; //stub
}

void cPlayer::advertise( const ResourceType type, const int value )
{
	return; //stub
}

void cPlayer::updateVictoryCount(const unsigned int value)
{
	victoryCount = value;
	m_guiPtr->updateVictoryCount(value);
}

void cPlayer::updateKnightCount(const unsigned int value)
{
	knightCount = value;
	m_guiPtr->updateKnightCount(value);
}

void cPlayer::updateResourceCount(const ResourceType type, const int value)
{
	switch( type ) {
	case Clay:		clayCount = value;		break;
	case Shep:		shepCount = value;		break;
	case Stone:		stoneCount = value;		break;
	case Whet:		whetCount = value;		break;
	case Wood:		woodCount = value;		break;
	case Desert:
	case Error:
	default:		return;
	}
	m_guiPtr->updateResourceCount(type, value);
}