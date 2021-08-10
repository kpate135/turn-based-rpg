#pragma once
#include <string>

class Entity {
	protected:
		std::string name = "";

		bool dead = false;
		int baseHP = 0; // Entities starting HP
		int currHP = 0; // Entities working HP

		int baseATK = 0; // Entities starting ATK
		int currATK = 0; // Entities working ATK

		int baseSPD = 0; // Entities starting SPD
		int currSPD = 0; // Entities working SPD


		void CheckDeath(); // Sets dead flag
		virtual void CheckOverHeal(); // Sets overheal to baseHP (if currHP > baseHP)

	public:
		Entity() {} //shouldn't be intialized this way
		Entity(int HP, int ATK, int spd) : baseHP(HP), baseATK(ATK), baseSPD(spd) {} //this will be mainly for testing purposes

		int GetHP() { return this->currHP; } // Will return currHP
		int GetATK() { return this->currATK; } // Will return currATK
		int GetSPD() { return this->currSPD; } // Will return currSPD

		virtual void BasicAttack(Entity *target);
		void TakeDamage(int dmg);
		void Heal(int healAmount);

};

