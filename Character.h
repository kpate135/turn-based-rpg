#pragma once
#include "Entity.h"
#include "Equipment.h"

class Character : public Entity {
	protected:
		int totalHP = 0; // Character's baseHP + armor
		int totalATK = 0;  // Character's baseHP + PowerGem
		int totalSPD = 0; // Character's baseSPD + PowerGem + armor

		PowerGem* powerGem = nullptr;
		Armor* armor = nullptr;

		void CheckOverHeal() override;

	public:
		Character();
		void UpdateStats();
};

