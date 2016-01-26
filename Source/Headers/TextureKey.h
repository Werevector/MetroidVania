#pragma once
#include "SDL.h"
class TextureKey{

public:
	int clip_key;
	SDL_RendererFlip flipping;

	TextureKey(){
		clip_key = 0;
		flipping = SDL_FLIP_NONE;
	}


};

