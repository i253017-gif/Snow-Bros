#pragma once
#pragma once
#include <string>

// ============================================================
// DB_manager.h
// Handles saving and loading game data to text files
// Written by: Ishmal (Student B)
// Spec ref: Section 10.2 - Database Schema
// 
// Files used:
// progress.txt  -> saves player game progress
// leaderboard.txt -> saves top scores
// ============================================================

class DB_manager {

private:
    // names of the files we save data to
    std::string game_file;        // "progress.txt"
    std::string leaderboard_file; // "leaderboard.txt"

    // who is currently logged in
    std::string active_user;

public:
    // constructor - sets up file names
    DB_manager();

    // sets which user is currently playing
    void set_active_user(std::string username);

    // returns who is currently playing
    std::string get_active_user();

    // saves player progress to progress.txt
    // called automatically when level is completed
    // spec ref: Section 10.3 - auto save on level complete
    void save_data(int level, int lives, int gems, int score);

    // loads player progress from progress.txt
    // called when player logs in
    // returns false if no save found for this player
    bool load_data(int& level, int& lives, int& gems, int& score);

    // adds score to leaderboard.txt
    // called when game session ends
    // spec ref: Section 9.4 - Leaderboard
    void add_to_leaderboard(int score, int level_reached);

    // checks if player already has saved progress
    bool has_save_data();

    // deletes player progress (for new game)
    void delete_save_data();
};