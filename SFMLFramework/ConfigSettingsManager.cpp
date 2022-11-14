#include "ConfigSettingsManager.h"
#include "Helpers.h"

// Constructor
ConfigSettingsManager::ConfigSettingsManager()
	: m_isFullScreen( false )
	, m_isMuted( false )
	, m_haveSettingsChanged( false )
{
	// Reads settings from text file, stores them in m_isFullScreen and m_isMuted
	readSettings();
}

// Destructor
ConfigSettingsManager::~ConfigSettingsManager()
{
	// If there has been any changes to the settings, then the changes are written to the file
	if( m_haveSettingsChanged )
	{
		// Writes all the settings to the config file
		writeSettings();
	}
}

// Getters and Setters
const bool ConfigSettingsManager::getFullScreen() const
{
	return m_isFullScreen;
}

void ConfigSettingsManager::setFullScreen( bool fullScreen )
{
	m_isFullScreen = fullScreen;
	m_haveSettingsChanged = true;
}

const bool ConfigSettingsManager::getMuted() const
{
	return m_isMuted;
}

const void ConfigSettingsManager::setMuted( bool muted )
{
	m_isMuted = muted;
	m_haveSettingsChanged = true;
}


//-----------------------------------------------------
// Function		: readSettings
// Purpose		: To read all of the settings from the config text file
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void ConfigSettingsManager::readSettings()
{
	// Reads all the settings from the file and assigns them to their respective bools
	for( auto it : readFileAsMap( "config.txt" ) )
	{
		if( it.first == "Muted" )
		{
			m_isMuted = std::stoi( it.second );
		}
		else if( it.first == "FullScreen" )
		{
			m_isFullScreen = std::stoi( it.second );
		}
	}
}

//-----------------------------------------------------
// Function		: writeSettings
// Purpose		: To write all the settings to the config text file
// Parameters	: None
// Returns		: void
// Notes		: 
// See also		:
//-----------------------------------------------------
void ConfigSettingsManager::writeSettings()
{
	// Variable to store the map file that is to be written 
	std::map<std::string, std::string> mapToWrite;

	// Adds all the settings to the map
	mapToWrite["Muted"] = convertIntToString( m_isMuted );
	mapToWrite["FullScreen"] = convertIntToString( m_isFullScreen );

	// Writes the settings to the config file
	writeMapToFile( "config.txt", mapToWrite );
}
