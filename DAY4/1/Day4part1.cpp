#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream file;
  file.open("puzzle_input.csv");
  if (file.fail()) {
    std::cout << "Unable to open the file" << std::endl;
  }
  std::string line;
  std::string str1;
  std::string str2;
  std::string str3;
  std::string str4;
  std::string str5;
  std::string str6;
  int buffer1;
  int buffer2;
  int counter = 0;

  while (file.good()) {
    getline(file, line);
    str1 = line.substr(0, line.find(","));
    str2 = line.substr(line.find(",") + 1, line.length());
    str3 = str1.substr(0, str1.find("-"));
    str4 = str1.substr(str1.find("-") + 1, str1.length());
    str5 = str2.substr(0, str2.find("-"));
    // We should be searching in string 2 not string 1
    str6 = str2.substr(str2.find("-") + 1, str2.length());
    int num1 = stoi(str3);
    int num2 = stoi(str4);
    int num3 = stoi(str5);
    // String 6 is empty for some reason
    // The rest seem to be okay
    int num4 = stoi(str6);
    if (num1 <= num3 && num2 >= num4 || num3 <= num1 && num4 >= num2) {
      counter++;
    }
  }
  file.close();
  std::cout << counter << std::endl;
}