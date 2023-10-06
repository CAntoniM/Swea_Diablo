#pragma once
#include <vector>
#include "UI.h"
#include <array>
#include <memory>

#include "Event.h"
#include "Room.h"
#include "Enemy.h"
#include "Room.h"
#include "Item.h"
#include "Player.h"

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

	std::vector<Enemy> _enemy_list;
	std::vector<std::shared_ptr<Item>> _item_list;
	std::vector<std::shared_ptr<Door>> _connecting_doors;
	std::shared_ptr<Event> _event;
	std::string _room_type;
	std::string _room_name;
	void RoomDescription();
	void CheckConnectingDoors(std::vector<std::shared_ptr<Door>> aListOfDoors);
	void CreateEnemys();
	void CreateItems(int aAmountOfItems);
	void Combat(Player& aPlayer);
	void Explore(Player& aPlayer);
	void Loot();
	void RoomOptions(Player& aPlayer, std::vector<Room>& aRoomList);
	int _room_nr;
	int _number_of_enemeis;
	bool LivingEnemies();
	bool _last_boss_room;
	bool _last_boss_defeted;
	bool _room_explored;

};

