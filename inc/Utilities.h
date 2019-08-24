#pragma once

//
// USEFUL MACROS
//

#define LOG_STD_OUT(printable) std::cout << printable << std::endl;

// log on the default output with the favourite framework (for the moment is std::cout)
#define LOG(printable) LOG_STD_OUT(printable)