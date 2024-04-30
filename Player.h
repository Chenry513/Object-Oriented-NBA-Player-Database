#include <iostream>     
#include <fstream>      
#include <string>       
#include <algorithm>    
#include <cassert>      

using namespace std;

// This class keeps track of the Players names and identifies thier attributes
class Player{
private:
	string player_name;
	string team_name;
	string player_pos;
	string salary_per_year;
	unsigned int jersey_number;
	unsigned int rookie_year;
public:
	
    //default constuctor
    Player(): 
	player_name(""), team_name(""), player_pos(""), salary_per_year(""), jersey_number(0), rookie_year(0){}

    //constructor
	Player(const string& new_name, const string& new_team, const string& new_pos, 
		const string& new_sal, const unsigned int& new_jersey, const unsigned int& new_rookie): 
		player_name(new_name), team_name(new_team), player_pos(new_pos), salary_per_year(new_sal), 
		jersey_number(new_jersey), rookie_year(new_rookie){}

    //destructor
	~Player(){}

	//set name
	void set_player(const string& new_player){
		player_name = new_player;
	}

    //get player
	string get_player() const{
		return player_name;
	}

	//set team
	void set_team(const string& new_team){
		team_name = new_team;
	}

    //get team
	string get_team() const{
		return team_name;
	}

	//set position
	void set_pos(const string& new_pos){
		player_pos = new_pos;
	}

    //get position
	string get_pos() const{
		return player_pos;
	}

	//set salary
	void set_sal(const string& new_sal){
		salary_per_year = new_sal;
	}

	string get_sal() const{
		return salary_per_year;
	}

	//set jersery
	void set_jersey(const unsigned int& new_jersey){
		jersey_number = new_jersey;
	}

    //get jersey
	unsigned int get_jersey() const{
		return jersey_number;
	}

	//set rookie year
	void set_rookie(const unsigned int& new_rookie){
		rookie_year = new_rookie;
	}

    //get rookie
	unsigned int get_rookie() const{
		return rookie_year;
	}

};

//overloaded the << operator to display the player object with its underalying attributes
std::ostream& operator <<(std::ostream& outs, Player& tmp){
    outs << "Name: " << tmp.get_player() << endl
         << "Team: " << tmp.get_team() << endl
         << "Position: " << tmp.get_pos() << endl
         << "Salary: " << tmp.get_sal() << endl
         << "Jersey: " << tmp.get_jersey() << endl
         << "Rookie Year: " << tmp.get_rookie() << endl;
    return outs;
}
