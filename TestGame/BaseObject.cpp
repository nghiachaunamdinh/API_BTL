#include"BaseObject.h"
#include"Common_Function.h"
BaseObject::BaseObject()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL;

}
BaseObject::~BaseObject() {
	SDL_FreeSurface(p_object_);
	p_object_ = NULL;
}
bool BaseObject::LoadImg(const char* file_name)
{
	p_object_ = SDLCommonfunction::LoadImage(file_name);
	if (p_object_ == NULL)
	{
		return false;
	}
	return true;
}
void BaseObject::show(SDL_Surface* des)
{
	if (p_object_ != NULL)
	{
		rect_=SDLCommonfunction::ApplySurface(p_object_, des, rect_.x, rect_.y);
	}
}