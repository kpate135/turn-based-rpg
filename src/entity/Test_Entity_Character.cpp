#include "gtest/gtest.h"


TEST(Entity_Character, GetName) {
	PowerGem *gem = new PowerGem("KNIGHT GEM", 2, -1, 0);
	Armor *armor = new Armor("BRONZE CHESTPLATE", 10, -4, 0);

	Character *Bob = new Character("BOB", "KNIGHT", new BasicAttack(), 10, 2, 7, gem, armor);

	EXPECT_EQ(Bob->GetName(), "BOB");
}

TEST(Entity_Character, GetType) {
        PowerGem *gem = new PowerGem("KNIGHT GEM", 2, -1, 0);
        Armor *armor = new Armor("BRONZE CHESTPLATE", 10, -4, 0);

        Character *Bob = new Character("BOB", "KNIGHT", new BasicAttack(), 10, 2, 7, gem, armor);

        EXPECT_EQ(Bob->GetType(), "KNIGHT");
}


TEST(Entity_Character, GetHP) {
        PowerGem *gem = new PowerGem("KNIGHT GEM", 2, -1, 0);
        Armor *armor = new Armor("BRONZE CHESTPLATE", 10, -4, 0);

        Character *Bob = new Character("BOB", "KNIGHT", new BasicAttack(), 10, 2, 7, gem, armor);

        EXPECT_EQ(Bob->GetHP(), 20);
}

TEST(Entity_Character, IsUnderHalfHP_false) {
        PowerGem *gem = new PowerGem("KNIGHT GEM", 2, -1, 0);
        Armor *armor = new Armor("BRONZE CHESTPLATE", 10, -4, 0);

        Character *Bob = new Character("BOB", "KNIGHT", new BasicAttack(), 10, 2, 7, gem, armor);

        EXPECT_EQ(Bob->IsUnderHalfHP(), false);
}

TEST(Entity_Character, IsUnderHalfHP_true) {
        PowerGem *gem = new PowerGem("KNIGHT GEM", 2, -1, 0);
        Armor *armor = new Armor("BRONZE CHESTPLATE", 10, -4, 0);

        Character *Bob = new Character("BOB", "KNIGHT", new BasicAttack(), 10, 2, 7, gem, armor);
	Bob->TakeDamage(10);

        EXPECT_EQ(Bob->IsUnderHalfHP(), true);
}


TEST(Entity_Character, GetATK) {
        PowerGem *gem = new PowerGem("KNIGHT GEM", 2, -1, 0);
        Armor *armor = new Armor("BRONZE CHESTPLATE", 10, -4, 0);

        Character *Bob = new Character("BOB", "KNIGHT", new BasicAttack(), 10, 2, 7, gem, armor);

        EXPECT_EQ(Bob->GetATK(), 4);
}

TEST(Entity_Character, GetSPD) {
        PowerGem *gem = new PowerGem("KNIGHT GEM", 2, -1, 0);
        Armor *armor = new Armor("BRONZE CHESTPLATE", 10, -4, 0);

        Character *Bob = new Character("BOB", "KNIGHT", new BasicAttack(), 10, 2, 7, gem, armor);

        EXPECT_EQ(Bob->GetSPD(), 2);
}

TEST(Entity_Character, GetPowerGemName) {
        PowerGem *gem = new PowerGem("KNIGHT GEM", 2, -1, 0);
        Armor *armor = new Armor("BRONZE CHESTPLATE", 10, -4, 0);

        Character *Bob = new Character("BOB", "KNIGHT", new BasicAttack(), 10, 2, 7, gem, armor);

        EXPECT_EQ(Bob->powerGem->GetName(), "KNIGHT GEM");
}

TEST(Entity_Character, GetPowerGemATK) {
        PowerGem *gem = new PowerGem("KNIGHT GEM", 2, -1, 0);
        Armor *armor = new Armor("BRONZE CHESTPLATE", 10, -4, 0);

        Character *Bob = new Character("BOB", "KNIGHT", new BasicAttack(), 10, 2, 7, gem, armor);

        EXPECT_EQ(Bob->powerGem->GetATK(), 2);
}

TEST(Entity_Character, GetPowerGemSPD) {
        PowerGem *gem = new PowerGem("KNIGHT GEM", 2, -1, 0);
        Armor *armor = new Armor("BRONZE CHESTPLATE", 10, -4, 0);

        Character *Bob = new Character("BOB", "KNIGHT", new BasicAttack(), 10, 2, 7, gem, armor);

        EXPECT_EQ(Bob->powerGem->GetSPD(), -1);
}

TEST(Entity_Character, GetArmorName) {
        PowerGem *gem = new PowerGem("KNIGHT GEM", 2, -1, 0);
        Armor *armor = new Armor("BRONZE CHESTPLATE", 10, -4, 0);

        Character *Bob = new Character("BOB", "KNIGHT", new BasicAttack(), 10, 2, 7, gem, armor);

        EXPECT_EQ(Bob->armor->GetName(), "BRONZE CHESTPLATE");
}

TEST(Entity_Character, GetArmorHP) {
        PowerGem *gem = new PowerGem("KNIGHT GEM", 2, -1, 0);
        Armor *armor = new Armor("BRONZE CHESTPLATE", 10, -4, 0);

        Character *Bob = new Character("BOB", "KNIGHT", new BasicAttack(), 10, 2, 7, gem, armor);

        EXPECT_EQ(Bob->armor->GetHP(), 10);
}

TEST(Entity_Character, GetArmorSPD) {
        PowerGem *gem = new PowerGem("KNIGHT GEM", 2, -1, 0);
        Armor *armor = new Armor("BRONZE CHESTPLATE", 10, -4, 0);

        Character *Bob = new Character("BOB", "KNIGHT", new BasicAttack(), 10, 2, 7, gem, armor);

        EXPECT_EQ(Bob->armor->GetSPD(), -4);
}

//------------------------------------------------------------------------------------------------

TEST(Entity_Character, Action1) {
        PowerGem *gem = new PowerGem("KNIGHT GEM", 2, -1, 0);
        Armor *armor = new Armor("BRONZE CHESTPLATE", 10, -4, 0);

	Entity **team = new Entity*[2];

        Character *Bob = new Character("BOB", "KNIGHT", new BasicAttack(), 10, 2, 7, gem, armor);
	team[0] = new Character("BOBBETTE", "MAGE", new ArcaneAttack(), 7, 6, 4, new PowerGem("MAGE GEM", 4, 0, 0), new Armor("ROBE", 3, 0, 0));

	Bob->action1->Act(Bob, team, 0);

        EXPECT_EQ(team[0]->GetHP(), 6);
}





