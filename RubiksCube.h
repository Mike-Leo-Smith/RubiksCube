//
// Created by mike on 16-10-21.
//

#ifndef _RUBIKSCUBE_H_
#define _RUBIKSCUBE_H_

#include "constants.h"

namespace RubiksCube
{
	class Block
	{
	private:
		COLOR_NAME _face[6];
	
	public:
		Block(int x, int y, int z, COLOR_NAME cx, COLOR_NAME cy, COLOR_NAME cz);
		Block(int x, int y, int z);
		void setFaceColor(FACE_NAME face, COLOR_NAME color);
		const COLOR_NAME getFaceColor(FACE_NAME fn) const;
		const COLOR_NAME *getFaceColor(void) const;
		void rotateBlock(ROTATE_METHOD rotate_method);
	};
	
	class Layer
	{
	private:
		Block **_block[8];       // pointers to pointer to blocks in a face in counter-clockwise to the direction of axes
		Block *&getBlockPtrRef(int index);
	
	public:
		void connectBlock(int index, Block *&block);
		void rotateBlockInLayer(ROTATE_METHOD rotate_method);
	};
	
	class Cube
	{
	private:
		Block *_block[3][3][3];
		Layer _layer[6];
		Block *&getBlockPtrRef(int x, int y, int z);
		FACE_NAME _color_face_map[6];
		void connectBlockToLayer(void);
		COLOR_NAME getFaceCenterColor(FACE_NAME fn) const;
	
	public:
		Cube(void);
		Cube(const Cube &cb);
		const Block *getBlockPtr(int x, int y, int z) const;
		void rotateLayer(ROTATE_METHOD rotate_method);
		void loadCube(const char face[6][3][3]);
		ROTATE_METHOD getMappedOperation(ROTATE_METHOD method) const;
	};
}

#endif  // _RUBIKSCUBE_H_
