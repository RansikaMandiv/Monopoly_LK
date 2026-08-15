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


void Inflation_Rate_Calculator(Economic *economic_status,square board[],int round_count,int * loan_interest)
{
  
    if((round_count % 10) == 0)
    {
        int Inflation_Rates[6] = {-3,0,2,5,8,12};

        double Rate_For_Round = ((double)(100 + Inflation_Rates[(rand() % 6)]) / 100);

        printf("\nInflation Rate for The Round: %.2f\n",Rate_For_Round);
    

        if(Rate_For_Round > 100.00)
        {
            (*economic_status) = Inflation;
        }
        else{
            (*economic_status) = Deflation;
        }

        (*loan_interest) = Round_Off((double)(*loan_interest) * Rate_For_Round);

        for(int i = 0; i < SQ_Board_Size; i++)
        {
            switch (board[i].Cell_Type)
            {
            case SQ_Type_Property:
            {
                board[i].Cell_Data.Properties.Base_Price = Round_Off((double)board[i].Cell_Data.Properties.Base_Price * Rate_For_Round);
                board[i].Cell_Data.Properties.Base_Rental = Round_Off((double)board[i].Cell_Data.Properties.Base_Rental * Rate_For_Round);
                board[i].Cell_Data.Properties.House_Construction_Cost = Round_Off((double)board[i].Cell_Data.Properties.House_Construction_Cost * Rate_For_Round);
                board[i].Cell_Data.Properties.Hotel_Construction_Cost = Round_Off((double)board[i].Cell_Data.Properties.Hotel_Construction_Cost * Rate_For_Round);
                break;
            }

            case SQ_Type_Railway:
            {
                board[i].Cell_Data.Railway.Base_Price = Round_Off((double)board[i].Cell_Data.Railway.Base_Price * Rate_For_Round);
                board[i].Cell_Data.Railway.Base_Rental = Round_Off((double)board[i].Cell_Data.Railway.Base_Rental * Rate_For_Round);

                break;
            }
            
            
            case SQ_Type_Utility:
            {
                board[i].Cell_Data.Utility.Base_Price = Round_Off((double)board[i].Cell_Data.Utility.Base_Price * Rate_For_Round);
                break;
            }

            default:
            {
                return;
            }
                
            }
        }

        
    }
}


