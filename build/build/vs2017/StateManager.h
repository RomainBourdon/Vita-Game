#pragma once
#include <input/input_manager.h>
#include "StatesBase.h"
#include "Level.h"
#include "Menu.h"
#include "Congrats.h"
#include "HighScore.h"
#include "Controls.h"
#include "Splash.h"

class StateManager
{
public:
	StateManager();
	~StateManager();

	void init(gef::SpriteRenderer* spri, gef::Font* fon, gef::InputManager* inp, gef::Renderer3D* ren, PrimitiveBuilder* primi, gef::AudioManager* audio, gef::Platform &plat, float ndc_z_min);
	void UpdateGameStateMachine(float frame_time, gef::Platform &plat);
	void Update(float frame_time, gef::Platform &plat);
	void Render(gef::Platform &plat);
	void Release();



protected:
	GameState states;
	GameState onstate;
	GameState oldGamestate;

	gef::SpriteRenderer* spriterenderer;

	gef::InputManager* inputmanager;

	gef::Renderer3D* renderer3d;

	PrimitiveBuilder* primitivebuilder;

	gef::AudioManager* audio_manager_;

	gef::Font* fo;

	Menu menustate;
	Level levelstate1;
	Level levelstate2;
	Level levelstate3;
	Congrats winstate;
	Controls controlstate;
	HighScore highscorestate;
	Splash splashstate;

	StatesBase* currentstate;
	StatesBase* oldstate;

	float fps_;
	float ndc_z_mi;

	int hscore1 = 5;
	int hscore2 = 4;
	int hscore3 = 3;

	int amount_grnd, amount_bnce, amount_enmy;
};

