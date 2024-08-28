#include "tuffle.h"
std::string DoCheck(std::string guess, std::string answer) {
  std::string wordcolors = "BBBBB";
  for (int i = 0; i < answer.size(); i++) {
    if (guess[i] == answer[i]) {
      wordcolors[i] = 'G';
      answer[i] = '-';
    }
  }
  for (int i = 0; i < answer.size(); i++) {
    if (answer.find(guess[i]) != -1) {
      int index = answer.find(guess[i]);
      if (wordcolors[i] != 'G') {
        wordcolors[i] = 'Y';
        answer[index] = '-';
      }
    }
  }
  return wordcolors;
}

void TuffleGame::NewGame() {
  game_state_ = GameState(dictionary_.GetRandomTuffle());
  game_state_.SetGameStatus("active");
}

void TuffleGame::LetterKeyPressed(char key) {
  if (game_state_.GetGameStatus() != "active") {
    return;
  }
  game_state_.SetError("");
  std::vector<std::string> guesses = game_state_.GetGuessedWords();
  if (guesses.size() == 0) {
    guesses.push_back("");
  }
  int index = guesses.size() - 1;
  std::string guess = guesses.at(index);
  if (guess.size() != 5) {
    guesses.at(index) = guess + key;
    game_state_.SetGuessedWords(guesses);
  }
}

void TuffleGame::EnterKeyPressed() {
  if (game_state_.GetGameStatus() != "active") {
    return;
  }
  std::vector<std::string> guesses = game_state_.GetGuessedWords();
  int index = guesses.size() - 1;
  std::string guess = guesses.at(index);
  if (guess.size() < 5) {
    game_state_.SetError("Please enter a word with 5 characters.");
    return;
  }
  if (!dictionary_.IsValidGuess(guess)) {
    game_state_.SetError("Please enter a valid word.");
    return;
  }
  std::vector<std::string> boardcolors = game_state_.GetBoardColors();
  std::string color = DoCheck(guess, game_state_.GetAnswer());
  boardcolors.push_back(color);
  game_state_.SetBoardColors(boardcolors);
  if (color == "GGGGG") {
    game_state_.SetGameStatus("win");
  } else if (guesses.size() > 5) {
    game_state_.SetGameStatus("lose");
  } else {
    guesses.push_back("");
    game_state_.SetGuessedWords(guesses);
  }
}

void TuffleGame::DeleteKeyPressed() {
  if (game_state_.GetGameStatus() != "active") {
    return;
  }
  std::vector<std::string> guesses = game_state_.GetGuessedWords();
  int index = guesses.size() - 1;
  std::string guess = guesses.at(index);
  if (guess.size() == 0) {
    return;
  }
  guess.pop_back();
  guesses.at(index) = guess;
  game_state_.SetGuessedWords(guesses);
}

crow::json::wvalue TuffleGame::GameStateInJson() {
  crow::json::wvalue game_state_json({});
  game_state_json["answer"] = game_state_.GetAnswer();
  game_state_json["boardColors"] = game_state_.GetBoardColors();
  game_state_json["guessedWords"] = game_state_.GetGuessedWords();
  game_state_json["gameStatus"] = game_state_.GetGameStatus();
  game_state_json["errorMessage"] = game_state_.GetErrorMsg();
  return game_state_json;
}