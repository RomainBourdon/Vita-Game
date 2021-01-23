#include "Level.h"
#include "input/touch_input_manager.h"



Level::Level() :
	world_(NULL),
	pickedPlatform(NULL)
{
}

Level::~Level()
{
}

void Level::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer_3d->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}

void Level::Init(gef::SpriteRenderer* spr, gef::Font* fon, gef::InputManager* inp, gef::Renderer3D* ren, PrimitiveBuilder* primi, gef::AudioManager* audio, gef::Platform &plat, int ag, int ab, int ae, float ndc_z_min, int &hscore1, int &hscore2, int &hscore3, GameState state)
{
	
	//pointer initialization
	sprite_renderer = spr;
	input_manager = inp;
	renderer_3d = ren;
	primitive_builder = primi;
	font = fon;
	amount_ground = ag;
	amount_bounce = ab;
	amount_enemy = ae;
	ndc_z_min_ = ndc_z_min;
	SetupLights();
	audio_manager = audio;
	
	//audio manager initialization
	audio_manager = gef::AudioManager::Create();

	//load music
	audio_manager->LoadMusic("audio_hero_Marching-Disorders_SIPML_K-04-41-01.wav", plat);

	//load sound effect
	pickup_sfx_id_ = audio_manager->LoadSample("zapsplat_multimedia_game_jump_24928.wav", plat);

	pickup_voice = -1;

	playing = false;

	primitive_builder = new PrimitiveBuilder(plat);

	//touch manager initialization
	if (input_manager && input_manager->touch_manager() && (input_manager->touch_manager()->max_num_panels() > 0))
		input_manager->touch_manager()->EnablePanel(0);

	// initialise the physics world
	b2Vec2 gravity(0.0f, -19.6f);
	world_ = new b2World(gravity);
	
	//player initialization
	Player.InitPlayer(primitive_builder, world_, { -10, -5 }, plat);
	
	//ground initialization
	ground_normal[0].ground_pos = {-10, -7 };
	ground_normal[1].ground_pos = { 10, 3 };

	//win_layer initialization
	win_layer.ground_pos = { ground_normal[1].ground_pos };
	win_layer.InitWin(primitive_builder, world_);

	for (int i = 0; i< 2; i++)
		ground_normal[i].InitGround(primitive_builder, world_, plat_size);

	//sets the seed to be based on time 
	srand(time(NULL));

	//sets platforms to random plces in world
	for(int i = 0; i < amount_ground; i++ )
	{
		ground_plat[i].ground_pos = { rand() % 10 - 5 , rand() % 10 - 5 };
		ground_plat[i].InitGround(primitive_builder, world_, plat_size);
		

		touch_sphere[i].sphere_pos = { ground_plat[i].ground_pos };
		touch_sphere[i].initSphere(primitive_builder, world_);	
	}

	//bounce layer initialization
	for (int i = 0; i < amount_bounce; i++)
	{
		bouncy_layer[i].ground_pos = { ground_plat[i].ground_pos };
		bouncy_layer[i].Initbounce(primitive_builder, world_);
	}

	//enemy initialization
	for (int i = 0; i < amount_enemy; i++)
	{
		enemy[i].init(primitive_builder, world_);
		enemy[i].enemy_body_->SetTransform({ground_plat[i].ground_pos.x, ground_plat[i].ground_pos.y + 0.80}, 0);
	}

	//background initialization
	Background = CreateTextureFromPNG("background.png", plat);

	//add 1 to score
	tries++;

	//sets tries variable to high score to be passed to the highscore state
	if (state == LEVEL1)
		hscore1 = tries;
	if (state == LEVEL2)
		hscore2 = tries;
	if (state == LEVEL3)
		hscore3 = tries;

}

