// ERROR 1: Missing return type in function header
RecursiveSum(const std::vector<int>& numbers, size_t index) {
  if (index >= numbers.size()) {
    return 0 // ERROR 2: Missing semicolon at end of statement
  }

  return numbers[index] + RecursiveSum(numbers, index + 1);
}

int main() {
  std::vector<int> scores = {88, 92, 79, 95, 84};

  // ERROR 3: Function call argument count mismatch (missing required 'index' argument)
  int total = RecursiveSum(scores);

  std::cout << "Total score: " << total << std::endl;
  return 0;
}


