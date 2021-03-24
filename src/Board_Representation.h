#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <utility>

class Board_Representation {

public:
	static std::vector<std::vector<float>> evaluationTableP1, evaluationTableP2;

	Board_Representation() = delete;
	Board_Representation(unsigned int width = 3, unsigned int height = 3);
	~Board_Representation() = default;

	void GenerateBoard(unsigned int width, unsigned int height);
	void GenerateEvaluationTables(unsigned int width, unsigned int height);
	void SetPlateFill(unsigned int x, unsigned int y, int value) { 
		if(x < _width && y < _height)
			_board.at(y).at(x) = value; 
	}

	inline unsigned int GetWidth() const { return _width; }
	inline unsigned int GetHeigh() const { return _height; }
	inline int GetPlateFill(unsigned int x, unsigned int y) const { 
		if (x < _width && y < _height)
			return _board.at(y).at(x);
	}
	std::string ToString() const {
		std::stringstream ss;			
		for (int y = 0; y < _height; y++) {
			for (int x = 0; x < _width; x++) {
				if(_board.at(y).at(x) < 0)
					ss << "|" << _board.at(y).at(x) << " ";
				else
					ss << "| " << _board.at(y).at(x) << " ";
			}
			ss << "|\n";
		}
		return ss.str();
	}	

private:
	unsigned int _width, _height;
	std::vector<std::vector<int>> _board;
};

inline std::ostream& operator<<(std::ostream& os, const Board_Representation& data) {
	return os << data.ToString();
}

static std::vector<std::pair<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>>> GenerateLegitMoves(
	std::shared_ptr<Board_Representation> board, bool whiteTurn) {
	std::vector<std::pair<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>>> temp;
	for (int y = 0; y < board->GetHeigh(); y++) {
		for (int x = 0; x < board->GetWidth(); x++) {
			if (whiteTurn && board->GetPlateFill(x, y) > 0) {				
				if (y + 1 < board->GetHeigh() && board->GetPlateFill(x, y + 1) == 0)
					temp.emplace_back(std::make_pair(std::make_pair(y, x), std::make_pair(y + 1, x)));

				if (x - 1 >= 0 && y + 1 < board->GetHeigh() && board->GetPlateFill(x - 1, y + 1) == -1)
					temp.emplace_back(std::make_pair(std::make_pair(y, x), std::make_pair(y + 1, x - 1)));

				if (x + 1 < board->GetWidth() && y + 1 < board->GetHeigh() && board->GetPlateFill(x + 1, y + 1) == -1)
					temp.emplace_back(std::make_pair(std::make_pair(y, x), std::make_pair(y + 1, x + 1)));
			}
			else if (!whiteTurn && board->GetPlateFill(x, y) < 0) {
				if (y - 1 >= 0 && board->GetPlateFill(x, y - 1) == 0)
					temp.emplace_back(std::make_pair(std::make_pair(y, x), std::make_pair(y - 1, x)));

				if (x - 1 >= 0 && y - 1 >= 0 && board->GetPlateFill(x - 1, y - 1) == 1)
					temp.emplace_back(std::make_pair(std::make_pair(y, x), std::make_pair(y - 1, x - 1)));

				if (x + 1 < board->GetWidth() && y - 1 >= 0 && board->GetPlateFill(x + 1, y - 1) == 1)
					temp.emplace_back(std::make_pair(std::make_pair(y, x), std::make_pair(y - 1, x + 1)));
			}
		}
	}
	return temp;
}

static bool EndGameCheck(std::shared_ptr<Board_Representation> board, bool whiteTurn) {
	bool end = false;
	int whiteCount = 0, blackCount = 0;
	for (int y = 0; y < board->GetHeigh(); y++) {
		for (int x = 0; x < board->GetWidth(); x++) {
			if (board->GetPlateFill(x, board->GetHeigh() - 1) == 1 || board->GetPlateFill(x, 0) == -1)
				end = true;

			if (board->GetPlateFill(x, y) == 1)
				whiteCount++;

			if (board->GetPlateFill(x, y) == -1)
				blackCount++;
		}
	}

	if (whiteCount == 0 || blackCount == 0)
		end = true;

	if (GenerateLegitMoves(board, whiteTurn).size() == 0)
		end = true;

	return end;
}

static double EvaluateBoard(std::shared_ptr<Board_Representation> board, bool whiteTurn) {
	double pieceValueP1 = 0, pieceValueP2 = 0;
	for (int y = 0; y < board->GetHeigh(); y++) {
		for (int x = 0; x < board->GetWidth(); x++) {
			if (board->GetPlateFill(x, y) == 1)
				pieceValueP1 += 1 + Board_Representation::evaluationTableP1.at(y).at(x);
			else if (board->GetPlateFill(x, y) == -1)
				pieceValueP2 += -1 - Board_Representation::evaluationTableP2.at(y).at(x);
		}
	}

	if (whiteTurn && EndGameCheck(board, whiteTurn))
		pieceValueP2 += -5;
	else if (!whiteTurn && EndGameCheck(board, whiteTurn))
		pieceValueP1 += 5;

	return pieceValueP1 + pieceValueP2;
}