GameState Level::update(float ft, gef::Platform &plat, GameState state)
{
	fps_ = 1.0f / ft;
	// update physics world
	float32 timeStep = 1.0f / 60.0f;

	//checks if music id playing
	if (playing != true)
	{
		audio_manager->PlayMusic();
		playing = true;
	}
	
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	world_->Step(timeStep, velocityIterations, positionIterations);

	// update object visuals from simulation data
	Player.UpdateFromSimulation(Player.player_body_);

	for (int i = 0; i < amount_enemy; i++)
	enemy[i].UpdateFromSimulation(enemy[i].enemy_body_);

	for(int i = 0; i < amount_bounce; i++)
	bouncy_layer[i].UpdateFromSimulation(bouncy_layer[i].bounce_body);

	for (int i = 0; i < amount_ground; i++)
	{
		ground_plat[i].UpdateFromSimulation(ground_plat[i].ground_body_);
		touch_sphere[i].UpdateFromSimulation(touch_sphere[i].sphere_body);
	}
	
	//moves the enemy's back and forth on their respective platform
	for (int i = 0; i < amount_enemy; i++)
	{
		moving_pos[i] = enemy[i].enemy_body_->GetPosition().x - ground_plat[i].ground_body_->GetPosition().x;
		if (moving_pos[i] > (plat_size.x() * 0.5) * 0.8)
		{
			dir = -5;
		}
		if (moving_pos[i] <= (-plat_size.x() * 0.5) * 0.8)
		{
			dir = 5;
		}
		enemy[i].update(dir, 0);
	}
	
	//gives the player update the controller
	if (input_manager)
	{
		gef::SonyControllerInputManager* controller_input = input_manager->controller_input();

		if (controller_input)
		{
			const gef::SonyController* controller = input_manager->controller_input()->GetController(0);
			Player.update(controller);
			if (pickup_sfx_id_ != -1)
			{
				//makes a sound effect when cross is pressed
				if (controller->buttons_pressed() & gef_SONY_CTRL_CROSS)
				{
					pickup_voice = audio_manager->PlaySample(pickup_sfx_id_, false);
					
				}
			}
			
			//started = true;
			
			if (controller->buttons_pressed() & gef_SONY_CTRL_SELECT)
			{
				state = RESTART;
			}
			if (controller->buttons_pressed() & gef_SONY_CTRL_START)
			{
				state = MENU;
				tries = 0;
			}
		}
	}
		const gef::SonyController* controller = input_manager->controller_input()->GetController(0);
		const gef::TouchInputManager * touch_manager = input_manager->touch_manager();

		// get the active touches for this panel
		const gef::TouchContainer& panel_touches = touch_manager->touches(0);

		if (panel_touches.size() > 0)
		{
			// just grabbing the first touch for simplicity here
			// normally we go through all active touches and check the id
			gef::Touch touch = panel_touches.front();

			// only process this touch if it is NEW or ACTIVE
			if ((touch.type == gef::TT_NEW))
			{
				// convert the touch position to a ray that starts on the camera near plane
				// and shoots into the camera view frustum
				gef::Vector2 screen_position = touch.position;
				gef::Vector4 ray_start_position, ray_direction;
				GetScreenPosRay(screen_position, renderer_3d->projection_matrix(), renderer_3d->view_matrix(), ray_start_position, ray_direction, plat);
				

				// Create a sphere around the position of the platform body
				// the radius can be changed for larger objects
				// radius= 0.5f is a sensible value for a 1x1x1 cube
				for (int i = 0; i < amount_ground; i++)
				{
					gef::Vector4 sphere_centre(ground_plat[i].ground_body_->GetPosition().x, ground_plat[i].ground_body_->GetPosition().y, 0.0f);
					float  sphere_radius = 1.0f;

					// check to see if the ray intersects with the bound sphere that is around the player
					if (RaySphereIntersect(ray_start_position, ray_direction, sphere_centre, sphere_radius))
					{
						
						pickedPlatform = ground_plat[i].ground_body_;
					}
				}
			}
			else if (touch.type == gef::TT_ACTIVE)
			{
				// if picked object and touch is active
				// move picked object to new touch
				if (pickedPlatform)
				{
					gef::Vector2 screen_position = touch.position;
					gef::Vector4 ray_start_position, ray_direction;
					GetScreenPosRay(screen_position, renderer_3d->projection_matrix(), renderer_3d->view_matrix(), ray_start_position, ray_direction, plat);

					gef::Vector4 sphere_centre(pickedPlatform->GetPosition().x, pickedPlatform->GetPosition().y, 0.0f);
					float rayLength = (sphere_centre - ray_start_position).Length();

					gef::Vector4 end = ray_start_position + (ray_direction * rayLength);
					pickedPlatform->SetTransform({ end.x(), end.y() }, 0);

					for (int i = 0; i < amount_bounce; i++)
					{
						bouncy_layer[i].bounce_body->SetTransform({ ground_plat[i].ground_body_->GetPosition().x,  ground_plat[i].ground_body_->GetPosition().y + 0.6 }, 0);
					}
					for (int i = 0; i < amount_enemy; i++)
					{
						enemy[i].enemy_body_->SetTransform({ ground_plat[i].ground_body_->GetPosition().x, ground_plat[i].ground_body_->GetPosition().y + 0.6 }, 0);
					}
					for (int i = 0; i < amount_ground; i++)
					{
						touch_sphere[i].sphere_body->SetTransform({ ground_plat[i].ground_body_->GetPosition().x, ground_plat[i].ground_body_->GetPosition().y }, 0);
					}
				}
			}
			else // released
			{
				pickedPlatform = NULL;
			}
		}
	state = UpdateSimulation(ft, state);

	return state;
}

