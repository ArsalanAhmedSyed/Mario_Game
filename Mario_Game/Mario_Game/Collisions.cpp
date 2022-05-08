#include "Collisions.h"
#include "Character.h"

//Initialise the instance to nullptr
Collisions* Collisions::m_instance = nullptr;

Collisions::Collisions(){}

Collisions::~Collisions() { m_instance = nullptr; }

Collisions* Collisions::Instance()
{
	//check if its set up
	if (!m_instance)
	{
		//set the instance to the collisions
		m_instance = new Collisions;
	}

	return m_instance;
}

bool Collisions::Circle(Circle2D object1, Circle2D object2)
{
	Vector2D vec = Vector2D((object1.x - object2.x), (object1.y - object2.y));

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	double combined_distance = (object1.radius + object2.radius);

	return distance < combined_distance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if (rect1.x + (rect1.width / 2) > rect2.x && rect1.x + (rect1.width / 2) < rect2.x + rect2.width
		&& rect1.y +(rect1.height/2) > rect2.y && rect1.y + (rect1.height/2) < rect2.y + rect2.height)
	{
		return true;
	}

	return false; 
}

bool Collisions::Hit(Rect2D player, Rect2D enemy)
{
	if (player.x + (player.width / 2) > enemy.x && player.x + (player.width / 2) < enemy.x + enemy.width
		&& player.y + (player.height) > enemy.y && player.y + (player.height) < enemy.y + enemy.height)
	{
		return true;
	}

	return false;
}
