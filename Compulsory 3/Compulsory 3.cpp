#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <cctype>
#include <limits>

#include <conio.h>
#include <ctype.h>

#include <vector>
#include <iomanip>
#include <fstream>

const int M = 6 /*Must be smaller than 100*/, N = 6 /*Must be smaller than 27*/;
const char BLANK = '~'; //I changed BLANK to '~' instead of ' ', because it looks more fancy. This can easily be changed back
const char SHIP = 'S';
const char MISS = 'M';
const char HIT = 'H';


std::string NewPassword()
{
    std::string inputPassword = "A";
    std::string newPassword;
    int inputPosX{0};
    int inputPosY{0};
    int confirmedPassword{0}; // 0 = player has not yet confirmed the new password; 1 = New password has been set but not yet confirmed twice; 2 = Password and new password has been confirmed
    
    //"\u001b[96m" + text + "\u001b[0m";
    char letter;
    while(confirmedPassword < 2)
    {
        system("cls");
        std::cout << "Please enter a new password!\n\n(Navigate using WASD or the arrow keys)\nPress Enter to confrim\n\n";

        for (int i = 0; i < 4; i++)
        {

            for (int j = 0; j < 4; j++)
            {
                letter = 4 * i + j + 65;
                if (inputPosY == i && inputPosX == j)
                {
                    std::string tempString(1, letter);
                    std::cout << "|" << "\u001b[96m" + tempString + "\u001b[0m";
                }
                else
                {
                    std::cout << "|" << letter;
                }
            }
            std::cout << "|\n";
        }

        if(confirmedPassword == 0)
        {
            std::cout << "\nNew password:     ";
            for (int i = 0; i < inputPassword.length(); i++)
            {
                std::cout << "*";
            }
        }
        else 
        {
            std::cout << "\nNew password:     ";
            for (int i = 0; i < newPassword.length(); i++)
            {
                std::cout << "*";
            }
            std::cout << "\nConfirm password: ";
            for (int i = 0; i < inputPassword.length(); i++)
            {
                std::cout << "*";
            }
        }

        //Get arrow key or letter
        int input = _getch();
        if(input == 224)
        {
            input = _getch();
        }

        switch (input)
        {
        case 'w': case 'W': case 72: //Up
            if(inputPosY != 0)
            {
                inputPosY--;
                inputPassword += 4 * inputPosY + inputPosX + 65;
            }
            break;

        case 'a': case 'A': case 75://Left
            if (inputPosX != 0)
            {
                inputPosX--;
                inputPassword += 4 * inputPosY + inputPosX + 65;
            }
            break;

        case 's': case 'S': case 80://Down
            if (inputPosY != 3)
            {
                inputPosY++;
                inputPassword += 4 * inputPosY + inputPosX + 65;
            }
            break;

        case 'd': case 'D': case 77://Right
            if(inputPosX != 3)
            {
                inputPosX++;
                inputPassword += 4 * inputPosY + inputPosX + 65;
            }
            break;

        case 13: //Enter
            if(confirmedPassword == 0)
            {
                newPassword = inputPassword;
                inputPassword.clear();
                inputPassword = "A";
                inputPosX = 0;
                inputPosY = 0;
                confirmedPassword = 1;
            }
            else if(confirmedPassword == 1)
            {
                if(inputPassword == newPassword)
                {
                    //Wrong Password
                    confirmedPassword = 2;
                }
                else 
                {
                    //Wrong password
                    newPassword.clear();
                    inputPassword.clear();
                    inputPassword = "A";
                    inputPosX = 0;
                    inputPosY = 0;
                    confirmedPassword = 0;
                }
            }
            break;

        default:
            break;
        }
    }
    return (newPassword);
}

void ChangePassword()
{
    std::fstream passwordOverWriteFile("Password.txt", std::ios::out);
    passwordOverWriteFile << NewPassword();
    passwordOverWriteFile.close();
}

