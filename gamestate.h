#pragma once

#include <string>
#include <vector>

#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
 public:
  GameState(const std::string &answer) : ans_(answer) {}

  std::string GetAnswer() { return ans_; }
  std::vector<std::string> GetGuessedWords() { return guessed_words_; }
  std::vector<std::string> GetBoardColors() { return board_colors_; }
  std::string GetGameStatus() { return game_status_; }
  std::string GetErrorMsg() { return error_msg_; }

  void SetAnswer(const std::string &answer) { ans_ = answer; }
  void SetBoardColors(const std::vector<std::string> &vector) {
    board_colors_ = vector;
  }
  void SetGuessedWords(const std::vector<std::string> &vector) {
    guessed_words_ = vector;
  }
  void SetGameStatus(const std::string &status) { game_status_ = status; }
  void SetError(const std::string &error) { error_msg_ = error; }

  void Reset(const std::string &answer) {
    board_colors_.clear();
    guessed_words_.clear();
    game_status_ = "active";
    error_msg_ = "";
    ans_ = answer;
  }

 private:
  std::string ans_;
  std::string error_msg_;
  std::string game_status_;
  std::vector<std::string> board_colors_;
  std::vector<std::string> guessed_words_;
};

#endif  // GAMESTATE_H