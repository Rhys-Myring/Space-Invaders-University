#include "Animation.h"
#include "Helpers.h"
#include "Settings.h"

// Constructor
Animation::Animation( int numberOfFrames, float framesPerSecond, int startingXPos, int startingYPos, int frameWidth, int frameHeight )
	: m_pFrames( nullptr )
	, m_framesPerSecond( framesPerSecond )
	, m_frameWidth( frameWidth )
	, m_frameHeight( frameHeight )
	, m_numberOfFrames( numberOfFrames )
	, m_startingXPos( startingXPos )
	, m_startingYPos( startingYPos )
{
	// Sets the m_pFrames to a new array of m_numberOfFrames sf::Rects 
	m_pFrames = new sf::IntRect[ m_numberOfFrames ];

	// Iterates through all the frames and sets their coordinates based on the values passed into the constructor
	for( int i = 0; i < m_numberOfFrames; i++ )
	{
		m_pFrames[i].left = m_startingXPos + i * ( frameWidth + k_imageSpacing );
		m_pFrames[i].top = m_startingYPos;
		m_pFrames[i].width = m_frameWidth;
		m_pFrames[i].height = m_frameHeight;
	}
}

// Destructor
Animation::~Animation()
{
	// Deletes m_pFrames to avoid a memory leak
	safeDeleteArray( m_pFrames );
}

// Getters and Setters
const sf::IntRect& Animation::getAnimationFrame( int frameIndex ) const
{
	return m_pFrames[frameIndex];
}

void Animation::setAnimationFrame( int frameIndex, sf::IntRect& frame )
{
	m_pFrames[frameIndex] = frame;
}

const int Animation::getNumberOfFrames() const
{
	return m_numberOfFrames;
}

const float Animation::getFramesPerSecond() const
{
	return m_framesPerSecond;
}
