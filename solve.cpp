//
// Created by mike on 16-10-25.
//

#include <iostream>
#include "solve.h"
#include "useful.h"

namespace RubiksCube
{
	static OpStack op_seq;
	static Cube *cube;
	
	static std::string mapOperationName(ROTATE_METHOD rotate_method);
	
	static void fixButtomLayer(void);
	static void fixMiddleLayer(void);
	static void fixTopLayer(void);
	
	static void fixBottomEdge(void);
	static void fixBottomRightCorner(void);
	static void fixRightFrontEdge(void);
	static void fixTopFace(void);
	static void fixTopCorner(void);
	static void fixTopEdge(void);
	static void searchEdge(COLOR_NAME c1, COLOR_NAME c2, int &x0, int &y0, int &z0);
	static void searchCorner(COLOR_NAME c1, COLOR_NAME c2, COLOR_NAME c3, int &x0, int &y0, int &z0);
	static int countColorInFace(COLOR_NAME color, FACE_NAME face);
	
	static void performFormula(const char *formula);
	
	void solveCube(const Cube &cb, ROTATE_METHOD *op_sequence)
	{
		cube = new Cube(cb);
		op_seq.setElemPtr(op_sequence);
		
		fixButtomLayer();
		fixMiddleLayer();
		fixTopLayer();
		
		op_seq.add(STOP);
	}
	
	void printOperation(void)
	{
		for (int i = 0; op_seq[i] != STOP; i++)
		{
			std::string c = mapOperationName(op_seq[i]);
			if (c != "N") std::cout << c << ' ';
		}
		std::cout << std::endl;
	}
	
	std::string mapOperationName(ROTATE_METHOD rotate_method)
	{
		switch (rotate_method)
		{
		case U:
			return "U";
		case Ui:
			return "Ui";
		case D:
			return "D";
		case Di:
			return "Di";
		case F:
			return "F";
		case Fi:
			return "Fi";
		case B:
			return "B";
		case Bi:
			return "Bi";
		case R:
			return "R";
		case Ri:
			return "Ri";
		case L:
			return "L";
		case Li:
			return "Li";
		default:
			std::cerr << "Unknown operation: " << rotate_method << std::endl;
			return "Unknown";
		}
	}
	
	void performFormula(const char *formula)
	{
		char step;
		ROTATE_METHOD op;
		int index = 0;
		
		while ((step = formula[index++]) != 0)
		{
			if (step == 'R') op = R;
			else if (step == 'r') op = Ri;
			else if (step == 'L') op = L;
			else if (step == 'l') op = Li;
			else if (step == 'U') op = U;
			else if (step == 'u') op = Ui;
			else if (step == 'D') op = D;
			else if (step == 'd') op = Di;
			else if (step == 'F') op = F;
			else if (step == 'f') op = Fi;
			else if (step == 'B') op = B;
			else if (step == 'b') op = Bi;
			else if (step == 'X') op = X;
			else if (step == 'x') op = Xi;
			else if (step == 'Y') op = Y;
			else if (step == 'y') op = Yi;
			else if (step == 'Z') op = Z;
			else if (step == 'z') op = Zi;
			else op = N;
			
			op_seq.add(op);
			cube->rotateLayer(op);
		}
	}
	
	void fixButtomLayer(void)
	{
		for (int i = 0; i < 4; i++)
		{
			fixBottomEdge();
			performFormula("Y");
		}
		
		for (int i = 0; i < 4; i++)
		{
			fixBottomRightCorner();
			performFormula("y");
		}
		
	}
	
	void fixMiddleLayer(void)
	{
		for (int i = 0; i < 4; i++)
		{
			fixRightFrontEdge();
			performFormula("Y");
		}
	}
	
	void fixTopLayer(void)
	{
		fixTopFace();
		fixTopEdge();
		fixTopCorner();
	}
	
	void searchEdge(COLOR_NAME c1, COLOR_NAME c2, int &x0, int &y0, int &z0)
	{
		bool match_c1, match_c2;
		
		// search for the block to fix
		for_edge(x, y, z)
					{
						match_c1 = match_c2 = false;
						for (int i = 0; i < 6; i++)
						{
							if (cube->getBlockPtr(x, y, z)->getFaceColor(FACE_NAME(i)) == c1) match_c1 = true;
							if (cube->getBlockPtr(x, y, z)->getFaceColor(FACE_NAME(i)) == c2) match_c2 = true;
						}
						
						if (match_c1 && match_c2)
						{
							x0 = x, y0 = y, z0 = z;
							return;
						}
					}
	}
	
