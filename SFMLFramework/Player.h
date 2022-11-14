#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedGameSprite.h"

// Forward class declaration to avoid including another header file
namespace sf
{
	class Sound;
	class SoundBuffer;
}
class Bullet;

//-----------------------------------------------------
// Class	:	Player
// Purpose	:	To control a player object
// Usage	:	Player player;
//				player.update( deltaTime )
// See also	:	AnimatedGameSprite
//-----------------------------------------------------
class Player : public AnimatedGameSprite
{
private:
	Bullet*		m_pBullet;				// Stores Player's bullet object
	Animation*  m_pDeathAnimation;		// Stores Player's death animation
	sf::Sound*	m_pDeathSound;			// Stores Player's death sound
	sf::Sound*  m_pShootingSound;		// Stores Player's shooting sound
	float		m_velocity;				// Stores Player's velocity

	// Takes input from the user and moves the player accordingly
	void checkInputs( float deltaTime );

public:
	// Constructor
	Player();

	// Destructor
	~Player();

	// Getters and Setters
	const Bullet* getBullet() const;
	void setBullet( Bullet* bullet );

	// Sets the player's death sound to a given sound effect
	void setDeathSound( sf::SoundBuffer& sound );

	// Sets the player's shooting sound to a given sound effect
	void setShootingSound( sf::SoundBuffer& sound );

	// Sets the player's sound effect volume
	void setSoundEffectVolume( float volume );

	// Plays the player death sound
	void playDeathSound();

	// Plays the player death animation
	void playDeathAnimation();

	// Resets the values in a player object to their defaults
	void reset();

	// Update function
	virtual void update( float deltaTime ) override;	
};

#endif // !PLAYER_H