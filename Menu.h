#include <iostream>     
#include <fstream>      
#include <string>       
#include <algorithm>    
#include <cassert>  
#include <cctype>
#include "Database.h"

using namespace std;

class Menu {
    string selection; // user input variable
    Database data;    // Database object
    string name,team,pos,sal;
    int jersey, rook;
public:

    //Displaying the main menu and prompts user to enter a valid option
    void input() {

        do{
            cout   <<  "\n\n----------------------------------- \n"<<
                        "Welcome to the NBA Player Database! \n" <<
                        "----------------------------------- \n\n" <<
                        "Select an option from the following: \n" <<
                        "(A)dd a Player.\n" <<
                        "(F)ind a Player.\n" <<
                        "(D)elete a Player.\n" <<
                        "(L)ist Players.\n" <<
                        "(Q)uit\n\n";
            
            cout << "Enter the letter of your choice: ";
            cin >> selection;
            for(int i = 0; i < selection.size(); i++)
                selection[i] = tolower(selection[i]);

            bool one_input = true;
            while(one_input){
                if(selection.length() != 1){
                    cout << "Invalid input. Please enter one character: ";
                    cin >> selection;
                   for(int i = 0; i < selection.size(); i++)
                        selection[i] = tolower(selection[i]);
                } else if(selection.length() == 1){
                    one_input = false;
                }
            }
            char sel = selection[0];
            switch (sel){
                case 'a':
                    add_player();
                    break;
               
                case 'f':
                    find_player();
                    break;
                
                case 'd':
                    delete_player();
                    break;
               
                case 'l':
                    list_player();
                    break;
                
                case 'q':
                    cout << "\nThanks for using The NBA Player Database! Goodbye..\n";
                    exit(-1);
                    break;
                
                default:
                    cout << "\nBad choice! Please try again.\n";
            }
        } while (true);
            
    }

    // Menu option to add a player
    void add_player(){
         
        cout << "\n            Add a player\n"
            << "----------------------------------- \n\n" 
            << "Enter the following players information:\n" 
            << "Player name: ";
        getline(cin,name);
        getline(cin,name);
        cout <<"Team: ";
        getline(cin,team);
        cout << "Position: ";
        getline(cin,pos);
        cout << "Salary: ";
        getline (cin,sal);
        cout << "Jersey: ";
        cin >> jersey;
        cout << "rookie year: ";
        cin >> rook;

        // promting the user to enter a valid input for jersery and rookie year
        bool too_large = true;
        while(too_large){
            if(rook <= 1955 || rook >= 2021){
            cout << "\nPlease enter a valid rookie year: ";
                cin >> rook;
            }

            if(jersey < 0 || jersey >= 100 ){
                cout << "\nPlease enter a valid jersery number: ";
                cin >> jersey;
            }
            
            if((rook >= 1955 && rook <= 2021) && (jersey > 0 && jersey <= 100)){
                too_large = false;
            }
        }

        // appending the user-prompted player to the database
        Player a(name,team,pos,sal,jersey,rook);
        data.append(a);

        cout << "\nNew Player has been added.";

    }

