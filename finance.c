#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"


int Round_Off(double value)
{
    int Decimal_Removed = (int)value;
    double Decimal_Part = value - Decimal_Removed;

    if(Decimal_Part >= 0.5)
    {
        return (Decimal_Removed + 1);
    }
    else
    {
        return (Decimal_Removed);
    }
}