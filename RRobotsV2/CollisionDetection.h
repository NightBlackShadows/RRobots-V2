//
// Created by shade on 3/18/19.
//

#ifndef RROBOTSV2_COLLISIONDETECTION_H
#define RROBOTSV2_COLLISIONDETECTION_H

#include <vector>
#include <SDL_rect.h>
#include "WayType.h"
#include "Character.h"
#include "Marker.h"

class CollisionDetection {
public:
    CollisionDetection();
    bool MarkerCollision(Character &character, Marker &marker);
    bool PossibleMovement(int x,int y, WayType wayType,std::vector<std::vector<int>> gameBoard,std::vector<std::vector<int>> entityBoard);
    SDL_Rect MoveCharacter(Character &character, WayType way,std::vector<std::vector<int>> gameBoard,std::vector<std::vector<int>> entityBoard);
    ~CollisionDetection();
private:
    bool CheckLeft(int x,int y,std::vector<std::vector<int>> gameBoard,std::vector<std::vector<int>> entityBoard);
    bool CheckRight(int x,int y,std::vector<std::vector<int>> gameBoard,std::vector<std::vector<int>> entityBoard);
    bool CheckUp(int x,int y,std::vector<std::vector<int>> gameBoard,std::vector<std::vector<int>> entityBoard);
    bool CheckDown(int x,int y,std::vector<std::vector<int>> gameBoard,std::vector<std::vector<int>> entityBoard);
};


#endif //RROBOTSV2_COLLISIONDETECTION_H
