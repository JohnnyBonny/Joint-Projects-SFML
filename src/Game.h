#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <iostream>
#include <sstream>
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
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game Objects
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;

	//Private functions
	void initVariables();
	void initWindow();
	void initEnemies();
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
	void updateText();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};