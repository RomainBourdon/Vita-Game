#pragma once
#include "StatesBase.h"
#include "system\debug_log.h"
#include "game_object.h"
#include "player.h"
#include "Ground.h"
#include "Enemy.h"
#include <stdlib.h>
#include <time.h> 
#include "primitive_builder.h"
#include "HighScore.h"

class Level :
	public StatesBase
{
public:

	Level();
	~Level();
	void Init(gef::SpriteRenderer* spr, gef::Font* fon, gef::InputManager* inp, gef::Renderer3D* ren, PrimitiveBuilder* primi, gef::AudioManager* audio, gef::Platform& plat, int ag, int ab, int ae, float ndc_z_min, int &hscore1, int &hscore2, int &hscore3, GameState state);
	void Release();
	GameState update(float frame_time, gef::Platform &plat, GameState state);
	void Render(gef::Platform &plat);
	GameState UpdateSimulation(float dt, GameState state);
	void SetupLights();
	void DrawHUD();

	void GetScreenPosRay(const gef::Vector2& screen_position, const gef::Matrix44& projection, const gef::Matrix44& view, gef::Vector4& startPoint, gef::Vector4& direction, gef::Platform& plat);
	bool RaySphereIntersect(gef::Vector4& startPoint, gef::Vector4& direction, gef::Vector4& sphere_centre, float sphere_radius);

protected:
	// GAME DECLARATIONS
	b2World* world_;

	//player variables
	player Player;
	
	int tries = 0;

	gef::Vector4 plat_size = { 3.0, 0.6, 0.5 };
	float moving_pos[4];
	float dir = 5;
	
	// ground variables
	int amount_ground;
	Ground ground_normal[2];
	Ground ground_plat[4];

	int amount_bounce;
	Bounce bouncy_layer[4];

	Win win_layer;

	HighScore score;

	Sphere_touch touch_sphere[4];

	//enemy variables
	int amount_enemy;
	Enemy enemy[4];

	float fps_;
	
	b2Body* pickedPlatform;

	gef::Texture* Background;
};

