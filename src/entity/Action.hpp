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
		~Action() {}
		virtual int Act(Entity* self, Entity** team, int target) = 0; // target will be passed in team size if an attack is a group attack
		std::string GetTargettingInfo() { return this->targettingInfo; } // Way to determine how this skill targets in combat
		std::string GetDescription() { return description; }
		std::string BeingUsed() { return beingUsed; }
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
			this->beingUsed = "IS ATTACKING";
		}
		int Act(Entity* self, Entity** team, int target) {
			int damage = self->GetATK();
			team[target]->TakeDamage(damage);
			return damage;
		}
};


class ArcaneAttack : public Action {
	public:
		ArcaneAttack() {
			this->cooldown = 0;
			this->targettingInfo = "singleAttack";
			this->description = "A SIMPLE ARCANE ATTACK THAT IS EFFECTIVE AGAINST SPECTRAL ENEMIES";
			this->beingUsed = "IS CASTING A SPELL AT";
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
		this->beingUsed = "IS SAVAGELY ATTACKING";
	}
	int Act(Entity* self, Entity** team, int target) {
		int damage = self->GetATK();

		if (self->IsUnderHalfHP()) damage *= 2;

		team[target]->TakeDamage(damage);
		return damage;
	}
};


class FireAttack : public Action {
public:
	FireAttack() {
		this->cooldown = 0;
		this->targettingInfo = "groupAttack";
		this->description = "A WALL OF FIRE THAT BURNS ALL FOES";
		this->beingUsed = "IS BURNING";
	}
	int Act(Entity* self, Entity** team, int target) {
		int damage = (self->GetATK() / 2);
		team[target]->TakeDamage(damage);
		return damage;
	}
};

class BasicHeal : public Action {
public:
	BasicHeal() {
		this->cooldown = 0;
		this->targettingInfo = "singleHeal";
		this->description = "A SIMPLE HEAL";
		this->beingUsed = "IS HEALING";
	}
	int Act(Entity* self, Entity** team, int target) {
		int heal = self->GetATK();
		team[target]->Heal(heal);
		return heal;
	}
};

class CovidAttack : public Action {
public:
	CovidAttack() {
		this->cooldown = 0;
		this->targettingInfo = "singleAttack";
		this->description = "EWWW";
		this->beingUsed = "IS COUGHING ON";
	}
	int Act(Entity* self, Entity** team, int target) {
		int damage = self->GetATK();

		if (team[target]->GetType() == "human") damage *= 2;

		team[target]->TakeDamage(damage);
		return damage;
	}
};

class HackAttack : public Action {
public:
	HackAttack() {
		this->cooldown = 0;
		this->targettingInfo = "groupAttack";
		this->description = "THIS IS BROKEN";
		this->beingUsed = "WHAT";
	}
	int Act(Entity* self, Entity** team, int target) {
		int damage = 99;
		team[target]->TakeDamage(damage);
		return damage;
	}
};

class GroupHeal : public Action {
public:
	GroupHeal() {
		this->cooldown = 0;
		this->targettingInfo = "groupHeal";
		this->description = "HEAL THE TEAM";
		this->beingUsed = "IS HEALING";
	}
	int Act(Entity* self, Entity** team, int target) {
		int heal = (self->GetATK() / 2);
		team[target]->Heal(heal);
		return heal;
	}
};


#endif
