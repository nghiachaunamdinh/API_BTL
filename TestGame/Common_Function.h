#pragma once
#ifndef COMMON_FUNCTION_H_H
#include <Windows.h>
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<SDL_mixer.h>
#include <SDL_ttf.h>
const int SCREEN_WIDTH = 561;
const int SCREEN_HEIGHT = 800;
const int SCREEN_BPP = 32;
static SDL_Event g_even;
static SDL_Surface *g_screen = NULL;
static SDL_Surface *g_bkground = NULL;
static SDL_Surface* g_img_menu = NULL;//khoi tao anh menu
static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];

namespace SDLCommonfunction {	
	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void CleanUp();
	int ShowMenu(SDL_Surface* des, TTF_Font* font);
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	bool CheckFocus(const int& x, const  int& y, const SDL_Rect& rect);
}
#endif // !COMMON_FUNCTION_H_H
