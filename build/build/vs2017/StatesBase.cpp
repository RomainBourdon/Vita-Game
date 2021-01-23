#include "StatesBase.h"



StatesBase::StatesBase() :
	//set the pointers to null
	sprite_renderer(NULL),
	input_manager(NULL),
	renderer_3d(NULL),
	font(NULL),
	primitive_builder(NULL),
	audio_manager(NULL)
{
}


StatesBase::~StatesBase()
{
}

void StatesBase::Releases()
{
	//delete the pointers that the different scenes share
	delete input_manager;
	input_manager = NULL;

	delete sprite_renderer;
	sprite_renderer = NULL;

	delete renderer_3d;
	renderer_3d = NULL;

	delete primitive_builder;
	primitive_builder = NULL;

	delete font;
	font = NULL;

	delete audio_manager;
	audio_manager = NULL;

	audio_manager->UnloadMusic();
}

