#include <iostream>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "Bullet.h"
#include "CollisionDetector.h"
#include "ConfigSettingsManager.h"
#include "EnemyBullet.h"
#include "FontManager.h"
#include "Game.h"
#include "GameStates.h"
#include "GameText.h"
#include "Helpers.h"
#include "HighScoreManager.h"
#include "Invader.h"
#include "InvaderFormationManager.h"
#include "InvaderStates.h"
#include "MenuScreens.h"
#include "MouseManager.h"
#include "Player.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "Settings.h"
#include "TextInputManager.h"
#include "TextureManager.h"

// Constructor
Game::Game()
// Sets m_currentLevel to k_startingLevel (1), starting lives to k_playerLives and m_timeInCurrentState in current state to 0 
	: m_currentLevel( k_startingLevel )
	, m_lives( k_playerLives )
	, m_timeInCurrentState( 0.0f )

	// Sets pointers to null by default
	, m_pClock( nullptr )
	, m_pCollisionDetector( nullptr )
	, m_pConfigSettingsManager( nullptr )
	, m_pCurrentGameState( nullptr )
	, m_pCurrentMenuScreen( nullptr )
	, m_pFontManager( nullptr )
	, m_pFullScreenButton( nullptr )
	, m_pGameBackground( nullptr )
	, m_pGameLogo( nullptr )
	, m_pGameMusic( nullptr )
	, m_pGameOverText( nullptr )
	, m_pHighScoreManager( nullptr )
	, m_pInfoText( nullptr )
	, m_pInvaders( nullptr )
	, m_pInvaderFormationManager( nullptr )
	, m_pInvalidText( nullptr )
	, m_pMainMenuButtons( nullptr )
	, m_pMenuBackground( nullptr )
	, m_pMenuMusic( nullptr )
	, m_pMouseManager( nullptr )
	, m_pMuteButton( nullptr )
	, m_pNameText( nullptr )
	, m_pLeaderBoardText( nullptr )
	, m_pLevelText( nullptr )
	, m_pLivesText( nullptr )
	, m_pPlayer( nullptr )
	, m_pReturnToMainMenuButton( nullptr )
	, m_pScoreManager( nullptr )
	, m_pScoreText( nullptr )
	, m_pSoundManager( nullptr )
	, m_pSubmitButton( nullptr )
	, m_pTextInputManager( nullptr )
	, m_pTextureManager( nullptr )
	, m_pWindow( nullptr )
{
	// Initialises all the game objects
	initialise();
}

// Destructor
Game::~Game()
{
	// Deletes all the pointers to avoid memory leaks
	deleteAllPointers();
}

//-----------------------------------------------------
// Function		: run
// Purpose		: To run the main game loop
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::run()
{
	// Declares variable needed for storing deltaTime
	sf::Time deltaTime;

	while( m_pWindow->isOpen() )
	{
		// Gets the time elapsed since the beginning of the last frame
		deltaTime = m_pClock->restart();

		// Deals with all the window events and stops the window from freezing
		handleWindowEvents();

		// Clears the screen
		m_pWindow->clear();

		// Updates all objects
		update( deltaTime.asSeconds() );

		// Renders all objects
		render();

		// Displays rendered textures in the window
		m_pWindow->display();
	}
}

//-----------------------------------------------------
// Function		: deleteAllPointers
// Purpose		: To delete all the pointers to avoid memory leaks
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::deleteAllPointers()
{
	// Deletes m_pclock to avoid a memory leak
	safeDelete( m_pClock );

	// Deletes m_pCollisionDetector to avoid a memory leak
	safeDelete( m_pCollisionDetector );

	// Deletes m_pConfigSettingsManager to avoid a memory leak
	safeDelete( m_pConfigSettingsManager );

	// Deletes m_pCurrentGameState to avoid a memory leak
	safeDelete( m_pCurrentGameState );

	// Deletes m_pCurrentMenuScreen to avoid a memory leak
	safeDelete( m_pCurrentMenuScreen );

	// Deletes m_pFontManager to avoid a memory leak
	safeDelete( m_pFontManager );

	// Deletes m_pFullScreenButton to avoid a memory leak
	safeDelete( m_pFullScreenButton );

	// Deletes m_pGameBackground to avoid a memory leak
	safeDelete( m_pGameBackground );

	// Deletes m_pGameLogo to avoid a memory leak
	safeDelete( m_pGameLogo );

	// Deletes m_pGameMusic to avoid a memory leak
	safeDelete( m_pGameMusic );

	// Deletes m_pGameOverText to avoid a memory leak
	safeDelete( m_pGameOverText );

	// Deletes m_pHighScoreManager to avoid a memory leak
	safeDelete( m_pHighScoreManager );

	// Deletes m_pInfoText to avoid a memory leak
	safeDelete( m_pInfoText );

	// Deletes m_pInvaders to avoid a memory leak
	safeDeleteArray( m_pInvaders );

	// Deletes m_pInvaderFormationManager to avoid a memory leak
	safeDelete( m_pInvaderFormationManager );

	// Deletes m_pInvalidText to avoid a memory leak
	safeDelete( m_pInvalidText );

	// Deletes m_pMainMenuButtons to avoid a memory leak
	safeDeleteArray( m_pMainMenuButtons );

	// Deletes m_pMenuBackground to avoid a memory leak
	safeDelete( m_pMenuBackground );

	// Deletes m_pMouseManager to avoid a memory leak
	safeDelete( m_pMouseManager );

	// Deletes m_pMuteButton to avoid a memory leak
	safeDelete( m_pMuteButton );

	// Deletes m_pMenuMusic to avoid a memory leak
	safeDelete( m_pMenuMusic );

	// Deletes m_pNameText to avoid a memory leak
	safeDelete( m_pNameText );

	// Deletes m_pLeaderBoardText to avoid a memory leak
	safeDeleteArray( m_pLeaderBoardText );

	// Deletes m_pLevelText to avoid a memory leak
	safeDelete( m_pLevelText );

	// Deletes m_pLivesText to avoid a memory leak
	safeDelete( m_pLivesText );

	// Deletes m_pPlayer to avoid a memory leak
	safeDelete( m_pPlayer );

	// Deletes m_pReturnToMainMenuButton to avoid a memory leak
	safeDelete( m_pReturnToMainMenuButton );

	// Deletes m_pScoreManager to avoid a memory leak
	safeDelete( m_pScoreManager );

	// Deletes m_pScoreText to avoid a memory leak
	safeDelete( m_pScoreText );

	// Deletes m_pSoundManager to avoid a memory leak
	safeDelete( m_pSoundManager );

	// Deletes m_pSubmitButton to avoid a memory leak
	safeDelete( m_pSubmitButton );

	// Deletes m_pTextInputManager to avoid a memory leak
	safeDelete( m_pTextInputManager );

	// Deletes m_pTextureManager to avoid a memory leak
	safeDelete( m_pTextureManager );

	// Deletes m_pwindow to avoid a memory leak
	safeDelete( m_pWindow );
}

//-----------------------------------------------------
// Function		: initialise
// Purpose		: To intialise all the game objects
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialise()
{
	// Intialises the configuration settings manager
	initialiseConfigSettingsManager();

	// Initialises the window
	initialiseWindow();

	// Initialises the texture manager
	initialiseTextureManager();

	// Initialises the sound manager
	initialiseSoundManager();

	// Initialises the font manager
	initialiseFontManager();

	// Initialises the high score manager
	initialiseHighScoreManager();

	// Initialises the in game background
	initialiseGameBackground();

	// Initialises the menu background
	initialiseMenuBackground();

	// Intialises all the bullet objects and loads their textures
	initialiseBullets();

	// Intialises player object and loads its texture
	initialisePlayer();

	// Intialises all the invader objects and loads their textures
	initialiseInvaders();

	// Intialises InvaderFormationManager object
	initialiseInvaderFormationManager();

	// Intialises ScoreManager object
	initialiseScoreManager();

	// Intialises the Collision Detector
	initialiseCollisionDetector();

	// Intialises main menu button array
	initialiseMainMenuButtons();

	// Intialises game over text object and loads its font
	initialiseGameOverText();

	// Intialises level text object and loads its font
	initialiseLevelText();

	// Intialises lives text object and loads its font
	initialiseLivesText();

	// Intialises score text object and loads its font
	initialiseScoreText();

	// Intialises return to main menu button object and loads its font
	initialiseReturnToMainMenuButton();

	// Intialises mute button object and loads its font
	initialiseMuteButton();

	// Intialises full screen button object and loads its font
	initialiseFullScreenButton();

	// Intialises leaderboard text array and loads its font
	initialiseLeaderBoardText();

	// Intialises name text object and loads its font
	initialiseNameText();

	// Intialises info text object and loads its font
	initialiseInfoText();

	// Intialises invalid text object and loads its font
	initialiseInvalidText();

	// Intialises submit button object and loads its font
	initialiseSubmitButton();

	// Initialises Menu Music
	initialiseMenuMusic();

	// Initialises Game Music
	initialiseGameMusic();

	// Initialises Game Logo
	initialiseGameLogo();

	// Initialises Game State
	initialiseGameState();

	// Intialises the Menu Screen
	initialiseMenuScreen();

	// Intialises the Mouse Manager
	initialiseMouseManager();

	// Intialises the Text Input Manager
	initialiseTextInputManager();

	// Intialises the Clock
	initialiseClock();

	// Initialises the Volume level of the game
	initialiseVolume();

	// Generates a seed based on the current time to make randomisation in the game more random
	generateSeed();
}

