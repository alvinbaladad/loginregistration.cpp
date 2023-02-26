// Create a registration function that stores usernames and passwords.


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>

bool checkDatabase(std::string& usernameRef, std::string& passwordRef, int choice){
    std::ifstream database; // Open a read stream
    database.open ("database.txt");
    std::string line;
    while (std::getline(database, line))
    {
        std::stringstream ss(line);
        std::string word;
        char del{':'};
        int x{0};
        bool usernameCheck{false};
        bool passwordCheck{false};

        while (!ss.eof()) {
            std::getline(ss, word, del);

            ++x; // Keep count of data lines

        // Login
            // usernameCheck and passwordCheck must both be true
            //
            // using std::cout, data flow will be:
            // username
            // password
            if (choice == 1){
                if ((x % 2 == 1) && (word == usernameRef)){
                    usernameCheck = true;
                }
                else if ((x % 2 == 1) && (word != usernameRef)){
                    usernameCheck = false;
                }
                if ((x % 2 == 0) && (word == passwordRef)){
                    passwordCheck = true;
                }
                else if ((x % 2 == 0) && (word != passwordRef)){
                    passwordCheck = false;
                }
                if ((usernameCheck == true && passwordCheck == true)){
                    database.close();
                    return true;
                }
            }

        // Register
            // usernameRef is preset to false, any hit will trigger true
            if (choice == 2){
                if ((x % 2 == 1) && (word == usernameRef)){
                    database.close();
                    return true;
                }
                
            }
        }
    }
    return false; // explicity return false for both login and register
}

void writeDatabase(std::string& usernameRef, std::string& passwordRef, int choice){
    if ((checkDatabase(usernameRef, passwordRef, choice) == false)){
        std::ofstream database; // Open a write stream
        database.open ("database.txt", std::ios_base::app); // std::ios_base::app is appending to the file
        database << usernameRef << ':' << passwordRef << std::endl;
        database.close();
        std::cout << "Username: " << usernameRef << " registered!\n";
    }
    else if ((checkDatabase(usernameRef, passwordRef, choice) == true)){
        std::cout << "Username: " << usernameRef << " is already taken!\n";
    }
}

void introText(){
    // Introduction text
    std::cout << std::endl << "Login/Register\n\n";
    std::cout << "Would you like to login or register as a new user?\n";
    std::cout << "1) Login\n";
    std::cout << "2) Register\n";
    std::cout << "3) Quit\n\n";
    std::cout << "Enter: ";
}

std::string inputUsername(){
    std::string username{};
    std::cout << "Enter a username: ";
    std::cin >> username;
    return username;
}

std::string inputPassword(){
    std::string password{};
    std::cout << "Enter a password: ";
    std::cin >> password;
    return password;
}

int loginUser(std::string& usernameRef, std::string& passwordRef){
    usernameRef = inputUsername();
    passwordRef = inputPassword();
    int choice {1};
    if ((checkDatabase(usernameRef, passwordRef, choice)) == true){
        std::cout << "Successful login as user: " << usernameRef;
    }
    else{
        std::cout << "Invalid login: " << usernameRef << "\nIncorrect password or username does not exist.\n";
    }
    return 0;
}

int registerUser(std::string& usernameRef, std::string& passwordRef){
    usernameRef = inputUsername();
    passwordRef = inputPassword();
    int choice {2};
    writeDatabase(usernameRef, passwordRef, choice);
    return 0;

}

int main(){
    std::string username{};
    std::string password{};
    std::string& usernameRef{username};
    std::string& passwordRef{password};

    while(true){
        introText();
        char userSelection{};
        std::cin >> userSelection;
        if (userSelection == '1'){
            loginUser(usernameRef, passwordRef);
        }
        else if (userSelection == '2'){
            registerUser(usernameRef, passwordRef);
        }
        else if (userSelection == '3'){
            break;
        }
        else{
            std::cout << "**Invalid selection, try again.**\n\n";
        }
    }
    
    return 0;
}