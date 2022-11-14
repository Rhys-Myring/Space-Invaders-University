#include "GameText.h"

// Constructor
GameText::GameText()
{
}

// Destructor
GameText::~GameText()
{
}

//-----------------------------------------------------
// Function		: setOriginToCentre
// Purpose		: To set the object's origin to the centre of its string of text
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void GameText::setOriginToCentre()
{
	// Sets origin to the centre of the string
	// Takes away the left and top values because text objects don't have their rectangle origins at 0,0
	setOrigin( ( getGlobalBounds().width / 2 ) - getLocalBounds().left, ( getGlobalBounds().height / 2 ) - getLocalBounds().top );
}
