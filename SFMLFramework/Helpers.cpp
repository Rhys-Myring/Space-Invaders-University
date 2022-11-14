#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>

#include "Helpers.h"

//-----------------------------------------------------
// Function		: addStrings
// Purpose		: To add together 2 given strings and return the result
// Parameters	: std::string string1, std::string string2
// Returns		: std::string
// Notes		:
// See also		:
//-----------------------------------------------------
std::string addStrings( std::string string1, std::string string2 )
{
	// Adds the strings together
	std::string combinedString = string1 + string2;

	// Returns the combined string
	return combinedString;
}

//-----------------------------------------------------
// Function		: convertIntToString
// Purpose		: To convert a passed in integer to a string
// Parameters	: int integerToConvert
// Returns		: std::string
// Notes		:
// See also		:
//-----------------------------------------------------
std::string convertIntToString( int integerToConvert )
{
	// Creates string stream to add integer to
	std::stringstream convertedInteger;

	// Adds integer to the string stream
	convertedInteger << integerToConvert;

	// Returns the string stream as a string
	return convertedInteger.str();
}

//-----------------------------------------------------
// Function		: generateSeed
// Purpose		: To generate a seed based on the current system time so that rand() returns different values on each playthrough
// Parameters	: None
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void generateSeed()
{
	// Passes elapsed time since 1970 into srand to generate more random numbers from rand()
	srand( static_cast<int>( std::chrono::system_clock::now().time_since_epoch().count() ) );
}

//-----------------------------------------------------
// Function		: generateRandom
// Purpose		: To generate a random float between 0 and 1
// Parameters	: None
// Returns		: float
// Notes		:
// See also		:
//-----------------------------------------------------
float generateRandom()
{
	return static_cast<float>( rand() ) / static_cast<float>( RAND_MAX );
}

//-----------------------------------------------------
// Function		: readFileAsMap
// Purpose		: To read a given file and return it as a map
// Parameters	: const char* fileName
// Returns		: std::map<std::string, std::string>
// Notes		:
// See also		:
//-----------------------------------------------------
std::map<std::string, std::string> readFileAsMap( const char* fileName )
{
	// Variable to store the file stream
	std::ifstream fileStream;

	// Stores the current line
	std::string currentLine;

	// Map to return
	std::map<std::string, std::string> mapToStoreIn;

	// Opens up the file
	fileStream.open( fileName );

	// Checks if the file is open
	if( fileStream.is_open() )
	{
		// File opened for reading successfully

		// Reads in all lines from the file
		while( std::getline( fileStream, currentLine ) )
		{
			// Splits current line into the key and value
			std::string stringSplitter = ",";
			std::string key = currentLine.substr( 0, currentLine.find( stringSplitter ) );
			std::string value = currentLine.substr( currentLine.find( stringSplitter ) + 1, currentLine.length() );

			// Adds key and value to given map
			mapToStoreIn[key] = value;
		}

		// Closes the file
		fileStream.close();
	}
	
	return mapToStoreIn;
}

//-----------------------------------------------------
// Function		: writeMapToFile
// Purpose		: To write a given map into a given file
// Parameters	: const char* fileName, std::map<std::string, std::string>& mapToWrite
// Returns		: void
// Notes		:
// See also		:
//-----------------------------------------------------
void writeMapToFile( const char* fileName, std::map<std::string, std::string>& mapToWrite )
{
	// File output stream
	std::ofstream fileStream;

	// Creates new file
	fileStream.open( fileName );

	// Checks if the file is open
	if( fileStream.is_open() )
	{
		// Iterates through the map and writes each key and value pair to the file with a comma between them
		for( auto it : mapToWrite )
		{
			fileStream << it.first;
			fileStream << ",";
			fileStream << it.second;
			fileStream << "\n";
		}

		// Closes the file
		fileStream.close();
	}
}
