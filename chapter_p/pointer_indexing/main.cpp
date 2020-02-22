#include <algorithm>
#include <iostream>
#include <iterator>  /* for std::begin and std::end */
 

/* Determine if a char is also a vowel */
bool isVowel(char ch) {
  switch (ch) {
  case 'e':  /* letter sorted by frequency in the English language */
  case 'E':
  case 'a':
  case 'A':
  case 'o':
  case 'O':
  case 'i':
  case 'I':
  case 'u':
  case 'U':
    return true;
  default:
    return false;
  }
}


int main() {
  char name[]{ "Mollie" };
  int numVowels{ std::count_if(std::begin(name), std::end(name), isVowel) };
 
  std::cout << name << " has " << numVowels << " vowels.\n";
 
  return 0;
}

