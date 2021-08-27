#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include "Character.hpp"
#include "Equipment.hpp"

class AbstractFactory {

	public:
		AbstractFactory() {};
		~AbstractFactory() {};

		virtual Entity* MakeByArea(std::string area) = 0;
		virtual Entity* MakeByID(int id) = 0;

};



// Entities
class EntityFactory : public AbstractFactory {
	public:
	Entity* MakeByArea(std::string area) override {
		if (area == "Forest") {
			return MakeByID(rand()%4 + 1);
		}
		if (area == "Catacombs") {
			return MakeByID(rand() % 4 + 5);
		}
		if (area == "Covid Tower") {
			return MakeByID(rand() % 4 + 9);
		}
		return MakeByID(99);
	}
	Entity* MakeByID(int id) override {
		switch (id) {
			
			case 1:
				return new Entity("SLIME", "slime", new BasicAttack(), 4, 2, 2);
				break;
			case 2:
				return new Entity("SPIDER", "bug", new BasicAttack(), 3, 2, 6);
				break;
			case 3:
				return new Entity("BANDIT", "human", new BerzerkAttack(), 6, 4, 2);
				break;
			case 4:
				return new Entity("BAT", "flying", new BasicAttack(), 2, 2, 10);
				break;
			// Catacomb
			case 5:
				return new Entity("COUGHBIE", "undead", new CovidAttack(), 10, 3, 1);
				break;
			case 6:
				return new Entity("HAUNTED COFFIN", "spectral", new ArcaneAttack(), 5, 5, 1);
				break;
			case 7:
				return new Entity("GRAVE ROBBER", "human", new BasicAttack(), 7, 3, 8);
				break;
			case 8:
				return new Entity("SKELETON", "undead", new BasicAttack(), 4, 2, 10);
				break;

			// End Catacomb
			// COVID tower
			case 9:
				return new Entity("RAT", "rodent", new BasicAttack(), 7, 6, 5);
				break;
			case 10:
				return new Entity("HAUNTED ARMOR", "spectral", new BerzerkAttack(), 15, 8, 2);
				break;
			case 11:
				return new Entity("COVID ILL MAN", "human", new CovidAttack(), 10, 6, 5);
				break;
			case 12:
				return new Entity("HAUNTED HAMMER", "spectral", new BasicAttack(), 5, 6, 10);
				break;

			default:
				return new Entity("ERROR", "error", new BasicAttack(), 99, 99, 99);
				break;

		}
		return new Entity("ERROR", "error", new BasicAttack(), 99, 99, 99);
	}
};



// Characters
class CharacterFactory : public AbstractFactory {
	public:
	Character* MakeByArea(std::string area) override {
		return MakeByID(rand()%7 + 1);
	}
	Character* MakeByID(int id) override {
		switch (id) {
		case 1:
			return new Character("BOB", "KNIGHT", new BasicAttack(), 10, 4, 4, new PowerGem(), new Armor());
			break;
		case 2:
			return new Character("SAM", "CLERIC", new BasicHeal(), 6, 4, 2, new PowerGem(), new Armor());
			break;
		case 3:
			return new Character("SETH", "MAGE", new ArcaneAttack(), 6, 6, 4, new PowerGem(), new Armor());
			break;
		case 4:
			return new Character("PYRA", "PYROMANCER", new FireAttack(), 6, 6, 2, new PowerGem(), new Armor());
			break;
		case 5:
			return new Character("WILL", "RASCAL", new CovidAttack(), 7, 4, 2, new PowerGem(), new Armor());
			break;
		case 6:
			return new Character("RAWR", "KAREN", new BerzerkAttack(), 8, 6, 1, new PowerGem(), new Armor());
			break;
		case 7:
			return new Character("JAZZ", "SINGER", new GroupHeal(), 6, 4, 7, new PowerGem(), new Armor());
			break;
		case 8:
			return new Character("HAX", "HACKER", new HackAttack(), 99, 99, 99, new PowerGem(), new Armor());
			break;

		default:
			return new Character("ERROR", "ERROR", new BasicAttack(), 99, 99, 99, new PowerGem(), new Armor());
			break;

		}
		return new Character("ERROR", "ERROR", new BasicAttack(), 99, 99, 99, new PowerGem(), new Armor());
	}
};




