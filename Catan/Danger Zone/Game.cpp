#include <SFML\Graphics.hpp>
#include <iostream>
#include <random>
#include "Globals.h"
#include "GameGui.h"
#include "Game.h"

// 2 3 4 5 6 |7| 8 9 10 11 12 = 11 possible rolls

//ResourceManager Class
//ResourceManager::ResourceManager(){};

ResourceManager::ResourceManager(vector<PlayerOBJ*> &players ) :
	m_player_list(players)
{
	for ( auto &c : m_payout ) { //create empty Cost objects on heap
		for ( auto &c2 : c ) {
			//c2 = new Cost(0, 0, 0, 0, 0); //actual
			c2 = new Cost(2, 3, 0, 1, 0); //for testing
		}
	}
}

void ResourceManager::addPlayer( PlayerOBJ *player )
{
	m_player_list.push_back(player);
}

void ResourceManager::adjustPayout( int const player_id, int const tile_num, ResourceType re )
{
	//excess player in player vector, then get dice roll number
	//subtraction is used to accomendate index difference from actual value
	//example: m_payout[player_id-1][tile_num-2]
	switch (re) {
	case Wood:
		m_payout[player_id-1][tile_num-2]->wood++;
	case Shep:
		m_payout[player_id-1][tile_num-2]->shep++;
	case Whet:
		m_payout[player_id-1][tile_num-2]->whet++;
	case Stone:
		m_payout[player_id-1][tile_num-2]->stone++;
	case Clay:
		m_payout[player_id-1][tile_num-2]->clay++;

	case Desert:
	case Error:
		std::cout << "Error with payout adjust system" << endl << endl;
		break;
	};
}

//Tested 9/30 - Resources Distributed Correctly
void ResourceManager::distributeResources( int const dice_roll )
{
	cout << "Distributing Resources..." << endl << endl;
	for ( auto &p : m_player_list ) { //for each player
		//place resources in the bank based on dice roll
		p->add_to_bank( (*m_payout[p->getId()-1][dice_roll-2]) );
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Statics
mt19937 Game::dice(static_cast<int>(time(0)));
uniform_int_distribution<unsigned int> Game::roll(1,6);

Game::Game( GameGui &gui ) : m_gui(gui), m_manager(ResourceManager(m_players_list))
{
	m_state = Loading;
	//temp hack version
	for ( unsigned int i=0; i<4; i++ ) {
		m_players_list.push_back( new PlayerOBJ(gui, i+1) );
	}
	m_curr_turn = m_players_list[0];
	//m_manager = ResourceManager( m_players_list );
}

//possibly the most important game function. Updates the Game Screen
void Game::update()
{
	//Update Resources:
	//m_curr_turn->getPlayerGui().updateResourceCount(m_curr_turn->getWallet());
	for ( auto &p : m_players_list ) {
		p->getPlayerGui().updateResourceCount(p->getWallet());
	}
}

void Game::runTurn()
{
	cout << "*************************************************************************" << endl << endl;
	cout << "Current Turn : " << m_curr_turn->getId() << endl << endl;
	runDiceRoll();
	cout << "Dice Rolled/Resources Distributed" << endl << endl;
	update();
	cout << "Game Screen Updated" << endl << endl;
	m_curr_turn = ( m_curr_turn->getId() == 4 ) ? m_players_list[0] : m_players_list[m_curr_turn->getId()];
	cout << "Switched User" << endl << endl;
}

//possibly temp function for development
void Game::runDiceRoll()
{
	//call twice, one for each die
	int r = roll(dice) + roll(dice);
	cout << "Rolling Dice....." << endl << endl;
	//elminate 7 for now, adjust later in development
	while ( r == 7 ) {
		r = roll(dice) + roll(dice);
		cout << "**NOTE: 7 Rolled, Elminated**" << endl << endl;
	}
	cout << r << " Was Rolled" << endl << endl;
	m_manager.distributeResources(r);
}