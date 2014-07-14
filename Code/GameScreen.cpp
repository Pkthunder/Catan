#include <iostream>

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "MapTile.h"
#include "Gui.h"
#include "GameScreen.h"

GameScreen::GameScreen()
{
	this->active = true;
}

int GameScreen::Run(sf::RenderWindow &Win)
{
	cout << "Loading Game Screen..." << endl << endl;
	
	sf::Sprite background;
	sf::Texture ocean;
	//taken from www.GodsAndIdols.org
	if ( !ocean.loadFromFile("resources/water.png")) {
		cout << "Error Loading Ocean Sprite...." << endl << endl;
		return (-1);
	}
	background.setTexture(ocean);
	background.setScale(1.2f, 1.2f);


	//Fix the 'add_to' functions to statics
	//and fix the player labels not positioning correctly
	Map m_map(3);
	Gui m_gui;
	PlayerGui player1(1);
	m_gui.add_to_Gui((cGuiElement*)&player1);
	PlayerGui player2(2);
	m_gui.add_to_Gui((cGuiElement*)&player2);
	PlayerGui player3(3);
	m_gui.add_to_Gui((cGuiElement*)&player3);
	PlayerGui player4(4);
	m_gui.add_to_Gui((cGuiElement*)&player4);

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
		Win.clear();
		Win.draw(background);
		m_map.drawMap(Win);
		m_gui.drawGui(Win);
		Win.display();
    }

	return (-1);
}