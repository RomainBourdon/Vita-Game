#include "scene_app.h"
#include <system/platform.h>
#include <system/debug_log.h>

SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	input_manager_(NULL),
	renderer_3d_(NULL),
	font_(NULL),
	primitive_builder_(NULL),
	audio_manager_(NULL)
{
}

void SceneApp::Init()
{
	//initialize the font
	InitFont();

	//iniialize the 3d renderer
	renderer_3d_ = gef::Renderer3D::Create(platform_);

	//initialize the sprite renderer
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	// initialise input manager
	input_manager_ = gef::InputManager::Create(platform_);

	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(platform_);

	//initialize audio manager
	audio_manager_ = gef::AudioManager::Create();

	//call the statemanager initializer
	stateManager.init(sprite_renderer_, font_, input_manager_, renderer_3d_, primitive_builder_, audio_manager_, platform_, ndc_z_min_);

	

}

void SceneApp::CleanUp()
{
	//delete the font pointer
	CleanUpFont();

	//delete all the game pointers
	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	delete input_manager_;
	input_manager_ = NULL;

	delete font_;
	font_ = NULL;

	delete audio_manager_;
	audio_manager_ = NULL;

	stateManager.Release();
}

bool SceneApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	//call the input manager update
	input_manager_->Update();

	//call the statemanager update
	stateManager.Update(frame_time, platform_);

	return true;
}

void SceneApp::Render()
{
	//call the statemanager render
	stateManager.Render(platform_);
}

void SceneApp::InitFont()
{

	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void SceneApp::CleanUpFont()
{
	delete font_;
	font_ = NULL;
}
