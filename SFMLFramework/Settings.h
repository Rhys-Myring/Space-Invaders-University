#ifndef SETTINGS_H
#define SETTINGS_H

// File to store different constants to avoid magic numbers

// Window Constants
const int k_windowWidth = 1920;
const int k_windowHeight = 1080;
const int k_maxFrameRate = 60;

// Boundary Constants
const float k_minBoundaryPosition = 120.0f;
const float k_maxBoundaryPosition = 1800.0f;

// Player Constants
const int	k_playerLives = 3;
const float	k_playerStartingXPos = k_windowWidth / 2.0f;
const float	k_playerStartingYPos = k_windowHeight * 0.8f;
const float k_playerSpeed = 250.0f;
const float k_playerDamping = 0.85f;

// Invader Constants
const int	k_invaderColumns = 11;
const int	k_invaderRows = 5;
const int	k_maxNumberOfInvaders = k_invaderRows * k_invaderColumns;
const int	k_initialInvaderMovementDirection = 1;
const int	k_invaderScore = 100;
const float	k_invaderChanceOfDiving = 0.000000125f;
const float	k_invaderChanceOfShooting = 0.00025f;
const float	k_invaderSpacing = 50.0f;
const float k_invaderStartingXPos = k_playerStartingXPos - k_invaderColumns * ( k_invaderSpacing / 2.0f );
const float k_invaderStartingYPos = 70.0f;
const float k_minInvaderSpeed = 75.0f;
const float k_maxInvaderSpeed = 300.0f;
const float k_invaderSpeedIncrease = 10.0f;
const float k_invaderYStep = 50.0f;
const float k_lowestMaxInvaderPosition = k_maxBoundaryPosition - ( k_invaderColumns - 1.0f ) * k_invaderSpacing;
const float k_minInvaderPosition = k_minBoundaryPosition;
const float k_invaderWinHeight = k_windowHeight * 0.75f;
const float k_invaderEnterHeight = -20.0f;

// Invader Formation Manager Constants
const int k_minimumColumn = 0;
const int k_maximumColumn = k_invaderColumns - 1;

// Bullet Constants
const int	k_playerBulletIndex = 0;
const int	k_invaderBulletStartingIndex = 1;
const float k_bulletSpeed = 750.0f;
const float k_bulletRespawnTop = -200.0f;
const float k_bulletRespawnBottom = k_windowHeight + 50.0f;
const float k_maxBullets = k_maxNumberOfInvaders + 1.0f;

// Text Constants
const int k_hudTextSize = 45;
const int k_levelTextPositionX = 1700;
const int k_scoreTextPositionX = 100;
const int k_screenCentreX = k_windowWidth / 2;
const int k_screenCentreY = k_windowHeight / 2;
const int k_leaderBoardTextPositionY = k_screenCentreY - 150;
const int k_mainMenuTextPositionY = k_screenCentreY - 100;
const int k_infoTextPositionY = k_screenCentreY - 150;
const int k_invalidTextPositionY = k_screenCentreY + 250;
const int k_returnToMainMenuTextPositionY = k_screenCentreY + 350;
const int k_fullScreenTextPositionY = k_screenCentreY + 100;
const int k_muteTextPositionY = k_screenCentreY;
const float k_menuTextSpacing = 100.0f;

// Menu Constants
const int k_numMainMenuButtons = 4;
const int k_playButton = 0;
const int k_highScoreButton = 1;
const int k_settingsButton = 2;
const int k_exitButton = 3;

// Animation Contants
const int k_imageSpacing = 1;

// Player Animation Constants
const int k_numberPlayerAnimationOfFrames = 3;
const int k_playerStartingFrameXPos = 0;
const int k_playerStartingFrameYPos = 0;
const int k_playerFrameWidth = 40;
const int k_playerFrameHeight = 25;
const float k_playerDeathAnimFramesPerSecond = 6.0f;

// Invader Animation Constants
const int k_numberInvaderAnimationOfFrames = 2;
const int k_invaderStartingFrameXPos = 0;
const int k_invaderFrameWidth = 40;
const int k_invaderFrameHeight = 27;
const int k_invaderDefaultAnimStartingFrameYPos = 0;
const int k_invaderDeathAnimStartingFrameYPos = 27;
const float k_invaderDefaultAnimFramesPerSecond = 1.5f;
const float k_invaderDeathAnimFramesPerSecond = 15.0f;

// Misc Constants
const int	k_startingLevel = 1;
const int	k_maxNumberOfHighScores = 5;
const int	k_maxNameLength = 15;
const int	k_nonPrintableChar = 128;
const char	k_backspaceChar = 8;
const float k_timeBeforeReset = 1.0f;
const float k_timeBeforeReturningToMenu = 3.0f;
const float k_logoXPos = k_windowWidth / 2.0f;
const float k_logoYPos = 175.0f;

#endif // !SETTINGS_H