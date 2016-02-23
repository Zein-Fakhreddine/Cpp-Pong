#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <iostream>

//Declare funtions
void update();
void keyInput();
void resetGame();
bool getIntersection(const sf::RectangleShape& shape1, const sf::CircleShape& shape2);
bool getInterSectionWithGround(const sf::CircleShape& ball);

//Creates the window
sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Game");

//Creat Shapes
sf::RectangleShape plankOne(sf::Vector2f(10.f, 70.f));
sf::RectangleShape plankTwo(sf::Vector2f(10.f, 70.f));
sf::CircleShape ball(10.f);

//Declare Text
sf::Text titleText;

//Plank variables
const float plankSpeed = .2f;

//Ball variables
const float ballSpeed = .3f;
float ballMoveX = .05f;
float ballMoveY = .03f;

bool isPlaying = false;

int main()
{

	//Init Plank and ball
	plankOne.setFillColor(sf::Color::White);
	plankTwo.setFillColor(sf::Color::White);
	plankOne.setPosition(sf::Vector2f(10, 300));
	plankTwo.setPosition(sf::Vector2f(780, 300));
	ball.setFillColor(sf::Color::White);
	ball.setPosition(sf::Vector2f(400, 300));

	sf::Font font;
	if (font.loadFromFile("/arial.ttf"))
	{
		std::cout << "loaded file" << std::endl;
		titleText.setFont(font);
		titleText.setString("Press P tos tart the game!");
		titleText.setCharacterSize(24);
		titleText.setColor(sf::Color::White);
		titleText.setStyle(sf::Text::Bold | sf::Text::Underlined); 
	} 
	
	
	// run the program as long as the window is open
	while (window.isOpen()) {
		// check all windiw's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event)) {
			
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//Clear the window with the black color
		window.clear(sf::Color::Black);
		update();
		keyInput();
		window.display();
	}

	return 0;
}

void update() {

	//Draw shapes
	window.draw(plankOne);
	window.draw(plankTwo);
	window.draw(ball);

	if (!isPlaying) {
		window.draw(titleText);
		return;
	}
	//Simple bot ai for the plank
	plankTwo.move(0, (ball.getPosition().y + (rand() % 12) > plankTwo.getPosition().y && ballMoveX > 0) ? plankSpeed / 7 : ((ballMoveX > 0) ?  -plankSpeed / 7 : 0));
	
	if (getIntersection(plankOne, ball) || getIntersection(plankTwo, ball)) 
		ballMoveX = -ballMoveX;

	if (getInterSectionWithGround(ball))
		ballMoveY = -ballMoveY;
	ball.move(ballMoveX, ballMoveY);

	if (ball.getPosition().x > (800 - 10 - 20 - 1) || ball.getPosition().x < 10)
		resetGame();

}

void keyInput() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && !isPlaying) {
		isPlaying = true;
		std::cout << "Game has started" << std::endl;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();

	if (!isPlaying)
		return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (plankOne.getPosition().y >= 0))
		plankOne.move(0, -plankSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (plankOne.getPosition().y <= (window.getSize().y - plankOne.getSize().y)))
		plankOne.move(0, plankSpeed);

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) && (plankTwo.getPosition().y >= 0))
		plankTwo.move(0, -plankSpeed);
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))  && (plankTwo.getPosition().y <= (window.getSize().y - plankTwo.getSize().y)))
		plankTwo.move(0, plankSpeed);

}
 
bool getIntersection(const sf::RectangleShape& shape1, const sf::CircleShape& shape2) {
	sf::Rect<float> rect1(sf::Vector2<float>(shape1.getPosition().x, shape1.getPosition().y), sf::Vector2<float>(shape1.getSize().x, shape1.getSize().y));
	sf::Rect<float> rect2(sf::Vector2<float>(shape2.getPosition().x, shape2.getPosition().y), sf::Vector2<float>(shape2.getRadius() * 2, shape2.getRadius() * 2));
	if (rect1.intersects(rect2)) 
		return true;
	
	return false;
}

bool getInterSectionWithGround(const sf::CircleShape& ball) {
	if (ball.getPosition().y < 0 || (ball.getPosition().y + ball.getRadius() * 2) > 600)
		return true;

	return false;
}


void resetGame() {
	plankOne.setPosition(sf::Vector2f(10, 300));
	plankTwo.setPosition(sf::Vector2f(780, 300));

	ball.setPosition(sf::Vector2f(400, 300));
	isPlaying = false;
}

