#include "Player.h"
#include "Enums.h"
#include "Quick functions.h"
#include "Items.h"
#include "Equipment.h"
#include "UI.h"
#include <array>
#include <string>

Player::Player()
{
	myEquipment;
	myInventory;

	myStrength			= myBaseStrength;
	myDexterety			= myBaseDexterety;
	myDodge				= myBaseDodge;
	myCharisma			= myBaseCharisma;

	myHp				= (myStrength * 6) + (myDexterety * 3);
	myMaxHp				= myHp;
	myBaseDamage		= (myStrength * 2) + myDexterety;
	myCarryingCapacity	= (myStrength * 2) - myDodge;
	myAthletics			= myStrength + myDexterety;
	mySlightOfHand		= myDodge + myDexterety;
	myPersuasion		= myCharisma + myDodge;

	myIsAlive			= true;
	myCurrentRoom		= 0;
}

void Player::ChangeRoom(int aNewRoom)
{
	myCurrentRoom = aNewRoom;
}

void Player::PlayerFindPrimeStatBuff(PrimeStats aPrimeStat, int aStatBuff)
{
	switch (aPrimeStat)
	{
	case PrimeStats::Strength:
		myStrength += aStatBuff;
		break;

	case PrimeStats::Dexterety:
		myDexterety += aStatBuff;
		break;

	case PrimeStats::Charisma:
		myCharisma += aStatBuff;
		break;

	case PrimeStats::Armor:
		myArmor += aStatBuff;
		break;

	default:
		break;
	}
}

void Player::PlayerFindSecondaryStatBuff(SecondaryStats aSecondaryStat, int aStatBuff)
{
	switch (aSecondaryStat)
	{
	case SecondaryStats::Strength:
		myStrength += aStatBuff;
		break;

	case SecondaryStats::Dexterety:
		myDexterety += aStatBuff;
		break;

	case SecondaryStats::Charisma:
		myCharisma += aStatBuff;
		break;

	case SecondaryStats::MaxHp:
		myHp += aStatBuff;
		break;

	case SecondaryStats::Damage:
		myBaseDamage += aStatBuff;
		break;
	
	case SecondaryStats::Athletics:
		myAthletics += aStatBuff;
		break;

	case SecondaryStats::SlightOfHand:
		mySlightOfHand += aStatBuff;
		break;
	
	case SecondaryStats::Persuasion:
		myPersuasion += aStatBuff;
		break;

	case SecondaryStats::Armor:
		myArmor += aStatBuff;
		break;
	default:
		break;
	}
}

void Player::UppdatePlayerStats()
{
	float tempHp = static_cast<float>(myHp) / static_cast<float>(myMaxHp);


	myStrength = myBaseStrength;
	myDexterety = myBaseDexterety;
	myDodge = myBaseDodge;
	myCharisma = myBaseCharisma;

	myHp				= static_cast<int>(PlayerBase::ResetStats);
	myBaseDamage		= static_cast<int>(PlayerBase::ResetStats);
	myCarryingCapacity	= static_cast<int>(PlayerBase::ResetStats);
	myAthletics			= static_cast<int>(PlayerBase::ResetStats);
	mySlightOfHand		= static_cast<int>(PlayerBase::ResetStats);
	myPersuasion		= static_cast<int>(PlayerBase::ResetStats);



	if (myEquipment.GetEquipmentWeapon() != nullptr)
	{
		PlayerFindPrimeStatBuff(myEquipment.GetEquipmentWeapon()->GetPrimeStat(), myEquipment.GetEquipmentWeapon()->GetPrimeStatBuff());
		PlayerFindSecondaryStatBuff(myEquipment.GetEquipmentWeapon()->GetSecondaryStat(), myEquipment.GetEquipmentWeapon()->GetSecondaryStatBuff());
	}
	if (myEquipment.GetEquipmentHelm() != nullptr)
	{
		PlayerFindPrimeStatBuff(myEquipment.GetEquipmentHelm()->GetPrimeStat(), myEquipment.GetEquipmentHelm()->GetPrimeStatBuff());
		PlayerFindSecondaryStatBuff(myEquipment.GetEquipmentHelm()->GetSecondaryStat(), myEquipment.GetEquipmentHelm()->GetSecondaryStatBuff());

	}
	if (myEquipment.GetEquipmentArmor() != nullptr)
	{
		PlayerFindPrimeStatBuff(myEquipment.GetEquipmentArmor()->GetPrimeStat(), myEquipment.GetEquipmentArmor()->GetPrimeStatBuff());
		PlayerFindSecondaryStatBuff(myEquipment.GetEquipmentArmor()->GetSecondaryStat(), myEquipment.GetEquipmentArmor()->GetSecondaryStatBuff());

	}

	myHp				+= (myStrength * 6) + (myDexterety * 3);
	myBaseDamage		+= (myStrength * 2) + myDexterety;
	myCarryingCapacity	+= (myStrength * 2) - myDodge;
	myAthletics			+= myStrength + myDexterety;
	mySlightOfHand		+= myDodge + myDexterety;
	myPersuasion		+= myCharisma + myDodge;

	myMaxHp = myHp;
	tempHp *= static_cast<float>(myHp);
	myHp = static_cast<int>(tempHp);

}

