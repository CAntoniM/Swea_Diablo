#pragma once

class Enemy
{
public:
	Enemy();
	void ShowTarget(int aStartX, int aStartY, bool aTarget);
	void PrintEnemySprite(int aStartX, int aStartY);
	void UppdateHp(int aChange);
	int GetEnemyHp();
	int GetNormalAttack();
	const int GetSpriteSizeX();
	bool GetIsAlive();



private:
	int hp;
	int strength;
	int dexterety;
	int dodge;
	bool isAlive;
	const int spriteSizeX = 16;
	const int spriteSizeY = 13;
};

