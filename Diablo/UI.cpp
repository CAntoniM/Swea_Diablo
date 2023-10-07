#include "UI.h"
#include "Quick_functions.h"
#include <Windows.h>
#include <vector>
#include "Enemy.h"
#include "Door.h"
#include "Room.h"
#include "Enums.h"
#include "Item.h"
#include <conio.h>

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_ENTER 13
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_RIGHT 77

namespace ui {

	void Clear()
	{
		system("cls");
	}

	void Pause()
	{
		system("Pause>0");
	}

	void Print(std::string string)
	{
		std::cout << string << std::endl;
	}

	void PrintInMenu(std::string string)
	{
		int row = 0;
		std::string print_out_string_part = string;
		std::string tempString;

		ClearMenu();

		while (print_out_string_part.size() > static_cast<int>(MenuOptions::StatsSeperatorX) - 2)
		{
			if (string.size() > static_cast<int>(MenuOptions::StatsSeperatorX) - 2)
			{
				std::string::size_type split = print_out_string_part.rfind(' ', static_cast<int>(MenuOptions::StatsSeperatorX) - 2);
				SetCursorPosition(static_cast<int>(MenuOptions::menyStartX), static_cast<int>(MenuOptions::menyStartY) + row);
				std::cout << print_out_string_part.substr(0, split) << std::endl;
				print_out_string_part.erase(0, split + 1);
				row++;
			}
		}

		SetCursorPosition(static_cast<int>(MenuOptions::menyStartX), static_cast<int>(MenuOptions::menyStartY) + row);
		std::cout << print_out_string_part << std::endl;
	}

