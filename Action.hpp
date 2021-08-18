#ifndef __ACTION_HPP__
#define __ACTION_HPP__

#include "Entity.hpp"

class Action {
	protected:
		unsigned int cooldown = 0;
		std::string targettingInfo = ""; // Way to determine how this skill targets in combat
		/*
			singleAttack
			groupAttack
			singleHeal
			groupHeal
			everyone
		*/
		
		std::string description = ""; // Description of the action
		std::string beingUsed = ""; // Describe the action beeing taken


	public:
		Action() {}
		~Action() {}
		virtual int Act(Entity* self, Entity** team, int target) = 0; // target will be passed in team size if an attack is a group attack
		std::string GetTargettingInfo() { return this->targettingInfo; } // Way to determine how this skill targets in combat
		std::string GetDescription() { return description; }
		int GetCooldown() { return this->cooldown; }
		bool IsCooldownReady() { return this->cooldown == 0; } //used to check cooldown
		void UpdateCooldown() { if (this->cooldown > 0) this->cooldown--; } // used after the end of a turn
		void RestoreCooldown() { this->cooldown = 0; } // used after the end of a battle
};

//*******************************************************

class BasicAttack : public Action {
	public:
		BasicAttack() {
			this->cooldown = 0;
			this->targettingInfo = "singleAttack";
			this->description = "A SIMPLE BASIC ATTACK";
		}
		int Act(Entity* self, Entity** team, int target) {
			int damage = self->GetATK();
			team[target]->TakeDamage(damage);
			return damage;
		}
};

//------------------------------------------------------

class ArcaneAttack : public Action {
	public:
		ArcaneAttack() {
			this->cooldown = 0;
			this->targettingInfo = "singleAttack";
			this->description = "A SIMPLE ARCANE ATTACK THAT IS EFFECTIVE AGAINST SPECTRAL ENEMIES";
		}

		int Act(Entity* self, Entity** team, int target) {
			int damage = self->GetATK();

			if (team[target]->GetType() == "spectral") damage *= 2;

			team[target]->TakeDamage(damage);
			return damage;
		}
};


class BerzerkAttack : public Action {
public:
	BerzerkAttack() {
		this->cooldown = 0;
		this->targettingInfo = "singleAttack";
		this->description = "A SAVAGE ATTACK THAT DEALS DOUBLE DAMAGE WHEN BELOW HALF MAX HP";
	}
	int Act(Entity* self, Entity** team, int target) {
		int damage = self->GetATK();

		if (self->IsUnderHalfHP()) damage *= 2;

		team[target]->TakeDamage(damage);
		return damage;
	}
};




#endif
