#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Screen.h"

class GameScreen : public cScreen
{
public:
	GameScreen(void);
	virtual int Run(sf::RenderWindow &Win);
};

#endif