#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Button.h"
#include "Gui.h"
#include "Player.h"

enum tGameState { Playing, Pause, Loading };

class Game {
private:
	tGameState state;
	cPlayer players[4];
	Gui& the_Gui;
	cPlayer* currTurn;
	
public:
	Game();

	void RunGame();
	unsigned int DiceRoll();
	void determineTurnOrder();
	void nextTurn();
	void tradeResources();
	void buildRoad();
	void buildSettlement();
	void buildCity();

	void transitionState();
	void onLeaveState();
	void onEnterState();
};

#endif