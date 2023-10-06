#pragma once
#include <string>
#include <array>
#include <vector>
#include "Enums.h"
#include "Equipment.h"
#include <memory>

class Items;
class Equipment;


class Player
{
public:
	Player();
	std::vector<std::shared_ptr<Items>> GetInventory();
	std::string* GetAbilityCheckList();
	int GetPlayerHp();
	int GetNormalAttack();
	int GetCurrentRoom();
	int GetPlayerAbilityInt(PlayerBase anAbility); 
	bool GetIsAlive();
	void UppdatePlayerStats();
	void PickUpItem(std::shared_ptr<Items> aItem);
	void UppdateHp(int aChange);
	void ChangeRoom(int aNewRoom);
	void ShowPlayerStats();
	void EquipItem(int aItemChoise);
	void InventoryManagement();
	void PlayerFindPrimeStatBuff(PrimeStats aPrimeStat, int aStatBuff);
	void PlayerFindSecondaryStatBuff(SecondaryStats aSecondaryStat, int aStatBuff);


private:
	Equipment myEquipment;
	std::vector<std::shared_ptr<Items>> myInventory;
	std::string myAbilityChecks[static_cast<int>(PlayerBase::NumberOfPlayerAbilitys)] = { "Athletics", "Sleight of Hand", "Persuasion" };;
	int myCurrentRoom;
	
	const int myBaseStrength = static_cast<int>(PlayerBase::PlayerBaseStrength);
	const int myBaseDexterety = static_cast<int>(PlayerBase::PlayerBaseDexterety);
	const int myBaseDodge = static_cast<int>(PlayerBase::PlayerBaseDodge);
	const int myBaseCharisma = static_cast<int>(PlayerBase::PlayerBaseCharisma);
	const int myBaseArmor = static_cast<int>(PlayerBase::PlayerBaseArmor);

	int myStrength;
	int myDexterety;
	int myDodge;
	int myCharisma;
	int myArmor;

	int myHp;
	int myMaxHp;
	int myBaseDamage;
	int myCarryingCapacity;
	int myAthletics;
	int mySlightOfHand;
	int myPersuasion;

	bool myIsAlive;
};

