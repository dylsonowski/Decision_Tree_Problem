#pragma once
#include "Board_Representation.h"

class Game_Tree_Node;

class Game_Tree {

public:
	static std::vector<int> _finalPath;
	static bool _finalPathComplete;

	Game_Tree() = delete;
	Game_Tree(unsigned int width, unsigned int height);
	~Game_Tree() = default;

	void GenerateGameTree(std::shared_ptr<Game_Tree_Node> node, bool whiteTurn, unsigned int depth);
	void SetDepth(unsigned int depth) { _depth = depth; }
	void ClearTree(std::shared_ptr<Game_Tree_Node> newRoot);

	void MinMaxAlgorithm(std::shared_ptr<Game_Tree_Node> node, bool max);
	void FindPath(std::shared_ptr<Game_Tree_Node> node);

	inline std::shared_ptr<Game_Tree_Node> GetRoot() const { return _root; }
	inline unsigned int GetDepth() const { return _depth; }
	inline std::vector<int> GetFinalPath() const { return _finalPath; }
	inline bool IsFinalPathComplete() const { return _finalPathComplete; }

private:
	std::shared_ptr<Game_Tree_Node> _root;
	unsigned int _depth;
};

class Game_Tree_Node {

public:
	Game_Tree_Node() = delete;
	Game_Tree_Node(std::shared_ptr<Board_Representation> board, bool whiteTurn) : _boardSituation(board), _evaluationValue(0), _whiteTurn(whiteTurn) {}
	~Game_Tree_Node() = default;

	void EvaluateSituation(double value) { _evaluationValue = value; }
	void AddBranch(std::shared_ptr<Board_Representation> board, bool whiteTurn) { _childs.emplace_back(std::make_shared<Game_Tree_Node>(board, whiteTurn)); }
	void RemoveBranch(std::vector<std::shared_ptr<Game_Tree_Node>>::iterator iterator) { _childs.erase(iterator); }
	void ClearBranches() { _childs.clear(); }

	inline double GetEvaluationValue() const { return _evaluationValue; }
	inline int GetChildrenCount() const { return _childs.size(); }
	inline std::shared_ptr<Board_Representation> GetBoardSituation() const { return _boardSituation; }
	inline std::shared_ptr<Game_Tree_Node> GetChild(unsigned int iterator) const { return _childs.at(iterator); }
	inline bool GetPlayerTurn() const { return _whiteTurn; }

private:
	std::shared_ptr<Board_Representation> _boardSituation;
	bool _whiteTurn;
	double _evaluationValue;
	std::vector<std::shared_ptr<Game_Tree_Node>> _childs;
};