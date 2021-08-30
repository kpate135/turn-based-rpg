#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include "Entity.hpp"
#include "Equipment.hpp"


class Character : public Entity {
	protected:
		int maxHP = 0; // Character's baseHP + armor
		int maxATK = 0;  // Character's baseHP + PowerGem
		int maxSPD = 0; // Character's baseSPD + PowerGem + armor

		void UpdateOverHeal() override;
		void UpdateStats(); // Called after equipment changes to alter totalStat attributes

	public:
		Character();
		Character(std::string nm, std::string typ, Action* act1, int hp, int atk, int spd, PowerGem* pwrGem, Armor* armr);
		~Character() { delete action1; delete powerGem; delete armor; }
		bool IsUnderHalfHP() override { return (this->currHP <= (this->maxHP/2)); }
		void RestoreStats(); // Used after battle to recover from ailments and stat debuffs
		void EquipPowerGem(PowerGem *pwrGem); // Used to equip a new PowerGem, discards old one
		void EquipArmor(Armor *armr); // Used to equip new Armor, discards old one
};


#endif