void EnterPassword(std::string password)
{
    std::string inputPassword = "A";
    int passwordAttempts{0};
    const int maxPasswordAttempts{ 3 };
    int inputPosX{ 0 };
    int inputPosY{ 0 };
    bool correctPassword{ false };
    

    //"\u001b[96m" + text + "\u001b[0m";
    char letter;
    while (!correctPassword)
    {
        system("cls");
        std::cout << "Please enter your password to log in!\nYou have "<< maxPasswordAttempts - passwordAttempts << " attempts left\n\n(Navigate using WASD or the arrow keys)\nPress Enter to confrim\n\n";

        for (int i = 0; i < 4; i++)
        {

            for (int j = 0; j < 4; j++)
            {
                letter = 4 * i + j + 65;
                if (inputPosY == i && inputPosX == j)
                {
                    std::string tempString(1, letter);
                    std::cout << "|" << "\u001b[96m" + tempString + "\u001b[0m";
                }
                else
                {
                    std::cout << "|" << letter;
                }
            }
            std::cout << "|\n";
        }

        std::cout << "\npassword:     ";
        for (int i = 0; i < inputPassword.length(); i++)
        {
            std::cout << "*";
        }

        //Get arrow key or letter
        int input = _getch();
        if (input == 224)
        {
            input = _getch();
        }

        switch (input)
        {
        case 'w': case 'W': case 72: //Up
            if (inputPosY != 0)
            {
                inputPosY--;
                inputPassword += 4 * inputPosY + inputPosX + 65;
            }
            break;

        case 'a': case 'A': case 75://Left
            if (inputPosX != 0)
            {
                inputPosX--;
                inputPassword += 4 * inputPosY + inputPosX + 65;
            }
            break;

        case 's': case 'S': case 80://Down
            if (inputPosY != 3)
            {
                inputPosY++;
                inputPassword += 4 * inputPosY + inputPosX + 65;
            }
            break;

        case 'd': case 'D': case 77://Right
            if (inputPosX != 3)
            {
                inputPosX++;
                inputPassword += 4 * inputPosY + inputPosX + 65;
            }
            break;

        case 13: //Enter
            if (inputPassword == password)
            {
                //Correct password
                correctPassword = true;
            }
            else
            {
                //Wrong password
                passwordAttempts++;
                inputPassword.clear();
                inputPassword = "A";
                inputPosX = 0;
                inputPosY = 0;

                if(passwordAttempts >= maxPasswordAttempts)
                {
                    system("cls");
                    std::cout << "You are out of attempts!\nThis program will now stop\n\n";
                    exit(0);
                }
            }
            break;

        default:
            break;
        }
    }
}

void Login()
{
    system("cls");
    std::string password;
    std::fstream passwordFile("Password.txt", std::ios::in);
    passwordFile >> password;

    if (password == "")
    {
        ChangePassword();
    }
    else 
    {
        std::cout << "You must enter password!"; 
        EnterPassword(password);
    }
    passwordFile.close();
}

//////////////////////////////////////////////////////
int randomRow(int to, int from)
{
    int row;
    row = rand() % to + from;
    return(row);
}

int randomColumn(int to, int from)
{
    int column;
    column = rand() % to + from;
    return(column);
}

int letterToNumber(char letter) //Only big letters
{
    return (static_cast<int>(letter) - 65);
}

void printAIBoard(char board[M][N])
{
    for (int i = 0; i < M; i++)
    {
        std::cout << M - i;
        //Extra Space
        if (M - i < 10)
        {
            std::cout << " ";
        }
        //Prints grid
        for (int j = 0; j < N; j++)
        {

            std::cout << "|";
            if(board[i][j] == HIT)
            {
                std::string text;
                text += board[i][j];
                std::cout << "\u001b[91m" + text + "\u001b[0m";
            }
            else if(board[i][j] == MISS)
            {
                std::string text;
                text += board[i][j];
                std::cout << "\u001b[96m" + text + "\u001b[0m";
            }
            else 
            {
                std::cout << board[i][j];
            }
        }
        std::cout << "|\n";
    }

    
    std::cout << "  ";
    //Prints "----------..."
    for (int i = 0; i < N; i++)
    {
        std::cout << "--";
    }
    std::cout << "-\n";
}

