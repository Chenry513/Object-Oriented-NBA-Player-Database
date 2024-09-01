#include "gtest/gtest.h"
#include "Database.h"  // Make sure this is the correct path to your Database header file.
#include <sstream>

class DatabaseTest : public ::testing::Test {
protected:
    Database db;

    void SetUp() override {
        // Initialize the database; make sure this prepares the database properly for each test.
        db.initializeDatabase();  // Assumes this method sets up the database connection.
    }
};

TEST_F(DatabaseTest, AppendToDBTest) {
    Player newPlayer("New Player", "New Team", "Guard", "7000 USD", 99, 2023);
    EXPECT_NO_THROW(db.appendToDB(newPlayer)) << "appendToDB should successfully insert the player without throwing errors.";
}


TEST_F(DatabaseTest, AppendTest) {
    Player newPlayer("New Player", "New Team", "Guard", "7000 USD", 99, 2023);

    // First append should succeed and add the player.
    db.append(newPlayer);  // Assuming `append` internally checks for duplicates and interacts with the database.

    // Attempt to append the same player again; expect no change in state due to internal duplicate checks.
    EXPECT_NO_THROW(db.append(newPlayer)) << "Appending the same player should not cause errors; duplicate check should prevent re-insertion.";

    // Ideally, you should have a way to check if the size of your internal data structure has not changed or the player hasn't been duplicated.
    // Since such a method is not specified, consider implementing `get_size()` or similar to enable this check.
}


TEST_F(DatabaseTest, SearchPlayerSubstring) {
    std::ostringstream output;
    auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect cout to output stream for capturing

    // Test with a substring that matches one of the players
    db.search_playersub("Doe");
    std::string result = output.str();
    EXPECT_NE(result.find("John Doe"), std::string::npos) << "John Doe should be found with 'Doe' substring.";
    output.str(""); output.clear(); // Clear the output stream for next test

    // Test with a substring that matches no players
    db.search_playersub("XYZ");
    result = output.str();
    EXPECT_NE(result.find("No player has this name"), std::string::npos) << "Should report no player found for 'XYZ' substring.";

    std::cout.rdbuf(old_buf); // Reset cout to standard output
}

TEST_F(DatabaseTest, SearchTeamSubstring) {
    std::ostringstream output;
    auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect cout to capture output

    // Test with a substring that matches one of the teams
    db.search_teamsub("Lakers");
    std::string result = output.str();
    EXPECT_NE(result.find("Lakers"), std::string::npos) << "Players from Lakers should be found.";
    output.str(""); output.clear(); // Clear output for next test

    // Test with a substring that matches no teams
    db.search_teamsub("Sharks");
    result = output.str();
    EXPECT_NE(result.find("No player on this team"), std::string::npos) << "Should report no players found for 'Sharks' team.";

    std::cout.rdbuf(old_buf); // Reset cout to standard output
}

#include <sstream>

TEST_F(DatabaseTest, SearchPosition) {
    std::ostringstream output;
    auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect cout to capture output

    // Test with a position that matches one of the players
    db.search_pos("Guard");
    std::string result = output.str();
    EXPECT_NE(result.find("Guard"), std::string::npos) << "Players with position 'Guard' should be found.";
    output.str(""); output.clear(); // Clear the output stream for next test

    // Test with a position that matches no players
    db.search_pos("Coach");
    result = output.str();
    EXPECT_NE(result.find("No player plays this position"), std::string::npos) << "Should report no player found for 'Coach' position.";

    std::cout.rdbuf(old_buf); // Reset cout to standard output
}

TEST_F(DatabaseTest, SearchSalarySubstring) {
    std::ostringstream output;
    auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect cout to capture output

    // Test with a salary substring that matches one of the players
    db.searchsalsub("5000");
    std::string result = output.str();
    EXPECT_NE(result.find("5000 USD"), std::string::npos) << "Players with salary containing '5000' should be found.";
    output.str(""); output.clear(); // Clear output for next test

    // Test with a salary substring that matches no players
    db.searchsalsub("10000");
    result = output.str();
    EXPECT_NE(result.find("No player makes this amount of money"), std::string::npos) << "Should report no player found with salary '10000'.";

    std::cout.rdbuf(old_buf); // Reset cout to standard output
}


