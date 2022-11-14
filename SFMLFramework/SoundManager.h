#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <map>

//-----------------------------------------------------
// Class	:	SoundManager
// Purpose	:	To store all the sounds used by the game
// Usage	:	SoundManager soundManager;
//				soundManager.getSound( "name" )
// See also	:	
//-----------------------------------------------------
class SoundManager
{
private:
	std::map<std::string, sf::SoundBuffer> m_soundsToName; // Stores all the sound buffers and their corresponding names

	// Loads a sound from a given filename
	sf::SoundBuffer loadSound( const char* fileName );

	// Adds all the sounds to the map
	void addSoundsToMap();

public:
	// Constructor
	SoundManager();

	// Destructor
	~SoundManager();

	// Returns the sound that coresponds to the given name
	sf::SoundBuffer& getSound( std::string name );
};

#endif // !SOUNDMANAGER_H