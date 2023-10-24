#pragma once

#include <iostream>;
#include <SFML/Graphics.hpp>;
#include <SFML/System.hpp>;

using namespace sf;
using namespace std;

class Shell
{
private:
	//Objects
	Sprite shell;
	Texture* texture;
	Vector2f direction;
	//Variables
	float moveSpeed;
public:
	//Constructor/destructor
	Shell(Texture* texture, float pos_X, float pos_Y, float dir_X, float move_Speed);
	~Shell();
	//Accessors
	const FloatRect getBounds() const;
	//Functions
	void update();
	void render(RenderTarget* target);
};

