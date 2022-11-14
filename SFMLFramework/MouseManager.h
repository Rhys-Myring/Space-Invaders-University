#ifndef MOUSEMANAGER_H
#define MOUSEMANAGER_H

#include <SFML/Window/Mouse.hpp>

//-----------------------------------------------------
// Class	:	MouseManager
// Purpose	:	To track whether the mouse has been clicked or not
// Usage	:	MouseManager mouseManager;
//				mouseManager.checkIfClicked();
// See also	:	
//-----------------------------------------------------
class MouseManager
{
private:
	bool m_previousState; // Stores the state of the left mouse button on the previous frame
	bool m_currentState;  // Stores the state of the left mouse button on the current frame

public:
	// Constructor
	MouseManager();

	// Destructor
	~MouseManager();

	// Gets whether the mouse has just been clicked or not
	bool checkIfClicked();

	// Updates the values that track the state of the mouse
	void updateMouseState();
};

#endif // !MOUSEMANAGER_H