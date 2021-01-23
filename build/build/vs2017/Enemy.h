#pragma once
#include "game_object.h"
#include "primitive_builder.h"
#include <input/input_manager.h>
#include "input\sony_controller_input_manager.h"
#include <system/debug_log.h>

class Enemy :
	public GameObject
{
public:
	Enemy();
	~Enemy();

	void init(PrimitiveBuilder* primitive_builder_, b2World* world_);
	void update(float32 forcesx, float32 forcesy);

	b2Body* enemy_body_;
};

