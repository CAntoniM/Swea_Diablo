#pragma once
#include <string>
#include <array>
#include "Enums.h"
class Player
{
public:
	Player();
	void UppdateHp(int aChange);
	void ChangeRoom(int aNewRoom);
	void ShowPlayerStats();
	int GetPlayerHp();
	int GetNormalAttack();
	int GetCurrentRoom();
	int GetPlayerAbilityInt(int anAbility); 
	bool GetIsAlive();
	std::string* GetAbilityCheckList();



private:
	std::string abilityChecks[PlayerBase::NumberOfPlayerAbilitys] = { "Athletics", "Sleight of Hand", "Persuasion" };;
	int currentRoom;
	int strength;
	int dexterety;
	int dodge;
	int charisma;

	int hp;
	int maxHp;
	int baseDamage;
	int carryingCapacity;
	int athletics;
	int slightOfHand;
	int persuasion;

	bool isAlive;
};

