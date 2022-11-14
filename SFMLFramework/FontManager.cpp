#include "Helpers.h"
#include "FontManager.h"

// Constructor
FontManager::FontManager()
{
	// Adds all the fonts to m_fontsToName
	addFontsToMap();
}

// Destructor
FontManager::~FontManager()
{
}

//-----------------------------------------------------
// Function		: loadFont
// Purpose		: To load a font from a given filename
// Parameters	: const char* fileName
// Returns		: sf::Font
// Notes		:
// See also		:
//-----------------------------------------------------
sf::Font FontManager::loadFont( const char* fileName )
{
	// Temporary font variable
	sf::Font fontToLoad;

	// Loads the font from the file and stores the result
	bool loaded = fontToLoad.loadFromFile( fileName );

	// Makes sure loaded is true, stops running the program if it isn't
	ASSERT( loaded );

	// Returns the font
	return fontToLoad;
}

//-----------------------------------------------------
// Function		: addFontsToMap
// Purpose		: To add all the loaded fonts and their corresponding name to m_fontsToName
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void FontManager::addFontsToMap()
{
	// Reads file that contains a list of all fonts used in the game and then loads each font that is listed into m_fontsToName
	for( auto it : readFileAsMap( "assets/fontList.txt" ) )
	{
		m_fontsToName[it.first] = loadFont( it.second.c_str() );
	}
}

//-----------------------------------------------------
// Function		: getFont
// Purpose		: To return the font that coresponds to the given name
// Parameters	: std::string fileName
// Returns		: sf::Font&
// Notes		:
// See also		:
//-----------------------------------------------------
sf::Font& FontManager::getFont( std::string name )
{
	return m_fontsToName[name];
}