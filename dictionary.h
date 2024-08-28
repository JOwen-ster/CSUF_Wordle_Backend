#include <string>
#include <unordered_set>
#include <vector>

#ifndef DICTIONARY_H
#define DICTIONARY_H

class Dictionary {
 public:
  Dictionary(const std::string &valid_tuffles_filename,
             const std::string &valid_guesses_filename);
  bool IsValidGuess(const std::string &word) const;
  const std::string &GetRandomTuffle() const;

 private:
  std::vector<std::string> valid_tuffles_;
  std::unordered_set<std::string> valid_guesses_;
};

#endif