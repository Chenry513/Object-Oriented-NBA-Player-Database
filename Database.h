#include <iostream>     
#include <fstream>      
#include <string>       
#include <algorithm>    
#include <cassert>  
#include "Player.h"
#include "json.hpp" 
using json = nlohmann::json;

using namespace std;

class Database{
private:
	int cap;      // capacity for the dynamic array
	Player* data; // pinter to first array element of player objects 
	int sz;		  // size of array
public:

	//destrucor
	~Database(){
		delete[] data;
		data = nullptr;
	}

	//append a player to the database(array fo player objects)
	void append(Player aplayer){
		//checking if player exists
		string record_exists;
		for(int j = 0; j<sz; j++){
			if((aplayer.get_player() == data[j].get_player()) && (aplayer.get_team() == data[j].get_team()) && (aplayer.get_pos() == data[j].get_pos()) 
				&& (aplayer.get_sal() == data[j].get_sal()) && (aplayer.get_jersey() == data[j].get_jersey()) && (aplayer.get_jersey() == data[j].get_jersey()) ){
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

	//function that removes a player by searching for the name
	void remove_player(const string& info){
		Player* new_data = new Player[cap];
		int counter = 0;
		int j = 0;
		for(int i = 0; i<sz; i++){
			if(data[i].get_player() != info){
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

	//function that removes a player by searching for the team
	void remove_team(const string& info){
		Player* new_data = new Player[cap];
		int counter = 0;
		int j = 0;
		for(int i = 0; i<sz; i++){
			if(data[i].get_team() != info){
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

	//function that removes a player by searching for the position
	void remove_pos(const string& info){
		Player* new_data = new Player[cap];
		int counter = 0;
		int j = 0;
		for(int i = 0; i<sz; i++){
			if(data[i].get_pos() != info){
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

	//function that removes a player by searching for the salary
	void remove_sal(const string& info){
		Player* new_data = new Player[cap];
		int counter = 0;
		int j = 0;
		for(int i = 0; i<sz; i++){
			if(data[i].get_sal() != info){
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

	//function that removes a player by searching for the position including a substring with the posiion 
	void remove_possub(const string& info){
		Player* new_data = new Player[cap];
		int counter = 0;
		int j = 0;
		for(int i = 0; i<sz; i++){
			if(!(data[i].get_pos().find(info) != string::npos)){
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

	//function that removes a player by searching for the position including a substring with the posiion 
	void remove_salsub(const string& info){
		Player* new_data = new Player[cap];
		int counter = 0;
		int j = 0;
		for(int i = 0; i<sz; i++){
			if(!(data[i].get_sal().find(info) != string::npos)){
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

	// Constructor that reads info from a JSON file
	Database(): cap(100), sz(0) {
        Player* new_data = new Player[cap];
        data = new_data;

        ifstream inputstream("nba_players.json");
        json j;
        inputstream >> j;  // Deserialize the JSON data directly from the file

        for (auto& element : j) {
            string salary = to_string(element["salary"].get<unsigned int>()) + " USD";
            unsigned int jerseyNumber = element["number"].get<unsigned int>();
            unsigned int rookieYear = element["draft_year"].get<unsigned int>();

            Player player(
                element["name"].get<string>(),
                element["team"].get<string>(),
                element["position"].get<string>(),
                salary,
                jerseyNumber,
                rookieYear
            );

            append(player);  // Append player to the database
        }

        inputstream.close();
    }
};

