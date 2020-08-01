#include"ThreatsObject.h"

ThreatsOject::ThreatsOject()
{
	rect_.x = SCREEN_WIDTH*0.5;
	rect_.y =0;
	rect_.w = 70;
	rect_.h = 70;
	x_val_ = 0;
	y_val_ = 0;
}
ThreatsOject::~ThreatsOject()
{

}
void ThreatsOject::InitAmo(AmoObject* p_amo)
{
	if (p_amo) {
		bool ret = p_amo->LoadImg("sphere.png");
		if (ret)
		{
			p_amo->set_is_move(true);
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->set_type(AmoObject::SPHERE);
			p_amo->setRect(rect_.x+rect_.w*0.5, rect_.y);
			p_amo_list_.push_back(p_amo);
		}
	}
}
void ThreatsOject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit) {
	for (int i = 0; i < p_amo_list_.size(); ++i)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo)
		{
 			if (p_amo->get_is_move())
			{
				p_amo->show(des);
				p_amo->HandleMoveSearch(3);

			}
			else
			{
				p_amo->set_is_move(true);
				p_amo->setRect(rect_.x +x_val_, rect_.y+y_val_);
			}
		}
	}
}
void ThreatsOject::HandleMove(const int& x_border, const int& y_border)
{
	//SDL_Delay(5);
	rect_.y += y_val_;
	if (rect_.y > SCREEN_HEIGHT)
	{
		rect_.y = 0;
		int rand_x = rand() % 400;
		if (rand_x > SCREEN_WIDTH - 20)
		{
			rand_x = SCREEN_WIDTH * 0.3;
		}
		rect_.x = rand_x;
	}
	
}
void ThreatsOject::HandleInputAction(SDL_Event events)
{

}
void ThreatsOject::Reset(const int& yborder)
{
	rect_.y = yborder;
	int rand_x = rand() % 400;
	if (rand_x > SCREEN_WIDTH)
	{
		rand_x = SCREEN_WIDTH * 0.3;
	}
	rect_.x = rand_x;
	for (int i = 0; i < p_amo_list_.size(); ++i)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo)
		{
			ResetAmo(p_amo);
		}
	}
}

void ThreatsOject::ResetAmo(AmoObject* p_amo)
{
	p_amo->setRect(rect_.x + rect_.w*0.5, rect_.y);
}