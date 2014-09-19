#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

const int SRCNWIDTH = 800;
const int SRCNHEIGHT = 500;

vector<sf::CircleShape> tileLists;

void addShapes( sf::CircleShape s )
{
	tileLists.push_back(s);
}

//top = -1, bottom = 1
sf::CircleShape createLefts(sf::CircleShape parent, float top) 
{
	float r = parent.getRadius();
	sf::Vector2f center = parent.getPosition();
	float x = center.x, y = center.y; //coords for new shape

	cout << "************** Blue Hexagon *******************" << endl;
	cout << "x = " << x << endl
		<< "y = " << y << endl;
	x = x - r;
	float leg = 0.5f * r * sqrt(2);
	cout << "leg = " << leg << endl
		<< "radius = " << r << endl;
	//float leg2 = 73.48469;
	float leg2 = 36.742346;
	x = x - leg2;
	y = y + (leg2 * top);
	//trial and error offset
	y = y + (18.0f * top);

	sf::CircleShape shape(60, 6);
	shape.setFillColor(sf::Color::Blue);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(2);
	sf::FloatRect sRect = shape.getLocalBounds();
	shape.setOrigin( (sRect.left/2.0f) + sRect.width/2.0f,
						(sRect.top/2.0f) + sRect.height/2.0f);
	//shape.setOrigin( sRect.width/2.0f, sRect.height/2.0f );
	shape.setPosition(x,y);
	shape.rotate(90);
	sf::Vector2f temp = shape.getPosition();
	cout << "****new coords****" << endl;
	cout << "x = " << temp.x << endl
		<< "y = " << temp.y << endl;
	cout << "***********************************************" << endl << endl << endl;
	addShapes(shape);

	sf::CircleShape s2(5);
	s2.setFillColor(sf::Color::Red);
	s2.setOrigin(s2.getRadius()/2.0f, s2.getRadius()/2.0f);
	s2.setPosition(x,y);
	addShapes(s2);

	return shape;
}

void createRights( sf::CircleShape parent, float top ) {
	float r = parent.getRadius();
	sf::Vector2f center = parent.getPosition();
	float x = center.x, y = center.y; //coords for new shape

	x = x + 96.5f;
	y = y + (55.0f * top);

	sf::CircleShape shape(60, 6);
	shape.setFillColor(sf::Color::Yellow);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(2);
	sf::FloatRect sRect = shape.getLocalBounds();
	shape.setOrigin( (sRect.left/2.0f) + sRect.width/2.0f,
						(sRect.top/2.0f) + sRect.height/2.0f);
	shape.setPosition(x,y);
	shape.rotate(90);
	addShapes(shape);
}

void Test3() 
{

    sf::RenderWindow window(sf::VideoMode(SRCNWIDTH, SRCNHEIGHT), "Settlers of Catan");
	cout << "************** Map Info *******************" << endl;
	cout << "width = " << SRCNWIDTH << endl
		<< "height = " << SRCNHEIGHT << endl;
	cout << "***********************************************" << endl << endl << endl;

    sf::CircleShape shape(60, 6);
	shape.setFillColor(sf::Color::Green);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(2);

	//center the first hexagon
	sf::FloatRect sRect = shape.getLocalBounds();
	shape.setOrigin( (sRect.left/2.0f) + sRect.width/2.0f,
						(sRect.top/2.0f) + sRect.height/2.0f);
	//shape.setOrigin( sRect.width/2.0f, sRect.height/2.0f );
	shape.setPosition(sf::Vector2f(SRCNWIDTH/2.0f, SRCNHEIGHT/2.0f));
	shape.rotate(90);
	sf::Vector2f temp = shape.getPosition();
	cout << "************** Green Hexagon *******************" << endl;
	cout << "x = " << temp.x << endl
		<< "y = " << temp.y << endl;
	cout << "***********************************************" << endl << endl << endl;
	addShapes(shape);

	sf::CircleShape s2(5);
	s2.setFillColor(sf::Color::Red);
	s2.setOrigin(s2.getRadius()/2.0f, s2.getRadius()/2.0f);
	s2.setPosition(sf::Vector2f(SRCNWIDTH/2.0f, SRCNHEIGHT/2.0f));
	temp = s2.getPosition();
	cout << "************** Center Red Dot *******************" << endl;
	cout << "x = " << temp.x << endl
		<< "y = " << temp.y << endl;
	cout << "***********************************************" << endl << endl << endl;
	addShapes(s2);

	//Adding surrounding tiles
	sf::CircleShape s3 = createLefts(shape, -1.0f);
	sf::CircleShape s4 = createLefts(shape, 1.0f);
	//addShape(s3);
	createRights(shape, -1.0f);
	createRights(shape, 1.0f);

	while (window.isOpen())
	{
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch(event.key.code) {
				case sf::Keyboard::Q:
				case sf::Keyboard::Space:
					window.close();
					break;
				default: break;
				}
			}
		}
		window.clear();
		for ( unsigned int i = 0; i < tileLists.size(); i++ ) {
			window.draw( tileLists[i] );
		}
		window.display();
	}

    return;
}