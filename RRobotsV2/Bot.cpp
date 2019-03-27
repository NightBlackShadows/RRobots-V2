#include "Bot.h"
#include "ColorType.h"
#include "CollisionDetection.h"

Bot::Bot(int difficulty){
    moves = std::vector<WayType>();
    bestMoves = std::vector<WayType>();
}

int Bot::FindSolution(Marker marker, std::vector<std::vector<int>> gameBoard, std::vector<std::vector<int>> entityBoard) {
    this->gameBoard = gameBoard;
    switch(difficulty){
        case 0:
            return FindSolutionEasy(ColorType::BLACK,marker,entityBoard,gameBoard);
        case 1:
            return FindSolutionMedium(ColorType::BLACK,marker,entityBoard,gameBoard);
        default:
            return FindSolutionHard(ColorType::BLACK,marker,entityBoard,gameBoard);
    }
}

Bot::~Bot() {
}

std::vector<WayType> Bot::getSolution() {
    return moves;
}

int Bot::FindSolutionEasy(ColorType character,Marker marker, std::vector<std::vector<int>> entityBoard, std::vector<std::vector<int>> gameBoard) {
    if(moves.size() >= 40)
        return -1;
    if(marker.getColor() == character)
        return moves.size();
    return moves.size();
}

int Bot::FindSolutionMedium(ColorType character,Marker marker, std::vector<std::vector<int>> entityBoard, std::vector<std::vector<int>> gameBoard) {
    if(moves.size() >= 40)
        return -1;
    if(marker.getColor() == character)
        return moves.size();
    return moves.size();
}

int Bot::FindSolutionHard(ColorType character,Marker marker, std::vector<std::vector<int>> entityBoard, std::vector<std::vector<int>> gameBoard) {
    if(moves.size() >= 40)
        return -1;
    Bot::pos* posChar = FindPos(ColorInt(character),entityBoard);
    if(marker.getColor() == character && marker.getMapXPos() == posChar->x && marker.getMapYPos() == posChar->y)
        return moves.size();
    int up, down, left, right;



    return moves.size();
}

int Bot::ColorInt(ColorType character){
    switch (character){
        case ColorType::GREEN:
            return 2;
        case ColorType::BLUE:
            return 3;
        case ColorType::BLACK:
            return 4;
        case ColorType::RED:
            return 5;
        case ColorType::YELLOW:
            return 6;
    }
}

Bot::pos* Bot::FindPos(int character, std::vector<std::vector<int>> entityBoard){
    for(int y = 0; y < 18;y++){
        for(int x = 0; x < 18; x++){
            if(entityBoard.at(y).at(x) == character){
                return new pos(x,y);
            }
        }
    }
}