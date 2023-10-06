#include "UI.h"
#include "Quick_functions.h"
#include <Windows.h>
#include <vector>
#include "Enemy.h"
#include "Door.h"
#include "Room.h"
#include "Enums.h"
#include "Item.h"



void DrawFrame()
{
	SetCursorPosition(0, 0);
	for (int y = 0; y < static_cast<int>(MenuOptions::FrameSizeEndY); y++)
	{
		for (int x = 0; x < static_cast<int>(MenuOptions::FrameSizeEndX); x++)
		{
			if (y == static_cast<int>(MenuOptions::FrameSizeStartY) || y == static_cast<int>(MenuOptions::FrameSizeEndY) - 1 || y == static_cast<int>(MenuOptions::ScreenSeperatorY))
			{
				SetCursorPosition(x, y);
				std::cout << "-";
			}
			else if (x == static_cast<int>(MenuOptions::FrameSizeStartX) || x == static_cast<int>(MenuOptions::FrameSizeEndX) - 1)
			{
				SetCursorPosition(x, y);
				std::cout << "|";
			}
			else if (x == static_cast<int>(MenuOptions::StatsSeperatorX) && y > static_cast<int>(MenuOptions::ScreenSeperatorY) && y < static_cast<int>(MenuOptions::FrameSizeEndY))
			{
				SetCursorPosition(x, y);
				std::cout << "|";

			}
		}
	}
	std::cout << std::endl;
}

