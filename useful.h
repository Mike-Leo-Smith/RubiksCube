//
// Created by mike on 16-10-25.
//

#ifndef _USEFUL_H_
#define _USEFUL_H_

#define for_right(x, y, z)    for (int x = 1, y = -1; y <= 1; y++)    for (int z = -1; z <= 1; z++)
#define for_left(x, y, z)   for (int x = -1, y = -1; y <= 1; y++)   for (int z = -1; z <= 1; z++)
#define for_up(x, y, z)     for (int y = 1, x = -1; x <= 1; x++)    for (int z = -1; z <= 1; z++)
#define for_down(x, y, z)   for (int y = -1, x = -1; x <= 1; x++)   for (int z = -1; z <= 1; z++)
#define for_front(x, y, z)  for (int x = -1; x <= 1; x++)           for (int y = -1, z = 1; y <= 1; y++)
#define for_back(x, y, z)   for (int x = -1; x <= 1; x++)           for (int y = -1, z = -1; y <= 1; y++)

#define for_noright(x, y, z)    for (int x = -1; x <= 0; x++)   for (int y = -1; y <= 1; y++)   for (int z = -1; z <= 1; z++)
#define for_noleft(x, y, z)     for (int x = 0; x <= 1; x++)    for (int y = -1; y <= 1; y++)   for (int z = -1; z <= 1; z++)
#define for_noup(x, y, z)       for (int x = -1; x <= 1; x++)   for (int y = -1; y <= 0; y++)   for (int z = -1; z <= 1; z++)
#define for_nodown(x, y, z)     for (int x = -1; x <= 1; x++)   for (int y = 0; y <= 1; y++)    for (int z = -1; z <= 1; z++)
#define for_nofront(x, y, z)    for (int x = -1; x <= 1; x++)   for (int y = -1; y <= 1; y++)   for (int z = -1; z <= 0; z++)
#define for_noback(x, y, z)     for (int x = -1; x <= 1; x++)   for (int y = -1; y <= 1; y++)   for (int z = 0; z <= 1; z++)
#define for_each(x, y, z)       for (int x = -1; x <= 1; x++)   for (int y = -1; y <= 1; y++)   for (int z = -1; z <= 1; z++)

#define for_edge(x, y, z)    for_each(x, y, z)    if (abs(x) == 1 && abs(y) == 1 && z == 0 || abs(y) == 1 && abs(z) == 1 && x == 0 || abs(z) == 1 && abs(x) == 1 && y == 0)
#define for_corner(x, y, z)    for (int x = -1; x <= 1; x += 2)    for (int y = -1; y <= 1; y += 2)    for (int z = -1; z <= 1; z += 2)

namespace RubiksCube
{
	template<typename T> inline T abs(const T &x)
	{
		return T(x >= 0 ? x : -x);
	}
	
	template<typename T> inline int sgn(const T &x)
	{
		return x == 0 ? 0 : (x > 0 ? 1 : -1);
	}
	
	template<typename T> inline void shift4(T &x1, T &x2, T &x3, T &x4, bool isCCW)
	{
		T tmp;
		isCCW ? (tmp = x4, x4 = x3, x3 = x2, x2 = x1, x1 = tmp) : (tmp = x1, x1 = x2, x2 = x3, x3 = x4, x4 = tmp);
	}
}

#endif 	// _USEFUL_H_