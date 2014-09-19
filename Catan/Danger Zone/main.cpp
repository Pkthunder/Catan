#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
//#include "Testers.h"
#include "Globals.h"
#include "Screen.h"
#include "GameScreen.h"

using namespace std;

ResourceType getResourceType( unsigned int index )
{
	switch( index ) {
	case 0:
		return Wood;
	case 1:
		return Shep;
	case 2:
		return Whet;
	case 3:
		return Stone;
	case 4:
		return Clay;
	default:
		return Error;
	};

	return Error;
}
//For Later Expansion
//
int main(int argc, char** argv)
{
    std::vector<cScreen*> Screens;
    int screen = 0;

	sf::RenderWindow App(sf::VideoMode(SCRNWIDTH, SCRNHEIGHT), "Settlers of Catan");

    //Screens preparations
    MainMenu main;
    Screens.push_back(&main);
    GameScreen game;
    Screens.push_back(&game);
	/*TempScreen ts1(sf::Color::Cyan);
	Screens.push_back(&ts1);*/
	TempScreen ts2(sf::Color::Red);
	Screens.push_back(&ts2);
	TempScreen ts3(sf::Color::Green);
	Screens.push_back(&ts3);

    //Main loop
	while (screen >= 0 && App.isOpen())
    {
        screen = Screens[screen]->Run(App);
    }

    return 0;
}
