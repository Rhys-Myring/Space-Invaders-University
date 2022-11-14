#include "CollisionDetector.h"

// Constructor
CollisionDetector::CollisionDetector()
{
}

// Destructor
CollisionDetector::~CollisionDetector()
{

}

//-----------------------------------------------------
// Function		: checkIfCollided
// Purpose		: To check whether 2 given objects have collided
// Parameters	: const sf::Rect<float>& hitBox1, const sf::Rect<float>& hitBox2
// Returns		: bool
// Notes		:
// See also		:
//-----------------------------------------------------
bool CollisionDetector::checkIfCollided( const sf::Rect<float>& hitBox1, const sf::Rect<float>& hitBox2 )
{
	return hitBox1.intersects( hitBox2 );
}

//-----------------------------------------------------
// Function		: checkIfCollided
// Purpose		: To check whether 2 given objects have collided
// Parameters	: const sf::Rect<float>& hitBox1, const sf::Vector2f position2
// Returns		: bool
// Notes		: Override for using an object that doesn't have bounds
// See also		:
//-----------------------------------------------------
bool CollisionDetector::checkIfCollided( const sf::Rect<float>& hitBox1, const sf::Vector2f position2 )
{
	return hitBox1.contains( position2 );
}

