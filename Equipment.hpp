#ifndef __EQUIPMENT_HPP__
#define __EQUIPMENT_HPP__

#include <string>

class PowerGem {
	private:
		std::string name = "";
		int ATK = 0;
		int SPD = 0;
		int tier = 0;

	public:
		PowerGem() : name("bare hands"), ATK(0), SPD(0) {}
		PowerGem(std::string nm, int atk, int spd, int tr) : name(nm), ATK(atk), SPD(spd), tier(tr) {}
		std::string GetName() { return this->name; }
		int GetATK() {
			if (tier > 0) return this->ATK + 2 + (this->tier * this->tier);
			return this->ATK;
		}
		int GetSPD() { return this->SPD; }
		int GetTier() { return this->tier; }
};

class Armor {
	private:
		std::string name = "";
		int HP = 0;
		int SPD = 0;
		int tier = 0;

	public:
		Armor() : name("naked o.O"), HP(0), SPD(0) {}
		Armor(std::string nm, int hp, int spd, int tr) : name(nm), HP(hp), SPD(spd), tier(tr) {}
		std::string GetName() { return this->name; }
		int GetHP()  {
                        if (tier > 0) return this->HP + 2 + (this->tier * this->tier);
                        return this->HP;
                }
		int GetSPD() { return this->SPD; }
		int GetTier() { return this->tier; }
};

#endif
