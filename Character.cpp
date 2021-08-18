#include "Character.hpp"

Character::Character() {
	this->powerGem = new PowerGem();
	this->armor = new Armor();
	this->UpdateStats();
	this->Heal(999);
}

Character::Character(std::string nm, std::string typ, Action* act1, int hp, int atk, int spd, PowerGem *pwrGem, Armor *armr) {
	this->name = nm;
	this->type = typ;
	this->baseHP = hp;
	this->baseATK = atk;
	this->baseSPD = spd;
	this->action1 = act1;
	this->powerGem = pwrGem;
	this->armor = armr;
	this->UpdateStats();
	this->Heal(999);
}

void Character::UpdateOverHeal() {
	if (this->currHP > this->maxHP) this->currHP = this->maxHP;
}

void Character::UpdateStats() {
	this->maxATK = this->baseATK + this->powerGem->GetATK();
	this->maxHP = this->baseHP + this->armor->GetHP();
	this->maxSPD = this->baseSPD + this->powerGem->GetSPD() + this->armor->GetSPD();
	this->RestoreStats();
}

void Character::RestoreStats() {
	this->currATK = this->maxATK;
	//this->currHP = this->maxHP;
	this->currSPD = this->maxSPD;
}

void Character::EquipPowerGem(PowerGem *pwrGem) {
	delete this->powerGem;
	this->powerGem = pwrGem;
	this->UpdateStats();
}

void Character::EquipArmor(Armor* armr) {
	delete this->armor;
	this->armor = armr;
	this->UpdateStats();
}
