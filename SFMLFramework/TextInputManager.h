#ifndef TEXTINPUTMANAGER_H
#define TEXTINPUTMANAGER_H

#include <SFML/Window/Keyboard.hpp>

//-----------------------------------------------------
// Class	:	TextInputManager
// Purpose	:	To track text input from the keyboard 
// Usage	:	TextInputManager textInputManager;
//				textInputManager.getInputtedChar();
// See also	:	
//-----------------------------------------------------
class TextInputManager
{
private:
	char m_charInputted;		// Stores the last character inputted by the Player
	bool m_hasKeyBeenPressed;	// Stores whether the player has just pressed a key
	bool m_isWaitingForInput;	// Stores whether the game is waiting for the Player to enter text or not

public:
	// Constructor
	TextInputManager();

	// Destructor
	~TextInputManager();

	// Getters and Setters
	const char getInputtedChar() const;
	void setInputtedChar( char inputtedChar );

	const bool getWaitingForInput() const;
	void setWaitingForInput( bool isWaitingForInput );

	const bool getHasKeyBeenPressed() const;
	void setHasKeyBeenPressed( bool hasKeyBeenInputted );
};

#endif // !TEXTINPUTMANAGER_H