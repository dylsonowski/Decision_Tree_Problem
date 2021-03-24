#include "Board_Representation.h"

std::vector<std::vector<float>> Board_Representation::evaluationTableP1, Board_Representation::evaluationTableP2;

Board_Representation::Board_Representation(unsigned int width, unsigned int height) : _width(width), _height(height) {
	GenerateBoard(width, height);
	GenerateEvaluationTables(width, height);
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

void Board_Representation::GenerateEvaluationTables(unsigned int width, unsigned int height) {
	float valueP1 = 0.1f, valueP2 = 0.1f + ((height - 1) * 0.2f);	
	for (int y = 0; y < height; y++) {
		std::vector<float> tempP1, tempP2;
		for (int x = 0; x < width; x++) {
			tempP1.emplace_back(valueP1);
			tempP2.emplace_back(valueP2);
		}
		evaluationTableP1.emplace_back(tempP1);
		evaluationTableP2.emplace_back(tempP2);
		valueP1 += 0.2f;
		valueP2 -= 0.2f;
	}
}
