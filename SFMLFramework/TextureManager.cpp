#include "Helpers.h"
#include "TextureManager.h"

// Constructor
TextureManager::TextureManager()
{
	// Adds all the textures to m_texturesToName
	addTexturesToMap();
}

// Destructor
TextureManager::~TextureManager()
{
}

//-----------------------------------------------------
// Function		: loadTexture
// Purpose		: To load a texture from a given filename
// Parameters	: const char* fileName
// Returns		: sf::Texture
// Notes		:
// See also		:
//-----------------------------------------------------
sf::Texture TextureManager::loadTexture( const char* fileName )
{
	// Temporary texture variable
	sf::Texture textureBeingLoaded;

	// Loads the texture from the file and stores the result
	bool loaded = textureBeingLoaded.loadFromFile( fileName );

	// Makes sure loaded is true, stops running the program if it isn't
	ASSERT( loaded );

	// Returns the texture
	return textureBeingLoaded;
}

//-----------------------------------------------------
// Function		: addTexturesToMap
// Purpose		: To add all the loaded textures and their corresponding name to m_texturesToName
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void TextureManager::addTexturesToMap()
{
	// Reads file that contains a list of all textures used in the game and then loads each texture that is listed into m_texturesToName
	for( auto it : readFileAsMap( "assets/textureList.txt" ) )
	{
		m_texturesToName[it.first] = loadTexture( it.second.c_str() );
	}
}

//-----------------------------------------------------
// Function		: getTexture
// Purpose		: To return the texture that coresponds to the given name
// Parameters	: std::string fileName
// Returns		: sf::Texture&
// Notes		:
// See also		:
//-----------------------------------------------------
sf::Texture& TextureManager::getTexture( std::string name )
{
	return m_texturesToName[name];
}