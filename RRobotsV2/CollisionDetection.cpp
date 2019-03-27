//
// Created by shade on 3/18/19.
//

#include <SDL_rect.h>
#include "CollisionDetection.h"

CollisionDetection::CollisionDetection() {

}

//Check if the correct character collides with the marker
bool CollisionDetection::MarkerCollision(Character &character, Marker &marker)
{
    if (character.getMapXPos() == marker.getMapXPos() &&
        character.getMapYPos() == marker.getMapYPos()) {
        if (character.getColor() == marker.getColor()) {
            return true;
        }
    }
    return false;
}

//Detect collision of characters and walls
SDL_Rect CollisionDetection::MoveCharacter(Character &character, WayType way,std::vector<std::vector<int>> gameBoard,std::vector<std::vector<int>> entityBoard)
{
    int x, y;
    y = character.getMapYPos();
    x = character.getMapXPos();
    SDL_Rect newPos;
    switch (way) {
        case WayType::LEFT:
            while ( x > 1 && CheckLeft(x,y,gameBoard,entityBoard)) {
                if (CheckLeft(x,y,gameBoard,entityBoard))
                {
                    if (x != character.getMapXPos() || y != character.getMapYPos()) {
                        entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
                        entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
                        character.setMapX(x);
                    }
                    newPos.x = x * 32;
                    newPos.y = y * 32 - 32;
                    return newPos;
                }
                else {
                }
                x--;
                if (x <= 1) {
                    entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
                    entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
                    character.setMapX(x);
                }
            }
            newPos.x = x * 32;
            newPos.y = y * 32 - 32;
            return newPos;
        case WayType::RIGHT:
            while (x < 16) {
                if (CheckRight(x,y,gameBoard,entityBoard))
                {
                    if (x != character.getMapXPos() || y != character.getMapYPos()) {
                        entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
                        entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
                        character.setMapX(x);
                    }
                    newPos.x = x * 32;
                    newPos.y = y * 32 - 32;
                    return newPos;
                }
                else {
                }
                x++;
                if (x >= 16) {
                    entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
                    entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
                    character.setMapX(x);
                }
            }
            newPos.x = x * 32;
            newPos.y = y * 32 - 32;
            return newPos;
        case WayType::UP:
            while (y > 1) {
                if (CheckUp(x,y,gameBoard,entityBoard))
                {
                    if (x != character.getMapXPos() || y != character.getMapYPos()) {
                        entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
                        entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
                        character.setMapY(y);
                    }
                    newPos.x = x * 32;
                    newPos.y = y * 32 - 32;
                    return newPos;
                }
                else {
                }
                y--;
                if (y <= 1) {
                    entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
                    entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
                    character.setMapY(y);
                }
            }
            newPos.x = x * 32;
            newPos.y = y * 32 - 32;
            return newPos;
        case WayType::DOWN:
            while (y < 16) {
                if (CheckDown(x,y,gameBoard,entityBoard))
                {
                    if (x != character.getMapXPos() || y != character.getMapYPos()) {
                        entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
                        entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
                        character.setMapY(y);
                    }
                    newPos.x = x * 32;
                    newPos.y = y * 32 - 32;
                    return newPos;
                }
                else {
                }
                y++;
                if (y >= 16) {
                    entityBoard[y][x] = entityBoard[character.getMapYPos()][character.getMapXPos()];
                    entityBoard[character.getMapYPos()][character.getMapXPos()] = 0;
                    character.setMapY(y);
                }
            }
            newPos.x = x * 32;
            newPos.y = y * 32 - 32;
            return newPos;
        default:
            return SDL_Rect();
    }
}

CollisionDetection::~CollisionDetection() {

}

bool CollisionDetection::PossibleMovement(int x,int y, WayType wayType,std::vector<std::vector<int>> gameBoard,std::vector<std::vector<int>> entityBoard) {

    switch (wayType) {
        case WayType::LEFT:
            if (CheckLeft(x,y,gameBoard,entityBoard)) {
                return false;
            } else
                return true;
        case WayType::RIGHT:
            if (CheckRight(x,y,gameBoard,entityBoard)) {
                return false;
            } else
                return true;
        case WayType::UP:
            if (CheckUp(x,y,gameBoard,entityBoard)) {
                return false;
            } else
                return true;
        case WayType::DOWN:
            if (CheckDown(x,y,gameBoard,entityBoard)) {
                return false;
            } else
                return true;
        default:
            return false;
    }
}

bool CollisionDetection::CheckLeft(int x,int y,std::vector<std::vector<int>> gameBoard,std::vector<std::vector<int>> entityBoard) {
    return gameBoard[y][x - 1] == 0 || gameBoard[y][x - 0] == 3 ||
           gameBoard[y][x - 1] == 4 || gameBoard[y][x - 0] == 5 ||
           gameBoard[y][x - 0] == 6 || gameBoard[y][x - 1] == 7 ||
           (entityBoard[y][x - 1] >= 2 && entityBoard[y][x - 1] <= 6);
}

bool CollisionDetection::CheckRight(int x,int y,std::vector<std::vector<int>> gameBoard,std::vector<std::vector<int>> entityBoard) {
    return gameBoard[y][x + 1] == 0 || gameBoard[y][x + 1] == 3 ||
           gameBoard[y][x + 0] == 4 || gameBoard[y][x + 1] == 5 ||
           gameBoard[y][x + 1] == 6 || gameBoard[y][x + 0] == 7 ||
           (entityBoard[y][x + 1] >= 2 && entityBoard[y][x + 1] <= 6);
}

bool CollisionDetection::CheckUp(int x,int y,std::vector<std::vector<int>> gameBoard,std::vector<std::vector<int>> entityBoard) {
    return gameBoard[y - 1][x] == 0 ||	gameBoard[y + 0][x] == 2 ||
           gameBoard[y + 0][x] == 4 ||	gameBoard[y + 0][x] == 5 ||
           gameBoard[y - 1][x] == 6 ||	gameBoard[y - 1][x] == 7 ||
           (entityBoard[y - 1][x] >= 2 && entityBoard[y - 1][x] <= 6);
}

bool CollisionDetection::CheckDown(int x,int y,std::vector<std::vector<int>> gameBoard,std::vector<std::vector<int>> entityBoard) {
    return gameBoard[y + 1][x] == 0 ||	gameBoard[y + 1][x] == 2 ||
           gameBoard[y + 1][x] == 4 ||	gameBoard[y + 1][x] == 5 ||
           gameBoard[y + 0][x] == 6 ||	gameBoard[y + 0][x] == 7 ||
           (entityBoard[y + 1][x] >= 2 && entityBoard[y + 1][x] <= 6);
}
