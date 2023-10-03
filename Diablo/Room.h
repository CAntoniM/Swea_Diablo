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
	void EnterRoom(Player& aPlayer, std::vector<std::shared_ptr<Door>> aListOfDoors, std::vector<Room>& aRoomList);
	void SwitchRoom(Player& aPlayer, std::vector<Room>& aRoomList);
	bool LastBossDefeted();
	bool GetRoomExplored();
	std::string GetRoomName();

private:
	std::vector<Enemy> myEnemyList;
	std::vector<std::shared_ptr<Door>> myConnectingDoors;
	std::string myRoomType;
	std::string myRoomName;
	void RoomDescription();
	void CheckConnectingDoors(std::vector<std::shared_ptr<Door>> aListOfDoors);
	void CreateEnemys();
	void Combat(Player& aPlayer);
	void Explore();
	void Loot();
	void RoomOptions(Player& aPlayer, std::vector<Room>& aRoomList);
	int myRoomNr;
	int myNumberOfEnemeis;
	bool LivingEnemies();
	bool myLastBossRoom;
	bool myLastBossDefeted;
	bool myRoomExplored;

};

