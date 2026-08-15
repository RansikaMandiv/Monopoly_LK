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
        Player_List[i].Player_Loan_Amount = 0;
        Player_List[i].Player_Loan_Interest_Rate = 0;
        Player_List[i].Player_Loan_Start = 0;
        Player_List[i].Player_Tax_Due = 0;
        Player_List[i].Player_Position = SQ_GO;
        Player_List[i].Player_Roll_Order = false;
        Player_List[i].Temp_Dice_Value = 0;
        Player_List[i].Total_Dice_Value = 0;
        Player_List[i].Is_Bankrupt = Not_Bankrupt;
        Player_List[i].Jail_Status = Not_In_Jail;
        Player_List[i].Bidding_Status = Bidding;
        Player_List[i].Jail_Counter = 0;
        Player_List[i].Player_Passed_Go = Not_Passed;
        Player_List[i].Previous_Data.Player_Loan_Previous = 0;
        National_Event_Initialization(Player_List[i].Player_Card_Stack);
        Player_List[i].Current_Boost = (Player_Temp_Boosts){
            
            .Closed_Property = Property_Open,
            .Insurance_Dis_Value = 1.0,
            .Property_Boost = 1,
            .Railway_Boost = 1,
            .Random_Group = None,
            .utility_Boost = 1.0,
        };

        for (int j = 0; j < 9; j++)
        {
            Player_List[i].Has_Partial_Monopoly[j] = None;
            Player_List[i].Has_Monopoly[j] = None;
        }
    }
}


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
                        (board[i].Cell_Data.Properties.Property_Owner != (Owners_Property)player_id) &&
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
                int Possible_Income = Round_Off(board[Current_Pos].Cell_Data.Properties.Base_Rental * 10 * Probability_Of_Landing * Total_Players * Rounds_ROI);
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
                        (board[i].Cell_Data.Properties.Property_Owner != (Owners_Property)player_id) &&
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
                        (board[i].Cell_Data.Properties.Property_Owner != (Owners_Property)player_id) &&
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

        default:
        {
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
          
        player_list[player_id].Player_Cash -= board[Current_Pos].Cell_Data.Properties.Base_Price;
        board[Current_Pos].Cell_Data.Properties.Property_Owner = player_id;
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

    default:
    {
        break;
    }
    }
    return Didnt_Buy;
}


void Player_Pays_Rent(Players player_list[],square board[],int player_id,Auction *auction_status,short final_order[],Economic econ_status)

