#include <iostream>
#include <chrono>
#include <string>
#include <algorithm>
#include <cctype>
#include <thread>
#include <random>

#include "ai.h"

std::string input()
{
    std::string inp_str;
    char ch;
    while (std::cin.get(ch) && ch != '\n') {
        inp_str += ch;
    }
    return inp_str;
}

char choice3 (std::string _choice1, std::string _choice2, std::string _choice3)
{
    // renders the prompt text with the choices
    std::cout << "   1) " << _choice1 + ", 2) " << _choice2 + ", 3) " << _choice3 << std::endl;

    // user input
    std::string picked;

    std::cout << " > " << std::flush;
    picked = input();

    // if input is within the choices then exit loop
    if(picked[0] == '1' || picked[0] == '2' || picked[0] == '3') {
        return picked[0];
    } else {
        choice3(_choice1, _choice2, _choice3);
    }

    return '0';
}

char choice2 (std::string _choice1, std::string _choice2)
{
    // renders the prompt text with the choices
    std::cout << "   1) " << _choice1 + ", 2) " << _choice2 << std::endl;

    // user input
    std::string picked;

    std::cout << " > " << std::flush;
    picked = input();

    // if input is within the choices then exit loop
    if(picked[0] == '1' || picked[0] == '2') {
        return picked[0];
    } else {
        choice2(_choice1, _choice2);
    }

    return '0';
}

// prints a rock ascii art and prints the name
void print_rock()
{
    std::cout << "    _______\n";
    std::cout << "---'   ____)\n";
    std::cout << "      (_____)\n";
    std::cout << "      (_____)\n";
    std::cout << "      (____)\n";
    std::cout << "---.__(___)\n";
    std::cout << "\nRock" << std::endl;
}

// prints a paper ascii art and prints the name
void print_paper()
{
    std::cout << "    _______\n";
    std::cout << "---'   ____)____\n";
    std::cout << "          ______)\n";
    std::cout << "          _______)\n";
    std::cout << "         _______)\n";
    std::cout << "---.__________)\n";
    std::cout << "\nPaper" << std::endl;
}

// prints a scissors ascii art and prints the name
void print_scissors()
{
    std::cout << "    _______\n";
    std::cout << "---'   ____)____\n";
    std::cout << "          ______)\n";
    std::cout << "       __________)\n";
    std::cout << "      (____)\n";
    std::cout << "---.__(___)\n";
    std::cout << "\nScissors" << std::endl;
}

void wait (int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void round()
{
    char choice = choice3 ("Rock", "Paper", "Scissors");
    std::cout << "You chose" << std::endl;

    // user plays
    if (choice == '1')
    {   
        print_rock();  
    }
    else if (choice == '2')
    {
        print_paper();
    }
    else
    {
        print_scissors();
    }

    if (!debug)
    {
        wait(1000);
    }

    std::cout << "\nYour opponent chose\n" << std::endl;

    if (!debug)
    {
        wait(750);
    }
    
    // ai plays
    int num = ai::predict();
    if (num == 0)
    {
        print_rock();
    }
    else if (num == 1)
    {
        print_paper();
    }
    else if (num == 2)
    {
        print_scissors();
    }
    
    ai::append_move(choice);
    ai::update_biases();

    if (!debug)
    {
        wait(1000);
    }
    std::cout << std::endl;

    // rock - rock
    if (choice == '1' && num == 0)
    {
        std::cout << "Tie" << std::endl;
    }
    // paper - rock
    else if (choice == '2' && num == 0)
    {
        std::cout << "You Win" << std::endl;
    }
    // scissors - rock
    else if (choice == '3' && num == 0)
    {
        std::cout << "You Lost" << std::endl;
    }
    // rock - paper
    else if (choice == '1' && num == 1)
    {
        std::cout << "You Lost" << std::endl;
    }
    // paper - paper
    else if (choice == '2' && num == 1)
    {
        std::cout << "Tie" << std::endl;
    }
    // scissors - paper
    else if (choice == '3' && num == 1)
    {
        std::cout << "You Win" << std::endl;
    }
    // rock - scissors
    else if (choice == '1' && num == 2)
    {
        std::cout << "You Win" << std::endl;
    }
    // paper - scissors
    else if (choice == '2' && num == 2)
    {
        std::cout << "You Lost" << std::endl;
    }
    // scissors - scissors
    else if (choice == '3' && num == 2)
    {
        std::cout << "Tie" << std::endl;
    }
    // unexpected result
    else
    {
        std::cout << "Undetermined" << std::endl;
    }
}

int main()
{
    // start
    std::cout << "do you want to enable debug mode?" << std::endl;
    char choice = choice2("Yes", "No");

    // yes
    if (choice == '1')
    {
        debug = true;
    }
    // no
    else
    {
        debug = false;
    }
    // init
    ai::update_biases();

    // game loop
    while (true)
    {
        srand(time(NULL));
        round();
    }
    
}