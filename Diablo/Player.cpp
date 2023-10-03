#include "Player.h"
#include "Enums.h"
#include "Quick functions.h"
#include <array>
#include <string>

Player::Player()
{
	myStrength			= PlayerBase::PlayerBaseStrength;
	myDexterety			= PlayerBase::PlayerBaseDexterety;
	myDodge				= PlayerBase::PlayerBaseDodge;
	myCharisma			= PlayerBase::PlayerBaseCharisma;

	myHp					= (myStrength * 6) + (myDexterety * 3);
	myMaxHp				= myHp;
	myBaseDamage			= (myStrength * 2) + myDexterety;
	myCarryingCapacity	= (myStrength * 2) - myDodge;
	myAthletics			= myStrength + myDexterety;
	mySlightOfHand		= myDodge + myDexterety;
	myPersuasion			= myCharisma + myDodge;

	myIsAlive				= true;
	myCurrentRoom			= 0;
}

void Player::ChangeRoom(int aNewRoom)
{
	myCurrentRoom = aNewRoom;
}

void Player::ShowPlayerStats()
{
	int row = 1;
	ClearArea(MenuOptions::StatsSeperatorX + 1, 
		MenuOptions::ScreenSeperatorY + 1, 
		MenuOptions::FrameSizeEndX - StatsSeperatorX - 2, 
		MenuOptions::FrameSizeEndY - MenuOptions::ScreenSeperatorY - 2);
	SetCursorPosition(MenuOptions::StatsSeperatorX + 1, MenuOptions::ScreenSeperatorY + row);
	Print("HP: " + std::to_string(myHp) + "/" + std::to_string(myMaxHp));
	row += 2;

	SetCursorPosition(MenuOptions::StatsSeperatorX + 1, MenuOptions::ScreenSeperatorY + row);
	Print("STR: \t" + std::to_string(myStrength));
	row++;
	SetCursorPosition(MenuOptions::StatsSeperatorX + 1, MenuOptions::ScreenSeperatorY + row);
	Print("DEX: \t" + std::to_string(myDexterety));
	row++;
	SetCursorPosition(MenuOptions::StatsSeperatorX + 1, MenuOptions::ScreenSeperatorY + row);
	Print("CHA: \t" + std::to_string(myCharisma));
	row++;
	SetCursorPosition(MenuOptions::StatsSeperatorX + 1, MenuOptions::ScreenSeperatorY + row);
	Print("Dodge: \t" + std::to_string(myDodge));

}

int Player::GetPlayerAbilityInt(int anAbility)
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
