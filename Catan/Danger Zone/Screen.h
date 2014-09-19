// Code based off the example given at https://github.com/LaurentGomila/SFML/wiki/Tutorial:-Manage-different-Screens

#ifndef SCREEN_H_
#define SCREEN_H_

#include <SFML/Graphics.hpp>
#include "Button.h"

class cScreen
{
public:
	cScreen();
	virtual int Run (sf::RenderWindow &Win) = 0;
	bool active; //true if the Main Menu is being displayed
	vector<ButtonTracker*> buttonList; //list of all 'clickable' objects
	virtual int HandleScreenEvents(sf::Event &event); //generically handles common events, ie: click, etc
	void cScreen::RegisterButton(sf::Drawable &obj, const sf::FloatRect r, 
		const std::function<void(sf::Drawable&, ButtonEvent)> overCB,
		const std::function<int(sf::Drawable&)> clickCB); //adds a button to the list
};

class MainMenu : public cScreen
{
public:
	MainMenu(void);
	virtual int Run(sf::RenderWindow &Win);
};

class TempScreen : public cScreen
{
public:
	sf::Color color;
	TempScreen(sf::Color color);
	virtual int Run(sf::RenderWindow &Win);
};

//More Screens to be added later

#endif 