#pragma once
#include<iostream>
#include<vector>
#include<ctime>
#include<map>
#include<string>
#include<sstream>

#include "Player.h";
#include "Enemy.h";
#include "Shell.h";
using namespace std;
using namespace sf;
//Wrapper class



class Game
{
private:

	//Variables
	bool gameEnd;
	float spawnTimerMax;
	float spawnTimer;
	int maxEnemy;
	int type;
	unsigned points;
	int kills;
	//Window
	RenderWindow* window;
	VideoMode video;
	Event ev;

	//Game objects
	Player* player;
	map<string, Texture*> textures;
	vector<Shell*> shells;
	vector<Enemy*> enemies;
	
	//GUI
	Font font;
	Text pointText;
	Text gameOverText;
	//World
	Texture backgroundTexture;
	Sprite worldBackground;
	//Private functions
	void initWindow();
	void initGUI();
	void initWorld();
	void initTextures();
	void initPlayer();
	void initVariables();
public:
	//contructors / destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool getWindowIsOpen() const;

	//Functions
	void pollEvents();
	void updateInput();
	void updateCollision();
	void updateShell();
	void updateEnemy_Combat();
	void updateGUI();
	void run();
	void update();
	void renderWorld();
	void renderGUI();
	void render();
};

