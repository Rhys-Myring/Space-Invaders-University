#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics/Rect.hpp>

//-----------------------------------------------------
// Class	:	Animation
// Purpose	:	To store all of the texture rectangles for each frame of an animation
// Usage	:	Animation animation;
//				animation.getAnimationFrame();
// See also	:	
//-----------------------------------------------------
class Animation
{
private:
	sf::IntRect*	m_pFrames;			// Stores the texture rects of each frame of the animation 
	float			m_framesPerSecond;	// Stores the framerate of the animation
	int				m_frameHeight;		// Stores the height of each frame
	int				m_frameWidth;		// Stores the width of each frame
	int				m_numberOfFrames;	// Stores the number of frames the animation has
	int				m_startingXPos;		// Stores the starting X coordinate of the first frame of the animation
	int				m_startingYPos;		// Stores the starting Y coordinate of the first frame of the animation

public:
	// Constructor
	Animation( int numberOfFrames = 0, float framesPerSecond = 0.0f, int startingXPos = 0, int startingYPos = 0, int frameWidth = 0, int frameHeight = 0 );

	// Destructor
	~Animation();

	// Getters and Setters
	const sf::IntRect& getAnimationFrame( int frameIndex ) const;
	void setAnimationFrame( int frameIndex, sf::IntRect& frame );
	const int getNumberOfFrames() const;	
	const float getFramesPerSecond() const;
};

#endif // !ANIMATION_H