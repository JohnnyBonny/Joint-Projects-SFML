#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;

	this->userClicks = 0;
	this->passiveMultiplier = 1.0;
	this->clickMultiplier = 1.0;
	this->PriceClickerMuliplier = 55;
	this->PricePassiveMultiplier = 55;
	this->storeClickerMultiplier = 5;
	this->storePassiveMuliplier = 2.5;
	this->mouseHeld = false;
	this->endGame = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "ClickerGame", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initButtons()
{

	this->userClickerButton.setPosition(sf::Vector2f(165.f, 50.f));
	this->userClickerButton.setRadius(225.f);
	this->userClickerButton.setFillColor(sf::Color::Cyan);

	this->upgradeClickedMultiplierButton.setPosition(sf::Vector2f(0.f, 530.f));
	this->upgradeClickedMultiplierButton.setSize(sf::Vector2f(300.f, 100.f));
	this->upgradeClickedMultiplierButton.setFillColor(sf::Color::Blue);

	this->upgradePassiveMultiplierButton.setPosition(sf::Vector2f(498.f, 530.f));
	this->upgradePassiveMultiplierButton.setSize(sf::Vector2f(300.f, 100.f));
	this->upgradePassiveMultiplierButton.setFillColor(sf::Color::Red);
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
	this->initButtons();
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
/*
void Game::spawnEnemy()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f);

	this->enemy.setFillColor(sf::Color::Green);

	this->enemies.push_back(this->enemy);
}
*/
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
	ss << "Clicks:" << this->userClicks << "\n";
	ss << "Passive Clicks:" << this->passiveMultiplier << "\n";
	ss << "Clicks per click:" << this->clickMultiplier << "\n";
	this->uiText.setString(ss.str());
}

void Game::updateButtons()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			if (this->userClickerButton.getGlobalBounds().contains(this->mosuePosView))
			{
				this->userClicks += clickMultiplier;
			}

			if (this->upgradeClickedMultiplierButton.getGlobalBounds().contains(this->mosuePosView))
			{
				if (userClicks >= static_cast<unsigned int>(PriceClickerMuliplier))
				{
					clickMultiplier += storeClickerMultiplier;
					PriceClickerMuliplier *= 1.5;
					storeClickerMultiplier *= 2.5;
					userClicks -= PriceClickerMuliplier;
				}
				else
				{
					std::stringstream ss;
					ss << "Sorry, not enough clicks!!"
					   << "\n";
					this->uiText.setString(ss.str());
				}
			}

			if (this->upgradePassiveMultiplierButton.getGlobalBounds().contains(this->mosuePosView))
			{
				if (userClicks >= static_cast<unsigned int>(PricePassiveMultiplier))
				{
					passiveMultiplier += storePassiveMuliplier;
					PricePassiveMultiplier *= 1.5;
					storePassiveMuliplier *= 2.5;
					userClicks -= PricePassiveMultiplier;
				}
				else
				{
					std::stringstream ss;
					ss << "Sorry, not enough clicks!!"
					   << "\n";
					this->uiText.setString(ss.str());
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}
/*
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
*/

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
		std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";

		this->updateText();

		//this->updateEnemies();
		this->updateButtons();
	}

	//if the user uses the right buttion, we exit the game
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		this->endGame = true;
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::renderButtons(sf::RenderTarget& target)
{
	target.draw(this->userClickerButton);
	target.draw(this->upgradeClickedMultiplierButton);
	target.draw(this->upgradePassiveMultiplierButton);
}
/*
void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}
*/
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

	//this->renderEnemies(*this->window);
	this->renderButtons(*this->window);
	this->renderText(*this->window);
	//draw game objects
	this->window->display();
}
