#include "DB_manager.h"
#include <fstream>    // for reading and writing files
#include <sstream>    // for splitting lines by |
#include <ctime>      // for getting current time

// ============================================================
// DB_manager.cpp
// Written by: Ishmal (Student B)
// Spec ref: Section 10.2 and 10.3
// ============================================================

// constructor - sets up file names
DB_manager::DB_manager() {
    game_file = "progress.txt";
    leaderboard_file = "leaderboard.txt";
    active_user = "";
}

// sets which user is currently playing
void DB_manager::set_active_user(std::string username) {
    active_user = username;
}

// returns who is currently playing
std::string DB_manager::get_active_user() {
    return active_user;
}

// -------------------------------------------------------
// save_data()
// saves player progress to progress.txt
// FORMAT: username | level | lives | gems | score | time
// if player already has a save - it gets updated
// if not - a new line is added
// -------------------------------------------------------
void DB_manager::save_data(int level, int lives, int gems, int score) {

    // step 1 - read ALL existing lines from progress.txt
    std::ifstream read_file(game_file);
    std::string line;
    std::string all_lines = ""; // will hold updated file content
    bool found = false;         // did we find this player's save?

    while (std::getline(read_file, line)) {
        // split line by | to get each piece of data
        std::stringstream ss(line);
        std::string saved_username;
        std::getline(ss, saved_username, '|'); // first piece = username

        if (saved_username == active_user) {
            // found this player's save - replace it with new data
            all_lines += active_user + "|"
                + std::to_string(level) + "|"
                + std::to_string(lives) + "|"
                + std::to_string(gems) + "|"
                + std::to_string(score) + "|"
                + std::to_string((long long)std::time(nullptr)) + "\n";
            found = true;
        }
        else {
            // not this player - keep their data unchanged
            all_lines += line + "\n";
        }
    }
    read_file.close();

    // step 2 - if player had no save, add a new line
    if (!found) {
        all_lines += active_user + "|"
            + std::to_string(level) + "|"
            + std::to_string(lives) + "|"
            + std::to_string(gems) + "|"
            + std::to_string(score) + "|"
            + std::to_string((long long)std::time(nullptr)) + "\n";
    }

    // step 3 - write everything back to progress.txt
    std::ofstream write_file(game_file);
    write_file << all_lines;
    write_file.close();
}

// -------------------------------------------------------
// load_data()
// loads player progress from progress.txt
// fills in level, lives, gems, score by reference
// returns true if save found, false if not
// -------------------------------------------------------
bool DB_manager::load_data(int& level, int& lives, int& gems, int& score) {

    std::ifstream file(game_file);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        // split each piece of data by |
        std::string saved_username, saved_level, saved_lives, saved_gems, saved_score;
        std::getline(ss, saved_username, '|');
        std::getline(ss, saved_level, '|');
        std::getline(ss, saved_lives, '|');
        std::getline(ss, saved_gems, '|');
        std::getline(ss, saved_score, '|');

        if (saved_username == active_user) {
            // found this player's save!
            // convert strings back to integers
            level = std::stoi(saved_level);
            lives = std::stoi(saved_lives);
            gems = std::stoi(saved_gems);
            score = std::stoi(saved_score);
            file.close();
            return true; // save found!
        }
    }

    file.close();
    return false; // no save found for this player
}

// -------------------------------------------------------
// add_to_leaderboard()
// adds player score to leaderboard.txt
// FORMAT: username | score | level_reached | date
// spec says top 10 scores are displayed
// -------------------------------------------------------
void DB_manager::add_to_leaderboard(int score, int level_reached) {

    // append new score entry to leaderboard.txt
    std::ofstream file(leaderboard_file, std::ios::app);
    file << active_user + "|"
        + std::to_string(score) + "|"
        + std::to_string(level_reached) + "|"
        + std::to_string((long long)std::time(nullptr)) + "\n";
    file.close();
}

// -------------------------------------------------------
// has_save_data()
// checks if player has existing saved progress
// returns true if save found, false if not
// -------------------------------------------------------
bool DB_manager::has_save_data() {
    int level, lives, gems, score; // dummy variables just for checking
    return load_data(level, lives, gems, score);
}

// -------------------------------------------------------
// delete_save_data()
// removes player's save from progress.txt
// used when player starts a new game
// -------------------------------------------------------
void DB_manager::delete_save_data() {

    // read all lines except this player's
    std::ifstream read_file(game_file);
    std::string line;
    std::string all_lines = "";

    while (std::getline(read_file, line)) {
        std::stringstream ss(line);
        std::string saved_username;
        std::getline(ss, saved_username, '|');

        // keep everyone's data except this player
        if (saved_username != active_user) {
            all_lines += line + "\n";
        }
    }
    read_file.close();

    // write back without this player's data
    std::ofstream write_file(game_file);
    write_file << all_lines;
    write_file.close();
}