#include <iostream>     
#include <fstream>      
#include <string>       
#include <algorithm>    
#include <cassert>  
#include "Player.h"
#include "json.hpp" 
#include "sqlite3.h"
using json = nlohmann::json;

using namespace std;

class Database{
private:
	int cap;      // capacity for the dynamic array
	Player* data; // pinter to first array element of player objects 
	int sz;		  // size of array
	sqlite3 *db;  // SQLite database connection pointer
    int rc;       // Return code for SQLite operations
public:
	bool intialization = false;

	// Constructor
	Database() : cap(100), sz(0), db(nullptr) {
        data = new Player[cap]; // Initialize the dynamic array with initial capacity
    }

	//destrucor
	~Database(){
		delete[] data;
		data = nullptr;
		if (db != nullptr) {
            sqlite3_close(db); // Ensure the database is closed if it was opened
        }
	}

	// Initialize database and load data
    void initializeDatabase() {
		if (db != nullptr) {
            sqlite3_close(db);  // Ensure any existing connection is closed
            db = nullptr;
        }
        rc = sqlite3_open("playerdata.db", &db);
        if (rc != SQLITE_OK) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            db = nullptr;
            return;
        }

        const char* sql = "SELECT Name, Team, Position, Salary, JerseyNumber, RookieYear FROM Players;";
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            db = nullptr;
            return;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Player player(
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                std::to_string(sqlite3_column_int(stmt, 3)) + " USD",
                sqlite3_column_int(stmt, 4),
                sqlite3_column_int(stmt, 5)
            );
            append(player); // Append players to the dynamic array
        }
		intialization = true;

        sqlite3_finalize(stmt);
        //sqlite3_close(db);
        //db = nullptr;
    }
	//append to db
	void appendToDB(const Player& aplayer) {
		// SQL statement for inserting a new player into the database
		const char* sql = "INSERT INTO Players (Name, Team, Position, Salary, JerseyNumber, RookieYear) VALUES (?, ?, ?, ?, ?, ?);";
		sqlite3_stmt* stmt;
		
		// Prepare the SQL statement
		if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
			// Bind the player data to the SQL statement
			sqlite3_bind_text(stmt, 1, aplayer.get_player().c_str(), -1, SQLITE_TRANSIENT);
			sqlite3_bind_text(stmt, 2, aplayer.get_team().c_str(), -1, SQLITE_TRANSIENT);
			sqlite3_bind_text(stmt, 3, aplayer.get_pos().c_str(), -1, SQLITE_TRANSIENT);
			sqlite3_bind_text(stmt, 4, aplayer.get_sal().c_str(), -1, SQLITE_TRANSIENT);
			sqlite3_bind_int(stmt, 5, aplayer.get_jersey());
			sqlite3_bind_int(stmt, 6, aplayer.get_rookie());

			// Execute the SQL statement
			if (sqlite3_step(stmt) != SQLITE_DONE) {
				cout << "Error inserting data into SQLite database: " << sqlite3_errmsg(db) << endl;
			}
			// Clean up the prepared statement to avoid resource leaks
			sqlite3_finalize(stmt);
		} else {
			cout << "SQL error while preparing the insertion statement: " << sqlite3_errmsg(db) << endl;
		}
	}

	//append a player to the database(array fo player objects)
	void append(Player aplayer){
		//checking if player exists
		string record_exists;
		for(int j = 0; j<sz; j++){
			if((aplayer.get_player() == data[j].get_player()) && (aplayer.get_team() == data[j].get_team()) && (aplayer.get_pos() == data[j].get_pos()) 
				&& (aplayer.get_sal() == data[j].get_sal()) && (aplayer.get_jersey() == data[j].get_jersey()) && (aplayer.get_rookie() == data[j].get_rookie()) ){
				string record_exists = "\nplayer already exists.";
				cout<<record_exists;
				return;			
			}
		}

		
		if(cap > sz){
			data[sz].set_player(aplayer.get_player());
			data[sz].set_team(aplayer.get_team());
			data[sz].set_pos(aplayer.get_pos());
			data[sz].set_sal(aplayer.get_sal());
			data[sz].set_jersey(aplayer.get_jersey());
			data[sz].set_rookie(aplayer.get_rookie());
			sz++;
			if(intialization == true){
				//cout<<"init: "<<intialization<< std::endl;
				appendToDB(aplayer);
			}
		}

		else{
			cap = 2*cap;
			Player* new_data = new Player[cap];
			for(int i = 0; i<sz; i++){
				new_data[i].set_player(aplayer.get_player());
				new_data[i].set_team(aplayer.get_team());
				new_data[i].set_pos(aplayer.get_pos());
				new_data[i].set_sal(aplayer.get_sal());
				new_data[i].set_jersey(aplayer.get_jersey());
				new_data[i].set_rookie(aplayer.get_rookie());
			}
			delete[] data;
			data = new_data;
			data[sz].set_player(aplayer.get_player());
			data[sz].set_team(aplayer.get_team());
			data[sz].set_pos(aplayer.get_pos());
			data[sz].set_sal(aplayer.get_sal());
			data[sz].set_jersey(aplayer.get_jersey());
			data[sz].set_rookie(aplayer.get_rookie());
			sz++;
			if(intialization == true){
				//cout<<"init: "<<intialization<< std::endl;
				appendToDB(aplayer);
			}
		}
	}
	
	//search function for player name including substrings for names, display all players with the same first/last name
	void search_playersub(const string& info){
		bool found = false;
		for(int i = 0; i<sz; i++){
			if(data[i].get_player().find(info) != string::npos){
				found = true;
				cout<<"\nPlayer found: ";
				cout<<data[i].get_player()<<", "<<
				data[i].get_team()<<", "<<
				data[i].get_pos()<<", "<<
				data[i].get_sal()<<", "<<
				to_string(data[i].get_jersey())<<", "<<
				to_string(data[i].get_rookie())<<"\n";
			}
		}

		if(found == false){
			cout<<"No player has this name\n";
		}
	}

	//search function for player team including substrings for names and display all players with the same team
	void search_teamsub(const string& info){
		bool found = false;
		for(int i = 0; i<sz; i++){
			if(data[i].get_team().find(info) != string::npos){
				found = true;
				cout<<"\nPlayer found: ";
				cout<<data[i].get_player()<<", "<<
				data[i].get_team()<<", "<<
				data[i].get_pos()<<", "<<
				data[i].get_sal()<<", "<<
				to_string(data[i].get_jersey())<<", "<<
				to_string(data[i].get_rookie())<<"\n";
			}
		}

		if(found == false){
			cout<<"No player on this team\n";
		}
	}

	//search function for player positon and display all players with the same position
	void search_pos(const string& info){
		bool found = false;
		for(int i = 0; i<sz; i++){
			if(data[i].get_pos() == info){
				found = true;
				cout<<"\nPlayer found: ";
				cout<<data[i].get_player()<<", "<<
				data[i].get_team()<<", "<<
				data[i].get_pos()<<", "<<
				data[i].get_sal()<<", "<<
				to_string(data[i].get_jersey())<<", "<<
				to_string(data[i].get_rookie())<<"\n";
			}
		}

		if(found == false){
			cout<<"No player plays this position.\n";
		}

	}

	//search function for player salary including substrings for salary display all players with the same salary
	void searchsalsub(const string& info){
		bool found = false;
		for(int i = 0; i<sz; i++){
			if(data[i].get_sal().find(info) != string::npos){
				found = true;
				cout<<"\nPlayer found: ";
				cout<<data[i].get_player()<<", "<<
				data[i].get_team()<<", "<<
				data[i].get_pos()<<", "<<
				data[i].get_sal()<<", "<<
				to_string(data[i].get_jersey())<<", "<<
				to_string(data[i].get_rookie())<<"\n";
			}
		}

		if(found == false){
			cout<<"No player makes this amount of money.\n";
		}
	}

	//search function for player jersey and display all players with the same number
	void search_jersey(const unsigned int& info){
		bool found = false;
		for(int i = 0; i<sz; i++){
			if(data[i].get_jersey() == info){
				found = true;
				cout<<"\nPlayer found: ";
				cout<<data[i].get_player()<<", "<<
				data[i].get_team()<<", "<<
				data[i].get_pos()<<", "<<
				data[i].get_sal()<<", "<<
				to_string(data[i].get_jersey())<<", "<<
				to_string(data[i].get_rookie())<<"\n";
			}
		}

		if(found == false){
			cout<<"No player has that jersey number.\n";
		}
	}

	//search function for player jersey in a range provided by the user
	//and display all players with the same number
	void search_range_jersey(const unsigned int& first, const unsigned int& second){
		bool found = false;
		for(int i = 0; i<sz; i++){
			if(data[i].get_jersey() >= first && data[i].get_jersey() <= second){
				found = true;
				cout<<data[i].get_player()<<", "<<
				data[i].get_team()<<", "<<
				data[i].get_pos()<<", "<<
				data[i].get_sal()<<", "<<
				to_string(data[i].get_jersey())<<", "<<
				to_string(data[i].get_rookie())<<"\n";
			}
		}
		if(found == false){
				cout<<"no players with jersies in this range.";
		}
	}

	//search function for player rooki year in a range provided by the user
	//and display all players with the same rookie year
	void search_range_rookie(const unsigned int& first, const unsigned int& second){
        bool found = false;
        for(int i = 0; i<sz; i++){
            if(data[i].get_rookie() >= first && data[i].get_rookie() <= second){
                found = true;
                cout<<data[i].get_player()<<", "<<
                data[i].get_team()<<", "<<
                data[i].get_pos()<<", "<<
                data[i].get_sal()<<", "<<
                to_string(data[i].get_jersey())<<", "<<
                to_string(data[i].get_rookie())<<"\n";
            }
        }
        if(found == false){
                cout<<"no players with rookie years in this time frame";
        }
    }

	//search function for player rookie year and display all players with the rookie year
	void search_rookie(const unsigned int& info){
        bool found = false;
        for(int i = 0; i<sz; i++){
            if(data[i].get_rookie() == info){
                found = true;
                cout<<"\nPlayer found: ";
                cout<<data[i].get_player()<<", "<<
                data[i].get_team()<<", "<<
                data[i].get_pos()<<", "<<
                data[i].get_sal()<<", "<<
                to_string(data[i].get_jersey())<<", "<<
                to_string(data[i].get_rookie())<<"\n";
            }
        }

        if(found == false){
            cout<<"No player with rookie years in this year.\n";
        }
    }
	
	//for substring of player names SQL db
	void remove_playersub_from_db(const std::string& info) {
		// SQL statement to remove players whose names contain the given substring
		const char* sql = "DELETE FROM Players WHERE Name LIKE ?;";
		sqlite3_stmt* stmt;

		// Prepare the SQL statement
		int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error while preparing the delete statement: " << sqlite3_errmsg(db) << std::endl;
			return;
		}

		// Create a search pattern that includes the '%' wildcard for partial matching
		std::string pattern = "%" + info + "%";

		// Bind the pattern to the query parameter
		rc = sqlite3_bind_text(stmt, 1, pattern.c_str(), -1, SQLITE_TRANSIENT);
		if (rc != SQLITE_OK) {
			std::cerr << "Error binding text to delete statement: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_finalize(stmt);
			return;
		}

		// Execute the SQL statement
		rc = sqlite3_step(stmt);
	
		// Finalize the statement to release resources
		sqlite3_finalize(stmt);
	}

	//remove substring of team names SQL db
	void remove_teamsub_from_db(const std::string& info) {
		// SQL statement to remove players whose team names contain the given substring
		const char* sql = "DELETE FROM Players WHERE Team LIKE ?;";
		sqlite3_stmt* stmt;

		// Prepare the SQL statement
		int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error while preparing the delete statement: " << sqlite3_errmsg(db) << std::endl;
			return;
		}
		
		// Create a pattern that includes the '%' wildcard for partial matching
		std::string pattern = "%" + info + "%";

		// Bind the pattern to the SQL query parameter
		rc = sqlite3_bind_text(stmt, 1, pattern.c_str(), -1, SQLITE_TRANSIENT);
		if (rc != SQLITE_OK) {
			std::cerr << "Error binding text to delete statement: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_finalize(stmt);
			return;
		}

		// Execute the SQL statement
		rc = sqlite3_step(stmt);
	
		// Finalize the statement to release resources
		sqlite3_finalize(stmt);
	}

	//remove by jersey from SQL db
	void remove_jersey_from_db(const unsigned int& jerseyNumber) {
		// SQL statement to delete players by a specific jersey number
		const char* sql = "DELETE FROM Players WHERE JerseyNumber = ?;";
		sqlite3_stmt* stmt;

		// Prepare the SQL statement
		int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error while preparing the delete statement: " << sqlite3_errmsg(db) << std::endl;
			return;
		}

		// Bind the jersey number to the query parameter
		rc = sqlite3_bind_int(stmt, 1, jerseyNumber);
		if (rc != SQLITE_OK) {
			std::cerr << "Error binding integer to delete statement: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_finalize(stmt);
			return;
		}

		// Execute the delete statement
		rc = sqlite3_step(stmt);
		
		// Finalize the statement to release resources
		sqlite3_finalize(stmt);
	}

	//remove by rookie year from SQL db
	void remove_rookie_from_db(const unsigned int& rookieYear) {
		// SQL statement to delete players by a specific rookie year
		const char* sql = "DELETE FROM Players WHERE RookieYear = ?;";
		sqlite3_stmt* stmt;

		// Prepare the SQL statement
		int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error while preparing the delete statement: " << sqlite3_errmsg(db) << std::endl;
			return;
		}

		// Bind the rookie year to the query parameter
		rc = sqlite3_bind_int(stmt, 1, rookieYear);
		if (rc != SQLITE_OK) {
			std::cerr << "Error binding integer to delete statement: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_finalize(stmt);
			return;
		}

		// Execute the delete statement
		rc = sqlite3_step(stmt);
		
		// Finalize the statement to release resources
		sqlite3_finalize(stmt);
	}

	//remove palyers in a range of jerseys from SQl db
	void remove_jerseyran_from_db(const unsigned int& first, const unsigned int& second) {
		// SQL statement to delete players with jersey numbers between `first` and `second`
		const char* sql = "DELETE FROM Players WHERE JerseyNumber BETWEEN ? AND ?;";
		sqlite3_stmt* stmt;

		// Prepare the SQL statement
		int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error while preparing the delete statement: " << sqlite3_errmsg(db) << std::endl;
			return;
		}

		// Bind the first and second jersey numbers to the query parameters
		rc = sqlite3_bind_int(stmt, 1, first);
		if (rc != SQLITE_OK) {
			std::cerr << "Error binding first jersey number: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_finalize(stmt);
			return;
		}
		rc = sqlite3_bind_int(stmt, 2, second);
		if (rc != SQLITE_OK) {
			std::cerr << "Error binding second jersey number: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_finalize(stmt);
			return;
		}

		// Execute the delete statement
		rc = sqlite3_step(stmt);
		
		// Finalize the statement to release resources
		sqlite3_finalize(stmt);
	}

	//remove players in a range of rookie years from SQl db
	void remove_rookieran_from_db(const unsigned int& first, const unsigned int& second) {
		// SQL statement to delete players with rookie years between `first` and `second`
		const char* sql = "DELETE FROM Players WHERE RookieYear BETWEEN ? AND ?;";
		sqlite3_stmt* stmt;

		// Prepare the SQL statement
		int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error while preparing the delete statement: " << sqlite3_errmsg(db) << std::endl;
			return;
		}

		// Bind the first and second rookie years to the query parameters
		rc = sqlite3_bind_int(stmt, 1, first);
		if (rc != SQLITE_OK) {
			std::cerr << "Error binding first rookie year: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_finalize(stmt);
			return;
		}
		rc = sqlite3_bind_int(stmt, 2, second);
		if (rc != SQLITE_OK) {
			std::cerr << "Error binding second rookie year: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_finalize(stmt);
			return;
		}

		// Execute the delete statement
		rc = sqlite3_step(stmt);
		
		// Finalize the statement to release resources
		sqlite3_finalize(stmt);
	}

	//remove players by their position from SQL db
	void remove_pos_from_db(const std::string& info) {
		// SQL statement to delete players by position
		const char* sql = "DELETE FROM Players WHERE Position = ?;";
		sqlite3_stmt* stmt;

		// Prepare the SQL statement
		int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error while preparing the delete statement: " << sqlite3_errmsg(db) << std::endl;
			return;
		}

		// Bind the position string to the query parameter
		rc = sqlite3_bind_text(stmt, 1, info.c_str(), -1, SQLITE_TRANSIENT);
		if (rc != SQLITE_OK) {
			std::cerr << "Error binding position to delete statement: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_finalize(stmt);
			return;
		}

		// Execute the delete statement
		rc = sqlite3_step(stmt);

		// Finalize the statement to release resources
		sqlite3_finalize(stmt);
	}

	//remove players bt their salary from SQL db
	void remove_salsub_from_db(const std::string& info) {
		// SQL statement to delete players whose salary contains the given substring
		const char* sql = "DELETE FROM Players WHERE Salary LIKE ?;";
		sqlite3_stmt* stmt;

		// Prepare the SQL statement
		int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error while preparing the delete statement: " << sqlite3_errmsg(db) << std::endl;
			return;
		}

		// Create a pattern that includes the '%' wildcard for partial matching
		std::string pattern = "%" + info + "%";

		// Bind the salary pattern to the query parameter
		rc = sqlite3_bind_text(stmt, 1, pattern.c_str(), -1, SQLITE_TRANSIENT);
		if (rc != SQLITE_OK) {
			std::cerr << "Error binding salary pattern to delete statement: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_finalize(stmt);
			return;
		}

		// Execute the delete statement
		rc = sqlite3_step(stmt);
		
		// Finalize the statement to release resources
		sqlite3_finalize(stmt);
	}

	//function that removes a player by searching for the position
	void remove_pos(const string& info){
		Player* new_data = new Player[cap];
		int counter = 0;
		int j = 0;
		for(int i = 0; i<sz; i++){
			if(data[i].get_pos() != info){
				remove_pos_from_db(info);
				new_data[j].set_player(data[i].get_player());
				new_data[j].set_team(data[i].get_team());
				new_data[j].set_pos(data[i].get_pos());
				new_data[j].set_sal(data[i].get_sal());
				new_data[j].set_jersey(data[i].get_jersey());
				new_data[j].set_rookie(data[i].get_rookie());
				j++;
			}
			else{
				counter++;
			}
		}
		sz-=counter;
		delete[] data;
		data = new_data;
	}

	void remove_salsub(const string& info){
		Player* new_data = new Player[cap];
		int counter = 0;
		int j = 0;
		for(int i = 0; i<sz; i++){
			if(!(data[i].get_sal().find(info) != string::npos)){
				remove_salsub_from_db(info);
				new_data[j].set_player(data[i].get_player());
				new_data[j].set_team(data[i].get_team());
				new_data[j].set_pos(data[i].get_pos());
				new_data[j].set_sal(data[i].get_sal());
				new_data[j].set_jersey(data[i].get_jersey());
				new_data[j].set_rookie(data[i].get_rookie());
				j++;
			}
			else{
				counter++;
			}
		}
		sz-=counter;
		delete[] data;
		data = new_data;
	}

	//function that removes a player by searching for the name including a substring with the player name
	void remove_playersub(const string& info){
		Player* new_data = new Player[cap];
		int counter = 0;
		int j = 0;
		for(int i = 0; i<sz; i++){
			if(!(data[i].get_player().find(info) != string::npos)){
				remove_playersub_from_db(info);
				new_data[j].set_player(data[i].get_player());
				new_data[j].set_team(data[i].get_team());
				new_data[j].set_pos(data[i].get_pos());
				new_data[j].set_sal(data[i].get_sal());
				new_data[j].set_jersey(data[i].get_jersey());
				new_data[j].set_rookie(data[i].get_rookie());
				j++;
			}
			else{
				counter++;
			}
		}
		sz-=counter;
		delete[] data;
		data = new_data;
	}

	//function that removes a player by searching for the team including a substring with the team name
	void remove_teamsub(const string& info){
		Player* new_data = new Player[cap];
		int counter = 0;
		int j = 0;
		for(int i = 0; i<sz; i++){
			if(!(data[i].get_team().find(info) != string::npos)){
				remove_teamsub_from_db(info);
				new_data[j].set_player(data[i].get_player());
				new_data[j].set_team(data[i].get_team());
				new_data[j].set_pos(data[i].get_pos());
				new_data[j].set_sal(data[i].get_sal());
				new_data[j].set_jersey(data[i].get_jersey());
				new_data[j].set_rookie(data[i].get_rookie());
				j++;
			}
			else{
				counter++;
			}
		}
		sz-=counter;
		delete[] data;
		data = new_data;
	}

	//function that removes a player by searching for the jersey num including all jerserys with that num
	void remove_jersey(const unsigned int& info){
		Player* new_data = new Player[cap];
		int counter = 0;
		int j = 0;
		for(int i = 0; i<sz; i++){
			if(data[i].get_jersey() != info){
				remove_jersey_from_db(info);
				new_data[j].set_player(data[i].get_player());
				new_data[j].set_team(data[i].get_team());
				new_data[j].set_pos(data[i].get_pos());
				new_data[j].set_sal(data[i].get_sal());
				new_data[j].set_jersey(data[i].get_jersey());
				new_data[j].set_rookie(data[i].get_rookie());
				j++;
			}
			else{
				counter++;
			}
		}
		sz-=counter;
		delete[] data;
		data = new_data;
	}

	//function that removes a player by searching for the rookie year num including all jerserys with the rookie year
	void remove_rookie(const unsigned int& info){
		Player* new_data = new Player[cap];
		int counter = 0;
		int j = 0;
		for(int i = 0; i<sz; i++){
			if(data[i].get_rookie() != info){
				remove_rookie_from_db(info);
				new_data[j].set_player(data[i].get_player());
				new_data[j].set_team(data[i].get_team());
				new_data[j].set_pos(data[i].get_pos());
				new_data[j].set_sal(data[i].get_sal());
				new_data[j].set_jersey(data[i].get_jersey());
				new_data[j].set_rookie(data[i].get_rookie());
				j++;
			}
			else{
				counter++;
			}
		}
		sz-=counter;
		delete[] data;
		data = new_data;
	}
	
	// function that deletes a player, by seraching for range of players between
	// jersey numbers prompted by the user
	void remove_jerseyran(const unsigned int& first, const unsigned int& second){
		Player* new_data = new Player[cap];
		int counter = 0;
		int j = 0;
		for(int i = 0; i<sz; i++){
			if(!(data[i].get_jersey() >= first && data[i].get_jersey() <= second)){
				remove_jerseyran_from_db(first,second);
				new_data[j].set_player(data[i].get_player());
				new_data[j].set_team(data[i].get_team());
				new_data[j].set_pos(data[i].get_pos());
				new_data[j].set_sal(data[i].get_sal());
				new_data[j].set_jersey(data[i].get_jersey());
				new_data[j].set_rookie(data[i].get_rookie());
				j++;
			}
			else{
				counter++;
			}
		}
		sz-=counter;
		delete[] data;
		data = new_data;
	}

	// function that deletes a player, by seraching for range of players between
	// rookie years prompted by the user
	void remove_rookieran(const unsigned int& first, const unsigned int& second){
		Player* new_data = new Player[cap];
		int counter = 0;
		int j = 0;
		for(int i = 0; i<sz; i++){
			if(!(data[i].get_rookie() >= first && data[i].get_rookie() <= second)){
				remove_rookieran_from_db(first, second);
				new_data[j].set_player(data[i].get_player());
				new_data[j].set_team(data[i].get_team());
				new_data[j].set_pos(data[i].get_pos());
				new_data[j].set_sal(data[i].get_sal());
				new_data[j].set_jersey(data[i].get_jersey());
				new_data[j].set_rookie(data[i].get_rookie());
				j++;
			}
			else{
				counter++;
			}
		}
		sz-=counter;
		delete[] data;
		data = new_data;
	}

	//Sorting the players names in alphabetical order.
	void sort_name(){
        bool done = false;
            Player tmp;
            while(!done){
                done = true;
                for(int i=0; i < sz-1; i++){
                    if(data[i].get_player() > data[i+1].get_player()){
                        done = false;
                        tmp = data[i];
                        data[i] = data[i+1];
                        data[i+1] = tmp;
                    }    
                }    
            }    
    }
	
	//Sorting the players names in reverse alphabetical order.
	void sort_name_rev(){
		sort_name();
		std::reverse(data, data + sz);
	}

	//Sorting the players salary in alphabetical order.
	void sort_salary(){
        bool done = false;
            Player tmp;
            while(!done){
                done = true;
                for(int i=0; i < sz-1; i++){
                    if(data[i].get_sal() > data[i+1].get_sal()){
                        done = false;
                        tmp = data[i];
                        data[i] = data[i+1];
                        data[i+1] = tmp;
                    }    
                }    
            }    
    }

	//Sorting the players salary in reverse alphabetical order.
	void sort_salary_rev(){
		sort_salary();
		std::reverse(data, data + sz);
	}

	//Sorting the players position in alphabetical order.
	void sort_pos(){
        bool done = false;
            Player tmp;
            while(!done){
                done = true;
                for(int i=0; i < sz-1; i++){
                    if(data[i].get_pos() > data[i+1].get_pos()){
                        done = false;
                        tmp = data[i];
                        data[i] = data[i+1];
                        data[i+1] = tmp;
                    }    
                }    
            }    
    }

	//Sorting the players positions in reverse alphabetical order.
	void sort_pos_rev(){
		sort_pos();
		std::reverse(data, data + sz);
	}

	//Sorting the players teams in alphabetical order.
	void sort_team(){
        bool done = false;
            Player tmp;
            while(!done){
                done = true;
                for(int i=0; i < sz-1; i++){
                    if(data[i].get_team() > data[i+1].get_team()){
                        done = false;
                        tmp = data[i];
                        data[i] = data[i+1];
                        data[i+1] = tmp;
                    }    
                }    
            }    
    }

	//Sorting the players teams in reverse alphabetical order.
	void sort_team_rev(){
		sort_team();
		std::reverse(data, data + sz);
	}

	//Sorting the players jersey in asending order.
	void sort_jersey(){
        bool done = false;
            Player tmp;
            while(!done){
                done = true;
                for(int i=0; i < sz-1; i++){
                    if(data[i].get_jersey() > data[i+1].get_jersey()){
                        done = false;
                        tmp = data[i];
                        data[i] = data[i+1];
                        data[i+1] = tmp;
                    }    
                }    
            }    
    }

	//Sorting the players jersey in descending order.
	void sort_jersey_rev(){
		sort_jersey();
		std::reverse(data, data + sz);
	}
	
	//Sorting the players rookie years in asending order.
	void sort_rookie_year(){
        bool done = false;
            Player tmp;
            while(!done){
                done = true;
                for(int i=0; i < sz-1; i++){
                    if(data[i].get_rookie() > data[i+1].get_rookie()){
                        done = false;
                        tmp = data[i];
                        data[i] = data[i+1];
                        data[i+1] = tmp;
                    }    
                }    
            }    
    }

	//Sorting the players jersey in descedning order.
	void sort_rookie_rev(){
		sort_rookie_year();
		std::reverse(data, data + sz);
	}
	
	//display all players with their fields in order
	void display_all(){
        for(int i=0; i<sz; i++){
            cout << data[i] << endl;
        }
    }
};

