#include "Door.h"
#include "Quick functions.h"

Door::Door(int aRoomOne, int aRoomTwo)
{
	connectingRoomOne = aRoomOne;
	connectingRoomTwo = aRoomTwo;
	lockDifficultyStr = 0;
	lockDifficultyDex = 0;
	doorLockt = RandomNumber(0, 1) == 1 ? true : false;
	if (doorLockt == true)
	{
		lockDifficultyStr = RandomNumber(20, 40);
		lockDifficultyDex = RandomNumber(20, 30);
	}
}

int Door::GetLockDifficultyStr()
{
	return lockDifficultyStr;
}

int Door::GetLockDifficultyDex()
{
	return lockDifficultyDex;
}

int Door::GetConnectingRoom(int aCurrentRoom)
{
	if (aCurrentRoom == connectingRoomOne)
	{
		return connectingRoomTwo;
	}
	else if (aCurrentRoom == connectingRoomTwo)
	{
		return connectingRoomOne;
	}
	
	return -1;
}


bool Door::GetIsInCurrentRoom(int aCurrentRoom)
{
	if (aCurrentRoom == connectingRoomOne)
	{
		return true;
	}
	else if (aCurrentRoom == connectingRoomTwo)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Door::GetDoorLockt()
{
	return doorLockt;
}
void Door::SetDoorLockt(bool aDoorLockt)
{
	doorLockt = aDoorLockt;
}