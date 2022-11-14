#include "ScoreManager.h"

// Constructor
ScoreManager::ScoreManager()
	: m_playerScore( 0 )
{
}

// Destructor
ScoreManager::~ScoreManager()
{
}

//-----------------------------------------------------
// Function		: increaseScore
// Purpose		: To increase the player's score by a given amount
// Parameters	: int score
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void ScoreManager::increaseScore( int score )
{
	m_playerScore += score;
}

// Getter and Setter
int ScoreManager::getScore()
{
	return m_playerScore;
}

void ScoreManager::setScore( int score )
{
	m_playerScore = score;
}
