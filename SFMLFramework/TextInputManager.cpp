#include "TextInputManager.h"

// Constructor
TextInputManager::TextInputManager()
	: m_charInputted( false )
	, m_hasKeyBeenPressed( false )
	, m_isWaitingForInput( false )
{
}

// Destructor
TextInputManager::~TextInputManager()
{

}

// Getters and Setters
const char TextInputManager::getInputtedChar() const
{
	return m_charInputted;
}

void TextInputManager::setInputtedChar( char inputtedChar )
{
	m_charInputted = inputtedChar;
}

const bool TextInputManager::getWaitingForInput() const
{
	return m_isWaitingForInput;
}

void TextInputManager::setWaitingForInput( bool isWaitingForInput )
{
	m_isWaitingForInput = isWaitingForInput;
}

const bool TextInputManager::getHasKeyBeenPressed() const
{
	return m_hasKeyBeenPressed;
}

void TextInputManager::setHasKeyBeenPressed( bool hasKeyBeenInputted )
{
	m_hasKeyBeenPressed = hasKeyBeenInputted;
}
