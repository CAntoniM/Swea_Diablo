#include "Door.h"
#include "Quick_functions.h"

Door::Door(int room_one, int room_two)
{
	_connecting_room_one = room_one;
	_connecting_room_two = room_two;
	_lock_difficulty_str = 0;
	_lock_difficulty_dex = 0;
	_door_lockt = RandomNumber(0, 1) == 1 ? true : false;
	if (_door_lockt)
	{
		_lock_difficulty_str = RandomNumber(20, 40);
		_lock_difficulty_dex = RandomNumber(20, 30);
	}
}

int Door::GetLockDifficultyStr()
{
	return _lock_difficulty_str;
}

int Door::GetLockDifficultyDex()
{
	return _lock_difficulty_dex;
}

int Door::GetConnectingRoom(int current_room)
{
	if (current_room == _connecting_room_one)
	{
		return _connecting_room_two;
	}
	else if (current_room == _connecting_room_two)
	{
		return _connecting_room_one;
	}
	
	return -1;
}

bool Door::IsInCurrentRoom(int _current_room)
{
	return (_current_room == _connecting_room_one || _current_room == _connecting_room_two);
}

bool Door::IsDoorLocked()
{
	return _door_lockt;
}

void Door::isDoorLocked(bool aDoorLockt)
{
	_door_lockt = aDoorLockt;
}