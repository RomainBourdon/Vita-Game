#pragma once
#include "primitive_builder.h"
#include <input/input_manager.h>
#include "input\sony_controller_input_manager.h"
#include <system/debug_log.h>
#include "game_object.h"
#include "graphics\scene.h"
#include "graphics\mesh_instance.h"
#include "load_texture.h"


class player : public GameObject
{
public:
	player();
	~player();

	void InitPlayer(PrimitiveBuilder* primitive_builder_, b2World* world_, b2Vec2 pos, gef::Platform &plat);
	void update(const gef::SonyController* controller);
	void Collision_Response(GameObject* ob);
	void Release();
	gef::Scene* LoadSceneAssets(gef::Platform& platform, const char* filename);
	gef::Mesh* GetMeshFromSceneAssets(gef::Scene* scene);

	// player variables
	gef::Scene* model;

	b2Body* player_body_;
	b2Vec2 player_start_pos;

	bool dead = false;
	bool jumped = false;

	gef::Matrix44 player_transform = transform_;
	//gef::Vector4 player_pos;
	float32 ang;

};

