#include <iostream>
#include <SFML/Audio/Sound.hpp>

#include "Animation.h"
#include "EnemyBullet.h"
#include "Helpers.h"
#include "Invader.h"
#include "InvaderStates.h"
#include "Settings.h"

// Constructor
Invader::Invader()
	: m_pBullet( nullptr )
	, m_pCurrentState( nullptr )
	, m_pDeathAnimation( nullptr )
	, m_pDefaultAnimation( nullptr )
	, m_pDeathSound( nullptr )
	, m_pShootingSound( nullptr )
	, m_isMovingHorizontally( true )
	, m_movementSpeed( k_minInvaderSpeed )
	, m_maxXPos( k_maxBoundaryPosition )
	, m_minXPos( k_minBoundaryPosition )
	, m_movementDirection( k_initialInvaderMovementDirection )
	, m_nextYPos( k_invaderStartingYPos + k_invaderYStep )
	, m_returnXPos( 0.0f )
	, m_returnYPos( 0.0f )
	, m_score( k_invaderScore )
{
	// Sets the current Invader state pointer to a new Invader state object
	m_pCurrentState = new InvaderStates( InvaderStates::Formation );

	// Sets death sound to a new instance of sf::Sound
	m_pDeathSound = new sf::Sound();

	// Sets shooting sound to a new instance of sf::Sound
	m_pShootingSound = new sf::Sound();

	// Creates default animation
	m_pDefaultAnimation = new Animation( k_numberInvaderAnimationOfFrames, k_invaderDefaultAnimFramesPerSecond, 
		k_invaderStartingFrameXPos, k_invaderDefaultAnimStartingFrameYPos, k_invaderFrameWidth, k_invaderFrameHeight );

	// Creates death animation
	m_pDeathAnimation = new Animation( k_numberInvaderAnimationOfFrames, k_invaderDeathAnimFramesPerSecond,
		k_invaderStartingFrameXPos, k_invaderDeathAnimStartingFrameYPos, k_invaderFrameWidth, k_invaderFrameHeight );

}

// Destructor
Invader::~Invader()
{
	// Deletes m_pBullet to avoid memory leak
	safeDelete( m_pBullet );
	
	// Deletes m_pCurrentState to avoid memory leak
	safeDelete( m_pCurrentState );

	// Deletes m_pDeathAnimation to avoid memory leak
	safeDelete( m_pDeathAnimation );

	// Deletes m_pDeathSound to avoid memory leak
	safeDelete( m_pDeathSound );

	// Deletes m_pDefaultAnimation to avoid memory leak
	safeDelete( m_pDefaultAnimation );

	// Deletes m_pShootingSound to avoid memory leak
	safeDelete( m_pShootingSound );
}

// Getters and Setters
const EnemyBullet* Invader::getBullet() const
{
	return m_pBullet;
}

void Invader::setBullet( EnemyBullet* bullet )
{
	m_pBullet = bullet;
}

const float Invader::getMaxXPosition() const
{
	return m_maxXPos;
}

void Invader::setMaxXPosition( float maxPosition )
{
	m_maxXPos = maxPosition;
}

const float Invader::getMinXPosition() const
{
	return m_minXPos;
}

void Invader::setMinXPosition( float minPosition )
{
	m_minXPos = minPosition;
}

const float Invader::getNextYPosition() const
{
	return m_nextYPos;
}

void Invader::setNextYPosition( float yPosition )
{
	m_nextYPos = yPosition;
}

const int Invader::getScore() const
{
	return m_score;
}

void Invader::setScore( int score )
{
	m_score = score;
}

const int Invader::getMovementDirection() const
{
	return m_movementDirection;
}

void Invader::setMovementDirection( int direction )
{
	m_movementDirection = direction;
}

const float Invader::getSpeed() const
{
	return m_movementSpeed;
}

void Invader::setSpeed( float speed )
{
	m_movementSpeed = speed;
}

const InvaderStates& Invader::getCurrentState() const
{
	return *m_pCurrentState;
}

void Invader::setCurrentState( InvaderStates& newState )
{
	m_pCurrentState = &newState;
}

//-----------------------------------------------------
// Function		: setDeathSound
// Purpose		: To set the invader's death sound to a given sound effect
// Parameters	: sf::SoundBuffer& sound
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void Invader::setDeathSound( sf::SoundBuffer& sound )
{
	m_pDeathSound->setBuffer( sound );
}

