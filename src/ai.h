#ifndef AI_H
#define AI_H

extern bool debug;

namespace ai
{
    void append_move(const char move);
    void update_biases();
    int predict();
}

#endif