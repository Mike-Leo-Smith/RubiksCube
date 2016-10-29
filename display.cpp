//
// Created by mike on 16-10-23.
//

#include "GL/freeglut.h"
#include "RubiksCube.h"
#include "display.h"
#include "usefull.h"

namespace RubiksCube
{
	static Animation ani = Animation(N);
	
	float rot_x = 20;
	float rot_y = -30;
	float rot_z = 0;
	
	const ROTATE_METHOD *operation;
	int op_count = 0;
	
	RubiksCube::Cube *cube;
	
	static void drawBlock(const COLOR_NAME *face, int x, int y, int z);
	static void drawAnimation(Animation &ani);
	
	static void reshape(int w, int h)
	{
		if (h == 0)
			h = 1;
		
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(20, GLfloat(w) / h, 1, 100);
		glMatrixMode(GL_MODELVIEW);
	}
	
	static void procKey(int keycode, int x, int y)
	{
		if (keycode == GLUT_KEY_UP)
			rot_x -= 5;
		else if (keycode == GLUT_KEY_DOWN)
			rot_x += 5;
		else if (keycode == GLUT_KEY_LEFT)
			rot_y -= 5;
		else if (keycode == GLUT_KEY_RIGHT)
			rot_y += 5;
		else if (keycode == GLUT_KEY_F1)
			ani = Animation(R);
		else if (keycode == GLUT_KEY_F2)
			ani = Animation(L);
		else if (keycode == GLUT_KEY_F3)
			ani = Animation(U);
		else if (keycode == GLUT_KEY_F4)
			ani = Animation(D);
		else if (keycode == GLUT_KEY_F5)
			ani = Animation(F);
		else if (keycode == GLUT_KEY_F6)
			ani = Animation(B);
		else if (keycode == GLUT_KEY_F7)
			ani = Animation(L);
		else if (keycode == GLUT_KEY_F8)
			ani = Animation(Li);
		
	}
	
	void startDisplay()
	{
		glutMainLoop();
	}
	
	void drawBlock(const COLOR_NAME *face, int x, int y, int z)
	{
		const double sticker_size = 0.85;
		const double block_size = 0.97;
		
		glBegin(GL_QUADS);
		{
			// right
			glColor3ubv(Color3ub[face[RIGHT]]);
			glVertex3d(2 * x + 1, 2 * y + sticker_size, 2 * z + sticker_size);
			glVertex3d(2 * x + 1, 2 * y - sticker_size, 2 * z + sticker_size);
			glVertex3d(2 * x + 1, 2 * y - sticker_size, 2 * z - sticker_size);
			glVertex3d(2 * x + 1, 2 * y + sticker_size, 2 * z - sticker_size);
			glColor3ubv(Color3ub[INVISIBLE]);
			glVertex3d(2 * x + block_size, 2 * y + block_size, 2 * z + block_size);
			glVertex3d(2 * x + block_size, 2 * y - block_size, 2 * z + block_size);
			glVertex3d(2 * x + block_size, 2 * y - block_size, 2 * z - block_size);
			glVertex3d(2 * x + block_size, 2 * y + block_size, 2 * z - block_size);
			
			// left
			glColor3ubv(Color3ub[face[LEFT]]);
			glVertex3d(2 * x - 1, 2 * y + sticker_size, 2 * z + sticker_size);
			glVertex3d(2 * x - 1, 2 * y + sticker_size, 2 * z - sticker_size);
			glVertex3d(2 * x - 1, 2 * y - sticker_size, 2 * z - sticker_size);
			glVertex3d(2 * x - 1, 2 * y - sticker_size, 2 * z + sticker_size);
			glColor3ubv(Color3ub[INVISIBLE]);
			glVertex3d(2 * x - block_size, 2 * y + block_size, 2 * z + block_size);
			glVertex3d(2 * x - block_size, 2 * y + block_size, 2 * z - block_size);
			glVertex3d(2 * x - block_size, 2 * y - block_size, 2 * z - block_size);
			glVertex3d(2 * x - block_size, 2 * y - block_size, 2 * z + block_size);
			
			// up
			glColor3ubv(Color3ub[face[UP]]);
			glVertex3d(2 * x + sticker_size, 2 * y + 1, 2 * z + sticker_size);
			glVertex3d(2 * x + sticker_size, 2 * y + 1, 2 * z - sticker_size);
			glVertex3d(2 * x - sticker_size, 2 * y + 1, 2 * z - sticker_size);
			glVertex3d(2 * x - sticker_size, 2 * y + 1, 2 * z + sticker_size);
			glColor3ubv(Color3ub[INVISIBLE]);
			glVertex3d(2 * x + block_size, 2 * y + block_size, 2 * z + block_size);
			glVertex3d(2 * x + block_size, 2 * y + block_size, 2 * z - block_size);
			glVertex3d(2 * x - block_size, 2 * y + block_size, 2 * z - block_size);
			glVertex3d(2 * x - block_size, 2 * y + block_size, 2 * z + block_size);
			
			// down
			glColor3ubv(Color3ub[face[DOWN]]);
			glVertex3d(2 * x + sticker_size, 2 * y - 1, 2 * z + sticker_size);
			glVertex3d(2 * x - sticker_size, 2 * y - 1, 2 * z + sticker_size);
			glVertex3d(2 * x - sticker_size, 2 * y - 1, 2 * z - sticker_size);
			glVertex3d(2 * x + sticker_size, 2 * y - 1, 2 * z - sticker_size);
			glColor3ubv(Color3ub[INVISIBLE]);
			glVertex3d(2 * x + block_size, 2 * y - block_size, 2 * z + block_size);
			glVertex3d(2 * x - block_size, 2 * y - block_size, 2 * z + block_size);
			glVertex3d(2 * x - block_size, 2 * y - block_size, 2 * z - block_size);
			glVertex3d(2 * x + block_size, 2 * y - block_size, 2 * z - block_size);
			
			// front
			glColor3ubv(Color3ub[face[FRONT]]);
			glVertex3d(2 * x + sticker_size, 2 * y + sticker_size, 2 * z + 1);
			glVertex3d(2 * x - sticker_size, 2 * y + sticker_size, 2 * z + 1);
			glVertex3d(2 * x - sticker_size, 2 * y - sticker_size, 2 * z + 1);
			glVertex3d(2 * x + sticker_size, 2 * y - sticker_size, 2 * z + 1);
			glColor3ubv(Color3ub[INVISIBLE]);
			glVertex3d(2 * x + block_size, 2 * y + block_size, 2 * z + block_size);
			glVertex3d(2 * x - block_size, 2 * y + block_size, 2 * z + block_size);
			glVertex3d(2 * x - block_size, 2 * y - block_size, 2 * z + block_size);
			glVertex3d(2 * x + block_size, 2 * y - block_size, 2 * z + block_size);
			
			// back
			glColor3ubv(Color3ub[face[BACK]]);
			glVertex3d(2 * x + sticker_size, 2 * y + sticker_size, 2 * z - 1);
			glVertex3d(2 * x + sticker_size, 2 * y - sticker_size, 2 * z - 1);
			glVertex3d(2 * x - sticker_size, 2 * y - sticker_size, 2 * z - 1);
			glVertex3d(2 * x - sticker_size, 2 * y + sticker_size, 2 * z - 1);
			glColor3ubv(Color3ub[INVISIBLE]);
			glVertex3d(2 * x + block_size, 2 * y + block_size, 2 * z - block_size);
			glVertex3d(2 * x + block_size, 2 * y - block_size, 2 * z - block_size);
			glVertex3d(2 * x - block_size, 2 * y - block_size, 2 * z - block_size);
			glVertex3d(2 * x - block_size, 2 * y + block_size, 2 * z - block_size);
		}
		glEnd();
	}
	
