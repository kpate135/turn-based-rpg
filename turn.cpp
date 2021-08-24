#include <iostream>
#include "Character.hpp"
#include "Action.hpp"
#include <fstream>
#include <queue>
#include <random>
#include <time.h>
#include "Factory.hpp"

using namespace std;

string currentScene = "";

queue<Entity*> turnQueue;
bool inBattle = false;
bool battleOver = false;
bool turnTaken = false;
bool confirm = false;
int MAX_TEAM_CAPACITY = 4;
int playerTeam_size = 0;
int enemyTeam_size = 0;
Entity** playerTeam = new Entity*[MAX_TEAM_CAPACITY];
Entity** enemyTeam = new Entity * [MAX_TEAM_CAPACITY];
Entity* currEntity = nullptr;
Entity* targetEntity = nullptr;

int globalDamage = 0;
int battleChoice = 4;

void OrderQueue() {
    for (int i = 0; i < playerTeam_size; i++) {
        if (!playerTeam[i]->IsDead()) turnQueue.push(playerTeam[i]);
    }
    for (int i = 0; i < enemyTeam_size; i++) {
        if (!enemyTeam[i]->IsDead()) turnQueue.push(enemyTeam[i]);
    }
}


void OrderQueue_() {
    Entity** full = new Entity*[playerTeam_size + enemyTeam_size];
    for (int i = 0; i < playerTeam_size; i++) {
        full[i] = playerTeam[i];
    }
    for (int i = playerTeam_size; i < enemyTeam_size + playerTeam_size; i++) {
        full[i] = enemyTeam[i - playerTeam_size];
    }

    for (int i = 0; i < enemyTeam_size + playerTeam_size; ++i) {
        for (int j = 0; j < enemyTeam_size + playerTeam_size - 1; ++j) {
            if (full[j]->GetSPD() < full[j + 1]->GetSPD()) {
                Entity* temp = full[j];
                full[j] = full[j + 1];
                full[j + 1] = temp;
                temp = nullptr;
            }
        }
    }

    for (int i = 0; i < enemyTeam_size + playerTeam_size; i++) {
        if (!full[i]->IsDead()) turnQueue.push(full[i]);
    }

    for (int i = 0; i < enemyTeam_size + playerTeam_size; i++) {
        full[i] = nullptr;
    }
}




bool playerDefeated() {
    if (playerTeam_size < 1) return true;

    for (int i = 0; i < playerTeam_size; i++)    {
        if (!playerTeam[i]->IsDead()) return false;
    }

    return true;
}

bool enemyDefeated() {
    if (enemyTeam_size < 1) return true;

    for (int i = 0; i < enemyTeam_size; i++) {
        if (!enemyTeam[i]->IsDead()) return false;
    }

    return true;
}


void CheckTeamHP() {
    for (int i = 0; i < playerTeam_size; i++) {
        if (!playerTeam[i]->IsDead()) cout << playerTeam[i]->GetName() + " HAS " << playerTeam[i]->GetHP() << " HP LEFT" << endl;
        else cout << playerTeam[i]->GetName() + " IS DEAD" << endl;
    }
}

void CheckEnemyHP() {
    for (int i = 0; i < enemyTeam_size; i++) {
        if (!enemyTeam[i]->IsDead()) cout << enemyTeam[i]->GetName() + " HAS " << enemyTeam[i]->GetHP() << " HP LEFT" << endl;
        else cout << enemyTeam[i]->GetName() + " IS DEAD" << endl;
    }
}


bool PlayerTurn() {
    
    cout << currEntity->GetName() << endl << "MAKE A BATTLE CHOICE\n"; cin >> battleChoice; confirm = true; // testing purpsoes
    if (battleChoice == 0) return true; // Do nothing option
    if (battleChoice == 7) CheckTeamHP(); 
    if (battleChoice == 8) CheckEnemyHP();
    if (currEntity->action1->GetTargettingInfo() == "singleAttack") {
        if ((battleChoice <= enemyTeam_size) && confirm) {
            if (enemyTeam[battleChoice - 1]->IsDead()) return false;
            cout << currEntity->GetName() + " " + currEntity->action1->BeingUsed() + " " + enemyTeam[battleChoice - 1]->GetName() << endl;
            globalDamage = currEntity->action1->Act(currEntity, enemyTeam, battleChoice - 1);
            cout << "Which dealt " << globalDamage << " points of damage" << endl;
            targetEntity = enemyTeam[battleChoice - 1];
            return true;
        }
    }
    else if (currEntity->action1->GetTargettingInfo() == "groupAttack") {
        if ((battleChoice <= enemyTeam_size) && confirm) {
            for (int i = 0; i < enemyTeam_size; ++i) {
                cout << currEntity->GetName() + " " + currEntity->action1->BeingUsed() + " " + enemyTeam[i]->GetName() << endl;
                globalDamage = currEntity->action1->Act(currEntity, enemyTeam, i);
                cout << "Which dealt " << globalDamage << " points of damage" << endl;
            }
            return true;
        }
    }
    else if (currEntity->action1->GetTargettingInfo() == "singleHeal") {
        if ((battleChoice <= playerTeam_size) && confirm) {
            if (playerTeam[battleChoice - 1]->IsDead()) return false;
            cout << currEntity->GetName() + " " + currEntity->action1->BeingUsed() + " " + playerTeam[battleChoice - 1]->GetName() << endl;
            globalDamage = currEntity->action1->Act(currEntity, playerTeam, battleChoice - 1);
            cout << "Which recovered " << globalDamage << " points of damage" << endl;
            targetEntity = playerTeam[battleChoice - 1];
            return true;
        }
    }
    else if (currEntity->action1->GetTargettingInfo() == "groupHeal") {
        if ((battleChoice <= playerTeam_size) && confirm) {
            for (int i = 0; i < playerTeam_size; ++i) {
                cout << currEntity->GetName() + " " + currEntity->action1->BeingUsed() + " " + playerTeam[i]->GetName() << endl;
                globalDamage = currEntity->action1->Act(currEntity, playerTeam, i);
                cout << "Which recovered " << globalDamage << " points of damage" << endl;
            }
            return true;
        }
    }
    return false;
}


