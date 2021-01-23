#include "Splash.h"



Splash::Splash()
{
}


Splash::~Splash()
{
}

void Splash::Init(gef::SpriteRenderer * spr, gef::Font * fon, gef::InputManager * inp, gef::Renderer3D * ren, PrimitiveBuilder * primi, gef::AudioManager* audio, gef::Platform & plat, int ag, int ab, int ae, float ndc_z_min, int &hscore1, int &hscore2, int &hscore3, GameState state)
{
	//initialize pointers inherited from statebase
	sprite_renderer = spr;
	input_manager = inp;
	font = fon;
	audio_manager = audio;


	//create a texture and set it to this variable
	Background = CreateTextureFromPNG("background.png", plat);

	//load in the music we want to play
	audio_manager->LoadMusic("audio_hero_Playroom_SIPML_K-0349.wav", plat);

	//set playing to be false
	playing = false;
}

void Splash::Release()
{
	//delete the pointers to the background
	delete Background;
	Background = NULL;

	//delete the pointer to the audio manager
	delete audio_manager;
	audio_manager = NULL;
}

GameState Splash::update(float frame_time, gef::Platform & plat, GameState state)
{
	const gef::SonyController* controller = input_manager->controller_input()->GetController(0);

	//check if any button is being pressed
	if (controller->buttons_pressed())
	{
		//change the state
		state = MENU;
	}
	//check to see if the music is playing 
	if (playing != true)
	{
		//play the music
		audio_manager->PlayMusic();
		//set playing to true to avoid calling the function every frame
		playing = true;
	}
	return state;
}

void Splash::Render(gef::Platform & plat)
{
	//start rendering the sprites and text
	sprite_renderer->Begin();

	gef::Sprite background;
	background.set_texture(Background);
	background.set_position(gef::Vector4(plat.width()*0.5, plat.height()*0.5, -0.99f));
	background.set_height(plat.height());
	background.set_width(plat.width());
	sprite_renderer->DrawSprite(background);

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f, plat.height()*0.4f, -0.99f),
		2.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"Ivy's Escape");

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f, plat.height()*0.6f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"Press any button");

	sprite_renderer->End();
}
