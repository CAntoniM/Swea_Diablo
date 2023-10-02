#include "Player.h"
#include "Enums.h"
#include "Quick functions.h"
#include <array>
#include <string>

Player::Player()
{
	strength			= PlayerBase::PlayerBaseStrength;
	dexterety			= PlayerBase::PlayerBaseDexterety;
	dodge				= PlayerBase::PlayerBaseDodge;
	charisma			= PlayerBase::PlayerBaseCharisma;

	hp					= (strength * 6) + (dexterety * 3);
	maxHp				= hp;
	baseDamage			= (strength * 2) + dexterety;
	carryingCapacity	= (strength * 2) - dodge;
	athletics			= strength + dexterety;
	slightOfHand		= dodge + dexterety;
	persuasion			= charisma + dodge;

	isAlive				= true;
	currentRoom			= 0;
}

void Player::ChangeRoom(int aNewRoom)
{
	currentRoom = aNewRoom;
}

void Player::ShowPlayerStats()
{
	ClearArea(MenuOptions::StatsSeperatorX + 1, 
		MenuOptions::ScreenSeperatorY + 1, 
		MenuOptions::FrameSizeEndX - StatsSeperatorX, 
		MenuOptions::FrameSizeEndY - MenuOptions::ScreenSeperatorY);
	SetCursorPosition(MenuOptions::StatsSeperatorX + 1, MenuOptions::ScreenSeperatorY + 1);
	Print("HP: " + std::to_string(hp) + "/" + std::to_string(maxHp));

	SetCursorPosition(MenuOptions::StatsSeperatorX + 1, MenuOptions::ScreenSeperatorY + 3);
	Print("STR: \t" + std::to_string(strength));
	SetCursorPosition(MenuOptions::StatsSeperatorX + 1, MenuOptions::ScreenSeperatorY + 4);
	Print("DEX: \t" + std::to_string(dexterety));
	SetCursorPosition(MenuOptions::StatsSeperatorX + 1, MenuOptions::ScreenSeperatorY + 5);
	Print("Dodge: \t" + std::to_string(dodge));

}

int Player::GetPlayerAbilityInt(int anAbility)
{
	switch (anAbility)
	{
		case PlayerBase::AthleticsPlayerSkill:
		{
			return athletics;
			break;
		}
		case PlayerBase::SlightOfHandPlayerSkill:
		{
			return slightOfHand;
			break;
		}
		case PlayerBase::PersuasionPlayerSkill:
		{
			return persuasion;
			break;
		}
	}
	return 0;
}

int Player::GetPlayerHp()
{
	return hp;
}

int Player::GetCurrentRoom()
{
	return currentRoom;
}

int Player::GetNormalAttack()
{
	int damage = DamageAdjustment(baseDamage);
	PrintInMenu("You deal: " + std::to_string(damage) + " damage!");
	return damage;
}

void Player::UppdateHp(int aChange)
{
	hp -= aChange;
	if (hp <= 0)
	{
		isAlive = false;
	}
}

bool Player::GetIsAlive()
{
	return isAlive;
}

std::string* Player::GetAbilityCheckList()
{
	return abilityChecks;
}
