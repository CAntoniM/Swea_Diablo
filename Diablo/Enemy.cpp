#include "Enemy.h"
#include "Enums.h"
#include "UI.h"
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
	ui::PrintInMenu("The enemy deals: " + std::to_string(damage) + " damage!");
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
		ui::SetColor(ColorInt::RedColorText);
		ui::SetCursorPosition(start_x, start_y + _sprite_size_y);
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
		ui::SetColor(ColorInt::WhiteColorText);
	}
	else
	{
		ui::SetCursorPosition(start_x, start_y + _sprite_size_y);
		for (int j = 0; j < _sprite_size_x; j++)
		{
			std::cout << " ";
		}
	}
}

void Enemy::PrintSprite(int x, int y)
{
	ui::SetCursorPosition(x, y);
	std::cout << "  @#@@@@##(@@@  \n";    
	ui::SetCursorPosition(x, ++y);
	std::cout << "@@             @\n";     
	ui::SetCursorPosition(x, ++y);
	std::cout << "@@   @@   @@   @\n";     
	ui::SetCursorPosition(x, ++y);
	std::cout << "@@             @\n";     
	ui::SetCursorPosition(x, ++y);
	std::cout << "@@             @\n";     
	ui::SetCursorPosition(x, ++y);
	std::cout << "%%#@#&@  #@(&*, \n";     
	ui::SetCursorPosition(x, ++y);
	std::cout << "  (@&#     %@&%/\n";
	ui::SetCursorPosition(x, ++y);
	std::cout << "   @&&&  (&&@&& \n";
	ui::SetCursorPosition(x, ++y);
	std::cout << "   @%&@@@@@(@,  \n";     
	ui::SetCursorPosition(x, ++y);
	std::cout << " .@%@/     @(&@ \n";         

	y += 2;
	ui::SetCursorPosition(x + _sprite_size_x/4, y);
	std::cout << "Hp: " << _hp << std::endl;
}