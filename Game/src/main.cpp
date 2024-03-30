// Use discrete GPU by default.
//#if defined(_WIN32) || defined(_WIN64)
//extern "C" {
//	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
//	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
//}
//#endif


#include "Game.hpp"
#include "Constants.hpp"

#include <memory>

int main(int argc, char* argv[]) {

	std::unique_ptr<Game> game = std::make_unique<Game>(winWidth, winHeight, "Exercise Game Using Motion Detection");

	game->run();

	return 0;
}