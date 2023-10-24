#include "Shell.h"

//Constructor/destructor
Shell::Shell(Texture* texture, float pos_X, float pos_Y, float dir_X, float move_Speed)
{
	this->shell.setTexture(*texture);
	this->shell.setPosition(pos_X, pos_Y);
	this->direction.x = dir_X;
	this->direction.y = 0;
	this->moveSpeed = move_Speed;
}

Shell::~Shell()
{

}
//Accessors
const FloatRect Shell::getBounds() const
{

	return this->shell.getGlobalBounds();
}
//Functions
void Shell::update()
{
	this->shell.move(this->moveSpeed * this->direction);
}

void Shell::render(RenderTarget* target)
{
	target->draw(this->shell);
}
