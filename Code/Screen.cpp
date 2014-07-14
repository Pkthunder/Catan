// Code based off the example given at https://github.com/LaurentGomila/SFML/wiki/Tutorial:-Manage-different-Screens

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Screen.h"

using namespace std;

//Helper Class
int ButtonTracker::currId = 0;

ButtonTracker::ButtonTracker() : id(-1) {}

ButtonTracker::ButtonTracker(sf::Shape* shape, ButtonType type, int subtype) : id(currId++)
{
	this->obj = (sf::Drawable*)shape;
	this->type = type;
	this->subtype = subtype;
	currId = id;
	sf::Vector2f pos = shape->getPosition();
	xMin = pos.x;
	xMax = pos.x + shape->getGlobalBounds().width;
	yMin = pos.y;
	yMax = pos.y + shape->getGlobalBounds().height;
}

ButtonTracker::ButtonTracker(sf::Text* text, ButtonType type, int subtype) : id(currId++)
{
	this->obj = (sf::Drawable*)text;
	this->type = type;
	this->subtype = subtype;
	currId = id;
	sf::Vector2f pos = text->getPosition();
	xMin = pos.x;
	yMin = pos.y;
	xMax = pos.x + (text->findCharacterPos( (text->getString().getSize()) - 1).x - text->findCharacterPos(0).x);
	yMax = text->getCharacterSize() + pos.y;
}

ButtonTracker* ButtonTracker::wasClicked(const sf::Event* click)
{
	cout << "Mouse Coords: " << click->mouseButton.x << ", " << click->mouseButton.y <<
		"\nButton Coords: " << xMin << "-" << xMax << ", " << yMin << "-" << yMax << endl;

	if (click->mouseButton.x >= xMin && click->mouseButton.x <= xMax &&
		click->mouseButton.y >= yMin && click->mouseButton.y <= yMax )
	{
		return &(*this);
	}

	return NULL; //no buttons were clicked
}

int ButtonTracker::clickHandler()
{
	switch(type) {
		
	case Navigation:
		return subtype;
		break;

	default:
		cout << "No Click Handler Written" << endl << endl;
		return 0;
		break;
	};

	return 0; //should never reach this point
}

cScreen::cScreen(){}

MainMenu::MainMenu(void)
{
	active = false;
}

//Sets up and displays everything on this screen
int MainMenu::Run(sf::RenderWindow &Win)
{
	cout << "Loading Main Menu..." << endl << endl;
	enum SubType { Exit_Btn = -1, QuickStart_Btn = 1, CreateGame_Btn = 2, BuildMap_Btn = 3 };

	active = true;
	sf::Sprite background;
	sf::Font font;
	sf::Text QuickStart;
	sf::Text CreateGame;
	sf::Text BuildMap;
	sf::Text Exit;
	sf::CircleShape CursorMarker;
	sf::FloatRect sRect;
	float yRef = 0.0f; //holds the size of each line (y axis) for spacing purposes
	vector<sf::Shape*> drawQue;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Create Background
	sf::Texture background_pic;
	if (!background_pic.loadFromFile("resources/green_grassland_wide.jpg"))
	{
		cout << "Error Loading Background..." << endl << endl;
		return (-1);
	}
	background.setTexture(background_pic);
	background.setScale(0.4f, 0.55f);
	drawQue.push_back((sf::Shape*)&background);
	cout << "Background Created!" << endl << endl;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Load Text
	if (!font.loadFromFile("resources/sansation.ttf"))
	{
		cout << "Font Loading Error..." << endl << endl;
		return (-1);
	}
	cout << "Font Loaded!" << endl << endl; 
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
	drawQue.push_back((sf::Shape*)&QuickStart);

	CreateGame.setString(sf::String("Create Game"));
	CreateGame.setFont(font);
	sRect = CreateGame.getLocalBounds();
	CreateGame.setPosition( buttonX, buttonY + yRef );
	CreateGame.setColor(sf::Color::White);
	yRef = sRect.height + 20.0f + yRef;
	drawQue.push_back((sf::Shape*)&CreateGame);

	BuildMap.setString(sf::String("Build a Map"));
	BuildMap.setFont(font);
	sRect = BuildMap.getLocalBounds();
	BuildMap.setPosition( buttonX, buttonY + yRef );
	BuildMap.setColor(sf::Color::White);
	yRef = sRect.height + 20.0f + yRef;
	drawQue.push_back((sf::Shape*)&BuildMap);

	Exit.setString(sf::String("Exit"));
	Exit.setFont(font);
	sRect = Exit.getLocalBounds();
	Exit.setPosition( buttonX, buttonY + yRef );
	Exit.setColor(sf::Color::White);
	yRef = sRect.height + 20.0f + yRef;
	drawQue.push_back((sf::Shape*)&Exit);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Register Each Button
	buttonList.push_back(new ButtonTracker(&QuickStart, Navigation, QuickStart_Btn));
	buttonList.push_back(new ButtonTracker(&CreateGame, Navigation, CreateGame_Btn));
	buttonList.push_back(new ButtonTracker(&BuildMap, Navigation, BuildMap_Btn));
	buttonList.push_back(new ButtonTracker(&Exit, Navigation, Exit_Btn));

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
                default:
                    break;
                }
            }
			//Click Events
			if (Event.type == sf::Event::MouseButtonReleased)
			{
				cout << "\n*******************************\nMouse Click Detected" << endl;

				switch (Event.mouseButton.button)
				{
				case sf::Mouse::Left:
					cout << "Processing Left Mouse Click" << endl;
					ButtonTracker *btn;
					for ( unsigned int i=0; i<buttonList.size(); i++ )
					{
						cout << "\nChecking Button Number " << i << endl;
						if ( (btn = buttonList[i]->wasClicked(&Event)) != NULL )
						{
							cout << "Button Click Detected! Processing...\n"
								<< "*******************************" << endl << endl;
							return btn->clickHandler();
						}
					}
					cout << "\nNon-Button Click Determined\n*******************************" << endl << endl;
				}
			}
        }
        Win.clear();
		for ( unsigned int i=0; i<drawQue.size(); i++ )
		{
			Win.draw(*drawQue[i]);
		}
        Win.display(); 
    }

	cout << "\n***Error with Main Function!***" << endl << endl;
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
	cout << "Loading Temp Screen..." << endl << endl;
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
                default:
                    break;
                }
            }
			//Click Events
			if (Event.type == sf::Event::MouseButtonReleased)
			{
				return 0;
			}
        }
		Win.clear(color);
		Win.display();
    }

	return (-1);
}