#pragma once
#include <memory>

#include "Item.h"

class Equipment
{
public:
	Equipment();
	void SetEquipentWeapon(std::shared_ptr<Item>);
	void SetEquipentHelm(std::shared_ptr<Item>);
	void SetEquipentArmor(std::shared_ptr<Item>);

	std::shared_ptr<Item> GetEquipmentWeapon();
	std::shared_ptr<Item> GetEquipmentHelm();
	std::shared_ptr<Item> GetEquipmentArmor();


private:
	std::shared_ptr<Item> _equipment_armor;
	std::shared_ptr<Item> _equipment_weapon;
	std::shared_ptr<Item> _equipment_helm;

};

