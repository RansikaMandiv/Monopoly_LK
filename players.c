#include <stdio.h>
#include <string.h>
#include "types.h"

void Player_Initialization(Players Player_List[])
{

    const char *Default_Names[] = {

        "Aggressive Investor",
        "Conservative Banker",
        "Risk Taker",
        "Opportunistic Trader"};

    for (int i = 0; i < Total_Players; i++)
    {
        strncpy(Player_List[i].Player_Name, Default_Names[i], sizeof(Player_List[i].Player_Name) - 1);
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

        for (int j = 0; j < 9; j++)
        {
            Player_List[i].Has_Partial_Monopoly[j] = None;
            Player_List[i].Has_Monopoly[j] = None;
        }
    }
};


Player_Buy Player_Buys_Property(Players player_list[], square board[], int player_id,Economic economic_status)
{
    Player_Choice Willing_to_Buy = No;
    Property_Group_Type Prioritized = None;
    int Current_Pos = player_list[player_id].Player_Position;
    Square_type Prop_Type = board[Current_Pos].Cell_Type;

    if (Prop_Type == SQ_Type_Property || Prop_Type == SQ_Type_Railway || Prop_Type == SQ_Type_Utility)
    {
        switch (Prop_Type)
        {
        case SQ_Type_Property:
        {
            switch (player_id)
            {
            case Aggressive_Investor:
            {
                int Max_Rent = 0;
                int Cash_Reserve = player_list[player_id].Player_Cash - board[Current_Pos].Cell_Data.Properties.Base_Price;

                for (int i = 0; i < SQ_Board_Size; i++)
                {
                    if ((board[i].Cell_Type == SQ_Type_Property) &&
                        (board[i].Cell_Data.Properties.Property_Owner != player_id) &&
                        (board[i].Cell_Data.Properties.Property_Owner != Owner_Bank))
                    {
                        if (board[i].Cell_Data.Properties.Base_Rental > Max_Rent)
                        {
                            Max_Rent = board[i].Cell_Data.Properties.Base_Rental;
                        }
                    }
                }

                if(((board[Current_Pos].Location_ID == SQ_Galle_Face) || (board[Current_Pos].Location_ID == SQ_Nuwara_Eliya)) &&
                    (board[Current_Pos].Cell_Data.Properties.Property_Owner == Owner_Bank) &&
                    (Max_Rent < Cash_Reserve))
                    {
                        Willing_to_Buy = Yes;
                        Prioritized = board[Current_Pos].Cell_Data.Properties.Group;
                        break;
                    }

                if ((player_list[player_id].Has_Partial_Monopoly[0] == None) &&
                    (board[Current_Pos].Cell_Data.Properties.Property_Owner == Owner_Bank) &&
                    (Max_Rent < Cash_Reserve))
                {
                    Willing_to_Buy = Yes;
                    Prioritized = board[Current_Pos].Cell_Data.Properties.Group;
                }
                else
                {

                    for (int i = 0; i < 9; i++)
                    {
                        if ((Max_Rent < Cash_Reserve) &&
                            (player_list[player_id].Has_Partial_Monopoly[i] != None) &&
                                (board[Current_Pos].Cell_Data.Properties.Property_Owner == Owner_Bank))
                        {

                            Prioritized = player_list[player_id].Has_Partial_Monopoly[i];
                            Willing_to_Buy = Yes;
                            break;
                        }
                    }
                }

                break;
            }

            case Conservative_Banker:
            {
                int Maximum_Spendable_Cash = (player_list[player_id].Player_Cash / 2);

                

                if((board[Current_Pos].Cell_Data.Properties.Base_Price < Maximum_Spendable_Cash) &&
                 (board[Current_Pos].Cell_Data.Properties.Property_Owner == Owner_Bank) &&
                    (economic_status != Recession))
                {
                    Prioritized = board[Current_Pos].Cell_Data.Properties.Group;
                    Willing_to_Buy = Yes;
                }
                break;
            }

            case Risk_Taker:
            {
                if((player_list[player_id].Player_Cash > board[Current_Pos].Cell_Data.Properties.Base_Price) && 
                (board[Current_Pos].Cell_Data.Properties.Property_Owner == Owner_Bank))
                {
                    Prioritized = board[Current_Pos].Cell_Data.Properties.Group;
                    Willing_to_Buy = Yes;
                }
                break;
            }

            case Opportunistic_Trader:
            {
                //calculating possible income for next 20 rounds assuming player builds a hotel right after buying
                int Possible_Income = (board[Current_Pos].Cell_Data.Properties.Base_Rental * 10 * Probability_Of_Landing * Total_Players * 20);
                int Possible_Expense = (board[Current_Pos].Cell_Data.Properties.Base_Price + (board[Current_Pos].Cell_Data.Properties.House_Construction_Cost * 4) + board[Current_Pos].Cell_Data.Properties.Hotel_Construction_Cost);
                if((Possible_Income > Possible_Expense) &&
                 (board[Current_Pos].Cell_Data.Properties.Property_Owner == Owner_Bank) &&
                    (player_list[player_id].Player_Cash > board[Current_Pos].Cell_Data.Properties.Base_Price))
                {
                    Prioritized = board[Current_Pos].Cell_Data.Properties.Group;
                    Willing_to_Buy = Yes;
                }
                break;
            }
            }
            break;
        }

        case SQ_Type_Railway:
        {
            switch (player_id)
            {
            case Aggressive_Investor:
            {
                int Max_Rent = 0;
                int Cash_Reserve = player_list[player_id].Player_Cash - board[Current_Pos].Cell_Data.Railway.Base_Price;

                for (int i = 0; i < SQ_Board_Size; i++)
                {
                    if ((board[i].Cell_Type == SQ_Type_Property) &&
                        (board[i].Cell_Data.Properties.Property_Owner != player_id) &&
                        (board[i].Cell_Data.Properties.Property_Owner != Owner_Bank))
                    {
                        if (board[i].Cell_Data.Properties.Base_Rental > Max_Rent)
                        {
                            Max_Rent = board[i].Cell_Data.Properties.Base_Rental;
                        }
                    }
                }

                if((player_list[player_id].Player_Cash > board[Current_Pos].Cell_Data.Railway.Base_Price) &&
                 (board[Current_Pos].Cell_Data.Railway.Railway_Owner == Owner_Bank) &&
                    (Max_Rent < Cash_Reserve))
                {
                    Willing_to_Buy = Yes;
                    Prioritized = Other;
                }
            
                break;
            }

            case Conservative_Banker:
            {
                int Maximum_Spendable_Cash = (player_list[player_id].Player_Cash / 2);

                if((board[Current_Pos].Cell_Data.Railway.Base_Price < Maximum_Spendable_Cash) &&
                    (board[Current_Pos].Cell_Data.Railway.Railway_Owner == Owner_Bank) &&
                    (economic_status != Recession))
                {
                    Willing_to_Buy = Yes;
                    Prioritized = Other;
                }
                
                break;
            }
            
            case Risk_Taker:
            {
                if((player_list[player_id].Player_Cash > board[Current_Pos].Cell_Data.Railway.Base_Price) &&
                 (board[Current_Pos].Cell_Data.Railway.Railway_Owner == Owner_Bank))
                {
                    Willing_to_Buy = Yes;
                    Prioritized = Other;
                }
                
                break;
            }

            
            case Opportunistic_Trader:
            {
                //calculating average rental income of train station for 20 rounds to evaluate ROI
                int Possible_Income = board[Current_Pos].Cell_Data.Railway.Base_Rental * Total_Players * Probability_Of_Landing * 20;
                int Possible_Expense = board[Current_Pos].Cell_Data.Railway.Base_Price;

                if((Possible_Income > Possible_Expense) &&
                    (player_list[player_id].Player_Cash > board[Current_Pos].Cell_Data.Railway.Base_Price) &&
                    (board[Current_Pos].Cell_Data.Railway.Railway_Owner == Owner_Bank))
                {
                    Willing_to_Buy = Yes;
                    Prioritized = Other;
                }
                break;
            }
            }

            break;
        }

        case SQ_Type_Utility:
        {
            switch (player_id)
            {
            case Aggressive_Investor:
            {
                int Max_Rent = 0;
                int Cash_Reserve = player_list[player_id].Player_Cash - board[Current_Pos].Cell_Data.Utility.Base_Price;

                for (int i = 0; i < SQ_Board_Size; i++)
                {
                    if ((board[i].Cell_Type == SQ_Type_Property) &&
                        (board[i].Cell_Data.Properties.Property_Owner != player_id) &&
                        (board[i].Cell_Data.Properties.Property_Owner != Owner_Bank))
                    {
                        if (board[i].Cell_Data.Properties.Base_Rental > Max_Rent)
                        {
                            Max_Rent = board[i].Cell_Data.Properties.Base_Rental;
                        }
                    }
                }

                if((player_list[player_id].Player_Cash > board[Current_Pos].Cell_Data.Utility.Base_Price) &&
                 (board[Current_Pos].Cell_Data.Utility.Company_Owner == Owner_Bank) &&
                    (Max_Rent < Cash_Reserve))
                {
                    Willing_to_Buy = Yes;
                    Prioritized = Other;
                }
                break;
            }

            case Conservative_Banker:
            {
                int Maximum_Spendable_Cash = (player_list[player_id].Player_Cash / 2);
                
                if((Maximum_Spendable_Cash > board[Current_Pos].Cell_Data.Utility.Base_Price) &&
                    (board[Current_Pos].Cell_Data.Utility.Company_Owner == Owner_Bank) &&
                    (economic_status != Recession))
                {
                    Willing_to_Buy = Yes;
                    Prioritized = Other;
                }
                break;
            }

            case Risk_Taker:
            {
                if((player_list[player_id].Player_Cash > board[Current_Pos].Cell_Data.Utility.Base_Price) &&
                    (board[Current_Pos].Cell_Data.Utility.Company_Owner == Owner_Bank))
                {
                    Willing_to_Buy = Yes;
                    Prioritized = Other;
                }
                break;
                
            }

            case Opportunistic_Trader:
            {
                 //calculating average rental income of utility for 50 rounds to evaluate ROI assuming players lands on have maximum dice value
                int Possible_Income = 4 * 12 * Total_Players * Probability_Of_Landing * 50;
                int Possible_Expense = board[Current_Pos].Cell_Data.Utility.Base_Price;

                if((Possible_Income > Possible_Expense &&
                    board[Current_Pos].Cell_Data.Utility.Company_Owner == Owner_Bank) &&
                    player_list[player_id].Player_Cash > board[Current_Pos].Cell_Data.Utility.Base_Price)
                {
                    Willing_to_Buy = Yes;
                    Prioritized = Other;
                }
                break;
                
            }
            
            }
            break;
        }

        break;
        }
    }
    else{
        return Couldnt_Buy; // To say it aint a propert or something that players could buy
    }



    switch (Prop_Type)
    {
    case SQ_Type_Property:
    {
        if((Willing_to_Buy == Yes) && 
        (Prioritized != None))
        {
           // printf("Owner Previous: %d",board[Current_Pos].Cell_Data.Properties.Property_Owner);
        player_list[player_id].Player_Cash -= board[Current_Pos].Cell_Data.Properties.Base_Price;
        board[Current_Pos].Cell_Data.Properties.Property_Owner = player_id;
           //  printf("Owner Previous: %d",board[Current_Pos].Cell_Data.Properties.Property_Owner);
        printf("\n%s Purchased %s for LKR %d.\nRemaining Balance : %d\n",player_list[player_id].Player_Name,board[Current_Pos].Square_Name,board[Current_Pos].Cell_Data.Properties.Base_Price,player_list[player_id].Player_Cash);
        
        return Bought;
        }

        return Didnt_Buy;
        break;
    }

    case SQ_Type_Railway:
    {
        if((Willing_to_Buy == Yes) && 
        (Prioritized != None))
        {
        player_list[player_id].Player_Cash -= board[Current_Pos].Cell_Data.Railway.Base_Price;
        board[Current_Pos].Cell_Data.Railway.Railway_Owner = player_id;
        printf("\n%s Purchased %s for LKR %d.\nRemaining Balance : %d\n",player_list[player_id].Player_Name,board[Current_Pos].Square_Name,board[Current_Pos].Cell_Data.Railway.Base_Price,player_list[player_id].Player_Cash);

        return Bought;
        }

        return Didnt_Buy;
        break;
    }

    case SQ_Type_Utility:
    {
        if((Willing_to_Buy == Yes) && 
        (Prioritized != None))
        {
        player_list[player_id].Player_Cash -= board[Current_Pos].Cell_Data.Utility.Base_Price;
        board[Current_Pos].Cell_Data.Utility.Company_Owner = player_id;
        printf("\n%s Purchased %s for LKR %d.\nRemaining Balance : %d\n",player_list[player_id].Player_Name,board[Current_Pos].Square_Name,board[Current_Pos].Cell_Data.Utility.Base_Price,player_list[player_id].Player_Cash);

        return Bought;
        }

        return Didnt_Buy;
        break;
    }
    }
    return Didnt_Buy;
}