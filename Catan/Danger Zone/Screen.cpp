// Code based off the example given at https://github.com/LaurentGomila/SFML/wiki/Tutorial:-Manage-different-Screens

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Button.h"
#include "Screen.h"

using namespace std;

cScreen::cScreen(){}

int cScreen::HandleScreenEvents(sf::Event &event)
{
	int result;
	for ( const auto &b : buttonList ) {
		result = b->HandleEvents(event);
		if (result != (-2) ) return result; //if not continue (-2), return result
	}
	return (-2); //do nothing
}

void cScreen::RegisterButton(sf::Drawable &obj, const sf::FloatRect r, 
		const std::function<void(sf::Drawable&, ButtonEvent)> overCB,
		const std::function<int(sf::Drawable&)> clickCB)
{
	buttonList.push_back(new ButtonTracker(obj, r, overCB, clickCB));
}

/////////////////////////////////////////////////////////////////////////

//Button Callback Registery - MainMenu
void Button_OverCB( sf::Drawable &obj, ButtonEvent type)
{
	switch (type) {
	case MouseEnter:
		static_cast<sf::Text&>(obj).setColor(sf::Color::Red);
		break;
	case MouseLeave:
		static_cast<sf::Text&>(obj).setColor(sf::Color::White);
		break;
	};
}

int QuickStart_ClickCB( sf::Drawable &obj)
{
	return 1;
}

int CreateGame_ClickCB( sf::Drawable &obj)
{
	return 2;
}

int BuildMap_ClickCB( sf::Drawable &obj)
{
	return 3;
}

int Exit_ClickCB( sf::Drawable &obj)
{
	cout << "Exit Callback Reached" << endl << endl;
	return (-1);
}

////////////////////////////////////////////////////////////////////
//Main Menu Member Functions

MainMenu::MainMenu(void)
{
	active = false;
}

//Sets up and displays everything on this screen
int MainMenu::Run(sf::RenderWindow &Win)
{
	std::cout << "Loading Main Menu..." << endl << endl;

	active = true;
	sf::Sprite background;
	sf::Font font;
	sf::Text QuickStart;
	sf::Text CreateGame;
	sf::Text BuildMap;
	sf::Text Exit;
	sf::FloatRect sRect;
	float yRef = 0.0f; //holds the size of each line (y axis) for spacing purposes
	vector<sf::Drawable*> drawQue;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Create Background
	sf::Texture background_pic;
	if (!background_pic.loadFromFile("resources/green_grassland_wide.jpg"))
	{
		std::cout << "Error Loading Background..." << endl << endl;
		return (-1);
	}
	background.setTexture(background_pic);
	background.setScale(0.4f, 0.6f);
	drawQue.push_back((sf::Drawable*)&background);
	std::cout << "Background Created!" << endl << endl;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Load Text
	if (!font.loadFromFile("resources/sansation.ttf"))
	{
		std::cout << "Font Loading Error..." << endl << endl;
		return (-1);
	}
	std::cout << "Font Loaded!" << endl << endl; 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Create the actual Menu Display
	float buttonX = 30.0f;
	float buttonY = SCRNHEIGHT*0.73f;

	QuickStart.setString(sf::String("Quick Start"));
	QuickStart.setFont(font);
	sRect = QuickStart.getLocalBounds();
	QuickStart.setPosition( buttonX, buttonY + yRef );
	QuickStart.setColor(sf::Color::White);
	yRef = sRect.height + 20.0f + yRef;
	drawQue.push_back((sf::Drawable*)&QuickStart);

	CreateGame.setString(sf::String("Create Game"));
	CreateGame.setFont(font);
	sRect = CreateGame.getLocalBounds();
	CreateGame.setPosition( buttonX, buttonY + yRef );
	CreateGame.setColor(sf::Color::White);
	yRef = sRect.height + 20.0f + yRef;
	drawQue.push_back((sf::Drawable*)&CreateGame);

	BuildMap.setString(sf::String("Build a Map"));
	BuildMap.setFont(font);
	sRect = BuildMap.getLocalBounds();
	BuildMap.setPosition( buttonX, buttonY + yRef );
	BuildMap.setColor(sf::Color::White);
	yRef = sRect.height + 20.0f + yRef;
	drawQue.push_back((sf::Drawable*)&BuildMap);

	Exit.setString(sf::String("Exit"));
	Exit.setFont(font);
	sRect = Exit.getLocalBounds();
	Exit.setPosition( buttonX, buttonY + yRef );
	Exit.setColor(sf::Color::White);
	yRef = sRect.height + 20.0f + yRef;
	drawQue.push_back((sf::Drawable*)&Exit);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Register Each Button
	RegisterButton(QuickStart, QuickStart.getGlobalBounds(), Button_OverCB, QuickStart_ClickCB );
	RegisterButton(CreateGame, CreateGame.getGlobalBounds(), Button_OverCB, CreateGame_ClickCB );
	RegisterButton(BuildMap, BuildMap.getGlobalBounds(), Button_OverCB, BuildMap_ClickCB );
	RegisterButton(Exit, Exit.getGlobalBounds(), Button_OverCB, Exit_ClickCB );

	sf::Event Event;
	while (active && Win.isOpen())
    {
		//cout << "Rendering...." << endl << endl;
		int result = (-2);
        while (Win.pollEvent(Event))
        {
			switch(Event.type) {

			case sf::Event::Closed:
				return (-1);

			case sf::Event::KeyReleased:
				switch (Event.key.code) {
					case sf::Keyboard::Q:
					case sf::Keyboard::Space:
						Win.close();
				};
				break;

			case sf::Event::MouseButtonPressed:
			case sf::Event::MouseMoved:
				result = HandleScreenEvents(Event);
				break;
				
			};
			if ( result != -2 ) return result;
        }
        Win.clear();
		for ( unsigned int i=0; i<drawQue.size(); i++ )
		{
			Win.draw(*drawQue[i]);
		}
        Win.display(); 
    }

	std::cout << "\n***Error with Main Function!***" << endl << endl;
	return (-1);
}

//****************************************************************************************************************************//

TempScreen::TempScreen(sf::Color color)
{
	this->color = color;
	this->active = true;
}

int TempScreen::Run(sf::RenderWindow &Win)
{
	std::cout << "Loading Temp Screen..." << endl << endl;
	sf::Event Event;
	while (active && Win.isOpen())
    {
		//cout << "Rendering...." << endl << endl;
        while (Win.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed)
            {
                return (-1);
            }
            //Key pressed
            if (Event.type == sf::Event::KeyPressed)
            {
                switch (Event.key.code)
                {
				case sf::Keyboard::Space:
                    Win.close();
                    break;
				case sf::Keyboard::B:
					return 0;
                default:
                    break;
                }
            }
        }
		Win.clear(color);
		Win.display();
    }

	return (-1);
}