#ifndef HELPERS_H
#define HELPERS_H

#include <cassert>
#include <map>
#include <string>

// Templated function to delete pointers safely to cut down on the amount of times this code needs to be written
template<typename T>
void safeDelete( T*& pointer )
{
	// Checks if the pointer is null or not
	if( pointer )
	{
		// Deletes the pointer
		delete pointer;

		// Sets the pointer to null
		pointer = nullptr;
	}
}

// Templated function to delete arrays from the heap safely to cut down on the amount of times 
// this code needs to be written
template<typename T>
void safeDeleteArray( T*& arrayPointer )
{
	// Checks if the array is null or not
	if( arrayPointer )
	{
		// Deletes the array
		delete [] arrayPointer;

		// Sets the pointer to the start of the array to null
		arrayPointer = nullptr;
	}
}

// Templated function to swap 2 values
template<typename T>
void swap( T& value1, T& value2 )
{
	T temp = value1;
	value1 = value2;
	value2 = temp;
}

// Add together 2 given strings and returns the result
std::string addStrings( std::string string1, std::string string2 );

// Converts a passed in integer to a string
std::string convertIntToString( int integerToConvert );

// Generates a seed based on the current system time so that rand() returns different values on each playthrough
void generateSeed();

// Generates a random float between 0 and 1
float generateRandom();

// Reads a given file and returns it as a map
std::map<std::string, std::string> readFileAsMap( const char* fileName );

// Writes a given map into a given file
void writeMapToFile( const char* fileName, std::map<std::string, std::string>& mapToWrite );

// Macro to use assert in debug mode but make it disappear in Release mode
#ifdef _DEBUG
	#define ASSERT( a ) assert( a )
#else
	#define ASSERT( a ) 
#endif // _DEBUG


#endif // !HELPERS_H
