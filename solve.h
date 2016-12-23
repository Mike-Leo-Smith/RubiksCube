//
// Created by mike on 16-10-25.
//

#ifndef _SOLVE_H_
#define _SOLVE_H_

#include "RubiksCube.h"

namespace RubiksCube
{
	class OpStack
	{
	private:
		int _stack_top;
		ROTATE_METHOD *_elem;
		ROTATE_METHOD pop(void);
		void push(ROTATE_METHOD rotate_method);
	
	public:
		void add(ROTATE_METHOD method);
		void setElemPtr(ROTATE_METHOD *op);
		ROTATE_METHOD operator[](int index);
	};
	
	void solveCube(const Cube &cb, ROTATE_METHOD *op_sequence);
	void printOperation(void);
}

#endif	// _SOLVE_H_
