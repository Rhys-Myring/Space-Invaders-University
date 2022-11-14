#include "Helpers.h"
#include "SoundManager.h"

// Constructor
SoundManager::SoundManager()
{
	// Adds all the sounds to m_soundsToName
	addSoundsToMap();
}

// Destructor
SoundManager::~SoundManager()
{
}

//-----------------------------------------------------
// Function		: loadSound
// Purpose		: To load a sound from a given filename
// Parameters	: const char* fileName
// Returns		: sf::SoundBuffer
// Notes		:
// See also		:
//-----------------------------------------------------
sf::SoundBuffer SoundManager::loadSound( const char* fileName )
{
	// Temporary sound variable
	sf::SoundBuffer soundToLoad;

	// Loads the sound from the file and stores the result
	bool loaded = soundToLoad.loadFromFile( fileName );

	// Makes sure loaded is true, stops running the program if it isn't
	ASSERT( loaded );

	// Returns the sound
	return soundToLoad;
}

//-----------------------------------------------------
// Function		: addSoundsToMap
// Purpose		: To add all the loaded sounds and their corresponding name to m_soundsToName
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void SoundManager::addSoundsToMap()
{
	// Reads file that contains a list of all sounds used in the game and then loads each sound that is listed into m_soundsToName
	for( auto it : readFileAsMap( "assets/soundList.txt" ) )
	{
		m_soundsToName[it.first] = loadSound( it.second.c_str() );
	}
}

//-----------------------------------------------------
// Function		: getSound
// Purpose		: To return the sound that coresponds to the given name
// Parameters	: std::string fileName
// Returns		: sf::SoundBuffer&
// Notes		:
// See also		:
//-----------------------------------------------------
sf::SoundBuffer& SoundManager::getSound( std::string name )
{
	return m_soundsToName[name];
}