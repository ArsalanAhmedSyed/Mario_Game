//#include "Collisions.h"
//#include "Character.h"
//
////Initialise the instance to nullptr
//Collisions* Collisions::m_instance = nullptr;
//
//Collisions::Collisions(){}
//
//Collisions::~Collisions() { m_instance = nullptr; }
//
//Collisions* Collisions::Instance()
//{
//	if (!m_instance)
//	{
//		m_instance = new Collisions;
//	}
//
//	return m_instance;
//}
//
//bool Circle(Character* character1, Character* character2)
//{
//	Vector2D vec = Vector2D((character1->getPosition().x - character2->getPosition().x), (character1->getPosition().y, character2->getPosition().x));
//
//	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));
//
//	double combined_distance = (character1->GetCollisionRaidus() + character2->GetCollisionRaidus());
//
//	return distance < combined_distance;
//}
//bool Box(Rect2D rect1, Rect2D rect2)
//{
//
//}
