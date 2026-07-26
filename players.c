#include <stdio.h>
#include <string.h>
#include "types.h"

#define Total_Players 4



Players Player_List[Total_Players];


void Player_Initialization(void){

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

        for(int j = 0; j < 30; j++)
        {
            Player_List[i].Player_Owns[j] = SQ_None;

        }
    }

   // printf("%s\n",Player_List[1].Player_Name);
   // printf("%d\n",Player_List[1].Player_ID);
   // printf("%d\n",Player_List[1].Player_Owns[1]);
   // printf("%d\n",Player_List[1].Player_Cash);
   // printf("%d\n",Player_List[1].Player_Assets);
   // printf("%d\n",Player_List[1].Loan_status);
   // printf("%d\n",Player_List[1].Player_Position);

    
};