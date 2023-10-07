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
		if (list_of_doors[i]->IsCurrentRoom(_room_nr) == true && _connecting_doors.size() < static_cast<int>(DoorBase::maxDoorsInARoom))
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
	ui::ClearMenu();
	int player_target = 0;
	while (player.IsAlive() == true && LivingEnemies() == true)
	{
		ui::ShowEnemy(_enemy_list);
		player_target = ui::ChoseEnemy(_enemy_list);
		_enemy_list[player_target].UppdateHp(player.GetNormalAttack()); 
		
		for (int i = 0; i < _number_of_enemeis; i++)
		{
			if (_enemy_list[i].GetHP() >= 0)
			{
				Sleep();
				ui::PrintInMenu("The enemy is retaliating and attacking you!");
				player.UppdateHp(_enemy_list[i].GetNormalAttack());
				player.ShowStats();
			}
		}
	}
	Sleep(1000);
	ui::ClearGameView();
}

void Room::Explore(Player& player)
{
	int user_menu_choice = 0;
	if (_event)
	{
		std::string awnsers[2] = { "Yes", "No" };
		ui::SetCursorPosition(static_cast<int>(MenuOptions::gameStartX), static_cast<int>(MenuOptions::gameStartY));
		ui::Print("You see somthing wierd in the room, do you wana interact with it?");
		ui::MenuControll(awnsers, 2, user_menu_choice, static_cast<int>(MenuOptions::menyStartY));
		ui::ClearMenu();
		switch (user_menu_choice)
		{
		case 0:
		{
			ui::PrintInMenu("You walk towards the object and tuch it...");
			Sleep();
			_event->GetEventDescription();
			break;
		}
		case 1:
		{
			ui::PrintInMenu("You chose to ignore it and search for some items instead");
			Sleep();
			break;
		}
		default:
			break;
		}
	}

	if (static_cast<int>(_item_list.size()) <= 0)
	{
		ui::PrintInMenu("You don't find any items in the room!");
		Sleep();
		return;
	}

	user_menu_choice = 0;
	while (true)
	{
		int playerTryPickUp = ui::showItems(_item_list, user_menu_choice);
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
	ui::PrintInMenu("You don't find anything on the monster!");
	Sleep();
}

void Room::SwitchRoom(Player& player, std::vector<Room>& rooms)
{
	while (true)
	{

		int door_try = ui::ShowDoors(_connecting_doors, rooms, _room_nr);
		if (_connecting_doors[door_try]->IsDoorLocked() == true)
		{
			int user_menu_choise = 0;
			ui::PrintInMenu("The door is lockt...");
			Sleep();
			ui::MenuControll(player.GetAbilityCheckList(), static_cast<int>(PlayerBase::NumberOfPlayerAbilitys), user_menu_choise, static_cast<int>(MenuOptions::menyStartY));
			ui::ClearMenu();
			switch (user_menu_choise)
			{
				case static_cast<int>(PlayerBase::AthleticsPlayerSkill):
				{
					ui::PrintInMenu("You try to break the door open...");
					Sleep(1500);
					if ((player.GetAbilityInt(PlayerBase::AthleticsPlayerSkill) + RandomNumber(1, 20)) > _connecting_doors[door_try]->GetLockDifficultyStr())
					{
						_connecting_doors[door_try]->IsDoorLocked(false);
						ui::PrintInMenu("You break the door open and can walk through");
						Sleep();
						player.ChangeRoom(_connecting_doors[door_try]->GetConnectingRoom(_room_nr));
						return;
					}
					else
					{
						ui::PrintInMenu("The door isn't budging");
						Sleep();
					}
					break;
				}
				case static_cast<int>(PlayerBase::SlightOfHandPlayerSkill):
				{
					ui::PrintInMenu("You try to pick the lock...");
					Sleep(1500);
					if ((player.GetAbilityInt(PlayerBase::SlightOfHandPlayerSkill) + RandomNumber(1, 20)) > _connecting_doors[door_try]->GetLockDifficultyDex())
					{
						ui::PrintInMenu("The lock opens and you can walk through");
						Sleep();
						_connecting_doors[door_try]->IsDoorLocked(false);
						player.ChangeRoom(_connecting_doors[door_try]->GetConnectingRoom(_room_nr));
						return;
					}
					else
					{
						ui::PrintInMenu("You can't find a way to open the lock");
					}
					break;
				}
				case static_cast<int>(PlayerBase::PersuasionPlayerSkill):
				{
					ui::PrintInMenu("You try to convins the door to open...");
					Sleep();

					if (RandomNumber(1, 20) == 20)
					{
						ui::PrintInMenu("The door opens...");
						Sleep();
						ui::PrintInMenu("You're not quite sure how...");
						Sleep();
						ui::PrintInMenu("You choose to take the chance to go through!");
						_connecting_doors[door_try]->IsDoorLocked(false);
						player.ChangeRoom(_connecting_doors[door_try]->GetConnectingRoom(_room_nr));
						return;
					}
					else
					{
						ui::PrintInMenu("It looks like it's not working");
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

void Room::RoomOptions(Player& player, std::vector<Room>& rooms)
{
	std::string room_options[] = { "Explore", "Loot", "Inventory", "Switch Room"};
	int player_choise = 0;
	
	while (true)
	{
		player.ShowStats();
		ui::MenuControll(room_options, static_cast<int>(size(room_options)), player_choise, static_cast<int>(MenuOptions::menyStartY));
		ui::ClearMenu();
		ui::ClearGameView();
		switch (player_choise)
		{
			case static_cast<int>(RoomBase::MenuExplore):
			{
				Explore(player);
				break;
			}
			case static_cast<int>(RoomBase::MenuLoot):
			{
				Loot();
				break;
			}
			case static_cast<int>(RoomBase::MenuInventory):
			{
				player.InventoryManagement();
				break;
			}
			case static_cast<int>(RoomBase::MenuSwitchRoom):
			{
				SwitchRoom(player, rooms);
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
		ui::PrintInMenu("You are in the entrance of the dungeon, the path to the surface is blockt!");
		ui::Pause();
	}
	else if (_room_name == "Corridor")
	{
		ui::PrintInMenu("It is a long and dark corridor, you can hear something up ahead...");
		ui::Pause();
	}
	else if (_room_name == "Boss Room")
	{
		ui::PrintInMenu("You feel like something big might jump at you...");
		ui::Pause();
	}
}

void Room::EnterRoom(Player& player, std::vector<std::shared_ptr<Door>> doors, std::vector<Room>& rooms)
{

	RoomDescription();
	Sleep();
	_room_explored = true;
	if (LivingEnemies())
	{
		Combat(player);
		ui::ClearGameView();
	}

	if (_last_boss_room == true && player.IsAlive() == true)
	{
		_last_boss_defeted = true;
		return;
	}
	else if (player.IsAlive() == true)
	{
		ui::PrintInMenu("All enemys have been defeted...");
		CheckConnectingDoors(doors);
		RoomOptions(player, rooms);
	}
}