#include "tools.h"
#include <iostream>

int main() {
  string s = "abcdefgh";
  int array[] = {67, 68, 69};
  // int *arr = stringToIntArray(s);
  /*
  for (int i = 0; i < s.length(); i++) {
    cout << arr[i] << " ";
  }
  */
  int *arr = stringToIntArray(s);

  for (int i = 0; i < s.length(); i++) {
    cout << arr[i] << " " << endl;
  }
  free(arr);
  return 0;
}