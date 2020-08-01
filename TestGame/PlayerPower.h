#pragma once
#ifndef PLAYER_POWER_H
#define PLAYER_POWER_H
#include "BaseObject.h"
#include <vector>
class PlayerPower :public BaseObject {
public:
	PlayerPower();
	~PlayerPower();
	void SetNumber(const int& num) { number_ = num; };
	void Render(SDL_Surface* des);
	void Init();
	void Dercre();//hàm giảm mạng
	void AddPos(const int& xpos);//add vị trí cho vector
private:
	int number_;//số mạng
	std::vector<int>post_list_;//dãy các vị trí
};
#endif // !PLAYER_POWER_H