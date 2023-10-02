#include "Enemy.h"
#include "Enums.h"
#include "Quick functions.h"

Enemy::Enemy()
{
	hp			= EnemyBase::EnemyBaseHp +			RandomNumber(0, 10);
	strength	= EnemyBase::EnemyBaseStrength +	RandomNumber(0, 5);
	dexterety	= EnemyBase::EnemyBaseDexterety +	RandomNumber(0, 5);
	dodge		= EnemyBase::EnemyBaseDodge +		RandomNumber(0, 5);
	isAlive		= EnemyBase::EnemyLivingState;
}

int Enemy::GetNormalAttack()
{
	int damage = DamageAdjustment(strength);
	PrintInMenu("The enemy deals: " + std::to_string(damage) + " damage!");
	return damage; 
}

void Enemy::UppdateHp(int aChange)
{
	hp -= aChange;
	if (hp <= 0)
	{
		isAlive = false;
	}
}

int Enemy::GetEnemyHp()
{
	return hp;
}


bool Enemy::GetIsAlive()
{
	return isAlive;
}

const int Enemy::GetSpriteSizeX()
{
	return spriteSizeX;
}

void Enemy::ShowTarget(int aStartX, int aStartY, bool aTarget)
{
	if (aTarget == true)
	{
		SetColor(ColorInt::RedColorText);
		SetCursorPosition(aStartX, aStartY + spriteSizeY);
		for (int j = 0; j < spriteSizeX; j++)
		{
			if (j == 0 || j == spriteSizeX - 1)
			{
				std::cout << "-";
			}
			else
			{
				std::cout << "=";
			}
		}
		SetColor(ColorInt::WhiteColorText);
	}
	else
	{
		SetCursorPosition(aStartX, aStartY + spriteSizeY);
		for (int j = 0; j < spriteSizeX; j++)
		{
			std::cout << " ";
		}
	}
}

void Enemy::PrintEnemySprite(int aStartX, int aStartY)
{
	SetCursorPosition(aStartX, aStartY);
	std::cout << "  @#@@@@##(@@@  " << std::endl;    
	SetCursorPosition(aStartX, aStartY + 1);
	std::cout << "@@             @" << std::endl;     
	SetCursorPosition(aStartX, aStartY + 2);
	std::cout << "@@   @@   @@   @" << std::endl;     
	SetCursorPosition(aStartX, aStartY + 3);
	std::cout << "@@             @" << std::endl;     
	SetCursorPosition(aStartX, aStartY + 4);
	std::cout << "@@             @" << std::endl;     
	SetCursorPosition(aStartX, aStartY + 5);
	std::cout << "%%#@#&@  #@(&*, " << std::endl;     
	SetCursorPosition(aStartX, aStartY + 6);
	std::cout << "  (@&#     %@&%/" << std::endl;
	SetCursorPosition(aStartX, aStartY + 7);
	std::cout << "   @&&&  (&&@&& " << std::endl;
	SetCursorPosition(aStartX, aStartY + 8);
	std::cout << "   @%&@@@@@(@,  " << std::endl;     
	SetCursorPosition(aStartX, aStartY + 9);
	std::cout << " .@%@/     @(&@ " << std::endl;         

	SetCursorPosition(aStartX + spriteSizeX/4, aStartY + 11);
	std::cout << "Hp: " << hp << std::endl;
}