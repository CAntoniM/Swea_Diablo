#pragma once
#include <string>
#include "Enums.h"

class Item
{
	public:
		Item(ItemType aItems);
		ItemType GetItemType();
		PrimeStats GetPrimeStat();
		SecondaryStats GetSecondaryStat();
		int GetPrimeStatBuff();
		int GetSecondaryStatBuff();
		ItemSlot GetItemSlot();
	
	private:
		int SetLevel();
		void SetStats();
		ItemType _item_type;
		ItemSlot _item_slot;
		PrimeStats _prime_stat; // This variable name is unclear to what are prime stats I am assuming they are something 
		SecondaryStats _secondary_stat;
		int _prime_stat_buff;
		int _secondary_stat_buff;
		int _level;
};

