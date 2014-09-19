#include <iostream>

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Button.h"
#include "MapTile.h"
#include "GameGui.h"
#include "GameScreen.h"

GameScreen::GameScreen()
{
	this->active = true;
}

int GameScreen::Run(sf::RenderWindow &Win)
{
	cout << "Loading Game Screen..." << endl << endl;
	
	sf::Sprite background;
	sf::Texture ocean; //taken from www.GodsAndIdols.org
	if ( !ocean.loadFromFile("resources/water.png")) {
		cout << "Error Loading Ocean Sprite...." << endl << endl;
		return (-1);
	}
	background.setTexture(ocean);
	background.setScale(1.2f, 1.2f);

	Map m_map;
	GameGui m_gui(buttonList);

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
			/*if (Event.type == sf::Event::MouseButtonReleased)
			{
				return 0;
			}*/
        }
		Win.clear();
		Win.draw(background);
		m_map.drawMap(Win);
		m_gui.drawGui(Win);
		Win.display();
    }

	return (-1);
}