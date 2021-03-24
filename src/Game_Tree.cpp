#include "Game_Tree.h"

std::vector<int> Game_Tree::_finalPath;
bool Game_Tree::_finalPathComplete = false;

Game_Tree::Game_Tree(unsigned int width, unsigned int height) : _depth(0) {
	_root = std::make_shared<Game_Tree_Node>(std::make_shared<Board_Representation>(width, height), true);
}

void Game_Tree::GenerateGameTree(std::shared_ptr<Game_Tree_Node> node, bool whiteTurn, unsigned int depth) {	
	if (depth == 0 || EndGameCheck(node->GetBoardSituation(), whiteTurn))
		node->EvaluateSituation(EvaluateBoard(node->GetBoardSituation(), whiteTurn));
	else {
		std::vector<std::pair<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>>> moves;
		moves = GenerateLegitMoves(node->GetBoardSituation(), whiteTurn);
		for (int it = 0; it < moves.size(); it++) {
			std::shared_ptr<Board_Representation> tempSituation = std::make_shared<Board_Representation>(*node->GetBoardSituation());
			if (whiteTurn) {
				tempSituation->SetPlateFill(moves.at(it).second.second, moves.at(it).second.first, 1);
				tempSituation->SetPlateFill(moves.at(it).first.second, moves.at(it).first.first, 0);
			}
			else {
				tempSituation->SetPlateFill(moves.at(it).second.second, moves.at(it).second.first, -1);
				tempSituation->SetPlateFill(moves.at(it).first.second, moves.at(it).first.first, 0);
			}
			node->AddBranch(tempSituation, !whiteTurn);
		}

		for (int it = 0; it < node->GetChildrenCount(); it++) {
			GenerateGameTree(node->GetChild(it), !whiteTurn, depth - 1);
		}
	}
}

void Game_Tree::MinMaxAlgorithm(std::shared_ptr<Game_Tree_Node> node, bool max) {
	if (node->GetChildrenCount() != 0) {
		bool noFurtherChilds = true;
		for (int it = 0; it < node->GetChildrenCount(); it++) {
			if (node->GetChild(it)->GetChildrenCount() != 0) {
				noFurtherChilds = false;
				break;
			}
		}

		if (noFurtherChilds) {
			std::pair<float, int> choice = std::make_pair(node->GetChild(0)->GetEvaluationValue(), 0);
			for (int it = 1; it < node->GetChildrenCount(); it++) {
				if (max && node->GetChild(it)->GetEvaluationValue() > choice.first)
					choice = std::make_pair(node->GetChild(it)->GetEvaluationValue(), it);
				else if (!max && node->GetChild(it)->GetEvaluationValue() < choice.first)
					choice = std::make_pair(node->GetChild(it)->GetEvaluationValue(), it);
			}
			node->EvaluateSituation(choice.second);
		}
		else {
			for (int it = 0; it < node->GetChildrenCount(); it++) {
				if (node->GetChild(it)->GetChildrenCount() != 0)
					MinMaxAlgorithm(node->GetChild(it), !max);
			}
		}
	}
}

void Game_Tree::FindPath(std::shared_ptr<Game_Tree_Node> node) {
	if (node->GetChildrenCount() == 0) {
		if(EndGameCheck(node->GetBoardSituation(), node->GetPlayerTurn()))
			_finalPathComplete = true;
		else if (GenerateLegitMoves(node->GetBoardSituation(), !node->GetPlayerTurn()).size() != 0) {
			_finalPathComplete = false;
			ClearTree(node);
		}
		else
			_finalPathComplete = true;
	}
	else {
		_finalPath.emplace_back(node->GetEvaluationValue());
		FindPath(node->GetChild(static_cast<int>(node->GetEvaluationValue())));
	}
}

void Game_Tree::ClearTree(std::shared_ptr<Game_Tree_Node> newRoot) {
	_root->ClearBranches();
	_root = newRoot;
	_root->ClearBranches();
}