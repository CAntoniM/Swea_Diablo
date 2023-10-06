#pragma once
#include <memory>
#include "Room.h"
#include "UI.h"
#include "Quick functions.h"
#include "Door.h"
#include "Enums.h"
#include "Player.h"
#include "Events.h"

Room::Room(int aRoomNr, std::string aRoomType)
{
	myEnemyList;
	myConnectingDoors;
	myItemList;
	
	myRoomType = aRoomType;
	myRoomNr = aRoomNr;
	myRoomName = " ? ? ? ";
	
	myRoomExplored = false;
	myLastBossRoom = false;
	myLastBossDefeted = false;
	myEvent = nullptr;
	
	if (myRoomType == "Random")
	{
		myRoomType = "Normal";
	}

	if (myRoomType == "Normal")
	{
		CreateEnemys();
		CreateItems(RandomNumber(0, static_cast<int>(RoomBase::MaxNumberOfItemsDropt)));
		myNumberOfEnemeis = static_cast<int>(myEnemyList.size());
		myRoomName = "Corridor";
		if (RandomNumber(0, static_cast<int>(RoomBase::ChansOfGettingAEvent)) == 0)
		{
			myEvent = std::make_shared<Events>();
		}
	}
	else if (myRoomType == "Boss")
	{

		myNumberOfEnemeis = static_cast<int>(myEnemyList.size());
		myLastBossRoom = true;
		myRoomName = "Boss Room";

	}
	else if (myRoomType == "Start")
	{
		myEvent = std::make_shared<Events>();
		CreateItems(RandomNumber(0, 1));
		myRoomName = "Entrance";
	}
}

std::string Room::GetRoomName()
{
	return myRoomName;
}

bool Room::GetRoomExplored()
{
	return myRoomExplored;
}

bool Room::LastBossDefeted()
{
	return myLastBossDefeted;
}

void Room::CheckConnectingDoors(std::vector<std::shared_ptr<Door>> aListOfDoors)
{
	myConnectingDoors.clear();
	for (int i = 0; i < aListOfDoors.size(); i++)
	{
		if (aListOfDoors[i]->GetIsInCurrentRoom(myRoomNr) == true && myConnectingDoors.size() < static_cast<int>(DoorBase::maxDoorsInARoom))
		{
			myConnectingDoors.push_back(aListOfDoors[i]);
		}
	}
}

bool Room::LivingEnemies()
{
	bool livingEnemie = false;
	for (int i = 0; i < myEnemyList.size(); i++)
	{
		if (myEnemyList[i].GetIsAlive() == true)
		{
			livingEnemie = true;
		}
	}
	return livingEnemie;
}

void Room::CreateEnemys()
{
	int numberOfEnemeis = RandomNumber(static_cast<int>(RoomBase::MinNumberOfEnemis), static_cast<int>(RoomBase::MaxNumberOfEnemis));
		for (int i = 0; i < numberOfEnemeis; i++)
		{
			Enemy enemy;
			myEnemyList.push_back(enemy);
		}
}

void Room::CreateItems(int aAmountOfItems)
{
	std::vector<ItemType> randomItemType =
	{
		ItemType::Dagger,
		ItemType::Sword,
		ItemType::GreatSword,
		ItemType::Helm,
		ItemType::Armor,
	};
	int numberOfItems = RandomNumber(static_cast<int>(RoomBase::MinNumberOfItemsDropt), static_cast<int>(RoomBase::MaxNumberOfItemsDropt));
	for (int i = 0; i < numberOfItems; i++)
	{
		std::shared_ptr<Items> items = std::make_shared <Items>(randomItemType[RandomNumber(0, static_cast<int>(randomItemType.size()) - 1)]);
		myItemList.push_back(items);
	}
}

void Room::Combat(Player& aPlayer)
{
	ClearMenu();
	int playerTarget = 0;
	while (aPlayer.GetIsAlive() == true && LivingEnemies() == true)
	{
		ShowEnemy(myEnemyList);
		playerTarget = ChoseEnemy(myEnemyList);
		myEnemyList[playerTarget].UppdateHp(aPlayer.GetNormalAttack()); 
		
		for (int i = 0; i < myNumberOfEnemeis; i++)
		{
			if (myEnemyList[i].GetEnemyHp() >= 0)
			{
				Sleep();
				PrintInMenu("The enemy is retaliating and attacking you!");
				aPlayer.UppdateHp(myEnemyList[i].GetNormalAttack());
				aPlayer.ShowPlayerStats();
			}
		}
	}
	Sleep(1000);
	ClearGame();
}