{

    if(player_list[player_id].Is_Bankrupt == Bankrupt)
    {
        return;
    }

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
            Rent_to_Pay = Rent_to_Pay * 2;
            break;
        }

        case 2:
        {
            Rent_to_Pay = Rent_to_Pay * 3;
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

        for(int i = 0; i < Total_Players; i++)
        {
            if((Prop_Owner == (Owners_Property)player_id) &&
                (player_list[Prop_Owner].Current_Boost.Property_Boost == 2))
            {
                Rent_to_Pay = Rent_to_Pay * 2;

            }else if((Prop_Owner == (Owners_Property)player_id) &&
                (player_list[Prop_Owner].Current_Boost.Property_Boost == 50) &&
                    (board[Current_Pos].Cell_Data.Properties.Number_of_Hotels == 1))
            {
                Rent_to_Pay = Round_Off((double)Rent_to_Pay * 1.5);
            }  
        }


        if((Prop_Owner != (Owners_Property)player_id) &&
            (Prop_Owner != Owner_Bank) &&
                (Prop_Owner < Total_Players) &&
                (board[Current_Pos].Square_Status != Property_Closed))
        {
            int player_cash = player_list[player_id].Player_Cash - Rent_to_Pay;

            if(player_cash < 0)
            {
                (*auction_status) = Player_Selling;

                while(player_cash < 0)
                {
                    int before = player_list[player_id].Player_Cash;

                    Property_Auctions(player_list,board,player_id,*auction_status,final_order,&board[Current_Pos],econ_status);

                    if(player_list[player_id].Player_Cash == before)
                    {
                        break;
                    }

                    player_cash = player_list[player_id].Player_Cash - Rent_to_Pay;
                }

                

                if((player_cash < 0) && 
                    (player_list[player_id].Is_Bankrupt != Bankrupt))
                {
                    player_list[player_id].Is_Bankrupt = Bankrupt;
                    printf("\n%s has been declared bankrupt.\n",player_list[player_id].Player_Name);

                    (*auction_status) = Bank_Foreclosure;
                    Property_Auctions(player_list,board,player_id,*auction_status,final_order,&board[SQ_GO],econ_status);

                    (*auction_status) = No_Auctions;
                }

                (*auction_status) = No_Auctions;
            }

            if(player_list[player_id].Is_Bankrupt != Bankrupt)
            {
                player_list[player_id].Player_Cash -= Rent_to_Pay;
                player_list[Prop_Owner].Player_Cash += Rent_to_Pay;
            }
            
            

        }
        break;
    }

    case SQ_Type_Railway:
    {
        Owners_Property Prop_Owner = board[Current_Pos].Cell_Data.Railway.Railway_Owner;

       if(Prop_Owner < Total_Players)
       {
            
            Player_Status Temp_Values = Player_Assessing(player_list,board,Prop_Owner,auction_status,final_order,econ_status);
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

            for(int i = 0; i < Total_Players; i++)
            {
                if((Prop_Owner == (Owners_Property)player_id) &&
                    (player_list[Prop_Owner].Current_Boost.Railway_Boost == 2))
                {
                    Rent_to_Pay = Rent_to_Pay * 2;

                }
            }

            if((Prop_Owner != (Owners_Property)player_id) &&
            (Prop_Owner != Owner_Bank) &&
                (Prop_Owner < Total_Players))
            {
                int player_cash = player_list[player_id].Player_Cash - Rent_to_Pay;

                if(player_cash < 0)
                {
                    (*auction_status) = Player_Selling;

                    while(player_cash < 0)
                    {
                        int before = player_list[player_id].Player_Cash;

                        Property_Auctions(player_list,board,player_id,*auction_status,final_order,&board[SQ_GO],econ_status);
                    
                        if(player_list[player_id].Player_Cash == before)
                        {
                            break;
                        }

                        player_cash = player_list[player_id].Player_Cash - Rent_to_Pay;
                    }

                    player_cash = player_list[player_id].Player_Cash - Rent_to_Pay;

                    if((player_cash < 0) && 
                    (player_list[player_id].Is_Bankrupt != Bankrupt))
                    {
                        player_list[player_id].Is_Bankrupt = Bankrupt;
                        printf("\n%s has been declared bankrupt.\n",player_list[player_id].Player_Name);

                        (*auction_status) = Bank_Foreclosure;
                        Property_Auctions(player_list,board,player_id,*auction_status,final_order,&board[SQ_GO],econ_status);

                        (*auction_status) = No_Auctions;
                    }

                    (*auction_status) = No_Auctions;
                }

                if(player_list[player_id].Is_Bankrupt != Bankrupt)
                {
                    player_list[player_id].Player_Cash -= Rent_to_Pay;
                    player_list[Prop_Owner].Player_Cash += Rent_to_Pay;
                }
                    

        }
            
       }
       break;
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

        for(int i = 0; i < Total_Players; i++)
            {
                if((Prop_Owner == (Owners_Property)player_id) &&
                    (player_list[Prop_Owner].Current_Boost.utility_Boost == 0.5))
                {
                    Rent_to_Pay = Round_Off((double)Rent_to_Pay * 0.5);
                }
            }

        if((Prop_Owner != (Owners_Property)player_id) &&
            (Prop_Owner != Owner_Bank) &&
                (Prop_Owner < Total_Players))
        {
            int player_cash = player_list[player_id].Player_Cash - Rent_to_Pay;

            if(player_cash < 0)
            {
                (*auction_status) = Player_Selling;

                while(player_cash < 0)
                {
                    int before = player_list[player_id].Player_Cash;

                    Property_Auctions(player_list,board,player_id,*auction_status,final_order,&board[SQ_GO],econ_status);
                
                    if(player_list[player_id].Player_Cash == before)
                    {
                        break;
                    }

                    player_cash = player_list[player_id].Player_Cash - Rent_to_Pay;
                }

                player_cash = player_list[player_id].Player_Cash - Rent_to_Pay;

                if((player_cash < 0) && 
                    (player_list[player_id].Is_Bankrupt != Bankrupt))
                {
                    player_list[player_id].Is_Bankrupt = Bankrupt;
                    printf("\n%s has been declared bankrupt.\n",player_list[player_id].Player_Name);

                    (*auction_status) = Bank_Foreclosure;
                    Property_Auctions(player_list,board,player_id,*auction_status,final_order,&board[SQ_GO],econ_status);

                    (*auction_status) = No_Auctions;
                }

                (*auction_status) = No_Auctions;
            }

            if(player_list[player_id].Is_Bankrupt != Bankrupt)
            {
                player_list[player_id].Player_Cash -= Rent_to_Pay;
                player_list[Prop_Owner].Player_Cash += Rent_to_Pay;
            }
            

        }
        
        break;
        
    }

    default:
    {
        break;
    }
    }
}


Player_Status Player_Assessing(Players player_list[],square board[],int player_id,Auction *auction_status,short final_order[],Economic econ_status)

