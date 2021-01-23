#include "StateManager.h"
#include <input/sony_controller_input_manager.h>




StateManager::StateManager():
	spriterenderer(NULL),
	inputmanager(NULL),
	renderer3d(NULL),
	primitivebuilder(NULL), 
	fo(NULL)
{
}

StateManager::~StateManager()
{
}

void StateManager::Release()
{
	//call the cleanup of the current state
	currentstate->Release();

	//delete the pointers statemachine is using
	delete inputmanager;
	inputmanager = NULL;

	delete spriterenderer;
	spriterenderer = NULL;

	delete renderer3d;
	renderer3d = NULL;

	delete primitivebuilder;
	primitivebuilder = NULL;

	delete fo;
	fo = NULL;
}

void StateManager::init(gef::SpriteRenderer * spr, gef::Font* fon, gef::InputManager * inp, gef::Renderer3D * ren, PrimitiveBuilder * primi, gef::AudioManager* audio, gef::Platform &plat, float ndc_z_min)
{
	//initialize the pointers 
	spriterenderer = spr;
	inputmanager = inp;
	renderer3d = ren;
	primitivebuilder = primi;
	fo = fon;
	ndc_z_mi = ndc_z_min;
	audio_manager_ = audio;

	//set the first state to be splash screen
	states =SPLASH;
	currentstate = &splashstate;
	currentstate->Init(spr, fon, inp, ren, primi, audio, plat, amount_grnd, amount_bnce, amount_enmy, ndc_z_mi, hscore1, hscore2, hscore3, states);
}

void StateManager::UpdateGameStateMachine(float frame_time, gef::Platform &plat)
{	
		//save the old currentstate pointer
		oldstate = currentstate;

		//switch the states
		switch (states)
		{
		case MENU:
			currentstate = &menustate;
			break;
		case LEVEL1:
			currentstate = &levelstate1;
			amount_grnd = 2;
			amount_bnce = 2;
			amount_enmy = 0;
			break;
		case LEVEL2:
			currentstate = &levelstate2;
			amount_grnd = 3;
			amount_bnce = 1;
			amount_enmy = 2;
			break;
		case LEVEL3:
			currentstate = &levelstate3;
			amount_grnd = 4;
			amount_bnce = 0;
			amount_enmy = 4;
			break;
		case CONGRATS:
			currentstate = &winstate;
			break;
		case RESTART:
			currentstate->Release();
			states = oldGamestate;
			break;
		case CONTROLS:
			currentstate = &controlstate;
			break;
		case HIGH_SCORE:
			currentstate = &highscorestate;
			break;
		default:
			break;
		}

		//clean up the state we were on previously
		oldstate->Release();
		
		//if its the congrats state pass in the oldstate instead of state
		if (states == CONGRATS)
		{
			currentstate->Init(spriterenderer, fo, inputmanager, renderer3d, primitivebuilder, audio_manager_, plat, amount_grnd, amount_bnce, amount_enmy, ndc_z_mi, hscore1, hscore2, hscore3, oldGamestate);
		}
		else //initialize the new current state 
		{
			currentstate->Init(spriterenderer, fo, inputmanager, renderer3d, primitivebuilder, audio_manager_, plat, amount_grnd, amount_bnce, amount_enmy, ndc_z_mi, hscore1, hscore2, hscore3, states);
		}
	
}

void StateManager::Update(float frame_time, gef::Platform &plat)
{
	//set the null variable onstate to equal the return value of update
	onstate = currentstate->update(frame_time, plat, states);
	//save the Gamestate we were on previously
	oldGamestate = states;
	//check if the Gamestates dont match
	if (states != onstate)
	{
		states = onstate;
		UpdateGameStateMachine(frame_time, plat);
		
	}
	
	
}

void StateManager::Render(gef::Platform &plat)
{
	//render the current state
		
	currentstate->Render(plat);
}