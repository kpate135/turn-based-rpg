#include "Equipment.h"

int PowerGem::GetATK() {
	return this->ATK + (this->tier * this->tier);
}

int PowerGem::GetSPD() {
	return this->SPD;
}

int Armor::GetHP() {
	return this->HP + (this->tier * this->tier);
}

int Armor::GetSPD() {
	return this->SPD;
}
