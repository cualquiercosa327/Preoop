#pragma once

#include <stdlib.h>

#define object typedef struct

#define initCall(a) init_ ## a(malloc(sizeof(a)))
#define new(a) initCall(a)

#define method(a, b, ...) b##_ ##a(a *self, ##__VA_ARGS__)
#define invoke(a, b, ...) objects(a, b)(a, ##__VA_ARGS__)