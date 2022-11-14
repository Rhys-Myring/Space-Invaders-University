#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

//-----------------------------------------------------
// Class	:	ScoreManager
// Purpose	:	To manage the player's score
// Usage	:	ScoreManager scoreManager;
//				scoreManager.increaseScore( score )
// See also	:	
//-----------------------------------------------------
class ScoreManager
{
private:
	int m_playerScore;	// Stores the Player's score

public:
	// Constructor
	ScoreManager();

	// Destructor
	~ScoreManager();

	// Increases the player's score by a given amount
	void increaseScore( int score );

	// Getter and Setter
	int getScore();
	void setScore( int score );
};

#endif // !SCOREMANAGER_H