{
    Player_Status Status_Return;
    player_list[player_id].Player_Assets = 0;
    Status_Return.Total_No_Prop_Owned = 0;
    Status_Return.No_of_Hotels = 0;
    Status_Return.Railways_Owned = 0;
    Status_Return.Outstanding_Loan = player_list[player_id].Player_Loan_Amount;
    

    for(int i = 0; i < SQ_Board_Size; i++)
    {
        if((board[i].Cell_Type == SQ_Type_Property) &&
            (board[i].Cell_Data.Properties.Property_Owner == (Owners_Property)player_id))
        {
            
            player_list[player_id].Player_Assets += board[i].Cell_Data.Properties.Base_Price;
            Status_Return.Total_No_Prop_Owned++;
            Status_Return.No_of_Hotels += board[i].Cell_Data.Properties.Number_of_Hotels;
        }
        
        if((board[i].Cell_Type == SQ_Type_Railway) &&
            (board[i].Cell_Data.Railway.Railway_Owner == (Owners_Property)player_id))
        {
            player_list[player_id].Player_Assets += board[i].Cell_Data.Railway.Base_Price;
            Status_Return.Total_No_Prop_Owned++;
            Status_Return.Railways_Owned++;
        }

        if((board[i].Cell_Type == SQ_Type_Utility) &&
            (board[i].Cell_Data.Utility.Company_Owner == (Owners_Property)player_id))
        {
            player_list[player_id].Player_Assets += board[i].Cell_Data.Utility.Base_Price;
            Status_Return.Total_No_Prop_Owned++;
        }
    }

    Status_Return.Net_Worth = (player_list[player_id].Player_Cash + player_list[player_id].Player_Assets - player_list[player_id].Player_Loan_Amount - player_list[player_id].Player_Tax_Due);

    if(Status_Return.Net_Worth < 0 && player_list[player_id].Is_Bankrupt != Bankrupt)
    {
        player_list[player_id].Is_Bankrupt = Bankrupt;
        printf("\n%s has been declared bankrupt.\n",player_list[player_id].Player_Name);

        for(int i = 0; i < SQ_Board_Size; i++)
        {
            if((board[i].Cell_Type == SQ_Type_Property) &&
                (board[i].Cell_Data.Properties.Property_Owner == (Owners_Property)player_id))
            {
                
                (*auction_status) = Bank_Foreclosure;
                Property_Auctions(player_list,board,player_id,*auction_status,final_order,&board[i],econ_status);
            }
            else if((board[i].Cell_Type == SQ_Type_Railway) &&
            (board[i].Cell_Data.Railway.Railway_Owner == (Owners_Property)player_id))
            {
                (*auction_status) = Bank_Foreclosure;
                Property_Auctions(player_list,board,player_id,*auction_status,final_order,&board[i],econ_status);
            }
            else if((board[i].Cell_Type == SQ_Type_Utility) &&
            (board[i].Cell_Data.Utility.Company_Owner == (Owners_Property)player_id))
            {
                (*auction_status) = Bank_Foreclosure;
                Property_Auctions(player_list,board,player_id,*auction_status,final_order,&board[i],econ_status);
            }
        }
    }

    (*auction_status) = No_Auctions;
    return Status_Return;


}


