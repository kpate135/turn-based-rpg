#include "Character.h"

Character::Character() {
	this->powerGem = new PowerGem();
	this->armor = new Armor();
}

void Character::CheckOverHeal() {
	if (this->currHP > this->totalHP) this->currHP = this->totalHP;
}

void Character::UpdateStats() {
	this->currATK = this->baseATK + powerGem->GetATK();
	this->currHP = this->baseHP + armor->GetHP();
}