void printPlayerBoard(char board[M][N])
{
    for (int i = 0; i < M; i++)
    {
        std::cout << M - i;
        //Extra Space
        if (M - i < 10)
        {
            std::cout << " ";
        }
        //Prints grid
        for (int j = 0; j < N; j++)
        {

            std::cout << "|";
            if (board[i][j] == HIT)
            {
                std::string text;
                text += board[i][j];
                std::cout << "\u001b[91m" + text + "\u001b[0m";
            }
            else if (board[i][j] == MISS)
            {
                std::string text;
                text += board[i][j];
                std::cout << "\u001b[96m" + text + "\u001b[0m";
            }
            else
            {
                std::cout << board[i][j];
            }
        }
        std::cout << "|\n";
    }


    std::cout << "  ";
    //Prints "----------..."
    for (int i = 0; i < N; i++)
    {
        std::cout << "--";
    }
    std::cout << "-\n";


    std::cout << "  ";
    //Prints "|A|B|C|D|E|..."
    for (int i = 0; i < N; i++)
    {
        char letter = i + 65;
        std::cout << "|" << letter;
    }
    std::cout << "|\n";
}

void printBoard(bool ships[M][N])
{
    for (int i = 0; i < M; i++)
    {
        std::cout << M - i;
        //Extra Space
        if (M - i < 10)
        {
            std::cout << " ";
        }
        //Prints grid
        for(int j = 0; j < N; j++)
        {
            std::cout << "|";
            if(ships[i][j] == true)
            {
                std::cout << SHIP;
            }
            else { std::cout << " "; }
        }
        std::cout << "|\n";
    }


    std::cout << "  ";
    //Prints "----------..."
    for(int i = 0; i < N; i++)
    {
        std::cout << "--";
    }
    std::cout << "-\n";

    std::cout << "  ";
    //Prints "|A|B|C|D|E|..."
    for(int i = 0; i < N; i++)
    {
        char letter = i + 65;
        std::cout << "|" << letter;
    }
    std::cout << "|\n";
}

void makeBoard(bool ships[M][N], int numberOfShips)
{
    for (int i = 0; i < numberOfShips; i++)
    {
        int row;
        int colum;
        do
        {
            row = randomRow(M, 0);
            colum = randomColumn(N, 0);
        } while (ships[row][colum] == true);

        ships[row][colum] = true;
    }
}

void makeBoard3(bool ships[M][N], int numberOfShips)
{
    for (int i = 0; i < numberOfShips; i++)
    {
        int row;
        int colum;
        int direction = rand() % 2 + 1;
        if(direction == 2) //Vertical Ship
        {
            do
            {
                row = randomRow((M - 2), 1);
                colum = randomColumn((N - 1), 0);
            } while (ships[row - 1][colum] == true || ships[row][colum] == true || ships[row + 1][colum] == true);

            ships[row - 1][colum] = true;
            ships[row][colum] = true;
            ships[row + 1][colum] = true;
        }
        else //Horizontal Ship
        {
            do
            {
                row = randomRow((M - 1),0);
                colum = randomColumn((N - 2), 1);
            } while (ships[row][colum - 1] == true || ships[row][colum] == true || ships[row][colum + 1] == true);

            ships[row][colum - 1] = true;
            ships[row][colum] = true;
            ships[row][colum + 1] = true;
        }
    }
}

//Could've made the code work without making this as a seperate function. So I'm only doing it this way sine it's


void makeEmptyBoard(char board[M][N], bool ships[M][N])
{ 
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            board[i][j] = BLANK;
            ships[i][j] = false;
        }
    }
}

