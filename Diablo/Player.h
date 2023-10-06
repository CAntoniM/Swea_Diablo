#pragma once
#include <string>
#include <array>
#include <vector>
#include "Enums.h"
#include "Equipment.h"
#include <memory>
#include "Item.h"


class Player
{
public:
	Player();
	std::vector<std::shared_ptr<Item>> GetInventory();
	std::string* GetAbilityCheckList();
	int GetHP();
	int GetNormalAttack();
	int GetCurrentRoom();
	int GetAbilityInt(PlayerBase anAbility); 
	bool IsAlive();
	void UppdateStats();
	void PickUpItem(std::shared_ptr<Item> aItem);
	void UppdateHp(int aChange);
	void ChangeRoom(int aNewRoom);
	void ShowStats();
	void EquipItem(int aItemChoise);
	void InventoryManagement();
	void FindPrimeStatBuff(PrimeStats aPrimeStat, int aStatBuff);
	void FindSecondaryStatBuff(SecondaryStats aSecondaryStat, int aStatBuff);


private:
	Equipment _equipment;
	std::vector<std::shared_ptr<Item>> _inventory;
	std::string _ability_checks[static_cast<int>(PlayerBase::NumberOfPlayerAbilitys)] = { "Athletics", "Sleight of Hand", "Persuasion" };;
	int myCurrentRoom;
	
	const int _base_strength = static_cast<int>(PlayerBase::PlayerBaseStrength);
	const int _base_dexterety = static_cast<int>(PlayerBase::PlayerBaseDexterety);
	const int _base_dodge = static_cast<int>(PlayerBase::PlayerBaseDodge);
	const int _base_charisma = static_cast<int>(PlayerBase::PlayerBaseCharisma);
	const int _base_armor = static_cast<int>(PlayerBase::PlayerBaseArmor);

	int _strength;
	int _dexterety;
	int _dodge;
	int _charisma;
	int _armor;

	int _hp;
	int _max_hp;
	int _base_damage;
	int _carrying_capacity;
	int _athletics;
	int _slight_of_hand;
	int _persuasion;

	bool _is_alive;
};

