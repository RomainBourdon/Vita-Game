#pragma once
#include "StatesBase.h"

namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}
class Menu :
	public StatesBase
{
public:
	Menu();
	~Menu();
	void Init(gef::SpriteRenderer* spr, gef::Font* fon, gef::InputManager* inp, gef::Renderer3D* ren, PrimitiveBuilder* primi, gef::AudioManager* audio, gef::Platform& plat, int ag, int ab, int ae, float ndc_z_min, int &hscore1, int &hscore2, int &hscore3, GameState state);
	void Release();
	GameState update(float frame_time, gef::Platform &plat, GameState state);
	void Render(gef::Platform &plat);

protected:

	gef::Texture* button_icon_cross;
	gef::Texture* button_icon_circle;
	gef::Texture* button_icon_square;

	gef::Texture* Background;
};

