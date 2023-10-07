#include "Player.h"
#include "Enums.h"
#include "Quick_functions.h"
#include "Item.h"
#include "Equipment.h"
#include "UI.h"
#include <array>
#include <string>

Player::Player()
{
	_equipment;
	_inventory;

	_strength			= _base_strength;
	_dexterety			= _base_dexterety;
	_dodge				= _base_dodge;
	_charisma			= _base_charisma;

	_hp				= (_strength * 6) + (_dexterety * 3);
	_max_hp				= _hp;
	_base_damage		= (_strength * 2) + _dexterety;
	_carrying_capacity	= (_strength * 2) - _dodge;
	_athletics			= _strength + _dexterety;
	_slight_of_hand		= _dodge + _dexterety;
	_persuasion		= _charisma + _dodge;

	_armor = 0;

	_is_alive			= true;
	myCurrentRoom		= 0;
}

void Player::ChangeRoom(int new_room)
{
	myCurrentRoom = new_room;
}

void Player::FindPrimeStatBuff(PrimeStats prime_stat, int stat_buff)
{
	switch (prime_stat)
	{
	case PrimeStats::Strength:
		_strength += stat_buff;
		break;

	case PrimeStats::Dexterety:
		_dexterety += stat_buff;
		break;

	case PrimeStats::Charisma:
		_charisma += stat_buff;
		break;

	case PrimeStats::Armor:
		_armor += stat_buff;
		break;

	default:
		break;
	}
}

void Player::FindSecondaryStatBuff(SecondaryStats secondary_stat, int stat_buff)
{
	switch (secondary_stat)
	{
	case SecondaryStats::Strength:
		_strength += stat_buff;
		break;

	case SecondaryStats::Dexterety:
		_dexterety += stat_buff;
		break;

	case SecondaryStats::Charisma:
		_charisma += stat_buff;
		break;

	case SecondaryStats::MaxHp:
		_hp += stat_buff;
		break;

	case SecondaryStats::Damage:
		_base_damage += stat_buff;
		break;
	
	case SecondaryStats::Athletics:
		_athletics += stat_buff;
		break;

	case SecondaryStats::SlightOfHand:
		_slight_of_hand += stat_buff;
		break;
	
	case SecondaryStats::Persuasion:
		_persuasion += stat_buff;
		break;

	case SecondaryStats::Armor:
		_armor += stat_buff;
		break;
	default:
		break;
	}
}

void Player::UppdateStats()
{
	float tempHp = static_cast<float>(_hp) / static_cast<float>(_max_hp);


	_strength = _base_strength;
	_dexterety = _base_dexterety;
	_dodge = _base_dodge;
	_charisma = _base_charisma;

	_hp				= static_cast<int>(PlayerBase::ResetStats);
	_base_damage		= static_cast<int>(PlayerBase::ResetStats);
	_carrying_capacity	= static_cast<int>(PlayerBase::ResetStats);
	_athletics			= static_cast<int>(PlayerBase::ResetStats);
	_slight_of_hand		= static_cast<int>(PlayerBase::ResetStats);
	_persuasion		= static_cast<int>(PlayerBase::ResetStats);



	if (_equipment.GetEquipmentWeapon() != nullptr)
	{
		FindPrimeStatBuff(_equipment.GetEquipmentWeapon()->GetPrimeStat(), _equipment.GetEquipmentWeapon()->GetPrimeStatBuff());
		FindSecondaryStatBuff(_equipment.GetEquipmentWeapon()->GetSecondaryStat(), _equipment.GetEquipmentWeapon()->GetSecondaryStatBuff());
	}
	if (_equipment.GetEquipmentHelm() != nullptr)
	{
		FindPrimeStatBuff(_equipment.GetEquipmentHelm()->GetPrimeStat(), _equipment.GetEquipmentHelm()->GetPrimeStatBuff());
		FindSecondaryStatBuff(_equipment.GetEquipmentHelm()->GetSecondaryStat(), _equipment.GetEquipmentHelm()->GetSecondaryStatBuff());

	}
	if (_equipment.GetEquipmentArmor() != nullptr)
	{
		FindPrimeStatBuff(_equipment.GetEquipmentArmor()->GetPrimeStat(), _equipment.GetEquipmentArmor()->GetPrimeStatBuff());
		FindSecondaryStatBuff(_equipment.GetEquipmentArmor()->GetSecondaryStat(), _equipment.GetEquipmentArmor()->GetSecondaryStatBuff());

	}

	_hp				+= (_strength * 6) + (_dexterety * 3);
	_base_damage		+= (_strength * 2) + _dexterety;
	_carrying_capacity	+= (_strength * 2) - _dodge;
	_athletics			+= _strength + _dexterety;
	_slight_of_hand		+= _dodge + _dexterety;
	_persuasion		+= _charisma + _dodge;

	_max_hp = _hp;
	tempHp *= static_cast<float>(_hp);
	_hp = static_cast<int>(tempHp);

}

