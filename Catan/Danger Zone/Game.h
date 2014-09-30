#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include <random>
#include "Globals.h"
#include "Button.h"
#include "GameGui.h"
#include "GameData.h"

enum GameState { Loading, Pause, SwitchTurn, DiceRoll, PayOut, PlayerTurn, BuyRoad, BuySettlement, BuyCity, Trade, DrawCard, Winner, Done};

class ResourceManager {
private:
	vector<PlayerOBJ*> &m_player_list;
	Cost* m_payout[4][11]; //2D holding the payouts for each player, for each dice roll

public:
	//ResourceManager();
	ResourceManager( vector<PlayerOBJ*> &players );
	void addPlayer( PlayerOBJ *player );
	void adjustPayout ( int const player_id, int const tile_num, ResourceType re );
	void distributeResources( int const dice_roll );
};

//a singleton object
class Game {
private:
	GameState m_state;
	PlayerOBJ *m_curr_turn;
	GameGui &m_gui;
	vector<PlayerOBJ*> m_players_list;
	ResourceManager m_manager;
	//GameData m_data; //add to game soon

	static mt19937 dice;
	static uniform_int_distribution<unsigned int> roll;
	
public:
	Game( GameGui  &gui );
	void runTurn();
	void runDiceRoll();
	void update(); //update the game screen
};

#endif