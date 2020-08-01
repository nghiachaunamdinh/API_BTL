#include "AmoObject.h"
AmoObject::AmoObject()
{
	rect_.x = 0;
	rect_.y = 0;
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
	amo_type_ = NONE;

}
AmoObject::~AmoObject()
{

}
void AmoObject::HandleMove(const int& x_border,const int& y_border)
{
	rect_.y -= y_val_;
	if (rect_.y <0)//neu vien dat di chuyen vuot qua do dai cua man hinh
	{
		is_move_ = false;
	}
}
void AmoObject::HandleMoveSearch(int speedfire) {
	rect_.y += speedfire;
		;
	if (rect_.y > SCREEN_HEIGHT) {
		is_move_ = false;
	}
}
void AmoObject::HandleInputAction(SDL_Event events)
{
	;
}