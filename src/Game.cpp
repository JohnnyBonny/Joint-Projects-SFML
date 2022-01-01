#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;

	//game logic
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
	this->mouseHeld = false;
	this->health = 10;
	this->endGame = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "ClickerGame", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5, 0.5));
	this->enemy.setFillColor(sf::Color::Cyan);
	// this->enemy.setOutlineColor(sf::Color::Green);
	// this->enemy.setOutlineThickness(5.f);
}

void Game::initFonts()
{
	if (this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
		std::cout << "Error::Game::INITFONTS::FAILED TO LOAD FONT"
				  << "\n";
}

void Game::initTexts()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initTexts();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}
//Accessors
bool Game::running() const
{
	return this->window->isOpen();
}

bool Game::getEndGame() const
{
	return this->endGame;
}

//Functions
void Game::spawnEnemy()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f);

	this->enemy.setFillColor(sf::Color::Green);

	this->enemies.push_back(this->enemy);
}
void Game::pollsEvents()
{
	//Event Polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
			case sf::Event::Closed:
				this->window->close();
				break;

			case sf::Event::KeyPressed:
				if (this->ev.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;

			default:
				break;
		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mosuePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

//Updates the text of the game
void Game::updateText()
{
	std::stringstream ss;

	ss << "Points:" << this->points << "\n"
	   << "Health: " << this->health << "\n";

	this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
	//updating the time for enemy spawning
	if (static_cast<int>(this->enemies.size()) < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = .0f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Moving and updating enemies
	for (int i = 0; i < (static_cast<int>(this->enemies.size())); i++)
	{
		this->enemies[i].move(0.f, 2.f);

		//of enemy is past the bottom of the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
		}
	}
	//check if clicked
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mosuePosView))
				{
					//delete enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
					this->points += 10.f;
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

//everything is being calculated behind the scenes
void Game::update()
{
	this->pollsEvents();

	if (this->endGame == false)
	{
		this->updateMousePositions();
		//updates mouse position relative to the screen
		//std::cout << "Mouse pos: " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << "\n";

		//relative to the window
		//std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";

		this->updateText();

		this->updateEnemies();
	}

	if (this->health <= 0)
	{
		this->endGame = true;
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

//seeing the calculations
void Game::render()
{
	/*
		-clear old frame
		-render objects
		-display frame in windows
		renders the game objects
	*/
	this->window->clear();

	this->renderEnemies(*this->window);

	this->renderText(*this->window);
	//draw game objects
	this->window->display();
}
