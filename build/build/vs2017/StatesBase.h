#pragma once
// FRAMEWORK FORWARD DECLARATIONS
#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/mesh_instance.h>
#include <input/input_manager.h>
#include <box2d/Box2D.h>
#include <graphics/sprite_renderer.h>
#include <graphics/renderer_3d.h>
#include <graphics/font.h>
#include <graphics\primitive.h>
#include "load_texture.h"
#include "input\sony_controller_input_manager.h"
#include "graphics\sprite.h"
#include "maths\math_utils.h"
#include "GameState.h"
#include <audio/audio_manager.h>
#include <input/input_manager.h>

namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}
class StatesBase
{
public:
	StatesBase();
	~StatesBase();

	virtual GameState update(float frame_time, gef::Platform &plat, GameState state) = 0;
	virtual void Release() = 0;
	virtual void Init(gef::SpriteRenderer* spr, gef::Font* font, gef::InputManager* inp, gef::Renderer3D* ren, PrimitiveBuilder* primi, gef::AudioManager* audiomanager, gef::Platform &plat, int ag, int ab, int ae, float ndc_z_min, int &hscore1, int &hscore2, int &hscore3, GameState state) = 0;
	virtual void Render(gef::Platform &plat) = 0;

	void Releases();

protected:
	gef::SpriteRenderer* sprite_renderer;

	gef::InputManager* input_manager;

	gef::Renderer3D* renderer_3d;

	PrimitiveBuilder* primitive_builder;

	gef::Font* font;

	gef::AudioManager* audio_manager;

	Int32 pickup_sfx_id_;
	Int32 pickup_voice;
	gef::VolumeInfo volume_info;
	bool playing;

	float ndc_z_min_;
};

