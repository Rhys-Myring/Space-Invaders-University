#include "GameSprite.h"
#include "Helpers.h"

// Constructor
GameSprite::GameSprite()
	: m_isActive( true )
{
}

// Destructor
GameSprite::~GameSprite()
{

}

// Getter and Setter
const bool GameSprite::getActiveState() const
{
	return m_isActive;
}

void GameSprite::setActiveState( bool active )
{
	m_isActive = active;
}

//-----------------------------------------------------
// Function		: setCentredTexture
// Purpose		: To set the sprite's texture to the texture passed into the function and then set the origin 
//				  of the sprite to the centre of the new texture
// Parameters	: sf::Texture& texture
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void GameSprite::setCentredTexture( sf::Texture& texture )
{
	// Sets the sprite texture to the texture passed through the parameter
	setTexture( texture );
		
	// Gets the size of the texture
	sf::Vector2u textureSize = texture.getSize();

	// Sets origin to the centre of the texture
	setOrigin( static_cast<float>( getTextureRect().width / 2 ), static_cast<float>( getTextureRect().height / 2 ) );
}

//-----------------------------------------------------
// Function		: setCentredTextureRect
// Purpose		: To set the sprite's texture Rectangle and set the origin to the centre based on the new size
// Parameters	: const sf::Rect<int>& textureRect
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void GameSprite::setCentredTextureRect( const sf::Rect<int>& textureRect )
{
	// Sets texture rect
	setTextureRect( textureRect );

	// Sets origin to the centre of the texture
	setOrigin( static_cast<float>( textureRect.width / 2 ), static_cast<float>( textureRect.height / 2 ) );
}

//-----------------------------------------------------
// Function		: moveClampedX
// Purpose		: To translate the object by a given velocity on the y-axis but clamp it between some given values
// Parameters	: float velocity, float minClampedValue, float maxClampedValue
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void GameSprite::moveClampedX( float velocity, float minClampedValue, float maxClampedValue )
{
	// Calculates the new position
	float newPos = getPosition().x + velocity;

	// Checks if the new position goes past the minimum value
	if( newPos < minClampedValue )
	{
		// Sets the position to the minimum value
		newPos = minClampedValue;
	}
	// Checks if the new position goes past the maximum value
	else if( newPos > maxClampedValue )
	{
		// Sets the position to the maximum value
		newPos = maxClampedValue;
	}

	// Sets the objects position to the new position
	setPosition( newPos, getPosition().y );
}

//-----------------------------------------------------
// Function		: moveClampedY
// Purpose		: To translate the object by a given velocity on the y-axis but clamp it between some given values
// Parameters	: float velocity, float minClampedValue, float maxClampedValue
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void GameSprite::moveClampedY( float velocity, float minClampedValue, float maxClampedValue )
{
	// Calculates the new position
	float newPos = getPosition().y + velocity;

	// Checks if the new position goes past the minimum value
	if( newPos < minClampedValue )
	{
		// Sets the position to the minimum value
		newPos = minClampedValue;
	}
	// Checks if the new position goes past the maximum value
	else if( newPos > maxClampedValue )
	{
		// Sets the position to the maximum value
		newPos = maxClampedValue;
	}

	// Sets the objects position to the new position
	setPosition( getPosition().x, newPos );
}

//-----------------------------------------------------
// Function		: update
// Purpose		: To update a GameSprite object
// Parameters	: float deltaTime
// Returns		: void
// Notes		: Virtual function with empty body so it can be overriden in a child class
// See also		:
//-----------------------------------------------------
void GameSprite::update( float deltaTime )
{
}
