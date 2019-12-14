#include "Weapon.h"

Weapon::Weapon(const Weapon & w) // copy constructor
{
	damage = w.damage;
	setName(w.getName());
	setWeight(w.getWeight());
	setGoldValue(w.getGoldValue());
}

int Weapon::getDamage() const
{
    return damage;
}

void Weapon::setDamage(int damage)
{
    this->damage = damage;
}
