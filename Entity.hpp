#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <string>

class Action;


class Entity {
	protected:
		std::string name = "";
		std::string type = "";

		bool dead = false;
		int baseHP = 0; // Entities starting HP
		int currHP = 0; // Entities working HP

		int baseATK = 0; // Entities starting ATK
		int currATK = 0; // Entities working ATK

		int baseSPD = 0; // Entities starting SPD
		int currSPD = 0; // Entities working SPD

		void UpdateDeath(); // Sets dead flag
		virtual void UpdateOverHeal(); // Sets overheal to baseHP (if currHP > baseHP)

	public:
		Action* action1 = 0;
		Entity() {} //shouldn't be intialized this way
		Entity(std::string nm, std::string typ, Action* act1, int HP, int ATK, int spd) : name(nm), type(typ), action1(act1), baseHP(HP), baseATK(ATK), baseSPD(spd) {} //this will be mainly for testing purposes
		~Entity() { delete action1; }

		std::string GetName() { return this->name; } // Will return the entities name
		std::string GetType() { return this->type; } // Will return the entities type
		int GetHP() { return this->currHP; } // Will return currHP
		virtual bool IsUnderHalfHP() { return (this->currHP <= (this->baseHP/2)); } // Will return a boolean determining if an Entity is under half their max HP
		int GetATK() { return this->currATK; } // Will return currATK
		int GetSPD() { return this->currSPD; } // Will return currSPD
		bool IsDead() { return this->dead; } // returns dead boolean

		void TakeDamage(int dmg);
		void Heal(int healAmount);

};


#endif