//-----------------------------------------------------
// Function		: initialiseConfigSettingsManager
// Purpose		: To intialise the configuration settings manager
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseConfigSettingsManager()
{
	// Sets the configuration settings manager pointer to a new configuration settings manager object
	m_pConfigSettingsManager = new ConfigSettingsManager();
}

//-----------------------------------------------------
// Function		: initialiseWindow
// Purpose		: To intialise the window object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseWindow()
{
	// Checks whether the config settings have full screen enabled
	if( m_pConfigSettingsManager->getFullScreen() )
	{
		// Creates window in full screen mode
		m_pWindow = new sf::RenderWindow( sf::VideoMode( k_windowWidth, k_windowHeight ), "Space Invaders", 
			sf::Style::Fullscreen );
	}
	else
	{
		// Creates window in window mode
		m_pWindow = new sf::RenderWindow( sf::VideoMode( k_windowWidth, k_windowHeight ), "Space Invaders" );
	}

	// Sets frame rate limit
	m_pWindow->setFramerateLimit( k_maxFrameRate );

	// Enables frame rate limit
	m_pWindow->setVerticalSyncEnabled( true );
}

//-----------------------------------------------------
// Function		: initialiseTextureManager
// Purpose		: To intialise the TextureManager object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseTextureManager()
{
	// Sets the texture manager pointer to a new texture manager
	m_pTextureManager = new TextureManager();
}

//-----------------------------------------------------
// Function		: initialiseSoundManager
// Purpose		: To intialise the SoundManager object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseSoundManager()
{
	// Sets the sound manager pointer to a new sound manager
	m_pSoundManager = new SoundManager();
}

//-----------------------------------------------------
// Function		: initialiseFontManager
// Purpose		: To intialise the FontManager object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseFontManager()
{
	// Sets the font manager pointer to a new font manager
	m_pFontManager = new FontManager();
}

//-----------------------------------------------------
// Function		: initialiseHighScoreManager
// Purpose		: To intialise the HighScoreManager object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseHighScoreManager()
{
	// Sets the high score manager pointer to a new high score manager object
	m_pHighScoreManager = new HighScoreManager();
}

//-----------------------------------------------------
// Function		: initialiseGameBackground
// Purpose		: To intialise the in game background object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseGameBackground()
{
	// Sets background to new a new sprite
	m_pGameBackground = new sf::Sprite();

	// Loads the background image
	m_pGameBackground->setTexture( m_pTextureManager->getTexture( "background" ) );
}

//-----------------------------------------------------
// Function		: initialiseMenuBackground
// Purpose		: To intialise the menu background object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseMenuBackground()
{
	// Sets menu background to new a new sprite
	m_pMenuBackground = new sf::Sprite();

	// Loads the menu background image
	m_pMenuBackground->setTexture( m_pTextureManager->getTexture( "menu" ) );
}

//-----------------------------------------------------
// Function		: initialiseBullets
// Purpose		: To intialise all of the bullet objects
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseBullets()
{
	// Adds player bullet to vector of bullets
	m_bullets.push_back( new Bullet() );

	// Loads the player bullet sprite texture
	m_bullets[k_playerBulletIndex]->setCentredTexture( m_pTextureManager->getTexture( "bullet" ) );

	// Creates a bullet for each invader and adds them to the vector
	for( int i = k_invaderBulletStartingIndex; i <= k_maxNumberOfInvaders; i++ )
	{
		// Adds enemy bullet to vector of bullets
		m_bullets.push_back( new EnemyBullet() );

		// Loads the enemy bullet sprite texture
		m_bullets[i]->setCentredTexture( m_pTextureManager->getTexture( "enemyBullet" ) );
	}
}

//-----------------------------------------------------
// Function		: initialisePlayer
// Purpose		: To intialise the player object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialisePlayer()
{
	// Sets player pointer to a new player
	m_pPlayer = new Player();

	// Loads the player sprite texture
	m_pPlayer->setCentredTexture( m_pTextureManager->getTexture( "player" ) );

	// Loads the player death sound
	m_pPlayer->setDeathSound( m_pSoundManager->getSound( "death" ) );

	// Loads the player shooting sound
	m_pPlayer->setShootingSound( m_pSoundManager->getSound( "shoot" ) );

	// Sets player's bullet to the player's bullet from the bullet vector (first index of the bullet vector) 
	m_pPlayer->setBullet( m_bullets[k_playerBulletIndex] );
}

//-----------------------------------------------------
// Function		: initialiseInvaders
// Purpose		: To intialise all the invader objects
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseInvaders()
{
	// Creates new array of invader objects
	m_pInvaders = new Invader[k_maxNumberOfInvaders];

	// Iterates through array of invaders, loads their textures and sets their positions
	for( int i = 0; i < k_maxNumberOfInvaders; i++ )
	{
		// Loads the invader sprite texture
		m_pInvaders[i].setTexture( m_pTextureManager->getTexture( "invader" ) );

		// Loads the invader's death sound
		m_pInvaders[i].setDeathSound( m_pSoundManager->getSound( "death" ) );

		// Loads the invader's shooting sound
		m_pInvaders[i].setShootingSound( m_pSoundManager->getSound( "shoot" ) );

		// Sets the invader's bullet to the corresponding bullet inside the bullet vector
		m_pInvaders[i].setBullet( static_cast<EnemyBullet*>( m_bullets[k_invaderBulletStartingIndex + i] ) );
	}

	// Sets the invaders to their starting positions
	setInvaderPositions();
}

//-----------------------------------------------------
// Function		: initialiseInvaderFormationManager
// Purpose		: To intialise the InvaderFormationManager object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseInvaderFormationManager()
{
	// Sets the invader formation manager pointer to a new invader formation manager
	m_pInvaderFormationManager = new InvaderFormationManager();

	// Sets the invader pointer inside the formation manager to the array of invaders 
	m_pInvaderFormationManager->setInvaderArray( m_pInvaders );
}

//-----------------------------------------------------
// Function		: initialiseScoreManager
// Purpose		: To intialise the ScoreManager object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseScoreManager()
{
	// Sets the score manager to new a new instance of ScoreManager
	m_pScoreManager = new ScoreManager();
}

//-----------------------------------------------------
// Function		: initialiseCollisionDetector
// Purpose		: To intialise the Collision Detector object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseCollisionDetector()
{
	// Sets the collision detector pointer to a new collsion detector object
	m_pCollisionDetector = new CollisionDetector();
}

