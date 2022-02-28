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

bool Collisions::Circle(Character* character1, Character* character2)
{
	Vector2D vec = Vector2D((character1->getPosition().x - character2->getPosition().x), (character1->getPosition().y - character2->getPosition().y));

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	double combined_distance = (character1->GetCollisionRaidus() + character2->GetCollisionRaidus());

	return distance < combined_distance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if (rect1.x + (rect1.width / 2) > rect2.x && rect1.x + (rect1.width / 2) < rect2.x + rect2.width
		&& rect1.y +(rect1.height/2) > rect2.y && rect1.y + (rect2.height/2) < rect2.y + rect2.height)
	{
		return true;
	}

	return false; 
}
