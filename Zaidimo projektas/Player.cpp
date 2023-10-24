#include "Player.h"


//Constructors/Destructors
Player::Player(float x, float y)
{
	this->initTexture();
	this->initSprite();
	this->initVariables();

}

Player::~Player()
{
	
}
//Accessors
const Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}
const FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
//Functions
void Player::initVariables()
{
	this->moveSpeed = 5.f;
	this->cooldownMax = 100.f;
	this->cooldown = this->cooldownMax;
}

void Player::initTexture()
{
	if(!this->texture.loadFromFile("Textures/AT_Truck.png"))
	{
		cout << "ERROR::PLAYER::INIT_TEXTURE::Couldnt load texture file" << endl;
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.35f, 0.35f);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x,y);
}

void Player::movement(const float dirY)
{
	this->sprite.move(0, this->moveSpeed * dirY);
}

const bool Player::attack()
{
	if(this->cooldown>=this->cooldownMax)
	{
		this->cooldown = 0.f;
		return true;
	}
	else
	{
		return false;
	}
	
}

void Player::updateCooldown()
{
	if(this->cooldown<this->cooldownMax)
	{
		this->cooldown += 1.f;
	}
	
}

void Player::update()
{
	this->updateCooldown();
}


void Player::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
