// Code based off the example given at https://github.com/LaurentGomila/SFML/wiki/Tutorial:-Manage-different-Screens

#ifndef SCREEN_H_
#define SCREEN_H_

#include <SFML/Graphics.hpp>

enum ButtonType { Navigation };

//Helper Class
class ButtonTracker
{
private:
	sf::Drawable* obj;
	//coords of the obj
	float xMin;
	float xMax;
	float yMin;
	float yMax;
	const int id;
	ButtonType type;
	int subtype;

	static int currId;

public:
	ButtonTracker();
	ButtonTracker(sf::Shape* shape, ButtonType type, int subtype);
	ButtonTracker(sf::Text* text, ButtonType type, int subtype);
	ButtonTracker* wasClicked(const sf::Event* click);
	int clickHandler();
};

class cScreen
{
public:
	cScreen();
	virtual int Run (sf::RenderWindow &Win) = 0;
	bool active; //true if the Main Menu is being displayed
	vector<ButtonTracker*> buttonList; //list of all 'clickable' objects
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