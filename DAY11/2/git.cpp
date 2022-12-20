// Advent of Code 2022
// Day 11: Monkey in the Middle

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

enum Operator { ADD, MULTIPLY };

struct Operation {
  Operator op;
  int value;
};

struct Monkey {
  std::queue<long long> items;
  Operation operation;

  int divisor;
  size_t target_true;
  size_t target_false;

  int inspections = 0;
};

long long monkey_business(std::vector<Monkey> monkeys,
                          std::function<long long(long long)> modifier,
                          int rounds) {
  for (int round = 0; round < rounds; ++round) {
    for (Monkey &monkey : monkeys) {
      monkey.inspections += monkey.items.size();

      for (; !monkey.items.empty(); monkey.items.pop()) {
        long long item = monkey.items.front();

        int value;
        if (monkey.operation.value == -1) {
          value = item;
        } else {
          value = monkey.operation.value;
        }

        switch (monkey.operation.op) {
        case ADD:
          item += value;
          break;

        case MULTIPLY:
          item *= value;
          break;
        }

        item = modifier(item);

        size_t &target = (item % monkey.divisor == 0) ? monkey.target_true
                                                      : monkey.target_false;

        if (item % monkey.divisor == 0) {
          monkeys[monkey.target_true].items.push(item);
        } else {
          monkeys[monkey.target_false].items.push(item);
        }
      }
    }
  }

  long long first = 0;
  long long second = 0;

  for (Monkey &monkey : monkeys) {
    if (monkey.inspections > first) {
      second = first;
      first = monkey.inspections;
    } else if (monkey.inspections > second) {
      second = monkey.inspections;
    }
  }

  return first * second;
}

int main() {
  std::ifstream file("../puzzle_input.csv");

  std::vector<Monkey> monkeys;
  int product = 1;

  Monkey current_monkey = Monkey();
  int monkey_line = 0;

  for (std::string line; std::getline(file, line); ++monkey_line) {
    switch (monkey_line) {
    case 1: {
      std::replace(line.begin(), line.end(), ',', ' ');
      std::istringstream stream(line.substr(18));

      for (std::string item; stream >> item;) {
        current_monkey.items.push(std::stoi(item));
      }
    } break;

    case 2: {
      switch (line[23]) {
      case '+':
        current_monkey.operation.op = ADD;
        break;
      case '*':
        current_monkey.operation.op = MULTIPLY;
        break;
      }

      std::string value_str = line.substr(25);

      if (value_str == "old") {
        current_monkey.operation.value = -1;
      } else {
        current_monkey.operation.value = std::stoi(value_str);
      }
    } break;

    case 3:
      current_monkey.divisor = std::stoi(line.substr(21));
      product *= current_monkey.divisor;
      break;

    case 4:
      current_monkey.target_true = std::stoi(line.substr(29));
      break;

    case 5:
      current_monkey.target_false = std::stoi(line.substr(30));
      monkeys.push_back(current_monkey);

      current_monkey = Monkey();
      monkey_line = -2;
      break;
    }
  }

  std::cout << "[PART 1] Monkey business: "
            << monkey_business(
                   monkeys,
                   [](long long item) -> long long { return item / 3; }, 20)
            << "\n";

  std::cout << "[PART 2] Monkey business: "
            << monkey_business(
                   monkeys,
                   [product](long long item) -> long long {
                     return item % product;
                   },
                   10000)
            << "\n";
}