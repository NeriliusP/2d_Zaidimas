#include "Enemy.h"

//Constructors/destructors
Enemy::Enemy(Texture* texture, float pos_x, float pos_y, float dir_x, float move_speed, int hpMax, int points)
{	
	this->tank.setTexture(*texture);
	this->tank.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = 0;
	this->moveSpeed = move_speed;
	this->hpMax = hpMax;
	this->hp = hpMax;
	this->points = points;
}

Enemy::~Enemy()
{

}

//Accessors
const FloatRect Enemy::getBounds() const
{
	return this->tank.getGlobalBounds();
}
const int& Enemy::getpoints() const
{
	return this->points;
}
const int& Enemy::returnHP() const
{
	return this->hp;
}
//Functions
void Enemy::loseHP(const int value)
{
	this->hp -= value;
	if(this->hp < 0)
	{
		this->hp = 0;
	}
}
void Enemy::update()
{
	this->tank.move(this->moveSpeed * this->direction);
}
void Enemy::render(RenderTarget* target)
{
	target->draw(this->tank);
}
