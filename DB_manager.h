#pragma once
#include <string>

// one leaderboard entry
struct LeaderboardEntry {
    std::string username;
    int score;
    int level_reached;
    long long timestamp; // raw time - convert with ctime when displaying
};

class DB_manager {
private:
    std::string game_file;
    std::string leaderboard_file;
    std::string active_user;

public:
    DB_manager();
    void set_active_user(std::string username);
    std::string get_active_user();
    void save_data(int level, int lives, int gems, int score);
    bool load_data(int& level, int& lives, int& gems, int& score);
    void add_to_leaderboard(int score, int level_reached);
    bool has_save_data();
    void delete_save_data();
    // simple top 10 - fills array, returns how many entries found
    int get_top_10(LeaderboardEntry entries[10]);
};