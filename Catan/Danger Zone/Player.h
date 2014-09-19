#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "Gui.h"

class cPlayer {
private:
	const unsigned int playerId;
	PlayerGui* m_guiPtr;
	unsigned int knightCount;
	unsigned int victoryCount;
	unsigned int clayCount;
	unsigned int shepCount;
	unsigned int stoneCount;
	unsigned int whetCount;
	unsigned int woodCount;
	unsigned int advertiseArray[5];
public:
	cPlayer( Gui& the_Gui, const int playerId );
	void trade( const int opponentId );
	void advertise( const ResourceType type, const int value );
	void updateVictoryCount(const unsigned int value);
	void updateKnightCount(const unsigned int value);
	void updateResourceCount(const ResourceType type, const int value);
};




#endif