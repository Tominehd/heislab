#include "globalvar.h"


// Er bare mulig å ha 10 ordere Håper at dette kan korte ned kjøretiden litt
static int ordersMatrix[10][2] = {{9,9},
                                  {9,9},
                                  {9,9},
                                  {9,9},
                                  {9,9},
                                  {9,9},
                                  {9,9},
                                  {9,9},
                                  {9,9},
                                  {9,9},
};

static int lastFloor = 0;

int static isDoorOpen = 0;
