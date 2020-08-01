#include "MainObject.h"
MainObject::MainObject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
}
MainObject::~MainObject()
{
	;
}
void MainObject:: HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2])
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			y_val_ -= HEIGHT_MAIN_OBJECT / 20;
			break;
		case SDLK_DOWN:
			y_val_ += HEIGHT_MAIN_OBJECT / 20;
			break;
		case SDLK_RIGHT:
			x_val_ += WIDTH_MAIN_OBJECT / 20;
			break;
		case SDLK_LEFT:
			x_val_ -= WIDTH_MAIN_OBJECT / 20;

			break;
		default:
			break;
		}

	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			y_val_ += HEIGHT_MAIN_OBJECT / 20;
			break;
		case SDLK_DOWN:
			y_val_ -= HEIGHT_MAIN_OBJECT / 20;
			break;
		case SDLK_RIGHT:
			x_val_ -= WIDTH_MAIN_OBJECT / 20;
			break;
		case SDLK_LEFT:
			x_val_ += WIDTH_MAIN_OBJECT / 20;

			break;
		default:
			break;
		}

	}
	else if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		AmoObject* p_amo = new AmoObject();//1 vien dan duoc sinh ra
		if (events.button.button == SDL_BUTTON_LEFT)//chuot trai
		{
			p_amo->SetWidthHeight(WIDTH_FIRE, HEIGHT_FIRE);//truyen vao 
			p_amo->LoadImg("Fire.png");//load hinh vien dan
			p_amo->set_type(AmoObject::LASER);
			Mix_PlayChannel(-1, bullet_sound[0], 0);//âm tanh khi đạn bắn
		}
		else if (events.button.button == SDL_BUTTON_RIGHT)//chuot phai
		{
			p_amo->SetWidthHeight(WIDTH_DAN2, HEIGHT_DAN2);//truyen vao 
			p_amo->LoadImg("DAN2.png");//load hinh vien dan
			p_amo->set_type(AmoObject::SPHERE);
			Mix_PlayChannel(-1, bullet_sound[1], 0);
		}

		p_amo->setRect(this->rect_.x + 25, this->rect_.y - 30);
		p_amo->set_is_move(true);
		p_amo->set_y_val(10);
		p_amo_list_.push_back(p_amo);

	}
	else if (events.type == SDL_MOUSEBUTTONUP)
	{

	}
	else
	{
		;
	}
  
}
void MainObject::MakeAmo(SDL_Surface* des)
{
	for (int i = 0; i <p_amo_list_.size(); i++)//kiem tra xem co dan hay ko
	{		
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo != NULL)
		{
			if (p_amo->get_is_move()) //neu duoc phep ban ra
			{
				p_amo->show(des); 
				p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			else //tu huy neu dan vuot qua gioi han
			{
				if (p_amo != NULL)
				{
					p_amo_list_.erase(p_amo_list_.begin() + i);//tru di 1 phan tu dan trong list					
					delete p_amo;
					p_amo = NULL;
				}
			}
		}
	}
}
void MainObject::HandleMove()//chuyen dong cua xe tang chinh
{
	rect_.x += x_val_;
	if (rect_.x < 0-20 || rect_.x +WIDTH_MAIN_OBJECT > SCREEN_WIDTH+40)
	{
		rect_.x -= x_val_;
	}
	rect_.y += y_val_;
	if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT)
	{
		rect_.y -= y_val_;
	}




	//rect_.y += y_val_;

}
void MainObject::RemoveAmo(const int& idx)
{
		
	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		if (idx < p_amo_list_.size())
		{
			AmoObject* p_amo = p_amo_list_.at(idx);
			p_amo_list_.erase(p_amo_list_.begin() + idx);

			if (p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
		
	}
}