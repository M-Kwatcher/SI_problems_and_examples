#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// LEGACY STARTER CODE: RAW POINTER MISSILE DATALINK SYSTEM
// ============================================================================

class Aircraft {
 public:
  Aircraft(const std::string& callsign, double distance_km)
      : callsign_(callsign), distance_km_(distance_km) {
    std::cout << "[+] Aircraft Spawned: " << callsign_ << " at " << distance_km_ << " km\n";
  }

  ~Aircraft() {
    std::cout << "[-] Aircraft Destroyed/Offline: " << callsign_ << "\n";
  }

  const std::string& GetCallsign() const { return callsign_; }
  double GetDistance() const { return distance_km_; }
  void SetDistance(double dist) { distance_km_ = dist; }

 private:
  std::string callsign_;
  double distance_km_;
};

class Missile {
 public:
  enum GuidanceState { MIDCOURSE_DATALINK, TERMINAL_PITBULL };

  Missile(const std::string& id, Aircraft* target)
      : id_(id), target_(target), distance_to_target_km_(30.0), state_(MIDCOURSE_DATALINK) {
    std::cout << "[+] Missile " << id_ << " Launched!\n";
  }

  ~Missile() {
    std::cout << "[-] Missile " << id_ << " Detonated/Self-Destructed.\n";
  }

  void Step() {
    distance_to_target_km_ -= 10.0;

    // Transition to terminal active radar guidance ("Pitbull") at close range
    if (distance_to_target_km_ <= 10.0 && state_ == MIDCOURSE_DATALINK) {
      state_ = TERMINAL_PITBULL;
      std::cout << "  [!] " << id_ << " went PITBULL! Onboard radar active.\n";
    }

    // STUDENT BUG NOTE: If 'target_' is deleted elsewhere, this dereference 
    // causes a crash/use-after-free error!
    std::cout << "  Missile " << id_ << " tracking target: " << target_->GetCallsign() 
              << " (Range: " << distance_to_target_km_ << " km)\n";
  }

  GuidanceState GetState() const { return state_; }
  Aircraft* GetTarget() const { return target_; }
  const std::string& GetID() const { return id_; }

 private:
  std::string id_;
  Aircraft* target_; // TODO FOR STUDENTS: Convert to std::weak_ptr<Aircraft>
  double distance_to_target_km_;
  GuidanceState state_;
};

class FighterJet {
 public:
  FighterJet(const std::string& callsign) : callsign_(callsign) {
    for (int i = 0; i < MAX_DATALINKS; ++i) {
      datalink_channels_[i] = nullptr;
    }
  }

  ~FighterJet() {
    // STUDENT BUG NOTE: Unclear ownership model. Deleting raw pointers here
    // risks double-free errors if the main airspace container also deletes them.
  }

  bool LaunchMissile(const std::string& missile_id, Aircraft* target, std::vector<Missile*>& airspace) {
    int open_slot = -1;
    for (int i = 0; i < MAX_DATALINKS; ++i) {
      if (datalink_channels_[i] == nullptr) {
        open_slot = i;
        break;
      }
    }

    if (open_slot == -1) {
      std::cout << "[X] Cannot launch " << missile_id << ": All " << MAX_DATALINKS 
                << " datalink channels full!\n";
      return false;
    }

    Missile* m = new Missile(missile_id, target);
    datalink_channels_[open_slot] = m;
    airspace.push_back(m);
    std::cout << "--> Datalink channel " << open_slot << " assigned to " << missile_id << "\n";
    return true;
  }

  void UpdateDatalinks() {
    // STUDENT BUG NOTE: Datalink channels are never automatically freed when 
    // missiles transition to TERMINAL_PITBULL state or detonate.
    std::cout << "--- " << callsign_ << " Datalink Status ---\n";
    for (int i = 0; i < MAX_DATALINKS; ++i) {
      if (datalink_channels_[i] != nullptr) {
        std::cout << " Channel " << i << ": Guiding " << datalink_channels_[i]->GetID() << "\n";
      } else {
        std::cout << " Channel " << i << ": [EMPTY]\n";
      }
    }
  }

 private:
  static const int MAX_DATALINKS = 2;
  std::string callsign_;
  Missile* datalink_channels_[MAX_DATALINKS]; // TODO FOR STUDENTS: Refactor to std::vector<std::weak_ptr<Missile>>
};

// Pure math helper function using non-owning inspection
double CalculateTargetDistance(const Aircraft* jet, const Missile* missile) {
  if (!jet || !missile) return -1.0;
  return jet->GetDistance();
}

// ============================================================================
// SIMULATION DRIVER & ENTRY POINT
// ============================================================================

void RunSimulation() {
  std::cout << "================ START SIMULATION ================\n";

  std::vector<Missile*> airspace; // TODO FOR STUDENTS: Store std::shared_ptr<Missile>

  // Spawn enemy targets
  Aircraft* bandit1 = new Aircraft("Bandit-1 (Su-35)", 50.0);
  Aircraft* bandit2 = new Aircraft("Bandit-2 (Mig-31)", 60.0);

  FighterJet player("Viper-1");

  // Attempt launches
  player.LaunchMissile("AIM-120_A", bandit1, airspace);
  player.LaunchMissile("AIM-120_B", bandit2, airspace);

  // Exceeds max 2-channel capacity
  player.LaunchMissile("AIM-120_C", bandit1, airspace);

  std::cout << "\n--- TURN 1 ---\n";
  for (Missile* m : airspace) {
    m->Step();
  }

  // Simulate target destroyed externally while missile is in flight
  std::cout << "\n--> Bandit-1 shot down by ground defense! Deleting target object...\n";
  delete bandit1;
  bandit1 = nullptr;

  std::cout << "\n--- TURN 2 (Will crash in starter state) ---\n";
  for (Missile* m : airspace) {
    // DANGEROUS ACCESS: AIM-120_A attempts to access freed memory (*bandit1)
    m->Step(); 
  }

  // Cleanup (unreachable prior to refactoring)
  delete bandit2;
  for (Missile* m : airspace) {
    delete m;
  }

  std::cout << "================ END SIMULATION ================\n";
}

int main() {
  RunSimulation();
  return 0;
}