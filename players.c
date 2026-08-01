#include <stdio.h>
#include <string.h>
#include "types.h"








void Player_Initialization(Players Player_List[]){

    const char* Default_Names[] = {

        "Aggressive Investor",
        "Conservative Banker",
        "Risk Taker",
        "Opportunistic Trader"
    };

    for(int i = 0; i < Total_Players; i++)
    {
        strncpy(Player_List[i].Player_Name,Default_Names[i], sizeof(Player_List[i].Player_Name) - 1);
        Player_List[i].Player_ID = (Player_Type)i;
        Player_List[i].Player_Cash = 30000;
        Player_List[i].Player_Assets = 0;
        Player_List[i].Loan_status = No_Loans;
        Player_List[i].Player_Position = SQ_GO;
        Player_List[i].Player_Roll_Order = -1;
        Player_List[i].Temp_Dice_Value = 0;
        Player_List[i].Total_Dice_Value = 0;
        Player_List[i].Is_Bankrupt = Not_Bankrupt;
        Player_List[i].Jail_Status = Not_In_Jail;
        Player_List[i].Player_Passed_Go = Not_Passed;

        for(int j = 0; j < 30; j++)
        {
            Player_List[i].Player_Owns[j] = SQ_None;

        }
    }

  
    
};

void Player_Models(Players Player_List[],int Player_Id)
{

}