//-----------------------------------------------------
// Function		: initialiseMainMenuButtons
// Purpose		: To intialise the main menu button array
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseMainMenuButtons()
{
	// Sets the main menu buttons to new a new array of GameText objects
	m_pMainMenuButtons = new GameText[k_numMainMenuButtons];

	for( int i = 0; i < k_numMainMenuButtons; i++ )
	{
		// Loads the font for the current main menu text object
		m_pMainMenuButtons[i].setFont( m_pFontManager->getFont( "lt_energy" ) );

		// Sets the character size of the current main menu text object
		m_pMainMenuButtons[i].setCharacterSize( k_hudTextSize );

		// Sets the string of the text based on which button is currently being initialised
		switch( i )
		{
			// If the button being intialised is the play text 
			case k_playButton:
			{
				m_pMainMenuButtons[i].setString( "Play" );
				break;
			}

			// If the button being intialised is the high scores text
			case k_highScoreButton:
			{
				m_pMainMenuButtons[i].setString( "High Scores" );
				break;
			}

			// If the button being intialised is the settings text
			case k_settingsButton:
			{
				m_pMainMenuButtons[i].setString( "Settings" );
				break;
			}

			// If the button being intialised is the exit text
			case k_exitButton:
			{
				m_pMainMenuButtons[i].setString( "Exit Game" );
				break;
			}

			// Default in case a bug causes the index to go too high 
			default:
			{
				std::cout << "Invalid GameText Object Being Assigned";
				break;
			}
		}

		// Sets the origin of the current main menu text object to its centre 
		m_pMainMenuButtons[i].setOriginToCentre();

		// Sets the position of the current main menu text object
		m_pMainMenuButtons[i].setPosition( k_screenCentreX, k_mainMenuTextPositionY + i * k_menuTextSpacing );
	}
}

//-----------------------------------------------------
// Function		: initialiseGameOverText
// Purpose		: To intialise the game over text object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseGameOverText()
{
	// Sets game over text to new a new instance of GameText
	m_pGameOverText = new GameText();

	// Loads the game over text font
	m_pGameOverText->setFont( m_pFontManager->getFont( "lt_energy" ) );

	// Sets the game over text string
	m_pGameOverText->setString( "Game Over" );

	// Sets the game over text size
	m_pGameOverText->setCharacterSize( k_hudTextSize );

	// Sets the position of the game over text
	m_pGameOverText->setPosition( k_screenCentreX, k_screenCentreY );

	// Sets the origin of the game over text to the centre
	m_pGameOverText->setOriginToCentre();
}

//-----------------------------------------------------
// Function		: initialiseLevelText
// Purpose		: To intialise the level text object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseLevelText()
{
	// Sets level text to new a new instance of GameText
	m_pLevelText = new GameText();

	// Loads the level text font
	m_pLevelText->setFont( m_pFontManager->getFont( "lt_energy" ) );

	// Sets the level text intial string
	m_pLevelText->setString( addStrings( "Level: ", convertIntToString( m_currentLevel ) ) );

	// Sets the level text size
	m_pLevelText->setCharacterSize( k_hudTextSize );

	// Sets the position of the level text
	m_pLevelText->setPosition( k_levelTextPositionX, m_pLevelText->getPosition().y );

	// Sets the origin of the level text to the centre
	m_pLevelText->setOriginToCentre();
}

//-----------------------------------------------------
// Function		: initialiseLivesText
// Purpose		: To intialise the lives text object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseLivesText()
{
	// Sets lives text to new a new instance of GameText
	m_pLivesText = new GameText();

	// Loads the lives text font
	m_pLivesText->setFont( m_pFontManager->getFont( "lt_energy" ) );

	// Sets the lives text intial string
	m_pLivesText->setString( addStrings( "Lives: ", convertIntToString( m_lives ) ) );

	// Sets the lives text size
	m_pLivesText->setCharacterSize( k_hudTextSize );

	// Sets the position of the lives text
	m_pLivesText->setPosition( k_screenCentreX, m_pLivesText->getPosition().y );

	// Sets the origin of the lives text to the centre
	m_pLivesText->setOriginToCentre();
}

//-----------------------------------------------------
// Function		: initialiseScoreText
// Purpose		: To intialise the score text object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseScoreText()
{
	// Sets score text to new a new instance of GameText
	m_pScoreText = new GameText();

	// Loads the score text font
	m_pScoreText->setFont( m_pFontManager->getFont( "lt_energy" ) );

	// Sets the score text intial string
	m_pScoreText->setString( addStrings( "Score: ", convertIntToString( m_pScoreManager->getScore() ) ) );

	// Sets the score text size
	m_pScoreText->setCharacterSize( k_hudTextSize );

	// Sets the position of the score text
	m_pScoreText->setPosition( k_scoreTextPositionX, m_pScoreText->getPosition().y );

	// Sets the origin of the score text to the centre
	m_pScoreText->setOriginToCentre();
}

//-----------------------------------------------------
// Function		: initialiseLeaderBoardText
// Purpose		: To intialise the leaderboard text array
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseLeaderBoardText()
{
	// Sets leaderboard text to new a new array of GameText objects
	m_pLeaderBoardText = new GameText[k_maxNumberOfHighScores];

	for( int i = 0; i < k_maxNumberOfHighScores; i++ )
	{
		// Loads the font for the current leaderboard text object
		m_pLeaderBoardText[i].setFont( m_pFontManager->getFont( "lt_energy" ) );

		// Sets the character size of the current leaderboard text object
		m_pLeaderBoardText[i].setCharacterSize( k_hudTextSize );

		if( i < m_pHighScoreManager->getNumberOfHighScores() )
		{
			// Sets the string of the current leaderboard text object
			std::string nameWithSpaces = m_pHighScoreManager->getName( i ) + "		";
			m_pLeaderBoardText[i].setString( addStrings( nameWithSpaces, convertIntToString( m_pHighScoreManager->getScore( i ) ) ) );
		}

		// Sets the origin of the current leaderboard text object to its centre 
		m_pLeaderBoardText[i].setOriginToCentre();

		// Sets the position of the current leaderboard text object
		m_pLeaderBoardText[i].setPosition( k_screenCentreX, k_leaderBoardTextPositionY + i * k_menuTextSpacing );
	}
}

//-----------------------------------------------------
// Function		: initialiseReturnToMainMenuButton
// Purpose		: To intialise the return the main menu button
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseReturnToMainMenuButton()
{
	// Sets return to main menu button to new a new instance of GameText
	m_pReturnToMainMenuButton = new GameText();

	// Loads the return to main menu text font
	m_pReturnToMainMenuButton->setFont( m_pFontManager->getFont( "lt_energy" ) );

	// Sets the return to main menu string
	m_pReturnToMainMenuButton->setString( "Return To Main Menu" );

	// Sets the return to main menu text size
	m_pReturnToMainMenuButton->setCharacterSize( k_hudTextSize );

	// Sets the position of the return to main menu text
	m_pReturnToMainMenuButton->setPosition( k_screenCentreX, k_returnToMainMenuTextPositionY );

	// Sets the origin of the return to main menu text to the centre
	m_pReturnToMainMenuButton->setOriginToCentre();
}

//-----------------------------------------------------
// Function		: initialiseMuteButton
// Purpose		: To intialise the mute button
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseMuteButton()
{
	// Sets mute button to new a new instance of GameText
	m_pMuteButton = new GameText();

	// Loads the mute text font
	m_pMuteButton->setFont( m_pFontManager->getFont( "lt_energy" ) );

	// Sets the mute button string based on whether the settings have mute enabled
	if( m_pConfigSettingsManager->getMuted() )
	{
		// Sets the mute button string to Unmute Sounds
		m_pMuteButton->setString( "Unmute Sounds" );
	}
	else
	{
		// Sets the mute button string to Mute Sounds
		m_pMuteButton->setString( "Mute Sounds" );
	}

	// Sets the mute text size
	m_pMuteButton->setCharacterSize( k_hudTextSize );

	// Sets the position of the mute text
	m_pMuteButton->setPosition( k_screenCentreX, k_screenCentreY );

	// Sets the origin of the mute text to the centre
	m_pMuteButton->setOriginToCentre();
}

//-----------------------------------------------------
// Function		: initialiseFullScreenButton
// Purpose		: To intialise the full screen button
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseFullScreenButton()
{
	// Sets full screen button to new a new instance of GameText
	m_pFullScreenButton = new GameText();

	// Loads the full screen text font
	m_pFullScreenButton->setFont( m_pFontManager->getFont( "lt_energy" ) );

	// Sets the full screen button string based on whether the settings have full screen enabled
	if( m_pConfigSettingsManager->getFullScreen() )
	{
		// Sets the full screen button string to Yes
		m_pFullScreenButton->setString( "Full Screen: Yes" );
	}
	else
	{
		// Sets the full screen button string to No
		m_pFullScreenButton->setString( "Full Screen: No" );
	}
	
	// Sets the full screen text size
	m_pFullScreenButton->setCharacterSize( k_hudTextSize );

	// Sets the position of the full screen text
	m_pFullScreenButton->setPosition( k_screenCentreX, k_fullScreenTextPositionY );

	// Sets the origin of the full screen text to the centre
	m_pFullScreenButton->setOriginToCentre();
}

