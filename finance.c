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
                break;
            }
                
            }
        }

        
    }
}


int Property_Value_Assess(square assessing_square)
{
    int total_value = 0;

    total_value += (assessing_square.Cell_Data.Properties.Base_Price);
    total_value += (assessing_square.Cell_Data.Properties.House_Construction_Cost * assessing_square.Cell_Data.Properties.Number_of_Houses);
    total_value += (assessing_square.Cell_Data.Properties.Hotel_Construction_Cost * assessing_square.Cell_Data.Properties.Number_of_Hotels);

    return total_value;
}


void Insurance_Round_Check(square board[],int round_count)
{
    for(int i = 0; i < SQ_Board_Size; i++)
    {
        if(board[i].Cell_Type != SQ_Type_Property)
        {
            continue;
        }

        if((board[i].Insurance_Details.Package != Not_Insured) &&
            ((board[i].Insurance_Details.Expire_Round - 3) == round_count) &&
                (board[i].Insurance_Details.Expire_Round != 0))
        {
            printf("\nInsurance policy on %s expires in 3 rounds.\n",board[i].Square_Name);
        }
        else if((board[i].Insurance_Details.Package != Not_Insured) &&
                (board[i].Insurance_Details.Expire_Round == round_count) &&
                (board[i].Insurance_Details.Expire_Round != 0))
        {
            printf("\nInsurance policy on %s expired.\n",board[i].Square_Name);
            board[i].Insurance_Details.Package = Not_Insured;
            board[i].Insurance_Details.Expire_Round = 0;
        }
    }
}


void Insurance_Claims(square *claiming_cell,Players player_list[])
{

    Insurance_Packages cell_package = claiming_cell->Insurance_Details.Package;
    Players Owner_Prop;
    
    if(claiming_cell->Cell_Data.Properties.Property_Owner == Owner_Bank)
    {
        return;
    }
    else{
        Owner_Prop = player_list[claiming_cell->Cell_Data.Properties.Property_Owner];
    }

    switch (cell_package)
    {
    case Not_Insured:
    {
        return;
        break;
    }
        
    case Basic_Property_Insurance:
    {
        if((claiming_cell->Insurance_Details.Is_Claimed != true) &&
            (claiming_cell->Cell_Data.Properties.Property_Damages != No_Damage) &&
            ((claiming_cell->Cell_Data.Properties.Property_Damages == Fire_Damage) ||
                (claiming_cell->Cell_Data.Properties.Property_Damages == Flood_Damage)))
        {
            int Receiving_Amount = Round_Off((double)Property_Value_Assess((*claiming_cell)) * 0.8);
            player_list[Owner_Prop.Player_ID].Player_Cash += Receiving_Amount;
            claiming_cell->Insurance_Details.Is_Claimed = true;

            printf("Insurance Claim Approved.");
            printf("\n%s received LKR : %d as compensation on %s Insurance Claim.\n",Owner_Prop.Player_Name,Receiving_Amount,claiming_cell->Square_Name);
        }

        break;
    }

    case Comprehensive_Insurance:
    {
        if((claiming_cell->Insurance_Details.Is_Claimed != true) &&
            (claiming_cell->Cell_Data.Properties.Property_Damages != No_Damage))
        {
            int Receiving_Amount = Round_Off((double)Property_Value_Assess(*claiming_cell));
            player_list[Owner_Prop.Player_ID].Player_Cash += Receiving_Amount;
            claiming_cell->Insurance_Details.Is_Claimed = true;

            printf("Insurance Claim Approved.");
            printf("\n%s received LKR : %d as compensation on %s Insurance Claim.\n",Owner_Prop.Player_Name,Receiving_Amount,claiming_cell->Square_Name);
        }

        break;
    }

    case Business_Interruption_Insurance:
    {
        if((claiming_cell->Insurance_Details.Is_Claimed != true) &&
            (claiming_cell->Cell_Data.Properties.Property_Damages != No_Damage))
        {
            int Receiving_Amount = Round_Off((double)Property_Value_Assess(*claiming_cell) + (claiming_cell->Cell_Data.Properties.Base_Rental * 10 * 5));// 5rounds income hotels
            player_list[Owner_Prop.Player_ID].Player_Cash += Receiving_Amount;
            claiming_cell->Insurance_Details.Is_Claimed = true;

            printf("Insurance Claim Approved.");
            printf("\n%s received LKR : %d as compensation on %s Insurance Claim.\n",Owner_Prop.Player_Name,Receiving_Amount,claiming_cell->Square_Name);
        }

        break;
    }
    
    default:
        return;
    }

}