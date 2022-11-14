#ifndef GAMETEXT_H
#define GAMETEXT_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

//-----------------------------------------------------
// Class	:	GameText
// Purpose	:	To create a text object with the ability to centre the origin
// Usage	:	GameText gameText;
//				gameText.setOriginToCentre();
// See also	:	sf::Text
//-----------------------------------------------------
class GameText : public sf::Text
{
private:

public:
	// Constructor
	GameText();

	// Destructor
	~GameText();

	// Sets the object's origin to the centre of its string of text
	void setOriginToCentre();
};

#endif // !GAMETEXT_H
