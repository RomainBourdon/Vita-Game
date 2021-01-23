#include "Ground.h"



Ground::Ground()
{
	//setting the type to ground so that the player can do a collision detection
	set_type(GROUND);
}


Ground::~Ground()
{
}

void Ground::InitGround(PrimitiveBuilder* primitive_builder_, b2World* world_, gef::Vector4 size)
{
	
	// ground dimensions
	gef::Vector4 ground_half_dimensions(size);

	// setup the mesh for the ground
	ground_mesh_ = primitive_builder_->CreateBoxMesh(ground_half_dimensions);
	set_mesh(ground_mesh_);

	// create physics bodies
	b2BodyDef body_def;
	body_def.type = b2_kinematicBody;
	body_def.position = b2Vec2(ground_pos);


	ground_body_ = world_->CreateBody(&body_def);

	// create the shape
	b2PolygonShape shape;
	shape.SetAsBox(ground_half_dimensions.x(), ground_half_dimensions.y());

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;
	
	// create the fixture on the rigid body
	ground_body_->CreateFixture(&fixture_def);

	set_type(GROUND);
	// update visuals from simulation data
	UpdateFromSimulation(ground_body_);

	ground_body_->SetUserData(this);
}



void Ground::Release()
{
	//delete the mesh
	delete ground_mesh_;
	ground_mesh_ = NULL;
}

Bounce::Bounce()
{
	set_type(BOUNCE);
}

void Bounce::Initbounce(PrimitiveBuilder * primitive_builder_, b2World * world_)
{
	gef::Vector4 ground_half_dimensions(2.9f, 0.1f, 0.5f);

	bounce_mesh_ = primitive_builder_->CreateBoxMesh(ground_half_dimensions);
	set_mesh(bounce_mesh_);

	// create a physics body for the player
	b2BodyDef body_def;
	body_def.type = b2_kinematicBody;
	body_def.position = b2Vec2(ground_pos.x, ground_pos.y+0.6);

	bounce_body = world_->CreateBody(&body_def);

	// create the shape for the player
	b2PolygonShape shape;
	shape.SetAsBox(ground_half_dimensions.x(), ground_half_dimensions.y());

	// create the fixture
	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;
	fixture_def.friction = 5.0f;
	fixture_def.density = 1.0f;

	// create the fixture on the rigid body
	bounce_body->CreateFixture(&fixture_def);

	set_type(BOUNCE);

	// update visuals from simulation data
	UpdateFromSimulation(bounce_body);

	// create a connection between the rigid body and GameObject
	bounce_body->SetUserData(this);
}
void Bounce::Release()
{
	delete bounce_mesh_;
	bounce_mesh_ = NULL;
}

Win::Win()
{
	set_type(WIN);
}

void Win::InitWin(PrimitiveBuilder * primitive_builder_, b2World * world_)
{
	gef::Vector4 ground_half_dimensions(3.0f, 0.1f, 0.5f);

	win_mesh_ = primitive_builder_->CreateBoxMesh(ground_half_dimensions);
	set_mesh(win_mesh_);

	// create a physics body for the player
	b2BodyDef body_def;
	body_def.type = b2_staticBody;
	body_def.position = b2Vec2(ground_pos.x, ground_pos.y + 0.6);

	win_body = world_->CreateBody(&body_def);

	// create the shape for the player
	b2PolygonShape shape;
	shape.SetAsBox(ground_half_dimensions.x(), ground_half_dimensions.y());

	// create the fixture
	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;
	fixture_def.friction = 5.0f;
	fixture_def.density = 1.0f;

	// create the fixture on the rigid body
	win_body->CreateFixture(&fixture_def);

	set_type(WIN);

	// update visuals from simulation data
	UpdateFromSimulation(win_body);

	// create a connection between the rigid body and GameObject
	win_body->SetUserData(this);
}

void Win::Release()
{
	delete win_mesh_;
	win_mesh_ = NULL;
}

Sphere_touch::Sphere_touch()
{
}

void Sphere_touch::initSphere(PrimitiveBuilder * primitive_builder_, b2World * world_)
{
	sphere_mesh_ = primitive_builder_->CreateSphereMesh(0.6, 20, 20);
	set_mesh(sphere_mesh_);

	// create physics bodies
	b2BodyDef body_def;
	body_def.type = b2_kinematicBody;
	body_def.position = b2Vec2(sphere_pos.x,sphere_pos.y);


	sphere_body = world_->CreateBody(&body_def);

	// create the shape
	b2CircleShape shape;
	shape.m_radius = 0.6;

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;

	// create the fixture on the rigid body
	sphere_body->CreateFixture(&fixture_def);

	// update visuals from simulation data
	UpdateFromSimulation(sphere_body);

	sphere_body->SetUserData(this);
}

void Sphere_touch::release()
{
	delete sphere_mesh_;
	sphere_mesh_ = NULL;
}