void Player::ShowPlayerStats()
{
	UppdatePlayerStats();
	int row = 1;
	ClearArea(static_cast<int>(MenuOptions::StatsSeperatorX) + 1,
		static_cast<int>(MenuOptions::ScreenSeperatorY) + 1, 
		static_cast<int>(MenuOptions::FrameSizeEndX) - static_cast<int>(MenuOptions::StatsSeperatorX) - 2,
		static_cast<int>(MenuOptions::FrameSizeEndY) - static_cast<int>(MenuOptions::ScreenSeperatorY) - 2);
	SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	Print("HP: " + std::to_string(myHp) + "/" + std::to_string(myMaxHp));
	row += 2;

	SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	Print("STR: \t" + std::to_string(myStrength) + "\tCHA: \t" + std::to_string(myCharisma));
	row++;
	SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	Print("DEX: \t" + std::to_string(myDexterety) + "\tDodge: \t" + std::to_string(myDodge));
	row += 2;

	if (myEquipment.GetEquipmentWeapon() != nullptr)
	{
		SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		Print("Weapon: \t" + ItemTypeToString(myEquipment.GetEquipmentWeapon()->GetItemType()));
	}
	else
	{
		SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		Print("Weapon: \t No Weapon");
	}
	row++;

	if (myEquipment.GetEquipmentHelm() != nullptr)
	{
		SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		Print("Helm: \t" + ItemTypeToString(myEquipment.GetEquipmentHelm()->GetItemType()));
	}
	else
	{
		SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		Print("Helm: \t No Helm");
	}
	row++;

	if (myEquipment.GetEquipmentArmor() != nullptr)
	{
		SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		Print("Armor: \t" + ItemTypeToString(myEquipment.GetEquipmentArmor()->GetItemType()));
	}
	else
	{
		SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		Print("Armor: \t No Armor");
	}
}

void Player::PickUpItem(std::shared_ptr<Items> aItem)
{
	myInventory.push_back(aItem);
}

int Player::GetPlayerAbilityInt(PlayerBase anAbility)
{
	switch (anAbility)
	{
		case PlayerBase::AthleticsPlayerSkill:
		{
			return myAthletics;
			break;
		}
		case PlayerBase::SlightOfHandPlayerSkill:
		{
			return mySlightOfHand;
			break;
		}
		case PlayerBase::PersuasionPlayerSkill:
		{
			return myPersuasion;
			break;
		}
	}
	return 0;
}

int Player::GetPlayerHp()
{
	return myHp;
}

int Player::GetCurrentRoom()
{
	return myCurrentRoom;
}

int Player::GetNormalAttack()
{
	int damage = DamageAdjustment(myBaseDamage);
	PrintInMenu("You deal: " + std::to_string(damage) + " damage!");
	return damage;
}

void Player::UppdateHp(int aChange)
{
	myHp -= aChange;
	if (myHp <= 0)
	{
		myIsAlive = false;
	}
}

bool Player::GetIsAlive()
{
	return myIsAlive;
}

std::string* Player::GetAbilityCheckList()
{
	return myAbilityChecks;
}

std::vector<std::shared_ptr<Items>> Player::GetInventory()
{
	return myInventory;
}

void Player::EquipItem(int aItemChoise)
{
	switch (myInventory[aItemChoise]->GetItemSlot())
		{
		case ItemSlot::Weapon: 
		{
			myEquipment.SetEquipentWeapon(myInventory[aItemChoise]);
			break;
		}
		case ItemSlot::Helm:
		{
			myEquipment.SetEquipentHelm(myInventory[aItemChoise]);
			break;
		}
		case ItemSlot::Armor:
		{
			myEquipment.SetEquipentArmor(myInventory[aItemChoise]);
			break;
		}
		break;
	}
}

void Player::InventoryManagement()
{
	int playerChoiseInMenu = 0;
	while (true)
	{
		ShowPlayerStats();
		int playerTryPickUp = showItems(GetInventory(), playerChoiseInMenu);
		if (playerTryPickUp >= GetInventory().size())
		{
			return;
		}
		else
		{
			EquipItem(playerTryPickUp);
		}
	}
}