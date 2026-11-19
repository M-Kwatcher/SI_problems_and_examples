#include <vector>
#include <iostream>

int RecursiveSum(const std::vector<int>& numbers, size_t index) {
  if (index >= numbers.size()) {
    return 0;
  }

  return numbers[index] + RecursiveSum(numbers, index + 1);
}

int main() {
  std::vector<int> scores = {88, 92, 79, 95, 84};

  int total = RecursiveSum(scores);

  std::cout << "Total score: " << total << std::endl;
  return 0;
}

