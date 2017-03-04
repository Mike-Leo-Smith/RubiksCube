//
// Created by mike on 16-10-25.
//

#include "RubiksCube.h"
#include "display.h"

using namespace RubiksCube;

int main(int argc, char *argv[])
{
	ROTATE_METHOD op[10000] = { STOP };
	Cube cube;
	/*
	char cube_raw[6][3][3];
	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cube_raw[i][j][k] = (char)std::cin.get();
			}
		}
		std::cin.get(); // Get rid of '\n'
	}
	*/
	//cube.loadCube(cube_raw);
	//solveCube(cube, op);
	//printOperation();
	
	initDisplay(cube);
	loadOperation(op);
	startDisplay();
	
	return 0;
}