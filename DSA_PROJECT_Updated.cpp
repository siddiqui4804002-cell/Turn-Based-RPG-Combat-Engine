#include <iostream>
#include <string>

using namespace std;

class Action {
public:
    string actorName; 
    string actionType;
    int amount;
    
    Action() {
        actorName = "";
        actionType = "";
        amount = 0;
    }
    
    Action(string name, string type, int val) {
        actorName = name;
        actionType = type;
        amount = val;
    }
};
class Character {
public:
    string name;
    string heroClass; 
    int hp;
    int maxHp;
    int attackPower;
    int defense;
    int mana;
    int maxMana;
    int arrows;
    bool isHero;

    Character() {
        name = "";
        heroClass = "Generic";
        hp = 0;
        maxHp = 0;
        attackPower = 0;
        defense = 0;
        mana = 0;
        maxMana = 0;
        arrows = 0;
        isHero = false;
    }

    Character(string n, string cls, int health, int atk, int def, int m, int arr, bool hero) {
        name = n;
        heroClass = cls;
        hp = health;
        maxHp = health;
        attackPower = atk;
        defense = def;
        mana = m;
        maxMana = m;
        arrows = arr;
        isHero = hero;
    }

    bool isAlive() { // character or enemy will remain alive if hp is greater than 0
        return hp > 0;
    }
void takeDamage(int dmg) {
        int actualDmg = dmg - defense;
        if (actualDmg < 1) actualDmg = 1; 
        hp -= actualDmg;
//Even if defense is greater than incoming damage, the attack will still cause 1 damage.
        if (hp < 0) hp = 0;
        
        cout <<"                          "<< name << " takes " << actualDmg << " damage! (HP: " << hp << "/" << maxHp << ")\n";
    }
                                                                                        
};
class ItemNode {
public:
    string itemName;
    string itemType; // "HEAL", "MANA", "ARROWS"
    int itemValue;
    ItemNode* next;

    ItemNode(string name, string type, int val) {
        itemName = name;
        itemType = type;
        itemValue = val;
        next = NULL;
    }
};

class InventoryLinkedList {
private:
    ItemNode* head;
    int count;

public:
    InventoryLinkedList() {
        head = NULL;
        count = 0;
    }

    ~InventoryLinkedList() { // to prevent memory leak travese the list and deltes it 
        while (head != NULL) { 
            ItemNode* temp = head; // else traverse to end and appends it
            head = head->next;
            delete temp;
        }
    }

    void addItem(string name, string type, int val) { // creates new itemnode 
        ItemNode* newNode = new ItemNode(name, type, val); //create new 
        if (head == NULL) { // becomes first node
            head = newNode;
        } else {
            ItemNode* temp = head;
            while (temp->next != NULL) { // else traverse to end and appends it
                temp = temp->next;
            }
            temp->next = newNode;
        }
        count++;
    }

    void displayInventory() { //iterates through the list using a temporary pointer temp and prints each item with a 1 based index
        if (head == NULL) {
            cout << "Inventory is empty!\n";
            return;
        }
        ItemNode* temp = head;
        int idx = 1;
        while (temp != NULL) {
            cout << idx << ". " << temp->itemName;
            if (temp->itemType == "HEAL") cout << " (Heals " << temp->itemValue << " HP)\n";
            else if (temp->itemType == "MANA") cout << " (Restores " << temp->itemValue << " Mana)\n";
            else if (temp->itemType == "ARROWS") cout << " (Adds " << temp->itemValue << " Arrows)\n";
            temp = temp->next;
            idx++;
        }
    }

