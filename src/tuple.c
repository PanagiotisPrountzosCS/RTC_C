#include "tuple.h"

bool isPoint(Tuple t) { return t.w == 1.0; }

bool isVector(Tuple t) { return t.w == 0.0; }