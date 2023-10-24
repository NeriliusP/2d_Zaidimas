#pragma once

#include <SFML/Graphics.hpp>;
#include <SFML/System.hpp>;
#include <SFML/Window.hpp>;

using namespace sf;
using namespace std;
class Enemy
{
private:
	//Objects
	Sprite tank;
	Texture* texture;
	Vector2f direction;
	//Variables
	int hp;
	int hpMax;
	int points;
	float moveSpeed;
public:
	//Constructor / Destructor
	Enemy(Texture* texture, float pos_x, float pos_y, float dir_x, float move_speed, int hpMax, int points);
	virtual ~Enemy();
	//Accessors
	const FloatRect getBounds() const;
	const int& getpoints() const;
	const int& returnHP() const;
	//Functions
	void loseHP(const int value);
	void update();
	void render(RenderTarget* target);

};

