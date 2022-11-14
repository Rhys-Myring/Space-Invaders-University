#include "Invader.h"
#include "InvaderFormationManager.h"
#include "Settings.h"

// Constructor
InvaderFormationManager::InvaderFormationManager()
	// Sets invader array pointer to null
	: m_pInvaderArray( nullptr )

	// Sets minimum and maximum column values to the default
	, m_minInvaderColumn( k_minimumColumn )
	, m_maxInvaderColumn( k_maximumColumn )
{
}

// Destructor
InvaderFormationManager::~InvaderFormationManager()
{
}

// Getter and Setter
void InvaderFormationManager::setInvaderArray( Invader* pInvaderArray )
{
	m_pInvaderArray = pInvaderArray;
}

const Invader* InvaderFormationManager::getInvaderArray() const
{
	return m_pInvaderArray;
}

//-----------------------------------------------------
// Function		: reset
// Purpose		: To reset the minimum and maximum column variables at the start of a new level
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void InvaderFormationManager::reset()
{
	// Resets minimum and maximum column variables
	m_minInvaderColumn = k_minimumColumn;
	m_maxInvaderColumn = k_maximumColumn;
}

//-----------------------------------------------------
// Function		: checkCurrentFormation
// Purpose		: To adjust the minimum and maximum positions of the different invaders based on which 
//				  invaders are still alive
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void InvaderFormationManager::checkCurrentFormation()
{
	// Variables to track how many invaders from a certain column are dead
	int invadersDeadLeft = 0;
	int invadersDeadRight = 0;

	// Iterates through the far left and right columns of invaders and checks if they're still alive
	for( int i = 0; i < k_invaderRows; i++ )
	{
		// If invader in far left column is dead then "invadersDeadLeft" increases by 1
		if( !m_pInvaderArray[i * k_invaderColumns + m_minInvaderColumn].getActiveState() )
		{
			invadersDeadLeft++;
		}

		// If invader in far right column is dead then "invadersDeadRight" increases by 1
		if( !m_pInvaderArray[i * k_invaderColumns + m_maxInvaderColumn].getActiveState() )
		{
			invadersDeadRight++;
		}
	}

	// If all invaders in the far left column are dead, the minimum column increases by 1
	// All invaders that are still alive have their minimum positions decreased so that the formation still 
	// goes all the way to the left side of the screen
	if( invadersDeadLeft == k_invaderRows )
	{
		m_minInvaderColumn++;

		// Iterates through all of the invaders and decreases their minimum position so they move all the way to the
		// left hand side of the screen
		for( int i = 0; i < k_maxNumberOfInvaders; i++ )
		{
			m_pInvaderArray[i].setMinXPosition( m_pInvaderArray[i].getMinXPosition() - k_invaderSpacing );
		}
	}

	// If all invaders in the far right column are dead, the maximum column decreases by 1
	// All invaders that are still alive have their maximum positions increased so that the formation still 
	// goes all the way to the right side of the screen
	if( invadersDeadRight == k_invaderRows )
	{
		m_maxInvaderColumn--;

		// Iterates through all of the invaders and increases their maximum position so they move all the way to the
		// right hand side of the screen
		for( int i = 0; i < k_maxNumberOfInvaders; i++ )
		{
			m_pInvaderArray[i].setMaxXPosition( m_pInvaderArray[i].getMaxXPosition() + k_invaderSpacing );
		}
	}
}