	void drawCube(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawAnimation(ani);
		if (ani.rotate_method == N)
		{
			char op;
			if ((op = operation[op_count]) != STOP)
			{
				op_count++;
				ani = Animation((ROTATE_METHOD)op);
			}
		}
		glutSwapBuffers();
	}
	
	void initDisplay(int &argc, char *argv[], const RubiksCube::Cube &cb)
	{
		cube = new RubiksCube::Cube(cb);
		
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
		glutInitWindowPosition(100, 100);
		glutInitWindowSize(600, 500);
		glutCreateWindow("Rubik's Cube");
		
		glutDisplayFunc(drawCube);
		glutIdleFunc(drawCube);
		glutReshapeFunc(reshape);
		glutSpecialFunc(procKey);
		
		glClearColor(0.3, 0.3, 0.3, 1.0);
		glClearDepth(1);
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_MULTISAMPLE);
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(20, GLfloat(600) / 500, 1, 100);
		glMatrixMode(GL_MODELVIEW);
		
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	
	void drawAnimation(Animation &ani)
	{
		if ((ani.frame_count += ani.STEP) > ani.MAX_FRAME)
		{
			if (ani.rotate_method != N) cube->rotateLayer(ani.rotate_method);
			ani = Animation(N);
		}
		
		glLoadIdentity();
		glTranslatef(0, 0, -30);
		glRotatef(rot_x, 1, 0, 0);
		glRotatef(rot_y, 0, 1, 0);
		glRotatef(rot_z, 0, 0, 1);
		
		switch (ani.rotate_method)
		{
		case N:
			for_each(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			break;
		
		case X:
		case Xi:
			glRotatef(ani.frame_count * sgn(ani.rotate_method), 1, 0, 0);
			for_each(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			break;
		
		case R:
		case Ri:
			for_noright(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			glRotatef(ani.frame_count * sgn(ani.rotate_method), 1, 0, 0);
			for_right(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			break;
		
		case L:
		case Li:
			for_noleft(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			glRotatef(ani.frame_count * sgn(ani.rotate_method), 1, 0, 0);
			for_left(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			break;
		
		case Y:
		case Yi:
			glRotatef(ani.frame_count * sgn(ani.rotate_method), 0, 1, 0);
			for_each(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			break;
		
		case U:
		case Ui:
			for_noup(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			glRotatef(ani.frame_count * sgn(ani.rotate_method), 0, 1, 0);
			for_up(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			break;
		
		case D:
		case Di:
			for_nodown(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			glRotatef(ani.frame_count * sgn(ani.rotate_method), 0, 1, 0);
			for_down(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			break;
		
		case Z:
		case Zi:
			glRotatef(ani.frame_count * sgn(ani.rotate_method), 0, 0, 1);
			for_each(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			break;
		
		case F:
		case Fi:
			for_nofront(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			glRotatef(ani.frame_count * sgn(ani.rotate_method), 0, 0, 1);
			for_front(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			break;
		
		case B:
		case Bi:
			for_noback(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			glRotatef(ani.frame_count * sgn(ani.rotate_method), 0, 0, 1);
			for_back(x, y, z) drawBlock(cube->getBlockPtr(x, y, z)->getFaceColor(), x, y, z);
			break;
		
		default:
			break;
		}
	}
	
	void loadOperation(const ROTATE_METHOD *s)
	{
		operation = s;
	}
}