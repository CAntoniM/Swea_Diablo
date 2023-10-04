#include "Player.h"
#include "Enums.h"
#include "Quick functions.h"
#include "Items.h"
#include <array>
#include <string>

Player::Player()
{
	myInventory;

	myStrength			= static_cast<int>(PlayerBase::PlayerBaseStrength);
	myDexterety			= static_cast<int>(PlayerBase::PlayerBaseDexterety);
	myDodge				= static_cast<int>(PlayerBase::PlayerBaseDodge);
	myCharisma			= static_cast<int>(PlayerBase::PlayerBaseCharisma);

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

void Player::ShowPlayerStats()
{
	int row = 1;
	ClearArea(static_cast<int>(MenuOptions::StatsSeperatorX) + 1,
		static_cast<int>(MenuOptions::ScreenSeperatorY) + 1, 
		static_cast<int>(MenuOptions::FrameSizeEndX) - static_cast<int>(MenuOptions::StatsSeperatorX) - 2,
		static_cast<int>(MenuOptions::FrameSizeEndY) - static_cast<int>(MenuOptions::ScreenSeperatorY) - 2);
	SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	Print("HP: " + std::to_string(myHp) + "/" + std::to_string(myMaxHp));
	row += 2;

	SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	Print("STR: \t" + std::to_string(myStrength));
	row++;
	SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	Print("DEX: \t" + std::to_string(myDexterety));
	row++;
	SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	Print("CHA: \t" + std::to_string(myCharisma));
	row++;
	SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	Print("Dodge: \t" + std::to_string(myDodge));

}

void Player::PickUpItem(Items aItem)
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