void Room::Explore(Player& aPlayer)
{
	int playerChoiseInMenu = 0;
	if (myEvent != nullptr)
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
			myEvent->GetEventDescription();
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

	if (static_cast<int>(myItemList.size()) <= 0)
	{
		PrintInMenu("You don't find any items in the room!");
		Sleep();
		return;
	}

	playerChoiseInMenu = 0;
	while (true)
	{
		int playerTryPickUp = showItems(myItemList, playerChoiseInMenu);
		if (playerTryPickUp >= myItemList.size())
		{
			return;
		}
		else
		{
			aPlayer.PickUpItem(myItemList[playerTryPickUp]);
			myItemList.erase(myItemList.begin() + playerTryPickUp);
		}
	}
}

void Room::Loot()
{
	PrintInMenu("You don't find anything on the monster!");
	Sleep();
}

void Room::SwitchRoom(Player& aPlayer, std::vector<Room>& aRoomList)
{
	while (true)
	{

		int doorTry = ShowDoors(myConnectingDoors, aRoomList, myRoomNr);
		if (myConnectingDoors[doorTry]->GetDoorLockt() == true)
		{
			int playerMenuChoise = 0;
			PrintInMenu("The door is lockt...");
			Sleep();
			MenuControll(aPlayer.GetAbilityCheckList(), static_cast<int>(PlayerBase::NumberOfPlayerAbilitys), playerMenuChoise, static_cast<int>(MenuOptions::menyStartY));
			ClearMenu();
			switch (playerMenuChoise)
			{
				case static_cast<int>(PlayerBase::AthleticsPlayerSkill):
				{
					PrintInMenu("You try to break the door open...");
					Sleep(1500);
					if ((aPlayer.GetPlayerAbilityInt(PlayerBase::AthleticsPlayerSkill) + RandomNumber(1, 20)) > myConnectingDoors[doorTry]->GetLockDifficultyStr())
					{
						myConnectingDoors[doorTry]->SetDoorLockt(false);
						PrintInMenu("You break the door open and can walk through");
						Sleep();
						aPlayer.ChangeRoom(myConnectingDoors[doorTry]->GetConnectingRoom(myRoomNr));
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
					if ((aPlayer.GetPlayerAbilityInt(PlayerBase::SlightOfHandPlayerSkill) + RandomNumber(1, 20)) > myConnectingDoors[doorTry]->GetLockDifficultyDex())
					{
						PrintInMenu("The lock opens and you can walk through");
						Sleep();
						myConnectingDoors[doorTry]->SetDoorLockt(false);
						aPlayer.ChangeRoom(myConnectingDoors[doorTry]->GetConnectingRoom(myRoomNr));
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
						myConnectingDoors[doorTry]->SetDoorLockt(false);
						aPlayer.ChangeRoom(myConnectingDoors[doorTry]->GetConnectingRoom(myRoomNr));
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
		else if (myConnectingDoors[doorTry]->GetDoorLockt() == false)
		{
			aPlayer.ChangeRoom(myConnectingDoors[doorTry]->GetConnectingRoom(myRoomNr));
			return;
		}
	}
}

void Room::RoomOptions(Player& aPlayer, std::vector<Room>& aRoomList)
{
	std::string roomOptions[] = { "Explore", "Loot", "Inventory", "Switch Room"};
	int playerChoise = 0;
	
	while (true)
	{
		aPlayer.ShowPlayerStats();
		MenuControll(roomOptions, static_cast<int>(size(roomOptions)), playerChoise, static_cast<int>(MenuOptions::menyStartY));
		ClearMenu();
		ClearGame();
		switch (playerChoise)
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
	if (myRoomName == "Entrance")
	{
		PrintInMenu("You are in the entrance of the dungeon, the path to the surface is blockt!");
		Pause();
	}
	else if (myRoomName == "Corridor")
	{
		PrintInMenu("It is a long and dark corridor, you can hear something up ahead...");
		Pause();
	}
	else if (myRoomName == "Boss Room")
	{
		PrintInMenu("You feel like something big might jump at you...");
		Pause();
	}
}

void Room::EnterRoom(Player& aPlayer, std::vector<std::shared_ptr<Door>> aListOfDoors, std::vector<Room>& aRoomList)
{

	RoomDescription();
	Sleep();
	myRoomExplored = true;
	if (LivingEnemies())
	{
		Combat(aPlayer);
		ClearGame();
	}

	if (myLastBossRoom == true && aPlayer.GetIsAlive() == true)
	{
		myLastBossDefeted = true;
		return;
	}
	else if (aPlayer.GetIsAlive() == true)
	{
		PrintInMenu("All enemys have been defeted...");
		CheckConnectingDoors(aListOfDoors);
		RoomOptions(aPlayer, aRoomList);
	}
}