//-----------------------------------------------------
// Function		: initialiseNameText
// Purpose		: To intialise the name text object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseNameText()
{
	// Sets name text to new a new instance of GameText
	m_pNameText = new GameText();

	// Loads the name text font
	m_pNameText->setFont( m_pFontManager->getFont( "lt_energy" ) );

	// Sets the name text size
	m_pNameText->setCharacterSize( k_hudTextSize );

	// Sets the position of the name text
	m_pNameText->setPosition( k_screenCentreX, k_screenCentreY );

	// Sets the origin of the name text to the centre
	m_pNameText->setOriginToCentre();
}

//-----------------------------------------------------
// Function		: initialiseInfoText
// Purpose		: To intialise the information text object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseInfoText()
{
	// Sets info text to new a new instance of GameText
	m_pInfoText = new GameText();

	// Loads the info text font
	m_pInfoText->setFont( m_pFontManager->getFont( "lt_energy" ) );

	// Sets the info text size
	m_pInfoText->setCharacterSize( k_hudTextSize );

	// Sets the position of the info text
	m_pInfoText->setPosition( k_screenCentreX, k_infoTextPositionY );

	// Sets the origin of the info text to the centre
	m_pInfoText->setOriginToCentre();
}

//-----------------------------------------------------
// Function		: initialiseInvalidText
// Purpose		: To intialise the invalid text object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseInvalidText()
{
	// Sets invalid text to new a new instance of GameText
	m_pInvalidText = new GameText();

	// Loads the invalid text font
	m_pInvalidText->setFont( m_pFontManager->getFont( "lt_energy" ) );

	// Sets the invalid text size
	m_pInvalidText->setCharacterSize( k_hudTextSize );

	// Sets the position of the invalid text
	m_pInvalidText->setPosition( k_screenCentreX, k_invalidTextPositionY );

	// Sets the origin of the invalid text to the centre
	m_pInvalidText->setOriginToCentre();
}

//-----------------------------------------------------
// Function		: initialiseSubmitButton
// Purpose		: To intialise the submit button
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseSubmitButton()
{
	// Sets submit button to new a new instance of GameText
	m_pSubmitButton = new GameText();

	// Loads the return to submit text font
	m_pSubmitButton->setFont( m_pFontManager->getFont( "lt_energy" ) );

	// Sets the submit string
	m_pSubmitButton->setString( "Submit" );

	// Sets the submit text size
	m_pSubmitButton->setCharacterSize( k_hudTextSize );

	// Sets the position of the submit text
	m_pSubmitButton->setPosition( k_screenCentreX, k_returnToMainMenuTextPositionY );

	// Sets the origin of the submit text to the centre
	m_pSubmitButton->setOriginToCentre();
}

//-----------------------------------------------------
// Function		: initialiseGameLogo
// Purpose		: To intialise the game logo object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseGameLogo()
{
	// Sets logo to new a game sprite
	m_pGameLogo = new GameSprite();

	// Loads the logo image
	m_pGameLogo->setCentredTexture( m_pTextureManager->getTexture( "logo" ) );

	// Sets the position logo image
	m_pGameLogo->setPosition( k_logoXPos, k_logoYPos );
}

//-----------------------------------------------------
// Function		: initialiseMenuMusic
// Purpose		: To intialise the Menu Music object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseMenuMusic()
{
	// Sets Menu Music to a new instance of sf::Sound
	m_pMenuMusic = new sf::Sound();

	// Loads the Menu Music 
	m_pMenuMusic->setBuffer( m_pSoundManager->getSound( "menuMusic" ) );

	// Plays Menu Music
	m_pMenuMusic->play();

	// Loops Menu Music
	m_pMenuMusic->setLoop( true );
}

//-----------------------------------------------------
// Function		: initialiseGameMusic
// Purpose		: To intialise the Game Music object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseGameMusic()
{
	// Sets Game Music to a new instance of sf::Sound
	m_pGameMusic = new sf::Sound();

	// Loads the Game Music
	m_pGameMusic->setBuffer( m_pSoundManager->getSound( "gameMusic" ) );

	// Loops Game Music
	m_pGameMusic->setLoop( true );
}

//-----------------------------------------------------
// Function		: initialiseGameState
// Purpose		: To intialise the Current Game State object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseGameState()
{
	// Sets the current game state pointer to a new game state object
	m_pCurrentGameState = new GameStates( GameStates::Menu );
}

//-----------------------------------------------------
// Function		: initialiseMenuScreen
// Purpose		: To intialise the Current Menu Screen object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseMenuScreen()
{
	// Sets the menu screen pointer to a new menu screen object
	m_pCurrentMenuScreen = new MenuScreens( MenuScreens::MainMenu );
}

//-----------------------------------------------------
// Function		: initialiseMouseManager
// Purpose		: To intialise the Mouse Manager object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseMouseManager()
{
	// Sets the mouse manager pointer to a new mouse manager object
	m_pMouseManager = new MouseManager();
}

//-----------------------------------------------------
// Function		: initialiseTextInputManager
// Purpose		: To intialise the Text Input Manager object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseTextInputManager()
{
	// Sets the text input manager pointer to a new text input manager object
	m_pTextInputManager = new TextInputManager();
}

//-----------------------------------------------------
// Function		: initialiseClock
// Purpose		: To intialise the Clock object
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseClock()
{
	// Sets the clock pointer to a new clock object
	m_pClock = new sf::Clock();
}

//-----------------------------------------------------
// Function		: initialiseVolume
// Purpose		: To intialise the Game's volume
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::initialiseVolume()
{
	// If mute is enabled in the configuration settings then all sounds are muted
	if( m_pConfigSettingsManager->getMuted() )
	{
		// Mutes all sounds
		setVolume( 0.0f );
	}
}

//-----------------------------------------------------
// Function		: setInvaderPositions
// Purpose		: To set the invaders to their starting positions
// Parameters	: None
// Returns		: void
// Notes		: Separate function as it needs to be called from the reset and intialise invader functions
// See also		: initialiseInvaders, resetInvaders
//-----------------------------------------------------
void Game::setInvaderPositions()
{
	// Iterates through array of invaders and sets their positions
	for( int i = 0; i < k_maxNumberOfInvaders; i++ )
	{
		// Offsets invader positions so they each spawn in the correct spot
		float xOffset = k_invaderSpacing * ( i % k_invaderColumns );
		float yOffset = k_invaderSpacing * ( i % k_invaderRows );

		// Sets the position of the current invader being initialised
		m_pInvaders[i].setPosition( sf::Vector2f( k_invaderStartingXPos + xOffset,
			k_invaderStartingYPos + yOffset ) );

		// Sets the next y position of the current invader being initialised
		m_pInvaders[i].setNextYPosition( m_pInvaders[i].getPosition().y + k_invaderYStep );

		// Sets minimum and maximum X positions based on their starting offset so they all change direction
		// at the same time
		m_pInvaders[i].setMaxXPosition( k_lowestMaxInvaderPosition + xOffset );
		m_pInvaders[i].setMinXPosition( k_minInvaderPosition + xOffset );
	}
}

//-----------------------------------------------------
// Function		: startNextLevel
// Purpose		: To start the next level
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		: 
//-----------------------------------------------------
void Game::startNextLevel()
{
	// Updates the level text on screen
	updateLevelText();

	// Resets the invaders and adjusts their speed accordingly
	resetInvaders();

	// Deactivates all the bullets ready for the level to start
	deactivateBullets();
}

//-----------------------------------------------------
// Function		: calculateInvaderSpeed
// Purpose		: To calculate the new speed for the new level
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		: 
//-----------------------------------------------------
float Game::calculateInvaderSpeed()
{
	// Calculates new speed for the new level
	float newSpeed = k_minInvaderSpeed + m_currentLevel * k_invaderSpeedIncrease;

	// If new speed is larger than the max speed the speed is capped at the maximum
	if( newSpeed > k_maxInvaderSpeed )
	{
		newSpeed = k_maxInvaderSpeed;
	}

	// Returns the calculated speed
	return newSpeed;
}

