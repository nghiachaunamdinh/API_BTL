#include"Common_Function.h"
#include"MainObject.h"
#include"ThreatsObject.h"
#include"TextObject.h"
#include"ExplosionObject.h"
#include<SDL_mixer.h>
#include<vector>
#include"PlayerPower.h"
	#undef main

TTF_Font* g_font_text=NULL ;
TTF_Font* g_font_menu = NULL;
SDL_Surface *g_object;
ThreatsOject* g_threatslinh;
ExlosionObject exp_main;//KHAI BAO DOI TUONG VU NO
ThreatsOject* g_threatstank;
MainObject g_xetangchinh_object;
TextObject mark_game;
int num_threattank=1;
int num_threatlinh = 1;
PlayerPower player_power;
TextObject time_game;//khoi tao doi tuongw thoi gian
int g_score = 0;
int g_level = 1;
//khởi tạo biến đếm lượt chết
unsigned int dair_number = 0;
//lhai bao bien dem diem
unsigned int mark_number = 0;
//bieens thoi gian
bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (g_screen == NULL)
	{
		return false;
	}
	//------------------------------------------
	//xử lý âm thanh
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096)==-1) {
		return false;
	}
	g_sound_bullet[0] = Mix_LoadWAV("no_may_bay.wav");
	g_sound_bullet[1] = Mix_LoadWAV("xe_tang_minh_no.wav");
	g_sound_exp[0] = Mix_LoadWAV("minh_chet.wav");
	g_sound_exp[1] = Mix_LoadWAV("dich_chet.wav");
	if (g_sound_exp[0] == NULL || g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL||g_sound_exp[1] == NULL) {
		return false;
	}

	//khoi tao font chu
	if (TTF_Init() == -1)
	{
		return false;
	}
	g_font_text = TTF_OpenFont("adelline personal use only.ttf", 20);
	g_font_menu = TTF_OpenFont("adelline personal use only.ttf", 50);
	if (g_font_text ==NULL|| g_font_menu == NULL)
	{
		return false;
	}
	return true;
}
void makeThreat(int num,int width_threat,int height_threat,const char* img,const char* kieuthreat)
{
	if (kieuthreat == "linh")
	{
		g_threatslinh = new ThreatsOject[num];
		for (int sl = 0; sl < num; ++sl)
		{
			ThreatsOject* p_Threat = g_threatslinh + sl;
			if (p_Threat)
			{
				p_Threat->setWidth_Threat(width_threat);
				p_Threat->setHeight_Threat(height_threat);				
				
				
				int rand_x = rand() % 400;
				if (rand_x > SCREEN_WIDTH + 30)
				{
					rand_x = SCREEN_WIDTH * 0.3;
				}
				int rand_y = rand() % 400;
				if (rand_y >300)
				{
					rand_y = 150;
				}
				p_Threat->setRect(rand_x, rand_y);
				bool ret = p_Threat->LoadImg(img);
				if (!ret) //kiem tra xem co xe tang ko
				{
					return;
				}
				//p_Threat->set_y_val(1);
				AmoObject* p_amo = new AmoObject();
				p_Threat->InitAmo(p_amo);
			}
		}
	

	}
	else
	{
		g_threatstank=NULL;
		g_threatstank = new ThreatsOject[num];
		for (int sl = 0; sl < num; ++sl)
		{
			ThreatsOject* p_Threat = g_threatstank + sl;
			if (p_Threat)
			{
				p_Threat->setWidth_Threat(width_threat);
				p_Threat->setHeight_Threat(height_threat);
				bool ret = p_Threat->LoadImg(img);
				if (!ret) //kiem tra xem co xe tang ko
				{
					return;
				}
				int rand_x = rand() % 400;
				int rand_y = rand() % 400;
				if (rand_x > SCREEN_WIDTH + 30)
				{
					rand_x = SCREEN_WIDTH * 0.3;
				}
				if (rand_y > 300)
				{
					rand_y = 100;
				}
				p_Threat->setRect(rand_x, 0 - sl *200);
				AmoObject* p_amo = new AmoObject();
				p_Threat->InitAmo(p_amo);
			}
		}
	}

}
bool Makelevel()
{
	//Make tao threat
	if (g_score == 0)
	{
		g_level = 1;
		num_threatlinh = 3;
		makeThreat(num_threatlinh, 28, 46, "linh.png", "linh");//g_level1	
		return true;
	}
	
	if (g_score == 5)
	{
		g_level = 2;
		num_threattank = 3;
		makeThreat(num_threattank, 40, 44, "tangdich1.png", "tank");	//g_level2	
		return true;
	}
	if (g_score == 10)
	{
		num_threattank = 2;
		num_threatlinh = 2;
		g_level = 3;
		makeThreat(num_threatlinh, 28, 46, "linh.png", "linh");
		makeThreat(num_threattank, 39, 46, "tangdich2.png", "tank");	//g_level3
		return true;
	}
	if (g_score == 20)
	{
		num_threattank = 2;
		num_threatlinh = 3;
		g_level = 4;
		makeThreat(num_threatlinh, 28, 46, "linh.png", "linh");
		makeThreat(num_threattank, 39, 46, "tangdich2.png", "tank");		//g_level4	
		return true;
	}
	if (g_score == 30)
	{
		num_threattank = 2;
		num_threatlinh = 3;
		g_level = 5;
		makeThreat(num_threatlinh, 28, 46, "linh.png", "linh");
		makeThreat(num_threattank, 48, 57, "tangdich3.png", "tank");//g_level5
		return true;
	}
	return false;
}
bool CheckCollisionMain(ThreatsOject* p_Threat )
{

	//check Collision main and threat				
	bool test = SDLCommonfunction::CheckCollision(g_xetangchinh_object.GetRect(), p_Threat->GetRect());

	if (test) {
		dair_number++;
		Mix_PlayChannel(-1, g_sound_exp[0], 0);//âm tanh khi đạn bắn
		//hieenj vuj noor

		for (int ex = 0; ex < 4; ex++) {
			int x_pos = (g_xetangchinh_object.GetRect().x + g_xetangchinh_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
			int Y_pos = (g_xetangchinh_object.GetRect().y + g_xetangchinh_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
			exp_main.set_frame(ex);
			exp_main.setRect(x_pos, Y_pos);
			exp_main.ShowEx(g_screen);			
			if (SDL_Flip(g_screen) == -1)
				return 0;
		}
		//Mix_PlayChannel(-1, g_sound_exp[0], 0);//âm tanh khi đạn bắn
		if (dair_number <= 2) {			
			g_xetangchinh_object.setRect(235, 620);
			player_power.Dercre();
			player_power.Render(g_screen);
			if (SDL_Flip(g_screen) == -1) {
				delete[]p_Threat;
				SDLCommonfunction::CleanUp();
				SDL_Quit();
				return 0;
			}
			p_Threat->Reset(0);
			SDL_Delay(200);
		}
		else {
			if (MessageBox(NULL, "Boom Boom you lose!", "game over", MB_OK) == IDOK) {
				if (g_threatslinh != NULL)
					delete[] g_threatslinh;
				if (g_threatstank != NULL)
					delete[] g_threatstank;
				SDLCommonfunction::CleanUp();
				SDL_Quit();
				return true;
			}
		}
		
	}
//check Collision main and Amothreat
std::vector<AmoObject*>amo_listofthreat = p_Threat->GetAmoList();
for (int iam = 0; iam < amo_listofthreat.size(); iam++)
{
	AmoObject* p_amo = amo_listofthreat.at(iam);
	if (p_amo != NULL) {
		bool ret = SDLCommonfunction::CheckCollision(g_xetangchinh_object.GetRect(), p_amo->GetRect());
		if (ret) {
			//hieenj vuj noor
			dair_number++;
			for (int ex = 0; ex < 4; ex++) {
				int x_pos = (g_xetangchinh_object.GetRect().x + g_xetangchinh_object.GetRect().w * 0.5) - EXP_WIDTH * 0.5;
				int Y_pos = (g_xetangchinh_object.GetRect().y + g_xetangchinh_object.GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
				exp_main.set_frame(ex);
				exp_main.setRect(x_pos, Y_pos);
				exp_main.ShowEx(g_screen);
				p_Threat->Reset(0);
				SDL_Delay(200);
				if (SDL_Flip(g_screen) == -1)
					return 0;
			}
			Mix_PlayChannel(-1, g_sound_exp[0], 0);//âm tanh khi đạn bắn

			if (dair_number <= 2) {
				
				g_xetangchinh_object.setRect(235, 620);
				player_power.Dercre();
				player_power.Render(g_screen);
				if (SDL_Flip(g_screen) == -1) {
					delete[]p_Threat;
					SDLCommonfunction::CleanUp();
					SDL_Quit();
					return 0;
				}
			}
			else {
				if (MessageBox(NULL, "Boom Boom you lose!", "game over", MB_OK) == IDOK) {
					if (g_threatslinh != NULL)
						delete[] g_threatslinh;
					if (g_threatstank != NULL)
						delete[] g_threatstank;
					//  delete[] p_amo;
					amo_listofthreat.clear();
					SDLCommonfunction::CleanUp();
					SDL_Quit();
					return true;
				}
			}
		}
	}
}
}
int runthreat(int num, int level, int Amo_x, int Amo_y, const char* kieuthreat)
{
	if (kieuthreat == "linh")
	{
		for (int sl2 = 0; sl2 < num; ++sl2)
		{

			ThreatsOject* p_Threat = (g_threatslinh + sl2);
			if (p_Threat)
			{
				p_Threat->show(g_screen);
				p_Threat->set_y_val(level);
				//p_Threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_Threat->set_x_val(Amo_x);
				p_Threat->set_y_val(Amo_y);
				p_Threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			//Check Collision Main
			bool retcol = CheckCollisionMain(p_Threat);
			if (retcol == true)
				return 1;
				//kiem tra va cham giua đạn
				std::vector<AmoObject*>amo_list = g_xetangchinh_object.GetAmoList();
				for (int im = 0; im < amo_list.size(); im++) {
					AmoObject* p_amo = amo_list.at(im);
					if (p_amo != NULL) {
						bool ret = SDLCommonfunction::CheckCollision(p_amo->GetRect(), p_Threat->GetRect());
						if (ret) {
							//hieenj vuj noor
							mark_number++;
							for (int ex = 0; ex < 4; ex++) {
								int x_pos = (p_Threat->GetRect().x + p_Threat->GetRect().w * 0.5) - EXP_WIDTH * 0.5;
								int Y_pos = (p_Threat->GetRect().y + p_Threat->GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
								exp_main.set_frame(ex);
								exp_main.setRect(x_pos, Y_pos);
								exp_main.ShowEx(g_screen);								
								if (SDL_Flip(g_screen) == -1)
									return 0;
							}
							//show mark_value
							std::string val_str_mark = std::to_string(mark_number);
							std::string strMark("DIEM : ");
							strMark += val_str_mark;
							mark_game.SetText(strMark);
							mark_game.CreateGameText(g_font_text, g_screen);
							Mix_PlayChannel(-1, g_sound_exp[0], 0);//âm tanh khi đạn bắn
							++g_score;
							bool levelup = Makelevel();
							int rand_y = rand() % 400;
							if (rand_y > 300)
							{
								rand_y = 150;
							}
							p_Threat->Reset(rand_y);
							g_xetangchinh_object.RemoveAmo(im);
							//Mix_PlayChannel(-1, g_sound_exp[1], 0);//âm tanh khi đạn bắn
							if (levelup == true)
								return 0;
						}
					}
				}

			}
		}
	else
	{
		for (int sl2 = 0; sl2 < num; ++sl2)
		{

			ThreatsOject* p_Threat = (g_threatstank + sl2);
			if (p_Threat)
			{  
				
				p_Threat->show(g_screen);				
				p_Threat->set_y_val(level);
				p_Threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_Threat->set_x_val(Amo_x);
				p_Threat->set_y_val(Amo_y);
				p_Threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
			}

			bool retcol = CheckCollisionMain(p_Threat);
			if (retcol == true)
				return 1;
			//kiem tra va cham giua đạn
			std::vector<AmoObject*>amo_list = g_xetangchinh_object.GetAmoList();
			for(int im = 0; im < amo_list.size(); im++) {
				AmoObject* p_amo = amo_list.at(im);
				if (p_amo != NULL) {
					bool ret = SDLCommonfunction::CheckCollision(p_amo->GetRect(), p_Threat->GetRect());
					if (ret) {	
						mark_number++;
						//hieenj vuj noor
						for (int ex = 0; ex < 4; ex++) {
							int x_pos = (p_Threat->GetRect().x + p_Threat->GetRect().w * 0.5) - EXP_WIDTH * 0.5;
							int Y_pos = (p_Threat->GetRect().y + p_Threat->GetRect().h * 0.5) - EXP_HEIGHT * 0.5;
							exp_main.set_frame(ex);
							exp_main.setRect(x_pos, Y_pos);
							exp_main.ShowEx(g_screen);
							
							if (SDL_Flip(g_screen) == -1)
								return 0;
						}
						//show mark_value
						std::string val_str_mark = std::to_string(mark_number);
						std::string strMark("DIEM : ");
						strMark += val_str_mark;
						mark_game.SetText(strMark);
						mark_game.CreateGameText(g_font_text, g_screen);
						Mix_PlayChannel(-1, g_sound_exp[0], 0);//âm tanh khi đạn bắn
						g_score++;
						bool levelup = Makelevel();
						p_Threat->Reset(0 - sl2 * 200);
						g_xetangchinh_object.RemoveAmo(im);
						//Mix_PlayChannel(-1, g_sound_exp[0], 0);//âm tanh khi đạn bắn
						if (levelup == true)
							return 0;
					}
				}
		
			}
			
		}
		
     }
	 //hien thi thoiwf gian

	 std::string strTime("Time : ");
	 Uint32 time_value = SDL_GetTicks() / 1000;//laays thoi gian hien tai la bao nhieu giay
	 std::string val_str_time = std::to_string(time_value);
	 strTime += val_str_time;
	 time_game.SetText(strTime);
	 time_game.setRect(450, 10);
	 time_game.CreateGameText(g_font_text, g_screen);
}



int main(int arc, char* argv[])
{
	bool is_quit = false;
	if (Init() == false)
	{
		return 0;
	}
	g_bkground = SDLCommonfunction::LoadImage("boicanh.png");
	if (g_bkground == NULL)
	{
		return 0;
	}
	
	//Make Make 
	player_power.Init();
	//hieenj chu
	
	mark_game.SetColor(TextObject::WHITE_TEXT);

	//Make MainObject
	g_xetangchinh_object.setRect(235, 620);//vi tri xe tang chinh xuat hien
	bool ret = g_xetangchinh_object.LoadImg("tank123.png");
	if (!ret) //kiem tra xem co xe tang ko
	{
		return 0;
	}
	//iNIT EXPLO
	ret = exp_main.LoadImg("exp_.png");
	exp_main.set_clips();
	if (ret == false) {
		return 0;
	}
	//Make ThreatsObject
	 g_score=0;	
	 Makelevel();
				
	
	unsigned int checkreturn=0;
	int ret_menu = SDLCommonfunction::ShowMenu(g_screen, g_font_menu);
	if (ret_menu == 1) {
		is_quit = true;
	}


	//unsigned int mark_value;
	while (!is_quit)
	{
		while (SDL_PollEvent(&g_even))
		{
			if (g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			g_xetangchinh_object.HandleInputAction(g_even, g_sound_bullet);//xu li su kien

		}
		SDLCommonfunction::ApplySurface(g_bkground, g_screen, 0, 0);//full màn,reset lai man hinh
		//hiện playerpower
		player_power.Render(g_screen);

		g_xetangchinh_object.show(g_screen);  //up lai vi tri sau khi thao tac
		g_xetangchinh_object.HandleMove();		
		g_xetangchinh_object.MakeAmo(g_screen);
	    
		
		//Chạy threats
		if(g_level==1)
		{
			if (checkreturn != 1)
				checkreturn=runthreat(num_threatlinh, 1, 14, 32,"linh");
		}
		else
		if (g_level == 2)
		{
			if (checkreturn != 1)
			checkreturn = runthreat(num_threattank, 1, 14, 32, "tank");
		}
		else
			if (g_level == 3)
			{
				checkreturn = runthreat(num_threatlinh, 1, 14, 32, "linh");
				if (checkreturn != 1)
				{					
					checkreturn = runthreat(num_threattank, 2, 15, 32, "tank");
				}
				
			}
			else
				if(g_level==4)
			{
					checkreturn = runthreat(num_threatlinh, 1, 14, 32, "linh");
					if (checkreturn != 1)
					{						
						checkreturn = runthreat(num_threattank, 2, 20, 40, "tank");
					}
					
				}
				else
					if(g_level == 5)
				{
						checkreturn = runthreat(num_threatlinh, 1, 14, 32, "linh");
						if (checkreturn != 1)
						{
							
							checkreturn = runthreat(num_threattank, 2, 20, 44, "tank");
						}
						
				}
		
		//Show score to screen
		std::string val_str_mark = std::to_string(g_score);
		std::string strMark("Mark:");
		strMark += val_str_mark;

		mark_game.SetText(strMark);
		if(checkreturn!=1)
		mark_game.CreateGameText(g_font_text, g_screen);


			//update screen
		if (checkreturn == 1)
		{
			return 0;
		}
		if (SDL_Flip(g_screen) == -1)
		{
			delete[] g_threatslinh;
			delete[] g_threatstank;
			SDLCommonfunction::CleanUp();
			SDL_Quit();

			return 0;
		}
			
	}
	
}