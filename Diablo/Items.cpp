#include "Item.h"
#include "Quick_functions.h"
#include "Enums.h"
#include <string>
#include <vector>

Item::Item(ItemType items)
{
	_item_type = items;
	_level = SetLevel();
	SetStats();
}

int Item::SetLevel()
{
	int level = RandomNumber(1, 100);
	return level >= static_cast<int>(ItemBase::ProcentalChansLvlThree) ? 3 : level >= static_cast<int>(ItemBase::procentalChansLvlTwo) ? 2 : 1;
}
void Item::SetStats()
{
	std::vector<PrimeStats> randomPrimeStat;
	std::vector<SecondaryStats> randomSecondaryStats;
	int buff_divider = RandomNumber(1, 5);
	switch (_item_type)
	{
	case ItemType::Dagger:

		randomPrimeStat =
		{
			PrimeStats::Dexterety,
			PrimeStats::Charisma,
		};

		randomSecondaryStats = 
		{
			SecondaryStats::Strength,
			SecondaryStats::Charisma,
			SecondaryStats::Damage,
			SecondaryStats::Persuasion,
			SecondaryStats::SlightOfHand
		};

		_item_slot = ItemSlot::Weapon;
		_prime_stat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
		_secondary_stat = randomSecondaryStats[RandomNumber(0, static_cast<int>(randomSecondaryStats.size()) - 1)];
		_prime_stat_buff = RandomNumber(buff_divider, (buff_divider + 2)) * _level;
		_secondary_stat_buff = RandomNumber(1, buff_divider) * _level;
		break;
	case ItemType::Sword:

		randomPrimeStat =
		{
			PrimeStats::Dexterety,
			PrimeStats::Strength,
		};

		randomSecondaryStats =
		{
			SecondaryStats::Strength,
			SecondaryStats::Dexterety,
			SecondaryStats::Damage,
			SecondaryStats::Persuasion,
			SecondaryStats::MaxHp
		};

		_item_slot = ItemSlot::Weapon;
		_prime_stat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
		_secondary_stat = randomSecondaryStats[RandomNumber(0, static_cast<int>(randomSecondaryStats.size()) - 1)];
		_prime_stat_buff = RandomNumber(buff_divider, (buff_divider + 2)) * _level;
		_secondary_stat_buff = RandomNumber(1, buff_divider) * _level;
		break;
	case ItemType::GreatSword: 

		randomPrimeStat =
		{
			PrimeStats::Armor,
			PrimeStats::Strength,
		};
		
		randomSecondaryStats =
		{
			SecondaryStats::Strength,
			SecondaryStats::Armor,
			SecondaryStats::Damage,
			SecondaryStats::Persuasion,
			SecondaryStats::MaxHp,
			SecondaryStats::Athletics,
		};

		_item_slot = ItemSlot::Weapon;
		_prime_stat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
		_secondary_stat = randomSecondaryStats[RandomNumber(0, static_cast<int>(randomSecondaryStats.size()) - 1)];
		_prime_stat_buff = RandomNumber(buff_divider, (buff_divider + 2)) * _level;
		_secondary_stat_buff = RandomNumber(1, buff_divider) * _level;
		break;
	case ItemType::Helm:

		randomPrimeStat =
		{
			PrimeStats::Charisma,
			PrimeStats::Dexterety,
			PrimeStats::Armor,
		};

		randomSecondaryStats =
		{
			SecondaryStats::Charisma,
			SecondaryStats::Armor,
			SecondaryStats::MaxHp,
			SecondaryStats::Persuasion,
		};

		_item_slot = ItemSlot::Helm;
		_prime_stat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
		_secondary_stat = randomSecondaryStats[RandomNumber(0, static_cast<int>(randomSecondaryStats.size()) - 1)];
		_prime_stat_buff = RandomNumber(buff_divider, (buff_divider + 2)) * _level;
		_secondary_stat_buff = RandomNumber(1, buff_divider) * _level;
		break;
	case ItemType::Armor:

		randomPrimeStat =
		{
			PrimeStats::Strength,
			PrimeStats::Armor,
		};

		randomSecondaryStats =
		{
			SecondaryStats::Strength,
			SecondaryStats::Armor,
			SecondaryStats::Damage,
			SecondaryStats::Persuasion,
			SecondaryStats::MaxHp,
			SecondaryStats::Athletics,
		};

		_item_slot = ItemSlot::Armor;
		_prime_stat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
		_secondary_stat = randomSecondaryStats[RandomNumber(0, static_cast<int>(randomSecondaryStats.size()) - 1)];
		_prime_stat_buff = RandomNumber(buff_divider, (buff_divider + 2)) * _level;
		_secondary_stat_buff = RandomNumber(1, buff_divider) * _level;
		break;
	default:
		break;
	}
}

PrimeStats Item::GetPrimeStat()
{
	return _prime_stat;
}

SecondaryStats Item::GetSecondaryStat()
{
	return _secondary_stat;
}

int Item::GetPrimeStatBuff()
{
	return _prime_stat_buff;
}

int Item::GetSecondaryStatBuff() 
{
	return _secondary_stat_buff;
}

ItemType Item::GetItemType()
{
	return _item_type;
}

ItemSlot Item::GetItemSlot()
{
	return _item_slot;
}