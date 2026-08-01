#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"



int Dice_Roll(void)
{
    
    int Dice_1 = (rand() % 6 + 1);
    int Dice_2 = (rand() % 6 + 1);

    return (Dice_1 + Dice_2);
};


int Round_Counter(Players Player_List[],short *Round_Count)
{
    for (int i = 0; i < Total_Players; i++)
    {
        if(Player_List[i].Total_Dice_Value > 39)
        {
            Player_List[i].Player_Passed_Go = Passed_Go;
            Player_List[i].Total_Dice_Value = (Player_List[i].Total_Dice_Value) % (SQ_Board_Size);
        }
    }

    if((Player_List[Aggressive_Investor].Player_Passed_Go == Passed_Go) && (Player_List[Opportunistic_Trader].Player_Passed_Go == Passed_Go) && (Player_List[Risk_Taker].Player_Passed_Go == Passed_Go) && (Player_List[Conservative_Banker].Player_Passed_Go == Passed_Go))
    {
        (*Round_Count)++;
       
        for (int i = 0; i < Total_Players; i++)
        {
        
            Player_List[i].Player_Passed_Go = Not_Passed;
           
        }
    }

}



void Player_Moves(Players Player_List[],int Player_Id_Input)
{

    Player_List[Player_Id_Input].Temp_Dice_Value = Dice_Roll();
    Player_List[Player_Id_Input].Player_Position = (Player_List[Player_Id_Input].Player_Position + Player_List[Player_Id_Input].Temp_Dice_Value) % 39;
    Player_List[Player_Id_Input].Total_Dice_Value += Player_List[Player_Id_Input].Temp_Dice_Value;
    printf("\n%s Rolls: %d Player Moves to: %d\n",Player_List[Player_Id_Input].Player_Name,Player_List[Player_Id_Input].Temp_Dice_Value,Player_List[Player_Id_Input].Player_Position);
    
}


//Determining Player Order//

void Determine_Order(Players Players_Arr[],int No_Of_Players)
{
    int Tie_Found;

    do{
        Tie_Found = 0;

        Players* Sorted_Ptrs[Total_Players];
        for (int i = 0; i < Total_Players; i++)
        {
            Sorted_Ptrs[i] = &Players_Arr[i];
        }

        for (int i = 0; i < Total_Players - 1; i++)
        {
            for (int j = 0; j < Total_Players -i -1; j++)
            {
                if (Sorted_Ptrs[j]->Temp_Dice_Value < Sorted_Ptrs[j+1]->Temp_Dice_Value)
                {
                    Players* Temp = Sorted_Ptrs[j];
                    Sorted_Ptrs[j] = Sorted_Ptrs[j+1];
                    Sorted_Ptrs[j + 1] = Temp; 
                }
            }
        }

        for (int i = 0; i < Total_Players - 1; i++)
        {
            if (Sorted_Ptrs[i]->Temp_Dice_Value == Sorted_Ptrs[i + 1]->Temp_Dice_Value)
            {
                Tie_Found = 1;

                int Tied_Value = Sorted_Ptrs[i]->Temp_Dice_Value;
                printf("\n[Tie Detected] Players Tied with a Roll of %d are Re Rolling\n",Tied_Value);

                for (int j = 0; j < Total_Players; j++)
                {
                    if (Players_Arr[j].Temp_Dice_Value == Tied_Value)
                    {
                        Players_Arr[j].Temp_Dice_Value = Dice_Roll();
                        printf("Player %s Re-Rolled and got: %d\n",Players_Arr[j].Player_Name,Players_Arr[j].Temp_Dice_Value);
                    }
                }
                break;
            }
        }

        if (!Tie_Found)
        {
            for(int rank = 0; rank < Total_Players; rank++)
            {
                Sorted_Ptrs[rank]->Player_Roll_Order = rank;
            }
        }
    }while (Tie_Found);


}



void Start_Game(void)
{

short Round_Count = 0;
int Turn_Count = 0;

square Board[SQ_Board_Size];
Board_Initialization(Board);

Players Player_List[Total_Players];
Player_Initialization(Player_List);

//Determining Player Turning Orders//

short Final_Order[Total_Players];
int count = 0;

for (int i = 0; i < Total_Players; i++)
{
    Player_List[i].Temp_Dice_Value = Dice_Roll();
    printf("\n%s Rolled:\t%d\n",Player_List[i].Player_Name,Player_List[i].Temp_Dice_Value);
}

Determine_Order(Player_List, Total_Players);

for (int i = 0; i < Total_Players; i++)
{
    printf("\nFinal Player Roll Order is:\n%s:\t%d\n",Player_List[i].Player_Name,Player_List[i].Player_Roll_Order);

   for (int j = 0; j < Total_Players; j++)
    {
        if (i == Player_List[j].Player_Roll_Order)
        {
            Final_Order[i] = Player_List[j].Player_ID;
        }
    }

}

printf("\nFinal Order is:\t\n");
for (int j = 0; j < Total_Players; j++) 
{
    printf("\n%d Position is %s\n",j+1,Player_List[Final_Order[j]].Player_Name);
}

//Resetting Temp Dice Values

{
    for (int i = 0; i < Total_Players; i++)
    {
        Player_List[i].Temp_Dice_Value = 0;
    }
}
//

    
while(Round_Count < 5)
{
    

    for(int i = 0; i < Total_Players; i++)
    {
        int Id_Input = Final_Order[i];
        Player_Moves(Player_List,Id_Input);
        
        Round_Counter(Player_List,&Round_Count);
        
    }
    Turn_Count++;
    printf("%d",Turn_Count);

}
}

int Player_Buys_Property(Players Player_List[])
{
    
}