	void ClearArea(int x, int y, int aXLength, int aYLength)
	{
		for (; y < aYLength; y++)
		{
			for (; x < aXLength; x++)
			{
				SetCursorPosition(x, y);
				Print(" ");
			}
		}

	}
	void ClearGameView()
	{
		for (int y = 1; y < static_cast<int>(MenuOptions::ScreenSeperatorY); y++)
		{
			for (int x = 1; x < static_cast<int>(MenuOptions::FrameSizeEndX) - 1; x++)
			{
				SetCursorPosition(x, y);
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
	void ClearMenu()
	{
		for (int y = static_cast<int>(MenuOptions::ScreenSeperatorY) + 1; y < static_cast<int>(MenuOptions::FrameSizeEndY) - 1; y++)
		{
			for (int x = 1; x < static_cast<int>(MenuOptions::StatsSeperatorX) - 1; x++)
			{
				SetCursorPosition(x, y);
				std::cout << " ";
			}
		}
	}

	void SetColor(ColorInt color)
	{
		switch (color)
		{
			case ColorInt::GreenColorText:
				std::cout << "\x1B[32m";
				break;
			case ColorInt::WhiteColorText:
				std::cout << "\x1B[37m";
				break;
			case ColorInt::RedColorText:
				std::cout << "\x1B[31m";
				break;
			case ColorInt::LightGrayColorText:
				std::cout << "\x1B[90m";
				break;
			default:
				std::cout << "\x1B[37m";
				break;
		}
	}

	void SetCursorPosition(int x, int y)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout.flush();
		COORD coord = { (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition(hConsole, coord);
	}


	MenuOptions ButtonPress()
	{
		int button = 0;
		while (true)
		{
			button = _getch();
			if (button == 0 || button == 224)
			{
				switch (_getch())
				{
				case KEY_ARROW_UP:
				{
					return MenuOptions::MenuListUp;
					break;
				}
				case KEY_ARROW_DOWN:
				{
					return MenuOptions::MenuListDown;
					break;
				}
				case KEY_ARROW_LEFT:
				{
					return MenuOptions::MenuListLeft;
					break;
				}
				case KEY_ARROW_RIGHT:
				{
					return MenuOptions::MenuListRight;
					break;
				}
				}
			}
			else
			{
				if (button == KEY_W)
				{
					return MenuOptions::MenuListUp;
				}
				else if (button == KEY_S)
				{
					return MenuOptions::MenuListDown;
				}
				else if (button == KEY_A)
				{
					return MenuOptions::MenuListLeft;
				}
				else if (button == KEY_D)
				{
					return MenuOptions::MenuListRight;
				}
				else if (button == KEY_ENTER)
				{
					return MenuOptions::MenuListOption;
				}
			}
		}
	}

	void SetCursorVisibility(bool is_visible)
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.dwSize = 100;
		cursorInfo.bVisible = is_visible;

		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	}

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
					COORD cursor_position = csbi.dwCursorPosition;
					int x = cursor_position.X + 1;
					int y = cursor_position.Y;
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
					std::cout << toString(items[i]->GetSecondaryStat()) << ": +" << items[i]->GetSecondaryStatBuff() << std::endl;
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
		int offset_x = 3;
		for (int i = 0; i < aList.size(); i++)
		{
			if (aList[i].IsAlive() == true)
			{
				aList[i].PrintSprite(static_cast<int>(MenuOptions::gameStartX) + offset_x, static_cast<int>(MenuOptions::gameStartY) + 2);
				offset_x += aList[i].GetSpriteSizeX() + 10;
			}
			else
			{
				offset_x += aList[i].GetSpriteSizeX() + 10;
			}

		}
	}

	int ChoseEnemy(std::vector<Enemy>& aList)
	{
		bool missing_target = true;
		int player_choise = 0;
		while (true)
		{
			int offset_x = 3;
			ClearArea(static_cast<int>(MenuOptions::gameStartX) + offset_x, static_cast<int>(MenuOptions::gameStartY), static_cast<int>(MenuOptions::FrameSizeEndX) - offset_x);
			for (int i = 0; i < aList.size(); i++)
			{
				if (i == player_choise)
				{
					aList[i].ShowTarget(static_cast<int>(MenuOptions::gameStartX) + offset_x, static_cast<int>(MenuOptions::gameStartY) + 2, true);

				}
				else
				{
					aList[i].ShowTarget(static_cast<int>(MenuOptions::gameStartX) + offset_x, static_cast<int>(MenuOptions::gameStartY) + 2, false);
				}
				offset_x += aList[i].GetSpriteSizeX() + 10;

			}

			switch (ButtonPress())
			{
			case MenuOptions::MenuListLeft:
			{
				if (player_choise > 0)
				{
					player_choise--;
				}
				else
				{
					player_choise = static_cast<int>(aList.size()) - 1;
				}
				break;
			}
			case MenuOptions::MenuListRight:
			{
				if (player_choise < static_cast<int>(aList.size()) - 1)
				{
					player_choise++;
				}
				else
				{
					player_choise = 0;
				}
				break;
			}
			case MenuOptions::MenuListOption:
			{
				if (aList[player_choise].IsAlive() == true)
				{
					return player_choise;
				}
				else
				{
					if (missing_target == true)
					{
						ClearMenu();
						PrintInMenu("There is no monster there, try again!");
						Sleep();
						missing_target = false;
					}

				}
				break;
			}
			}
		}
	}

	int ShowDoors(std::vector<std::shared_ptr<Door>> doors, std::vector<Room>& rooms, int current_room)
	{
		int player_choise = 0;

		while (true)
		{
			int extra_space = 0;
			ClearGameView();

			for (int i = 0; i < doors.size(); i++)
			{
				if (i == player_choise)
				{
					PrintDoorSprite(static_cast<int>(MenuOptions::gameStartX) + static_cast<int>(ExtraInts::OfSet) + (static_cast<int>(DoorBase::doorSpriteSizeX) * i) + extra_space, static_cast<int>(MenuOptions::gameStartY),
						true, rooms[doors[i]->GetConnectingRoom(current_room)].GetRoomExplored(), rooms[doors[i]->GetConnectingRoom(current_room)].GetRoomName());
					extra_space += 3;
				}
				else
				{
					PrintDoorSprite(static_cast<int>(MenuOptions::gameStartX) + static_cast<int>(ExtraInts::OfSet) + (static_cast<int>(DoorBase::doorSpriteSizeX) * i) + extra_space, static_cast<int>(MenuOptions::gameStartY),
						false, rooms[doors[i]->GetConnectingRoom(current_room)].GetRoomExplored(), rooms[doors[i]->GetConnectingRoom(current_room)].GetRoomName());
					extra_space += 3;
				}
			}

			switch (ButtonPress())
			{
			case MenuOptions::MenuListLeft:
			{
				if (player_choise > 0)
				{
					player_choise--;
				}
				else
				{
					player_choise = static_cast<int>(doors.size()) - 1;
				}
				break;
			}
			case MenuOptions::MenuListRight:
			{
				if (player_choise < static_cast<int>(doors.size()) - 1)
				{
					player_choise++;
				}
				else
				{
					player_choise = 0;
				}
				break;
			}
			case MenuOptions::MenuListOption:
			{
				return player_choise;
				break;
			}
			}
		}
	}

	void PrintDoorSprite(int x, int y, bool target, bool room_explored, std::string room_name)
	{
		if (room_explored == false)
		{
			SetCursorPosition(x, y);
			std::cout << "     ______     \n";
			SetCursorPosition(x, ++y);
			std::cout << "  ,-' ;  ! `-.  \n";
			SetCursorPosition(x, ++y);
			std::cout << " / :  !  :  . \\ \n";
			SetCursorPosition(x, ++y);
			std::cout << "|_ ;   __:  ;  |\n";
			SetCursorPosition(x, ++y);
			std::cout << ")| .  :)(.  !  |\n";
			SetCursorPosition(x, ++y);
			std::cout << "|     (##)  _  |\n";
			SetCursorPosition(x, ++y);
			std::cout << "|  :  ;`'  (_) (\n";
			SetCursorPosition(x, ++y);
			std::cout << "|  :  :  .     |\n";
			SetCursorPosition(x, ++y);
			std::cout << ")_ !  ,  ;  ;  |\n";
			SetCursorPosition(x, ++y);
			std::cout << "|| .  .  :  :  |\n";
			SetCursorPosition(x, ++y);
			std::cout << "|  .  |  :  .  |\n";
			SetCursorPosition(x, ++y);
			std::cout << "|___.------.___|\n";
			SetCursorPosition(x, ++y);
			std::cout << "      ???       " << std::endl;
		}
		else if (room_explored == true)
		{
			SetCursorPosition(x, y);
			std::cout << "     ______     \n";
			SetCursorPosition(x, ++y);
			std::cout << "  ,-'      `-.  \n";
			SetCursorPosition(x, ++y);
			std::cout << " /            \\\n";
			SetCursorPosition(x, ++y);
			std::cout << "|              |\n";
			SetCursorPosition(x, ++y);
			std::cout << "|              |\n";
			SetCursorPosition(x, ++y);
			std::cout << "|              |\n";
			SetCursorPosition(x, ++y);
			std::cout << "|              |\n";
			SetCursorPosition(x, ++y);
			std::cout << "|              |\n";
			SetCursorPosition(x, ++y);
			std::cout << "|              |\n";
			SetCursorPosition(x, ++y);
			std::cout << "|              |\n";
			SetCursorPosition(x, ++y);
			std::cout << "|              |\n";
			SetCursorPosition(x, ++y);
			std::cout << "|______________|\n";
			SetCursorPosition(x, ++y);
			std::cout << "   " << room_name << std::endl;
		}

		if (target)
		{
			SetCursorPosition(x, y + 15);
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
			ClearArea(x, y + 15, static_cast<int>(DoorBase::doorSpriteSizeX));

		}
	}

}
