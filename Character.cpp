#include "Character.h"

Character::Character()
{
	for (int i = 0; i <6; i++) {
		equippedArmor[i] = nullptr;
	}
	equippedWeapon = nullptr;
}

const Collection<const Item>& Character::getInventory()
{
	return playerInventory;
}

void Character::addItem(const Item & item)
{
	//determine what type of item we need to add
	//if the item being added is an armor, then copy it from the blueprint as an armor
	//if the item being added is a weapon, then copy it from the blueprint as a weapon
	//if the item is not an armor or a weapon (so a generic item), then copy it as a generic item
	//finally, sort the inventory by Value to Weight ratio
	if (const Armor* a = dynamic_cast<const Armor*>(&item)) {
		Armor* toAdd = new Armor(*a);
		playerInventory.inventory.push_front(toAdd);
	}
	else if (const Weapon* w = dynamic_cast<const Weapon*>(&item)) {
		Weapon* toAdd = new Weapon(*w);
		playerInventory.inventory.push_front(toAdd);
	}
	else {
		Item* toAdd = new Item(item);
		playerInventory.inventory.push_front(toAdd);
	}
	
	playerInventory.sortValueToWeightRatio();

}

void Character::dropItem(const Item & item)
{
	//start off with the item being not found
	bool found = false;

	//iterate through the inventory
	for (list<const Item*>::iterator i = playerInventory.inventory.begin(); i != playerInventory.inventory.end(); i++) {
		//if we find the item, remove it and set found to true
		if ((*i) == &item) {
			playerInventory.inventory.erase(i);
			found = true;
			break;
		}
	}
	// if we dont find it, throw an error
	if (!found) {
		throw logic_error("Item not found");
	}
	
}

double Character::getTotalWeight() const
{
	//iterate through the inventory, adding each item's weight to the total
	double totalWeight = 0.0;
	for (auto i : playerInventory.inventory) {
		totalWeight += i->getWeight();
	}

	//add the weight of the equipped weapon
	if (equippedWeapon != nullptr) {
		totalWeight += equippedWeapon->getWeight();
	}

	//add the weight of the equipped armors
	for (int i = 0; i < 6; i++) {
		if (equippedArmor[i] != nullptr) {
			totalWeight += equippedArmor[i]->getWeight();
		}
	}

	return totalWeight;
}

const Armor * Character::getEquippedArmor(unsigned int slotID) const
{
	if (slotID > 5)
		throw out_of_range("SlotID too big");

	return equippedArmor[slotID];
}

unsigned int Character::getTotalArmorRating() const
{
	//iterate through the equipped armor slots, totalling the armor ratings
	unsigned int totalRating = 0;
	for (int i = 0; i < 6; i++) {
		if (equippedArmor[i] != nullptr) {
			totalRating += equippedArmor[i]->getRating();
		}
	}
	return totalRating;
}

void Character::equipArmor(const Armor & armor)
{
	//find the requested armor
	const Item* toEquip = playerInventory.findItem(&armor);

	//if the requested armor is in the inventory, equip it to the proper slot, then drop it from the inventory
	if (toEquip) {
		equippedArmor[armor.getSlotID()] = dynamic_cast<const Armor*>(toEquip);
	}
	dropItem(armor);
}

void Character::unequipArmor(unsigned int slotID)
{

	if (slotID > 5) {
		throw out_of_range("Invalid Slot ID");
	}

	//if there is something equipped in the requested slot, add it to the inventory and set the slot to null
	if (equippedArmor[slotID] != nullptr) {
		//const Item& toAdd = dynamic_cast<const Item&>(equippedArmor[slotID]);
		addItem(*(dynamic_cast<const Item*>(equippedArmor[slotID])));
		equippedArmor[slotID] = nullptr;

	}
}

const Weapon * Character::getEquippedWeapon() const
{
	return equippedWeapon;
}

void Character::equipWeapon(const Weapon & weapon)
{
	//find the weapon that we are equipping
	const Item* toEquip = playerInventory.findItem(&weapon);

	// if the weapon was found, equip it, then remove it from the inventory
	if (toEquip) {

		// if there's something already equipped, unequip it
		if (equippedWeapon != nullptr) {
			unequipWeapon();
		}

		equippedWeapon = dynamic_cast<const Weapon*>(toEquip);
	}
	dropItem(weapon);
}

void Character::unequipWeapon()
{
	//if there is something equipped, add that item to the inventory and set the equipped slot to null
	if (equippedWeapon != nullptr) {
		addItem(*(dynamic_cast<const Item*>(equippedWeapon)));
		equippedWeapon = nullptr;
	}
}

void Character::optimizeInventory(double maximumWeight)
{
	if (maximumWeight < 0) {
		throw out_of_range("Invalid max weight");
	}
	
	//iterate through the inventory starting from the bottomm
	//in each iteration, check to see if the total weight is bigger than the max weight, if it is, drop the bottom item
	//otherwise, stop iterating through the inventory
	for (list<const Item*>::reverse_iterator i = playerInventory.inventory.rbegin(); i != playerInventory.inventory.rend(); ) {
		if (getTotalWeight() > maximumWeight) {
			dropItem(*(*i));
		}
		else {
			break;
		}
	}
	
}

void Character::optimizeEquipment()
{
	list<const Item*>::iterator i = playerInventory.inventory.begin();
	//iterate through the inventory
	while (i != playerInventory.inventory.end()) {
		//determine if the item being checked is Armor or Weapon
		//if it is an armor or weapon, compare its rating to whatever is currently equipped
		if (const Armor* a = dynamic_cast<const Armor*>((*i))) {
			if (equippedArmor[a->getSlotID()] == nullptr) {
				equippedArmor[a->getSlotID()] = a;
				++i;
				dropItem(*a);
			}
			else if (equippedArmor[a->getSlotID()]->getRating() < a->getRating()) {
				addItem(*equippedArmor[a->getSlotID()]);
				equippedArmor[a->getSlotID()] = a;
				++i;
				dropItem(*a);
			}
			else {
				++i;
			}
		}
		else if (const Weapon* w = dynamic_cast<const Weapon*>(*i)) {
			if (equippedWeapon == nullptr) {
				equippedWeapon = w;
				++i;
				dropItem(*w);
			}
			else if (equippedWeapon->getDamage() < w->getDamage()) {
				addItem(*equippedWeapon);
				equippedWeapon = w;
				++i;
				dropItem((*w));
				
			}
			else {
				++i;
			}
		}
		else {
			++i;
		}

	}
}


