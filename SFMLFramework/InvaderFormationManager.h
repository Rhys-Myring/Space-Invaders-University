#ifndef INVADERFORMATIONMANAGER_H
#define INVADERFORMATIONMANAGER_H

// Forward class declaration
class Invader;

//-----------------------------------------------------
// Class	:	InvaderFormationManager
// Purpose	:	To manage the formation of all the Invader objects
// Usage	:	InvaderFormationManager invaderFormationManager;
//				invaderFormationManager.checkCurrentFormation();
// See also	:	Invader
//-----------------------------------------------------
class InvaderFormationManager
{
private:
	int		 m_minInvaderColumn;	// Stores the index of the far left column of Invaders
	int		 m_maxInvaderColumn;	// Stores the index of the far right column of Invaders
	Invader* m_pInvaderArray;		// Points to the array of Invader objects

public:
	// Constructor
	InvaderFormationManager();

	// Destructor
	~InvaderFormationManager();

	// Getter and Setter
	void setInvaderArray( Invader* pInvaderArray );
	const Invader* getInvaderArray() const;

	// Resets min and max column variables
	void reset();

	// Adjusts the minimum and maximum positions of the different invaders based on which invaders are still alive
	void checkCurrentFormation();
};

#endif // !INVADERFORMATIONMANAGER_H
