#pragma once
#include <string>
#include <vector>
#include "Enemy.h"
#include "Door.h"
#include "Room.h"

class Room;
class Door;

void DrawFrame();
void MenuControll(std::string aMenuList[], int aMenuSize, int& aPlayerChoiseInMenu, int aStartingYPosision);
int ShowDoors(std::vector<Door>& aVectorOfDoors, std::vector<Room>& aVectorOfRooms, int aCurrentRoom);
void PrintDoorSprite(int aStartX, int aStartY, bool aTarget, bool aRoomExplored, std::string aRoomName);
void ShowEnemy(std::vector<Enemy>& aList);
int ChoseEnemy(std::vector<Enemy>& aList);



