#include <optional>
#include "Board_Representation.h"

int main(int argc, char** argv) {
	unsigned int w = 3, h = 3;
	std::optional<unsigned int> depth;
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			if (static_cast<std::string>(argv[i]) == "-w")
				w = std::stoi(argv[i + 1]);

			if(static_cast<std::string>(argv[i]) == "-h")
				h = std::stoi(argv[i + 1]);

			if(static_cast<std::string>(argv[i]) == "-d")
				depth = std::stoi(argv[i + 1]);
		}
	}

	Board_Representation board(w, h);
	if ((w > 4 || h > 4) && !depth)
		depth = 3;
	else if ((w <= 4 || h <= 4) && !depth)
		depth = 5;

	board.SetPlateFill(1, 1, 1);
	board.SetPlateFill(1, 0, 0);
	std::vector<std::pair<unsigned int, unsigned int>> moves = GenerateLegitMoves(std::make_shared<Board_Representation>(board), false);

	std::cout << board << "\n";
	system("pause");
	return 0;
}