void Player::ShowStats()
{
	UppdateStats();
	int row = 1;
	ui::ClearArea(static_cast<int>(MenuOptions::StatsSeperatorX) + 1,
		static_cast<int>(MenuOptions::ScreenSeperatorY) + 1, 
		static_cast<int>(MenuOptions::FrameSizeEndX) - static_cast<int>(MenuOptions::StatsSeperatorX) - 2,
		static_cast<int>(MenuOptions::FrameSizeEndY) - static_cast<int>(MenuOptions::ScreenSeperatorY) - 2);
	ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	ui::Print("HP: " + std::to_string(_hp) + "/" + std::to_string(_max_hp));
	row += 2;

	ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	ui::Print("STR: \t" + std::to_string(_strength) + "\tCHA: \t" + std::to_string(_charisma));
	row++;
	ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
	ui::Print("DEX: \t" + std::to_string(_dexterety) + "\tDodge: \t" + std::to_string(_dodge));
	row += 2;

	if (_equipment.GetEquipmentWeapon() != nullptr)
	{
		ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		ui::Print("Weapon: \t" + toString(_equipment.GetEquipmentWeapon()->GetItemType()));
	}
	else
	{
		ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		ui::Print("Weapon: \t No Weapon");
	}
	row++;

	if (_equipment.GetEquipmentHelm() != nullptr)
	{
		ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		ui::Print("Helm: \t" + toString(_equipment.GetEquipmentHelm()->GetItemType()));
	}
	else
	{
		ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		ui::Print("Helm: \t No Helm");
	}
	row++;

	if (_equipment.GetEquipmentArmor() != nullptr)
	{
		ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		ui::Print("Armor: \t" + toString(_equipment.GetEquipmentArmor()->GetItemType()));
	}
	else
	{
		ui::SetCursorPosition(static_cast<int>(MenuOptions::StatsSeperatorX) + 1, static_cast<int>(MenuOptions::ScreenSeperatorY) + row);
		ui::Print("Armor: \t No Armor");
	}
}

void Player::PickUpItem(std::shared_ptr<Item> item)
{
	_inventory.push_back(item);
}

int Player::GetAbilityInt(PlayerBase ability)
{
	switch (ability)
	{
		case PlayerBase::AthleticsPlayerSkill:
		{
			return _athletics;
			break;
		}
		case PlayerBase::SlightOfHandPlayerSkill:
		{
			return _slight_of_hand;
			break;
		}
		case PlayerBase::PersuasionPlayerSkill:
		{
			return _persuasion;
			break;
		}
	}
	return 0;
}

int Player::GetHP()
{
	return _hp;
}

int Player::GetCurrentRoom()
{
	return myCurrentRoom;
}

int Player::GetNormalAttack()
{
	int damage = DamageAdjustment(_base_damage);
	ui::PrintInMenu("You deal: " + std::to_string(damage) + " damage!");
	return damage;
}

void Player::UppdateHp(int change)
{
	_hp -= change;
	_is_alive = (_hp <= 0);
}

bool Player::IsAlive()
{
	return _is_alive;
}

std::string* Player::GetAbilityCheckList()
{
	return _ability_checks;
}

std::vector<std::shared_ptr<Item>> Player::GetInventory()
{
	return _inventory;
}

void Player::EquipItem(int item_choise)
{
	switch (_inventory[item_choise]->GetItemSlot())
		{
		case ItemSlot::Weapon: 
		{
			_equipment.SetEquipentWeapon(_inventory[item_choise]);
			break;
		}
		case ItemSlot::Helm:
		{
			_equipment.SetEquipentHelm(_inventory[item_choise]);
			break;
		}
		case ItemSlot::Armor:
		{
			_equipment.SetEquipentArmor(_inventory[item_choise]);
			break;
		}
		break;
	}
}

void Player::InventoryManagement()
{
	int player_choise_in_menu = 0;
	while (true)
	{
		ShowStats();
		int player_try_pick_up = ui::showItems(GetInventory(), player_choise_in_menu);
		if (player_try_pick_up >= GetInventory().size())
		{
			return;
		}
		else
		{
			EquipItem(player_try_pick_up);
		}
	}
}