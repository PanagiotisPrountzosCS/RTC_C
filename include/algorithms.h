#ifndef ALGORITHMS_H
#define ALGORITHMS_H

// clamps value between min and max
int clamp(float value, float min, float max);

// returns the length of an integer as a string
int int_len(int n);

static inline float absolute(float n){
    return n < 0 ? -n : n;
}

#endif