    bool useItem(int index, string& outItemName, string& outType, int& outVal) { 
        if (head == NULL || index < 1 || index > count) { // pass by reference
            return false; 
        }

        ItemNode* temp = head;
        if (index == 1) {
            head = head->next; //moves head to head next and deletes old head
            outItemName = temp->itemName;
            outType = temp->itemType;
            outVal = temp->itemValue;
            delete temp;
            count--;
            return true;
        }

        ItemNode* prev = NULL;
        for (int i = 1; i < index; i++) {
            prev = temp; //traverse to the target node and deletes temp
            temp = temp->next;
        }

        prev->next = temp->next;
        outItemName = temp->itemName;
        outType = temp->itemType;
        outVal = temp->itemValue;
        delete temp;
        count--;
        return true;
    }

    int getCount() {
        return count;
    }
};
class StackNode {
public:
    Action data;
    StackNode* next;

    StackNode(Action act) {
        data = act;
        next = NULL;
    }
};

class ActionStack {
private:
    StackNode* top; //points to most recently pushed item

public:
    ActionStack() {
        top = NULL;
    }

    ~ActionStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() {
        return top == NULL;
    }

    void push(Action act) {
        StackNode* newNode = new StackNode(act); //alocates new stacknode
        newNode->next = top; //points next to top
        top = newNode; //updates top to new node
    }

    Action pop() { //copies top data and moves top to top nezxt 
        if (isEmpty()) {
            return Action();
        }
        StackNode* temp = top;
        Action poppedAction = temp->data;
        top = top->next;
        delete temp; // frees memory 
        return poppedAction; //o(1)
    }
};
class QueueNode {
public:
    Character* fighter;//HOLDS POINTER TO A CHARACTER SO MODIFICATIONS of hp mama affects the actual character
    QueueNode* next;

    QueueNode(Character* c) {
        fighter = c;
        next = NULL;
    }
};

class TurnQueue {
private:
    QueueNode* front; //tracks both end for insertion and deletion
    QueueNode* rear;

public:
    TurnQueue() {
        front = NULL;
        rear = NULL;
    }

    ~TurnQueue() {
        clear();
    }

