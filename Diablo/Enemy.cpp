#include "Enemy.h"
#include "Enums.h"
#include "Quick functions.h"

Enemy::Enemy()
{
	myHp			= static_cast<int>(EnemyBase::EnemyBaseHp)			+ RandomNumber(0, 10);
	myStrength		= static_cast<int>(EnemyBase::EnemyBaseStrength)	+ RandomNumber(0, 5);
	myDexterety		= static_cast<int>(EnemyBase::EnemyBaseDexterety)	+ RandomNumber(0, 5);
	myDodge			= static_cast<int>(EnemyBase::EnemyBaseDodge)		+ RandomNumber(0, 5);
	myIsAlive		= static_cast<bool>(EnemyBase::EnemyLivingState);
}

int Enemy::GetNormalAttack()
{
	int damage = DamageAdjustment(myStrength);
	PrintInMenu("The enemy deals: " + std::to_string(damage) + " damage!");
	return damage; 
}

void Enemy::UppdateHp(int aChange)
{
	myHp -= aChange;
	if (myHp <= 0)
	{
		myIsAlive = false;
	}
}

int Enemy::GetEnemyHp()
{
	return myHp;
}


bool Enemy::GetIsAlive()
{
	return myIsAlive;
}

const int Enemy::GetSpriteSizeX()
{
	return mySpriteSizeX;
}

void Enemy::ShowTarget(int aStartX, int aStartY, bool aTarget)
{
	if (aTarget == true)
	{
		SetColor(ColorInt::RedColorText);
		SetCursorPosition(aStartX, aStartY + mySpriteSizeY);
		for (int j = 0; j < mySpriteSizeX; j++)
		{
			if (j == 0 || j == mySpriteSizeX - 1)
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
		SetCursorPosition(aStartX, aStartY + mySpriteSizeY);
		for (int j = 0; j < mySpriteSizeX; j++)
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

	SetCursorPosition(aStartX + mySpriteSizeX/4, aStartY + 11);
	std::cout << "Hp: " << myHp << std::endl;
}