#include "Armor.h"
#include <stdexcept>

using namespace std;

Armor::Armor(const Armor & a) // copy contructor
{
	slotID = a.slotID;
	rating = a.rating;
	setName(a.getName());
	setWeight(a.getWeight());
	setGoldValue(a.getGoldValue());
}

unsigned int Armor::getSlotID() const
{
    return slotID;
}

int Armor::getRating() const
{
    return rating;
}

void Armor::setSlotID(unsigned int slotID)
{
    if (slotID >= Armor::SLOT_COUNT)
    {
        throw out_of_range("Invalid slot ID: " + to_string(slotID));
    }
    else
    {
        this->slotID = slotID;
    }
}

void Armor::setRating(int rating)
{
    this->rating = rating;
}
