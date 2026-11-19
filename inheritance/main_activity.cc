#include <iostream>
#include <string>

class PlayerCharacter {
 public:
  void Attack(int damage) {
    std::cout << "Base: Attack(int)\n";
  }

  void Attack(std::string weapon) {
    std::cout << "Base: Attack(string)\n";
  }
};

class Wizard : public PlayerCharacter {
 public:
  void Attack(double mana_cost) {
    std::cout << "Derived: Attack(double)\n";
  }
};

int main() {
  Wizard wiz;
  PlayerCharacter& base_ref = wiz;
  PlayerCharacter* base_ptr = &wiz;

  // Trace each call below:
  wiz.Attack(15.5);                       // Call 1
  wiz.Attack(10);                         // Call 2
  wiz.Attack("Staff");                    // Call 3
  base_ref.Attack(10);                    // Call 4
  base_ref.Attack("Staff");               // Call 5
  base_ptr->Attack(15.5);                 // Call 6
  wiz.PlayerCharacter::Attack("Staff");   // Call 7

  return 0;
}