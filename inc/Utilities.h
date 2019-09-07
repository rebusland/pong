#pragma once
#include <SFML/Graphics/Font.hpp>

//
// USEFUL MACROS
//

#define LOG_STD_OUT(printable) std::cout << printable << std::endl;

// log on the default output with the favourite framework (for the moment is std::cout)
#define LOG(printable) LOG_STD_OUT(printable)


namespace utils {

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