void Level::Release()
{
	// destroying the physics world also destroys all the objects within it
	delete world_;
	world_ = NULL;

	Player.Release();

	for (int i = 0; i < 2; i++)
		ground_normal[i].Release();

	for (int i = 0; i < amount_ground; i++)
		ground_plat[i].Release();

	for (int i = 0; i < amount_bounce; i++)
		bouncy_layer[i].Release();

	win_layer.Release();

	touch_sphere->release();

	delete Background;
	Background = NULL;

	delete audio_manager;
	audio_manager = NULL;
}

void Level::DrawHUD()
{
	if (font)
	{
		// display frame rate
		font->RenderText(sprite_renderer, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);
		font->RenderText(sprite_renderer, gef::Vector4(700.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "Tries: %i", tries);
	}
}

void Level::Render(gef::Platform &plat)
{
	// setup camera
	// projection
	float fov = gef::DegToRad(45.0f);
	float aspect_ratio = (float)plat.width() / (float)plat.height();
	gef::Matrix44 projection_matrix;
	projection_matrix = plat.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);
	renderer_3d->set_projection_matrix(projection_matrix);

	// view
	gef::Vector4 camera_eye(0.0f, 0.0f, 20.0f);
	gef::Vector4 camera_lookat(0.0f, 0.0f, 0.0f);
	gef::Vector4 camera_up(0.0f, 1.0f, 0.0f);
	gef::Matrix44 view_matrix;
	view_matrix.LookAt(camera_eye, camera_lookat, camera_up);
	renderer_3d->set_view_matrix(view_matrix);

	sprite_renderer->Begin();
	gef::Sprite background;
	background.set_texture(Background);
	background.set_position(gef::Vector4(plat.width()*0.5, plat.height()*0.5, -0.99f));
	background.set_height(plat.height());
	background.set_width(plat.width());
	sprite_renderer->DrawSprite(background);

	sprite_renderer->End();

	// draw 3d geometry
	renderer_3d->Begin(false);

	// draw ground
	for (int i = 0; i < 2; i++)
		renderer_3d->DrawMesh(ground_normal[i]);
	for (int i = 0; i < amount_ground; i++)
	{
		renderer_3d->DrawMesh(ground_plat[i]);
		renderer_3d->set_override_material(&primitive_builder->orange_material());
		renderer_3d->DrawMesh(touch_sphere[i]);
		renderer_3d->set_override_material(NULL);
	}
	for (int i = 0; i < amount_bounce; i++)
	{
		renderer_3d->set_override_material(&primitive_builder->green_material());
		renderer_3d->DrawMesh(bouncy_layer[i]);
		renderer_3d->set_override_material(NULL);
	}

	renderer_3d->set_override_material(&primitive_builder->yellow_material());
	renderer_3d->DrawMesh(win_layer);
	renderer_3d->set_override_material(NULL);

	//draw enemy
	renderer_3d->set_override_material(&primitive_builder->purple_material());
	for (int i = 0; i < amount_enemy; i++)
	renderer_3d->DrawMesh(enemy[i]);
	renderer_3d->set_override_material(NULL);

	// draw player
	renderer_3d->DrawMesh(Player);

	renderer_3d->End();

	// start drawing sprites, but don't clear the frame buffer
	sprite_renderer->Begin(false);
	DrawHUD();
	sprite_renderer->End();
}

