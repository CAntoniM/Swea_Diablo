#pragma once
class Room;

class Door
{
public:
	Door(int aRoomOne, int aRoomTwo);
	int GetConnectingRoom(int aCurrentRoom);
	int GetLockDifficultyStr();
	int GetLockDifficultyDex();
	bool IsCurrentRoom(int aCurrentRoom);
	bool IsDoorLocked();
	void IsDoorLocked(bool aDoorLockt);


private:
	int _connecting_room_one;
	int _connecting_room_two;
	int _lock_difficulty_str;
	int _lock_difficulty_dex;
	bool _door_lockt;
};

