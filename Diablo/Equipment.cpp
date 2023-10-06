#include "Equipment.h"
#include "Item.h"
#include <memory>

Equipment::Equipment()
{
	_equipment_weapon = nullptr;
	_equipment_helm = nullptr;
	_equipment_armor = nullptr;
}

void Equipment::SetEquipentWeapon(std::shared_ptr<Item> item)
{
	_equipment_weapon = item;
}

void Equipment::SetEquipentHelm(std::shared_ptr<Item> item)
{
	_equipment_helm = item;
}

void Equipment::SetEquipentArmor(std::shared_ptr<Item> item)
{
	_equipment_armor = item;
}

std::shared_ptr<Item> Equipment::GetEquipmentWeapon()
{
	return _equipment_weapon;
}

std::shared_ptr<Item> Equipment::GetEquipmentHelm()
{
	return _equipment_helm;
}

std::shared_ptr<Item> Equipment::GetEquipmentArmor()
{
	return _equipment_armor;
}