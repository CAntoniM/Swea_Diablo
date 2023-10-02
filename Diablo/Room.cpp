#pragma once
#include "Room.h"
#include "UI.h"
#include "Quick functions.h"
#include "Door.h"
#include "Enums.h"

Room::Room(int aRoomNr, std::string aRoomType)
{
	enemyList;
	connectingDoors;
	roomType = aRoomType;
	roomNr = aRoomNr;
	roomName = " ? ? ? ";
	roomExplored = false;
	lastBossRoom = false;
	lastBossDefeted = false;
	if (roomType == "Random")
	{
		roomType = "Normal";
	}

	if (roomType == "Normal")
	{
		CreateEnemys();
		numberOfEnemeis = static_cast<int>(enemyList.size());
		roomName = "Corridor";
	}
	else if (roomType == "Boss")
	{

		numberOfEnemeis = static_cast<int>(enemyList.size());
		lastBossRoom = true;
		roomName = "Boss Room";

	}
	else if (roomType == "Start")
	{
		roomName = "Entrance";
	}
}

std::string Room::GetRoomName()
{
	return roomName;
}

bool Room::GetRoomExplored()
{
	return roomExplored;
}

bool Room::LastBossDefeted()
{
	return lastBossDefeted;
}

void Room::CheckConnectingDoors(std::vector<Door>& aListOfDoors)
{
	connectingDoors.clear();
	for (int i = 0; i < aListOfDoors.size(); i++)
	{
		if (aListOfDoors[i].GetIsInCurrentRoom(roomNr) == true && connectingDoors.size() < DoorBase::maxDoorsInARoom)
		{
			connectingDoors.push_back(aListOfDoors[i]);
		}
	}
}

bool Room::LivingEnemies()
{
	bool livingEnemie = false;
	for (int i = 0; i < enemyList.size(); i++)
	{
		if (enemyList[i].GetIsAlive() == true)
		{
			livingEnemie = true;
		}
	}
	return livingEnemie;
}

void Room::CreateEnemys()
{
	int NumberOfEnemeis = RandomNumber(RoomBase::MinNumberOfEnemis, RoomBase::MaxNumberOfEnemis); 
		for (int i = 0; i < NumberOfEnemeis; i++)
		{
			Enemy enemy;
			enemyList.push_back(enemy);
		}
}

void Room::Combat(Player& aPlayer)
{
	ClearMenu();
	int playerTarget = 0;
	while (aPlayer.GetIsAlive() == true && LivingEnemies() == true)
	{
		ShowEnemy(enemyList);
		playerTarget = ChoseEnemy(enemyList);
		enemyList[playerTarget].UppdateHp(aPlayer.GetNormalAttack()); 
		
		for (int i = 0; i < numberOfEnemeis; i++)
		{
			if (enemyList[i].GetEnemyHp() >= 0)
			{
				Sleep();
				PrintInMenu("The enemy is retaliating and attacking you!");
				aPlayer.UppdateHp(enemyList[i].GetNormalAttack());
				aPlayer.ShowPlayerStats();
			}
		}
	}
	Sleep(1000);
	ClearGame();
	PrintInMenu("All enemys have been defeted...");
	Sleep();
}

void Room::Explore()
{
	PrintInMenu("You don't find anything in the room!");
	Sleep();
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

		int doorTry = ShowDoors(connectingDoors, aRoomList, roomNr);
		if (connectingDoors[doorTry].GetDoorLockt() == true)
		{
			int playerMenuChoise = 0;
			PrintInMenu("The door is lockt...");
			MenuControll(aPlayer.GetAbilityCheckList(), PlayerBase::NumberOfPlayerAbilitys, playerMenuChoise, MenuOptions::menyStartY);
			ClearMenu();
			switch (playerMenuChoise)
			{
				case PlayerBase::AthleticsPlayerSkill: 
				{
					PrintInMenu("You try to break the door open...");
					Sleep(1500);
					if ((aPlayer.GetPlayerAbilityInt(PlayerBase::AthleticsPlayerSkill) + RandomNumber(1, 20)) > connectingDoors[doorTry].GetLockDifficultyStr())
					{
						PrintInMenu("You break the door open and can walk through");
						aPlayer.ChangeRoom(connectingDoors[doorTry].GetConnectingRoom(roomNr));
						return;
					}
					else
					{
						PrintInMenu("The door isn't budging");
						Sleep();
					}
					break;
				}
				case PlayerBase::SlightOfHandPlayerSkill: 
				{
					PrintInMenu("You try to pick the lock...");
					Sleep(1500);
					if ((aPlayer.GetPlayerAbilityInt(PlayerBase::SlightOfHandPlayerSkill) + RandomNumber(1, 20)) > connectingDoors[doorTry].GetLockDifficultyDex())
					{
						PrintInMenu("The lock opens and you can walk through");
						Sleep();
						aPlayer.ChangeRoom(connectingDoors[doorTry].GetConnectingRoom(roomNr));
						return;
					}
					else
					{
						PrintInMenu("You can't find a way to open the lock");
					}
					break;
				}
				case PlayerBase::PersuasionPlayerSkill: 
				{
					PrintInMenu("You try to convins the door to open...");
					Sleep();
					PrintInMenu("It looks like it's not working");
					break;
				}
			default:
				break;
			}
		}
		else if (connectingDoors[doorTry].GetDoorLockt() == false)
		{
			aPlayer.ChangeRoom(connectingDoors[doorTry].GetConnectingRoom(roomNr));
			return;
		}
	}
}

void Room::RoomOptions(Player& aPlayer, std::vector<Room>& aRoomList)
{
	std::string roomOptions[] = { "Explore", "Loot", "Switch Room" };
	int playerChoise = 0;
	
	while (true)
	{

		MenuControll(roomOptions, static_cast<int>(size(roomOptions)), playerChoise, MenuOptions::menyStartY);

		switch (playerChoise)
		{
			case RoomBase::MenuExplore: 
			{
				Explore();
				break;
			}
			case RoomBase::MenuLoot:
			{
				Loot();
				break;
			}
			case RoomBase::MenuSwitchRoom:
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
	if (roomName == "Entrance")
	{
		PrintInMenu("You are in the entrance of the dungeon, the path to the surface is blockt!");
		Pause();
	}
	else if (roomName == "Corridor")
	{
		PrintInMenu("It is a long and dark corridor, you can hear something up ahead...");
		Pause();
	}
	else if (roomName == "Boss Room")
	{
		PrintInMenu("You feel like something big might jump at you...");
		Pause();
	}
}

void Room::EnterRoom(Player& aPlayer, std::vector<Door>& aListOfDoors, std::vector<Room>& aRoomList)
{

	RoomDescription();
	roomExplored = true;
	if (LivingEnemies())
	{
		Combat(aPlayer);
		ClearGame();
	}

	if (lastBossRoom == true && aPlayer.GetIsAlive() == true)
	{
		lastBossDefeted = true;
		return;
	}
	else if (aPlayer.GetIsAlive() == true)
	{
		CheckConnectingDoors(aListOfDoors);
		RoomOptions(aPlayer, aRoomList);
	}
}