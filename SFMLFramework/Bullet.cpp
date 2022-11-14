#include "Bullet.h"
#include "Settings.h"

// Constructor
Bullet::Bullet()
	:  m_speed( -k_bulletSpeed )
{
	setActiveState( false );
}

// Destructor
Bullet::~Bullet()
{
}

// Getters and Setters
const float Bullet::getSpeed() const
{
	return m_speed;
}

void Bullet::setSpeed( float newSpeed )
{
	m_speed = newSpeed;
}

//-----------------------------------------------------
// Function		: update
// Purpose		: To update a bullet object
// Parameters	: float deltaTime
// Returns		: void
// Notes		: Overidden function
// See also		:
//-----------------------------------------------------
void Bullet::update( float deltaTime )
{
	// If the bullet is active it moves up or down the screen until it goes off the screen
	if( getActiveState() )
	{
		// Moves vertically
		move( 0.0f, m_speed * deltaTime );

		// If the bullet goes off the screen it is set to inactive
		if( !( ( getPosition().y > k_bulletRespawnTop ) && ( getPosition().y < k_bulletRespawnBottom ) ) )
		{
			setActiveState( false );
		}
	}
}