void MenuControll(std::string menu_items[], int menu_size, int& users_menu_choise, int starting_y_posision)
{
	while (true)
	{
		ClearMenu();
		SetCursorPosition(static_cast<int>(MenuOptions::menyStartX), static_cast<int>(MenuOptions::menyStartY));
		for (int i = 0; i < menu_size; ++i)
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
			if (i == users_menu_choise)
			{
				SetColor(ColorInt::GreenColorText);
				std::cout << "\t" << menu_items[i] << "\t <---" << std::endl;
			}
			else
			{
				
				SetColor(ColorInt::WhiteColorText);
				std::cout << menu_items[i] << std::endl;
			}
		}
		SetColor(ColorInt::WhiteColorText);
		switch (ButtonPress())
		{
		case MenuOptions::MenuListUp:
		{
			if (users_menu_choise > 0)
			{
				users_menu_choise--;
			}
			else
			{
				users_menu_choise = menu_size - 1;
			}
			break;
		}
		case MenuOptions::MenuListDown:
		{
			if (users_menu_choise < menu_size - 1)
			{
				users_menu_choise++;
			}
			else
			{
				users_menu_choise = 0;
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

int showItems(std::vector<std::shared_ptr<Item>> items, int& player_choise_in_menu)
{
	if (player_choise_in_menu > static_cast<int>(items.size()))
	{
		player_choise_in_menu--;
	}
	while (true)
	{

		int x;
		int y;

		ClearGameView();
		SetCursorPosition(static_cast<int>(MenuOptions::gameStartX), static_cast<int>(MenuOptions::gameStartX) + 1);
		for (int i = 0; i < static_cast<int>(items.size()); ++i)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO csbi; 

			if (GetConsoleScreenBufferInfo(hConsole, &csbi)) 
			{
				COORD cursorPosition = csbi.dwCursorPosition;
				x = cursorPosition.X + 1;
				y = cursorPosition.Y;
				SetCursorPosition(x, y);
			}

			if (i == player_choise_in_menu)
			{
				SetColor(ColorInt::GreenColorText);
				std::cout << "\t" << toString(items[i]->GetItemType()) << " <---";
				SetColor(ColorInt::WhiteColorText);

				if (GetConsoleScreenBufferInfo(hConsole, &csbi))
				{
					COORD cursorPosition = csbi.dwCursorPosition;
					x = static_cast<int>(MenuOptions::ItemStatsPrimeStartX);
					y = cursorPosition.Y;
					SetCursorPosition(x, y);
				}
				std::cout << toString(items[i]->GetPrimeStat()) << ": +" << items[i]->GetPrimeStatBuff();
				
				if (GetConsoleScreenBufferInfo(hConsole, &csbi))
				{
					COORD cursorPosition = csbi.dwCursorPosition;
					x = static_cast<int>(MenuOptions::ItemStatsSecondaryStartX);
					y = cursorPosition.Y;
					SetCursorPosition(x, y);
				}
				std::cout << toString(items[i]->GetSecondaryStat()) << ": +" <<items[i]->GetSecondaryStatBuff() << std::endl;
			}
			else
			{

				SetColor(ColorInt::WhiteColorText);
				std::cout << toString(items[i]->GetItemType());
				
				if (GetConsoleScreenBufferInfo(hConsole, &csbi))
				{
					COORD cursorPosition = csbi.dwCursorPosition;
					x = static_cast<int>(MenuOptions::ItemStatsPrimeStartX);
					y = cursorPosition.Y;
					SetCursorPosition(x, y);
				}
				std::cout << toString(items[i]->GetPrimeStat()) << ": +" << items[i]->GetPrimeStatBuff();
				
				if (GetConsoleScreenBufferInfo(hConsole, &csbi))
				{
					COORD cursorPosition = csbi.dwCursorPosition;
					x = static_cast<int>(MenuOptions::ItemStatsSecondaryStartX);
					y = cursorPosition.Y;
					SetCursorPosition(x, y);
				}
				std::cout << toString(items[i]->GetSecondaryStat()) << ": +" << items[i]->GetSecondaryStatBuff() << std::endl;

			}
		}

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		if (GetConsoleScreenBufferInfo(hConsole, &csbi))
		{
			COORD cursorPosition = csbi.dwCursorPosition;
			x = cursorPosition.X + 1;
			y = cursorPosition.Y;
			SetCursorPosition(x, y);
		}

		if (player_choise_in_menu == static_cast<int>(items.size()))
		{
			SetColor(ColorInt::GreenColorText);
			std::cout << "\tReturn  <---" << std::endl;
		}
		else
		{
			SetColor(ColorInt::WhiteColorText);
			std::cout << "Return" << std::endl;

		}
		SetColor(ColorInt::WhiteColorText);

		switch (ButtonPress())
		{
		case MenuOptions::MenuListUp:
		{
			if (player_choise_in_menu > 0)
			{
				player_choise_in_menu--;
			}
			else
			{
				player_choise_in_menu = static_cast<int>(items.size());
			}
			break;
		}
		case MenuOptions::MenuListDown:
		{
			if (player_choise_in_menu < static_cast<int>(items.size()))
			{
				player_choise_in_menu++;
			}
			else
			{
				player_choise_in_menu = 0;
			}
			break;
		}
		case MenuOptions::MenuListOption:
		{
			return player_choise_in_menu;
			break;
		}
		}
	}
}

void ShowEnemy(std::vector<Enemy>& aList)
{
	ClearGameView();
	int ofSetX = 3;
	for (int i = 0; i < aList.size(); i++)
	{
		if (aList[i].IsAlive() == true)
		{
			aList[i].PrintSprite(static_cast<int>(MenuOptions::gameStartX) + ofSetX, static_cast<int>(MenuOptions::gameStartY) + 2);
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
		ClearArea(static_cast<int>(MenuOptions::gameStartX) + ofSetX, static_cast<int>(MenuOptions::gameStartY), static_cast<int>(MenuOptions::FrameSizeEndX) - ofSetX);
		for (int i = 0; i < aList.size(); i++)
		{
			if (i == playerChoise)
			{
				aList[i].ShowTarget(static_cast<int>(MenuOptions::gameStartX) + ofSetX, static_cast<int>(MenuOptions::gameStartY) + 2, true);
			
			}
			else
			{
				aList[i].ShowTarget(static_cast<int>(MenuOptions::gameStartX) + ofSetX, static_cast<int>(MenuOptions::gameStartY) + 2, false);
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
			if (aList[playerChoise].IsAlive() == true)
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

int ShowDoors(std::vector<std::shared_ptr<Door>> aVectorOfDoors, std::vector<Room>& aVectorOfRooms, int aCurrentRoom)
{
	int playerChoise = 0;

	while (true)
	{
		int extraSpace = 0;
		ClearGameView();

		for (int i = 0; i < aVectorOfDoors.size(); i++)
		{
			if (i == playerChoise)
			{
				PrintDoorSprite(static_cast<int>(MenuOptions::gameStartX) + static_cast<int>(ExtraInts::OfSet) + (static_cast<int>(DoorBase::doorSpriteSizeX) * i) + extraSpace, static_cast<int>(MenuOptions::gameStartY),
					true, aVectorOfRooms[aVectorOfDoors[i]->GetConnectingRoom(aCurrentRoom)].GetRoomExplored(), aVectorOfRooms[aVectorOfDoors[i]->GetConnectingRoom(aCurrentRoom)].GetRoomName());
				extraSpace += 3;
			}
			else
			{
				PrintDoorSprite(static_cast<int>(MenuOptions::gameStartX) + static_cast<int>(ExtraInts::OfSet) + (static_cast<int>(DoorBase::doorSpriteSizeX) * i) + extraSpace, static_cast<int>(MenuOptions::gameStartY),
					false, aVectorOfRooms[aVectorOfDoors[i]->GetConnectingRoom(aCurrentRoom)].GetRoomExplored(), aVectorOfRooms[aVectorOfDoors[i]->GetConnectingRoom(aCurrentRoom)].GetRoomName());
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
					playerChoise = static_cast<int>(aVectorOfDoors.size()) - 1;
				}
				break;
			}
			case MenuOptions::MenuListRight:
			{
				if (playerChoise < static_cast<int>(aVectorOfDoors.size()) - 1)
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
		for (int j = 0; j < static_cast<int>(DoorBase::doorSpriteSizeX); j++)
		{
			if (j == 0 || j == static_cast<int>(DoorBase::doorSpriteSizeX) - 1)
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
		ClearArea(aStartX, aStartY + 15, static_cast<int>(DoorBase::doorSpriteSizeX));

	}
}