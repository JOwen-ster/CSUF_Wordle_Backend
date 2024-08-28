#include "dictionary.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <random>
#include <string>

Dictionary::Dictionary(const std::string& valid_tuffles_filename,
                       const std::string& valid_guesses_filename) {
  std::ifstream tuffles_file(valid_tuffles_filename);
  std::string word;
  while (tuffles_file >> word) {
    valid_tuffles_.push_back(word);
  }
  std::ifstream guesses_file(valid_guesses_filename);
  while (guesses_file >> word) {
    valid_guesses_.insert(word);
  }
  srand(time(nullptr));
}

bool Dictionary::IsValidGuess(const std::string& word) const {
  return valid_guesses_.find(word) != valid_guesses_.end();
}

const std::string& Dictionary::GetRandomTuffle() const {
  return valid_tuffles_.at(rand() % (valid_tuffles_.size()));
}
