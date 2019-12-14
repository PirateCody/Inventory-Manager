#pragma once
#include "Collection.h"
#include "Item.h"
#include <list>
using namespace std;
class Inventory : public Collection<const Item>
{
public:

	virtual unsigned int getSize() const;

	virtual void forEach(const std::function<void(const Item&)>& accept) const override;

	virtual void forEach(const std::function<void(const Item&)>& accept);

	// function to find an item in the inventory; not for dropping
	const Item* findItem(const Item* item);

	void sortValueToWeightRatio();
	

private:
	list<const Item*> inventory; // data structure to serve as the list of items in the inventory
	
	friend class Character;
};

