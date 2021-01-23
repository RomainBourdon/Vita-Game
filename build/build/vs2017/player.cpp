#include "player.h"



player::player() :
	model(NULL)
{
	//sets object type
	set_type(PLAYER);
}


player::~player()
{
}

void player::InitPlayer(PrimitiveBuilder* primitive_builder_, b2World* world_, b2Vec2 pos, gef::Platform &plat)
{
	player_start_pos = pos;

	//fetchs and creates model mesh for player
	const char* model_filename = "ivy.scn";
	model = LoadSceneAssets(plat, model_filename);

	if (model)
	{

		set_mesh(GetMeshFromSceneAssets(model));
	}
	else
	{
		gef::DebugOut("Scene file %s failed to load\n", model_filename);
	}

	// create a physics body for the player
	b2BodyDef player_body_def;
	player_body_def.type = b2_dynamicBody;
	player_body_def.position = b2Vec2(player_start_pos);

	player_body_ = world_->CreateBody(&player_body_def);

	// create the shape for the player
	b2PolygonShape player_shape;
	player_shape.SetAsBox(0.5f, 0.5f);

	// create the fixture
	b2FixtureDef player_fixture_def;
	player_fixture_def.shape = &player_shape;
	player_fixture_def.density = 1.0f;

	// create the fixture on the rigid body
	player_body_->CreateFixture(&player_fixture_def);

	set_type(PLAYER);

	// update visuals from simulation data
	UpdateFromSimulation(player_body_);

	// create a connection between the rigid body and GameObject
	player_body_->SetUserData(this);
}

void player::update(const gef::SonyController* controller)
{
	if (controller)
	{
		//apply force to player when jumped is false and the cross button is pressed
		if (jumped == false)
		{
			if (controller->buttons_pressed() & gef_SONY_CTRL_CROSS)
			{
				b2Vec2 force;
				force.Set(0.0f, 7.0f);
				player_body_->ApplyLinearImpulseToCenter(force, true);
				jumped = true;
			}
		}
		
		//apply forces to player when right or left d pad button is pressed
		if (controller->buttons_down() & gef_SONY_CTRL_RIGHT)
		{
			b2Vec2 force, pos;
			force.Set(10.0f, 0.0f);
			player_body_->ApplyForceToCenter(force, true);
		}
		if (controller->buttons_down() & gef_SONY_CTRL_LEFT)
		{
			b2Vec2 force;
			force.Set(-10.0f, 0.0f);
			player_body_->ApplyForceToCenter(force, true);
		}

		//setup the player transform
		//gef::Matrix44 player_transform;
		player_transform.SetIdentity();

		////setup the player translation
		gef::Vector4 player_translation(player_body_->GetPosition().x, player_body_->GetPosition().y, 0.0f, 0.0f);
		player_transform.SetTranslation(player_translation);
				
		player_transform.SetTranslation(player_translation);
		set_transform(player_transform);
	}
}

void player::Collision_Response(GameObject* ob)
{
	if (ob != NULL)
	{
		//collision response for a bounce platform
		if (ob->type() == BOUNCE)
		{
			b2Vec2 force;
			force.Set(0.0f, 7.5f);
			player_body_->ApplyLinearImpulseToCenter(force, true);
			jumped = true;
		}
		//collsion response when touching the ground
		if (ob->type() == GROUND)
		{
			jumped = false;
		}
	}
}

void player::Release()
{
	//delete mesh
	delete model;
	model = NULL;
}


gef::Scene* player::LoadSceneAssets(gef::Platform& platform, const char* filename)
{
	gef::Scene* scene = new gef::Scene();

	if (scene->ReadSceneFromFile(platform, filename))
	{
		// if scene file loads successful
		// create material and mesh resources from the scene data
		scene->CreateMaterials(platform);
		scene->CreateMeshes(platform);
	}
	else
	{
		delete scene;
		scene = NULL;
	}

	return scene;
}

gef::Mesh* player::GetMeshFromSceneAssets(gef::Scene* scene)
{
	gef::Mesh* mesh = NULL;

	// if the scene data contains at least one mesh
	// return the first mesh
	if (scene && scene->meshes.size() > 0)
		mesh = scene->meshes.front();

	return mesh;
}



