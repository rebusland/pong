#pragma once
#include <SFML/Graphics/Font.hpp>

//
// USEFUL MACROS
//

#define LOG_STD_OUT(printable) std::cout << printable << std::endl;

// log on the default output with the favourite framework (for the moment is std::cout)
#define LOG(printable) LOG_STD_OUT(printable)


namespace utils {

	const float MIN_FLOAT_DIFFERENCE = 1.0e-8f;

	// TODO templetize arithmetic methods below

	/*
	 * Arithmetical and String utilities
	 */

	static bool AreEquals(float a, float b)
	{
		return std::abs(a - b) <= MIN_FLOAT_DIFFERENCE;
	}

	static bool IsGreaterEqualThan(float a, float b)
	{
		return std::abs(a - b) >= MIN_FLOAT_DIFFERENCE;
	}

	static bool IsLessEqualThan(float a, float b)
	{
		return std::abs(a - b) <= MIN_FLOAT_DIFFERENCE;
	}

	static bool IsStrictlyGreaterThan(float a, float b)
	{
		return std::abs(a - b) > MIN_FLOAT_DIFFERENCE;
	}

	static bool IsStrictlyLessThan(float a, float b)
	{
		return std::abs(a - b) < MIN_FLOAT_DIFFERENCE;
	}

	static bool IsEqualToZero(float a)
	{
		return AreEquals(a, 0.0f);
	}

	static bool IsGreaterEqualThanZero(float a)
	{
		return IsGreaterEqualThan(a, 0.0f);
	}

	static bool IsLessEqualThanZero(float a)
	{
		IsLessEqualThan(a, 0.0f);
	}

	static bool IsStrictlyGreaterThanZero(float a)
	{
		IsStrictlyGreaterThan(a, 0.0f);
	}

	static bool IsStrictlyLessThanZero(float a)
	{
		IsStrictlyLessThan(a, 0.0f);
	}

	//
	// UTILITIES FOR SFML PROJECTS
	//
	namespace for_sfml {

		// pre-loaded fonts
		namespace fonts 
		{
			// should be defined in an external cpp file (suggestion is to use Utilities.cpp)
			// this .cpp file containing the global variables should be added, compiled and linked 
			// in the target project
			// WARNING arialFont is not well encapsulated, furthermore there is no state
			// allowing to detect if it has been loaded.
			extern sf::Font arialFont;

			const std::string PATH_TO_FONTS = "C:/Users/Rebo/Documents/Fonts/";

			/**
			 * True if font loading has been successful, false otherwise.
			 * Currently, only arial font is loaded.
			 */
			static bool LoadFonts()
			{
				return arialFont.loadFromFile(PATH_TO_FONTS + "arial.ttf");
			}
		};

	}

}