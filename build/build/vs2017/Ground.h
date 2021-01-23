#pragma once
#include "primitive_builder.h"
#include "game_object.h"

class Ground : public GameObject
{
public:
	Ground();
	~Ground();
	void InitGround(PrimitiveBuilder* primitive_builder_, b2World* world_, gef::Vector4 size);
	void Release();


	//mesh variable
	gef::Mesh* ground_mesh_;

	//physics body
	b2Body* ground_body_;
	b2Vec2 ground_pos;

};

class Bounce : public Ground
{
public:
	Bounce();
	void Initbounce(PrimitiveBuilder* primitive_builder_, b2World* world_);
	void Release();


	//mesh variable
	gef::Mesh* bounce_mesh_;

	//physics body variables
	b2Body* bounce_body;
	b2Vec2 bounce_pos;
};

class Win : public Ground
{
public:
	Win();
	void InitWin(PrimitiveBuilder* primitive_builder_, b2World* world_);
	void Release();

	b2Body* win_body;
	gef::Mesh* win_mesh_;
	b2Vec2 win_pos;
};

class Sphere_touch : public Ground
{
public:
	Sphere_touch();
	void initSphere(PrimitiveBuilder* primitive_builder_, b2World* world_);
	void release();


	b2Body* sphere_body;
	gef::Mesh*sphere_mesh_;
	b2Vec2 sphere_pos;
};
