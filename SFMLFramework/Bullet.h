#ifndef BULLET_H
#define BULLET_H

#include "GameSprite.h"

//-----------------------------------------------------
// Class	:	Bullet
// Purpose	:	To manage a bullet object
// Usage	:	Bullet bullet;
//				bullet.update( deltaTime );
// See also	:	GameSprite
//-----------------------------------------------------
class Bullet : public GameSprite
{
private:
	float m_speed; // Stores the speed the bullet travels at

public:
	// Constructor
	Bullet();

	// Destructor
	~Bullet();

	// Getters and setters
	const float getSpeed() const;
	void setSpeed( float newSpeed );

	// Update function
	virtual void update( float deltaTime ) override;
};

#endif  // !BULLET_H