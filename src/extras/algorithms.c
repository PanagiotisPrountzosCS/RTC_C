#include "extras/algorithms.h"

#include <math.h>
#include <stdlib.h>

int clamp(float value, float min, float max) {
    if (value < min) {
        return (int)ceil(min);
    } else if (value > max) {
        return (int)ceil(max);
    } else {
        return (int)ceil(value);
    }
}

int int_len(int n) {
    if (n == 0) return 1;
    return floor(log10(abs(n))) + 1;
}