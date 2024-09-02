# Object Oriented NBA Player Database

The NBA Player Database project is designed to efficiently manage and retrieve player data using a C++ and Python-based system. The database is built using SQLite for persistent storage, ensuring that all player information is retained even after the application is closed. The system supports real-time data manipulation, allowing for dynamic updates and queries.

The project employs object-oriented programming (OOP) principles to create a modular and maintainable codebase, with over 3,000 lines of code refactored for readability and efficiency. Additionally, the database's functionality and reliability are rigorously validated using Google Unit Testing, covering over 20 key functions to ensure robustness and minimize runtime errors. This project highlights the integration of C++, Python, and SQLite to create a powerful tool for managing NBA player data.

## How to Run

To run this project, follow these steps:

1. **Clone the Repository:**
   - Clone the repository to your local machine using the following command:
     ```bash
     git clone https://github.com/Chenry513/Object-Oriented-NBA-Player-Database/tree/master
     ```

2. **Compile the Project:**
   - Navigate to the project directory and compile the 'final_project.cpp' file using the following g++ command:
     ```bash
     g++ -o final_project final_project.cpp -std=c++17 -lsqlite3 -I.
     ```

3. **Run the Application:**
   - Start the application by running the following command:
     ```bash
     ./final_project
     ```
By following these steps, you will be able to set up and run the Netflix Recommendation System on your local machine.

## Technologies Used

- **C++**: For developing the core functionalities and implementing object-oriented programming principles.
- **SQLite3**: To manage and persist player data across sessions.
- **Google Unit Testing**: To ensure the reliability and accuracy of the database functionalities.
- **g++**: For compiling the C++ code with appropriate flags and libraries.

