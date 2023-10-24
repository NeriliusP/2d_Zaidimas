#include "Game.h"




//Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initWorld();
	this->initPlayer();
	this->initTextures();
	this->initGUI();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	for(auto &i : this->textures)
	{
		delete i.second;
	}
	for(auto &i : this->shells)
	{
		delete i;
	}
	for (auto& i : this->enemies)
	{
		delete i;
	}
}
//Init's
void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode(1400, 800), "Tank Defence", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}
void Game::initGUI()
{
	if(!this->font.loadFromFile("Fonts/DeatheMaachNcv-2ejv.ttf"))
	{
		cout << "ERROR::GAME::INIT_GUI::Couldnt load font" << "/n";
	}
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(21);
	this->pointText.setFillColor(Color::White);
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(70);
	this->gameOverText.setFillColor(Color::White);
	this->gameOverText.setString("GAME OVER!!!!");
	this->gameOverText.setPosition(550.f, 350.f);

}
void Game::initWorld()
{
	if(!this->backgroundTexture.loadFromFile("Textures/Background.png"))
	{
		cout << "ERROR::GAME:INIT_WORLD::Couldnt load background" << "/n";
	}
	this->worldBackground.setTexture(this->backgroundTexture);

}
void Game::initTextures()
{
	this->textures["SHELL"] = new Texture();
	this->textures["SHELL"]->loadFromFile("Textures/AT_Shell.png");
	this->textures["ENEMY_LIGHT"] = new Texture();
	this->textures["ENEMY_LIGHT"]->loadFromFile("Textures/Light_Tank.png");
	this->textures["ENEMY_MEDIUM"] = new Texture();
	this->textures["ENEMY_MEDIUM"]->loadFromFile("Textures/Tank_Medium.png");
	this->textures["ENEMY_HEAVY"] = new Texture();
	this->textures["ENEMY_HEAVY"]->loadFromFile("Textures/Tank_Heavy.png");
}

void Game::initPlayer()
{
	this->player = new Player();
	
}

void Game::initVariables()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxEnemy = 5;
	this->kills = 0;
	this->points = 0;
	this->gameEnd = false;
}


//Accessors
const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}



//Functions
void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}
void Game::updateInput()
{
	//Up
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
	{
		this->player->movement(-1.f);
	}
	//Down
	if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
	{
		this->player->movement(1.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Space) && this->player->attack())
	{
		this->shells.push_back(new Shell(this->textures["SHELL"],this->player->getPos().x+100, this->player->getPos().y+4, 1.f, 10.f));
	}
}
void Game::updateCollision()
{
	//Top collision
	if(this->player->getBounds().top < 50.f)
	{
		this->player->setPosition(0.f, 50.f);
	}
	//Bottom collision
	if(this->player->getBounds().top + 100 > 800.f)
	{
		this->player->setPosition(0.f, 700.f);
	}
}
void Game::updateShell()
{
	unsigned counter = 0;
	for (auto* shell : this->shells)
	{
		shell->update();
		if(shell->getBounds().left > 1380.f)
		{
			delete this->shells.at(counter);
			this->shells.erase(this->shells.begin() + counter);
			--counter;
		}
		++counter;
	}
}
void Game::updateEnemy_Combat()
{
	//Enemy creation
	this->spawnTimer += 0.2f + this->kills*0.005;
	if(this->spawnTimer >= this->spawnTimerMax)
	{
		this->type = rand() % 3 + 1;
		switch (type)
		{
			case 1:
			{
				this->enemies.push_back(new Enemy(this->textures["ENEMY_LIGHT"], 1500.f, rand() % 650 + 50, -1.f, 4.f, 1, 5));
				this->spawnTimer = 0.f;
				break;
			}
			case 2:
			{
				this->enemies.push_back(new Enemy(this->textures["ENEMY_MEDIUM"], 1500.f, rand() % 650 + 50, -1.f, 3.f, 2, 10));
				this->spawnTimer = 0.f;
				break;
			}
				case 3:
			{
				this->enemies.push_back(new Enemy(this->textures["ENEMY_HEAVY"], 1500.f, rand() % 650 + 50, -1.f, 1.5f, 3, 15));
				this->spawnTimer = 0.f;
				break;
			}
				
			default:
			{
				break;
			}
		}	
	}
	//Combat
	for(int i=0; i<this->enemies.size(); i++)
	{
		bool shell_removed = false;
		this->enemies[i]->update();
		if(this->enemies[i]->getBounds().left <=200.f)
		{
			gameEnd = true;
		}
		for(size_t j=0; j< this->shells.size() && !shell_removed; j++)
		{
			if(this->shells[j]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
				this->enemies[i]->loseHP(1);
				delete this->shells[j];
				this->shells.erase(this->shells.begin() + j);
				if(this->enemies[i]->returnHP() == 0)
				{	
					this->points += this->enemies[i]->getpoints();
					delete this->enemies[i];
					this->enemies.erase(this->enemies.begin() + i);
					shell_removed = true;
					this->kills++;
				}
			}
		}
	}
}
void Game::updateGUI()
{
	stringstream score;
	score << "Points: " << this->points;
	this->pointText.setString(score.str());
}
void Game::run()
{
	while(this->window->isOpen())
	{
		this->pollEvents();
		if(!gameEnd)
		{
			this->update();
		}
		this->render();
	}
}
void Game::update()
{
	this->updateInput();
	this->updateCollision();
	this->updateShell();
	this->player->update();
	this->updateEnemy_Combat();
	this->updateGUI();
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
}

//Renders the game objects.
void Game::render()
{
		
	this->window->clear();
	//Draw world
	this->renderWorld();
	//Draw game objects
	this->player->render(*this->window);
	for(auto *shell : this->shells)
	{
		shell->render(this->window);
	}
	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}
	//Draw GUI
	this->renderGUI();
	//Draw game over screen
	if(gameEnd)
	{
		this->window->draw(this->gameOverText);
	}	
	this->window->display();
	}