GameState Level::UpdateSimulation(float dt, GameState state)
{
	//collision detection
	//get the head of the contact list
	b2Contact* contact = world_->GetContactList();
	//get contact count
	int contact_count = world_->GetContactCount();

	for (int contact_num = 0; contact_num<contact_count; ++contact_num)
	{
		if (contact->IsTouching())
		{
			// get the colliding bodies
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();

			// DO COLLISION RESPONSE HERE
			GameObject* gameObjectA = NULL;
			GameObject* gameObjectB = NULL;

			gameObjectA = (GameObject*)bodyA->GetUserData();
			gameObjectB = (GameObject*)bodyB->GetUserData();

			player* playr = NULL;
			Bounce* bouncy = NULL;
			Enemy* badguy = NULL;
			Win* winner = NULL;
			Ground* floor = NULL;

			if (gameObjectA)
			{
				if (gameObjectA->type() == PLAYER)
				{
					playr = (player*)gameObjectA;
				}
				
			}

			if (gameObjectB)
			{
				if (gameObjectB->type() == BOUNCE)
				{
					bouncy = (Bounce*)gameObjectB;
				}
				if (gameObjectB->type() == ENEMY)
				{
					badguy = (Enemy*)gameObjectB;
				}
				if (gameObjectB->type() == WIN)
				{
					winner = (Win*)gameObjectB;
				}
				if (gameObjectB->type() == GROUND)
				{
					floor = (Ground*)gameObjectB;
				}
			}

			if (playr)
			{
				if(gameObjectB == bouncy)
					playr->Collision_Response(bouncy);

				if (gameObjectB == floor)
					playr->Collision_Response(floor);

				if (gameObjectB == badguy)
				{
					state = RESTART;
				}

				if (gameObjectB == winner)
				{
					state = CONGRATS;
					tries = 0;
				}
			}
		}
		// Get next contact point
		contact = contact->GetNext();
	}
	return state;
}

void Level::GetScreenPosRay(const gef::Vector2& screen_position, const gef::Matrix44& projection, const gef::Matrix44& view, gef::Vector4& startPoint, gef::Vector4& direction, gef::Platform& plat)
{
	gef::Vector2 ndc;

	float hw = plat.width() * 0.5f;
	float hh = plat.height() * 0.5f;

	ndc.x = (static_cast<float>(screen_position.x) - hw) / hw;
	ndc.y = (hh - static_cast<float>(screen_position.y)) / hh;

	gef::Matrix44 projectionInverse;
	projectionInverse.Inverse(view * projection);

	gef::Vector4 nearPoint, farPoint;

	nearPoint = gef::Vector4(ndc.x, ndc.y, ndc_z_min_, 1.0f).TransformW(projectionInverse);
	farPoint = gef::Vector4(ndc.x, ndc.y, 1.0f, 1.0f).TransformW(projectionInverse);

	nearPoint /= nearPoint.w();
	farPoint /= farPoint.w();

	startPoint = gef::Vector4(nearPoint.x(), nearPoint.y(), nearPoint.z());
	direction = farPoint - nearPoint;
	direction.Normalise();
}

// modified from https://gamedev.stackexchange.com/questions/96459/fast-ray-sphere-collision-code
bool Level::RaySphereIntersect(gef::Vector4& startPoint, gef::Vector4& direction, gef::Vector4& sphere_centre, float sphere_radius)
{
	gef::Vector4 m = startPoint - sphere_centre;
	float b = m.DotProduct(direction);
	float c = m.LengthSqr() - sphere_radius * sphere_radius;

	// Exit if ray’s origin outside sphere (c > 0) and ray pointing away from sphere (b > 0) 
	if (c > 0.0f && b > 0.0f)
		return false;
	float discr = b * b - c;

	// A negative discriminant corresponds to ray missing sphere 
	if (discr < 0.0f)
		return false;

	// Ray now found to intersect sphere, compute smallest t value of intersection
	float t = -b - sqrtf(discr);

	// If t is negative, ray started inside sphere so clamp t to zero 
	if (t < 0.0f)
		t = 0.0f;

	gef::Vector4 hitpoint = startPoint + direction * t;

	return true;
}
