#ifndef ANIMATEDGAMESPRITE_H
#define ANIMATEDGAMESPRITE_H

#include "GameSprite.h"

// Forward Class Declaration
class Animation;

//-----------------------------------------------------
// Class	:	AnimatedGameSprite
// Purpose	:	To create a GameSprite with the ability to play animations
// Usage	:	AnimatedGameSprite animatedGameSprite;
//				animatedGameSprite.updateAnimation( deltaTime );
// See also	:	GameSprite
//-----------------------------------------------------
class AnimatedGameSprite : public GameSprite
{
private:
	Animation*  m_pCurrentAnimation;			// Stores the currently active animation
	int			m_pCurrentAnimationLastFrame;	// Stores the index of the last frame of the currently active animation
	bool		m_isAnimationLooped;			// Stores whether the animation currently being played is looped
	bool		m_isAnimationPlaying;			// Stores whether the currently active animation is being played
	float		m_timeInAnimation;				// Stores the amount of time the animation being played has been played for

	// Cycles through the frames of the animation currently being pointed to by m_pCurrentAnimation
	void playCurrentAnimation( float DeltaTime );

public:
	// Constructor
	AnimatedGameSprite();

	// Destructor
	~AnimatedGameSprite();

	// Getters and Setters
	void setCurrentAnimation( Animation& animation );
	bool getIsAnimationPlaying();
	void setLooped( bool looped );

	// Sets animation playing to true
	void playAnimation();
	void playAnimation( Animation& newAnimation );

	// Sets animation playing to false
	void stopAnimation();

	// Plays any currently active animation for an AnimatedGameSprite object
	virtual void updateAnimation( float deltaTime );

	// Virtual update function
	virtual void update( float deltaTime );
};

#endif // !ANIMATEDGAMESPRITE_H
