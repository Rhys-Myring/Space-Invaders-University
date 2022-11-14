#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include <string>
#include <vector>

//-----------------------------------------------------
// Class	:	HighScoreManager
// Purpose	:	To manage the player's high scores
// Usage	:	HighScoreManager highScoreManager;
//				highScoreManager.checkScore( score )
// See also	:	
//-----------------------------------------------------
class HighScoreManager
{
private:
	bool m_haveScoresChanged;			// Stores whether there has been any changes to the high scores
	int m_numberOfHighScores;			// Stores the number of saved high scores
	std::vector<int> m_scores;			// Stores the numerical score of all the high scores
	std::vector<std::string> m_names;	// Stores the names of all the high scores

	// Sorts the high scores from highest to lowest
	void sortScores();

	// Read all of the high scores from the highscores text file
	void readScores();

	// Writes all the highscores to the highscores text file
	void writeScores();

public:
	// Constructor
	HighScoreManager();

	// Destructor
	~HighScoreManager();

	// Getters
	const std::string& getName( int index ) const;
	const int getScore( int index ) const;
	const int getNumberOfHighScores() const;

	// Checks if a given score can go on the leaderboard
	bool checkScore( int score );

	// Checks if a given name is unique
	bool checkName( std::string& name );

	// Adds a given score to the leaderboard
	void addScore( std::string& name, int score );
};

#endif // !HIGHSCOREMANAGER_H
