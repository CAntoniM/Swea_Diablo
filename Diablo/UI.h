#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Enemy.h"
#include "Enums.h"
#include "Door.h"
#include "Room.h"
#include "Item.h"

namespace ui {
	void Clear();
	void Pause();
	void Print(std::string aString);
	void PrintInMenu(std::string aString);
	void ClearArea(int anX, int anY, int aXLength, int aYLength = 1);
	void ClearGameView();
	void ClearMenu();
	void SetColor(ColorInt aColor);
	void SetCursorPosition(int aX, int aY);
	void SetCursorVisibility(bool aSetCursor);	
	MenuOptions ButtonPress();
	void DrawFrame();
	void MenuControll(std::string aMenuList[], int aMenuSize, int& aPlayerChoiseInMenu, int aStartingYPosision);
	int showItems(std::vector<std::shared_ptr<Item>> aListOfItems, int& playerChoiseInMenu);
	void PrintDoorSprite(int aStartX, int aStartY, bool aTarget, bool aRoomExplored, std::string aRoomName);
	void ShowEnemy(std::vector<Enemy>& aList);
	int ShowDoors(std::vector<std::shared_ptr<Door>> aVectorOfDoors, std::vector<Room>& aVectorOfRooms, int aCurrentRoom);
	int ChoseEnemy(std::vector<Enemy>& aList);
}
