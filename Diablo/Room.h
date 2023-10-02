#pragma once
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "Door.h"
#include "UI.h"
#include <array>
class Door;

class Room
{
public:
	Room(int aRoomNr, std::string aRoomType);
	void EnterRoom(Player& aPlayer, std::vector<Door>& aListOfDoors, std::vector<Room>& aRoomList);
	void SwitchRoom(Player& aPlayer, std::vector<Room>& aRoomList);
	bool LastBossDefeted();
	bool GetRoomExplored();
	std::string GetRoomName();

private:
	std::vector<Enemy> enemyList;
	std::vector<Door> connectingDoors;
	std::string roomType;
	std::string roomName;
	void RoomDescription();
	void CheckConnectingDoors(std::vector<Door>& aListOfDoors);
	void CreateEnemys();
	void Combat(Player& aPlayer);
	void Explore();
	void Loot();
	void RoomOptions(Player& aPlayer, std::vector<Room>& aRoomList);
	int roomNr;
	int numberOfEnemeis;
	bool LivingEnemies();
	bool lastBossRoom;
	bool lastBossDefeted;
	bool roomExplored;

};

