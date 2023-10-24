#pragma once

#include <iostream>;
#include <SFML/Graphics.hpp>;
#include <SFML/System.hpp>;
using namespace sf;
using namespace std;
class Player
{
private:

	//Objects
	Sprite sprite;
	Texture texture;
	//Variables
	float moveSpeed;
	float cooldown;
	float cooldownMax;
	int points;
	//Functions
	void initVariables();
	void initTexture();
	void initSprite();
public:
	//Constructor / Destructor
	Player(float x=0.f, float y=300.f);
	virtual ~Player();

	//Accessors
	const Vector2f& getPos() const;
	const FloatRect getBounds() const;

	//Functions
	void setPosition(const float x, const float y);
	void movement(const float dirY);
	const bool attack();
	void updateCooldown();
	void update();
	void render(RenderTarget& target);
};

