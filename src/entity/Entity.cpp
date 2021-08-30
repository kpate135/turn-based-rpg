#include "Entity.hpp"

void Entity::UpdateDeath() {
	this->dead = (this->currHP <= 0);
}

void Entity::UpdateOverHeal() {
	if (this->currHP > this->baseHP) this->currHP = this->baseHP;
}

void Entity::TakeDamage(int dmg) {
	this->currHP -= dmg;
	this->UpdateDeath();
}

void Entity::Heal(int healAmount) {
	this->currHP += healAmount;
	this->UpdateOverHeal();
	this->UpdateDeath();
}