#include <sstream>

TEST_F(DatabaseTest, SearchJersey) {
    std::ostringstream output;
    auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect cout to capture output

    // Test with a jersey number that matches one of the players
    db.search_jersey(23);  // Assuming jersey number 23 is common in your test setup
    std::string result = output.str();
    EXPECT_NE(result.find("Player found:"), std::string::npos) << "Players with jersey number '23' should be found.";
    output.str(""); output.clear(); // Clear the output stream for next test

    // Test with a jersey number that matches no players
    db.search_jersey(100); // Assuming jersey number 100 does not exist
    result = output.str();
    EXPECT_NE(result.find("No player has that jersey number"), std::string::npos) << "Should report no player found with jersey number '100'.";

    std::cout.rdbuf(old_buf); // Reset cout to standard output
}


TEST_F(DatabaseTest, SearchJerseyRange) {
    std::ostringstream output;
    auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect cout to capture output

    // Test with a jersey range that includes players
    db.search_range_jersey(10, 30);  // Assuming this range includes some players
    std::string result = output.str();
    EXPECT_NE(result.find("Player found:"), std::string::npos) << "Players with jersey numbers between 10 and 30 should be found.";
    output.str(""); output.clear(); // Clear output for next test

    // Test with a jersey range that includes no players
    db.search_range_jersey(101, 200); // Assuming no players have jerseys in this range
    result = output.str();
    EXPECT_NE(result.find("no players with jerseys in this range"), std::string::npos) << "Should report no players found with jerseys between 101 and 200.";

    std::cout.rdbuf(old_buf); // Reset cout to standard output
}

#include <sstream>

TEST_F(DatabaseTest, SearchRookieYear) {
    std::ostringstream output;
    auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect cout to capture output

    // Test with a rookie year that matches one of the players
    db.search_rookie(2019);  // Assuming you have players who started in 2019
    std::string result = output.str();
    EXPECT_NE(result.find("Player found:"), std::string::npos) << "Players with rookie year '2019' should be found.";
    output.str(""); output.clear(); // Clear the output stream for the next test

    // Test with a rookie year that matches no players
    db.search_rookie(2000); // Assuming no players have this rookie year
    result = output.str();
    EXPECT_NE(result.find("No player with rookie years in this year"), std::string::npos) << "Should report no player found with rookie year '2000'.";

    std::cout.rdbuf(old_buf); // Reset cout to standard output
}

TEST_F(DatabaseTest, SearchRookieYearRange) {
    std::ostringstream output;
    auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect cout to capture output

    // Test with a rookie year range that includes players
    db.search_range_rookie(2018, 2021);  // Assuming this range includes some players
    std::string result = output.str();
    EXPECT_NE(result.find("Player found:"), std::string::npos) << "Players with rookie years between 2018 and 2021 should be found.";
    output.str(""); output.clear(); // Clear output for the next test

    // Test with a rookie year range that includes no players
    db.search_range_rookie(1990, 1995); // Assuming no players have rookie years in this range
    result = output.str();
    EXPECT_NE(result.find("no players with rookie years in this time frame"), std::string::npos) << "Should report no players found with rookie years between 1990 and 1995.";

    std::cout.rdbuf(old_buf); // Reset cout to standard output
}

TEST_F(DatabaseTest, RemovePlayerSubFromDB) {
    // Insert a player to ensure there's something to delete
    Player playerToAdd("John Doe", "Lakers", "Guard", "5000 USD", 23, 2019);
    db.appendToDB(playerToAdd);

    // Attempt to remove using a substring that matches the added player
    EXPECT_NO_THROW(db.remove_playersub_from_db("Doe")) << "Removing players by name substring should not throw errors.";

    // Optional: Verify the player has been removed if direct database querying is possible
    // This requires a method to check the database directly, which isn't provided in the current setup.
}

