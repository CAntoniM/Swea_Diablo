#include "UI.h"
#include "Quick functions.h"
#include <Windows.h>
#include "Enemy.h"
#include "Door.h"
#include "Room.h"
#include "Enums.h"


void DrawFrame()
{
	SetCursorPosition(0, 0);
	for (int y = 0; y < MenuOptions::FrameSizeEndY; y++)
	{
		for (int x = 0; x < MenuOptions::FrameSizeEndX; x++)
		{
			if (y == MenuOptions::FrameSizeStartY || y == MenuOptions::FrameSizeEndY - 1 || y == MenuOptions::ScreenSeperatorY)
			{
				SetCursorPosition(x, y);
				std::cout << "-";
			}
			else if (x == MenuOptions::FrameSizeStartX || x == MenuOptions::FrameSizeEndX - 1)
			{
				SetCursorPosition(x, y);
				std::cout << "|";
			}
			else if (x == MenuOptions::StatsSeperatorX && y > MenuOptions::ScreenSeperatorY && y < MenuOptions::FrameSizeEndY)
			{
				SetCursorPosition(x, y);
				std::cout << "|";

			}
		}
	}
	std::cout << std::endl;
}

void MenuControll(std::string aMenuList[], int aMenuSize, int& aPlayerChoiseInMenu, int aStartingYPosision)
{
	while (true)
	{
		ClearMenu();
		SetCursorPosition(MenuOptions::menyStartX, MenuOptions::menyStartY);
		for (int i = 0; i < aMenuSize; ++i)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			if (GetConsoleScreenBufferInfo(hConsole, &csbi))
			{
				COORD cursorPosition = csbi.dwCursorPosition;
				int x = cursorPosition.X + 1;
				int y = cursorPosition.Y;
				SetCursorPosition(x, y);
			}
			if (i == aPlayerChoiseInMenu)
			{
				SetColor(ColorInt::GreenColorText);
				std::cout << "\t" << aMenuList[i] << "\t <---" << std::endl;
			}
			else
			{
				
				SetColor(ColorInt::WhiteColorText);
				std::cout << aMenuList[i] << std::endl;
			}
		}
		SetColor(ColorInt::WhiteColorText);
		switch (ButtonPress())
		{
		case MenuOptions::MenuListUp:
		{
			if (aPlayerChoiseInMenu > 0)
			{
				aPlayerChoiseInMenu--;
			}
			else
			{
				aPlayerChoiseInMenu = aMenuSize - 1;
			}
			break;
		}
		case MenuOptions::MenuListDown:
		{
			if (aPlayerChoiseInMenu < aMenuSize - 1)
			{
				aPlayerChoiseInMenu++;
			}
			else
			{
				aPlayerChoiseInMenu = 0;
			}
			break;
		}
		case MenuOptions::MenuListOption:
		{
			return;
			break;
		}
		}
	}
}

void ShowEnemy(std::vector<Enemy>& aList)
{
	ClearGame();
	int ofSetX = 3;
	for (int i = 0; i < aList.size(); i++)
	{
		if (aList[i].GetIsAlive() == true)
		{
			aList[i].PrintEnemySprite(gameStartX + ofSetX, gameStartY + 2);
			ofSetX += aList[i].GetSpriteSizeX() + 10;
		}
		else
		{
			ofSetX += aList[i].GetSpriteSizeX() + 10;
		}

	}
}

int ChoseEnemy(std::vector<Enemy>& aList)
{
	bool missingTarget = true;
	int playerChoise = 0;
	while (true)
	{
		int ofSetX = 3;
		ClearArea(MenuOptions::gameStartX + ofSetX, MenuOptions::gameStartY, FrameSizeEndX - ofSetX);
		for (int i = 0; i < aList.size(); i++)
		{
			if (i == playerChoise)
			{
				aList[i].ShowTarget(MenuOptions::gameStartX + ofSetX, MenuOptions::gameStartY + 2, true);
			
			}
			else
			{
				aList[i].ShowTarget(MenuOptions::gameStartX + ofSetX, MenuOptions::gameStartY + 2, false);
			}	
			ofSetX += aList[i].GetSpriteSizeX() + 10;
			
		}

		switch (ButtonPress())
		{
		case MenuOptions::MenuListLeft:
		{
			if (playerChoise > 0)
			{
				playerChoise--;
			}
			else
			{
				playerChoise = static_cast<int>(aList.size()) - 1;
			}
			break;
		}
		case MenuOptions::MenuListRight:
		{
			if (playerChoise < static_cast<int>(aList.size()) - 1)
			{
				playerChoise++;
			}
			else
			{
				playerChoise = 0;
			}
			break;
		}
		case MenuOptions::MenuListOption:
		{
			if (aList[playerChoise].GetIsAlive() == true)
			{
				return playerChoise;
			}
			else
			{
				if (missingTarget == true)
				{
					ClearMenu();
					PrintInMenu("There is no monster there, try again!");
					Sleep();
					missingTarget = false;
				}

			}
			break;
		}
		}
	}
}

