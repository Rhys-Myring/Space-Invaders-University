#include "MouseManager.h"

// Constructor
MouseManager::MouseManager()
	: m_previousState( false )
	, m_currentState( false )
{
}

// Destructor
MouseManager::~MouseManager()
{

}

//-----------------------------------------------------
// Function		: checkIfClicked
// Purpose		: Returns whether the mouse was just clicked on this frame
// Parameters	: None
// Returns		: bool
// Notes		: 
// See also		:
//-----------------------------------------------------
bool MouseManager::checkIfClicked()
{
	return m_currentState && !m_previousState;
}

//-----------------------------------------------------
// Function		: updateMouseState
// Purpose		: To update the states of the mouse tracked by the MouseManager
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void MouseManager::updateMouseState()
{
	// Sets the previous state to the current state from the last frame
	m_previousState = m_currentState;

	// Sets current state to whether the left mouse button has been pressed
	m_currentState = sf::Mouse::isButtonPressed( sf::Mouse::Left );
}