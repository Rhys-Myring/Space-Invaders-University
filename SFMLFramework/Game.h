#ifndef GAME_H
#define GAME_H

#include <vector>

// Forward class declarations to avoid including header files
namespace sf
{
	class Clock;
	class RenderWindow;
	class Sound;
	class Sprite;
}
class Bullet;
class CollisionDetector;
class ConfigSettingsManager;
class FontManager;
class GameSprite;
class GameText;
class HighScoreManager;
class Invader;
class InvaderFormationManager;
class MouseManager;
class Player;
class ScoreManager;
class SoundManager;
class TextInputManager;
class TextureManager;
enum class GameStates;
enum class MenuScreens;

//-----------------------------------------------------
// Class	:	Game
// Purpose	:	To manage all windows and objects within the game
// Usage	:	Game game;
//				game.run();
// See also	:	
//-----------------------------------------------------
class Game
{
private:
	std::vector<Bullet*>	 m_bullets;						// All bullets used by the Player and Invaders
	sf::Clock*				 m_pClock;						// Clock to calculate delta time
	CollisionDetector*		 m_pCollisionDetector;			// Checks whether 2 objects have collided
	ConfigSettingsManager*	 m_pConfigSettingsManager;		// Stores all the configuration settings made by the Player
	GameStates*				 m_pCurrentGameState;			// Stores the current Game State
	int						 m_currentLevel;				// Stores the current Level Number
	MenuScreens*			 m_pCurrentMenuScreen;			// Stores the current Menu Screen
	FontManager*			 m_pFontManager;				// Manages all fonts used in the game
	GameText*				 m_pFullScreenButton;			// Text/Button that makes the game full screen/windowed
	sf::Sprite*				 m_pGameBackground;				// Background sprite during gameplay
	GameSprite*				 m_pGameLogo;					// Logo sprite
	sf::Sound*				 m_pGameMusic;					// Music played during Gameplay
	GameText*				 m_pGameOverText;				// Text displayed when the Player gets a Game Over
	HighScoreManager*		 m_pHighScoreManager;			// Manages all the player's highscores
	GameText*				 m_pInfoText;					// Text displaying different information to the Player depending on which menu they are in
	Invader*				 m_pInvaders;					// All the Invader objects used in the game
	InvaderFormationManager* m_pInvaderFormationManager;	// Makes sure the Invaders stay in formation
	GameText*				 m_pInvalidText;				// Text telling the player that the name they entered is invalid
	GameText*				 m_pMainMenuButtons;			// Text/Buttons that are displayed when the Player is in the Main Menu
	sf::Sprite*				 m_pMenuBackground;				// Menu background sprite
	sf::Sound*				 m_pMenuMusic;					// Music played when the Player is in the Menu
	MouseManager*			 m_pMouseManager;				// Tracks whether the mouse has been clicked or not
	GameText*				 m_pMuteButton;					// Text/Button that mutes/unmutes the sound
	GameText*				 m_pNameText;					// Text displaying the player's name as they type it in
	GameText*				 m_pLeaderBoardText;			// Text displaying all the high scores on the leaderboard
	GameText*				 m_pLevelText;					// Text displaying the current level during Gameplay
	int						 m_lives;						// Stores the number of Player Lives
	GameText*				 m_pLivesText;					// Text displaying the number of lives during Gameplay
	Player*					 m_pPlayer;						// The Player object
	GameText*				 m_pReturnToMainMenuButton;		// Text/Button that takes the Player from one menu back to the Main Menu
	ScoreManager*			 m_pScoreManager;				// Controls the Player's score
	GameText*				 m_pScoreText;					// Text displaying the score during Gameplay
	SoundManager*			 m_pSoundManager;				// Manages all sounds used in the game
	GameText*				 m_pSubmitButton;				// Text/Button that when clicked adds the Player's name to the leaderboard and then takes them back to the Main Menu
	TextInputManager*		 m_pTextInputManager;			// Manages the input of any text from the keyboard
	TextureManager*			 m_pTextureManager;				// Manages all textures used in the game
	float					 m_timeInCurrentState;			// Stores how long the current game state has been active
	sf::RenderWindow*		 m_pWindow;						// The window where all of the game is rendered

	// Deals with all the window events and stops the window from freezing
	void handleWindowEvents();

	// Deletes all pointers to avoid memory leaks
	void deleteAllPointers();

	// Intialises all the game objects
	void initialise();

	// Intialises the configuration settings object
	void initialiseConfigSettingsManager();

	// Intialises the window object
	void initialiseWindow();

	// Intialises the TextureManager object
	void initialiseTextureManager();

	// Intialises the SoundManager object
	void initialiseSoundManager();

	// Intialises the FontManager object
	void initialiseFontManager();

	// Intialises the HighScoreManager object
	void initialiseHighScoreManager();

	// Initialises the in game background
	void initialiseGameBackground();

	// Initialises the menu background
	void initialiseMenuBackground();