TEST_F(DatabaseTest, RemoveTeamSubFromDB) {
    // Insert a player to ensure there's something to delete
    Player playerToAdd("Jane Doe", "Warriors", "Forward", "6000 USD", 30, 2018);
    db.appendToDB(playerToAdd);

    // Attempt to remove using a substring that matches the added player's team
    EXPECT_NO_THROW(db.remove_teamsub_from_db("Warriors")) << "Removing players by team substring should not throw errors.";

    // Optional: Verify the team has been removed if direct database querying is possible
    // This requires a method to check the database directly, which isn't provided in the current setup.
}

TEST_F(DatabaseTest, RemoveJerseyFromDB) {
    // Presume insertion of a player with a specific jersey number for testing
    Player playerToAdd("John Doe", "Lakers", "Guard", "5000 USD", 23, 2019);
    db.appendToDB(playerToAdd);

    // Attempt to remove player by jersey number
    EXPECT_NO_THROW(db.remove_jersey_from_db(23)) << "Removing players by jersey number should not throw errors.";

    // Optional: Verify the player has been removed if direct database querying is possible
    // This requires a method to check the database directly, which isn't provided in the current setup.
}


TEST_F(DatabaseTest, RemoveRookieFromDB) {
    // Presume insertion of a player with a specific rookie year for testing
    Player playerToAdd("Jane Doe", "Warriors", "Forward", "6000 USD", 30, 2018);
    db.appendToDB(playerToAdd);

    // Attempt to remove player by rookie year
    EXPECT_NO_THROW(db.remove_rookie_from_db(2018)) << "Removing players by rookie year should not throw errors.";

    // Optional: Verify the rookie has been removed if direct database querying is possible
    // This requires a method to check the database directly, which isn't provided in the current setup.
}

TEST_F(DatabaseTest, RemoveJerseyRangeFromDB) {
    // Assuming insertion of players within the range for the purpose of this test
    db.appendToDB(Player("Player One", "Team One", "Guard", "1000 USD", 10, 2018));
    db.appendToDB(Player("Player Two", "Team Two", "Forward", "2000 USD", 20, 2019));

    // Attempt to remove players by jersey number range
    EXPECT_NO_THROW(db.remove_jerseyran_from_db(10, 20)) << "Removing players by jersey number range should not throw errors.";

    // Optional: Verify the players have been removed if direct database querying is possible
    // This step requires a method to check the database directly, which isn't provided in the current setup.
}

TEST_F(DatabaseTest, RemoveRookieYearRangeFromDB) {
    // Presuming the insertion of players within the rookie year range for the test
    db.appendToDB(Player("Rookie One", "Team One", "Guard", "3000 USD", 30, 2010));
    db.appendToDB(Player("Rookie Two", "Team Two", "Center", "4000 USD", 40, 2012));

    // Attempt to remove players by rookie year range
    EXPECT_NO_THROW(db.remove_rookieran_from_db(2010, 2012)) << "Removing players by rookie year range should not throw errors.";

    // Optional: Confirm the removal if direct database querying is possible
    // As before, this requires a method to check the database, not provided in the setup.
}

TEST_F(DatabaseTest, RemovePositionFromDB) {
    // Assuming the insertion of players with a specific position for the purpose of this test
    db.appendToDB(Player("John Doe", "Lakers", "Guard", "5000 USD", 23, 2019));
    db.appendToDB(Player("Jane Doe", "Lakers", "Guard", "6000 USD", 24, 2020));

    // Attempt to remove players by position
    EXPECT_NO_THROW(db.remove_pos_from_db("Guard")) << "Removing players by position should not throw errors.";

    // Optional: Verify the players have been removed if direct database querying is possible
    // This step requires a method to check the database directly, which isn't provided in the current setup.
}

TEST_F(DatabaseTest, RemoveSalarySubstringFromDB) {
    // Presuming the insertion of players with specific salary amounts for testing
    db.appendToDB(Player("Alice Doe", "Warriors", "Forward", "7500 USD", 25, 2021));
    db.appendToDB(Player("Bob Doe", "Warriors", "Center", "7500 USD", 26, 2022));

    // Attempt to remove players by a salary substring
    EXPECT_NO_THROW(db.remove_salsub_from_db("7500")) << "Removing players by salary substring should not throw errors.";

    // Optional: Confirm the removal if direct database querying is possible
    // As before, this requires a method to check the database, not provided in the setup.
}
