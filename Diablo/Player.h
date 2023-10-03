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
	std::string myAbilityChecks[PlayerBase::NumberOfPlayerAbilitys] = { "Athletics", "Sleight of Hand", "Persuasion" };;
	int myCurrentRoom;
	int myStrength;
	int myDexterety;
	int myDodge;
	int myCharisma;

	int myHp;
	int myMaxHp;
	int myBaseDamage;
	int myCarryingCapacity;
	int myAthletics;
	int mySlightOfHand;
	int myPersuasion;

	bool myIsAlive;
};

