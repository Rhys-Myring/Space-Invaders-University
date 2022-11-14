#ifndef CONFIGSETTINGSMANAGER_H
#define CONFIGSETTINGSMANAGER_H

//-----------------------------------------------------
// Class	:	ConfigSettingsManager
// Purpose	:	To manage the player's config settings
// Usage	:	ConfigSettingsManager configSettingsManager;
//				configSettingsManager.getMuted()
// See also	:	
//-----------------------------------------------------
class ConfigSettingsManager
{
private:
	bool m_isFullScreen;		// Stores whether the full screen option was enabled in the settings
	bool m_isMuted;				// Stores whether the sound was muted in the settings
	bool m_haveSettingsChanged;	// Stores whether any of the settings have been changed

	// Read all of the player's settings from the config text file
	void readSettings();

	// Writes all of the player's settings to the config text file
	void writeSettings();

public:
	// Constructor
	ConfigSettingsManager();

	// Destructor
	~ConfigSettingsManager();

	// Getters and Setters
	const bool getFullScreen() const;
	void setFullScreen( bool fullScreen );

	const bool getMuted() const;
	const void setMuted( bool muted );
};

#endif // !CONFIGSETTINGSMANAGER_H
