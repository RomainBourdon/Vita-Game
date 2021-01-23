#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <graphics/primitive.h>
#include <graphics/mesh_instance.h>
#include <graphics/sprite_renderer.h>
#include <graphics/renderer_3d.h>
#include <input/input_manager.h>
#include "StateManager.h"
#include "load_texture.h"
#include <graphics/font.h>
#include <audio/audio_manager.h>
#include <input/input_manager.h>



// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class Renderer3D;
}


class SceneApp : public gef::Application
{
public:
	SceneApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
	void InitFont();
	void CleanUpFont();

	inline void set_ndc_zmin(float value) { ndc_z_min_ = value; }
	inline gef::SpriteRenderer* get_spriterend() { return sprite_renderer_; }
	inline gef::InputManager* get_inputmanager() { return input_manager_; }
	inline gef::Renderer3D* get_renderer() { return renderer_3d_; }
	inline PrimitiveBuilder* get_primibuild() { return primitive_builder_; }
	inline gef::Font* get_font() { return font_; }
	inline gef::AudioManager* get_audiomanager() { return audio_manager_; }
	inline float get_fps() { return fps_; }
private:
	

	gef::Font* font_;
	float fps_;

	gef::SpriteRenderer* sprite_renderer_;

	gef::InputManager* input_manager_;

	gef::Renderer3D* renderer_3d_;

	PrimitiveBuilder* primitive_builder_;

	gef::AudioManager* audio_manager_;

	StateManager stateManager;

	float ndc_z_min_;
};

#endif // _SCENE_APP_H