int GenerateTier() {
	int r = (rand() % 100 + 1);

	if (r <= 40) {
		return 0;
	}
	if (r <= 70) {
		return 1;
	}
	if (r <= 90) {
		return 2;
	}
	if (r <= 100) {
		return 3;
	}
	return 0;
}



class PowerGemFactory {
	public:
		PowerGemFactory() {}
		~PowerGemFactory() {}
		PowerGem* MakeByArea(std::string area) {
			if (area == "Forest") {
				return MakeByID(rand() % 4 + 1);
			}
			if (area == "Catacombs") {
				return MakeByID(rand() % 4 + 5);
			}
			if (area == "Covid Tower") {
				return MakeByID(rand() % 4 + 9);
			}
			return MakeByID(99);
		}
		PowerGem* MakeByID(int id) {
			int tr = GenerateTier();

			switch (id) {
				
				case 1:
					return new PowerGem("BASIC GEM", 2, 2, tr);
					break;
				case 2:
					return new PowerGem("BRONZE GEM", 3, 0, tr);
					break;
				case 3:
					return new PowerGem("IRON GEM", 5, -2, tr);
					break;
				case 4:
					return new PowerGem("SILK GEM", 0, 5, tr);
					break;

				
				case 5:
					return new PowerGem("BONE GEM", 2, 8, tr);
					break;
				case 6:
					return new PowerGem("ANCIENT GEM", 10, -4, tr);
					break;
				case 7:
					return new PowerGem("MODERATE GEM", 4, 4, tr);
					break;
				case 8:
					return new PowerGem("BANDAGE GEM", 6, 0, tr);
					break;

				
				case 9:
					return new PowerGem("ENCHANTED GEM", 10, 0, tr);
					break;
				case 10:
					return new PowerGem("COVID GEM", 20, -10, tr);
					break;
				case 11:
					return new PowerGem("SPEED GEM", 5, 10, tr);
					break;
				case 12:
					return new PowerGem("GREAT GEM", 7, 7, tr);
					break;

				default:
					return new PowerGem("ERROR", 99, 99, 0);
			};
			return new PowerGem("ERROR", 99, 99, 0);
		}
};




class ArmorFactory {
	public:
		ArmorFactory() {}
		~ArmorFactory() {}
		Armor* MakeByArea(std::string area) {
			if (area == "Forest") {
				return MakeByID(rand() % 4 + 1);
			}
			if (area == "Catacombs") {
				return MakeByID(rand() % 4 + 5);
			}
			if (area == "Covid Tower") {
				return MakeByID(rand() % 4 + 9);
			}
			return MakeByID(99);
		}
		Armor* MakeByID(int id) {
			int tr = GenerateTier();

			switch (id) {
				
				case 1:
					return new Armor("BASIC ARMOR", 2, 2, tr);
					break;
				case 2:
					return new Armor("BRONZE ARMOR", 4, 0, tr);
					break;
				case 3:
					return new Armor("IRON ARMOR", 6, -2, tr);
					break;
				case 4:
					return new Armor("SILK ROBE", 0, 4, tr);
					break;

				
				case 5:
					return new Armor("RIB CAGE", 2, 8, tr);
					break;
				case 6:
					return new Armor("ANCIENT ARMOR", 10, -4, tr);
					break;
				case 7:
					return new Armor("MODERATE ARMOR", 4, 4, tr);
					break;
				case 8:
					return new Armor("BANDAGE WRAP", 6, 0, tr);
					break;

				
				case 9:
					return new Armor("ENCHANTED ARMOR", 10, 0, tr);
					break;
				case 10:
					return new Armor("HAZMAT SUIT", 20, -10, tr);
					break;
				case 11:
					return new Armor("SPEED ARMOR", 6, 10, tr);
					break;
				case 12:
					return new Armor("GREAT ARMOR", 7, 7, tr);
					break;

				default:
					return new Armor("ERROR", 99, 99, 0);
			};
			return new Armor("ERROR", 99, 99, 0);
		}
};



#endif
