#pragma once
#include <string>
#include <array>
#include <vector>
#include "Enums.h"
#include "Items.h"

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
	int GetPlayerAbilityInt(PlayerBase anAbility); 
	bool GetIsAlive();
	std::string* GetAbilityCheckList();
	void PickUpItem(Items aItem);


private:
	std::vector<Items> myInventory;
	std::string myAbilityChecks[static_cast<int>(PlayerBase::NumberOfPlayerAbilitys)] = { "Athletics", "Sleight of Hand", "Persuasion" };;
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