	void searchCorner(COLOR_NAME c1, COLOR_NAME c2, COLOR_NAME c3, int &x0, int &y0, int &z0)
	{
		bool match_c1, match_c2, match_c3;
		
		// search the block to fix
		for_corner(x, y, z)
				{
					match_c1 = match_c2 = match_c3 = false;
					
					for (int i = 0; i < 6; i++)
					{
						if (cube->getBlockPtr(x, y, z)->getFaceColor(FACE_NAME(i)) == c2) match_c1 = true;
						if (cube->getBlockPtr(x, y, z)->getFaceColor(FACE_NAME(i)) == c1) match_c2 = true;
						if (cube->getBlockPtr(x, y, z)->getFaceColor(FACE_NAME(i)) == c3) match_c3 = true;
					}
					
					if (match_c1 && match_c2 && match_c3)
					{
						x0 = x, y0 = y, z0 = z;
						return;
					}
				}
	}
	
	// code gets dirty from below...
	void fixBottomEdge(void)
	{
		COLOR_NAME target_down = cube->getBlockPtr(0, -1, 0)->getFaceColor(DOWN);
		COLOR_NAME target_front = cube->getBlockPtr(0, 0, 1)->getFaceColor(FRONT);
		
		int x0, y0, z0;
		
		searchEdge(target_down, target_front, x0, y0, z0);
		
		if (y0 == -1)    // the block to fix is in the bottom layer
		{
			if (x0 == 1) performFormula("rrU");
			else if (x0 == -1) performFormula("llu");
			else if (z0 == -1) performFormula("bbuu");
			else if (z0 == 1)
			{
				if (cube->getBlockPtr(0, -1, 1)->getFaceColor(DOWN) != target_down) performFormula("ff");
				else return;    // already in place
			}
		}
		else if (y0 == 0)    // the block to fix is in the middle layer
		{
			if (x0 == 1)
			{
				if (z0 == 1) performFormula("RUr");
				else performFormula("rUR");
			}
			else
			{
				if (z0 == 1) performFormula("luL");
				else performFormula("Lul");
			}
		}
		else    //the block to fix is in the top layer
		{
			if (x0 == 1) performFormula("U");
			else if (x0 == -1) performFormula("u");
			else if (z0 == -1) performFormula("uu");
		}
		
		// after the operations above the block to fix should have been placed in the top-front edge
		if (cube->getBlockPtr(0, 1, 1)->getFaceColor(UP) == target_down)
			performFormula("ff");
		else
			performFormula("urFR");
	}
	
	void fixBottomRightCorner(void)
	{
		COLOR_NAME target_right = cube->getBlockPtr(1, 0, 0)->getFaceColor(RIGHT);
		COLOR_NAME target_down = cube->getBlockPtr(0, -1, 0)->getFaceColor(DOWN);
		COLOR_NAME target_front = cube->getBlockPtr(0, 0, 1)->getFaceColor(FRONT);
		
		int x0, y0, z0;
		
		searchCorner(target_right, target_down, target_front, x0, y0, z0);
		
		if (y0 == 1)        // the block to fix is in the top layer
		{
			if (x0 == 1)
			{
				if (z0 == -1) performFormula("U");
			}
			else
			{
				if (z0 == 1) performFormula("u");
				else performFormula("UU");
			}
		}
		else    // the block is in the bottom layer
		{
			if (x0 == 1)
			{
				if (z0 == -1) performFormula("BUb");
				else if (cube->getBlockPtr(1, -1, 1)->getFaceColor(DOWN) == target_down) return;    // already in place
				else performFormula("RUru");
			}
			else
			{
				if (z0 == 1) performFormula("luL");
				else performFormula("Luul");
			}
		}
		
		// after the operations above, the block to fix should have been placed at the right-top-front corner
		if (cube->getBlockPtr(1, 1, 1)->getFaceColor(UP) == target_down)
			performFormula("ufUUFufUF");
		else if (cube->getBlockPtr(1, 1, 1)->getFaceColor(RIGHT) == target_down)
			performFormula("ufUF");
		else
			performFormula("URur");
	}
	
	void fixRightFrontEdge(void)
	{
		COLOR_NAME target_right = cube->getBlockPtr(1, 0, 0)->getFaceColor(RIGHT);
		COLOR_NAME target_front = cube->getBlockPtr(0, 0, 1)->getFaceColor(FRONT);
		
		int x0, y0, z0;
		
		searchEdge(target_right, target_front, x0, y0, z0);
		
		if (y0 == 0)        // the block to fix is in the middle layer
		{
			if (x0 == 1)
			{
				if (z0 == -1) performFormula("rURUBub");
				else if (cube->getBlockPtr(1, 0, 1)->getFaceColor(RIGHT) == target_right) return;    // already in place
				else performFormula("fUFURuru");
			}
			else
			{
				if (z0 == 1) performFormula("FufulULU");
				else performFormula("LulubUB");
			}
		}
		else    // the block to fix is in the top layer
		{
			if (x0 == 1) performFormula("U");
			else if (x0 == -1) performFormula("u");
			else if (z0 == -1) performFormula("UU");
		}
		
		if (cube->getBlockPtr(0, 1, 1)->getFaceColor(FRONT) == target_front)
			performFormula("URurufUF");
		else
			performFormula("UUfUFURur");
	}
	