int ShowDoors(std::vector<Door>& aVectorOfDoors, std::vector<Room>& aVectorOfRooms, int aCurrentRoom)
{
	int playerChoise = 0;

	while (true)
	{
		int extraSpace = 0;
		ClearGame();

		for (int i = 0; i < aVectorOfDoors.size(); i++)
		{
			if (i == playerChoise)
			{
				PrintDoorSprite(MenuOptions::gameStartX + ExtraInts::OfSet + (DoorBase::doorSpriteSizeX * i) + extraSpace, MenuOptions::gameStartY,
					true, aVectorOfRooms[aVectorOfDoors[i].GetConnectingRoom(aCurrentRoom)].GetRoomExplored(), aVectorOfRooms[aVectorOfDoors[i].GetConnectingRoom(aCurrentRoom)].GetRoomName());
				extraSpace += 3;
			}
			else
			{
				PrintDoorSprite(MenuOptions::gameStartX + ExtraInts::OfSet + (DoorBase::doorSpriteSizeX * i) + extraSpace, MenuOptions::gameStartY, 
					false, aVectorOfRooms[aVectorOfDoors[i].GetConnectingRoom(aCurrentRoom)].GetRoomExplored(), aVectorOfRooms[aVectorOfDoors[i].GetConnectingRoom(aCurrentRoom)].GetRoomName());
				extraSpace += 3;
			}
		}

		switch (ButtonPress())
		{
			case MenuOptions::MenuListLeft:
			{
				if (playerChoise > 0)
				{
					playerChoise--;
				}
				else
				{
					playerChoise = aVectorOfDoors.size() - 1;
				}
				break;
			}
			case MenuOptions::MenuListRight:
			{
				if (playerChoise < aVectorOfDoors.size() - 1)
				{
					playerChoise++;
				}
				else
				{
					playerChoise = 0;
				}
				break;
			}
			case MenuOptions::MenuListOption:
			{
				return playerChoise;
				break;
			}
		}
	}
}

void PrintDoorSprite(int aStartX, int aStartY, bool aTarget, bool aRoomExplored, std::string aRoomName)
{
	if (aRoomExplored == false)
	{
		SetCursorPosition(aStartX, aStartY);
		std::cout << "     ______     " << std::endl;
		SetCursorPosition(aStartX, aStartY + 1);
		std::cout << "  ,-' ;  ! `-.  " << std::endl;
		SetCursorPosition(aStartX, aStartY + 2);
		std::cout << " / :  !  :  . \\ " << std::endl;
		SetCursorPosition(aStartX, aStartY + 3);
		std::cout << "|_ ;   __:  ;  |" << std::endl;
		SetCursorPosition(aStartX, aStartY + 4);
		std::cout << ")| .  :)(.  !  |" << std::endl;
		SetCursorPosition(aStartX, aStartY + 5);
		std::cout << "|     (##)  _  |" << std::endl;
		SetCursorPosition(aStartX, aStartY + 6);
		std::cout << "|  :  ;`'  (_) (" << std::endl;
		SetCursorPosition(aStartX, aStartY + 7);
		std::cout << "|  :  :  .     |" << std::endl;
		SetCursorPosition(aStartX, aStartY + 8);
		std::cout << ")_ !  ,  ;  ;  |" << std::endl;
		SetCursorPosition(aStartX, aStartY + 9);
		std::cout << "|| .  .  :  :  |" << std::endl;
		SetCursorPosition(aStartX, aStartY + 10);
		std::cout << "|  .  |  :  .  |" << std::endl;
		SetCursorPosition(aStartX, aStartY + 11);
		std::cout << "|___.------.___|" << std::endl;
		SetCursorPosition(aStartX, aStartY + 13);
		std::cout << "      ???       " << std::endl;
	}
	else if (aRoomExplored == true)
	{
		SetCursorPosition(aStartX, aStartY);
		std::cout << "     ______     " << std::endl;
		SetCursorPosition(aStartX, aStartY + 1);
		std::cout << "  ,-'      `-.  " << std::endl;
		SetCursorPosition(aStartX, aStartY + 2);
		std::cout << " /            \\ " << std::endl;
		SetCursorPosition(aStartX, aStartY + 3);
		std::cout << "|              |" << std::endl;
		SetCursorPosition(aStartX, aStartY + 4);
		std::cout << "|              |" << std::endl;
		SetCursorPosition(aStartX, aStartY + 5);
		std::cout << "|              |" << std::endl;
		SetCursorPosition(aStartX, aStartY + 6);
		std::cout << "|              |" << std::endl;
		SetCursorPosition(aStartX, aStartY + 7);
		std::cout << "|              |" << std::endl;
		SetCursorPosition(aStartX, aStartY + 8);
		std::cout << "|              |" << std::endl;
		SetCursorPosition(aStartX, aStartY + 9);
		std::cout << "|              |" << std::endl;
		SetCursorPosition(aStartX, aStartY + 10);
		std::cout << "|              |" << std::endl;
		SetCursorPosition(aStartX, aStartY + 11);
		std::cout << "|______________|" << std::endl;
		SetCursorPosition(aStartX, aStartY + 13);
		std::cout <<"   " << aRoomName << std::endl;
	}

	if (aTarget)
	{
		SetCursorPosition(aStartX, aStartY + 15);
		SetColor(ColorInt::RedColorText);
		for (int j = 0; j < DoorBase::doorSpriteSizeX; j++)
		{
			if (j == 0 || j == DoorBase::doorSpriteSizeX - 1)
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
		ClearArea(aStartX, aStartY + 15, DoorBase::doorSpriteSizeX);

	}
}