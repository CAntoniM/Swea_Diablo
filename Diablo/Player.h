#pragma once
class Player
{
public:
	Player();
	void UppdateHp(int change); 
	int GetNormalAttack();
	int hp;
	bool GetIsAlive();


private:
	int strength;
	int dexterety;
	int dodge;
	bool isAlive;
};