	int countColorInFace(COLOR_NAME color, FACE_NAME face)
	{
		int count = 0;
		
		switch (face)
		{
		case RIGHT:
			for_right(x, y, z) if (cube->getBlockPtr(x, y, z)->getFaceColor(face) == color) count++;
			return count;
		case LEFT:
			for_left(x, y, z) if (cube->getBlockPtr(x, y, z)->getFaceColor(face) == color) count++;
			return count;
		case UP:
			for_up(x, y, z) if (cube->getBlockPtr(x, y, z)->getFaceColor(face) == color) count++;
			return count;
		case DOWN:
			for_down(x, y, z) if (cube->getBlockPtr(x, y, z)->getFaceColor(face) == color) count++;
			return count;
		case FRONT:
			for_front(x, y, z) if (cube->getBlockPtr(x, y, z)->getFaceColor(face) == color) count++;
			return count;
		case BACK:
			for_back(x, y, z) if (cube->getBlockPtr(x, y, z)->getFaceColor(face) == color) count++;
			return count;
		default:
			return 0;
		}
	}
	
	void fixTopFace(void)
	{
		bool top_match[3][3];
		int top_match_count;
		COLOR_NAME target_color = cube->getBlockPtr(0, 1, 0)->getFaceColor(UP);
		
		// top cross
		for (;;)
		{
			for_up(x, y, z) top_match[x + 1][z + 1] = (cube->getBlockPtr(x, y, z)->getFaceColor(UP) == target_color);
			if (top_match[0][1] && top_match[1][2] && top_match[2][1] && top_match[1][0]) break;    // top cross finished
			else if (top_match[1][0] && top_match[0][1]) performFormula("rufUFR");
			else if (top_match[1][0] && top_match[2][1]) performFormula("u");
			else if (top_match[2][1] && top_match[1][2]) performFormula("UU");
			else if (top_match[1][2] && top_match[0][1]) performFormula("U");
			else if (top_match[1][0] && top_match[1][2]) performFormula("u");
			else performFormula("rufUFR");
		}
		
		// top face
		if ((top_match_count = countColorInFace(target_color, UP)) == 5)
		{
			if (countColorInFace(target_color, RIGHT) == 2) performFormula("U");
			else if (countColorInFace(target_color, BACK) == 2) performFormula("UU");
			else if (countColorInFace(target_color, LEFT) == 2) performFormula("u");
			
			if (countColorInFace(target_color, BACK) == 2)
				performFormula("RuuruRUruRur");
			else
				performFormula("BuubbuBBubbuuB");
		}
		else if (top_match_count == 6)
		{
			if (top_match[2][0]) performFormula("u");
			else if (top_match[2][2]) performFormula("UU");
			else if (top_match[0][2]) performFormula("U");
			
			if (cube->getBlockPtr(1, 1, 1)->getFaceColor(FRONT) == target_color)
				performFormula("FUfUFuuf");
			else
				performFormula("BuubuBub");
		}
		else if (top_match_count == 7)
		{
			if (top_match[0][0] == top_match[2][2])
			{
				if (top_match[2][2]) performFormula("U");
				if (cube->getBlockPtr(1, 1, 1)->getFaceColor(RIGHT) == target_color) performFormula("UU");
				
				performFormula("fXLUruxlFR");
			}
			else
			{
				if (top_match[2][0] && top_match[2][2]) performFormula("U");
				else if (top_match[0][0] && top_match[2][0]) performFormula("UU");
				else if (top_match[0][0]) performFormula("u");
				
				if (countColorInFace(target_color, BACK))
					performFormula("RRdRuurDRuuR");
				else
					performFormula("ZBUfuzbLFl");
			}
		}
	}
	