void EnemyTurn() {

    int target = rand() % playerTeam_size;
    bool someoneIsAlive = false;

    for (int i = 0; i < playerTeam_size; i++) {
        if (!playerTeam[i]->IsDead()) someoneIsAlive = true;
    }
    if (!someoneIsAlive) return;

    while (playerTeam[target]->IsDead()) target = rand() % playerTeam_size;

    if (currEntity->action1->GetTargettingInfo() == "singleAttack") {
        if ((target <= playerTeam_size) && confirm) {
            cout << currEntity->GetName() + " " + currEntity->action1->BeingUsed() + " " + playerTeam[target]->GetName() << endl;
            globalDamage = currEntity->action1->Act(currEntity, playerTeam, target);
            cout << "Which dealt " << globalDamage << " points of damage" << endl;
            targetEntity = playerTeam[target];
            return;
        }
    }
    else if (currEntity->action1->GetTargettingInfo() == "groupAttack") {
        if ((battleChoice <= playerTeam_size) && confirm) {
            for (int i = 0; i < playerTeam_size; ++i) {
                cout << currEntity->GetName() + " " + currEntity->action1->BeingUsed() + " " + playerTeam[i]->GetName() << endl;
                globalDamage = currEntity->action1->Act(currEntity, playerTeam, i);
                cout << "Which dealt " << globalDamage << " points of damage" << endl;
            }
            return;
        }
    }
}

bool TakeTurn() {
    bool isPlayer = false;
    for (int i = 0; i < playerTeam_size; i++) {
        if (currEntity == playerTeam[i]) isPlayer = true;
    }
    if (currEntity->IsDead()) return true;

    cout << endl;

    if (!isPlayer) {
        EnemyTurn();
        cout << currEntity->GetName() + " completed their turn" << endl;
        return true;
    }
    return PlayerTurn();
}

enum states_Battle { SM_NotInBattle, SM_QueueTurn, SM_TakeTurn, SM_CheckBattleStatus, SM_BattleFinished } currState;
void turn_SM() {

    
    switch (currState) {
        case SM_NotInBattle:
            if (inBattle) currState = SM_QueueTurn;
            break;

        case SM_QueueTurn:
            if (!turnQueue.empty()) {
                currEntity = turnQueue.front();
                turnQueue.pop();
                turnTaken = false;
                currState = SM_TakeTurn;
            }
            else currState = SM_NotInBattle;
            break;

        case SM_TakeTurn:
            if (turnTaken) currState = SM_CheckBattleStatus;
            break;

        case SM_CheckBattleStatus:
            if (battleOver) currState = SM_BattleFinished;
            else {
                if (!turnQueue.empty()) {
                    currEntity = turnQueue.front();
                    turnQueue.pop();
                    turnTaken = false;
                    currState = SM_TakeTurn;
                }
                else currState = SM_QueueTurn;
            }
            break;

        case SM_BattleFinished:
            currState = SM_NotInBattle;
            break;
    }


    
    switch (currState) {
        case SM_NotInBattle:
            break;
        case SM_QueueTurn:
            OrderQueue_();
            break;
        case SM_TakeTurn:
            turnTaken = TakeTurn();
            break;
        case SM_CheckBattleStatus:
            turnTaken = false;
            battleOver = (playerDefeated() || enemyDefeated());
            break;
        case SM_BattleFinished:
            cout << "Battle Finished" << endl;
            while (!turnQueue.empty()) turnQueue.pop();
            currEntity = nullptr;
            inBattle = false;
            if (playerDefeated()) currentScene = "GameOver";
            else currentScene = "Victory";
            break;
    }
}



int main() {
    CharacterFactory characterFactory;
    EntityFactory entityFactory;
    PowerGemFactory powerGemFactory;
    ArmorFactory armorFactory;

    srand(time(0));

    currState = SM_NotInBattle;
    inBattle = true;

    playerTeam_size = 4;
    playerTeam[0] = characterFactory.MakeByID(1);
    playerTeam[1] = characterFactory.MakeByID(4);
    playerTeam[2] = characterFactory.MakeByID(2);
    playerTeam[3] = characterFactory.MakeByID(7);

    for (int i = 0; i < playerTeam_size; i++) {
        playerTeam[i]->EquipPowerGem(powerGemFactory.MakeByArea("Covid Tower"));
        playerTeam[i]->EquipArmor(armorFactory.MakeByArea("Covid Tower"));
    }

    for (int i = 0; i < playerTeam_size; i++) {
        cout << playerTeam[i]->powerGem->GetName() + " +" << playerTeam[i]->powerGem->GetTier() << endl;
        cout << playerTeam[i]->armor->GetName() + " +" << playerTeam[i]->armor->GetTier() << endl;
    }



    enemyTeam_size = 4;
    for (int i = 0; i < enemyTeam_size; i++) {
        enemyTeam[i] = entityFactory.MakeByArea("Covid Tower");
    }



    while (1) {
        turn_SM();
    }
    return 0;
}





