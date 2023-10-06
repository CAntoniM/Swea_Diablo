#pragma once

class Enemy
{
public:
	Enemy();
	void ShowTarget(int aStartX, int aStartY, bool aTarget);
	void PrintSprite(int aStartX, int aStartY);
	void UppdateHp(int aChange);
	int GetHP();
	int GetNormalAttack();
	const int GetSpriteSizeX();
	bool IsAlive();



private:
	int _hp;
	int _strength;
	int _dexterety;
	int _dodge;
	bool _is_alive;
	const int _sprite_size_x = 16;
	const int _sprite_size_y = 13;
};