    // menue option to find a player by searching by key strings/ints
    void find_player(){
        do{
            cout   <<  "\n            Find a player\n" <<
                        "----------------------------------- \n\n" <<
                        "Select an option from the following: \n" <<
                        "(N)ame of Player.\n" <<
                        "(T)eam of Player.\n" <<
                        "(P)osition of Player.\n" <<
                        "(S)alary of Player.\n" <<
                        "(J)ersey of Player.\n" <<
                        "(Y)ear rookie of Player.\n" <<
                        "\n(R)eturn to main menu\n\n";

            cout << "Enter the letter of your choice: ";
            cin >> selection;
            for(int i = 0; i < selection.size(); i++)
                selection[i] = tolower(selection[i]);

            bool one_input = true;
            while(one_input){
                if(selection.length() != 1){
                    cout << "Invalid input. Please enter one character: ";
                    cin >> selection;
                   for(int i = 0; i < selection.size(); i++)
                        selection[i] = tolower(selection[i]);
                } else if(selection.length() == 1){
                    one_input = false;
                }
            }
            char sel = selection[0];
            switch (sel){
                case 'n':
                    cout<<"Enter the name of your Player: ";
                    getline(cin, name);
                    getline(cin, name);
                    data.search_playersub(name);
                    break;

                case 't':
                    cout<<"Enter your Player's team: ";
                    getline(cin, team);
                    getline(cin, team);
                    data.search_teamsub(team);
                    break;

                case 'p':
                    cout<<"Enter the position of your Player: ";
                    getline(cin, pos);
                    getline(cin, pos);
                    data.search_pos(pos);
                    break;

                case 's':
                    cout<<"Enter your Player's salary ex.(32m): ";
                    getline(cin, sal);
                    getline(cin, sal);
                    data.searchsalsub(sal);
                    break;

                case 'j':
                    char choice;
                    cout<<"Select an option from the following: \n" 
                    <<"(N)umber range search.\n"
                    <<"(O)ne number search.\n";

                    cout << "Enter the letter of your choice: ";
                    cin>>choice;
                    choice = tolower(choice);
                    if(choice == 'n'){
                        int num1;
                        int num2;
                        cout<<"Enter the first jersey number: ";
                        cin>>num1;
                        cout<<"\nEnter the second jersey number: ";
                        cin>>num2;
                        data.search_range_jersey(num1,num2);
                    }
                    if(choice == 'o'){
                        int num;
                        cout<<"Enter your jersey number: ";
                        cin>>num;
                        data.search_jersey(num);
                    }
                    break;

                case 'y':
                    char choicey;
                    cout<<"Select an option from the following: \n" 
                    <<"(N)umber range search.\n"
                    <<"(O)ne number search.\n";

                    cout << "Enter the letter of your choice: ";
                    cin>>choicey;
                    choice = tolower(choicey);
                    if(choice == 'n'){
                        int numy1;
                        int numy2;

                        cout<<"Enter the first rookie year: ";
                        cin>>numy1;
                        if(numy1<1955 || numy1 >= 2021){
                            cout<<"Enter a proper number: ";
                            cin>>numy1;
                        }

                        cout<<"\nEnter the second rookie year: ";
                        cin>>numy2;
                        if(numy2<1955 || numy2 >= 2021){
                            cout<<"Enter a proper number: ";
                            cin>>numy2;
                        }
                        data.search_range_rookie(numy1,numy2);

                    }

                    else if(choice == 'o'){
                        int numy;
                        cout<<"Enter your rookie year: ";
                        cin>>numy;
                        if(numy<1955 || numy >= 2021){
                            cout<<"Enter a proper number: ";
                            cin>>numy;
                        }
                        data.search_rookie(numy);
                    }

                    break;

                case 'r':
                    input();
                    break;

                default:
                    cout << "\nBad choice! Please try again.\n";
            }
        } while (true);
    }

    // menue option to find a delete by searching by key strings/ints
    void delete_player(){
        do{
            cout   <<  "\n            Delete a player\n" <<
                        "----------------------------------- \n\n" <<
                        "Select an option from the following: \n" <<
                        "(N)ame of Player.\n" <<
                        "(T)eam of Player.\n" <<
                        "(P)osition of Player.\n" <<
                        "(S)alary of Player.\n" <<
                        "(J)ersey of Player.\n" <<
                        "(Y)ear rookie of Player.\n" <<
                        "\n(R)eturn to main menu\n\n";

            cout << "Enter the letter of your choice: ";
            cin >> selection;
            for(int i = 0; i < selection.size(); i++)
                selection[i] = tolower(selection[i]);

            bool one_input = true;
            while(one_input){
                if(selection.length() != 1){
                    cout << "Invalid input. Please enter one character: ";
                    cin >> selection;
                   for(int i = 0; i < selection.size(); i++)
                        selection[i] = tolower(selection[i]);
                } else if(selection.length() == 1){
                    one_input = false;
                }
            }
            char sel = selection[0];
            switch (sel){
                case 'n':
                    cout<<"Enter the name of your Player you want deleted: ";
                    getline(cin, name);
                    getline(cin, name);
                    data.remove_playersub(name);
                    cout<<"\nPlayer removed.\n";
                    
                    break;

                case 't':
                    cout<<"Enter your Player's team you want deleted: ";
                    getline(cin, team);
                    getline(cin, team);
                    data.remove_teamsub(team);
                    cout<<"\nPlayers on this team removed.\n";

                    break;

                case 'p':
                    cout<<"Enter the position of your Player you want deleted: ";
                    getline(cin, pos);
                    getline(cin, pos);
                    data.remove_possub(pos);
                    cout<<"\nPlayers that play this position removed.\n";
                    
                    break;

                case 's':
                    cout<<"Enter the salary of the Player you want deleted: ";
                    getline(cin, sal);
                    getline(cin, sal);
                    data.remove_salsub(sal);
                    cout<<"\nPlayers that make this salary removed.\n";
                    
                    break;

                case 'j':
                    char choice;
                    cout<<"Select an option from the following: \n" 
                    <<"(N)umber range delete.\n"
                    <<"(O)ne number delete.\n";

                    cout << "Enter the letter of your choice: ";
                    cin>>choice;
                    choice = tolower(choice);
                    if(choice == 'n'){
                        int num1;
                        int num2;

                        cout<<"Enter the first jersey number: ";
                        cin>>num1;
                        if(num1<0 || num1 >= 100){
                            cout<<"Enter a proper number: ";
                            cin>>num1;
                        }

                        cout<<"\nEnter the second jersey number: ";
                        cin>>num2;
                        if(num2<0 || num2 >= 100){
                            cout<<"Enter a proper number: ";
                            cin>>num2;
                        }
                        data.remove_jerseyran(num1,num2);
                        cout << "Players with this jersey range have been deleted.\n";
                    }
                    else if(choice == 'o'){
                        int num;
                        cout<<"Enter your jersey number: ";
                        cin>>num;
                        if(num<0 || num >= 100){
                            cout<<"Enter a proper number: ";
                            cin>>num;
                        }
                        data.remove_jersey(num);
                        cout << "Players with this jersey have been deleted.\n";
                    }             
                    break;

                case 'y':
                    char choicey;
                    cout<<"Select an option from the following: \n" 
                    <<"(N)umber range delete.\n"
                    <<"(O)ne number delete.\n";

                    cout << "Enter the letter of your choice: ";
                    cin>>choicey;
                    choice = tolower(choicey);
                    if(choice == 'n'){
                        int numy1;
                        int numy2;

                        cout<<"Enter the first rookie year: ";
                        cin>>numy1;
                        if(numy1<1955 || numy1 >= 2021){
                            cout<<"Enter a proper number: ";
                            cin>>numy1;
                        }

                        cout<<"\nEnter the second rookie year: ";
                        cin>>numy2;
                        if(numy2<1955 || numy2 >= 2021){
                            cout<<"Enter a proper number: ";
                            cin>>numy2;
                        }
                        data.remove_rookieran(numy1,numy2);

                        cout << "Players with this rookie year range have been deleted.\n";

                    }

                    else if(choice == 'o'){
                        int numy;
                        cout<<"Enter your rookie year: ";
                        cin>>numy;
                        if(numy<1955 || numy >= 2021){
                            cout<<"Enter a proper number: ";
                            cin>>numy;
                        }
                        data.remove_rookie(numy);
                        cout << "Players with this rookie year have been deleted.\n";
                    }

                    break;

                case 'r':
                    input();
                    break;

                default:
                    cout << "\nBad choice! Please try again.\n";
            }
        } while (true);
    }


