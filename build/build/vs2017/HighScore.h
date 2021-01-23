#pragma once
#include "StatesBase.h"

class HighScore :
	public StatesBase
{
public:
	HighScore();
	~HighScore();

	void Init(gef::SpriteRenderer* spr, gef::Font* fon, gef::InputManager* inp, gef::Renderer3D* ren, PrimitiveBuilder* primi, gef::AudioManager* audiomanager, gef::Platform& plat, int ag, int ab, int ae, float ndc_z_min, int &hscore1, int &hscore2, int &hscore3, GameState state);
	void Release();
	GameState update(float frame_time, gef::Platform &plat, GameState state);
	void Render(gef::Platform &plat);

protected:
	gef::Texture* button_icon_;
	gef::Texture* Background;

	int highscore_level1 = 10;
	int highscore_level2 = 10;
	int highscore_level3 = 10;

	int score1 =9;
	int score2 =9;
	int score3 =9;
};

