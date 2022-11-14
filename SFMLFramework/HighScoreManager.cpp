#include "Helpers.h"
#include "HighScoreManager.h"
#include "Settings.h"

// Constructor
HighScoreManager::HighScoreManager()
	: m_numberOfHighScores( 0 )
	, m_haveScoresChanged( false )
{
	// Reads highscores from text file, stores them in m_scores and their names in m_names
	readScores();
}

// Destructor
HighScoreManager::~HighScoreManager()
{
	// If there has been a change to the highscore table then the changes are written to the file
	if( m_haveScoresChanged )
	{
		// Writes all the high scores to the high scores file
		writeScores();
	}
}

// Getters
const std::string& HighScoreManager::getName( int index ) const
{
	return m_names[index];
}

const int HighScoreManager::getScore( int index ) const
{
	return m_scores[index];
}

const int HighScoreManager::getNumberOfHighScores() const
{
	return m_numberOfHighScores;
}

//-----------------------------------------------------
// Function		: checkScore
// Purpose		: To check if a given score can go on the leaderboard
// Parameters	: int score
// Returns		: bool
// Notes		: Checks whether the given score is in the top 5 scores
// See also		:
//-----------------------------------------------------
bool HighScoreManager::checkScore( int score )
{
	// Returns false if the score isn't larger than 0
	if( score > 0 )
	{
		// If the maximum number of scores on the high score table hasn't been reached then true is returned
		if( m_numberOfHighScores < k_maxNumberOfHighScores )
		{
			return true;
		}

		// If the maximum number of stored scores has been reached then it returns whether the current score 
		// is larger than the lowest score currently on the high score table
		return score > m_scores[m_numberOfHighScores - 1];
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------
// Function		: checkName
// Purpose		: To check if a given name is unique
// Parameters	: std::string& name
// Returns		: bool
// Notes		: 
// See also		:
//-----------------------------------------------------
bool HighScoreManager::checkName( std::string& name )
{
	// Checks each stored score to see if the name already exists on the leaderboard
	for( int i = 0; i < m_numberOfHighScores; i++ )
	{
		if( m_names[i] == name )
		{
			// Returns false if the name exists
			return false;
		}
	}

	// Returns true if it doesn't already exist
	return true;
}

//-----------------------------------------------------
// Function		: addScore
// Purpose		: To add a given score to the leaderboard
// Parameters	: std::string& name, int score
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void HighScoreManager::addScore( std::string& name, int score )
{
	// If the high score table is full then the lowest score is overwritten
	if( m_numberOfHighScores >= k_maxNumberOfHighScores )
	{
		m_names[m_numberOfHighScores - 1] = name;
		m_scores[m_numberOfHighScores - 1] = score;
	}
	// If there is still space then the additional score is added
	else
	{
		m_names.push_back( name );
		m_scores.push_back( score );

		// Increases the number of saved high scores as a new one has just been added
		m_numberOfHighScores++;
	}

	// Sorts the scores from highest to lowest
	sortScores();

	// Sets scores have changed to true
	m_haveScoresChanged = true;
}

//-----------------------------------------------------
// Function		: sortScores
// Purpose		: To sort the high scores from highest to lowest
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void HighScoreManager::sortScores()
{
	// If there is more than 1 highscore score saved
	if( m_numberOfHighScores > 1 )
	{
		// Variables to track whether the scores are in the correct order
		bool sorted = false;
		int valuesSorted = 0;
		int elementsToCheck = m_numberOfHighScores - 1;

		// Sorts the scores and their corresponding names (bubble sort)
		while( !sorted )
		{
			valuesSorted = 0;

			// Goes through all elements in the scores vector and compares them to see if they need swapping
			for( int i = 0; i < elementsToCheck; i++ )
			{
				// If the current element is smaller than the next element then they are swapped
				if( m_scores[i] < m_scores[i + 1] )
				{
					// Swaps the scores and their corresponding names
					swap( m_scores[i], m_scores[i + 1] );
					swap( m_names[i], m_names[i + 1] );
				}
				else
				{
					valuesSorted++;
				}
			}

			// If all values are in the correct place, set sorted to true and stop checking
			sorted = ( valuesSorted == elementsToCheck );
		}
	}
}

//-----------------------------------------------------
// Function		: readScores
// Purpose		: To read all of the high scores from the highscores text file
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void HighScoreManager::readScores()
{
	// Puts all the names and scores into their respective vectors
	for( auto it : readFileAsMap( "highScores.txt" ) )
	{
		m_names.push_back( it.first );

		// Code to convert string to int found here https://stackoverflow.com/questions/7663709/how-can-i-convert-a-stdstring-to-int
		m_scores.push_back( std::stoi( it.second ) );

		// Increases number of highscores
		m_numberOfHighScores++;
	}

	// Sorts the high scores from highest to lowest
	sortScores();	
}

//-----------------------------------------------------
// Function		: writeScores
// Purpose		: To write all the highscores to the highscores text file
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void HighScoreManager::writeScores()
{
	// Only writes the scores if there are any high scores to write
	if( m_numberOfHighScores )
	{
		// Variable to store the map file that is to be written 
		std::map<std::string, std::string> mapToWrite;

		// Adds each score and name to the map file
		for( int i = 0; i < m_numberOfHighScores; i++ )
		{
			mapToWrite[m_names[i]] = convertIntToString( m_scores[i] );
		}

		// Writes the high scores to the high scores file
		writeMapToFile( "highScores.txt", mapToWrite );
	}
}