void Player_Builds(Players player_list[],square board[],int player_id,Economic economic_status,Government_Regulations current_regulations)
{   

    if((player_list[player_id].Is_Bankrupt == Bankrupt))
    {
        return;
    }

    int Curr_Pos = player_list[player_id].Player_Position;

    if((board[Curr_Pos].Cell_Type != SQ_Type_Property))
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
            (board[i].Cell_Data.Properties.Group == Player_Has_Monopoly) &&
                (player_list[player_id].Current_Boost.Closed_Property != (Square_ID)i))
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
            if((economic_status != Recession) &&
                (player_list[player_id].Player_Card_Stack[Currency_Depreciation].National_Card_Status != Card_Activated))
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
            if(((economic_status != Inflation) && (player_list[player_id].Player_Card_Stack[Currency_Depreciation].National_Card_Status != Card_Activated)) ||
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

        printf("\n%s constructed one house on %s\n",player_list[player_id].Player_Name,board[Curr_Pos].Square_Name);
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

                if(board[SQ_PETTAH].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Brown_Count++;
                if(board[SQ_MARADANA].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Brown_Count++;

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

                if(board[SQ_BAMBALAPITIYA].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Light_Blue_Count++;
                if(board[SQ_Wellawatte].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Light_Blue_Count++;
                if(board[SQ_Mount_Lavinia].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Light_Blue_Count++;

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

                if(board[SQ_Maharagama].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Pink_Count++;
                if(board[SQ_Nugegoda].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Pink_Count++;
                if(board[SQ_Kottawa].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Pink_Count++;

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

                if(board[SQ_Negombo].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Orange_Count++;
                if(board[SQ_Katunayake].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Orange_Count++;
                if(board[SQ_Ja_Ela].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Orange_Count++;

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

                if(board[SQ_Kandy_City].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Red_Count++;
                if(board[SQ_Peradeniya].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Red_Count++;
                if(board[SQ_Katugastota].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Red_Count++;

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

                if(board[SQ_Galle_Fort].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Yellow_Count++;
                if(board[SQ_Unawatuna].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Yellow_Count++;
                if(board[SQ_Hikkaduwa].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Yellow_Count++;

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

                if(board[SQ_Jaffna_Town].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Green_Count++;
                if(board[SQ_Nallur].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Green_Count++;
                if(board[SQ_Trincomalee].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Green_Count++;

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

                if(board[SQ_Nuwara_Eliya].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Dark_Blue_Count++;
                if(board[SQ_Galle_Face].Cell_Data.Properties.Property_Owner == (Owners_Property)i) Dark_Blue_Count++;
                
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

            default:
            {
                break;
            }
            }
       }
    }

}


int Player_In_Jail(Players player_list[],int player_id,int *turn_count,Dice_Type dice)
{
    int Curr_Pos = player_list[player_id].Player_Position;
    int Player_Cash = player_list[player_id].Player_Cash;

    if((Curr_Pos == SQ_Go_To_Jail) &&
        (player_list[player_id].Jail_Status == Not_In_Jail))
    {
        player_list[player_id].Jail_Status = In_Jail;
        player_list[player_id].Player_Position = SQ_Jail;
        player_list[player_id].Jail_Counter = (*turn_count);
        printf("\n%s has Been Moved to Jail.\n",player_list[player_id].Player_Name);

        return 0;
    }

    

    if(player_list[player_id].Jail_Status == In_Jail)
    {
        if(((*turn_count) - player_list[player_id].Jail_Counter) >= 3)
        {
        player_list[player_id].Jail_Status = Not_In_Jail;
        printf("\n3 Turns Have Passed, %s Moved Out of Jail\n",player_list[player_id].Player_Name);
        return 1;
        }

        if(dice.Is_Double == 1)
        {
            player_list[player_id].Jail_Status = Not_In_Jail;
            printf("\n%s Rolled a Double Moved Out From Jail\n",player_list[player_id].Player_Name);

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
                printf("\n%s Paid LKR 300 And Moved Out From Jail\n",player_list[player_id].Player_Name);

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
                printf("\n%s Paid LKR 300 And Moved Out From Jail\n",player_list[player_id].Player_Name);

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
    if((player_list[player_id].Player_Position != SQ_INCOME_TAX) ||
        (player_list[player_id].Is_Bankrupt == Bankrupt))
    {
        return;
    }

    int income_tax = Round_Off((double)player_list[player_id].Player_Cash * income_tax_rate);
    int debt = player_list[player_id].Player_Tax_Due;
    int payable = debt + income_tax;

    

    if((player_list[player_id].Player_Position == board[SQ_INCOME_TAX].Location_ID) &&
        (player_list[player_id].Player_Cash) >= payable)
    {
        player_list[player_id].Player_Cash -= payable;
        player_list[player_id].Player_Tax_Due = 0;
        printf("\n%s Has paid Income Tax : LKR %d\n",player_list[player_id].Player_Name,payable);
    }
    else{
        player_list[player_id].Player_Tax_Due += income_tax;
        printf("\n%s Has Income Tax Due: LKR %d\n",player_list[player_id].Player_Name,payable);
    }
}


void Property_Auctions(Players player_list[],square board[],int player_id,int auction_status,short final_order[],square *foreclosure,Economic Econ_Status)
{
    

    switch (auction_status)
    {
    case Didnt_Buy:
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
        
        for(int i = 0; i < Total_Players; i++)
        {
            if(player_list[i].Is_Bankrupt != Bankrupt)
            {
                player_list[i].Bidding_Status = Bidding;
            }

        }

        int active = Total_Players;
        int last_bidder = -1;

        while(active > 1)
        {
            active = 0;
            
            for(int i = 0; i < Total_Players; i++)
            {
                if((player_list[final_order[i]].Bidding_Status == Bidding) &&
                    (Players_Bid(player_list,location,final_order[i],&Highest_Bid,Econ_Status)))
                {
                    active++;
                    last_bidder = final_order[i];
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

        if(winner == -1)
        {
            winner = last_bidder;
            
        }

        if(winner != -1)
        {
            player_list[winner].Player_Cash -= Highest_Bid;

            if(location.Cell_Type == SQ_Type_Property)
            {
                Building_Destroy(&board[location.Location_ID]);
                board[location.Location_ID].Cell_Data.Properties.Property_Owner = winner;
                
            }
            else if(location.Cell_Type == SQ_Type_Railway)
            {
                Building_Destroy(&board[location.Location_ID]);
                board[location.Location_ID].Cell_Data.Railway.Railway_Owner = winner;
            }
            else if(location.Cell_Type == SQ_Type_Utility)
            {
                Building_Destroy(&board[location.Location_ID]);
                board[location.Location_ID].Cell_Data.Utility.Company_Owner = winner;
            }

            printf("\n%s wins the auction.\n",player_list[winner].Player_Name);
            printf("\n%s purchased %s for LKR %d.\n",player_list[winner].Player_Name,location.Square_Name,Highest_Bid);
            printf("\nRemaining Balance : LKR %d.\n",player_list[winner].Player_Cash);
        }

        for(int i = 0; i < Total_Players; i++)
        {
            if(player_list[i].Is_Bankrupt != Bankrupt)
            {
                player_list[i].Bidding_Status = Bidding;
            }
        }

        break;

    }
    
    case Player_Selling:
    {
        square location = board[SQ_GO];
        int Highest_Bid = 0;
        int min = 10000000;


        for(int i = 0; i < SQ_Board_Size; i++)
        {
            
            if((board[i].Cell_Type == SQ_Type_Property) &&
                (board[i].Cell_Data.Properties.Property_Owner == (Owners_Property)player_id) &&
                (board[i].Cell_Data.Properties.Mortgage == Unmortgaged))
            {
                

                if(board[i].Cell_Data.Properties.Base_Price < min)
                {
                    location = board[i];
                    min = location.Cell_Data.Properties.Base_Price;
                }
            }
            else if((board[i].Cell_Type == SQ_Type_Railway) &&
                (board[i].Cell_Data.Railway.Railway_Owner == (Owners_Property)player_id) &&
                (board[i].Cell_Data.Railway.Mortgage == Unmortgaged))
            {
                if(board[i].Cell_Data.Railway.Base_Price < min)
                {
                    location = board[i];
                    min = location.Cell_Data.Railway.Base_Price;
                }
            }
            else if((board[i].Cell_Type == SQ_Type_Utility) &&
                (board[i].Cell_Data.Utility.Company_Owner == (Owners_Property)player_id) &&
                (board[i].Cell_Data.Utility.Mortgage == Unmortgaged))
            {
                 if(board[i].Cell_Data.Utility.Base_Price < min)
                {
                    location = board[i];
                    min = location.Cell_Data.Utility.Base_Price;
                }
            }
                
            
        }

        if(location.Location_ID == board[SQ_GO].Location_ID)
        {
            player_list[player_id].Is_Bankrupt = Bankrupt;
            printf("\n%s has been declared bankrupt.\n",player_list[player_id].Player_Name);
            return;
        }

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


        for(int i = 0; i < Total_Players; i++)
        {
            if(player_list[i].Is_Bankrupt != Bankrupt)
            {
                player_list[i].Bidding_Status = Bidding;
            }
        }

        //removing the selling player
        player_list[player_id].Bidding_Status = Not_Bidding;

        int active = Total_Players;
        int last_bidder= -1;

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

        if(winner == -1)
        {
            winner = last_bidder;
        }

        if(winner != -1)
        {
            player_list[winner].Player_Cash -= Highest_Bid;
            player_list[player_id].Player_Cash += Highest_Bid;

            if(location.Cell_Type == SQ_Type_Property)
            {
                Building_Destroy(&board[location.Location_ID]);
                board[location.Location_ID].Cell_Data.Properties.Property_Owner = winner;
                
            }
            else if(location.Cell_Type == SQ_Type_Railway)
            {
                Building_Destroy(&board[location.Location_ID]);
                board[location.Location_ID].Cell_Data.Railway.Railway_Owner = winner;
            }
            else if(location.Cell_Type == SQ_Type_Utility)
            {
                Building_Destroy(&board[location.Location_ID]);
                board[location.Location_ID].Cell_Data.Utility.Company_Owner = winner;
            }

            printf("\n%s wins the auction.\n",player_list[winner].Player_Name);
            printf("\n%s purchased %s for LKR %d.\n",player_list[winner].Player_Name,location.Square_Name,Highest_Bid);
            printf("\nRemaining Balance : LKR %d.\n",player_list[winner].Player_Cash);
        }

        for(int i = 0; i < Total_Players; i++)
        {
            if(player_list[i].Is_Bankrupt != Bankrupt)
            {
                player_list[i].Bidding_Status = Bidding;
            }
        }

        break;
    }
    
    case Bank_Foreclosure:
    {
        square location = (*foreclosure);

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
        
        for(int i = 0; i < Total_Players; i++)
        {
            if(player_list[i].Is_Bankrupt != Bankrupt)
            {
                player_list[i].Bidding_Status = Bidding;
            }

        }

        int active = Total_Players;
        int last_bidder = -1;

        while(active > 1)
        {
            active = 0;
            
            for(int i = 0; i < Total_Players; i++)
            {
                if((player_list[final_order[i]].Bidding_Status == Bidding) &&
                    (Players_Bid(player_list,location,final_order[i],&Highest_Bid,Econ_Status)))
                {
                    active++;
                    last_bidder = final_order[i];
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

        if((winner == -1) &&
            (last_bidder == -1))
        {
            printf("\nNO Bidders.%s not foreclosed.\n",location.Square_Name);
        }
        else if (winner == -1)
        {
            winner = last_bidder;
        }

        if(winner != -1)
        {
            player_list[winner].Player_Cash -= Highest_Bid;

            if(location.Cell_Type == SQ_Type_Property)
            {
                Building_Destroy(&board[location.Location_ID]);
                board[location.Location_ID].Cell_Data.Properties.Property_Owner = winner;
                
            }
            else if(location.Cell_Type == SQ_Type_Railway)
            {
                Building_Destroy(&board[location.Location_ID]);
                board[location.Location_ID].Cell_Data.Railway.Railway_Owner = winner;
            }
            else if(location.Cell_Type == SQ_Type_Utility)
            {
                Building_Destroy(&board[location.Location_ID]);
                board[location.Location_ID].Cell_Data.Utility.Company_Owner = winner;
            }

            printf("\n%s wins the auction.\n",player_list[winner].Player_Name);
            printf("\n%s purchased %s for LKR %d.\n",player_list[winner].Player_Name,location.Square_Name,Highest_Bid);
            printf("\nRemaining Balance : LKR %d.\n",player_list[winner].Player_Cash);
        }

        for(int i = 0; i < Total_Players; i++)
        {
            if(player_list[i].Is_Bankrupt != Bankrupt)
            {
                player_list[i].Bidding_Status = Bidding;
            }
        }

        break;

    }

        
    }
}


int Players_Bid(Players player_list[],square bidding_property,int player_id,int *highest_bid,Economic econ_status)
{
    int player_cash_reserve = (player_list[player_id].Player_Cash > ((*highest_bid) + 250));
    int Eligible_to_Bid = ((player_list[player_id].Bidding_Status == Bidding) && (player_list[player_id].Is_Bankrupt != Bankrupt)); 

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
                (player_cash_reserve) && Eligible_to_Bid )
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
        
        default:
        {
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
        
        default:
        {
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
        
        default:
        {
            break;
        }    
        } 
        break;
    }

    default:
    {
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


int Game_Over_Check(Players player_list[],square board[],Auction *auction_status,short final_order[],Economic econ_status,int *game_winner)
{
    int active_players = 0;
    int Winner = -1;
    int Highest_Net_Worth = -1;

    for (int i = 0; i < Total_Players; i++)
    {
        if(player_list[i].Is_Bankrupt != Bankrupt)
        {
            Player_Status temp = Player_Assessing(player_list,board,i,auction_status,final_order,econ_status);

            active_players++;

            if(temp.Net_Worth > Highest_Net_Worth)
            {
                Highest_Net_Worth = temp.Net_Worth;
                Winner = i;
            }
        }
    }

    (*game_winner) = Winner;

    if(Winner != -1 && active_players == 1)
    {
        return 1;
    }
    else{
        return 0;
    }
}


void Building_Destroy(square *location)
{
    if(location->Cell_Type == SQ_Type_Property)
    {
        location->Cell_Data.Properties.Number_of_Hotels = 0;
        location->Cell_Data.Properties.Number_of_Houses = 0;
        location->Cell_Data.Properties.Property_Owner = Owner_Bank;
        location->Cell_Data.Properties.Mortgage = Unmortgaged;
    }
    else if(location->Cell_Type == SQ_Type_Railway)
    {
        location->Cell_Data.Railway.Railway_Owner = Owner_Bank;
        location->Cell_Data.Railway.Mortgage = Unmortgaged;
    }
    else if(location->Cell_Type == SQ_Type_Utility)
    {
        location->Cell_Data.Utility.Company_Owner = Owner_Bank;
        location->Cell_Data.Utility.Mortgage = Unmortgaged;
    }
    
}


void Player_Obtains_Loans(Players player_list[],square board[],int player_id,int loan_interest_rate,int round_count,int *auction_status,Economic econ_status,short final_order[])
{
    if((player_list[player_id].Loan_status == Have_Loans) &&
        (round_count - player_list[player_id].Player_Loan_Start) >= 20)
    {

        printf("\n%s has defaulted.\nCollateral has been foreclosed.\nOutstanding debt cleared.\n",player_list[player_id].Player_Name);

        for(int i = 0; i < SQ_Board_Size; i++)
        {
            if((board[i].Cell_Type == SQ_Type_Property) &&
                (board[i].Cell_Data.Properties.Property_Owner == (Owners_Property)player_id) &&
                    (board[i].Cell_Data.Properties.Mortgage == Mortgaged))
            {
                (*auction_status) = Bank_Foreclosure;
                Property_Auctions(player_list,board,player_id,*auction_status,final_order,&board[i],econ_status);
                (*auction_status) = No_Auctions;

            }
            else if((board[i].Cell_Type == SQ_Type_Railway) &&
                (board[i].Cell_Data.Railway.Railway_Owner == (Owners_Property)player_id) &&
                    (board[i].Cell_Data.Railway.Mortgage == Mortgaged))
            {

                (*auction_status) = Bank_Foreclosure;
                Property_Auctions(player_list,board,player_id,*auction_status,final_order,&board[i],econ_status);
                (*auction_status) = No_Auctions;
            }
            else if((board[i].Cell_Type == SQ_Type_Utility) &&
                (board[i].Cell_Data.Utility.Company_Owner == (Owners_Property)player_id) &&
                (board[i].Cell_Data.Utility.Mortgage == Mortgaged))
            {

                (*auction_status) = Bank_Foreclosure;
                Property_Auctions(player_list,board,player_id,*auction_status,final_order,&board[i],econ_status);
                (*auction_status) = No_Auctions;
            }

            
            
        }
        player_list[player_id].Loan_status = No_Loans;
        player_list[player_id].Player_Loan_Amount = 0;
       
    }
    else if(player_list[player_id].Loan_status == Have_Loans)
    {
        if(player_list[player_id].Previous_Data.Player_Loan_Previous == (round_count - 1))
        {
            player_list[player_id].Player_Loan_Amount = Round_Off(((double)(player_list[player_id].Player_Loan_Amount) * (double)(100 + player_list[player_id].Player_Loan_Interest_Rate)/100));
            player_list[player_id].Previous_Data.Player_Loan_Previous++;
        }
    }


    if(player_list[player_id].Player_Position != SQ_Bank_of_Ceylon)
    {
        return;
    }


    if(player_list[player_id].Loan_status == No_Loans)
    {
        int Obtaining_Loan = 0;

        switch (player_id)
        {

        case Aggressive_Investor:
        {
            for(int i = 0; i < SQ_Board_Size; i++)
            {
                if((board[i].Cell_Type == SQ_Type_Property) &&
                    (board[i].Cell_Data.Properties.Property_Owner == Owner_Bank))
                {
                    Obtaining_Loan = 1;
                    break;
                }
                else if((board[i].Cell_Type == SQ_Type_Railway) &&
                    (board[i].Cell_Data.Railway.Railway_Owner == Owner_Bank))
                {
                    Obtaining_Loan = 1;
                    break;
                }
                else if((board[i].Cell_Type == SQ_Type_Utility) &&
                    (board[i].Cell_Data.Utility.Company_Owner == Owner_Bank))
                {
                    Obtaining_Loan = 1;
                    break;
                }
            }


            break;
        }
            
        
        case Conservative_Banker:
        {
            int max_rent = 0; 

            for(int i = 0; i < SQ_Board_Size; i++)
            {
                if((board[i].Cell_Type == SQ_Type_Property) &&
                    (board[i].Cell_Data.Properties.Property_Owner != (Owners_Property)player_id) &&
                    (board[i].Cell_Data.Properties.Base_Rental > max_rent))
                {
                    max_rent = board[i].Cell_Data.Properties.Base_Rental;
                }
            }

            max_rent = max_rent * 10; //Cost for a Hotel Rent

            if(player_list[player_id].Player_Cash < max_rent)
            {
                Obtaining_Loan = 1;
            }
            break;
        }

        case Risk_Taker:
        {
            Obtaining_Loan = 1;
            break;
        }

        case Opportunistic_Trader:
        {
            int Obtainable_Properties = 0;

            for(int i = 0; i < SQ_Board_Size; i++)
            {
                if((board[i].Cell_Type == SQ_Type_Property) &&
                    (board[i].Cell_Data.Properties.Property_Owner == Owner_Bank))
                {
                    Obtainable_Properties++;
                }
                else if((board[i].Cell_Type == SQ_Type_Railway) &&
                    (board[i].Cell_Data.Railway.Railway_Owner == Owner_Bank))
                {
                    Obtainable_Properties++;
                }
                else if((board[i].Cell_Type == SQ_Type_Utility) &&
                    (board[i].Cell_Data.Utility.Company_Owner == Owner_Bank))
                {
                    Obtainable_Properties++;
                }
            }

            if (Obtainable_Properties >= 5)
            {
                Obtaining_Loan = 1;
            }
            break;
        }
            
        }

        if(Obtaining_Loan == 1)
        {
            int max_loan_approved = 0;

            for(int i = 0; i < SQ_Board_Size; i++)
            {
                if((board[i].Cell_Type == SQ_Type_Property) &&
                    (board[i].Cell_Data.Properties.Property_Owner) == (Owners_Property)player_id && 
                    (board[i].Cell_Data.Properties.Mortgage == Unmortgaged))
                {
                    max_loan_approved += Round_Off(((double)board[i].Cell_Data.Properties.Base_Price * 75) / 100);
                    board[i].Cell_Data.Properties.Mortgage = Mortgaged;
                }
                else if((board[i].Cell_Type == SQ_Type_Railway) &&
                    (board[i].Cell_Data.Railway.Railway_Owner) == (Owners_Property)player_id && 
                    (board[i].Cell_Data.Railway.Mortgage == Unmortgaged))
                {
                    max_loan_approved += Round_Off(((double)board[i].Cell_Data.Railway.Base_Price * 75) / 100);
                    board[i].Cell_Data.Railway.Mortgage = Mortgaged;
                }
                else if((board[i].Cell_Type == SQ_Type_Utility) &&
                    (board[i].Cell_Data.Utility.Company_Owner) == (Owners_Property)player_id && 
                    (board[i].Cell_Data.Utility.Mortgage == Unmortgaged))
                {
                    max_loan_approved += Round_Off(((double)board[i].Cell_Data.Utility.Base_Price * 75) / 100);
                    board[i].Cell_Data.Utility.Mortgage = Mortgaged;
                }
            }

            if(max_loan_approved != 0)
            {
                player_list[player_id].Loan_status = Have_Loans;
                player_list[player_id].Player_Loan_Start = round_count;
                player_list[player_id].Previous_Data.Player_Loan_Previous = round_count;
                player_list[player_id].Player_Loan_Amount += max_loan_approved;
                player_list[player_id].Player_Cash += max_loan_approved;
                player_list[player_id].Player_Loan_Interest_Rate = loan_interest_rate;

                printf("\n%s obtained a secured loan.\n",player_list[player_id].Player_Name);
                printf("Loan Amount : LKR %d.",max_loan_approved);
                printf("\nCollateral:\n");
                
                for(int i = 0; i < SQ_Board_Size; i++)
                {
                    if((board[i].Cell_Type == SQ_Type_Property) &&
                    (board[i].Cell_Data.Properties.Property_Owner) == (Owners_Property)player_id && 
                    (board[i].Cell_Data.Properties.Mortgage == Mortgaged))
                    {
                        printf("%s\n",board[i].Square_Name);
                    }
                    else if((board[i].Cell_Type == SQ_Type_Railway) &&
                        (board[i].Cell_Data.Railway.Railway_Owner) == (Owners_Property)player_id && 
                        (board[i].Cell_Data.Railway.Mortgage == Mortgaged))
                    {
                        printf("%s\n",board[i].Square_Name);
                    }
                    else if((board[i].Cell_Type == SQ_Type_Utility) &&
                        (board[i].Cell_Data.Utility.Company_Owner) == (Owners_Property)player_id && 
                        (board[i].Cell_Data.Utility.Mortgage == Mortgaged))
                    {
                        printf("%s\n",board[i].Square_Name);
                    }
                }

                printf("\nInterest Rate : %d\n",player_list[player_id].Player_Loan_Interest_Rate);
                printf("\nDuration : 20 Rounds\n");
            }
        }
    }
    else if(player_list[player_id].Loan_status == Have_Loans)
    {
        int payable_amount = player_list[player_id].Player_Loan_Amount;
        int player_pays = 0;

        switch (player_id)
        {
        case Aggressive_Investor:
        {
            if(player_list[player_id].Player_Cash > (payable_amount * 2))
            {
                player_pays = 1;
            }

            break;
        }
            
        case Conservative_Banker:
        {
            if(player_list[player_id].Player_Cash >= payable_amount)
            {
                player_pays = 1;
            }
            break;
        }

        case Risk_Taker:
        {
            for(int i = 0; i < SQ_Board_Size; i++)
            {
                 if((board[i].Cell_Type == SQ_Type_Property) &&
                    (board[i].Cell_Data.Properties.Property_Owner) == (Owners_Property)player_id && 
                    (board[i].Cell_Data.Properties.Mortgage == Unmortgaged))
                {
                    player_list[player_id].Loan_status = No_Loans;
                    Player_Obtains_Loans(player_list,board,player_id,loan_interest_rate,round_count,auction_status,econ_status,final_order);
                    break;
                }
                else if((board[i].Cell_Type == SQ_Type_Railway) &&
                    (board[i].Cell_Data.Railway.Railway_Owner) == (Owners_Property)player_id && 
                    (board[i].Cell_Data.Utility.Mortgage == Unmortgaged))
                {
                    player_list[player_id].Loan_status = No_Loans;
                    Player_Obtains_Loans(player_list,board,player_id,loan_interest_rate,round_count,auction_status,econ_status,final_order);
                    break;
                }
                else if((board[i].Cell_Type == SQ_Type_Utility) &&
                    (board[i].Cell_Data.Utility.Company_Owner) == (Owners_Property)player_id && 
                    (board[i].Cell_Data.Utility.Mortgage == Unmortgaged))
                {
                    player_list[player_id].Loan_status = No_Loans;
                    Player_Obtains_Loans(player_list,board,player_id,loan_interest_rate,round_count,auction_status,econ_status,final_order);
                    break;
                }
                else
                {
                    break;
                }
            }

            break;
        }

        case Opportunistic_Trader:
        {
           if(player_list[player_id].Player_Cash > (payable_amount * 2))
            {
                player_pays = 1;
            }

            break;
        }
        }

        if(player_pays == 1)
        {
            player_list[player_id].Player_Cash -= payable_amount;
            player_list[player_id].Player_Loan_Amount = 0;
            player_list[player_id].Loan_status = No_Loans;

            for(int i = 0; i < SQ_Board_Size; i++)
            {
                if((board[i].Cell_Type == SQ_Type_Property) &&
                    (board[i].Cell_Data.Properties.Property_Owner == (Owners_Property)player_id) &&
                    (board[i].Cell_Data.Properties.Mortgage == Mortgaged))
                {
                    board[i].Cell_Data.Properties.Mortgage = Unmortgaged;
                }
                else if((board[i].Cell_Type == SQ_Type_Railway) &&
                    (board[i].Cell_Data.Railway.Railway_Owner == (Owners_Property)player_id) &&
                    (board[i].Cell_Data.Railway.Mortgage == Mortgaged))
                {
                    board[i].Cell_Data.Railway.Mortgage = Unmortgaged;
                }
                else if((board[i].Cell_Type == SQ_Type_Utility) &&
                    (board[i].Cell_Data.Utility.Company_Owner == (Owners_Property)player_id) &&
                    (board[i].Cell_Data.Utility.Mortgage == Mortgaged))
                {
                    board[i].Cell_Data.Utility.Mortgage = Unmortgaged;
                }

            }
            printf("\n%s repaid LKR %d.\n",player_list[player_id].Player_Name,payable_amount);
            printf("\nCollaterals Released.\n");
        }
    }
}