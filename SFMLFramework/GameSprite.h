#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

//-----------------------------------------------------
// Class	:	GameSprite
// Purpose	:	To create a sprite with a centred texture, clamped movement functions,
//				an active state and an update function
// Usage	:	GameSprite gameSprite;
//				gameSprite.setCentredTexture( "player" );
// See also	:	sf::Sprite
//-----------------------------------------------------
class GameSprite : public sf::Sprite
{
private:
	bool m_isActive; // Stores whether the GameSprite is active

public:
	// Constructor
	GameSprite();

	// Destructor
	~GameSprite();

	// Getter and Setter
	const bool getActiveState() const;
	void setActiveState( bool active );

	// Sets the sprite's texture to the texture passed into the function and then sets the origin of the sprite 
	// to the centre of the new texture		  
	void setCentredTexture( sf::Texture& texture );

	// Sets the sprite's texture Rectangle and sets the origin to the centre based on the new size	  
	void setCentredTextureRect( const sf::Rect<int>& textureRect );

	// Translates the object by a given velocity on the x-axis but clamps it between some given values
	void moveClampedX( float velocity, float minClampedValue, float maxClampedValue );

	// Translates the object by a given velocity on the y-axis but clamps it between some given values
	void moveClampedY( float velocity, float minClampedValue, float maxClampedValue );

	// Virtual update function
	virtual void update( float deltaTime );
};

#endif // !GAMESPRITE_H
