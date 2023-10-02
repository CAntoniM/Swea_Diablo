
#include <iostream>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Room.h"
#include "Door.h"
#include "Quick functions.h"
#include "UI.h"

void AddDoor(int aConnectingRoomOne, int aConnectingRoomTwo, std::vector<Door>& aListOfDoors)
{
	Door doorOne(aConnectingRoomOne, aConnectingRoomTwo);
	aListOfDoors.push_back(doorOne);
}

void AddRoom(int aRoomNumber, std::string aRoomType, std::vector<Room>& aListOfRooms, std::vector<Door>& aListOfDoors)
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
	FlipCursorVisibility(false);
	DrawFrame();
	std::vector<Door> doors;
	std::vector<Room> rooms;
	Player player; 

	
	

	AddRoom(static_cast<int>(rooms.size()), "Start", rooms, doors);
	AddRoom(static_cast<int>(rooms.size()), "Normal", rooms, doors);
	AddRoom(static_cast<int>(rooms.size()), "Normal", rooms, doors);
	AddRoom(static_cast<int>(rooms.size()), "Boss", rooms, doors);
	player.ShowPlayerStats();
	while (player.GetIsAlive() == true && rooms[player.GetCurrentRoom()].LastBossDefeted() == false)
	{
		ClearGame();
		rooms[player.GetCurrentRoom()].EnterRoom(player, doors, rooms);
	}
	



	if (player.GetPlayerHp() <= 0)
	{
		PrintInMenu("Hell is taking over after your defet!");
	}
	else
	{
		PrintInMenu("You have defeted Diablo!");
	}

}

