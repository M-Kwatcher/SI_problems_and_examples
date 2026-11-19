#include <iostream>
#include <string>

class PlayerCharacter {
 public:
  PlayerCharacter(std::string name, int health)
      : name_(name), health_(health) {}

  void Move() {
    std::cout << name_ << " moves forward.\n";
  }

 private:
  std::string name_;
  int health_;
};

class Wizard : PlayerCharacter {
 public:
  Wizard(std::string name, int health, int mana)
      : name_(name), health_(health), mana_(mana) {}

  void CastSpell() {
    mana_ -= 10;
    std::cout << name_ << " casts fireball! Mana: " << mana_ << "\n";
  }

 private:
  int mana_;
}

int main() {
  Wizard merlin("Merlin", 100, 50);

  merlin.Move();
  merlin.CastSpell();

  return 0;
}