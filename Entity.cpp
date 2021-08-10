#include "Entity.h"


void Entity::CheckDeath() {
	if (this->currHP <= 0) dead = true;
}

void Entity::CheckOverHeal() {
	if (this->currHP > this->baseHP) this->currHP = this->baseHP;
}

void Entity::BasicAttack(Entity *target) {
	target->TakeDamage(this->GetATK());
}

void Entity::TakeDamage(int dmg) {
	this->currHP -= dmg;
	this->CheckDeath();
}

void Entity::Heal(int healAmount) {
	this->currATK += healAmount;
	this->CheckOverHeal();
}