	// Intialises the bullet objects
	void initialiseBullets();

	// Intialises the player object
	void initialisePlayer();

	// Intialises the invader objects
	void initialiseInvaders();

	// Intialises the Invader Formation Manager object
	void initialiseInvaderFormationManager();

	// Intialises the score manager object
	void initialiseScoreManager();

	// Intialises the Collision Detector object
	void initialiseCollisionDetector();

	// Intialises the main menu button objects
	void initialiseMainMenuButtons();

	// Intialises the game over text object
	void initialiseGameOverText();

	// Intialises the level text object
	void initialiseLevelText();
	
	// Intialises the lives text object
	void initialiseLivesText();

	// Intialises the score text object
	void initialiseScoreText();

	// Intialises the leaderboard text objects
	void initialiseLeaderBoardText();

	// Intialises the return to main menu button
	void initialiseReturnToMainMenuButton();

	// Intialises the mute button
	void initialiseMuteButton();

	// Intialises the full screen button
	void initialiseFullScreenButton();

	// Intialises the name text object
	void initialiseNameText();

	// Intialises the information text object
	void initialiseInfoText();

	// Intialises the invalid text object
	void initialiseInvalidText();

	// Intialises the submit button
	void initialiseSubmitButton();

	// Intialises the game logo object
	void initialiseGameLogo();

	// Intialises the Menu Music object
	void initialiseMenuMusic();
	
	// Intialises the Game Music object
	void initialiseGameMusic();

	// Intialises the Current Game State object
	void initialiseGameState();

	// Intialises the Current Menu Screen object
	void initialiseMenuScreen();

	// Intialises the Mouse Manager object
	void initialiseMouseManager();

	// Intialises the Text Input Manager object
	void initialiseTextInputManager();

	// Intialises the Clock object
	void initialiseClock();

	// Intialises the Volume level
	void initialiseVolume();

	// Set the invaders to their starting positions
	void setInvaderPositions();

	// Starts the next level
	void startNextLevel();

	// Calculates new invader speed for the new level
	float calculateInvaderSpeed();

	// Resets the game at the start of a new game
	void resetGame();

	// Resets the invaders at the start of a new level
	void resetInvaders();

	// Sets all bullets to inactive at the end of a level or when the player has died
	void deactivateBullets();

	// Checks whether the invader has been hit by the bullet or not
	void checkIfInvaderHit();

	// Checks whether any of the invaders have got low enough to make the player lose
	bool checkIfInvadersTooLow();

	// Checks whether the player has been hit by any enemy bullets or diving invaders
	bool checkIfPlayerHit();

	// Checks whether all of the invaders have been killed or not
	bool checkIfAllInvadersDead();

	// Decreases the player's lives and sets the state to player dead
	void playerHit();

	// Sets the current game state to the passed in state
	void changeState( GameStates newState );

	// Carries out specific actions when entering a given state
	void onStateEnter( GameStates newState );

	// Carries out specific actions when exiting the current state
	void onStateExit();

	// Sets the current menu screen state to the passed in menu screen
	void changeMenuScreen( MenuScreens newScreen );

	// Carries out specific actions when entering a given menu screen
	void onMenuScreenEnter( MenuScreens newScreen );

	// Carries out specific actions when exiting the current menu screen 
	void onMenuScreenExit();

	// Checks whether the return to main menu button has been clicked or not
	void checkIfReturnToMenuIsClicked();

	// Returns whether the mouse is hovering over a given button
	bool isHoveringOver( GameText& button );

	// Creates a new window in either full screen or windowed based on the current setting
	void toggleFullScreen();

	// Mutes/unmutes all sounds based on the current mute setting
	void toggleMute();

	// Sets the game volume to the passed in value
	void setVolume( float volume );

	// Sets all the leaderboard strings to their corresponding highscore
	void setLeaderBoardStrings();

	// Updates level text
	void updateLevelText();
	
	// Updates lives text
	void updateLivesText();

	// Updates score text
	void updateScoreText();

	// Updates all the currently active bullet objects
	void updateBullets( float deltaTime );

	// Updates all the currently active invader objects
	void updateInvaders( float deltaTime );

	// Updates all the objects during gameplay
	void updateGameplay( float deltaTime );

	// Updates all the relevant objects whilst in the menu
	void updateMenu();

	// Updates all the relevant objects whilst in the new high score screen
	void updateNewHighScoreScreen();

	// Updates all the objects within the main menu
	void updateMainMenu();

	// Renders all the currently active bullet objects
	void renderBullets() const;

	// Renders all the currently active invader objects
	void renderInvaders() const;

	// Renders all the text objects used during gameplay
	void renderGameplayText() const;

	// Updates any logic for the current frame of the game
	void update( float deltaTime );

	// Draws everything in the window for current frame of the game
	void render() const;

public:
	// Constructor
	Game();

	// Destructor
	~Game();

	// Runs the main game loop
	void run();
};

#endif // !GAME_H
