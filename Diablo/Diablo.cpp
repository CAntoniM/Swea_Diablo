
#include <iostream>
#include <memory>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Room.h"
#include "Door.h"
#include "Quick_functions.h"
#include "UI.h"

void AddDoor(int aConnectingRoomOne, int aConnectingRoomTwo, std::vector<std::shared_ptr<Door>>& aListOfDoors)
{
	std::shared_ptr<Door> ptr = std::make_shared<Door>(aConnectingRoomOne, aConnectingRoomTwo);
	aListOfDoors.push_back(ptr);
}

void AddRoom(int aRoomNumber, std::string aRoomType, std::vector<Room>& aListOfRooms, std::vector<std::shared_ptr<Door>>& aListOfDoors)
{
	Room room(aRoomNumber, aRoomType);
	aListOfRooms.push_back(room);
	if (aRoomType == "Start")
	{
		AddDoor(aRoomNumber, aRoomNumber++, aListOfDoors);
	}
	else if (aRoomType == "Normal")
	{
		AddDoor(aRoomNumber, aRoomNumber++, aListOfDoors);
	}
}


int main()
{
	SetCursorVisibility(false);
	DrawFrame();
	std::vector<std::shared_ptr<Door>> doors_smart;
	std::vector<Room> rooms;
	Player player; 

	AddRoom(static_cast<int>(rooms.size()), "Start", rooms, doors_smart);
	AddRoom(static_cast<int>(rooms.size()), "Normal", rooms, doors_smart);
	AddRoom(static_cast<int>(rooms.size()), "Normal", rooms, doors_smart);
	AddRoom(static_cast<int>(rooms.size()), "Boss", rooms, doors_smart);
	player.ShowStats();

	/*
	* Code structure comment: 
	* This is not wrong but from another developers prospective its very strage 
	* 
	* normally the game state would be contained in its own global object as it is hard to understand working backwards
	* that the state of if the game is contained in the the state of the rooms rather than in a dedicated place so you might 
	* call that object world or gamestate and call something world.isLastBossDefeted(); as this is more a question about the
	* current game state rather than about the current room.
	*/
	while (player.IsAlive() && rooms[player.GetCurrentRoom()].LastBossDefeted() == false)
	{
		ClearGameView();
		rooms[player.GetCurrentRoom()].EnterRoom(player, doors_smart, rooms);
	}
	



	if (player.GetHP() <= 0)
	{
		PrintInMenu("Hell is taking over after your defet!");
	}
	else
	{
		PrintInMenu("You have defeted Diablo!");
	}

}

