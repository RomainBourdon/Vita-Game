#include "HighScore.h"




HighScore::HighScore()
{
}


HighScore::~HighScore()
{
}

void HighScore::Init(gef::SpriteRenderer * spr, gef::Font * fon, gef::InputManager * inp, gef::Renderer3D * ren, PrimitiveBuilder * primi, gef::AudioManager* audiomanager,gef::Platform & plat, int ag, int ab, int ae, float ndc_z_min, int &hscore1, int &hscore2, int &hscore3, GameState state)
{
	
	//pointer initialization
	sprite_renderer = spr;
	input_manager = inp;
	font = fon;
	button_icon_ = CreateTextureFromPNG("playstation-circle-dark-icon.png", plat);
	Background = CreateTextureFromPNG("background.png", plat);

	//sets the score to be the best score from the levels
	score1 = hscore1;
	score2 = hscore2;
	score3 = hscore3;
}

void HighScore::Release()
{
	//delete pointers for sprites
	delete button_icon_;
	button_icon_ = NULL;

	delete Background;
	Background = NULL;
}

GameState HighScore::update(float frame_time, gef::Platform & plat, GameState state)
{
	//changes state by pressing the cross button
	const gef::SonyController* controller = input_manager->controller_input()->GetController(0);
	if (controller->buttons_pressed() & gef_SONY_CTRL_CIRCLE)
	{
		state = MENU;
	}

	//checks if the high score has been beaten by the score of the player
	if (highscore_level1 > score1)
	{
		highscore_level1 = score1;
	}
	if (highscore_level2 > score2)
	{
		highscore_level2 = score2;
	}
	if (highscore_level3 > score3)
	{
		highscore_level3 = score3;
	}
	return state;
}

void HighScore::Render(gef::Platform & plat)
{
	//start sprite rendering and text
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
		"TOP SCORES");

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f - 84.0f, plat.height()*0.5f - 88.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"Number of tries to beat level 1: %i",highscore_level1);

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f - 84.0f, plat.height()*0.5f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"Number of tries to beat level 2: %i", highscore_level2);

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f - 84.0f, plat.height()*0.5f + 88.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"Number of tries to beat level 3: %i", highscore_level3);

	// render "PRESS" text
	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width() - 104.0f, plat.height() - 68.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"back");

	// Render button icon
	gef::Sprite button;
	button.set_texture(button_icon_);
	button.set_position(gef::Vector4(plat.width()- 60.0f, plat.height() - 48.0f, -0.99f));
	button.set_height(32.0f);
	button.set_width(32.0f);
	sprite_renderer->DrawSprite(button);

	sprite_renderer->End();
}