    void clear() { // clears leftover fighters between waves
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() {
        return front == NULL;
    }

    void enqueue(Character* c) { //adds fighter to rear
        QueueNode* newNode = new QueueNode(c);
        if (rear == NULL) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    Character* dequeue() { //removes the character at front
        if (isEmpty()) {
            return NULL;
        }
        QueueNode* temp = front;
        Character* c = temp->fighter;
        front = front->next;
        if (front == NULL) {
            rear = NULL; //resets it to avoid a dangling pointer
        }
        delete temp;
        return c;
    }
};
class RpgBattleEngine {
private:
    Character hero;
    Character boss;
    TurnQueue turnOrder;
    ActionStack history;
    InventoryLinkedList inventory;
    int wavesCleared;

public:
    RpgBattleEngine() {
        wavesCleared = 0;
    }

    void setupHero() { //menu
        string name;
        cout << "Enter Hero Name: ";
        cin >> name;

        cout << "\nChoose Class:\n";
        cout << "1. Warrior (High HP, Armor Bash)\n";
        cout << "2. Mage (Fireball, Uses Mana)\n";
        cout << "3. Archer (Double Shot, Uses Arrows)\n";
        cout << "Choice: ";
        int choice;
        cin >> choice;

        if (choice == 2) {
            hero = Character(name, "Mage", 85, 20, 2, 50, 0, true);
            inventory.addItem("Small Potion", "HEAL", 25);
            inventory.addItem("Mana Potion", "MANA", 30);
        } else if (choice == 3) {
            hero = Character(name, "Archer", 95, 18, 3, 0, 10, true);
            inventory.addItem("Small Potion", "HEAL", 25);
            inventory.addItem("Arrow Quiver", "ARROWS", 5);
        } else {
            hero = Character(name, "Warrior", 120, 22, 6, 0, 0, true);
            inventory.addItem("Small Potion", "HEAL", 30);
            inventory.addItem("Greater Potion", "HEAL", 50);
        }
    }

    void displayStatus() {
        cout << "\n----------------------------------------\n";
        cout << hero.name << " [" << hero.heroClass << "] HP: " << hero.hp << "/" << hero.maxHp;
        if (hero.heroClass == "Mage") cout << " | Mana: " << hero.mana << "/" << hero.maxMana;
        if (hero.heroClass == "Archer") cout << " | Arrows: " << hero.arrows;
        cout << "\n" << boss.name << " HP: " << boss.hp << "/" << boss.maxHp << "\n";
        cout << "----------------------------------------\n";
    }

    void executeTurn() { //deques the active fighter if dead exit early
        Character* current = turnOrder.dequeue();

        if (!current->isAlive()) {
            return;
        }

        cout << "\n                                          It is " << current->name << "'s turn!                                         \n";

        if (current->isHero) { 
            bool validChoice = false;
            while (!validChoice) {
                cout << "1. Attack\n";
                cout << "2. Special Ability\n";
                cout << "3. Open Inventory \n";
                cout << "4. Undo Last Action\n";
                cout << "Choose Action: ";
                
                int choice;
                cin >> choice;

                if (choice == 1) { // Attack
                    cout << "                                          " << hero.name << " attacks!\n";
                    boss.takeDamage(hero.attackPower);
                    
                    Action act(hero.name, "ATTACK", hero.attackPower);
                    history.push(act);
                    validChoice = true;
                }
                else if (choice == 2) { // Special Ability
                    if (hero.heroClass == "Warrior") {
                        int bashDmg = 15 + boss.defense;
                        cout << "                                          " << hero.name << " uses SHIELD BASH (Ignores Armor)!\n";
                        boss.takeDamage(bashDmg);
                        
                        Action act(hero.name, "ATTACK", bashDmg);
                        history.push(act);
                        validChoice = true;
                    }
                    else if (hero.heroClass == "Mage") {
                        if (hero.mana >= 15) {
                            hero.mana -= 15;
                            int spellDmg = hero.attackPower + 10;
                            cout << "                                           " << hero.name << " casts FIREBALL!\n";
                            boss.takeDamage(spellDmg);
                            
                            Action act(hero.name, "ATTACK", spellDmg);
                            history.push(act);
                            validChoice = true;
                        } else {
                            cout << "                                           Not enough Mana! Meditating to restore 20 Mana \n";
                            hero.mana += 20;
                            if (hero.mana > hero.maxMana) hero.mana = hero.maxMana;
                            validChoice = true;
                        }
                    }
                    else if (hero.heroClass == "Archer") {
                        if (hero.arrows >= 2) {
                            hero.arrows -= 2;
                            int shotDmg = (hero.attackPower + 4) * 2;
                            cout << "                                           " << hero.name << " fires DOUBLE SHOT!\n";
                            boss.takeDamage(shotDmg);
                            
                            Action act(hero.name, "ATTACK", shotDmg);
                            history.push(act);
                            validChoice = true;
                        } else {
                            cout << "                                           Out of arrows! Switched to Dagger strike.\n";
                            boss.takeDamage(8);
                            validChoice = true;
                        }
                    }
                }
                else if (choice == 3) { // Open Inventory
                    if (inventory.getCount() == 0) {
                        cout << "No items left in Inventory!\n";
                        continue;
                    }
                    inventory.displayInventory();
                    cout << "Select item number to use: ";
                    int itemIdx;
                    cin >> itemIdx;

                    string usedName, type;
                    int itemVal;
                    if (inventory.useItem(itemIdx, usedName, type, itemVal)) {
                        if (type == "HEAL") {
                            hero.hp += itemVal;
                            if (hero.hp > hero.maxHp) hero.hp = hero.maxHp;
                            cout << ">> Used " << usedName << "! Healed " << itemVal << " HP.\n";
                            Action act(hero.name, "POTION", itemVal);
                            history.push(act);
                        } else if (type == "MANA") {
                            hero.mana += itemVal;
                            if (hero.mana > hero.maxMana) hero.mana = hero.maxMana;
                            cout << ">> Used " << usedName << "! Restored " << itemVal << " Mana.\n";
                            Action act(hero.name, "MANA", itemVal);
                            history.push(act);
                        } else if (type == "ARROWS") {
                            hero.arrows += itemVal;
                            cout << ">> Used " << usedName << "! Added " << itemVal << " Arrows.\n";
                            Action act(hero.name, "ARROWS", itemVal);
                            history.push(act);
                        }
                        validChoice = true;
                    } else {
                        cout << "Invalid item selection!\n";
                    }
                }
                else if (choice == 4) { // Undo using stack 
                    if (history.isEmpty()) {
                        cout << "No actions to undo!\n";
                    } else {
                        Action lastAct = history.pop();
                        if (lastAct.actionType == "ATTACK") {
                            boss.hp += lastAct.amount;
                            cout << ">> UNDO: Restored " << lastAct.amount << " HP back to " << boss.name << "!\n";
                        } else if (lastAct.actionType == "POTION") {
                            hero.hp -= lastAct.amount;
                            cout << ">> UNDO: Removed " << lastAct.amount << " HP from " << hero.name << "!\n";
                        } else if (lastAct.actionType == "MANA") {
                            hero.mana -= lastAct.amount;
                            cout << ">> UNDO: Removed " << lastAct.amount << " Mana from " << hero.name << "!\n";
                        } else if (lastAct.actionType == "ARROWS") {
                            hero.arrows -= lastAct.amount;
                            cout << ">> UNDO: Removed " << lastAct.amount << " Arrows from " << hero.name << "!\n";
                        }
                    }
                } else {
                    cout << "Invalid input!\n";
                }
            }
        } 
        else {
            // Enemy Turn 
            cout << "                                          " << boss.name << " attacks " << hero.name << "!\n";
            hero.takeDamage(boss.attackPower);
        }

        // Re-queue active fighters
        if (current->isAlive()) { //if is alive puts the fighter back at the end of queue
            turnOrder.enqueue(current);
        }
    }

    void startWaveSession() {
        setupHero();

        // Sequential Enemy Waves
        Character waveEnemies[3];
        waveEnemies[0] = Character("Goblin Scout", "Enemy", 45, 12, 1, 0, 0, false);
        waveEnemies[1] = Character("Orc Warrior", "Enemy", 80, 18, 4, 0, 0, false);
        waveEnemies[2] = Character("Ancient Dragon Boss", "Enemy", 130, 24, 7, 0, 0, false);
//creates static array
        for (int i = 0; i < 3; i++) {
            boss = waveEnemies[i];

            // Clear leftover hero pointer from previous wave
            turnOrder.clear();

            // Re-populate Queue for current battle
            turnOrder.enqueue(&hero);
            turnOrder.enqueue(&boss);

 
            cout << "                                              BATTLE WAVE "<< (i + 1) <<"                                                       "<<endl;
			cout<< "\n                                        " << hero.name << " VS " << boss.name << "\n";


            while (hero.isAlive() && boss.isAlive()) {
                displayStatus();
                executeTurn();
            }

            if (hero.isAlive()) {
                cout << "\n*** VICTORY! Defeated " << boss.name << "! ***\n";
                wavesCleared++;
                hero.hp = hero.maxHp; // Fully heal before the next boss
            } else {
                cout << "\n                                           DEFEAT! You were slain by " << boss.name << "\n";
                break;
            }
        }
        cout << "\n========================================\n";
        cout << "                                        FINAL BATTLE SUMMARY                                        \n";
        cout << "========================================\n";
        cout << "                                        Hero Name     : " << hero.name << "\n";
        cout << "                                        Class         : " << hero.heroClass << "\n";
        cout << "                                        Waves Cleared : " << wavesCleared << "/3\n";
        cout << "========================================\n";
    }
};
int main() {
    RpgBattleEngine engine;
    engine.startWaveSession();
    return 0;
}
