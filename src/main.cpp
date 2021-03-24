#include "Game_Tree.h"
#include "Board_Representation.h"

int main(int argc, char** argv) {
	unsigned int w = 3, h = 3, depth;
	bool depthInitialized = false;
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			if (static_cast<std::string>(argv[i]) == "-w")
				w = std::stoi(argv[i + 1]);

			if(static_cast<std::string>(argv[i]) == "-h")
				h = std::stoi(argv[i + 1]);

			if (static_cast<std::string>(argv[i]) == "-d") {
				depth = std::stoi(argv[i + 1]);
				depthInitialized = true;
			}
		}
	}

	if ((w > 4 || h > 4) && !depthInitialized)
		depth = 3;
	else if ((w <= 4 || h <= 4) && !depthInitialized)
		depth = 5;

	Game_Tree gameTree(w, h);
	gameTree.SetDepth(depth);	

	while (!gameTree.IsFinalPathComplete()) {
		gameTree.GenerateGameTree(gameTree.GetRoot(), true, gameTree.GetDepth());
		gameTree.MinMaxAlgorithm(gameTree.GetRoot(), true);
		gameTree.FindPath(gameTree.GetRoot());
	}

	for (int it = 0; it < gameTree.GetFinalPath().size(); it++) {
		std::cout << gameTree.GetFinalPath().at(it) << " -> ";
	}
	std::cout << "END\n";
	system("pause");
	return 0;
}