#include "DB_manager.h"
#include <fstream>
#include <sstream>
#include <ctime>

DB_manager::DB_manager() {
    game_file = "progress.txt";
    leaderboard_file = "leaderboard.txt";
    active_user = "";
}

void DB_manager::set_active_user(std::string username) {
    active_user = username;
}

std::string DB_manager::get_active_user() {
    return active_user;
}

void DB_manager::save_data(int level, int lives, int gems, int score) {
    std::ifstream read_file(game_file);
    std::string line;
    std::string all_lines = "";
    bool found = false;

    while (std::getline(read_file, line)) {
        std::stringstream ss(line);
        std::string saved_username;
        std::getline(ss, saved_username, '|');
        if (saved_username == active_user) {
            all_lines += active_user + "|"
                + std::to_string(level) + "|"
                + std::to_string(lives) + "|"
                + std::to_string(gems) + "|"
                + std::to_string(score) + "\n";
            found = true;
        }
        else
            all_lines += line + "\n";
    }
    read_file.close();

    if (!found) {
        all_lines += active_user + "|"
            + std::to_string(level) + "|"
            + std::to_string(lives) + "|"
            + std::to_string(gems) + "|"
            + std::to_string(score) + "\n";
    }

    std::ofstream write_file(game_file);
    write_file << all_lines;
    write_file.close();
}

bool DB_manager::load_data(int& level, int& lives, int& gems, int& score) {
    std::ifstream file(game_file);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string saved_username, s_level, s_lives, s_gems, s_score;
        std::getline(ss, saved_username, '|');
        std::getline(ss, s_level, '|');
        std::getline(ss, s_lives, '|');
        std::getline(ss, s_gems, '|');
        std::getline(ss, s_score, '|');
        if (saved_username == active_user) {
            level = std::stoi(s_level);
            lives = std::stoi(s_lives);
            gems = std::stoi(s_gems);
            score = std::stoi(s_score);
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void DB_manager::add_to_leaderboard(int score, int level_reached) {
    std::ofstream file(leaderboard_file, std::ios::app);
    file << active_user << "|"
        << score << "|"
        << level_reached << "|"
        << (long long)std::time(nullptr) << "\n";
    file.close();
}

bool DB_manager::has_save_data() {
    int level, lives, gems, score;
    return load_data(level, lives, gems, score);
}

void DB_manager::delete_save_data() {
    std::ifstream read_file(game_file);
    std::string line;
    std::string all_lines = "";
    while (std::getline(read_file, line)) {
        std::stringstream ss(line);
        std::string saved_username;
        std::getline(ss, saved_username, '|');
        if (saved_username != active_user)
            all_lines += line + "\n";
    }
    read_file.close();
    std::ofstream write_file(game_file);
    write_file << all_lines;
    write_file.close();
}

// reads all entries, sorts by score, returns top 10
// simple bubble sort - no libraries needed
int DB_manager::get_top_10(LeaderboardEntry entries[10])
{
    // first read all entries into a big temp array
    LeaderboardEntry all[200];
    int count = 0;

    std::ifstream file(leaderboard_file);
    std::string line;
    while (std::getline(file, line) && count < 200)
    {
        std::stringstream ss(line);
        std::string s_user, s_score, s_level, s_time;
        std::getline(ss, s_user, '|');
        std::getline(ss, s_score, '|');
        std::getline(ss, s_level, '|');
        std::getline(ss, s_time, '|');

        if (s_user.empty() || s_score.empty()) continue;

        all[count].username = s_user;
        all[count].score = std::stoi(s_score);
        all[count].level_reached = std::stoi(s_level);
        all[count].timestamp = std::stoll(s_time);
        count++;
    }
    file.close();

    // bubble sort by score descending
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
            if (all[j].score < all[j + 1].score)
            {
                LeaderboardEntry tmp = all[j];
                all[j] = all[j + 1];
                all[j + 1] = tmp;
            }

    // copy top 10
    int take = count < 10 ? count : 10;
    for (int i = 0; i < take; i++)
        entries[i] = all[i];

    return take;
}