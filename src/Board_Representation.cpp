#include "Board_Representation.h"

Board_Representation::Board_Representation(unsigned int width, unsigned int height) : _width(width), _height(height) {
	GenerateBoard(width, height);
}

void Board_Representation::GenerateBoard(unsigned int width, unsigned int height) {
	for (int y = 0; y < height; y++) {
		std::vector<int> temp;
		for (int x = 0; x < width; x++) {
			if (y == 0)
				temp.emplace_back(1);
			else if (y == height - 1)
				temp.emplace_back(-1);
			else
				temp.emplace_back(0);
		}
		_board.emplace_back(temp);
	}
}
