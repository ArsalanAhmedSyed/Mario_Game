#ifndef _COLLISIONS_H
#define _COLLISIONS_H

#include "Commons.h"

class Character;

class Collisions
{
public:
	~Collisions();

	static Collisions* Instance();

	bool Circle(Circle2D object1, Circle2D object2);
	bool Box(Rect2D rect1, Rect2D rect2);
	bool Hit(Rect2D player, Rect2D enemy);

private:
	Collisions();
	static Collisions* m_instance;
};

#endif // !_COLLISIONS_H


