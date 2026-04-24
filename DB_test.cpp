#include <iostream>
#include "DB_manager.h"

// ============================================================
// db_test.cpp
// Simple test for DB_manager - no SFML needed!
// Run this to verify save/load/leaderboard works correctly
// Written by: Ishmal (Student B)
// ============================================================

int main() {

    DB_manager db;

    std::cout << "=== DB_manager Test ===" << std::endl;
    std::cout << std::endl;

    // -------------------------------------------------------
    // TEST 1 - set active user
    // -------------------------------------------------------
    std::cout << "TEST 1: Setting active user to 'ishmal'" << std::endl;
    db.set_active_user("ishmal");
    std::cout << "Active user: " << db.get_active_user() << std::endl;
    std::cout << std::endl;

    // -------------------------------------------------------
    // TEST 2 - check if save exists (should be false first time)
    // -------------------------------------------------------
    std::cout << "TEST 2: Checking if save exists (should be NO first time)" << std::endl;
    if (db.has_save_data())
        std::cout << "Save found!" << std::endl;
    else
        std::cout << "No save found - correct!" << std::endl;
    std::cout << std::endl;

    // -------------------------------------------------------
    // TEST 3 - save data
    // -------------------------------------------------------
    std::cout << "TEST 3: Saving data - Level 3, Lives 2, Gems 150, Score 4500" << std::endl;
    db.save_data(3, 2, 150, 4500);
    std::cout << "Data saved to progress.txt!" << std::endl;
    std::cout << std::endl;

    // -------------------------------------------------------
    // TEST 4 - load data back
    // -------------------------------------------------------
    std::cout << "TEST 4: Loading data back" << std::endl;
    int level, lives, gems, score;
    if (db.load_data(level, lives, gems, score)) {
        std::cout << "Loaded successfully!" << std::endl;
        std::cout << "Level: " << level << std::endl;
        std::cout << "Lives: " << lives << std::endl;
        std::cout << "Gems:  " << gems << std::endl;
        std::cout << "Score: " << score << std::endl;
    }
    else {
        std::cout << "Load failed!" << std::endl;
    }
    std::cout << std::endl;

    // -------------------------------------------------------
    // TEST 5 - update save with new data
    // -------------------------------------------------------
    std::cout << "TEST 5: Updating save - Level 5, Lives 1, Gems 300, Score 9000" << std::endl;
    db.save_data(5, 1, 300, 9000);
    db.load_data(level, lives, gems, score);
    std::cout << "Updated Level: " << level << std::endl;
    std::cout << "Updated Lives: " << lives << std::endl;
    std::cout << "Updated Gems:  " << gems << std::endl;
    std::cout << "Updated Score: " << score << std::endl;
    std::cout << std::endl;

    // -------------------------------------------------------
    // TEST 6 - test with second player
    // -------------------------------------------------------
    std::cout << "TEST 6: Testing with second player 'abiha'" << std::endl;
    db.set_active_user("abiha");
    db.save_data(2, 2, 80, 2000);
    db.load_data(level, lives, gems, score);
    std::cout << "Abiha's Level: " << level << std::endl;
    std::cout << "Abiha's Score: " << score << std::endl;
    std::cout << std::endl;

    // -------------------------------------------------------
    // TEST 7 - make sure ishmal's data is unchanged
    // -------------------------------------------------------
    std::cout << "TEST 7: Checking ishmal's data is still correct" << std::endl;
    db.set_active_user("ishmal");
    db.load_data(level, lives, gems, score);
    std::cout << "Ishmal's Level: " << level << " (should be 5)" << std::endl;
    std::cout << "Ishmal's Score: " << score << " (should be 9000)" << std::endl;
    std::cout << std::endl;

    // -------------------------------------------------------
    // TEST 8 - add to leaderboard
    // -------------------------------------------------------
    std::cout << "TEST 8: Adding scores to leaderboard" << std::endl;
    db.set_active_user("ishmal");
    db.add_to_leaderboard(9000, 5);
    db.set_active_user("abiha");
    db.add_to_leaderboard(2000, 2);
    std::cout << "Scores added to leaderboard.txt!" << std::endl;
    std::cout << std::endl;

    // -------------------------------------------------------
    // TEST 9 - delete save data
    // -------------------------------------------------------
    std::cout << "TEST 9: Deleting ishmal's save data" << std::endl;
    db.set_active_user("ishmal");
    db.delete_save_data();
    if (db.has_save_data())
        std::cout << "Save still exists - something wrong!" << std::endl;
    else
        std::cout << "Save deleted successfully!" << std::endl;
    std::cout << std::endl;

    std::cout << "=== All tests done! Check progress.txt and leaderboard.txt ===" << std::endl;

    return 0;
}