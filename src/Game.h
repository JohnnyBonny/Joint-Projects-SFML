#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>
class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mosuePosView;

	//Resources
	sf::Font font;

	//text
	sf::Text uiText;

	//Game Logic
	bool endGame;
	unsigned userClicks;		   // the amount of user clicks
	double passiveMultiplier;	   // number of passive clicks per second
	double clickMultiplier;		   //muliplier of clicks the users recieves when they click
	int PricePassiveMultiplier;	   //The price of Passive Multiplier
	int PriceClickerMuliplier;	   //The price of Clicker Multiplier
	double storeClickerMultiplier; //the Clicker Multiplier value in the store
	double storePassiveMuliplier;  //the Passive Multiplier value in the store
	bool mouseHeld;				   //checks to see if the user is holding down on the mouse
	sf::Time userTime;			   //Used to get the elapse time
	sf::Clock userClock;		   //Used to begin the timer for the program

	//Game Objects
	sf::CircleShape userClickerButton;				   //the object the user uses to add to their clicker score
	sf::RectangleShape upgradeClickedMultiplierButton; //the object to upgrade clicker mulitplier
	sf::RectangleShape upgradePassiveMultiplierButton; //the object to upgrade passive mulitplier

	//Private functions
	void initVariables();
	void initWindow();
	void initButtons();
	void initFonts();
	void initTexts();

public:
	//Constructors /Destructors
	Game();
	virtual ~Game();

	//Accessors
	bool running() const;
	bool getEndGame() const;

	//Functions
	void spawnEnemy();
	void pollsEvents();
	void updateMousePositions();
	void updateEnemies();
	void updateButtons();
	void updateText();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void renderButtons(sf::RenderTarget& target);
	void render();
};