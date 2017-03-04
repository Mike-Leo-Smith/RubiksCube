//
// Created by mike on 16-10-21.
//

#include "display.h"
#include "useful.h"

namespace RubiksCube
{
	Block::Block(int x, int y, int z)
	{
		for (int i = 0; i < 6; i++)
			_face[i] = INVISIBLE;
		
		if (x) _face[RIGHT + ((1 - x) >> 1)] = COLOR_NAME(RIGHT + ((1 - x) >> 1));
		if (y) _face[UP + ((1 - y) >> 1)] = COLOR_NAME(UP + ((1 - y) >> 1));
		if (z) _face[FRONT + ((1 - z) >> 1)] = COLOR_NAME(FRONT + ((1 - z) >> 1));
	}
	
	Block::Block(int x, int y, int z, COLOR_NAME cx, COLOR_NAME cy, COLOR_NAME cz)
	{
		for (int i = 0; i < 6; i++)
			_face[i] = INVISIBLE;
		
		_face[RIGHT + ((1 - x) >> 1)] = cx;
		_face[UP + ((1 - y) >> 1)] = cy;
		_face[FRONT + ((1 - z) >> 1)] = cz;
	}
	
	const COLOR_NAME Block::getFaceColor(FACE_NAME fn) const
	{
		return _face[fn];
	}
	
	void Block::rotateBlock(ROTATE_METHOD rotate_method)
	{
		if (abs(rotate_method) == Ri || abs(rotate_method) == Xi || abs(rotate_method) == L)
			shift4(_face[UP], _face[FRONT], _face[DOWN], _face[BACK], rotate_method > 0);
		else if (abs(rotate_method) == Ui || abs(rotate_method) == Yi || abs(rotate_method) == D)
			shift4(_face[RIGHT], _face[BACK], _face[LEFT], _face[FRONT], rotate_method > 0);
		else if (abs(rotate_method) == Fi || abs(rotate_method) == Zi || abs(rotate_method) == B)
			shift4(_face[UP], _face[LEFT], _face[DOWN], _face[RIGHT], rotate_method > 0);
	}
	
	const COLOR_NAME *Block::getFaceColor(void) const
	{
		return _face;
	}
	
	void Block::setFaceColor(FACE_NAME face, COLOR_NAME color)
	{
		_face[face] = color;
	}
	
	Block *&Cube::getBlockPtrRef(int x, int y, int z)
	{
		return _block[x + 1][y + 1][z + 1];
	}
	
	Cube::Cube(void)
	{
		for_each(x, y, z) getBlockPtrRef(x, y, z) = new Block(x, y, z);
		connectBlockToLayer();
		for (int i = 0; i < 6; i++) _color_face_map[getFaceCenterColor((FACE_NAME)i)] = (FACE_NAME)i;
	}
	
	void Cube::rotateLayer(ROTATE_METHOD rotate_method)
	{
		if (abs(rotate_method) < Xi)    // not to rotate the whole cube
		{
			_layer[abs(rotate_method) - 1].rotateBlockInLayer(rotate_method);
		}
		else    // rotate the whole cube
		{
			for_each(x, y, z) getBlockPtrRef(x, y, z)->rotateBlock(rotate_method);
			
			Block *temp[3][3][3];
			int dir = rotate_method > 0 ? 1 : -1;   // dir is set to 1 if counter-clockwise
			
			for_each(x, y, z) if (abs(rotate_method) == Xi) temp[x + 1][-dir * z + 1][dir * y + 1] = getBlockPtrRef(x, y, z);
						else if (abs(rotate_method) == Yi) temp[dir * z + 1][y + 1][-dir * x + 1] = getBlockPtrRef(x, y, z);
						else if (abs(rotate_method) == Zi) temp[-dir * y + 1][dir * x + 1][z + 1] = getBlockPtrRef(x, y, z);
			
			for_each(x, y, z) getBlockPtrRef(x, y, z) = temp[x + 1][y + 1][z + 1];
		}
	}
	
	const Block *Cube::getBlockPtr(int x, int y, int z) const
	{
		return _block[x + 1][y + 1][z + 1];
	}
	
	Cube::Cube(const Cube &cb)
	{
		for_each(x, y, z) getBlockPtrRef(x, y, z) = new Block(*cb.getBlockPtr(x, y, z));
		for (int i = 0; i < 6; i++)
		{
			_color_face_map[i] = cb._color_face_map[i];
		}
		connectBlockToLayer();
		for (int i = 0; i < 6; i++) _color_face_map[getFaceCenterColor((FACE_NAME)i)] = (FACE_NAME)i;
	}
	
