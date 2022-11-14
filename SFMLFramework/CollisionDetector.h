#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include <SFML/Graphics/Rect.hpp>

//-----------------------------------------------------
// Class	:	CollisionDetector
// Purpose	:	To check whether there has been a collision between objects
// Usage	:	CollisionDetector collisionDetector;
//				collisionDetector.checkIfCollided( hitBox1, hitBox2 );
// See also	:	sf::Rect
//-----------------------------------------------------
class CollisionDetector
{
private:

public:
	// Constructor
	CollisionDetector();

	// Destructor
	~CollisionDetector();

	// Checks if 2 given objects have collided
	bool checkIfCollided( const sf::Rect<float>& hitBox1, const sf::Rect<float>& hitBox2 );
	bool checkIfCollided( const sf::Rect<float>& hitBox1, const sf::Vector2f position2 );
};

#endif // !COLLISIONDETECTOR_H
