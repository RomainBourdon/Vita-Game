#pragma once
#include "StatesBase.h"
class Splash :
	public StatesBase
{
public:
	Splash();
	~Splash();

	void Init(gef::SpriteRenderer* spr, gef::Font* fon, gef::InputManager* inp, gef::Renderer3D* ren, PrimitiveBuilder* primi, gef::AudioManager* audio, gef::Platform& plat, int ag, int ab, int ae, float ndc_z_min, int &hscore1, int &hscore2, int &hscore3, GameState state);
	void Release();
	GameState update(float frame_time, gef::Platform &plat, GameState state);
	void Render(gef::Platform &plat);

	inline gef::Texture* get_backgrnd() { return Background; }

protected:
	gef::Texture* Background;
};

