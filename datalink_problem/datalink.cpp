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

    // Check if close enough to switch onboard active radar on ("Pitbull")
    if (distance_to_target_km_ <= 10.0 && state_ == MIDCOURSE_DATALINK) {
      state_ = TERMINAL_PITBULL;
      std::cout << "  [!] " << id_ << " went PITBULL! Onboard radar active.\n";
    }

    // BUG: If target was deleted in main/airspace, dereferencing 'target_' causes 
    // UNDEFINED BEHAVIOR / USE-AFTER-FREE CRASH!
    std::cout << "  Missile " << id_ << " tracking target: " << target_->GetCallsign() 
              << " (Range: " << distance_to_target_km_ << " km)\n";
  }

  GuidanceState GetState() const { return state_; }
  Aircraft* GetTarget() const { return target_; }
  const std::string& GetID() const { return id_; }

 private:
  std::string id_;
  Aircraft* target_; // BUG: Raw pointer does not know if target object is still alive!
  double distance_to_target