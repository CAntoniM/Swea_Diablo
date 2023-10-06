#pragma once
#include <memory>
#include "Room.h"
#include "UI.h"
#include "Quick_functions.h"
#include "Door.h"
#include "Enums.h"
#include "Player.h"
#include "Event.h"

Room::Room(int room_nr, std::string _room_type)
{
	_enemy_list;
	_connecting_doors;
	_item_list;
	
	_room_type = _room_type;
	_room_nr = room_nr;
	_room_name = " ? ? ? ";
	
	_room_explored = false;
	_last_boss_room = false;
	_last_boss_defeted = false;
	_event = nullptr;
	
	if (_room_type == "Random")
	{
		_room_type = "Normal";
	}

	if (_room_type == "Normal")
	{
		CreateEnemys();
		CreateItems(RandomNumber(0, static_cast<int>(RoomBase::MaxNumberOfItemsDropt)));
		_number_of_enemeis = static_cast<int>(_enemy_list.size());
		_room_name = "Corridor";
		if (RandomNumber(0, static_cast<int>(RoomBase::ChansOfGettingAEvent)) == 0)
		{
			_event = std::make_shared<Event>();
		}
	}
	else if (_room_type == "Boss")
	{

		_number_of_enemeis = static_cast<int>(_enemy_list.size());
		_last_boss_room = true;
		_room_name = "Boss Room";

	}
	else if (_room_type == "Start")
	{
		_event = std::make_shared<Event>();
		CreateItems(RandomNumber(0, 1));
		_room_name = "Entrance";
	}
}

std::string Room::GetRoomName()
{
	return _room_name;
}

bool Room::GetRoomExplored()
{
	return _room_explored;
}

bool Room::LastBossDefeted()
{
	return _last_boss_defeted;
}

void Room::CheckConnectingDoors(std::vector<std::shared_ptr<Door>> list_of_doors)
{
	_connecting_doors.clear();
	for (int i = 0; i < list_of_doors.size(); i++)
	{
		if (list_of_doors[i]->IsInCurrentRoom(_room_nr) == true && _connecting_doors.size() < static_cast<int>(DoorBase::maxDoorsInARoom))
		{
			_connecting_doors.push_back(list_of_doors[i]);
		}
	}
}

bool Room::LivingEnemies()
{
	bool living_enemie = false;
	for (int i = 0; i < _enemy_list.size(); i++)
	{
		if (_enemy_list[i].IsAlive() == true)
		{
			living_enemie = true;
		}
	}
	return living_enemie;
}

void Room::CreateEnemys()
{
	int number_of_enemeis = RandomNumber(static_cast<int>(RoomBase::MinNumberOfEnemis), static_cast<int>(RoomBase::MaxNumberOfEnemis));
		for (int i = 0; i < number_of_enemeis; i++)
		{
			Enemy enemy;
			_enemy_list.push_back(enemy);
		}
}

void Room::CreateItems(int aAmountOfItems)
{
	std::vector<ItemType> random_item_type =
	{
		ItemType::Dagger,
		ItemType::Sword,
		ItemType::GreatSword,
		ItemType::Helm,
		ItemType::Armor,
	};
	int number_of_items = RandomNumber(static_cast<int>(RoomBase::MinNumberOfItemsDropt), static_cast<int>(RoomBase::MaxNumberOfItemsDropt));
	for (int i = 0; i < number_of_items; i++)
	{
		std::shared_ptr<Item> items = std::make_shared <Item>(random_item_type[RandomNumber(0, static_cast<int>(random_item_type.size()) - 1)]);
		_item_list.push_back(items);
	}
}

void Room::Combat(Player& player)
{
	ClearMenu();
	int playerTarget = 0;
	while (player.IsAlive() == true && LivingEnemies() == true)
	{
		ShowEnemy(_enemy_list);
		playerTarget = ChoseEnemy(_enemy_list);
		_enemy_list[playerTarget].UppdateHp(player.GetNormalAttack()); 
		
		for (int i = 0; i < _number_of_enemeis; i++)
		{
			if (_enemy_list[i].GetHP() >= 0)
			{
				Sleep();
				PrintInMenu("The enemy is retaliating and attacking you!");
				player.UppdateHp(_enemy_list[i].GetNormalAttack());
				player.ShowStats();
			}
		}
	}
	Sleep(1000);
	ClearGameView();
}

void Room::Explore(Player& player)
{
	int playerChoiseInMenu = 0;
	if (_event)
	{
		std::string awnsers[2] = { "Yes", "No" };
		SetCursorPosition(static_cast<int>(MenuOptions::gameStartX), static_cast<int>(MenuOptions::gameStartY));
		Print("You see somthing wierd in the room, do you wana interact with it?");
		MenuControll(awnsers, 2, playerChoiseInMenu, static_cast<int>(MenuOptions::menyStartY));
		ClearMenu();
		switch (playerChoiseInMenu)
		{
		case 0:
		{
			PrintInMenu("You walk towards the object and tuch it...");
			Sleep();
			_event->GetEventDescription();
			break;
		}
		case 1:
		{
			PrintInMenu("You chose to ignore it and search for some items instead");
			Sleep();
			break;
		}
		default:
			break;
		}
	}

	if (static_cast<int>(_item_list.size()) <= 0)
	{
		PrintInMenu("You don't find any items in the room!");
		Sleep();
		return;
	}

	playerChoiseInMenu = 0;
	while (true)
	{
		int playerTryPickUp = showItems(_item_list, playerChoiseInMenu);
		if (playerTryPickUp >= _item_list.size())
		{
			return;
		}
		else
		{
			player.PickUpItem(_item_list[playerTryPickUp]);
			_item_list.erase(_item_list.begin() + playerTryPickUp);
		}
	}
}

