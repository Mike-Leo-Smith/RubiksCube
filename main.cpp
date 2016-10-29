//
// Created by mike on 16-10-25.
//

#include <iostream>
#include "RubiksCube.h"
#include "solve.h"
#include "display.h"

using namespace RubiksCube;

int main(int argc, char *argv[])
{
	ROTATE_METHOD op[10000] = {STOP};
	
	int seed, n;
	
	Cube cube;
	
	std::cin >> seed;
	srand((unsigned int)seed);
	
	for (int i = 0; i < 971216; i++)
		cube.rotateLayer(ROTATE_METHOD((rand() % 2 ? 1 : -1) * (rand() % 9 + 1)));
	
	solveCube(cube, op);
	initDisplay(argc, argv, cube);
	loadOperation(op);
	startDisplay();
	
	return 0;
}