//-----------------------------------------------------
// Function		: resetGame
// Purpose		: To reset the game at the start of a new game
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		: 
//-----------------------------------------------------
void Game::resetGame()
{
	// Resets score, level and lives
	m_currentLevel = k_startingLevel;
	m_pScoreManager->setScore( 0 );
	m_lives = k_playerLives;

	// Updates on screen text values
	updateScoreText();
	updateLevelText();
	updateLivesText();

	// Resets the Player's Position and animation
	m_pPlayer->reset();
}

//-----------------------------------------------------
// Function		: resetInvaders
// Purpose		: To set the invaders to their starting state and positions
// Parameters	: None
// Returns		: void
// Notes		: Also sets the speed of the invaders based on the level number
// See also		: 
//-----------------------------------------------------
void Game::resetInvaders()
{
	// Sets invaders back to their starting positions
	setInvaderPositions();

	// Resets formation manager so that the formation doesn't go out of sync
	m_pInvaderFormationManager->reset();

	// Calculates the invader speed based on the current level
	float newSpeed = calculateInvaderSpeed();

	// Iterates through array of invaders, sets them to their default state and sets speed based on the level number
	for( int i = 0; i < k_maxNumberOfInvaders; i++ )
	{
		// Sets speed based on the current level 
		if( m_currentLevel == k_startingLevel )
		{
			// Sets original speed if new level is level 1
			m_pInvaders[i].setSpeed( k_minInvaderSpeed );
		}
		else
		{
			// New speed is set
			m_pInvaders[i].setSpeed( newSpeed );
		}

		// Resets the invader's values to default
		m_pInvaders[i].reset();
	}
}

//-----------------------------------------------------
// Function		: deactivateBullets
// Purpose		: To set all bullets to inactive at the end of a level or when the player has died
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::deactivateBullets()
{
	// Iterates through vector of bullets
	for( auto it : m_bullets )
	{
		// Sets bullet to inactive
		it->setActiveState( false );
	}
}

//-----------------------------------------------------
// Function		: checkIfInvaderHit
// Purpose		: To check whether any of the invaders have been hit by the player's bullet or not
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::checkIfInvaderHit()
{
	// Iterates through array of invaders and checks if they have been hit
	for( int i = 0; i < k_maxNumberOfInvaders; i++ )
	{
		// If the invader is alive and the player's bullet is active
		if( m_pInvaders[i].getActiveState() && m_bullets[k_playerBulletIndex]->getActiveState() )
		{
			// Checks whether the bullet has collided with the invader
			bool hasBeenHit = m_pCollisionDetector->checkIfCollided( m_pInvaders[i].getGlobalBounds(),
				m_bullets[k_playerBulletIndex]->getGlobalBounds() );

			// If the bullet has collided with the current invader it kills the invader
			if( hasBeenHit )
			{
				// Kills the invader
				m_pInvaders[i].kill();

				// Sets the bullet to inactive
				m_bullets[k_playerBulletIndex]->setActiveState( false );

				// Increases the player's score
				m_pScoreManager->increaseScore( m_pInvaders[i].getScore() );
			}
		}
	}

	// Updates score text 
	updateScoreText();
}