//-----------------------------------------------------
// Function		: setShootingSound
// Purpose		: To set the invader's shooting sound to a given sound effect
// Parameters	: sf::SoundBuffer& sound
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void Invader::setShootingSound( sf::SoundBuffer& sound )
{
	m_pShootingSound->setBuffer( sound );
}

//-----------------------------------------------------
// Function		: setSoundEffectVolume
// Purpose		: To set the invader's sound effect volume
// Parameters	: float volume
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void Invader::setSoundEffectVolume( float volume )
{
	m_pDeathSound->setVolume( volume );
	m_pShootingSound->setVolume( volume );
}

//-----------------------------------------------------
// Function		: setDefaultValues
// Purpose		: To set the default values for the invader that can't be set in the initialiser list
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void Invader::setDefaultValues()
{
	// Sets intial texture rect so the invaders start with the first frame of their animation
	setCentredTextureRect( m_pDefaultAnimation->getAnimationFrame( 0 ) );

	// Sets the current animation to the default
	setCurrentAnimation( *m_pDefaultAnimation );

	// Plays default invader animation
	playAnimation();

	// Loops the default animation
	setLooped( true );
}

//-----------------------------------------------------
// Function		: calculateReturnPosition
// Purpose		: To calculate the position that the Invader will return to after diving
// Parameters	: float deltaTime
// Returns		: void
// Notes		: Replicates the movement of the invaders that are still in formation so that this invader can 
//				  return to the correct position when it has finished diving
// See also		:
//-----------------------------------------------------
void Invader::calculateReturnPosition( float deltaTime )
{
	if( m_isMovingHorizontally )
	{
		// Calculates invader's returning x position
		m_returnXPos += m_movementSpeed * m_movementDirection * deltaTime;

		// If calculated X pos is at the edge, the direction is flipped
		if( m_returnXPos >= m_maxXPos || m_returnXPos <= m_minXPos )
		{
			// Swaps the movement direction
			m_movementDirection *= -1;

			// Sets horizontal movement to false
			m_isMovingHorizontally = false;

			// Clamps calculated X value between minimum and maximum values
			if( m_returnXPos < m_minXPos )
			{
				// Sets the x value to the minimum value
				m_returnXPos = m_minXPos;
			}
			else if( m_returnXPos > m_maxXPos )
			{
				// Sets the x value to the maximum value
				m_returnXPos = m_maxXPos;
			}
		}
	}
	else
	{
		// Calculates invader's returning y position
		m_returnYPos += m_movementSpeed * deltaTime;

		// Checks if the calculated position has gone past the maximum value
		if( m_returnYPos >= m_nextYPos )
		{
			// Sets the calculated position to the maximum value
			m_returnYPos = m_nextYPos;

			// Once calculated y position has got to the maximum it starts calculating horizontally again
			m_isMovingHorizontally = true;

			// Sets next y position
			m_nextYPos += k_invaderYStep;
		}
	}
}

//-----------------------------------------------------
// Function		: moveInFormation
// Purpose		: To move the invader across the screen to the edge, make it go downwards and then turn around
// Parameters	: float deltaTime
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void Invader::moveInFormation( float deltaTime )
{
	if( m_isMovingHorizontally )
	{
		// Moves invader horizontally
		moveClampedX( m_movementSpeed * m_movementDirection * deltaTime, m_minXPos, m_maxXPos );

		if( checkIfAtEdge() )
		{
			// Swaps the movement direction
			m_movementDirection *= -1;

			// Sets horizontal movement to false
			m_isMovingHorizontally = false;
		}
	}
	else
	{
		// Moves invader vertically
		moveClampedY( m_movementSpeed * deltaTime, k_invaderStartingYPos, m_nextYPos );

		// Once invader has got to its new y position it starts moving horizontally again
		if( getPosition().y == m_nextYPos )
		{
			m_isMovingHorizontally = true;

			// Sets next y position
			m_nextYPos += k_invaderYStep;
		}
	}	
}

//-----------------------------------------------------
// Function		: checkIfAtEdge
// Purpose		: To return whether the invader is within the min and max bounds, if it reaches either of these it 
//				  returns true
// Parameters	: float deltaTime
// Returns		: bool
// Notes		:
// See also		:
//-----------------------------------------------------
bool Invader::checkIfAtEdge()
{
	// Returns whether invader is at the edge of the screen
	return getPosition().x >= m_maxXPos || getPosition().x <= m_minXPos;	
}

