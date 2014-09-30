#ifndef GAMECARDS_H_
#define GAMECARDS_H_

#include <vector>
#include <functional>

enum GameCardType { VP, Knight, Effect };
enum EffectType { NONE, Soldier, VictoryPoint, Monopoly, RoadBuilding, YearOfPlenty}; //TODO: Fill in all card names and write functions for them

struct GameCard {
	GameCard( GameCardType const type, EffectType const effect );
	GameCardType const m_type;
	EffectType const m_effect;
	std::function<void(void*, void*)> m_effect_func;
	static GameCard* CreateCard();
	static std::vector<std::function<void(void*, void*)>> funcMap;
};

struct EffectFunc {
	//list of all effect functions, place in struct?
};

//Place raw data about card decks

//14 Soldiers
//5 Victory Points
//2 Monopoly
//2 Road Building
//2 Year of Plenty
//according to http://boardgames.stackexchange.com/questions/3437/how-has-the-composition-of-catans-development-card-deck-changed-over-time

#endif