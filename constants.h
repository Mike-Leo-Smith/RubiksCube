//
// Created by mike on 16-10-23.
//

#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

namespace RubiksCube
{
	enum COLOR_NAME
	{
		RED, ORANGE, YELLOW, WHITE, BLUE, GREEN, BLOCK, PIVOT, INVISIBLE
	};
	
	const unsigned char Color3ub[][3] =
			{
					{220, 30, 40},      // red
					{250, 110, 25},     // orange
					{210, 220, 35},     // yellow
					{220, 220, 220},    // white
					{45, 65, 250},      // blue
					{45, 210, 45},      // green
					{25, 25, 25},       // color of block
					{20, 20, 20}        // color of pivot
			};
	
	enum FACE_NAME
	{
		RIGHT, LEFT, UP, DOWN, FRONT, BACK
	};
	
	// rotate methods of a layer or a block, positive if counter-clockwise to axes direction
	enum ROTATE_METHOD
	{
		STOP = 0x1f, N = 0,
		Ri = 1, L, Ui, D, Fi, B, Xi, Yi, Zi,
		Z = -Zi, Y, X, Bi, F, Di, U, Li, R
	};
	
	// index of coordination when traverse blocks in a face counter-clockwise
	const int INDEX_XY_CCW[8][2] = {{1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}};
	const int INDEX_YZ_CCW[8][2] = {{1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}};
	const int INDEX_XZ_CCW[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}};
}

#endif	// _CONSTANTS_H_
