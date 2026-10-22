#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// LEGACY STARTER CODE: UNENFORCED OWNERSHIP & DOUBLE-FREE BUGS
// ============================================================================

class Item {
 public:
  Item(const std::string& name, int attack, int defense)
      : name_(name), attack_bonus_(attack), defense_bonus_(defense) {
    std::cout << "[+] Item Created: " << name_ << "\n";
  }

  ~Item() {
    std::cout << "[-] Item Destroyed: " << name_ << "\n";
  }

  const std::string& GetName() const { return name_; }
  int GetAttack() const { return attack_bonus_; }
  int GetDefense() const { return defense_bonus_; }

 private:
  std::string name_;
  int attack_bonus_;
  int defense_bonus_;
};

class EquipmentSlots {
 public:
  ~EquipmentSlots() {
    // BUG: Deleting raw pointers here causes a DOUBLE-FREE crash if the 
    // item is also still stored inside (and deleted by) the Backpack!
    delete weapon_;
    delete armor_;
  }

  void EquipWeapon(Item* item) {
    weapon_ = item;
  }

  void EquipArmor(Item* item) {
    armor_ = item;
  }

  Item* GetWeapon() const { return weapon_; }
  Item* GetArmor() const { return armor_; }

 private:
  Item* weapon_ = nullptr;
  Item* armor_ = nullptr;
};

class Backpack {
 public:
  ~Backpack() {
    // Manual cleanup of raw pointers
    for (Item* item : items_) {
      delete item;
    }
  }

  void AddItem(Item* item) {
    items_.push_back(item);
  }

  Item* GetItem(size_t index) {
    if (index < items_.size()) {
      return items_[index];
    }
    return nullptr;
  }

  size_t GetSize() const { return items_.size(); }

 private:
  std::vector<Item*> items_;
};

// HELPER FUNCTION: Calculates total stats for equipped gear
// TODO FOR STUDENTS: Modify this to take non-owning raw pointers (const Item*)
int CalculateTotalPower(Item* weapon, Item* armor) {
  int total = 0;
  if (weapon) total += weapon->GetAttack();
  if (armor) total += armor->GetDefense();
  return total;
}

// ============================================================================
// SIMULATION
// ============================================================================

void RunSimulation() {
  std::cout << "================ START SIMULATION ================\n";

  Backpack backpack;
  EquipmentSlots equipment;

  // Create items on the heap
  Item* sword = new Item("Iron Sword", 15, 0);
  Item* shield = new Item("Wooden Shield", 0, 10);

  backpack.AddItem(sword);
  backpack.AddItem(shield);

  // Equip weapon directly from the backpack
  // BUG: 'sword' address is duplicated into equipment without transferring ownership!
  equipment.EquipWeapon(backpack.GetItem(0));

  std::cout << "\nEquipped Weapon: " << equipment.GetWeapon()->GetName() << "\n";
  std::cout << "Total Gear Power: " 
            << CalculateTotalPower(equipment.GetWeapon(), equipment.GetArmor()) 
            << "\n\n";

  std::cout << "--> Exiting RunSimulation (Destructors running...)...\n";
  // CRASH / DOUBLE FREE OCCURS HERE: 
  // 'backpack' destructor deletes 'sword'.
  // 'equipment' destructor ALSO attempts to delete 'sword'!
}

int main() {
  RunSimulation();
  return 0;
}