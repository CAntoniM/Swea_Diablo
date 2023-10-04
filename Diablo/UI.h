#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Enemy.h"
#include "Enums.h"
#include "Door.h"
#include "Room.h"
#include "Items.h"

class Room;
class Door;

std::string ItemTypeToString(ItemType aItem);
void DrawFrame();
void MenuControll(std::string aMenuList[], int aMenuSize, int& aPlayerChoiseInMenu, int aStartingYPosision);
int showItems(std::vector<Items> aListOfItems);
void PrintDoorSprite(int aStartX, int aStartY, bool aTarget, bool aRoomExplored, std::string aRoomName);
void ShowEnemy(std::vector<Enemy>& aList);
int ShowDoors(std::vector<std::shared_ptr<Door>> aVectorOfDoors, std::vector<Room>& aVectorOfRooms, int aCurrentRoom);
int ChoseEnemy(std::vector<Enemy>& aList);