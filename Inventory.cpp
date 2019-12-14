#include "Inventory.h"

using namespace std;


unsigned int Inventory::getSize() const
{
	return static_cast<unsigned int>(inventory.size());
}

void Inventory::forEach(const std::function<void(const Item&)>& accept) const
{
	for (auto item : inventory) {
		accept(*item);
	}

}

void Inventory::forEach(const std::function<void(const Item&)>& accept)
{
	for (auto item : inventory) {
		accept(*item);
	}

}


const Item * Inventory::findItem(const Item* item)
{
	for (list<const Item*>::iterator i = inventory.begin(); i != inventory.end(); i++) {
		if ((*i) == item) {
			return item;
		}
	}
	return nullptr;
}

void Inventory::sortValueToWeightRatio()
{
	inventory.sort([](const Item * item1, const Item * item2) {

		double ratio1 = item1->getGoldValue() / item1->getWeight();
		double ratio2 = item2->getGoldValue() / item2->getWeight();
		return ratio1 > ratio2;

	});
}





