#include "Enemy.h"
#include "Enums.h"
#include "Quick_functions.h"

Enemy::Enemy()
{
	_hp			    = static_cast<int>(EnemyBase::EnemyBaseHp)			+ RandomNumber(0, 10);
	_strength		= static_cast<int>(EnemyBase::EnemyBaseStrength)	+ RandomNumber(0, 5);
	_dexterety		= static_cast<int>(EnemyBase::EnemyBaseDexterety)	+ RandomNumber(0, 5);
	_dodge			= static_cast<int>(EnemyBase::EnemyBaseDodge)		+ RandomNumber(0, 5);
	_is_alive		= static_cast<bool>(EnemyBase::EnemyLivingState);
}

int Enemy::GetNormalAttack()
{
	int damage = DamageAdjustment(_strength);
	PrintInMenu("The enemy deals: " + std::to_string(damage) + " damage!");
	return damage; 
}

void Enemy::UppdateHp(int damage)
{
	_hp -= damage;
	_is_alive = (_hp <= 0);
}

int Enemy::GetHP()
{
	return _hp;
}


bool Enemy::IsAlive()
{
	return _is_alive;
}

const int Enemy::GetSpriteSizeX()
{
	return _sprite_size_x;
}

void Enemy::ShowTarget(int start_x, int start_y, bool _target)
{
	if (_target)
	{
		SetColor(ColorInt::RedColorText);
		SetCursorPosition(start_x, start_y + _sprite_size_y);
		for (int j = 0; j < _sprite_size_x; j++)
		{
			if (j == 0 || j == _sprite_size_x - 1)
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
		SetCursorPosition(start_x, start_y + _sprite_size_y);
		for (int j = 0; j < _sprite_size_x; j++)
		{
			std::cout << " ";
		}
	}
}

void Enemy::PrintSprite(int start_x, int start_y)
{
	SetCursorPosition(start_x, start_y);
	std::cout << "  @#@@@@##(@@@  \n";    
	SetCursorPosition(start_x, start_y + 1);
	std::cout << "@@             @\n";     
	SetCursorPosition(start_x, start_y + 2);
	std::cout << "@@   @@   @@   @\n";     
	SetCursorPosition(start_x, start_y + 3);
	std::cout << "@@             @\n";     
	SetCursorPosition(start_x, start_y + 4);
	std::cout << "@@             @\n";     
	SetCursorPosition(start_x, start_y + 5);
	std::cout << "%%#@#&@  #@(&*, \n";     
	SetCursorPosition(start_x, start_y + 6);
	std::cout << "  (@&#     %@&%/\n";
	SetCursorPosition(start_x, start_y + 7);
	std::cout << "   @&&&  (&&@&& \n";
	SetCursorPosition(start_x, start_y + 8);
	std::cout << "   @%&@@@@@(@,  \n";     
	SetCursorPosition(start_x, start_y + 9);
	std::cout << " .@%@/     @(&@ \n";         

	SetCursorPosition(start_x + _sprite_size_x/4, start_y + 11);
	std::cout << "Hp: " << _hp << std::endl;
}