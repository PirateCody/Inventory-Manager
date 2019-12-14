#pragma once
#include "Item.h"

class Weapon : public Item
{
public:
	Weapon() = default;
	Weapon(const Weapon &w);
    int getDamage() const;
    void setDamage(int damage);
private:
    int damage { 0 };
};