void shoot(char board[M][N], bool ships[M][N], int &numberOfShots, int &numberOfHits)
{
    char column;
    int row;
    std::cout << "Where would you like to shoot ('A3', etc.)?\nInput: ";
    std::cin >> column; std::cin >> row;

    column = toupper(column);
    int columnInt = letterToNumber(column);

    while(std::cin.fail() || row > M || row <= 0 || columnInt >= N || columnInt < 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nInvalid input, try typing something like 'A3' instead\nInput: ";
        std::cin >> column; std::cin >> row;
        column = toupper(column);
        columnInt = letterToNumber(column);
    }


    if(board[M- row][columnInt] == BLANK)
    {
        if(ships[M- row][columnInt] == true)
        {
            board[M- row][columnInt] = HIT;
            numberOfHits++;
        }
        else
        {
            board[M- row][columnInt] = MISS;
        }
    }
    numberOfShots++;
    //Stops the player from typing "A2B3C1" which would've been counted as three rapid shots
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void shootAI()
{

}

void Play()
{
    bool ships[M][N];
    char board[M][N]; //2D array with M rows and N columns
    int numberOfHits{ 0 }; //How many times the player has hit a ship
    int numberOfShots{ 0 }; //How many shots the player has used

    const int amountOfShips{ 3 }; //How many ships there are on the field 
    const int amountOfShots{ amountOfShips*3 + ((M*N - amountOfShips * 3)/3) }; //How many shots the player has available

    makeEmptyBoard(board, ships);
    makeBoard3(ships, amountOfShips);

    //makeBoard(ships, amountOfShips);
    //printBoard(ships);

    std::cout << std::endl;
    system("cls");
    std::cout << "Ammo: " << amountOfShots - numberOfShots << std::endl;
    printPlayerBoard(board);
    do
    {
        std::cout << "\n";
        shoot(board, ships, numberOfShots, numberOfHits);
        system("cls");
        std::cout << "Ammo: " << amountOfShots - numberOfShots << std::endl;
        printPlayerBoard(board);
    } while (numberOfShots < amountOfShots && numberOfHits < amountOfShips*3); //IMPORTANT: This only works when you run makeBoard3 and not makeBoard. Simply change "amountOfShips*3" to "amountOfShips" to make it work

    if(numberOfHits >= amountOfShips * 3)//IMPORTANT: This only works when you run makeBoard3 and not makeBoard. Simply change "amountOfShips*3" to "amountOfShips" to make it work
    {
        std::cout << "\nYou won! You shot down all the ships!\n";
    } 
    else
    {
        std::cout << "\nYou lost! You are out of shots!\n";
    }
    _getch();
}

void Play2()
{
    bool ships[M][N];
    bool shipsAI[M][N];
    char board[M][N]; //2D array with M rows and N columns
    char boardAI[M][M];
    int numberOfHits{ 0 }; //How many times the player has hit a ship
    int numberOfHitsAI{ 0 };
    int numberOfShots{ 0 }; //How many shots the player has used
    int numberOfShotsAI{ 0 };

    const int amountOfShips{ 3 }; //How many ships there are on the field 
    const int amountOfShots{ amountOfShips * 3 + ((M * N - amountOfShips * 3) / 3) }; //How many shots the player has available

    makeEmptyBoard(board, ships);
    makeEmptyBoard(boardAI, ships);
    makeBoard3(ships, amountOfShips);
    makeBoard3(shipsAI, amountOfShips);


    std::cout << std::endl;
    system("cls");
    std::cout << "       AI\n    Ammo: " << amountOfShots - numberOfShotsAI<<std::endl;
    printAIBoard(boardAI);
    std::cout << "     Player\n    Ammo: " << amountOfShots - numberOfShots << std::endl;
    printPlayerBoard(board);

    //Game Loop
    do
    {
        std::cout << "\n";
        shoot(board, ships, numberOfShots, numberOfHits);
        system("cls");
        std::cout << "       AI\n    Ammo: " << amountOfShots - numberOfShotsAI << std::endl;
        printAIBoard(boardAI);
        std::cout << "     Player\n    Ammo: " << amountOfShots - numberOfShots << std::endl;
        printPlayerBoard(board);
    } while (numberOfShots < amountOfShots && numberOfHits < amountOfShips * 3); //IMPORTANT: This only works when you run makeBoard3 and not makeBoard. Simply change "amountOfShips*3" to "amountOfShips" to make it work

    if (numberOfHits >= amountOfShips * 3)//IMPORTANT: This only works when you run makeBoard3 and not makeBoard. Simply change "amountOfShips*3" to "amountOfShips" to make it work
    {
        std::cout << "\nYou won! You shot down all the ships!\n";
    }
    else
    {
        std::cout << "\nYou lost! You are out of shots!\n";
    }
    _getch();
}

void Menu()
{
    system("cls");
    int userInput;;
    std::cout << "\n     |BATTLESHIPS|\n\n";
    std::cout << " 1: Change the password\n 2: Play battleship\n 3: Quit\n\n";
    std::cout << " Select an option (1-3): ";

    do
    {
        std::cin >> userInput;
        switch (userInput)
        {
        case 1:
            ChangePassword();
            break;
        case 2:
            Play();
            break;
        case 3:
            exit(0);
        default:
            break;
        }
    } while (userInput <= 0 && userInput > 3);
}



int main()
{
    Login();
    
    srand(time(NULL));
    //Play2();
    while (true)
    {
        Menu();
    }
}