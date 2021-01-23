#include "Congrats.h"



Congrats::Congrats()
{
	
}


Congrats::~Congrats()
{
}

void Congrats::Init(gef::SpriteRenderer * spr, gef::Font * fon, gef::InputManager * inp, gef::Renderer3D * ren, PrimitiveBuilder * primi, gef::AudioManager* audio, gef::Platform & plat, int ag, int ab, int ae, float ndc_z_min, int &hscore1, int &hscore2, int &hscore3, GameState state)
{
	//initialize pointers
	sprite_renderer = spr;
	input_manager = inp;
	font = fon;
	audio_manager = audio;

	//initilize sprites with textures
	Background = CreateTextureFromPNG("win_background.png", plat);

	ivy_happy = CreateTextureFromPNG("ivy_model.png", plat);

	//initialize audio manager 
	audio_manager = gef::AudioManager::Create();

	//load music
	audio_manager->LoadMusic("mr_clown.wav", plat);

	playing = false;
	
	if(state == LEVEL1)
	score = hscore1;
	if(state == LEVEL2)
	score = hscore2;
	if(state == LEVEL3)
	score = hscore3;

}

void Congrats::Release()
{
	//delete sprite pointers
	delete Background;
	Background = NULL;

	delete ivy_happy;
	ivy_happy = NULL;	

	//delete audio manager pointer
	delete audio_manager;
	audio_manager = NULL;
}

GameState Congrats::update(float frame_time, gef::Platform & plat, GameState state)
{
	//check to change state
	const gef::SonyController* controller = input_manager->controller_input()->GetController(0);
	if (controller->buttons_pressed())
	{
		state = MENU;
	}

	//check if music is playing
	if (playing != true)
	{
		audio_manager->PlayMusic();
		playing = true;
	}

	return state;
}

void Congrats::Render(gef::Platform & plat)
{
	//start sprite renderer and text
	sprite_renderer->Begin();

	gef::Sprite background;
	background.set_texture(Background);
	background.set_position(gef::Vector4(plat.width()*0.5, plat.height()*0.5, -0.99f));
	background.set_height(plat.height());
	background.set_width(plat.width());
	sprite_renderer->DrawSprite(background);

	// render "congrats" text
	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f, plat.height()*0.5f - 200.0f, -0.99f),
		2.0f,
		0xff000000,
		gef::TJ_CENTRE,
		"Congratulations");

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f, plat.height()*0.5f -140, -0.99f),
		1.0f,
		0xff000000,
		gef::TJ_CENTRE,
		"You helped Ivy escape!");

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f, plat.height()*0.5f -110.0f, -0.99f),
		1.0f,
		0xff000000,
		gef::TJ_CENTRE,
		"you took %i tries", score);

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f, plat.height()*0.5f + 220.0f, -0.99f),
		1.0f,
		0xff000000,
		gef::TJ_CENTRE,
		"Press any button to go back to Menu");

	gef::Sprite ivy;
	ivy.set_texture(ivy_happy);
	ivy.set_position(gef::Vector4(plat.width()*0.5, plat.height()*0.5 +140.0f, -0.99f));
	ivy.set_height(200);
	ivy.set_width(200);
	sprite_renderer->DrawSprite(ivy);

	sprite_renderer->End();
}


