#include "PlayerPower.h"
PlayerPower::PlayerPower() {

}
PlayerPower::~PlayerPower() {

}
void PlayerPower::AddPos(const int& xpos) {
	post_list_.push_back(xpos);//thêm vào list
}
void PlayerPower::Render(SDL_Surface* des) {
	if (number_ == post_list_.size()) {//kiểm tra số mạng bằng đúng số vị trí mạng
		for (int i = 0; i < post_list_.size(); i++) {
			rect_.x = post_list_.at(i);
			show(des);
		}
	}
}
void PlayerPower::Init() {
	LoadImg("HINH_SAO.png");
	number_ = 3;
	if (post_list_.size() > 0) {
		post_list_.clear();
	}
	AddPos(20);
	AddPos(60);
	AddPos(100);
	
}
void PlayerPower::Dercre() {
	number_--;//số mạng giảm
	post_list_.pop_back();//loại đi vị trí cuối cùng
}

