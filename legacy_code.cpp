#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// LEGACY CODEBASE: MANUAL MEMORY MANAGEMENT
// ============================================================================

class File {
 public:
  File(const std::string& name, int size_kb)
      : name_(name), size_kb_(size_kb) {
    std::cout << "[+] File Created: " << name_ << " (" << size_kb_ << " KB)\n";
  }

  ~File() {
    std::cout << "[-] File Destroyed: " << name_ << "\n";
  }

  void Read() const {
    std::cout << "Reading file: " << name_ << " [" << size_kb_ << " KB]\n";
  }

  const std::string& GetName() const { return name_; }

 private:
  std::string name_;
  int size_kb_;
};

class Shortcut {
 public:
  // BUG: Shortcut stores a raw pointer to a shared File.
  // If the owner Directory deletes 'target_file', this pointer becomes dangling!
  Shortcut(const std::string& shortcut_name, File* target_file)
      : shortcut_name_(shortcut_name), target_file_(target_file) {}

  ~Shortcut() {
    std::cout << "[-] Shortcut Removed: " << shortcut_name_ << "\n";
    // NOTE: We cannot call 'delete target_file_' here because Directory also 
    // deletes it, which would cause a DOUBLE FREE crash!
  }

  void Open() const {
    std::cout << "Opening Shortcut '" << shortcut_name_ << "' -> ";
    if (target_file_) {
      target_file_->Read(); // UNDEFINED BEHAVIOR if target_file_ was already deleted!
    } else {
      std::cout << "ERROR: Null target.\n";
    }
  }

 private:
  std::string shortcut_name_;
  File* target_file_; 
};

class Directory {
 public:
  Directory(const std::string& name) : name_(name) {
    std::cout << "[+] Directory Created: " << name_ << "\n";
  }

  ~Directory() {
    std::cout << "[-] Directory Destroyed: " << name_ << "\n";
    // Manual deletion loop
    for (File* f : files_) {
      delete f;
    }
    for (Shortcut* s : shortcuts_) {
      delete s;
    }
  }

  void AddFile(File* f) {
    files_.push_back(f);
  }

  void AddShortcut(Shortcut* s) {
    shortcuts_.push_back(s);
  }

  void ListContents() const {
    std::cout << "\n--- Directory Listing: " << name_ << " ---\n";
    for (File* f : files_) {
      f->Read();
    }
    for (Shortcut* s : shortcuts_) {
      s->Open();
    }
    std::cout << "------------------------------------\n\n";
  }

 private:
  std::string name_;
  std::vector<File*> files_;
  std::vector<Shortcut*> shortcuts_;
};

// ============================================================================
// SIMULATION & BUG DEMONSTRATION
// ============================================================================

void RunSimulation() {
  std::cout << "================ START SIMULATION ================\n";

  // Create Root directory
  Directory* root = new Directory("Root");

  // Heap allocate files
  File* report = new File("AnnualReport.pdf", 1024);
  File* image = new File("ProfilePic.png", 512);

  root->AddFile(report);
  root->AddFile(image);

  // Create Desktop directory with a shortcut pointing to AnnualReport.pdf
  Directory* desktop = new Directory("Desktop");
  Shortcut* desktop_shortcut = new Shortcut("Report_Link.lnk", report);
  desktop->AddShortcut(desktop_shortcut);

  root->ListContents();
  desktop->ListContents();

  // SCENARIO: User deletes 'Root' directory while Desktop is still active
  std::cout << "--> Deleting 'Root' Directory...\n";
  delete root; // Destroys AnnualReport.pdf and ProfilePic.png!

  std::cout << "\n--> Accessing Desktop shortcut after Root deletion:\n";
  // CRASH / USE-AFTER-FREE: Shortcut attempts to read destroyed AnnualReport.pdf!
  desktop->ListContents();

  delete desktop;

  std::cout << "================ END SIMULATION ================\n";
}

int main() {
  RunSimulation();
  return 0;
}