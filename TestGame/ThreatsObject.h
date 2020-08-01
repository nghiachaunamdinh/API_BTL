#pragma once
#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_
#include"Common_Function.h"
#include"BaseObject.h"
#include"AmoObject.h"
#include<vector>
class ThreatsOject : public BaseObject {
public:
	ThreatsOject();
	~ThreatsOject();
	void HandleMove(const int& x_border, const int& y_border);
	void HandleInputAction(SDL_Event event);

	void set_x_val(const int& val) { x_val_ = val; }
	void set_y_val(const int& val) { y_val_ = val; }
	int get_x_val() const { return x_val_; }
	int get_y_val() const { return y_val_; }
	void setWidth_Threat(const int& val) { width_threat_ = val; rect_.w = val; }
	void setHeight_Threat(const int& val) { height_threat_ = val;rect_.h = val;  }
	void SetAmoList(std::vector<AmoObject*> amo_list) { p_amo_list_ = amo_list; }
	std::vector<AmoObject*> GetAmoList() const { return p_amo_list_; }
	void InitAmo(AmoObject* p_amo);
	void MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit);
	void Reset(const int& yborder);
	void ResetAmo(AmoObject* p_amo_list_);
	
private:
	int x_val_;
	int y_val_;
	int width_threat_;
	int height_threat_;
	std::vector<AmoObject*> p_amo_list_;
};
#endif // !1
