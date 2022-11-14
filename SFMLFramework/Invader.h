#ifndef INVADER_H
#define INVADER_H

#include "AnimatedGameSprite.h"

// Forward class declarations to avoid including header files
namespace sf
{
	class Sound;
	class SoundBuffer;
}
class Animation;
class EnemyBullet;
enum class InvaderStates;

//-----------------------------------------------------
// Class	:	Invader
// Purpose	:	To control an invader object
// Usage	:	Invader invader;
//				invader.update( deltaTime );
// See also	:	AnimatedGameSprite
//-----------------------------------------------------
class Invader : public AnimatedGameSprite
{
private:
	EnemyBullet*	m_pBullet;					// Stores the Invader's bullet object
	InvaderStates*	m_pCurrentState;			// Stores the Invader's current state
	Animation*		m_pDeathAnimation;			// Stores the Invader's death animation
	sf::Sound*		m_pDeathSound;				// Stores the Invader's death sound
	Animation*		m_pDefaultAnimation;		// Stores the Invader's default animation
	bool			m_isMovingHorizontally;		// Stores whether the Invader is moving horizontally
	float			m_maxXPos;					// Stores the maximum X position the Invader can have
	float			m_minXPos;					// Stores the minimum X position the Invader can have
	int				m_movementDirection;		// Stores whether the invader is moving left or right
	float			m_movementSpeed;			// Stores the Invader's speed
	float			m_nextYPos;					// Stores the Y position of the row below the Invader
	float			m_returnXPos;				// Stores the X position that the Invader must return to after diving
	float			m_returnYPos;				// Stores the Y position that the Invader must return to after diving
	int				m_score;					// Stores the score that this Invader gives when killed
	sf::Sound*		m_pShootingSound;			// Stores the Invader's shooting sound

	// Sets the default values for the invader that can't be set in the initaliser list
	void setDefaultValues();

	// Calculates the position that the Invader will return to after diving at the player
	void calculateReturnPosition( float deltaTime );

	// Moves the invader across the screen to the edge, makes it go downwards and then turn around
	void moveInFormation( float deltaTime );

	// Returns whether the invader is within the min and max bounds, if it reaches either of these it returns true
	bool checkIfAtEdge();

	// Shoots a bullet down the screen towards the player 
	void shootAtPlayer();

public:
	// Constructor
	Invader();

	// Destructor
	~Invader();

	// Getters and Setters
	const EnemyBullet* getBullet() const;
	void setBullet( EnemyBullet* bullet );

	const float getMaxXPosition() const;
	void setMaxXPosition( float maxPosition );

	const float getMinXPosition() const;
	void setMinXPosition( float minPosition );

	const float getNextYPosition() const;
	void setNextYPosition( float yPosition );

	const int getScore() const;
	void setScore( int score );

	const int getMovementDirection() const;
	void setMovementDirection( int direction );

	const float getSpeed() const;
	void setSpeed( float speed );

	const InvaderStates& getCurrentState() const;
	void setCurrentState( InvaderStates& newState );

	// Sets the invader's death sound to a given sound effect
	void setDeathSound( sf::SoundBuffer& sound );

	// Sets the invader's shooting sound to a given sound effect
	void setShootingSound( sf::SoundBuffer& sound );

	// Sets the invader's sound effect volume
	void setSoundEffectVolume( float volume );

	// Kills the invader
	void kill();

	// Resets the invader's values to their defaults
	void reset();

	// Update function
	virtual void update( float deltaTime ) override;
};


#endif // !INVADER_H
