#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

class Login_manager {
private:
    std::string current_user;
    bool logged_in;
    const char separator = ';';

    std::string hash_password(std::string password) {
        if (password.empty()) return "0";
        int result = (int)password[0];
        int total = result;
        for (int i = 1; i < (int)password.length(); i++) {
            result = result % (int)password[i];
            total += result + (int)password[i];
        }
        return std::to_string(total);
    }

    bool username_exists(std::string username) {
        std::ifstream file("users.txt");
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string user_id, user_name;
            std::getline(ss, user_id, separator);
            std::getline(ss, user_name, separator);
            // CHANGED: was comparing user_name == user_name (always true)
            if (user_name == username)
                return true;
        }
        return false;
    }

    std::string generate_user_id() {
        std::ifstream file("users.txt");
        std::string line;
        int count = 0;
        while (std::getline(file, line)) count++;
        return std::to_string(count + 1);
    }

public:
    Login_manager() : current_user(""), logged_in(false) {}

    bool login(std::string username, std::string password) {
        std::string hashed = hash_password(password);
        std::ifstream file("users.txt");
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string user_id, user_name, p_hash;
            std::getline(ss, user_id, separator);
            std::getline(ss, user_name, separator);
            std::getline(ss, p_hash, separator);
            if (user_name == username && p_hash == hashed) {
                current_user = username;
                logged_in = true;
                return true;
            }
        }
        return false;
    }

    bool register_user(std::string username, std::string password, std::string email) {
        if (username_exists(username)) return false;
        std::ofstream file("users.txt", std::ios::app);
        file << generate_user_id() << separator
            << username << separator
            << hash_password(password) << separator
            << email << separator
            << generate_user_id() << "\n";
        current_user = username;
        logged_in = true;
        return true;
    }

    void logout() {
        current_user = "";
        logged_in = false;
    }

    std::string get_current_user() { return current_user; }
    bool get_logged_in() { return logged_in; }
};