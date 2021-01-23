#include "Menu.h"



Menu::Menu() :
	button_icon_cross(NULL),
	button_icon_square (NULL),
	button_icon_circle (NULL)
{
}

Menu::~Menu()
{
}


void Menu::Init(gef::SpriteRenderer* spr, gef::Font* fon, gef::InputManager* inp, gef::Renderer3D* ren, PrimitiveBuilder* primi, gef::AudioManager* audio, gef::Platform& plat, int ag, int ab, int ae, float ndc_z_min, int &hscore1, int &hscore2, int &hscore3, GameState state)
{
	//initialize the pointers
	sprite_renderer = spr;
	input_manager = inp;
	font = fon;
	audio_manager = audio;

	//initialize the sprites
	button_icon_cross = CreateTextureFromPNG("playstation-cross-dark-icon.png", plat);
	button_icon_circle = CreateTextureFromPNG("playstation-circle-dark-icon.png", plat);
	button_icon_square = CreateTextureFromPNG("playstation-square-dark-icon.png", plat);
	Background = CreateTextureFromPNG("background.png", plat);

	//create audio manager
	audio_manager = gef::AudioManager::Create();

	Background = CreateTextureFromPNG("background.png", plat);

	//load music
	audio_manager->LoadMusic("audio_hero_Playroom_SIPML_K-0349.wav", plat);

	playing = false;
}

void Menu::Release()
{
	//delete sprite pointers
	delete button_icon_cross;
	button_icon_cross = NULL;

	delete button_icon_circle;
	button_icon_circle = NULL;

	delete button_icon_square;
	button_icon_square = NULL;

	delete Background;
	Background = NULL;

	//delete audio manager
	delete audio_manager;
	audio_manager = NULL;

}

GameState Menu::update(float frame_time, gef::Platform &plat, GameState state)
{
	//checks if music is playing
	if (playing != true)
	{
		audio_manager->PlayMusic();
		playing = true;
	}

	//checks if button is pressed to change states
	const gef::SonyController* controller = input_manager->controller_input()->GetController(0);
	if (controller->buttons_pressed() & gef_SONY_CTRL_CROSS)
	{
		state = LEVEL1;

	}
	if (controller->buttons_pressed() & gef_SONY_CTRL_CIRCLE)
	{
		state = LEVEL2;
	}
	if (controller->buttons_pressed() & gef_SONY_CTRL_SQUARE)
	{
		state = LEVEL3;
	}
	if (controller->buttons_pressed() & gef_SONY_CTRL_SELECT)
	{
		state = HIGH_SCORE;
	}
	if (controller->buttons_pressed() & gef_SONY_CTRL_START)
	{
		state = CONTROLS;
	}

	return state;
}

void Menu::Render(gef::Platform &plat)
{
	//start sprite renderer for text and sprites
	sprite_renderer->Begin();

	gef::Sprite background;
	background.set_texture(Background);
	background.set_position(gef::Vector4(plat.width()*0.5, plat.height()*0.5, -0.99f));
	background.set_height(plat.height());
	background.set_width(plat.width());
	sprite_renderer->DrawSprite(background);

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f, plat.height()*0.1f, -0.99f),
		2.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"Ivy's Escape");

	// render "PRESS" text
	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f - 90.0f, plat.height()*0.5f - 58.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"Press");

	// Render button icon
	gef::Sprite button;
	button.set_texture(button_icon_cross);
	button.set_position(gef::Vector4(plat.width()*0.5f- 40.0f, plat.height()*0.5f-40.0f, -0.99f));
	button.set_height(32.0f);
	button.set_width(32.0f);
	sprite_renderer->DrawSprite(button);


	// render "TO START" text
	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f + 80.0f, plat.height()*0.5f -58.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"to start Easy mode");

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f-90.0f, plat.height()*0.5f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"Press");

	gef::Sprite button1;
	button1.set_texture(button_icon_circle);
	button1.set_position(gef::Vector4(plat.width()*0.5f - 40.0f, plat.height()*0.5f + 20.0f, -0.99f));
	button1.set_height(32.0f);
	button1.set_width(32.0f);
	sprite_renderer->DrawSprite(button1);

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f + 100.0f, plat.height()*0.5f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"to start Medium mode");

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f - 90.0f, plat.height()*0.5f + 58.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"Press" );

	gef::Sprite button2;
	button2.set_texture(button_icon_square);
	button2.set_position(gef::Vector4(plat.width()*0.5f-40.0f, plat.height()*0.5f+ 70.0f, -0.99f));
	button2.set_height(32.0f);
	button2.set_width(32.0f);
	sprite_renderer->DrawSprite(button2);

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f +90.0f, plat.height()*0.5f + 58.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"to start Hard mode");

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f, plat.height()*0.5f + 108.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"Press SELECT to see High Scores");

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f, plat.height()*0.5f + 158.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"Press START to go to Controls");

	
	sprite_renderer->End();
}

