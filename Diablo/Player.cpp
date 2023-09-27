#include "Player.h"
#include "Enums.h"
#include "Quick functions.h"

Player::Player()
{
	hp			= PlayerBase::PlayerBaseHp;
	strength	= PlayerBase::PlayerBaseStrength;
	dexterety	= PlayerBase::PlayerBaseDexterety;
	dodge		= PlayerBase::PlayerBaseDodge;
	isAlive		= true;
}

int Player::GetNormalAttack()
{
	int damage = DamageAdjustment(strength);
	PrintInMenu("You deal: " + std::to_string(damage) + " damage!");
	return damage;
}

void Player::UppdateHp(int change)
{
	hp -= change;
	if (hp <= 0)
	{
		isAlive = false;
	}
}

bool Player::GetIsAlive()
{
	return isAlive;
}
