#include "AnimatedGameSprite.h"
#include "Animation.h"

// Constructor
AnimatedGameSprite::AnimatedGameSprite()
	: m_pCurrentAnimation( nullptr )
	, m_pCurrentAnimationLastFrame( 0 )
	, m_isAnimationLooped( false )
	, m_isAnimationPlaying( false )
	, m_timeInAnimation( 0.0f )
{
}

// Destructor
AnimatedGameSprite::~AnimatedGameSprite()
{
}

// Getters and Setters
void AnimatedGameSprite::setCurrentAnimation( Animation& animation )
{
	m_pCurrentAnimation = &animation;
	m_pCurrentAnimationLastFrame = m_pCurrentAnimation->getNumberOfFrames() - 1;
}

bool AnimatedGameSprite::getIsAnimationPlaying()
{
	return m_isAnimationPlaying;
}

void AnimatedGameSprite::setLooped( bool looped )
{
	m_isAnimationLooped = looped;
}

//-----------------------------------------------------
// Function		: playCurrentAnimation
// Purpose		: To cycle through the frames of the animation currently being pointed to by m_pCurrentAnimation
// Parameters	: float deltaTime
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void AnimatedGameSprite::playCurrentAnimation( float deltaTime )
{
	if( m_pCurrentAnimation )
	{
		// Calcuates the current position within the animation cycle 
		m_timeInAnimation += deltaTime * m_pCurrentAnimation->getFramesPerSecond();

		// Sets the current frame based on the position within the animation cycle
		int currentFrame = static_cast<int>( m_timeInAnimation );
		currentFrame %= m_pCurrentAnimation->getNumberOfFrames();

		// Sets sprite's texture rect to the current frame of the animation
		setCentredTextureRect( m_pCurrentAnimation->getAnimationFrame( currentFrame ) );
	}
}

//-----------------------------------------------------
// Function		: playAnimation
// Purpose		: To set animation playing to true
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void AnimatedGameSprite::playAnimation()
{
	m_isAnimationLooped = false;
	m_isAnimationPlaying = true;

	// Resets time in animation
	m_timeInAnimation = 0.0f;
}

//-----------------------------------------------------
// Function		: playAnimation
// Purpose		: To set a new current animation and set playing to true
// Parameters	: Animation& newAnimation
// Returns		: void
// Notes		: Override to set the current animation and immediately start playing it
// See also		:
//-----------------------------------------------------
void AnimatedGameSprite::playAnimation( Animation& newAnimation )
{
	setCurrentAnimation( newAnimation );
	playAnimation();
}

//-----------------------------------------------------
// Function		: stopAnimation
// Purpose		: To set animation playing and animation looping to false
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void AnimatedGameSprite::stopAnimation()
{
	m_isAnimationLooped = false;
	m_isAnimationPlaying = false;
}

//-----------------------------------------------------
// Function		: updateAnimation
// Purpose		: To play any currently active animation for an AnimatedGameSprite object
// Parameters	: float deltaTime
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void AnimatedGameSprite::updateAnimation( float deltaTime )
{
	// If the animation is set to be playing
	if( m_isAnimationPlaying )
	{
		// Plays the current animation
		playCurrentAnimation( deltaTime );

		// If the animation has reached the end, sets the animation to not playing
		if( !m_isAnimationLooped && getTextureRect() == m_pCurrentAnimation->getAnimationFrame( m_pCurrentAnimationLastFrame ) )
		{
			stopAnimation();
		}
	}
}

//-----------------------------------------------------
// Function		: update
// Purpose		: To update an AnimatedGameSprite object
// Parameters	: float deltaTime
// Returns		: void
// Notes		: Virtual function with empty body so it can be overriden in a child class
// See also		:
//-----------------------------------------------------
void AnimatedGameSprite::update( float deltaTime )
{
}