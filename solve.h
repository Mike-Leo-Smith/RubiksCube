//
// Created by mike on 16-10-25.
//

#include "RubiksCube.h"

#ifndef _SOLVE_H_
#define _SOLVE_H_

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
		void add(ROTATE_METHOD rotate_method);
		void setElemPtr(ROTATE_METHOD *op);
	};
	
	void solveCube(const Cube &cb, ROTATE_METHOD *op_sequence);
}

#endif	// _SOLVE_H_
