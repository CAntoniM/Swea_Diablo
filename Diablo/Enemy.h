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
	int myHp;
	int myStrength;
	int myDexterety;
	int myDodge;
	bool myIsAlive;
	const int mySpriteSizeX = 16;
	const int mySpriteSizeY = 13;
};

