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
        Player_List[i].Player_Loan = 0;
        Player_List[i].Player_Position = SQ_GO;
        Player_List[i].Player_Roll_Order = -1;
        Player_List[i].Temp_Dice_Value = 0;
        Player_List[i].Total_Dice_Value = 0;
        Player_List[i].Is_Bankrupt = Not_Bankrupt;
        Player_List[i].Jail_Status = Not_In_Jail;
        Player_List[i].Bidding_Status = Bidding;
        Player_List[i].Jail_Counter = 0;
        Player_List[i].Player_Passed_Go = Not_Passed;

        for (int j = 0; j < 9; j++)
        {
            Player_List[i].Has_Partial_Monopoly[j] = None;
            Player_List[i].Has_Monopoly[j] = None;
        }
    }
};


Auction Player_Buys_Property(Players player_list[], square board[], int player_id,Economic economic_status) 

{
    Player_Choice Willing_to_Buy = No;
    Property_Group_Type Prioritized = None;
    int Current_Pos = player_list[player_id].Player_Position;
    Square_type Prop_Type = board[Current_Pos].Cell_Type;

    if(Prop_Type == SQ_Type_Property || Prop_Type == SQ_Type_Railway || Prop_Type == SQ_Type_Utility)
    {
        Owners_Property Owner;

        if(Prop_Type == SQ_Type_Property)
        {
            Owner = board[Current_Pos].Cell_Data.Properties.Property_Owner;
        }
        else if(Prop_Type == SQ_Type_Utility)
        {
            Owner = board[Current_Pos].Cell_Data.Utility.Company_Owner;
        }
        else{
            Owner = board[Current_Pos].Cell_Data.Railway.Railway_Owner;
        }

        if(Owner != Owner_Bank && Owner != Owner_None)
        {
            return No_Auctions;
        }
    }

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
                int Possible_Income = (board[Current_Pos].Cell_Data.Properties.Base_Rental * 10 * Probability_Of_Landing * Total_Players * Rounds_ROI);
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
                int Possible_Income = board[Current_Pos].Cell_Data.Railway.Base_Rental * Total_Players * Probability_Of_Landing * Rounds_ROI;
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
                int Possible_Income = 4 * 12 * Total_Players * Probability_Of_Landing * Rounds_ROI;
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


void Player_Pays_Rent(Players player_list[],square board[],int player_id)

{
    int Current_Pos = player_list[player_id].Player_Position;
    Square_type Prop_Type = board[Current_Pos].Cell_Type;
    


    switch (Prop_Type)
    {
    case SQ_Type_Property:
    {
        Owners_Property Prop_Owner = board[Current_Pos].Cell_Data.Properties.Property_Owner;
        int Rent_to_Pay = board[Current_Pos].Cell_Data.Properties.Base_Rental;

        switch (board[Current_Pos].Cell_Data.Properties.Number_of_Houses)
        {
        case 0:
        {
            if(board[Current_Pos].Cell_Data.Properties.Number_of_Hotels == 1)
            {
                Rent_to_Pay = Rent_to_Pay * 10;
            }
            break;
        }

        case 1:
        {
            Rent_to_Pay = Rent_to_Pay * 1;
            break;
        }

        case 2:
        {
            Rent_to_Pay = Rent_to_Pay * 2;
            break;
        }

        case 3:
        {
            Rent_to_Pay = Rent_to_Pay * 5;
            break;
        }

        case 4:
        {
            Rent_to_Pay = Rent_to_Pay * 7;
            break;
        }

        }

        if((Prop_Owner != player_id) &&
            (Prop_Owner != Owner_Bank) &&
                (Prop_Owner < Total_Players))
        {
            player_list[player_id].Player_Cash -= Rent_to_Pay;
            player_list[Prop_Owner].Player_Cash += Rent_to_Pay;
            printf("\n%s landed on %s.\nRent Paid : LKR %d.\nOWner : %s.\n",player_list[player_id].Player_Name,board[Current_Pos].Square_Name,Rent_to_Pay,player_list[Prop_Owner].Player_Name);
        }
        break;
    }

    case SQ_Type_Railway:
    {
        Owners_Property Prop_Owner = board[Current_Pos].Cell_Data.Railway.Railway_Owner;

       if(Prop_Owner < Total_Players)
       {
            
            Player_Status Temp_Values = Player_Assessing(player_list,board,Prop_Owner);
            int Rent_to_Pay = board[Current_Pos].Cell_Data.Railway.Base_Rental;

            switch (Temp_Values.Railways_Owned)
            {
            case 1:
            {
                Rent_to_Pay = Rent_to_Pay * 1;
                break;
            }
        
            case 2:
            {
                Rent_to_Pay = Rent_to_Pay * 2;
                break;
            }

            case 3:
            {
                Rent_to_Pay = Rent_to_Pay * 4;
                break;
            }

            case 4:
            {
                Rent_to_Pay = Rent_to_Pay * 8;
                break;
            }
        
            }

            if((Prop_Owner != player_id) &&
            (Prop_Owner != Owner_Bank) &&
                (Prop_Owner != Owner_None))
            {
                player_list[player_id].Player_Cash -= Rent_to_Pay;
                player_list[Prop_Owner].Player_Cash += Rent_to_Pay;
                printf("\n%s landed on %s.\nRent Paid : LKR %d.\nOWner : %s.\n",player_list[player_id].Player_Name,board[Current_Pos].Square_Name,Rent_to_Pay,player_list[Prop_Owner].Player_Name);
            }
        
            break;
       }
    }

    case SQ_Type_Utility:
    {
        Owners_Property Prop_Owner = board[Current_Pos].Cell_Data.Utility.Company_Owner;
        int Rent_to_Pay = player_list[player_id].Temp_Dice_Value;
        
        if((board[SQ_NWSDB].Cell_Data.Utility.Company_Owner == Prop_Owner) &&
            (board[SQ_CEB].Cell_Data.Utility.Company_Owner == Prop_Owner))
        {
            Rent_to_Pay = Rent_to_Pay * 10;
        }
        else
        {
            Rent_to_Pay = Rent_to_Pay * 4;
        }

        if((Prop_Owner != player_id) &&
            (Prop_Owner != Owner_Bank))
        {
            player_list[player_id].Player_Cash -= Rent_to_Pay;
            player_list[Prop_Owner].Player_Cash += Rent_to_Pay;
            printf("\n%s landed on %s.\nRent Paid : LKR %d.\nOWner : %s.\n",player_list[player_id].Player_Name,board[Current_Pos].Square_Name,Rent_to_Pay,player_list[Prop_Owner].Player_Name);
        }
        
        break;
        
    }
    }
}


Player_Status Player_Assessing(Players player_list[],square board[],int player_id)

{
    Player_Status Status_Return;
    player_list[player_id].Player_Assets = 0;
    Status_Return.Total_No_Prop_Owned = 0;
    Status_Return.No_of_Hotels = 0;
    Status_Return.Railways_Owned = 0;
    Status_Return.Outstanding_Loan = player_list[player_id].Player_Loan;
    

    for(int i = 0; i < SQ_Board_Size; i++)
    {
        if((board[i].Cell_Type == SQ_Type_Property) &&
            (board[i].Cell_Data.Properties.Property_Owner == player_id))
        {
            
            player_list[player_id].Player_Assets += board[i].Cell_Data.Properties.Base_Price;
            Status_Return.Total_No_Prop_Owned++;
            Status_Return.No_of_Hotels += board[i].Cell_Data.Properties.Number_of_Hotels;
        }
        
        if((board[i].Cell_Type == SQ_Type_Railway) &&
            (board[i].Cell_Data.Railway.Railway_Owner == player_id))
        {
            player_list[player_id].Player_Assets += board[i].Cell_Data.Railway.Base_Price;
            Status_Return.Total_No_Prop_Owned++;
            Status_Return.Railways_Owned++;
        }

        if((board[i].Cell_Type == SQ_Type_Utility) &&
            (board[i].Cell_Data.Utility.Company_Owner == player_id))
        {
            player_list[player_id].Player_Assets += board[i].Cell_Data.Utility.Base_Price;
            Status_Return.Total_No_Prop_Owned++;
        }
    }

    Status_Return.Net_Worth = (player_list[player_id].Player_Cash + player_list[player_id].Player_Assets);

    return Status_Return;

}


void Player_Builds(Players player_list[],square board[],int player_id,Economic economic_status,Government_Regulations current_regulations)
{   
    int Curr_Pos = player_list[player_id].Player_Position;

    if(board[Curr_Pos].Cell_Type != SQ_Type_Property)
    {
        return;
    }

    
    int Cash_Reserve_House = player_list[player_id].Player_Cash - board[Curr_Pos].Cell_Data.Properties.House_Construction_Cost;
    int Cash_Reserve_Hotel = player_list[player_id].Player_Cash - board[Curr_Pos].Cell_Data.Properties.Hotel_Construction_Cost;
    Property_Group_Type Player_Has_Monopoly = None;
    int Is_Eligible_to_Build_House = false;
    int Is_Eligible_to_Build_Hotel = true;
    int Min_Houses = 10;
    int If_Building_House = false;
    int If_Building_Hotel = false;

    for (int i = 0; i < 9; i++)
    {
        if(player_list[player_id].Has_Monopoly[i] == board[Curr_Pos].Cell_Data.Properties.Group)  
        {
            Player_Has_Monopoly = board[Curr_Pos].Cell_Data.Properties.Group;
        }
    }

    if(Player_Has_Monopoly == None)
    {
        return;
    }

   
    for(int i = 0; i < SQ_Board_Size; i++)
    {   
        
        if((board[i].Cell_Type == SQ_Type_Property) &&
            (Player_Has_Monopoly != None) &&
            (board[i].Cell_Data.Properties.Group == Player_Has_Monopoly))
        {
           if(board[i].Cell_Data.Properties.Number_of_Houses < Min_Houses)
           {
                Min_Houses = board[i].Cell_Data.Properties.Number_of_Houses;
           }

           if((board[i].Cell_Data.Properties.Number_of_Houses < 4) &&
                (board[i].Cell_Data.Properties.Number_of_Hotels == 0))
           {
                Is_Eligible_to_Build_Hotel = false;
           }
           
        } 
    }

    Is_Eligible_to_Build_House = (board[Curr_Pos].Cell_Data.Properties.Number_of_Houses == Min_Houses);

    //Building Houses

    if((board[Curr_Pos].Cell_Data.Properties.Number_of_Houses) < 4 &&
        (Is_Eligible_to_Build_House == true) &&
            (Cash_Reserve_House >= 0) && 
                board[Curr_Pos].Cell_Data.Properties.Number_of_Hotels == 0)

    {
        switch (player_id)
        {
        case Aggressive_Investor:
        {
            If_Building_House = true;
            break;
        }

        case Conservative_Banker:
        {
            if(economic_status != Recession)
            {
                If_Building_House = true;
            }
            break;
        }

        case Risk_Taker:
        {
           If_Building_House = true;
           break;
        }

        case Opportunistic_Trader:
        {
            if(economic_status != Inflation ||
                current_regulations == Housing_Subsidy)
            {
                If_Building_House =true;
            }
            break;
        }
        
        }
    }
    

  //Building Hotels

    if((Is_Eligible_to_Build_Hotel == true) &&
        (Cash_Reserve_Hotel > 0) &&
            (board[Curr_Pos].Cell_Data.Properties.Number_of_Hotels == 0))
    {
        switch (player_id)
        {
        case Aggressive_Investor:
        {
            If_Building_Hotel = true;
            
            break;
        }

        case Conservative_Banker:
        {
            if(player_list[player_id].Loan_status == No_Loans)
            {
                If_Building_Hotel = true;
            }
            break;
        }

        case Risk_Taker:
        {
            If_Building_Hotel = true;

            break;
        }
        
        case Opportunistic_Trader:
        {
            if(economic_status != Inflation ||
                current_regulations == Housing_Subsidy)
            {
                If_Building_Hotel = true;
            }
            break;
        }
        }
    }
 
    //printing

    if(If_Building_House == true)
    {
        player_list[player_id].Player_Cash -= board[Curr_Pos].Cell_Data.Properties.House_Construction_Cost;
        board[Curr_Pos].Cell_Data.Properties.Number_of_Houses++;

        printf("%s constructed one house on %s",player_list[player_id].Player_Name,board[Curr_Pos].Square_Name);
    }

    if(If_Building_Hotel == true)
    {
        player_list[player_id].Player_Cash -= board[Curr_Pos].Cell_Data.Properties.Hotel_Construction_Cost;
        board[Curr_Pos].Cell_Data.Properties.Number_of_Hotels = 1;
        board[Curr_Pos].Cell_Data.Properties.Number_of_Houses = 0;

        printf("\n%s upgraded %s to a Hotel.\n",player_list[player_id].Player_Name,board[Curr_Pos].Square_Name);
    }
 
}


void Player_Monopoly_Count(Players player_list[],square board[])
{
    Property_Group_Type Monopoly_Groups[8] = {Brown,Light_Blue,Pink,Orange,Red,Yellow,Green,Dark_Blue};

    for(int i = 0; i < Total_Players; i++)
    {

       for(int j = 0; j < 9; j++)
       {
            player_list[i].Has_Monopoly[j] = None;
            player_list[i].Has_Partial_Monopoly[j] = None;
            
       }

       int Monopoly_Count = 0;
       int Partial_Count = 0;

       for (int k = 0; k < 8; k++)
       {
            switch (Monopoly_Groups[k])
            {
            case Brown:
            {
                int Brown_Count = 0;

                if(board[SQ_PETTAH].Cell_Data.Properties.Property_Owner == i) Brown_Count++;
                if(board[SQ_MARADANA].Cell_Data.Properties.Property_Owner == i) Brown_Count++;

                if(Brown_Count == 2)
                {
                    player_list[i].Has_Monopoly[Monopoly_Count++] = Brown;   
                }
                else if(Brown_Count < 3 && Brown_Count != 0)
                {
                    player_list[i].Has_Partial_Monopoly[Partial_Count++] = Brown;
                }

                break;
            }

            case Light_Blue:
            {
                int Light_Blue_Count = 0;

                if(board[SQ_BAMBALAPITIYA].Cell_Data.Properties.Property_Owner == i) Light_Blue_Count++;
                if(board[SQ_Wellawatte].Cell_Data.Properties.Property_Owner == i) Light_Blue_Count++;
                if(board[SQ_Mount_Lavinia].Cell_Data.Properties.Property_Owner == i) Light_Blue_Count++;

                if(Light_Blue_Count == 3)
                {
                    player_list[i].Has_Monopoly[Monopoly_Count++] = Light_Blue;   
                }
                else if(Light_Blue_Count < 3 && Light_Blue_Count != 0)
                {
                    player_list[i].Has_Partial_Monopoly[Partial_Count++] = Light_Blue;
                }

                break;
            }

            case Pink:
            {
                int Pink_Count = 0;

                if(board[SQ_Maharagama].Cell_Data.Properties.Property_Owner == i) Pink_Count++;
                if(board[SQ_Nugegoda].Cell_Data.Properties.Property_Owner == i) Pink_Count++;
                if(board[SQ_Kottawa].Cell_Data.Properties.Property_Owner == i) Pink_Count++;

                if(Pink_Count == 3)
                {
                    player_list[i].Has_Monopoly[Monopoly_Count++] = Pink;   
                }
                else if(Pink_Count < 3 && Pink_Count != 0)
                {
                    player_list[i].Has_Partial_Monopoly[Partial_Count++] = Pink;
                }

                break;
            }

            case Orange:
            {
                int Orange_Count = 0;

                if(board[SQ_Negombo].Cell_Data.Properties.Property_Owner == i) Orange_Count++;
                if(board[SQ_Katunayake].Cell_Data.Properties.Property_Owner == i) Orange_Count++;
                if(board[SQ_Ja_Ela].Cell_Data.Properties.Property_Owner == i) Orange_Count++;

                if(Orange_Count == 3)
                {
                    player_list[i].Has_Monopoly[Monopoly_Count++] = Orange;   
                }
                else if(Orange_Count < 3 && Orange_Count != 0)
                {
                    player_list[i].Has_Partial_Monopoly[Partial_Count++] = Orange;
                }

                break;
            }

            case Red:
            {
                int Red_Count = 0;

                if(board[SQ_Kandy_City].Cell_Data.Properties.Property_Owner == i) Red_Count++;
                if(board[SQ_Peradeniya].Cell_Data.Properties.Property_Owner == i) Red_Count++;
                if(board[SQ_Katugastota].Cell_Data.Properties.Property_Owner == i) Red_Count++;

                if(Red_Count == 3)
                {
                    player_list[i].Has_Monopoly[Monopoly_Count++] = Red;   
                }
                else if(Red_Count < 3 && Red_Count != 0)
                {
                    player_list[i].Has_Partial_Monopoly[Partial_Count++] = Red;
                }
                
                break;

            }

            case Yellow:
            {
                int Yellow_Count = 0;

                if(board[SQ_Galle_Fort].Cell_Data.Properties.Property_Owner == i) Yellow_Count++;
                if(board[SQ_Unawatuna].Cell_Data.Properties.Property_Owner == i) Yellow_Count++;
                if(board[SQ_Hikkaduwa].Cell_Data.Properties.Property_Owner == i) Yellow_Count++;

                if(Yellow_Count == 3)
                {
                    player_list[i].Has_Monopoly[Monopoly_Count++] = Yellow;   
                }
                else if(Yellow_Count < 3 && Yellow_Count != 0)
                {
                    player_list[i].Has_Partial_Monopoly[Partial_Count++] = Yellow;
                }

                break;
            }

            case Green:
            {
                int Green_Count = 0;

                if(board[SQ_Jaffna_Town].Cell_Data.Properties.Property_Owner == i) Green_Count++;
                if(board[SQ_Nallur].Cell_Data.Properties.Property_Owner == i) Green_Count++;
                if(board[SQ_Trincomalee].Cell_Data.Properties.Property_Owner == i) Green_Count++;

                if(Green_Count == 3)
                {
                    player_list[i].Has_Monopoly[Monopoly_Count++] = Green;   
                }
                else if(Green_Count < 3 && Green_Count != 0)
                {
                    player_list[i].Has_Partial_Monopoly[Partial_Count++] = Green;
                }
                break;
            }

            case Dark_Blue:
            {
                int Dark_Blue_Count = 0;

                if(board[SQ_Nuwara_Eliya].Cell_Data.Properties.Property_Owner == i) Dark_Blue_Count++;
                if(board[SQ_Galle_Face].Cell_Data.Properties.Property_Owner == i) Dark_Blue_Count++;
                
                if(Dark_Blue_Count == 2)
                {
                    player_list[i].Has_Monopoly[Monopoly_Count++] = Dark_Blue;   
                }
                else if(Dark_Blue_Count < 3 && Dark_Blue_Count != 0)
                {
                    player_list[i].Has_Partial_Monopoly[Partial_Count++] = Dark_Blue;
                }

                break;
            }
            }
       }
    }

}


int Player_In_Jail(Players player_list[],square board[],int player_id,int *turn_count,Dice_Type dice)
{
    int Curr_Pos = player_list[player_id].Player_Position;
    int Player_Cash = player_list[player_id].Player_Cash;

    if((Curr_Pos == SQ_Go_To_Jail) &&
        (player_list[player_id].Jail_Status == Not_In_Jail))
    {
        player_list[player_id].Jail_Status = In_Jail;
        player_list[player_id].Player_Position = SQ_Jail;
        player_list[player_id].Jail_Counter = (*turn_count);
        printf("%s has Been Moved to Jail.",player_list[player_id].Player_Name);

        return 0;
    }

    

    if(player_list[player_id].Jail_Status == In_Jail)
    {
        if(((*turn_count) - player_list[player_id].Jail_Counter) >= 3)
        {
        player_list[player_id].Jail_Status = Not_In_Jail;
        printf("3 Turns Have Passed, %s Moved Out of Jail",player_list[player_id].Player_Name);
        return 1;
        }

        if(dice.Is_Double == 1)
        {
            player_list[player_id].Jail_Status = Not_In_Jail;
            printf("%s Rolled a Double Moved Out From Jail",player_list[player_id].Player_Name);

            return 1;
        }

        switch (player_id)
        {
        case Aggressive_Investor:
        {
            if(Player_Cash >= 300)
            {
                player_list[player_id].Player_Cash -= 300;
                player_list[player_id].Jail_Status = Not_In_Jail;
                printf("%s Paid LKR 300 And Moved Out From Jail",player_list[player_id].Player_Name);

                return 1;
            }
            break;
        }
        
        case Risk_Taker:
        {
            if(Player_Cash >= 300)
            {
                player_list[player_id].Player_Cash -= 300;
                player_list[player_id].Jail_Status = Not_In_Jail;
                printf("%s Paid LKR 300 And Moved Out From Jail",player_list[player_id].Player_Name);

                return 1;
            }
            break;
        }
        
        case Opportunistic_Trader:
        {
            if(Player_Cash >= 300)
            {
                player_list[player_id].Player_Cash -= 300;
                player_list[player_id].Jail_Status = Not_In_Jail;
                printf("%s Paid LKR 300 And Moved Out From Jail",player_list[player_id].Player_Name);

                return 1;
            }
            break;
        }

        return 0;
        }

        return 0;

    }
    return 1;
}


void Player_Pays_Tax(Players player_list[],square board[],int player_id,double income_tax_rate)

{
    int income_tax = Round_Off((double)player_list[player_id].Player_Cash * income_tax_rate);
    

    if((player_list[player_id].Player_Position == board[SQ_INCOME_TAX].Location_ID) &&
        (player_list[player_id].Player_Cash) >= income_tax)
    {
        player_list[player_id].Player_Cash -= income_tax;
        printf("\n%s Has paid Income Tax : LKR %d\n",player_list[player_id].Player_Name,income_tax);
    }
}


void Property_Auctions(Players player_list[],square board[],int player_id,int auction_status,short final_order[],Economic Econ_Status)
{
    square location = board[player_list[player_id].Player_Position];

    int Highest_Bid = 0;

    if(location.Cell_Type == SQ_Type_Property)
    {
        Highest_Bid = (location.Cell_Data.Properties.Base_Price * 0.5);
    }
    else if(location.Cell_Type == SQ_Type_Utility)
    {
        Highest_Bid = (location.Cell_Data.Utility.Base_Price * 0.5);
    }
    else if(location.Cell_Type == SQ_Type_Railway)
    {
        Highest_Bid = (location.Cell_Data.Railway.Base_Price * 0.5);
    }
    else{
        return;
    }

    switch (auction_status)
    {
    case Didnt_Buy:
    {
        for(int i = 0; i < Total_Players; i++)
        {
            player_list[i].Bidding_Status = Bidding;
        }

        int active = Total_Players;

        while(active > 1)
        {
            active = 0;
            
            for(int i = 0; i < Total_Players; i++)
            {
                if((player_list[final_order[i]].Bidding_Status == Bidding) &&
                    (Players_Bid(player_list,location,final_order[i],&Highest_Bid,Econ_Status)))
                {
                    active++;
                }
            }
        }

        int winner = -1;

        for(int i = 0; i < Total_Players; i++)
        {
            if(player_list[i].Bidding_Status == Bidding)
            {
                winner = i;
                break;
            }
        }

        if(winner != -1)
        {
            player_list[winner].Player_Cash -= Highest_Bid;

            if(location.Cell_Type == SQ_Type_Property)
            {
                board[location.Location_ID].Cell_Data.Properties.Property_Owner = winner;
            }
            else if(location.Cell_Type == SQ_Type_Railway)
            {
                board[location.Location_ID].Cell_Data.Railway.Railway_Owner = winner;
            }
            else if(location.Cell_Type == SQ_Type_Utility)
            {
                board[location.Location_ID].Cell_Data.Utility.Company_Owner = winner;
            }

            printf("\n%s wins the auction.\n",player_list[winner].Player_Name);
            printf("\n%s purchased %s for LKR %d.\n",player_list[winner].Player_Name,location.Square_Name,Highest_Bid);
            printf("\nRemaining Balance : LKR %d.\n",player_list[winner].Player_Cash);
        }

        for(int i = 0; i < Total_Players; i++)
        {
            player_list[i].Bidding_Status = Bidding;
        }

        break;

    }
        
    
    default:
        break;
    }
}


int Players_Bid(Players player_list[],square bidding_property,int player_id,int *highest_bid,Economic econ_status)
{
    int player_cash_reserve = (player_list[player_id].Player_Cash > ((*highest_bid) + 250));
    int Eligible_to_Bid = (player_list[player_id].Bidding_Status == Bidding); 

    switch (bidding_property.Cell_Type)
    {
    case SQ_Type_Property:
    {
        switch (player_id)
        {
        case Aggressive_Investor:
        {
            int cash_threshold = Round_Off((double)bidding_property.Cell_Data.Properties.Base_Price * 1.2); 

            if(((bidding_property.Location_ID == SQ_Galle_Face) || (bidding_property.Location_ID == SQ_Nuwara_Eliya)) && 
                (player_cash_reserve) && Eligible_to_Bid)
            {
                (*highest_bid) += 250;
            }

            else if((player_cash_reserve) &&
                    (Eligible_to_Bid) && 
                    ((*highest_bid) < cash_threshold))
            {
                (*highest_bid) += 250;
            }

            else{
                player_list[player_id].Bidding_Status = Not_Bidding;
            }
            break;
        }

        case Conservative_Banker:
        {
            if((econ_status != Recession) &&
                (player_cash_reserve) &&
                (Eligible_to_Bid) &&
                ( (*highest_bid) < bidding_property.Cell_Data.Properties.Base_Price))
            {
                (*highest_bid) += 250;
            }
            else{
                player_list[player_id].Bidding_Status = Not_Bidding;
            }
            break;
        }

        case Risk_Taker:
        {
            if((player_cash_reserve) &&
                (Eligible_to_Bid))
            {
                (*highest_bid) += 250;
            }
            else{
                player_list[player_id].Bidding_Status = Not_Bidding; 
            }
            break;
        }

        case Opportunistic_Trader:
        {
            if((player_cash_reserve) &&
                ((*highest_bid) < bidding_property.Cell_Data.Properties.Base_Price) &&
                (Eligible_to_Bid))
            {
                (*highest_bid) += 250;
            }
            else{
                player_list[player_id].Bidding_Status = Not_Bidding;
            }
            break;
        }
        
        break;
        } 
        break;
    }

    case SQ_Type_Railway:
    {  
        switch (player_id)
        {
        case Aggressive_Investor:
        {
            int cash_threshold = Round_Off((double)bidding_property.Cell_Data.Railway.Base_Price * 1.2); 

            if((player_cash_reserve) &&
                    (Eligible_to_Bid) && 
                    ((*highest_bid) < cash_threshold))
            {
                (*highest_bid) += 250;
            }
            else{
                player_list[player_id].Bidding_Status = Not_Bidding;
            }
            break;
        }

        case Conservative_Banker:
        {
            if((econ_status != Recession) &&
                (player_cash_reserve) &&
                (Eligible_to_Bid) &&
                ( (*highest_bid) < bidding_property.Cell_Data.Railway.Base_Price))
            {
                (*highest_bid) += 250;
            }
            else{
                player_list[player_id].Bidding_Status = Not_Bidding;
            }
            break;
        }

        case Risk_Taker:
        {
            if((player_cash_reserve) &&
                (Eligible_to_Bid))
            {
                (*highest_bid) += 250;
            }
            else{
                player_list[player_id].Bidding_Status = Not_Bidding; 
            }
            break;
        }

        case Opportunistic_Trader:
        {
            if((player_cash_reserve) &&
                ((*highest_bid) < bidding_property.Cell_Data.Railway.Base_Price) &&
                (Eligible_to_Bid))
            {
                (*highest_bid) += 250;
            }
            else{
                player_list[player_id].Bidding_Status = Not_Bidding;
            }
            break;
        }
        
        break;
        } 
        break;
    }

    case SQ_Type_Utility:
    {
        switch (player_id)
        {
        case Aggressive_Investor:
        {
            int cash_threshold = Round_Off((double)bidding_property.Cell_Data.Utility.Base_Price * 1.2); 

            if((player_cash_reserve) &&
                    (Eligible_to_Bid) && 
                    ((*highest_bid) < cash_threshold))
            {
                (*highest_bid) += 250;
            }

            else{
                player_list[player_id].Bidding_Status = Not_Bidding;
            }
            break;
        }

        case Conservative_Banker:
        {
            if((econ_status != Recession) &&
                (player_cash_reserve) &&
                (Eligible_to_Bid) &&
                ( (*highest_bid) < bidding_property.Cell_Data.Utility.Base_Price))
            {
                (*highest_bid) += 250;
            }
            else{
                player_list[player_id].Bidding_Status = Not_Bidding;
            }
            break;
        }

        case Risk_Taker:
        {
            if((player_cash_reserve) &&
                (Eligible_to_Bid))
            {
                (*highest_bid) += 250;
            }
            else{
                player_list[player_id].Bidding_Status = Not_Bidding; 
            }
            break;
        }

        case Opportunistic_Trader:
        {
            if((player_cash_reserve) &&
                ((*highest_bid) < bidding_property.Cell_Data.Utility.Base_Price) &&
                (Eligible_to_Bid))
            {
                (*highest_bid) += 250;
            }
            else{
                player_list[player_id].Bidding_Status = Not_Bidding;
            }
            break;
        }
        
            break;
        } 
        break;
    }
    }

    if(player_list[player_id].Bidding_Status == Bidding)
    {
        printf("\n%s bids LKR %d.\n",player_list[player_id].Player_Name,(*highest_bid));
        return 1;
    }
    else{
        printf("\n%s withdraws.\n",player_list[player_id].Player_Name);
        return 0;
    }

}