	void fixTopEdge(void)
	{
		COLOR_NAME target_front = cube->getBlockPtr(0, 0, 1)->getFaceColor(FRONT);
		
		if (cube->getBlockPtr(1, 1, 0)->getFaceColor(RIGHT) == target_front) performFormula("U");
		else if (cube->getBlockPtr(0, 1, -1)->getFaceColor(BACK) == target_front) performFormula("UU");
		else if (cube->getBlockPtr(-1, 1, 0)->getFaceColor(LEFT) == target_front) performFormula("u");
		
		COLOR_NAME target_right = cube->getBlockPtr(1, 0, 0)->getFaceColor(RIGHT);
		COLOR_NAME target_left = cube->getBlockPtr(-1, 0, 0)->getFaceColor(LEFT);
		COLOR_NAME target_back = cube->getBlockPtr(0, 0, -1)->getFaceColor(BACK);
		
		COLOR_NAME curr_right = cube->getBlockPtr(1, 1, 0)->getFaceColor(RIGHT);
		COLOR_NAME curr_left = cube->getBlockPtr(-1, 1, 0)->getFaceColor(LEFT);
		COLOR_NAME curr_back = cube->getBlockPtr(0, 1, -1)->getFaceColor(BACK);
		
		if (target_left == curr_left)
		{
			if (target_back != curr_back) performFormula("BUbrBUbubRBBubu");
		}
		else if (target_back == curr_back) performFormula("rURurfuFRUrFrfRuR");
		else if (target_right == curr_right) performFormula("FRuruRUrfRUrurFRf");
		else if (target_back == curr_left) performFormula("LLULUlululUl");
		else performFormula("LuLULULulull");
	}
	
	void fixTopCorner(void)
	{
		COLOR_NAME target_right = cube->getBlockPtr(1, 0, 0)->getFaceColor(RIGHT);
		COLOR_NAME target_left = cube->getBlockPtr(-1, 0, 0)->getFaceColor(LEFT);
		COLOR_NAME target_back = cube->getBlockPtr(0, 0, -1)->getFaceColor(BACK);
		COLOR_NAME target_front = cube->getBlockPtr(0, 0, 1)->getFaceColor(FRONT);
		
		COLOR_NAME curr_front_left = cube->getBlockPtr(-1, 1, 1)->getFaceColor(FRONT);
		COLOR_NAME curr_front_right = cube->getBlockPtr(1, 1, 1)->getFaceColor(FRONT);
		COLOR_NAME curr_right_front = cube->getBlockPtr(1, 1, 1)->getFaceColor(RIGHT);
		COLOR_NAME curr_right_back = cube->getBlockPtr(1, 1, -1)->getFaceColor(RIGHT);
		COLOR_NAME curr_back_right = cube->getBlockPtr(1, 1, -1)->getFaceColor(BACK);
		COLOR_NAME curr_back_left = cube->getBlockPtr(-1, 1, -1)->getFaceColor(BACK);
		COLOR_NAME curr_left_back = cube->getBlockPtr(-1, 1, -1)->getFaceColor(LEFT);
		COLOR_NAME curr_left_front = cube->getBlockPtr(-1, 1, 1)->getFaceColor(LEFT);
		
		if (curr_front_right == target_front)
		{
			if (curr_front_left == target_left) performFormula("XLLDDluLDDlUl");
			else if (curr_front_left == target_back) performFormula("XLuLDDlULDDll");
		}
		else if (curr_left_front == target_front)
		{
			if (curr_back_left == target_left) performFormula("zFuFDDfUFDDff");
			else if (curr_right_back == target_left) performFormula("xRuRDDrURDDrr");
			else performFormula("zFufDFUfdFUfDFufd");
		}
		else if (curr_back_left == target_front)
		{
			if (curr_front_left == target_front) performFormula("ZBuBDDbUBDDbb");
			else if (curr_back_right == target_front) performFormula("LrLrDLrLrUULrLrDLrLrUU");
			else performFormula("zFFDDfuFDDfUf");
		}
		else if (curr_right_back == target_front)
		{
			if (curr_back_left == target_left) performFormula("xRurDRUrdRUrDRurd");
			else if (curr_back_left == target_right) performFormula("ZBBDDbuBDDbUb");
			else performFormula("xRRDDruRDDrUr");
		}
	}
	
	inline void OpStack::setElemPtr(ROTATE_METHOD *op)
	{
		_elem = op;
		_stack_top = 0;
	}
	
	inline ROTATE_METHOD OpStack::pop(void)
	{
		if (_stack_top > 0)
			return _elem[--_stack_top];
		else
		{
			_stack_top = 0;
			return N;
		}
	}
	
	inline void OpStack::add(ROTATE_METHOD method)
	{
		if (method != X && method != Xi && method != Y && method != Yi && method != Z && method != Zi && method != N)
		{
			if (method == STOP)
			{
				push(STOP);
				return;
			}
			method = cube->getMappedOperation(method);
			
			ROTATE_METHOD top = pop();
			ROTATE_METHOD second = pop();
			
			if (method == -top)
			{
				push(second);
			}
			else if (method == top && method == second)
			{
				push(ROTATE_METHOD(-method));
			}
			else
			{
				if (second != N) push(second);
				if (top != N) push(top);
				push(method);
			}
		}
		
	}
	
	inline void OpStack::push(ROTATE_METHOD rotate_method)
	{
		_elem[_stack_top++] = rotate_method;
	}
	
	ROTATE_METHOD OpStack::operator[](int index)
	{
		return _elem[index];
	}
}