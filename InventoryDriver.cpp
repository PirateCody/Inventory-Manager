#include <iostream>
#include <string>
#include <iomanip>
#include "Character.h"
#include "Item.h"

using namespace std;

void commandQuit(bool* isActive) {
	*isActive = false;
	cout << "\n\nQuitting\n\n" << endl;
}

void optimizeInventory(Character* char1, ostream& out, istream& in) {
	double maxWeight;
	out << "Enter maximum weight: ";
	in >> maxWeight;
	in.ignore();
	
	char1->optimizeInventory(maxWeight);
	cout << "Inventory Optimized" << endl;
}

void optimizeEquipment(Character* char1, ostream& out) {
	char1->optimizeEquipment();
	out << "Equipment Optimized" << endl;
}

void addWeaponItem(Character* char1, ostream& out, istream& in) {

	Weapon item;
	string name;
	unsigned int value;
	double weight;
	int rating;

	out << "Enter the weapon name: ";
	getline(in, name);

	out << "Enter the weapon gold value: ";
	in >> value;

	out << "Enter the weapon weight value: ";
	in >> weight;

	out << "Enter the weapon damage rating: ";
	in >> rating;

	item.setName(name);
	item.setGoldValue(value);
	item.setWeight(weight);
	item.setDamage(rating);

	char1->addItem(item);

	out << endl << item.getName() << " added!" << endl;
	in.ignore();

}

void addArmorItem(Character* char1, ostream& out, istream& in) {

	Armor item;
	string name;
	unsigned int value;
	double weight;
	int rating;
	int slot;

	out << "Enter the armor Name: ";
	getline(in, name);

	out << "Enter the armor gold value: ";
	in >> value;

	out << "Enter the armor weight value: ";
	in >> weight;

	out << "Enter the armor rating: ";
	in >> rating;

	out << "Enter the armor slot: ";
	in >> slot;

	item.setName(name);
	item.setGoldValue(value);
	item.setWeight(weight);
	item.setRating(rating);
	item.setSlotID(slot);

	char1->addItem(item);

	out << endl << item.getName() << " added!" << endl;
	in.ignore();

}

void addItem(Character* char1, ostream& out, istream& in) {

	Item item;
	string name;
	unsigned int value;
	double weight;

	out << "Enter the Item Name: ";
	getline(in, name);

	out << "Enter the Item gold value: ";
	in >> value;

	out << "Enter the Item weight value: ";
	in >> weight;

	item.setName(name);
	item.setGoldValue(value);
	item.setWeight(weight);

	char1->addItem(item);

	out << endl << item.getName() << " added!" << endl;
	in.ignore();

}

void printInventory(Character* char1, ostream& out) {

	Item* item;

	out << "+++++++++++++++++|Inventory|+++++++++++++++++" << endl;
	out << "Items:" << endl;

	char1->getInventory().forEach([&item, &out](const Item& current)
	{
		out << current.getName() << "\t" <<current.getGoldValue() << "GP\t" << current.getWeight() << "lbs. " << endl;
	});
	cout << endl;

	out << "Equipped Armor: " << endl;
	for (int i = 0; i < Armor::SLOT_COUNT; i++) {
		if (char1->getEquippedArmor(i) != nullptr) {
			out << char1->getEquippedArmor(i)->getName() << "\t" << char1->getEquippedArmor(i)->getGoldValue() << "GP\t" << char1->getEquippedArmor(i)->getWeight() << "lbs.\t" << char1->getEquippedArmor(i)->getRating() << "AR" << endl;
		}
	}

	out << "Total Armor Rating: " << char1->getTotalArmorRating() << endl << endl;

	out << "Equipped Weapon: " << endl;
	if (char1->getEquippedWeapon() != nullptr) {
		out << char1->getEquippedWeapon()->getName() << "\t" << char1->getEquippedWeapon()->getGoldValue() << "GP\t" << char1->getEquippedWeapon()->getWeight() << "lbs.\t" << char1->getEquippedWeapon()->getDamage() << "DMG" << endl;
	}
	else {
		out << "None!" << endl;
	}

	out << endl << "Total Weight: " << char1->getTotalWeight() << endl;
	out << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void processInput(unsigned int input, bool* isActive, Character* char1, ostream* out, istream* in) {
	switch (input) {
	case 0: commandQuit(isActive); break;
	case 1: printInventory(char1, *out); break;
	case 2: addItem(char1, *out, *in); break;
	case 3: addArmorItem(char1, *out, *in); break;
	case 4: addWeaponItem(char1, *out, *in); break;
	case 5: optimizeEquipment(char1, *out); break;
	case 6: optimizeInventory(char1, *out, *in); break;
	default: *out << "Invalid command!" << endl;
	}
}

void header(ostream& out) {
	out << "++++++++++++++++++++++++++++++++++++" << endl;
	out << "Choose an option: " << endl;;
	out << "0: Quit\n1: Print Inventory\n2: Add an Item\n3: Add an Armor item\n4. Add a Weapon item\n5. Optimize Equipment\n6. Optimize Inventory";
	out << endl << "++++++++++++++++++++++++++++++++++++" << endl;
}


int main() {
	Item item;
	item.setName("Wood");
	Character char1;
	char1.addItem(item);

	bool active = true;
	bool* isActive = &active;

	bool active2 = *isActive;

	int input = -1;

	while (*isActive) {
		header(cout);
		cin >> input;
		cin.ignore();
		processInput(input, isActive, &char1, &cout, &cin);

	}

	system("pause");

	
	return 0;
}