void Room::Loot()
{
	PrintInMenu("You don't find anything on the monster!");
	Sleep();
}

void Room::SwitchRoom(Player& player, std::vector<Room>& room_list)
{
	while (true)
	{

		int door_try = ShowDoors(_connecting_doors, room_list, _room_nr);
		if (_connecting_doors[door_try]->IsDoorLocked() == true)
		{
			int user_menu_choise = 0;
			PrintInMenu("The door is lockt...");
			Sleep();
			MenuControll(player.GetAbilityCheckList(), static_cast<int>(PlayerBase::NumberOfPlayerAbilitys), user_menu_choise, static_cast<int>(MenuOptions::menyStartY));
			ClearMenu();
			switch (user_menu_choise)
			{
				case static_cast<int>(PlayerBase::AthleticsPlayerSkill):
				{
					PrintInMenu("You try to break the door open...");
					Sleep(1500);
					if ((player.GetAbilityInt(PlayerBase::AthleticsPlayerSkill) + RandomNumber(1, 20)) > _connecting_doors[door_try]->GetLockDifficultyStr())
					{
						_connecting_doors[door_try]->isDoorLocked(false);
						PrintInMenu("You break the door open and can walk through");
						Sleep();
						player.ChangeRoom(_connecting_doors[door_try]->GetConnectingRoom(_room_nr));
						return;
					}
					else
					{
						PrintInMenu("The door isn't budging");
						Sleep();
					}
					break;
				}
				case static_cast<int>(PlayerBase::SlightOfHandPlayerSkill):
				{
					PrintInMenu("You try to pick the lock...");
					Sleep(1500);
					if ((player.GetAbilityInt(PlayerBase::SlightOfHandPlayerSkill) + RandomNumber(1, 20)) > _connecting_doors[door_try]->GetLockDifficultyDex())
					{
						PrintInMenu("The lock opens and you can walk through");
						Sleep();
						_connecting_doors[door_try]->isDoorLocked(false);
						player.ChangeRoom(_connecting_doors[door_try]->GetConnectingRoom(_room_nr));
						return;
					}
					else
					{
						PrintInMenu("You can't find a way to open the lock");
					}
					break;
				}
				case static_cast<int>(PlayerBase::PersuasionPlayerSkill):
				{
					PrintInMenu("You try to convins the door to open...");
					Sleep();

					if (RandomNumber(1, 20) == 20)
					{
						PrintInMenu("The door opens...");
						Sleep();
						PrintInMenu("You're not quite sure how...");
						Sleep();
						PrintInMenu("You choose to take the chance to go through!");
						_connecting_doors[door_try]->isDoorLocked(false);
						player.ChangeRoom(_connecting_doors[door_try]->GetConnectingRoom(_room_nr));
						return;
					}
					else
					{
						PrintInMenu("It looks like it's not working");
						Sleep();
						break;
					}
				}
			default:
				break;
			}
		}
		else if (_connecting_doors[door_try]->IsDoorLocked() == false)
		{
			player.ChangeRoom(_connecting_doors[door_try]->GetConnectingRoom(_room_nr));
			return;
		}
	}
}

void Room::RoomOptions(Player& aPlayer, std::vector<Room>& aRoomList)
{
	std::string room_options[] = { "Explore", "Loot", "Inventory", "Switch Room"};
	int player_choise = 0;
	
	while (true)
	{
		aPlayer.ShowStats();
		MenuControll(room_options, static_cast<int>(size(room_options)), player_choise, static_cast<int>(MenuOptions::menyStartY));
		ClearMenu();
		ClearGameView();
		switch (player_choise)
		{
			case static_cast<int>(RoomBase::MenuExplore):
			{
				Explore(aPlayer);
				break;
			}
			case static_cast<int>(RoomBase::MenuLoot):
			{
				Loot();
				break;
			}
			case static_cast<int>(RoomBase::MenuInventory):
			{
				aPlayer.InventoryManagement();
				break;
			}
			case static_cast<int>(RoomBase::MenuSwitchRoom):
			{
				SwitchRoom(aPlayer, aRoomList);
				return;
				break;
			}
		}
	}
}

void Room::RoomDescription()
{
	if (_room_name == "Entrance")
	{
		PrintInMenu("You are in the entrance of the dungeon, the path to the surface is blockt!");
		Pause();
	}
	else if (_room_name == "Corridor")
	{
		PrintInMenu("It is a long and dark corridor, you can hear something up ahead...");
		Pause();
	}
	else if (_room_name == "Boss Room")
	{
		PrintInMenu("You feel like something big might jump at you...");
		Pause();
	}
}

void Room::EnterRoom(Player& aPlayer, std::vector<std::shared_ptr<Door>> aListOfDoors, std::vector<Room>& aRoomList)
{

	RoomDescription();
	Sleep();
	_room_explored = true;
	if (LivingEnemies())
	{
		Combat(aPlayer);
		ClearGameView();
	}

	if (_last_boss_room == true && aPlayer.IsAlive() == true)
	{
		_last_boss_defeted = true;
		return;
	}
	else if (aPlayer.IsAlive() == true)
	{
		PrintInMenu("All enemys have been defeted...");
		CheckConnectingDoors(aListOfDoors);
		RoomOptions(aPlayer, aRoomList);
	}
}