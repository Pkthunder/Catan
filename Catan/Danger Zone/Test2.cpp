
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>

#include "Testers.h"

void Test2()
{
	sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "TMX Loader");
	renderWindow.setVerticalSyncEnabled(true);

	//create map loader and load map
	tmx::MapLoader ml("maps\\");
	ml.Load("isometric_grass_and_water.tmx");

	//update the quad tree once so we can see it when drawing debug
	ml.UpdateQuadTree(sf::FloatRect(0.f, 0.f, 800.f, 600.f));

	bool showDebug = false;
	sf::Clock frameClock;

	//View Testing
	sf::View v = renderWindow.getView();
	v.setCenter(0, 350);
	renderWindow.setView(v);

	//-----------------------------------//

	while(renderWindow.isOpen())
	{
		//poll input
		sf::Event event;
		while(renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderWindow.close();
			if(event.type == sf::Event::KeyPressed)
			{
				switch(event.key.code)
				{
				case sf::Keyboard::F:
					showDebug = !showDebug;
					break;
				case sf::Keyboard::Q:
					renderWindow.close();
					break;
				case sf::Keyboard::W:
					if (v.getCenter().y > 100) {
						v.move(0, -25);
					}
					break;
				case sf::Keyboard::S:
					if (v.getCenter().y < 575) {
						v.move(0, 25);
					}
					break;
				case sf::Keyboard::A:
					if (v.getCenter().x > -450) {
						v.move(-25, 0);
					}
					break;
				case sf::Keyboard::D:
					if (v.getCenter().x < 450) {
						v.move(25, 0);
					}
					break;
				case sf::Keyboard::T:
					v.zoom(0.5f);
					break;
				case sf::Keyboard::R:
					v = renderWindow.getDefaultView();
					v.setCenter(0, 350);
					break;
				default: break;
				}
			}
        }
		////move objects about
		//std::vector<tmx::MapLayer>& layers = ml.GetLayers();
		//for(auto& l : layers)
		//{
		//	if(l.type == tmx::ObjectGroup)
		//	{
		//		for(auto& o : l.objects)
		//		{
		//			o.Move(0.f, 1.f);
		//			if(o.GetPosition().y > 600.f)
		//			{
		//				o.SetPosition(o.GetPosition().x, 0.f);
		//			}
		//		}
		//	}
		//}
		//ml.UpdateQuadTree(sf::FloatRect(0.f, 0.f, 800.f, 600.f));

		//draw
		frameClock.restart();
		renderWindow.clear();
		renderWindow.setView(v);
		renderWindow.draw(ml);
		if(showDebug) ml.Draw(renderWindow, tmx::MapLayer::Debug);//draw with debug information shown

		renderWindow.display();

		renderWindow.setTitle("Press D to Toggle debug shapes. " + std::to_string(1.f / frameClock.getElapsedTime().asSeconds()));
	}

	return;
}