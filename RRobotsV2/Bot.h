#pragma once
#include <vector>
#include <queue>
#include "LinkedList.h"
#include "WayType.h"
#include "Marker.h"
#include "CollisionDetection.h"

class Bot{
    public:
    Bot(int difficulty);
    int FindSolution(Marker marker, std::vector<std::vector<int>> gameBoard,std::vector<std::vector<int>> entityBoard);
    std::vector<WayType> getSolution();
    ~Bot();



    private:
    class pos{

    public:
        int x, y;
        pos(int xPos, int yPos){
            x = xPos;
            y = yPos;
        }
    };
    std::queue<std::pair<ColorType,WayType>> queue;
    int ColorInt(ColorType character);
    pos* FindPos(int character, std::vector<std::vector<int>> entityBoard);
    int difficulty;
    int FindSolutionEasy(ColorType character,Marker marker, std::vector<std::vector<int>> entityBoard, std::vector<std::vector<int>> gameBoard);
    int FindSolutionMedium(ColorType character,Marker marker, std::vector<std::vector<int>> entityBoard, std::vector<std::vector<int>> gameBoard);
    int FindSolutionHard(ColorType character,Marker marker, std::vector<std::vector<int>> entityBoard, std::vector<std::vector<int>> gameBoard);
    std::vector<std::vector<int>> gameBoard;
    std::vector<WayType> moves;
    std::vector<WayType> bestMoves;
    CollisionDetection cd;
};

