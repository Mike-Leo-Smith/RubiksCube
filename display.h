//
// Created by mike on 16-10-23.
//

#include "constants.h"
#include "RubiksCube.h"

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

namespace RubiksCube
{
	struct Animation
	{
		int frame_count;
		static const int MAX_FRAME = 90;
		static const int STEP = 6;
		ROTATE_METHOD rotate_method = N;
		
		Animation(ROTATE_METHOD rotate_method) : frame_count(0), rotate_method(rotate_method){}
	};
	
	extern void initDisplay(int &argc, char *argv[], const RubiksCube::Cube &cb);
	extern void startDisplay(void);
	extern void loadOperation(const ROTATE_METHOD *s);
}

#endif	// _DISPLAY_H_
