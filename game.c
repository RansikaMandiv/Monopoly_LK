#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"



Dice_Type Dice_Roll(void)
{
    Dice_Type returning_values;
    returning_values.Dice_Sum = 0;
    returning_values.Is_Double = false;

    int Dice_1 = (rand() % 6 + 1);
    int Dice_2 = (rand() % 6 + 1);

    if(Dice_1 == Dice_2)
    {
        returning_values.Is_Double = true;
    }

    returning_values.Dice_Sum = Dice_1 + Dice_2;

    return returning_values;
}


void Sort_Players(Players player_list[])
{
    Players temp;

    for(int i = 0; i < Total_Players; i++)
    {
        for(int j = 0; j < Total_Players - 1; j++)
        {
            if((player_list[j].Player_Roll_Order == false) &&
                (player_list[j].Temp_Dice_Value < player_list[j + 1].Temp_Dice_Value))
            {
                temp = player_list[j];
                player_list[j] = player_list[j + 1];
                player_list[j + 1] = temp;

            }
        }
    }
}


void Round_Counter(Players player_list[],short *Round_Count,square board[],Auction *auction_status,short final_order[],Economic econ_status,int *loan_interest)
{

    int Active_Passed_Go = 0;
    int Active_Players = 0;

    for(int i = 0; i < Total_Players; i++)
    {
        if(player_list[i].Is_Bankrupt != Bankrupt)
        {
            Active_Players++;
            if(player_list[i].Player_Passed_Go == Passed_Go)
            {
                Active_Passed_Go++;
            }
        }
    }

    if(Active_Players != 0 && Active_Passed_Go == Active_Players)
    {
        (*Round_Count)++;

        for (int i = 0; i < Total_Players; i++)
        {
            player_list[i].Previous_Data.Player_Previous_Round = (*Round_Count) - 1;
        }

        Inflation_Rate_Calculator(&econ_status,board,(*Round_Count),loan_interest);

    
        //Printing Round Summary
        

        printf("=============================================\nRound %d Summary\n=============================================",(*Round_Count));
        
        for(int i = 0; i < Total_Players; i++)
        {

            if(player_list[i].Is_Bankrupt == Bankrupt)
            {
                continue;
            }

            Player_Status Status_of_Players = Player_Assessing(player_list,board,i,auction_status,final_order,econ_status);

            printf("\n%s\n",player_list[i].Player_Name);
            printf("\nCash : LKR %d\n",player_list[i].Player_Cash);
            printf("\nNet Worth : LKR %d\n",Status_of_Players.Net_Worth);
            printf("\nProperties : %d\n",Status_of_Players.Total_No_Prop_Owned);
            printf("\nHotels : %d\n",Status_of_Players.No_of_Hotels);
            printf("\nOutstanding Loan : LKR %d\n",Status_of_Players.Outstanding_Loan);
            printf("\n---------------------------------------------\n");
        }
       
        for (int i = 0; i < Total_Players; i++)
        {
        
            player_list[i].Player_Passed_Go = Not_Passed;
           
        }
    }

}


void Player_Moves(Players player_list[],int Player_Id_Input,Dice_Type Dice_Values)
{
    int Old_Position = player_list[Player_Id_Input].Player_Position;

    player_list[Player_Id_Input].Temp_Dice_Value = Dice_Values.Dice_Sum;
    player_list[Player_Id_Input].Player_Position = (player_list[Player_Id_Input].Player_Position + player_list[Player_Id_Input].Temp_Dice_Value) % SQ_Board_Size;
    player_list[Player_Id_Input].Total_Dice_Value += player_list[Player_Id_Input].Temp_Dice_Value;
    printf("\n%s Rolls: %d Player Moves to: %d\n",player_list[Player_Id_Input].Player_Name,player_list[Player_Id_Input].Temp_Dice_Value,player_list[Player_Id_Input].Player_Position);

    if((Old_Position + player_list[Player_Id_Input].Temp_Dice_Value) >= SQ_Board_Size)
    {
        player_list[Player_Id_Input].Player_Passed_Go = Passed_Go;
        player_list[Player_Id_Input].Player_Cash += 2000;
        printf("\n%s has Passed Go.\nCollected LKR 2,000.\nCurrent Balance LKR : %d \n",player_list[Player_Id_Input].Player_Name,player_list[Player_Id_Input].Player_Cash);
            
    }
    
}


//Determining Player Order//

void Determine_Order(Players player_list[])
{
    int Ordered_Players = 0;
    int Tie_Count = 0;

    while(Ordered_Players < Total_Players)
    {
        for(int i = 0; i < Total_Players; i++)
        {
            if(player_list[i].Player_Roll_Order == false)
            {
                player_list[i].Temp_Dice_Value = Dice_Roll().Dice_Sum;
                printf("\n%s rolls %d.\n",player_list[i].Player_Name,player_list[i].Temp_Dice_Value);
            }
        }

        Sort_Players(player_list);

        for(int i = 0; i < Total_Players; i++)
        {
            Tie_Count = 0;

            if(player_list[i].Player_Roll_Order == false)
            {
                for(int j = 0; j < Total_Players; j++)
                {
                    if((player_list[j].Player_Roll_Order == false) &&
                        (player_list[i].Temp_Dice_Value == player_list[j].Temp_Dice_Value))
                    {
                        Tie_Count++;
                    }
                }
            }

            if (Tie_Count > 1)
            {
                player_list[i].Player_Roll_Order = false;
            }
            else{
                player_list[i].Player_Roll_Order = true;
            }
        }

        Ordered_Players = 0;
        for(int i = 0; i < Total_Players; i++)
        {
            if(player_list[i].Player_Roll_Order == true)
            {
                Ordered_Players++;
            }
        }
    }
}   
      

