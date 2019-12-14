#pragma once
#include "Item.h"
#include "Armor.h"
#include "Weapon.h"
#include "Inventory.h"

using namespace std;

class Character
{
public:
    Character();
    Character(const Character& character) = delete;
    Character& operator = (const Character& character) = delete;

    const Collection<const Item>& getInventory();

    void addItem(const Item& item);
    void dropItem(const Item& item);
    double getTotalWeight() const;

    const Armor* getEquippedArmor(unsigned int slotID) const;
    unsigned int getTotalArmorRating() const;
    void equipArmor(const Armor& armor);
    void unequipArmor(unsigned int slotID);

    const Weapon* getEquippedWeapon() const;
    void equipWeapon(const Weapon& weapon);
    void unequipWeapon();

    void optimizeInventory(double maximumWeight);
    void optimizeEquipment();

private:
	Inventory playerInventory; // instance of inventory to have the actual list
	const Armor * equippedArmor[6]; // an array to keep track of the equipped armor in each slot. array index corresponds to armor slot id
	const Weapon * equippedWeapon; // pointer to keep track of equipped weapon
    
};