//-----------------------------------------------------
// Function		: shootAtPlayer
// Purpose		: To shoot a bullet down the screen towards the player 
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Invader::shootAtPlayer()
{
	// If bullet is inactive
	if( !m_pBullet->getActiveState() )
	{
		// Sets bullet position to the invader's current position
		m_pBullet->setPosition( getPosition().x, getPosition().y );

		// Sets bullet to active
		m_pBullet->setActiveState( true );

		// Plays shooting sound
		m_pShootingSound->play();
	}
}

//-----------------------------------------------------
// Function		: kill
// Purpose		: To kill the invader
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Invader::kill()
{
	// Plays death animation
	playAnimation( *m_pDeathAnimation );

	// Plays death sound
	m_pDeathSound->play();

	// Sets invader's state to dead
	*m_pCurrentState = InvaderStates::Dead;
}

//-----------------------------------------------------
// Function		: reset
// Purpose		: To reset the values in an invader object to default
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void Invader::reset()
{
	// Sets object to active
	setActiveState( true );

	// Sets the current state to the default
	*m_pCurrentState = InvaderStates::Formation;

	// Sets movement direction to right
	m_movementDirection = k_initialInvaderMovementDirection;
	 
	// Sets moving horizontally to true
	m_isMovingHorizontally = true;
	
	// Sets texture and animation default values
	setDefaultValues();
}

//-----------------------------------------------------
// Function		: update
// Purpose		: To update an invader object
// Parameters	: float deltaTime
// Returns		: void
// Notes		: Overidden function
// See also		:
//-----------------------------------------------------
void Invader::update( float deltaTime )
{
	// If invader is active update
	if( getActiveState() )
	{
		switch( *m_pCurrentState )
		{
			// If the current state is Formation
			case InvaderStates::Formation:
			{
				// Moves the invader in it's formation pattern
				moveInFormation( deltaTime );

				// Generates a random number to decide whether the invader will shoot or not
				// If it's less than the chance of the invader shooting, it shoots
				if( generateRandom() <= k_invaderChanceOfShooting )
				{
					// Shoots at the player
					shootAtPlayer();
				}

				// Generates a random number to decide whether the invader will dive or not
				// If it's less than the chance of the invader diving, it changes to the diving state
				if( generateRandom() <= k_invaderChanceOfDiving )
				{
					// Sets the return position to the current position
					m_returnXPos = getPosition().x;
					m_returnYPos = getPosition().y;

					// Sets state to diving
					*m_pCurrentState = InvaderStates::Diving;
				}
				break;
			}

			// If the current state is Dead
			case InvaderStates::Dead:
			{
				// If Invader is dead and the death animation is finished then set invader to inactive
				if( !getIsAnimationPlaying() )
				{
					setActiveState( false );
				}
				break;
			}

			// If the current state is Diving
			case InvaderStates::Diving:
			{
				// Dives Down towards the player
				moveClampedY( m_movementSpeed * deltaTime, k_invaderStartingYPos, k_windowHeight );

				// Keeps track of their position in the formation
				calculateReturnPosition( deltaTime );

				// Starts to return to formation once they have exited the screen
				if( getPosition().y == k_windowHeight )
				{
					// Sets position high so invader comes from the top of the screen
					setPosition( m_returnXPos, k_invaderEnterHeight );

					// Sets state to returning to formation
					*m_pCurrentState = InvaderStates::ReturningToPosition;
				}

				break;
			}

			// If the current state is Returning to position
			case InvaderStates::ReturningToPosition:
			{
				// Keeps track of their position in the formation
				calculateReturnPosition( deltaTime );

				// Moves back towards the position it should be in the formation
				moveClampedX( m_movementSpeed * deltaTime, k_minInvaderPosition, m_returnXPos );
				moveClampedY( m_movementSpeed * deltaTime, k_invaderEnterHeight, m_returnYPos );

				// Returns to formation state once it has returned to its position
				if( getPosition().x == m_returnXPos && getPosition().y == m_returnYPos )
				{
					// Sets state to formation
					*m_pCurrentState = InvaderStates::Formation;
				}

				break;
			}

			// Default in case there is a bug that causes an invalid value to be stored in the current invader state
			default:
			{
				std::cout << "ERROR, Unexpected Value In m_pCurrentState";
				break;
			}
		}

		// Plays the current animation (if it is set to play)
		updateAnimation( deltaTime );
	}
}