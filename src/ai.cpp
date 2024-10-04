#include <string>
#include <iostream>
#include <vector>
#include <random>

#include "ai.h"


bool debug;

namespace ai
{
    float biases[3];
    const char options[3] = {'1', '2', '3'};
    std::string moves = "123123";

    float decide_with_biases()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::discrete_distribution<> dist(&biases[0], &biases[2]);

        int index = dist(gen);
        return options[index];
    }

    float bias_calculator (const char move)
    {
        int count = 0;
        for (size_t i = 0; i < moves.length(); i++)
        {
            if (moves[i] == move)
            {
                count++;
            }
        }
        return float(count) / float(moves.length());
    }

    

    void append_move (const char move)
    {
        moves.push_back(move);
        return;
    }
    
    void update_biases()
    {
        biases[0] = bias_calculator('1');
        biases[1] = bias_calculator('2');
        biases[2] = bias_calculator('3');
    }

    int find_counter (const char move)
    {
        // rock
        if (move == '1')
        {
            return 1; // paper
        }
        // paper
        else if (move == '2')
        {
            return 2; // scissors
        }
        // scissors
        else if (move == '3')
        {
            return 0; // rock
        }
        return -1;
    }

    int predict()
    {
        // find last character in memory
        char temp = moves[moves.length()-1];
        moves.pop_back();
        size_t pos = moves.rfind(temp);
        moves.push_back(temp);

        // if move is not repeating
        if (pos+1 < moves.length())
        {
            if (debug)
            {
                std::cout << "biases: rock (" << biases[0] << "), paper (" << biases[1] << "), scissors (" << biases[2] << ")" << std::endl;
            }
            
            std::cout << std::flush;

            // chose between pattern and bias
            if (rand() % 2 == 0)
            {
                // play by bias
                if (debug)
                {
                    std::cout << "playing with bias" << std::endl;
                }
                return find_counter(decide_with_biases());
            }
            else
            {
                // play by pattern
                if (debug)
                {
                    std::cout << "playing with pattern" << std::endl;
                }
                return find_counter(moves[pos+1]);
            }
        } 
        // if move is repeating
        else
        {
            if (debug)
            {
                std::cout << "biases: rock (" << biases[0] << "), paper (" << biases[1] << "), scissors (" << biases[2] << ")" << std::endl;
            }

            std::cout << std::flush;

            if (rand() % 2 == 0)
            {
                // play by bias
                if (debug)
                {
                    std::cout << "playing with bias" << std::endl;
                }
                return find_counter(decide_with_biases());
            }
            else
            {
                // play by pattern
                if (debug)
                {
                    std::cout << "playing with pattern" << std::endl;
                }
                return find_counter(moves[pos]);
            }
        }
    }
} 
