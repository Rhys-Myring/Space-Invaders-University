#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <map>

//-----------------------------------------------------
// Class	:	TextureManager
// Purpose	:	To store all the textures used by the game
// Usage	:	TextureManager textureManager;
//				textureManager.getTexture( "name" )
// See also	:	
//-----------------------------------------------------
class TextureManager
{
private:
	std::map<std::string, sf::Texture> m_texturesToName; // Stores all the textures and their corresponding names

	// Loads a texture from a given filename
	sf::Texture loadTexture( const char* fileName );

	// Adds all the textures to the map
	void addTexturesToMap();

public:
	// Constructor
	TextureManager();

	// Destructor
	~TextureManager();

	// Returns the texture that coresponds to the given name
	sf::Texture& getTexture( std::string name );
};

#endif // !TEXTUREMANAGER_H