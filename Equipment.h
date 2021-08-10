#pragma once
#include <string>

class PowerGem {
	private:
		std::string name = "";
		int ATK = 0;
		int SPD = 0;
		int tier = 0;

	public:
		PowerGem() : name("bare hands"), ATK(0), SPD(5) {}
		PowerGem(std::string nm, int atk, int spd, int tr) : name(nm), ATK(atk), SPD(spd), tier(tr) {}
		int GetATK();
		int GetSPD();
};

class Armor {
	private:
		std::string name = "";
		int HP = 0;
		int SPD = 0;
		int tier = 0;

	public:
		Armor() : name("naked o.O"), HP(0), SPD(10) {}
		Armor(std::string nm, int hp, int spd, int tr) : name(nm), HP(hp), SPD(spd), tier(tr) {}
		int GetHP();
		int GetSPD();
};

