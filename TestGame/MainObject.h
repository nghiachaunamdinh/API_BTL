#pragma once
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_
#include"Common_Function.h"
#include "BaseObject.h"
#include <vector>
#include "AmoObject.h"
#define WIDTH_MAIN_OBJECT 62
#define HEIGHT_MAIN_OBJECT 71


class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();
	

	void HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2]);
	void HandleMove();
	void SetAmoList(std::vector<AmoObject*> amo_list) { p_amo_list_ = amo_list; }
	std::vector<AmoObject*> GetAmoList() const { return p_amo_list_; }
	void MakeAmo(SDL_Surface* g_creen);
	void RemoveAmo(const int& idx); 
private:
	int x_val_;
	int y_val_;

	std::vector<AmoObject*> p_amo_list_; //amoobject se la 1 truong trong main object
};
#endif//MAIN_OBJECT_H_