void Start_Game(void)
{

short Round_Count = 0;
int Turn_Count = 0;
Economic Economy_Status = Normal;
Government_Regulations Cureent_Gov_Regulations = Housing_Subsidy;
double Income_Tax_Rate = 0.15;
Auction Auction_Status = None;
int Game_Winner = -1;
int Loan_Interest_Rate = 8;
int Drawn_National_Card = 0;


square Board[SQ_Board_Size];
Board_Initialization(Board);

Players Player_List[Total_Players];
Player_Initialization(Player_List);


//Determining Player Turning Orders//

short Final_Order[Total_Players];

///Printing the Opening

printf("=============================================\nMONOPOLY-LK Simulation\n=============================================\n");
printf("\nPlayer 1 : Aggressive Investor\n");
printf("Player 2 : Conservative Banker\n");
printf("Player 3 : Risk Taker\n");
printf("Player 4 : Opportunistic Trader\n");
printf("\nEach player begins with LKR 30,000.\n");



Determine_Order(Player_List);

printf("\n%s will begin the game.\n",Player_List[0].Player_Name);
printf("\nTurn Order");

for (int i = 0; i < Total_Players; i++)
{
    Final_Order[i] = Player_List[i].Player_ID;
    printf("\n%s.\n",Player_List[i].Player_Name);
}



//Resetting Temp Dice Values

{
    for (int i = 0; i < Total_Players; i++)
    {
        Player_List[i].Temp_Dice_Value = 0;
    }
}
//

    
while((Round_Count < 500) && 
        (!Game_Over_Check(Player_List,Board,&Auction_Status,Final_Order,Economy_Status,&Game_Winner)))
{
    if(Game_Over_Check(Player_List,Board,&Auction_Status,Final_Order,Economy_Status,&Game_Winner))
    {
        break;
    }

    
    for(int i = 0; i < Total_Players; i++)
    {
        int Id_Input = Final_Order[i];

        Dice_Type Dice_Values = Dice_Roll();

        int Can_Move = Player_In_Jail(Player_List,Id_Input,&Turn_Count,Dice_Values);

        if(Player_List[Id_Input].Is_Bankrupt == Bankrupt)
        {
            continue;
        }

        if(Can_Move)
        {
            Player_Moves(Player_List,Id_Input,Dice_Values);
        }
      
        Round_Counter(Player_List,&Round_Count,Board,&Auction_Status,Final_Order,Economy_Status,&Loan_Interest_Rate);

        Auction_Status = Player_Buys_Property(Player_List,Board,Id_Input,Economy_Status);

        Property_Auctions(Player_List,Board,Id_Input,Auction_Status,Final_Order,&Board[SQ_GO],Economy_Status);
        
        Player_Pays_Rent(Player_List,Board,Id_Input,&Auction_Status,Final_Order,Economy_Status);

        Player_Pays_Tax(Player_List,Board,Id_Input,Income_Tax_Rate);

        Player_Monopoly_Count(Player_List,Board); 
        
        Player_Builds(Player_List,Board,Id_Input,Economy_Status,Cureent_Gov_Regulations);

        Player_Obtains_Loans(Player_List,Board,Id_Input,Loan_Interest_Rate,Round_Count,&Auction_Status,Economy_Status,Final_Order);

        National_Event_Cards(Board,Player_List,Id_Input,&Drawn_National_Card,Round_Count,&Economy_Status);

        National_Event_Card_Reset(Board,Player_List,Id_Input,Round_Count);
        
    }
    Turn_Count++;
   // printf("%d",Turn_Count);

}

if(Game_Winner < 0)
{
    Game_Winner = 0;
    for(int i = 0; i < Total_Players; i++)
    {
        if(Player_List[i].Is_Bankrupt != Bankrupt)
        {
            Game_Winner = i;
            break;
        }
    }
}

printf("\n=============================================\n");
printf("\nGame Over\n");
printf("\nWinner\n%s\nTotal Cash\nLKR %d\n",Player_List[Game_Winner].Player_Name,Player_List[Game_Winner].Player_Cash);
printf("\nTotal Property Value\nLKR %d\n",Player_List[Game_Winner].Player_Assets);
printf("\nOutstanding Loans\n%d\n",Player_List[Game_Winner].Player_Loan_Amount);
printf("\nNet Worth\nLKR %d\n",Player_Assessing(Player_List,Board,Game_Winner,&Auction_Status,Final_Order,Economy_Status).Net_Worth);
}






