
#include <iostream>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Quick functions.h"
#include "UI.h"

bool LivingEnemies(std::vector<Enemy>& enemyList)
{
	bool livingEnemie = false;
	for (int i = 0; i < enemyList.size(); i++)
	{
		if (enemyList[i].GetIsAlive() == true)
		{
			livingEnemie = true;
		}
	}
	return livingEnemie;
}



int main()
{
	UI ui;
	ui.DrawFrame();

	std::vector<Enemy> enemyList;
	Player player;
	int playerTarget = 0;
	
	int NumberOfEnemeis = 3; // RandomNumber(RoomBase::MinNumberOfEnemis, RoomBase::MaxNumberOfEnemis); 
	for (int i = 0; i < NumberOfEnemeis; i++)
	{
		Enemy enemy;
		enemyList.push_back(enemy);

	}

	while (player.GetIsAlive() == true && LivingEnemies(enemyList)== true)
	{
		//Print("Player HP: " + std::to_string(player.hp));
		ui.ShowEnemy(enemyList);
		playerTarget = ui.ChoseEnemy(enemyList);
		enemyList[playerTarget].UppdateHp(player.GetNormalAttack());
		Sleep();
		for (int i = 0; i < NumberOfEnemeis; i++)
		{
			if (enemyList[i].hp > 0)
			{
				PrintInMenu("The enemy is retaliating and attacking you!");
				player.UppdateHp(enemyList[i].GetNormalAttack());
				Sleep();
			}
		}
	}
	
	if (player.hp <= 0)
	{
		PrintInMenu("Hell is taking over after your defet!");
	}
	else
	{
		PrintInMenu("You have defeted Diablo!");
	}

}

