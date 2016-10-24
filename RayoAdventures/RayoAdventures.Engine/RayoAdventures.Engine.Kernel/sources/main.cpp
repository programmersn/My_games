///////////////////////////////////////////////////////////////////////////////
/// \file main.cpp
/// \author Nouaïm SOUIKI
/// \email souiki.nouaim@yahoo.fr
///
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "ker/Kernel.h"
#include "core/Singleton.h"

int
main ()
{
	try {
      engn::ker::Kernel & kern = engn::ker::Kernel::getInstance();
      kern.run();
      std::cout << "Exiting try block...\n";
   } catch (std::runtime_error& e) {
		std::cerr << "[[GAME_ERROR]]--main: runtime error handled from:\n" 
                << e.what();
	} catch (std::exception& e) {
      std::cerr << "[[GAME_ERROR]]--main: unknown exception handled from:\n" 
                << e.what();
	}

   std::cout << "Exiting main function ...\n";
   getchar();
   return EXIT_SUCCESS;
}
