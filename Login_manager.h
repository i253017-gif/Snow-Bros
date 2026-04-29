#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

// ============================================================
// Login_manager.h
// Handles login, registration, password hashing
// Written by: Ishmal (Student B)
// Spec ref: Section 10.1
// ============================================================

class Login_manager {
private:
    std::string current_user;
    bool        logged_in;

    // custom hash - your formula
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

    // checks if username already in users.txt
    bool username_exists(std::string username) {
        std::ifstream file("users.txt");
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string uid, uname;
            std::getline(ss, uid, '|');
            std::getline(ss, uname, '|');
            if (uname == username) return true;
        }
        return false;
    }

    std::string generate_user_id() {
        return std::to_string((long long)std::time(nullptr));
    }

public:
    Login_manager() : current_user(""), logged_in(false) {}

    // tries to login - returns true if success
    bool login(std::string username, std::string password) {
        std::string hashed = hash_password(password);
        std::ifstream file("users.txt");
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string uid, uname, phash;
            std::getline(ss, uid, '|');
            std::getline(ss, uname, '|');
            std::getline(ss, phash, '|');
            if (uname == username && phash == hashed) {
                current_user = username;
                logged_in = true;
                return true;
            }
        }
        return false;
    }

    // registers new user - returns true if success
    bool register_user(std::string username, std::string password, std::string email) {
        if (username_exists(username)) return false;
        std::ofstream file("users.txt", std::ios::app);
        file << generate_user_id() << "|"
            << username << "|"
            << hash_password(password) << "|"
            << email << "|"
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
    bool        get_logged_in() { return logged_in; }
};