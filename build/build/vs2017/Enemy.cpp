#include "Enemy.h"



Enemy::Enemy()
{
	set_type(ENEMY);
}


Enemy::~Enemy()
{
}

void Enemy::init(PrimitiveBuilder* primitive_builder_, b2World* world_)
{
	// setup the mesh for the player
	set_mesh(primitive_builder_->GetDefaultCubeMesh());

	// create a physics body for the player
	b2BodyDef enemy_body_def;
	enemy_body_def.type = b2_dynamicBody;
	enemy_body_def.position = b2Vec2(-9.75f, -3.0f);

	enemy_body_ = world_->CreateBody(&enemy_body_def);

	// create the shape for the player
	b2PolygonShape enemy_shape;
	enemy_shape.SetAsBox(0.5f, 0.5f);

	// create the fixture
	b2FixtureDef enemy_fixture_def;
	enemy_fixture_def.shape = &enemy_shape;
	//enemy_fixture_def.friction = 5.0f;
	enemy_fixture_def.density = 1.0f;

	// create the fixture on the rigid body
	enemy_body_->CreateFixture(&enemy_fixture_def);

	// update visuals from simulation data
	UpdateFromSimulation(enemy_body_);

	set_type(ENEMY);
	//create connection between gameoblect and body
	enemy_body_->SetUserData(this);
}

void Enemy::update(float32 forcesx, float32 forcesy)
{
	//applies force to move enemy
	b2Vec2 force;
	force.Set(forcesx, forcesy);
	enemy_body_->ApplyForceToCenter(force, true);
}