	void Cube::connectBlockToLayer(void)
	{
		for (int i = 0; i < 8; i++)
		{
			_layer[UP].connectBlock(i, getBlockPtrRef(INDEX_XZ_CCW[i][0], 1, INDEX_XZ_CCW[i][1]));
			_layer[DOWN].connectBlock(i, getBlockPtrRef(INDEX_XZ_CCW[i][0], -1, INDEX_XZ_CCW[i][1]));
			_layer[RIGHT].connectBlock(i, getBlockPtrRef(1, INDEX_YZ_CCW[i][0], INDEX_YZ_CCW[i][1]));
			_layer[LEFT].connectBlock(i, getBlockPtrRef(-1, INDEX_YZ_CCW[i][0], INDEX_YZ_CCW[i][1]));
			_layer[FRONT].connectBlock(i, getBlockPtrRef(INDEX_XY_CCW[i][0], INDEX_XY_CCW[i][1], 1));
			_layer[BACK].connectBlock(i, getBlockPtrRef(INDEX_XY_CCW[i][0], INDEX_XY_CCW[i][1], -1));
		}
	}
	
	inline COLOR_NAME mapColorName(char color)
	{
		switch (color)
		{
		case 'R':
			return RED;
		case 'O':
			return ORANGE;
		case 'Y':
			return YELLOW;
		case 'W':
			return WHITE;
		case 'B':
			return BLUE;
		case 'G':
			return GREEN;
		default:
			return INVISIBLE;
		}
	}
	
	// Load the cube in FRONT-BACK-RIGHT-LEFT-UP-DOWN order
	void Cube::loadCube(const char face[6][3][3])
	{
		for_front(x, y, z) getBlockPtrRef(x, y, z)->setFaceColor(FRONT, mapColorName(face[0][-y + 1][x + 1]));
		for_back(x, y, z) getBlockPtrRef(x, y, z)->setFaceColor(BACK, mapColorName(face[1][-y + 1][-x + 1]));
		for_right(x, y, z) getBlockPtrRef(x, y, z)->setFaceColor(RIGHT, mapColorName(face[2][-y + 1][-z + 1]));
		for_left(x, y, z) getBlockPtrRef(x, y, z)->setFaceColor(LEFT, mapColorName(face[3][-y + 1][z + 1]));
		for_up(x, y, z) getBlockPtrRef(x, y, z)->setFaceColor(UP, mapColorName(face[4][z + 1][x + 1]));
		for_down(x, y, z) getBlockPtrRef(x, y, z)->setFaceColor(DOWN, mapColorName(face[5][-z + 1][x + 1]));
		
		// sadly we cannot have X, Y, Z rotations in the output, so use this mapping to patch...
		for (int i = 0; i < 6; i++) _color_face_map[getFaceCenterColor((FACE_NAME)i)] = (FACE_NAME)i;
	}
	
	COLOR_NAME Cube::getFaceCenterColor(FACE_NAME fn) const
	{
		int x = 0, y = 0, z = 0;
		
		if (fn == FRONT) z = 1;
		else if (fn == BACK) z = -1;
		else if (fn == RIGHT) x = 1;
		else if (fn == LEFT) x = -1;
		else if (fn == UP) y = 1;
		else if (fn == DOWN) y = -1;
		
		return getBlockPtr(x, y, z)->getFaceColor(fn);
	}
	
	ROTATE_METHOD Cube::getMappedOperation(ROTATE_METHOD method) const
	{
		FACE_NAME op_face = FACE_NAME(abs(method) - 1);
		FACE_NAME origin_face = _color_face_map[getFaceCenterColor(op_face)];
		ROTATE_METHOD origin_method = ROTATE_METHOD(origin_face + 1);
		if ((method > 0 && method % 2 != 0) || (method < 0 && abs(method) % 2 == 0))  // counter-clockwise rotation methods
		{
			if (origin_method % 2 == 0) origin_method = ROTATE_METHOD(-origin_method);
		}
		else    // clockwise rotation methods
		{
			if (origin_method % 2 != 0) origin_method = ROTATE_METHOD(-origin_method);
		}
		return origin_method;
	}
	
	void Layer::connectBlock(int index, Block *&block)
	{
		_block[index] = &block;
	}
	
	void Layer::rotateBlockInLayer(ROTATE_METHOD rotate_method)
	{
		// rotate blocks themselves first
		for (int i = 0; i < 8; i++)
			getBlockPtrRef(i)->rotateBlock(rotate_method);
		
		// then shift corners and edges
		shift4(getBlockPtrRef(0), getBlockPtrRef(2), getBlockPtrRef(4), getBlockPtrRef(6), rotate_method > 0);
		shift4(getBlockPtrRef(1), getBlockPtrRef(3), getBlockPtrRef(5), getBlockPtrRef(7), rotate_method > 0);
	}
	
	Block *&Layer::getBlockPtrRef(int index)
	{
		return *(_block[index]);
	}
}
