#include "Controls.h"



Controls::Controls()
{
}


Controls::~Controls()
{
}

void Controls::Init(gef::SpriteRenderer * spr, gef::Font * fon, gef::InputManager * inp, gef::Renderer3D * ren, PrimitiveBuilder * primi, gef::AudioManager* audio, gef::Platform & plat, int ag, int ab, int ae, float ndc_z_min, int &hscore1, int &hscore2, int &hscore3, GameState state)
{

	//initialize pointers
	sprite_renderer = spr;
	input_manager = inp;
	font = fon;

	//initialize sprites with textures
	button_icon_ = CreateTextureFromPNG("playstation-circle-dark-icon.png", plat);
	bounce = CreateTextureFromPNG("bounce_layer.png", plat);
	win = CreateTextureFromPNG("win_layer.png", plat);
	enemy = CreateTextureFromPNG("enemy.png", plat);
	Background = CreateTextureFromPNG("background.png", plat);
}

void Controls::Release()
{
	//delete sprite pointers
	delete button_icon_;
	button_icon_ = NULL;

	delete enemy;
	enemy = NULL;

	delete win;
	win = NULL;

	delete bounce;
	bounce = NULL;

	delete Background;
	Background = NULL;
}

GameState Controls::update(float frame_time, gef::Platform & plat, GameState state)
{
	//check to change state
	const gef::SonyController* controller = input_manager->controller_input()->GetController(0);
	if (controller->buttons_pressed() & gef_SONY_CTRL_CIRCLE)
	{
		state = MENU;
	}
	return state;
}

void Controls::Render(gef::Platform & plat)
{
	//start sprite renderer and text rendering
	sprite_renderer->Begin(true);

	gef::Sprite background;
	gef::Sprite bouncy;
	gef::Sprite winning;
	gef::Sprite badguy;

	background.set_texture(Background);
	background.set_position(gef::Vector4(plat.width()*0.5, plat.height()*0.5, -0.99f));
	background.set_height(plat.height());
	background.set_width(plat.width());
	sprite_renderer->DrawSprite(background);

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f+200.0f, plat.height()*0.5f - 140.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"Use the D-pad to move Ivy around the level");
	
	bouncy.set_texture(bounce);
	bouncy.set_position(gef::Vector4(plat.width()*0.5 - 180.0f, plat.height()*0.5 - 130.0f, -0.99f));
	bouncy.set_height(64.0f);
	bouncy.set_width(280.0f);
	sprite_renderer->DrawSprite(bouncy);

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f, plat.height()*0.5 - 100.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"the green layer is a bounce pad, use it to reach high places.");
	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f, plat.height()*0.5 - 80.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"the orange circle is for moving the paltform around the screen.");

	winning.set_texture(win);
	winning.set_position(gef::Vector4(plat.width()*0.5 - 180.0f, plat.height()*0.5, -0.99f));
	winning.set_height(80.0f);
	winning.set_width(280.0f);
	sprite_renderer->DrawSprite(winning);

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f, plat.height()*0.5f + 40, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"the yellow pad is the goal. reach it to get Ivy out of there!");

	badguy.set_texture(enemy);
	badguy.set_position(gef::Vector4(plat.width()*0.5 - 82.0f, plat.height()*0.5 + 100.0f, -0.99f));
	badguy.set_height(56.0f);
	badguy.set_width(80.0f);
	sprite_renderer->DrawSprite(badguy);

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f, plat.height()*0.5f + 120.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"these are smellies, avoid them so you don't die. if you do get hit you will restart");

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f, plat.height()*0.5f + 140.0f, -0.99f),
		1.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"if you fall, press SELECT to restart the level.");

	font->RenderText(
		sprite_renderer,
		gef::Vector4(plat.width()*0.5f, plat.height()*0.1f, -0.99f),
		2.0f,
		0xffffffff,
		gef::TJ_CENTRE,
		"HOW TO PLAY");

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
	button.set_position(gef::Vector4(plat.width() - 60.0f, plat.height() - 48.0f, -0.99f));
	button.set_height(32.0f);
	button.set_width(32.0f);
	sprite_renderer->DrawSprite(button);

	sprite_renderer->End();
}



