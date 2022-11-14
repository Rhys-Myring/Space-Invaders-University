#include <SFML/Audio/Sound.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Animation.h"
#include "Bullet.h"
#include "Helpers.h"
#include "Player.h"
#include "Settings.h"

// Constructor
Player::Player()
	: m_velocity( 0.0f )
	, m_pBullet( nullptr )
	, m_pDeathAnimation( nullptr )
	, m_pDeathSound( nullptr )
	, m_pShootingSound( nullptr )
{
	// Sets player's position to the starting position
	setPosition( k_playerStartingXPos, k_playerStartingYPos );

	// Sets death sound to a new instance of sf::Sound
	m_pDeathSound = new sf::Sound();

	// Sets shooting sound to a new instance of sf::Sound
	m_pShootingSound = new sf::Sound();

	// Creates death animation
	m_pDeathAnimation = new Animation( k_numberPlayerAnimationOfFrames, k_playerDeathAnimFramesPerSecond, 
		k_playerStartingFrameXPos, k_playerStartingFrameYPos, k_playerFrameWidth, k_playerFrameHeight );

	// Sets intial texture rect so the player starts with the first frame of their animation
	setCentredTextureRect( m_pDeathAnimation->getAnimationFrame( 0 ) );
}

// Destructor
Player::~Player()
{
	// Deletes m_pBullet to avoid memory leak
	safeDelete( m_pBullet );

	// Deletes m_pDeathAnimation to avoid memory leak
	safeDelete( m_pDeathAnimation );

	// Deletes m_pDeathSound to avoid memory leak
	safeDelete( m_pDeathSound );

	// Deletes m_pShootingSound to avoid memory leak
	safeDelete( m_pShootingSound );
}

// Getter and Setter
const Bullet* Player::getBullet() const
{
	return m_pBullet;
}

void Player::setBullet( Bullet* bullet )
{
	m_pBullet = bullet;
}

//-----------------------------------------------------
// Function		: setDeathSound
// Purpose		: To set the player's death sound to a given sound effect
// Parameters	: sf::SoundBuffer& sound
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void Player::setDeathSound( sf::SoundBuffer& sound )
{
	m_pDeathSound->setBuffer( sound );
}

//-----------------------------------------------------
// Function		: setShootingSound
// Purpose		: To set the player's shooting sound to a given sound effect
// Parameters	: sf::SoundBuffer& sound
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void Player::setShootingSound( sf::SoundBuffer& sound )
{
	m_pShootingSound->setBuffer( sound );

}

//-----------------------------------------------------
// Function		: setSoundEffectVolume
// Purpose		: To set the player's sound effect volume
// Parameters	: float volume
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void Player::setSoundEffectVolume( float volume )
{
	m_pDeathSound->setVolume( volume );
	m_pShootingSound->setVolume( volume );
}

//-----------------------------------------------------
// Function		: playDeathSound
// Purpose		: To play the player death sound
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void Player::playDeathSound()
{
	m_pDeathSound->play();
}

//-----------------------------------------------------
// Function		: playDeathSound
// Purpose		: To play the player death animation
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void Player::playDeathAnimation()
{
	playAnimation( *m_pDeathAnimation );
}

//-----------------------------------------------------
// Function		: reset
// Purpose		: To reset the values in a player object to default
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void Player::reset()
{
	// Sets player back to their starting postion
	setPosition( k_playerStartingXPos, k_playerStartingYPos );

	// Sets velocity back to 0 so the player doesn't continue to move after being reset
	m_velocity = 0.0f;

	// Sets intial texture rect so the player starts with the first frame of their animation
	setCentredTextureRect( m_pDeathAnimation->getAnimationFrame( 0 ) );
}

//-----------------------------------------------------
// Function		: checkInputs
// Purpose		: To take input from the user and move the player accordingly
// Parameters	: float deltaTime
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Player::checkInputs( float deltaTime )
{
	// If both the direction keys are pressed the player doesn't move
	if( ( ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) || ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) )
	&&  ( ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ) || ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ) ) )
	{
		// Sets velocity to 0 if both directions are pressed
		m_velocity = 0.0f;
	}

	// If either the left arrow key or A key is pressed move left
	else if( (sf::Keyboard::isKeyPressed( sf::Keyboard::Left )) || (sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ))
	{
		// Sets velocity to -k_playerSpeed * deltaTime speed so that the Player will move left
		m_velocity = -k_playerSpeed * deltaTime;
	}

	// If either the right arrow key or D key is pressed move right
	else if( ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) || ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) )
	{
		// Sets velocity to k_playerSpeed * deltaTime speed so that the Player will move right
		m_velocity = k_playerSpeed * deltaTime;
	}

	// If neither directions are pressed the velocity is damped
	else
	{
		// Damps velocity so that the ship has a feeling a weight to it
		m_velocity *= k_playerDamping;

		// If magnitude of damped velocity is approaching 0 it is set to 0
		if( abs( m_velocity ) <= 0.001f )
		{
			m_velocity = 0.0f;
		}
	}

	// Moves player in based on their velocity
	moveClampedX( m_velocity, k_minBoundaryPosition, k_maxBoundaryPosition );

	// If the space bar is pressed fires a bullet
	if( ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) ) && ! ( m_pBullet->getActiveState() ) )
	{
		// Sets bullet to active
		m_pBullet->setActiveState( true );

		// Fires bullet
		m_pBullet->setPosition( getPosition() );

		// Plays firing sound
		m_pShootingSound->play();
	}
}

//-----------------------------------------------------
// Function		: update
// Purpose		: To update a player object
// Parameters	: float deltaTime
// Returns		: void
// Notes		: Overidden function
// See also		:
//-----------------------------------------------------
void Player::update( float deltaTime )
{
	// Takes in user input and controls player accordingly
	checkInputs( deltaTime );

	// Plays the current animation (if it is set to play)
	updateAnimation( deltaTime );
}