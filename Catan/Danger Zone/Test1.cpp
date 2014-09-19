#include <SFML/Graphics.hpp>

using namespace std;

void Test1() {
	bool isometric = false;

    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");

    sf::RectangleShape shape(sf::Vector2f(100,100));
	shape.setFillColor(sf::Color::Green);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(2);
	shape.setPosition(100,50);

	sf::RectangleShape shape2(sf::Vector2f(100,100));
	shape2.setFillColor(sf::Color::Red);
	shape2.setOutlineColor(sf::Color::White);
	shape2.setOutlineThickness(2);
	shape2.setPosition(200,50);

	sf::RectangleShape shape3(sf::Vector2f(100,100));
	shape3.setFillColor(sf::Color::Blue);
	shape3.setOutlineColor(sf::Color::White);
	shape3.setOutlineThickness(2);
	shape3.setPosition(100,150);

	sf::RectangleShape shape4(sf::Vector2f(100,100));
	shape4.setFillColor(sf::Color::Yellow);
	shape4.setOutlineColor(sf::Color::White);
	shape4.setOutlineThickness(2);
	shape4.setPosition(200,150);

	if ( isometric ) {
		shape.setRotation(45.f);
		shape.setPosition(shape.getPosition().x, shape.getPosition().y * 2);
		shape2.setRotation(45.f);
		shape2.setPosition(shape2.getPosition().x, shape2.getPosition().y * 2);
		shape3.setRotation(45.f);
		shape3.setPosition(shape3.getPosition().x, shape3.getPosition().y * 2);
		shape4.setRotation(45.f);
		shape4.setPosition(shape4.getPosition().x, shape4.getPosition().y * 2);
	}

	while (window.isOpen())
	{
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if ( isometric ) {
			window.clear();
		
			sf::View v = window.getDefaultView();
			v.setSize(v.getSize().x, v.getSize().y * 2);
			v.setCenter(v.getSize() *.5f);

			window.setView(v);
			window.draw(shape);
			window.draw(shape2);
			window.draw(shape3);
			window.draw(shape4);
			window.setView(window.getDefaultView());
		
			window.display();
		}
		else {
			window.clear();
			window.draw(shape);
			window.draw(shape2);
			window.draw(shape3);
			window.draw(shape4);
			window.display();
			}
	}

    return;
}