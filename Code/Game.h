#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "MapTile.h"

enum tGameState { Playing, Pause, Loading };

class Game {
private:
	tGameState state;

public:
	Game();

	void transitionState();
	void onLeaveState();
	void onEnterState();
};

#endif