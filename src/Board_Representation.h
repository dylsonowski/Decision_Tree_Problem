#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <utility>

class Board_Representation {

public:
	Board_Representation() = delete;
	Board_Representation(unsigned int width = 3, unsigned int height = 3);
	~Board_Representation() = default;

	void GenerateBoard(unsigned int width, unsigned int height);
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

static std::vector<std::pair<unsigned int, unsigned int>> GenerateLegitMoves(std::shared_ptr<Board_Representation> board, bool whiteTurn) {
	std::vector<std::pair<unsigned int, unsigned int>> temp;
	for (int y = 0; y < board->GetHeigh(); y++) {
		for (int x = 0; x < board->GetWidth(); x++) {
			if (whiteTurn && board->GetPlateFill(x, y) > 0) {
				if (y + 1 < board->GetHeigh() && board->GetPlateFill(x, y + 1) == 0)
					temp.emplace_back(std::make_pair(x, y + 1));

				if (x - 1 >= 0 && y + 1 < board->GetHeigh() && board->GetPlateFill(x - 1, y + 1) == -1)
					temp.emplace_back(std::make_pair(x - 1, y + 1));

				if (x + 1 < board->GetWidth() && y + 1 < board->GetHeigh() && board->GetPlateFill(x + 1, y + 1) == -1)
					temp.emplace_back(std::make_pair(x + 1, y + 1));
			}
			else if (!whiteTurn && board->GetPlateFill(x, y) < 0) {
				if (y - 1 >= 0 && board->GetPlateFill(x, y - 1) == 0)
					temp.emplace_back(std::make_pair(x, y - 1));

				if (x - 1 >= 0 && y - 1 >= 0 && board->GetPlateFill(x - 1, y - 1) == 1)
					temp.emplace_back(std::make_pair(x - 1, y - 1));

				if (x + 1 < board->GetWidth() && y - 1 >= 0 && board->GetPlateFill(x + 1, y - 1) == 1)
					temp.emplace_back(std::make_pair(x + 1, y - 1));
			}
		}
	}
	return temp;
}

static double EvaluateBoard(std::shared_ptr<Board_Representation> board) {} //todo: Create evaluation function.