    // menue option to list out the sorted players accoridng to the option prompted by the menue
    void list_player(){
        do{
            cout   <<  "\n            List Players\n" <<
                        "----------------------------------- \n\n" <<
                        "Select an option from the following: \n" <<
                        "(A) Sort names by alphabetical order.\n" <<
                        "(B) Sort names by reverse alphabetical order.\n" <<
                        "(C) Sort teams by alphabetical order.\n" <<
                        "(D) Sort teams by reverse alphabetical order.\n" <<
                        "(E) Sort player positions by alphabetical order.\n" <<
                        "(F) Sort player positions by reverse alphabetical order.\n" <<
                        "(G) Sort Salary by alphabetical order.\n" <<
                        "(H) Sort Salary by reverse alphabetical order.\n" <<
                        "(I) Sort Jersey by ascending order.\n" <<
                        "(J) Sort Jersey by descending order.\n" <<
                        "(K) Sort rookie years by ascending order.\n" <<
                        "(L) Sort rookie years by descending order.\n" <<
                        "\n(R)eturn to main menu\n\n";

             cout << "Enter the letter of your choice: ";
            cin >> selection;
            for(int i = 0; i < selection.size(); i++)
                selection[i] = tolower(selection[i]);

            bool one_input = true;
            while(one_input){
                if(selection.length() != 1){
                    cout << "Invalid input. please enter one character: ";
                    cin >> selection;
                   for(int i = 0; i < selection.size(); i++)
                        selection[i] = tolower(selection[i]);
                } else if(selection.length() == 1){
                    one_input = false;
                }
            }
            char sel = selection[0];
            switch (sel){
                case 'a':
                    data.sort_name();
                    data.display_all();
                    break;

                case 'b':
                    data.sort_name_rev();
                    data.display_all();
                    break;
                
                case 'c':
                    data.sort_team();
                    data.display_all();
                    break;
                
                case 'd':
                    data.sort_team_rev();
                    data.display_all();
                    break;
                
                case 'e':
                    data.sort_pos();
                    data.display_all();
                    break;
                
                case 'f':
                    data.sort_pos_rev();
                    data.display_all();
                    break;
                
                case 'g':
                    data.sort_salary();
                    data.display_all();
                    break;
                
                case 'h':
                    data.sort_salary_rev();
                    data.display_all();
                    break;
                
                case 'i':
                    data.sort_jersey();
                    data.display_all();
                    break;
                
                case 'j':
                    data.sort_jersey_rev();
                    data.display_all();
                    break;

                case 'k':
                    data.sort_rookie_year();
                    data.display_all();
                    break;
                
                case 'l':
                    data.sort_rookie_rev();
                    data.display_all();
                    break;
                
                case 'r':
                    input();
                    break;
                default:
                    cout << "\nBad choice! Please try again later.\n";
            }
        } while (true);
    }
    
    //destructor
    ~Menu(){}

};


