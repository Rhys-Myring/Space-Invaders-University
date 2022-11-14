#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SFML/Graphics/Font.hpp>
#include <map>

//-----------------------------------------------------
// Class	:	FontManager
// Purpose	:	To store all the fonts used by the game
// Usage	:	FontManager fontManager;
//				fontManager.getFont( "name" )
// See also	:	
//-----------------------------------------------------
class FontManager
{
private:
	std::map<std::string, sf::Font> m_fontsToName; // Stores all the fonts and their corresponding names

	// Loads a font from a given filename
	sf::Font loadFont( const char* fileName );

	// Adds all the fonts to the map
	void addFontsToMap();

public:
	// Constructor
	FontManager();

	// Destructor
	~FontManager();

	// Returns the font that coresponds to the given name
	sf::Font& getFont( std::string name );
};

#endif // !FONTMANAGER_H