//-----------------------------------------------------
// Function		: checkIfInvadersTooLow
// Purpose		: To check whether any of the invaders have got low enough to make the player lose
// Parameters	: None
// Returns		: bool
// Notes		:
// See also		:
//-----------------------------------------------------
bool Game::checkIfInvadersTooLow()
{
	// Iterates through array of invaders and checks if they are too low
	for( int i = 0; i < k_maxNumberOfInvaders; i++ )
	{
		// If the invader's y position is more than the winning threshold and the Invader is in formation state
		if( m_pInvaders[i].getPosition().y >= k_invaderWinHeight
			&& m_pInvaders[i].getCurrentState() == InvaderStates::Formation )
		{
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------
// Function		: checkIfPlayerHit
// Purpose		: To check whether the player has been hit by any enemy bullets or not
// Parameters	: None
// Returns		: bool
// Notes		:
// See also		:
//-----------------------------------------------------
bool Game::checkIfPlayerHit()
{
	// Iterates through all the enemy bullets
	for( int i = 1; i <= k_maxNumberOfInvaders; i++ )
	{
		// If current bullet is active
		if( m_bullets[i]->getActiveState() )
		{
			// Checks whether the enemy bullet has collided with the player
			bool hasBeenHit = m_pCollisionDetector->checkIfCollided( m_pPlayer->getGlobalBounds(),
				m_bullets[i]->getGlobalBounds() );

			// If the enemy bullet has collided with the player it returns true
			if( hasBeenHit )
			{
				// Sets the invader's bullet to false
				m_bullets[i]->setActiveState( false );

				// Returns true
				return hasBeenHit;
			}
		}
	}

	// Iterates through all the enemies
	for( int i = 0; i < k_maxNumberOfInvaders; i++ )
	{
		// If current enemy is diving
		if( m_pInvaders[i].getCurrentState() == InvaderStates::Diving )
		{
			// Checks whether the enemy has collided with the player
			bool hasBeenHit = m_pCollisionDetector->checkIfCollided( m_pPlayer->getGlobalBounds(),
				m_pInvaders[i].getGlobalBounds() );

			// If the enemy has collided with the player it returns true
			if( hasBeenHit )
			{
				// Returns true
				return hasBeenHit;
			}
		}
	}

	// If no bullets or diving invaders have hit the player, false is returned
	return false;
}

//-----------------------------------------------------
// Function		: checkIfAllInvadersDead
// Purpose		: To check whether all of the invaders have been killed or not
// Parameters	: None
// Returns		: bool
// Notes		:
// See also		:
//-----------------------------------------------------
bool Game::checkIfAllInvadersDead()
{
	int deadInvaders = 0;

	// Iterates through array of invaders and checks if they are dead
	for( int i = 0; i < k_maxNumberOfInvaders; i++ )
	{
		// If the invader is dead 
		if( !m_pInvaders[i].getActiveState() )
		{
			// Increases number of dead invaders
			deadInvaders++;
		}
	}

	// Returns whether all the invaders are dead
	return ( deadInvaders == k_maxNumberOfInvaders );
}

//-----------------------------------------------------
// Function		: playerHit
// Purpose		: To decrease the player's lives and set the state to player dead
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::playerHit()
{
	// Plays the Player death sound
	m_pPlayer->playDeathSound();

	// Decreases the player's lives
	m_lives--;

	// Updates the lives text
	updateLivesText();

	// Plays death animation
	m_pPlayer->playDeathAnimation();

	// Sets game state to PlayerDead
	changeState( GameStates::PlayerDead );

	// If the player has no lives left
	if( m_lives <= 0 )
	{
		// Sets game state to GameOver
		changeState( GameStates::GameOver );
	}
}

//-----------------------------------------------------
// Function		: changeState
// Purpose		: To set the current game state to the passed in state
// Parameters	: GameStates newState
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::changeState( GameStates newState )
{
	// Carries out any functions used when exiting the current state
	onStateExit();

	// Carries out any functions used when entering the new state
	onStateEnter( newState );

	// Sets the new state
	*m_pCurrentGameState = newState;

	// Resets the current state time
	m_timeInCurrentState = 0.0f;
}

//-----------------------------------------------------
// Function		: onStateEnter
// Purpose		: To carry out specific actions when entering a given state
// Parameters	: GameStates newState
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::onStateEnter( GameStates newState )
{
	switch( newState )
	{
		// If the state being entered is Menu
		case GameStates::Menu:
		{
			// Stops Game Music
			m_pGameMusic->stop();

			// Plays Menu Music
			m_pMenuMusic->play();

			break;
		}

		// If the state being entered is Game
		case GameStates::Game:
		{
			break;
		}

		// If the state being entered is StartNewLevel
		case GameStates::StartNewLevel:
		{
			// Starts next level
			startNextLevel();

			break;
		}

		// If the state being entered is PlayerDead
		case GameStates::PlayerDead:
		{
			// Deactivates all the bullets ready for the player to respawn
			deactivateBullets();

			break;
		}

		// If the state being entered is GameOver
		case GameStates::GameOver:
		{

			break;
		}

		// Default in case there is a bug that causes an invalid value to be stored in the current game state
		default:
		{
			std::cout << "ERROR, Unexpected Value In newState";
			break;
		}
	}
}

//-----------------------------------------------------
// Function		: onStateExit
// Purpose		: To carry out specific actions when exiting the current state 
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::onStateExit()
{
	switch( *m_pCurrentGameState )
	{
		// If the state being exited is Menu
		case GameStates::Menu:
		{
			// Resets all the variables used during gameplay when staring a new game
			resetGame();

			// Stops Menu Music
			m_pMenuMusic->stop();

			// Plays Game Music
			m_pGameMusic->play();

			break;
		}

		// If the state being exited is Game
		case GameStates::Game:
		{
			break;
		}

		// If the state being exited is StartNewLevel
		case GameStates::StartNewLevel:
		{
			break;
		}

		// If the state being exited is PlayerDead
		case GameStates::PlayerDead:
		{
			break;
		}

		// If the state being exited is GameOver
		case GameStates::GameOver:
		{
			break;
		}

		// Default in case there is a bug that causes an invalid value to be stored in the current game state
		default:
		{
			std::cout << "ERROR, Unexpected Value In m_pCurrentGameState";
			break;
		}
	}
}

//-----------------------------------------------------
// Function		: changeMenuScreen
// Purpose		: To set the current menu screen state to the passed in screen
// Parameters	: MenuScreens newScreen
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::changeMenuScreen( MenuScreens newScreen )
{
	// Carries out any functions used when exiting the current menu screen
	onMenuScreenExit();

	// Carries out any functions used when entering the new menu screen
	onMenuScreenEnter( newScreen );

	// Sets the new menu screen
	*m_pCurrentMenuScreen = newScreen;
}

//-----------------------------------------------------
// Function		: onMenuScreenEnter
// Purpose		: To carry out specific actions when entering a given menu screen
// Parameters	: MenuScreens newScreen
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::onMenuScreenEnter( MenuScreens newScreen )
{
	switch( newScreen )
	{
		// If the screen being entered is the Main Menu
		case MenuScreens::MainMenu:
		{
			break;
		}

		// If the screen being entered is the High Scores Screen
		case MenuScreens::HighScores:
		{
			// Sets the information string to inform the player that there are no scores saved 
			// (Only rendered if it is the case)
			m_pInfoText->setString( "There are no high scores currently saved" );
			m_pInfoText->setOriginToCentre();
			break;
		}

		// If the screen being entered is the New High Score Screen
		case MenuScreens::NewHighScore:
		{
			// Sets waiting for text input to true so that key presses are stored
			m_pTextInputManager->setWaitingForInput( true );

			// Sets the information string to inform the player that they need to enter their name
			m_pInfoText->setString( "You Set A New Top 5 High Score! Please Enter Your Name" );
			m_pInfoText->setOriginToCentre();
			break;
		}

		// If the screen being entered is the Settings Screen
		case MenuScreens::Settings:
		{
			break;
		}

		// Default in case there is a bug that causes an invalid value to be stored in the current menu screen
		default:
		{
			std::cout << "ERROR, Unexpected Value In newScreen";
			break;
		}
	}
}

//-----------------------------------------------------
// Function		: onMenuScreenExit
// Purpose		: To carry out specific actions when exiting the current menu screen 
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::onMenuScreenExit()
{
	switch( *m_pCurrentMenuScreen )
	{
		// If the screen being exited is the Main Menu
		case MenuScreens::MainMenu:
		{
			break;
		}

		// If the screen being exited is the High Scores Screen
		case MenuScreens::HighScores:
		{
			break;
		}

		// If the screen being exited is the New High Score Screen
		case MenuScreens::NewHighScore:
		{
			// Updates all the strings for the high score table
			setLeaderBoardStrings();

			// Sets waiting for text input to false so that key presses are no longer stored
			m_pTextInputManager->setWaitingForInput( false );

			// Sets the invalid name text string to empty so it doesn't display next time the screen is loaded
			m_pInvalidText->setString( "" );
			break;
		}

		// If the screen being exited is the Settings Screen
		case MenuScreens::Settings:
		{
			break;
		}

		// Default in case there is a bug that causes an invalid value to be stored in the current menu screen
		default:
		{
			std::cout << "ERROR, Unexpected Value In m_pCurrentMenuScreen";
			break;
		}
	}
}

//-----------------------------------------------------
// Function		: checkIfReturnToMenuIsClicked
// Purpose		: To check whether the return to main menu button has been clicked or not
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::checkIfReturnToMenuIsClicked()
{
	// If the player clicks the return to main menu text, they are taken back to the main menu
	if( isHoveringOver( *m_pReturnToMainMenuButton ) && m_pMouseManager->checkIfClicked() )
	{
		// Sets current menu screen to the main menu
		changeMenuScreen( MenuScreens::MainMenu );
	}
}

//-----------------------------------------------------
// Function		: isHoveringOver
// Purpose		: To return whether the mouse is hovering over a given button
// Parameters	: GameText& button
// Returns		: bool
// Notes		:
// See also		:
//-----------------------------------------------------
bool Game::isHoveringOver( GameText& button )
{
	// If the mouse is hovering over the button being checked
	if( m_pCollisionDetector->checkIfCollided( button.getGlobalBounds(), 
		static_cast<sf::Vector2f>( sf::Mouse::getPosition( *m_pWindow ) ) ) )
	{
		// Sets colour of text to green when it's hovered over
		button.setFillColor( sf::Color::Green );
		return true;
	}
	// Sets colour back to white if it is not being hovered over
	else if( button.getFillColor() == sf::Color::Green )
	{
		button.setFillColor( sf::Color::White );
	}

	return false;
}

//-----------------------------------------------------
// Function		: toggleFullScreen
// Purpose		: To create a new window in either full screen or windowed mode based on the current setting
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::toggleFullScreen()
{
	// Inverts the full screen boolean
	m_pConfigSettingsManager->setFullScreen( !m_pConfigSettingsManager->getFullScreen() );

	// Deletes m_pwindow to avoid a memory leak
	safeDelete( m_pWindow );

	if( m_pConfigSettingsManager->getFullScreen() )
	{
		// Creates new window in full screen mode
		m_pWindow = new sf::RenderWindow( sf::VideoMode( k_windowWidth, k_windowHeight ), "Space Invaders", sf::Style::Fullscreen );

		// Sets the full screen button string to Yes
		m_pFullScreenButton->setString( "Full Screen: Yes" );
	}
	else
	{
		// Creates new window in windowed mode
		m_pWindow = new sf::RenderWindow( sf::VideoMode( k_windowWidth, k_windowHeight ), "Space Invaders" );

		// Sets the full screen button string to No
		m_pFullScreenButton->setString( "Full Screen: No" );
	}
	
	// Sets the origin of the full screen text to the centre
	m_pFullScreenButton->setOriginToCentre();

	// Sets frame rate limit
	m_pWindow->setFramerateLimit( k_maxFrameRate );

	// Enables frame rate limit
	m_pWindow->setVerticalSyncEnabled( true );
}

//-----------------------------------------------------
// Function		: toggleMute
// Purpose		: To mute/unmute all sounds based on the current mute setting
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		: setVolume
//-----------------------------------------------------
void Game::toggleMute()
{
	// Inverts the mute boolean
	m_pConfigSettingsManager->setMuted( !m_pConfigSettingsManager->getMuted() );

	if( m_pConfigSettingsManager->getMuted() )
	{
		// Sets the mute button string to Unmute Sounds
		m_pMuteButton->setString( "Unmute Sounds" );

		// Mutes all sounds
		setVolume( 0.0f );
	}
	else
	{
		// Sets the mute button string to Mute Sounds
		m_pMuteButton->setString( "Mute Sounds" );

		// Unmutes all sounds
		setVolume( 100.0f );
	}

	// Sets the origin of the mute text to the centre
	m_pMuteButton->setOriginToCentre();
}

//-----------------------------------------------------
// Function		: setVolume
// Purpose		: To set the game volume to the passed in value
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::setVolume( float volume )
{
	m_pMenuMusic->setVolume( volume );
	m_pGameMusic->setVolume( volume );
	m_pPlayer->setSoundEffectVolume( volume );

	// Iterates through array of invaders and sets their volume
	for( int i = 0; i < k_maxNumberOfInvaders; i++ )
	{
		// Mutes the current invader object
		m_pInvaders[i].setSoundEffectVolume( volume );
	}
}

//-----------------------------------------------------
// Function		: setLeaderBoardStrings
// Purpose		: To set all the leaderboard strings to their corresponding highscores
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::setLeaderBoardStrings()
{
	int numberOfStoredScores = m_pHighScoreManager->getNumberOfHighScores();

	// Iterates through the all the leaderboard text objects and assigns them their corresponding name and score
	for( int i = 0; i < numberOfStoredScores; i++ )
	{
		// Sets the string of the current leaderboard text object
		std::string nameWithSpaces = m_pHighScoreManager->getName( i ) + "		";
		m_pLeaderBoardText[i].setString( addStrings( nameWithSpaces, 
			convertIntToString( m_pHighScoreManager->getScore( i ) ) ) );

		// Sets the origin of the current leaderboard text object to its centre 
		m_pLeaderBoardText[i].setOriginToCentre();
	}
}

//-----------------------------------------------------
// Function		: updateLevelText
// Purpose		: To update the on-screen level text
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::updateLevelText()
{
	// Updates on-screen level text
	m_pLevelText->setString( addStrings( "Level: ", convertIntToString( m_currentLevel ) ) );
}

//-----------------------------------------------------
// Function		: updateLivesText
// Purpose		: To update the on-screen lives text
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::updateLivesText()
{
	// Updates on-screen lives text
	m_pLivesText->setString( addStrings( "Lives: ", convertIntToString( m_lives ) ) );
}

//-----------------------------------------------------
// Function		: updateScoreText
// Purpose		: To update the on-screen score text
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::updateScoreText()
{
	// Updates on-screen score text
	m_pScoreText->setString( addStrings( "Score: ", convertIntToString( m_pScoreManager->getScore() ) ) );
}

//-----------------------------------------------------
// Function		: updateBullets
// Purpose		: To update all the currently active bullet objects
// Parameters	: float deltaTime
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::updateBullets( float deltaTime )
{
	// Iterates through vector of bullets
	for( auto it : m_bullets )
	{
		// Checks if bullet is active
		if( it->getActiveState() )
		{
			// Updates the current bullet
			it->update( deltaTime );
		}
	}
}

//-----------------------------------------------------
// Function		: updateInvaders
// Purpose		: To update all the currently active invader objects
// Parameters	: float deltaTime
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::updateInvaders( float deltaTime )
{
	// Iterates through array of invaders and updates them
	for( int i = 0; i < k_maxNumberOfInvaders; i++ )
	{
		// Updates the current invader object
		m_pInvaders[i].update( deltaTime );
	}

	// Adjusts minimum and maximum positions of the formation based on which invaders are still alive
	m_pInvaderFormationManager->checkCurrentFormation();
}

//-----------------------------------------------------
// Function		: updateGameplay
// Purpose		: To update all the objects during gameplay
// Parameters	: float deltaTime
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::updateGameplay( float deltaTime )
{
	// Updates the player object
	m_pPlayer->update( deltaTime );

	// Updates all the invader objects
	updateInvaders( deltaTime );

	// Updates all the bullet objects
	updateBullets( deltaTime );

	// Checks if the player's bullet has collided with any of the invaders
	checkIfInvaderHit();

	// If player has been hit, player hit function is called
	if( checkIfPlayerHit() )
	{
		playerHit();
	}

	// If all Invaders are dead a new level is started
	if( checkIfAllInvadersDead() )
	{
		// Increases level number by 1
		m_currentLevel++;

		changeState( GameStates::StartNewLevel );
	}

	// If any of the Invaders got low enough to the ground to win the state is set to game over
	if( checkIfInvadersTooLow() )
	{
		changeState( GameStates::GameOver );
	}
}

//-----------------------------------------------------
// Function		: updateMenu
// Purpose		: To update all the relevant objects whilst in the menu
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::updateMenu()
{
	// Checks which menu screen the player is in
	switch( *m_pCurrentMenuScreen )
	{
		// If the player is on the main menu
		case MenuScreens::MainMenu:
		{
			// Checks whether any of the buttons have beem clicked in the main menu or not
			updateMainMenu();
			break;
		}

		// If the player is on the high scores screen
		case MenuScreens::HighScores:
		{
			// Returns player to main menu if the return to main menu button has been clicked
			checkIfReturnToMenuIsClicked();
			break;
		}

		// If the player is on the new high score screen
		case MenuScreens::NewHighScore:
		{
			// Makes the player enter their name for the highscore table
			updateNewHighScoreScreen();
			break;
		}

		// If the player is on the settings screen
		case MenuScreens::Settings:
		{
			// If mute button clicked, all sounds are muted/umuted depending on their current state
			if( isHoveringOver( *m_pMuteButton ) && m_pMouseManager->checkIfClicked() )
			{
				toggleMute();
			}

			// If Full Screen clicked, window is either made full screen or windowed depending on their current state
			else if( isHoveringOver( *m_pFullScreenButton ) && m_pMouseManager->checkIfClicked() )
			{
				toggleFullScreen();
			}

			// Returns player to main menu if the return to main menu button has been clicked
			checkIfReturnToMenuIsClicked();
			break;
		}

		// Default in case there is a bug that causes an invalid value to be stored in the current menu screen
		default:
		{
			std::cout << "ERROR, Unexpected Value In m_pCurrentMenuScreen";
			break;
		}
	}
}

//-----------------------------------------------------
// Function		: updateNewHighScoreScreen
// Purpose		: To update all the objects on the new high score screen
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::updateNewHighScoreScreen()
{
	// If a key has been pressed, it's corresponding character is added to the name string
	if( m_pTextInputManager->getHasKeyBeenPressed() )
	{
		// If the character inputted is the backspace then the last character of the string is removed
		if( m_pTextInputManager->getInputtedChar() == k_backspaceChar )
		{
			// Removes character from the string 
			m_pNameText->setString( m_pNameText->getString().substring( 0, m_pNameText->getString().getSize() - 1 ) );

			// Centres text based on the new length
			m_pNameText->setOriginToCentre();
		}

		// Checks that inputted character is not a comma as this would cause issues with reading/writing this to a file
		// Also makes sure name doesn't exceed the maximum length
		else if( m_pTextInputManager->getInputtedChar() != ',' && m_pNameText->getString().getSize() < k_maxNameLength )
		{
			// Adds character to the string 
			m_pNameText->setString( m_pNameText->getString() + m_pTextInputManager->getInputtedChar() );

			// Centres text based on the new length
			m_pNameText->setOriginToCentre();
		}

		// Sets key pressed to false so it doesn't spam the character
		m_pTextInputManager->setHasKeyBeenPressed( false );
	}

	// If the player clicks the submit button the name they entered is added to the high score table
	if( isHoveringOver( *m_pSubmitButton ) && m_pMouseManager->checkIfClicked() )
	{
		// Stores the entered name as an std::string
		std::string name = m_pNameText->getString();

		// Checks whether name can go on the high score table
		if( m_pHighScoreManager->checkName( name ) && name.size() > 0 )
		{
			// Adds new score to the high score table
			m_pHighScoreManager->addScore( name, m_pScoreManager->getScore() );

			// Sets current menu screen to the main menu
			changeMenuScreen( MenuScreens::MainMenu );
		}
		else
		{
			// Sets the invalid text string
			m_pInvalidText->setString( "Name Already Used, Please Enter A Unique Name" );

			// Sets the origin of the invalid text to the centre
			m_pInvalidText->setOriginToCentre();
		}
	}
}

//-----------------------------------------------------
// Function		: updateMainMenu
// Purpose		: To update all the objects within the main menu
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::updateMainMenu()
{
	// Iterates through all the buttons and checks if they are hovered over and/or clicked
	for( int buttonIndex = 0; buttonIndex < k_numMainMenuButtons; buttonIndex++ )
	{
		// If the player clicks the text they are hovering over then the corresponding action is carried out
		if( isHoveringOver( m_pMainMenuButtons[buttonIndex] ) && m_pMouseManager->checkIfClicked() )
		{
			// Carries out the specific action based on the index of the button that is clicked
			switch( buttonIndex )
			{
				// If the text being clicked is the play button 
				case k_playButton:
				{
					// Starts the game
					changeState( GameStates::StartNewLevel );
					break;
				}

				// If the text being clicked is the high score button 
				case k_highScoreButton:
				{
					// Sets current menu screen to the highscore screen
					changeMenuScreen( MenuScreens::HighScores );
					break;
				}

				// If the text being clicked is the settings button 
				case k_settingsButton:
				{
					// Sets current menu screen to the settings screen
					changeMenuScreen( MenuScreens::Settings );
					break;
				}

				// If the text being clicked is the exit button 
				case k_exitButton:
				{
					// Closes the window
					m_pWindow->close();
					break;
				}

				// Default in case a bug causes the index to go too high 
				default:
				{
					std::cout << "Invalid GameText Object Being Checked";
					break;
				}
			}
		}
	}
}

//-----------------------------------------------------
// Function		: renderBullets
// Purpose		: To render all the currently active bullet objects
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::renderBullets() const
{
	// Iterates through vector of bullets
	for( auto it : m_bullets )
	{
		// Checks if bullet is active
		if( it->getActiveState() )
		{
			// Renders the current bullet's sprite
			m_pWindow->draw( *it );
		}
	}
}

//-----------------------------------------------------
// Function		: renderInvaders
// Purpose		: To render all the currently active invader objects
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::renderInvaders() const
{
	// Iterates through array of invaders and renders them
	for( int i = 0; i < k_maxNumberOfInvaders; i++ )
	{
		// If the current invader is alive, renders the invader
		if( m_pInvaders[i].getActiveState() )
		{
			// Renders the invader sprite
			m_pWindow->draw( m_pInvaders[i] );
		}
	}
}

//-----------------------------------------------------
// Function		: renderGameplayText
// Purpose		: To render all the text objects used during gameplay
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::renderGameplayText() const
{
	// Renders the score text on screen
	m_pWindow->draw( *m_pScoreText );

	// Renders the level text on screen
	m_pWindow->draw( *m_pLevelText );

	// Renders the lives text on screen
	m_pWindow->draw( *m_pLivesText );
}

//-----------------------------------------------------
// Function		: handleWindowEvents
// Purpose		: To deal with all the window events and stop the window from freezing
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::handleWindowEvents()
{
	// Checks for any events within the window
	sf::Event event;
	while( m_pWindow->pollEvent( event ) )
	{
		// If "X" clicked the window is closed
		if( event.type == sf::Event::Closed )
		{
			m_pWindow->close();
		}

		// If text is entered and the game is waiting for text input, the inputted text is stored
		if( event.type == sf::Event::TextEntered && m_pTextInputManager->getWaitingForInput() )
		{
			// Makes sure character entered is a printable char
			if( event.text.unicode < k_nonPrintableChar )
			{
				// Stores inputted character
				m_pTextInputManager->setInputtedChar( static_cast<char>( event.text.unicode ) );

				// Sets key has been pressed to true
				m_pTextInputManager->setHasKeyBeenPressed( true );
			}
		}
	}
}

//-----------------------------------------------------
// Function		: update
// Purpose		: To update any logic for the current frame of the game
// Parameters	: float deltaTime
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::update( float deltaTime )
{
	// Updates time in current state
	m_timeInCurrentState += deltaTime;

	// Updates the states stored in the mouse manager
	m_pMouseManager->updateMouseState();

	// Updates different objects based on the current Game State
	switch( *m_pCurrentGameState )
	{
		// If the current state is Menu
		case GameStates::Menu:
		{
			// Updates all objects whilst in the menu
			updateMenu();
			break;
		}

		// If the current state is Game
		case GameStates::Game:
		{
			// Updates all objects during gameplay
			updateGameplay( deltaTime );
			break;
		}

		// If the current state is StartNewLevel
		case GameStates::StartNewLevel:
		{
			// Sets game state back to Game after k_timeBeforeReset seconds
			if( m_timeInCurrentState >= k_timeBeforeReset )
			{
				// Sets state back to Game so that gameplay resumes/starts
				changeState( GameStates::Game );
			}
			break;
		}

		// If the current state is PlayerDead
		case GameStates::PlayerDead:
		{
			// Sets game state back to Game after k_timeBeforeReset seconds
			if( m_timeInCurrentState >= k_timeBeforeReset )
			{
				// Resets the Player's Position and the animation
				m_pPlayer->reset();

				// Sets state back to Game so that gameplay resumes
				changeState( GameStates::Game );
			}

			// Updates the player's animation
			m_pPlayer->updateAnimation( deltaTime );
			break;
		}

		// If the current state is GameOver
		case GameStates::GameOver:
		{
			// Sets game state to Menu after k_timeBeforeReturningToMenu seconds
			if( m_timeInCurrentState >= k_timeBeforeReturningToMenu )
			{
				// Sets state back to Menu so that the user is returned to the menu
				changeState( GameStates::Menu );

				// If score is high enough to get on the top 5 scores the menu screen is set to new high score
				if( m_pHighScoreManager->checkScore( m_pScoreManager->getScore() ) )
				{
					changeMenuScreen( MenuScreens::NewHighScore );
				}
			}

			// Updates the player's animation
			m_pPlayer->updateAnimation( deltaTime );
			break;
		}

		// Default in case there is a bug that causes an invalid value to be stored in the current game state
		default:
		{
			std::cout << "ERROR, Unexpected Value In m_pCurrentGameState";
			break;
		}
	}
}

//-----------------------------------------------------
// Function		: render
// Purpose		: To draw everything in the window for current frame of the game
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void Game::render() const
{
	if( *m_pCurrentGameState != GameStates::Menu )
	{
		// Renders the background image
		m_pWindow->draw( *m_pGameBackground );

		// Renders all the active bullets
		renderBullets();

		// Renders the player sprite
		m_pWindow->draw( *m_pPlayer );

		// Renders all the currently active invader objects
		renderInvaders();

		// Renders all the text used during gameplay
		renderGameplayText();
	}
	else
	{
		// Renders the menu background
		m_pWindow->draw( *m_pMenuBackground );

		// Renders the game logo
		m_pWindow->draw( *m_pGameLogo );

		// Checks which menu screen the player is in
		switch( *m_pCurrentMenuScreen )
		{
			// If the player is on the main menu
			case MenuScreens::MainMenu:
			{
				// Iterates through all the main menu buttons and renders them
				for( int i = 0; i < k_numMainMenuButtons; i++ )
				{
					// Renders the current main menu GameText object
					m_pWindow->draw( m_pMainMenuButtons[i] );
				}
				break;
			}

			// If the player is on the high scores screen
			case MenuScreens::HighScores:
			{
				// Iterates through all the high score text objects and renders them
				for( int i = 0; i < m_pHighScoreManager->getNumberOfHighScores(); i++ )
				{
					// Renders the current leaderboard GameText object
					m_pWindow->draw( m_pLeaderBoardText[i] );
				}

				// If there are no high scores, text informing the player of this is displayed
				if( !m_pHighScoreManager->getNumberOfHighScores() )
				{
					// Renders the information GameText object
					m_pWindow->draw( *m_pInfoText );
				}

				// Renders the return to main menu text
				m_pWindow->draw( *m_pReturnToMainMenuButton );
				break;
			}

			// If the player is on the new high score screen
			case MenuScreens::NewHighScore:
			{
				// Renders the information GameText object
				m_pWindow->draw( *m_pInfoText );

				// Renders the player's name
				m_pWindow->draw( *m_pNameText );

				// Renders submit button
				m_pWindow->draw( *m_pSubmitButton );

				// Renders invalid text button
				m_pWindow->draw( *m_pInvalidText );
				break;
			}

			// If the player is on the settings screen
			case MenuScreens::Settings:
			{
				// Renders the mute button
				m_pWindow->draw( *m_pMuteButton );

				// Renders the full screen button
				m_pWindow->draw( *m_pFullScreenButton );

				// Renders the return to main menu text
				m_pWindow->draw( *m_pReturnToMainMenuButton );
				break;
			}

			// Default in case there is a bug that causes an invalid value to be stored in the current menu state
			default:
			{
				std::cout << "ERROR, Unexpected Value In m_pMenuState";
				break;
			}
		}
	}

	if( *m_pCurrentGameState == GameStates::GameOver )
	{
		// Renders the game over text
		m_pWindow->draw( *m_pGameOverText );
	}
}
