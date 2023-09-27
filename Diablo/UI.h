#pragma once
#include <string>
#include <vector>
#include "Enemy.h"

class UI
{
public:
	void DrawFrame();
	void MenuControll(std::string aMenuList[], int aMenuSize, int aPlayerChoiseInMenu, int aStartingYPosision);
	void ShowEnemy(std::vector<Enemy>& aList);
	int ChoseEnemy(std::vector<Enemy>& aList);

private:
};

