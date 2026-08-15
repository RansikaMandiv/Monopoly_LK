#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"


void National_Event_Initialization(National_Event_Card national_deck[])
{
    national_deck[Tourism_Hype] = (National_Event_Card){
        .Card_Type = Tourism_Hype,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Tourism Hype"
    };

    national_deck[Fuel_Shortage] = (National_Event_Card){
        .Card_Type = Fuel_Shortage,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Fuel Shortage"
    };

    national_deck[Heavy_Floods] = (National_Event_Card){
        .Card_Type = Heavy_Floods,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Heavy Floods"
    };

    national_deck[Political_Rally] = (National_Event_Card){
        .Card_Type = Political_Rally,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Political Rally"
    };

    national_deck[Stock_Market_Rise] = (National_Event_Card){
        .Card_Type = Stock_Market_Rise,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Stock Market Rise"
    };

    national_deck[Economic_Downturn] = (National_Event_Card){
        .Card_Type = Economic_Downturn,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Economic Downturn"
    };

    national_deck[Housing_Subsidy_Card] = (National_Event_Card){
        .Card_Type = Housing_Subsidy_Card,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Housing Subsidy"
    };

    national_deck[Interest_Rate_Cut] = (National_Event_Card){
        .Card_Type = Interest_Rate_Cut,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Interest Rate Cut"
    };

    national_deck[Interest_Rate_Increase] = (National_Event_Card){
        .Card_Type = Interest_Rate_Increase,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Interest Rate Increase"
    };

    national_deck[Tax_Amnesty] = (National_Event_Card){
        .Card_Type = Tax_Amnesty,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Tax Amnesty"
    };

    national_deck[Power_Failure] = (National_Event_Card){
        .Card_Type = Power_Failure,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Power Failure"
    };

    national_deck[Foreign_Funding] = (National_Event_Card){
        .Card_Type = Foreign_Funding,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Foreign Funding"
    };

    national_deck[Port_Expansion] = (National_Event_Card){
        .Card_Type = Port_Expansion,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Port Expansion"
    };

    national_deck[Festival_Season] = (National_Event_Card){
        .Card_Type = Festival_Season,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Festival Season"
    };

    national_deck[Labour_Strike] = (National_Event_Card){
        .Card_Type = Labour_Strike,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Labour Strike"
    };

    national_deck[Insurance_Discount] = (National_Event_Card){
        .Card_Type = Insurance_Discount,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Insurance Discount"
    };

    national_deck[Property_Revaluation] = (National_Event_Card){
        .Card_Type = Property_Revaluation,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Property Revaluation"
    };

    national_deck[Currency_Depreciation] = (National_Event_Card){
        .Card_Type = Currency_Depreciation,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Currency Depreciation"
    };

    national_deck[Government_Grant] = (National_Event_Card){
        .Card_Type = Government_Grant,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "Government Grant"
    };

    national_deck[National_Disaster] = (National_Event_Card){
        .Card_Type = National_Disaster,
        .National_Card_Status = Card_Deactivated,
        .Started_Round = 0,
        .Ending_Round = 0,
        .Card_Name = "National Disaster"
    };
}


void National_Event_Cards(square board[],Players player_list[],int player_id,int *drawn_card,int round_count,Economic *economy_status)
{
    int cur_pos = player_list[player_id].Player_Position;

    if((cur_pos == SQ_NATIONAL_EVENT_CARD_1) ||
        (cur_pos == SQ_National_Event_Card_2) ||
            (cur_pos == SQ_National_Event_Card_3))
    {
    

        int Drawn_Card = (*drawn_card) % 20;


        switch (Drawn_Card)
        {
        case Tourism_Hype:
        {
            (*drawn_card)++;

            player_list[player_id].Current_Boost.Property_Boost = 2;
            player_list[player_id].Player_Card_Stack[Tourism_Hype].National_Card_Status = Card_Activated;
            player_list[player_id].Player_Card_Stack[Tourism_Hype].Ending_Round = round_count + 5; 
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Tourism_Hype].Card_Name);

            break;
        }
        
    
        case Fuel_Shortage:
        {
            (*drawn_card)++;

            player_list[player_id].Current_Boost.Railway_Boost = 2;
            player_list[player_id].Player_Card_Stack[Fuel_Shortage].National_Card_Status = Card_Activated;
            player_list[player_id].Player_Card_Stack[Fuel_Shortage].Ending_Round = round_count + 5; 
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Fuel_Shortage].Card_Name);

            break;
        }
            
        case Heavy_Floods:
        {
            //deprciate property
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Heavy_Floods].Card_Name);
            break;
        }

        case Political_Rally:
        {

            (*drawn_card)++;
            int random_prop = 0;

            if(player_list[player_id].Current_Boost.Closed_Property == SQ_None)
            {
            
                do{

                random_prop = (rand() % 40);
 
            }while((board[random_prop].Cell_Type != SQ_Type_Property) ||
                    (board[random_prop].Cell_Data.Properties.Property_Owner != (Owners_Property)player_id));

            }else{
                random_prop = player_list[player_id].Current_Boost.Closed_Property;
            }

            
            player_list[player_id].Current_Boost.Closed_Property = random_prop;
            board[random_prop].Square_Status = Property_Closed;
            player_list[player_id].Player_Card_Stack[Political_Rally].National_Card_Status = Card_Activated;
            player_list[player_id].Player_Card_Stack[Political_Rally].Ending_Round = round_count + 2;
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Political_Rally].Card_Name);

            break;
        }

        case Stock_Market_Rise:
        {
            (*drawn_card)++;

            for(int i = 0; i < SQ_Board_Size; i++)
            {
                if(board[i].Cell_Type == SQ_Type_Property)
                {
                    board[i].Cell_Data.Properties.Base_Price = Round_Off((double)(board[i].Cell_Data.Properties.Base_Price) * 1.1);
                }
            }

            player_list[player_id].Player_Card_Stack[Stock_Market_Rise].National_Card_Status = Card_Activated;
            player_list[player_id].Player_Card_Stack[Stock_Market_Rise].Ending_Round = round_count + 15;
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Stock_Market_Rise].Card_Name);
            break;
        }

        case Economic_Downturn:
        {
            (*drawn_card)++;

            for(int i = 0; i < SQ_Board_Size; i++)
            {
                if(board[i].Cell_Type == SQ_Type_Property)
                {
                    board[i].Cell_Data.Properties.Base_Price = Round_Off((double)(board[i].Cell_Data.Properties.Base_Price) * 0.85);
                }
            }

            player_list[player_id].Player_Card_Stack[Economic_Downturn].National_Card_Status = Card_Activated;
            player_list[player_id].Player_Card_Stack[Economic_Downturn].Ending_Round = round_count + 15;
            (*economy_status) = Downturn;
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Economic_Downturn].Card_Name);


            break;
        }

        case Housing_Subsidy_Card:
        {
            (*drawn_card)++;

            for(int i = 0; i < SQ_Board_Size; i++)
            {
                if((board[i].Cell_Type == SQ_Type_Property) &&
                    (board[i].Cell_Data.Properties.Property_Owner == (Owners_Property)player_id))
                {
                    board[i].Cell_Data.Properties.House_Construction_Cost = Round_Off((double)(board[i].Cell_Data.Properties.House_Construction_Cost) * 0.70);
                }
            }

            player_list[player_id].Player_Card_Stack[Housing_Subsidy_Card].National_Card_Status = Card_Activated;
            player_list[player_id].Player_Card_Stack[Housing_Subsidy_Card].Ending_Round = round_count + 15;
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Housing_Subsidy_Card].Card_Name);
        }

        case Interest_Rate_Cut:
        {
            (*drawn_card)++;

            player_list[player_id].Player_Loan_Interest_Rate = Round_Off((double)(player_list[player_id].Player_Loan_Interest_Rate) * 0.98);
            player_list[player_id].Player_Card_Stack[Interest_Rate_Cut].National_Card_Status = Card_Activated;
            player_list[player_id].Player_Card_Stack[Interest_Rate_Cut].Ending_Round = round_count + 15;
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Interest_Rate_Cut].Card_Name);
            break;
        }

        case Interest_Rate_Increase:
        {
            (*drawn_card)++;

            player_list[player_id].Player_Loan_Interest_Rate = Round_Off((double)(player_list[player_id].Player_Loan_Interest_Rate) * 1.02);
            player_list[player_id].Player_Card_Stack[Interest_Rate_Increase].National_Card_Status = Card_Activated;
            player_list[player_id].Player_Card_Stack[Interest_Rate_Increase].Ending_Round = round_count + 15;
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Interest_Rate_Increase].Card_Name);
            break;
        }

        case Tax_Amnesty:
        {
            (*drawn_card)++;

            for(int i = 0; i < Total_Players; i++)
            {
                player_list[i].Player_Cash += 2000;
            }
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Tax_Amnesty].Card_Name);
            break;
        }

        case Power_Failure:
        {
            (*drawn_card)++;

            player_list[player_id].Current_Boost.utility_Boost = 0.5;
            player_list[player_id].Player_Card_Stack[Power_Failure].National_Card_Status = Card_Activated;
            player_list[player_id].Player_Card_Stack[Power_Failure].Ending_Round = round_count + 3;
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Power_Failure].Card_Name);
        }

        case Foreign_Funding:
        {
            (*drawn_card)++;

            //commercial property
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Foreign_Funding].Card_Name);
            break;
        }

        case Port_Expansion:
        {
            (*drawn_card)++;

            for(int i = 0; i < SQ_Board_Size; i++)
            {
                if((board[i].Cell_Type == SQ_Type_Railway) &&
                    (board[i].Cell_Data.Railway.Railway_Owner) == (Owners_Property)player_id)
                {
                    board[i].Cell_Data.Railway.Base_Price = Round_Off((double)(board[i].Cell_Data.Railway.Base_Price) * 1.2);
                }
            }

            player_list[player_id].Player_Card_Stack[Port_Expansion].National_Card_Status = Card_Activated;
            player_list[player_id].Player_Card_Stack[Port_Expansion].Ending_Round = round_count + 15;
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Foreign_Funding].Card_Name);

            break;
        }

        case Festival_Season:
        {
            (*drawn_card)++;

            player_list[player_id].Current_Boost.Property_Boost = 50;
            player_list[player_id].Player_Card_Stack[Festival_Season].National_Card_Status = Card_Activated;
            player_list[player_id].Player_Card_Stack[Festival_Season].Ending_Round = round_count + 15;
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Festival_Season].Card_Name);

            break;
        }

        case Labour_Strike:
        {
            (*drawn_card)++;

            player_list[player_id].Player_Card_Stack[Labour_Strike].National_Card_Status = Card_Activated;
            player_list[player_id].Player_Card_Stack[Labour_Strike].Ending_Round = round_count + 2;
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Labour_Strike].Card_Name);

            break;
        }

        case Insurance_Discount:
        {
            (*drawn_card)++;

            player_list[player_id].Current_Boost.Insurance_Dis_Value = 0.8;
            player_list[player_id].Player_Card_Stack[Insurance_Discount].National_Card_Status = Card_Activated;
            player_list[player_id].Player_Card_Stack[Insurance_Discount].Ending_Round = round_count + 15;
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Insurance_Discount].Card_Name);

            break;
        }

        case Property_Revaluation:
        {
            (*drawn_card)++;

            Property_Group_Type chosen_group = None;

            if(player_list[player_id].Current_Boost.Random_Group == None)
            {
                chosen_group = (Property_Group_Type)(rand() % 8);
                player_list[player_id].Current_Boost.Random_Group = chosen_group;

                for(int i = 0; i < SQ_Board_Size; i++)
                {
                    if((board[i].Cell_Type == SQ_Type_Property) &&
                        (board[i].Cell_Data.Properties.Group == chosen_group))
                    {
                        board[i].Cell_Data.Properties.Base_Price = Round_Off((double)(board[i].Cell_Data.Properties.Base_Price) * 1.15);
                    }
                }
            }else{
                chosen_group = player_list[player_id].Current_Boost.Random_Group;
            }
            

            player_list[player_id].Player_Card_Stack[Property_Revaluation].National_Card_Status = Card_Activated;
            player_list[player_id].Player_Card_Stack[Property_Revaluation].Ending_Round = round_count + 15;
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Property_Revaluation].Card_Name);

            break;
        }

        case Currency_Depreciation:
        {
            (*drawn_card)++;

            for(int i = 0; i < SQ_Board_Size; i++)
            {
                if((board[i].Cell_Type == SQ_Type_Property) &&
                    (board[i].Cell_Data.Properties.Property_Owner == (Owners_Property)player_id))
                {
                    board[i].Cell_Data.Properties.House_Construction_Cost = Round_Off((double)(board[i].Cell_Data.Properties.House_Construction_Cost) * 1.1);
                    board[i].Cell_Data.Properties.Hotel_Construction_Cost = Round_Off((double)(board[i].Cell_Data.Properties.Hotel_Construction_Cost) * 1.1);
                }
            }

            player_list[player_id].Player_Card_Stack[Currency_Depreciation].National_Card_Status = Card_Activated;
            player_list[player_id].Player_Card_Stack[Currency_Depreciation].Ending_Round = round_count + 15;
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Currency_Depreciation].Card_Name);

            break;
        }

        case Government_Grant:
        {
            (*drawn_card)++;

            int random_chosen = (rand() % 4);

            player_list[random_chosen].Player_Cash += 5000; 
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Government_Grant].Card_Name);
            break;
        }

        case National_Disaster:
        {
            (*drawn_card)++;

            //prop damage
            printf("\n%s Has Drawn %s National Event Card\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[National_Disaster].Card_Name);
            break;
        }
        }

        
    }

} 


void National_Event_Card_Reset(square board[],Players player_list[],int player_id,int *drawn_card,int round_count,Economic *economy_status)
{
    for (int i = 0; i < 20; i++)
    {
        if(player_list[player_id].Player_Card_Stack[i].National_Card_Status == Card_Activated)
        {
            int card = i;

            switch ((National_Event_Card_Deck)card)
            {
            case Tourism_Hype:
            {
                if(player_list[player_id].Player_Card_Stack[Tourism_Hype].Ending_Round == round_count)
                {
                    player_list[player_id].Current_Boost.Property_Boost = 1;
                    player_list[player_id].Player_Card_Stack[Tourism_Hype].National_Card_Status = Card_Deactivated;
                    printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Tourism_Hype].Card_Name);
            
                }

                break;
            }
                
            case Fuel_Shortage:
            {
                if(player_list[player_id].Player_Card_Stack[Fuel_Shortage].Ending_Round == round_count)
                {
                    player_list[player_id].Current_Boost.Railway_Boost = 1;
                    player_list[player_id].Player_Card_Stack[Fuel_Shortage].National_Card_Status = Card_Deactivated;
                    printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Fuel_Shortage].Card_Name);
                }
                break;
            }

            case Heavy_Floods:
            {
                //to be implement
                printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Heavy_Floods].Card_Name);
                break;
            }

            case Political_Rally:
            {
                 if(player_list[player_id].Player_Card_Stack[Political_Rally].Ending_Round == round_count)
                {
                    board[player_list[player_id].Current_Boost.Closed_Property].Square_Status = Property_Open;
                    player_list[player_id].Current_Boost.Closed_Property = SQ_None;
                    player_list[player_id].Player_Card_Stack[Political_Rally].National_Card_Status = Card_Deactivated;
                    printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Political_Rally].Card_Name);
            
                }
                break;
            }

            case Stock_Market_Rise:
            {
                if(player_list[player_id].Player_Card_Stack[Stock_Market_Rise].Ending_Round == round_count)
                {
                    for(int i = 0; i < SQ_Board_Size; i++)
                    {
                        if(board[i].Cell_Type == SQ_Type_Property)
                        {
                            board[i].Cell_Data.Properties.Base_Price = Round_Off((double)(board[i].Cell_Data.Properties.Base_Price) * 1.1);
                        }
                    }

                    player_list[player_id].Player_Card_Stack[Stock_Market_Rise].National_Card_Status = Card_Deactivated;
                    printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Stock_Market_Rise].Card_Name);
                    
                }
                
                break;
            }

            case Economic_Downturn:
            {
                if(player_list[player_id].Player_Card_Stack[Economic_Downturn].Ending_Round == round_count)
                {
                    for(int i = 0; i < SQ_Board_Size; i++)
                    {
                        if(board[i].Cell_Type == SQ_Type_Property)
                    {
                        board[i].Cell_Data.Properties.Base_Price = Round_Off((double)(board[i].Cell_Data.Properties.Base_Price) * 1.15);
                    }
                    }
                    printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Economic_Downturn].Card_Name);
                }
                break;
            }

            case Housing_Subsidy_Card:
            {
                if(player_list[player_id].Player_Card_Stack[Housing_Subsidy_Card].Ending_Round == round_count)
                {
                    for(int i = 0; i < SQ_Board_Size; i++)
                    {
                        if((board[i].Cell_Type == SQ_Type_Property) &&
                            (board[i].Cell_Data.Properties.Property_Owner == (Owners_Property)player_id))
                        {
                            board[i].Cell_Data.Properties.House_Construction_Cost = Round_Off((double)(board[i].Cell_Data.Properties.House_Construction_Cost) * 1.3);
                        }
                    }

                    player_list[player_id].Player_Card_Stack[Housing_Subsidy_Card].National_Card_Status = Card_Deactivated;
                    printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Housing_Subsidy_Card].Card_Name);
                }
                break;
            }

            case Interest_Rate_Cut:
            {
                if(player_list[player_id].Player_Card_Stack[Interest_Rate_Cut].Ending_Round == round_count)
                {
                    player_list[player_id].Player_Loan_Interest_Rate = Round_Off((double)(player_list[player_id].Player_Loan_Interest_Rate) * 1.02);
                    player_list[player_id].Player_Card_Stack[Interest_Rate_Cut].National_Card_Status = Card_Deactivated;
                    printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Interest_Rate_Cut].Card_Name);
                }
                
                break;
            }

            case Interest_Rate_Increase:
            {
                if(player_list[player_id].Player_Card_Stack[Interest_Rate_Increase].Ending_Round == round_count)
                {
                    player_list[player_id].Player_Loan_Interest_Rate = Round_Off((double)(player_list[player_id].Player_Loan_Interest_Rate) * 0.98);
                    player_list[player_id].Player_Card_Stack[Interest_Rate_Increase].National_Card_Status = Card_Deactivated;
                    printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Interest_Rate_Increase].Card_Name);
                }
                
                break;
            }

            case Tax_Amnesty:
            {
                printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Tax_Amnesty].Card_Name);
                return;
                break;
            }

            case Power_Failure:
            {
                if(player_list[player_id].Player_Card_Stack[Power_Failure].Ending_Round == round_count)
                {
                    player_list[player_id].Current_Boost.utility_Boost = 1;
                    player_list[player_id].Player_Card_Stack[Power_Failure].National_Card_Status = Card_Deactivated;
                    printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Power_Failure].Card_Name);
                }
                break;
            }

            case Foreign_Funding:
            {
                printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Foreign_Funding].Card_Name);
                //tbe
                break;
            }

            case Port_Expansion:
            {
                if(player_list[player_id].Player_Card_Stack[Port_Expansion].Ending_Round == round_count)
                {
                    for(int i = 0; i < SQ_Board_Size; i++)
                    {
                        if((board[i].Cell_Type == SQ_Type_Railway) &&
                        (board[i].Cell_Data.Railway.Railway_Owner) == (Owners_Property)player_id)
                        {
                            board[i].Cell_Data.Railway.Base_Price = Round_Off((double)(board[i].Cell_Data.Railway.Base_Price) * 0.8);
                        }
                    }
                }

                player_list[player_id].Player_Card_Stack[Port_Expansion].National_Card_Status = Card_Deactivated;
                printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Port_Expansion].Card_Name);


                break;
            }

            case Festival_Season:
            {
                if(player_list[player_id].Player_Card_Stack[Festival_Season].Ending_Round == round_count)
                {
                    player_list[player_id].Current_Boost.Property_Boost = 1;
                    player_list[player_id].Player_Card_Stack[Festival_Season].National_Card_Status = Card_Deactivated;
                    printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Festival_Season].Card_Name);
                }
                break;
            }

            case Labour_Strike:
            {
                if(player_list[player_id].Player_Card_Stack[Labour_Strike].Ending_Round == round_count)
                
                {
                    player_list[player_id].Player_Card_Stack[Labour_Strike].National_Card_Status = Card_Deactivated;
                    printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Labour_Strike].Card_Name);
                }
                break;
            }

            case Insurance_Discount:
            {
                if(player_list[player_id].Player_Card_Stack[Insurance_Discount].Ending_Round == round_count)
                {
                    player_list[player_id].Current_Boost.Insurance_Dis_Value = 1.0;
                    player_list[player_id].Player_Card_Stack[Insurance_Discount].National_Card_Status = Card_Deactivated;
                    printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Insurance_Discount].Card_Name);
                }
                break;
            }

            case Property_Revaluation:
            {
                if(player_list[player_id].Player_Card_Stack[Property_Revaluation].Ending_Round == round_count)
                {
                    for(int i = 0; i < SQ_Board_Size; i++)
                    {
                        if((board[i].Cell_Type == SQ_Type_Property) &&
                            (board[i].Cell_Data.Properties.Group == player_list[player_id].Current_Boost.Random_Group))
                        {
                            board[i].Cell_Data.Properties.Base_Price = Round_Off((double)(board[i].Cell_Data.Properties.Base_Price) * 0.85);
                        }
                    }

                    player_list[player_id].Player_Card_Stack[Property_Revaluation].National_Card_Status = Card_Deactivated;
                    printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Property_Revaluation].Card_Name);
                }
                break;
            }

            case Currency_Depreciation:
            {
                if(player_list[player_id].Player_Card_Stack[Currency_Depreciation].Ending_Round == round_count)
                {
                    for(int i = 0; i < SQ_Board_Size; i++)
                    {
                        if((board[i].Cell_Type == SQ_Type_Property) &&
                            (board[i].Cell_Data.Properties.Property_Owner == (Owners_Property)player_id))
                        {
                            board[i].Cell_Data.Properties.House_Construction_Cost = Round_Off((double)(board[i].Cell_Data.Properties.House_Construction_Cost) * 0.9);
                            board[i].Cell_Data.Properties.Hotel_Construction_Cost = Round_Off((double)(board[i].Cell_Data.Properties.Hotel_Construction_Cost) * 0.9);
                        }
                    }

                    player_list[player_id].Player_Card_Stack[Currency_Depreciation].National_Card_Status = Card_Deactivated;
                    printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Currency_Depreciation].Card_Name);
                }
                break;
            }

            case Government_Grant:
            {
                printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[Government_Grant].Card_Name);
                return;
                break;
            }

            case National_Disaster:
            {
                printf("\n%s Drawned %s National Event Card Weared Off\n",player_list[player_id].Player_Name,player_list[player_id].Player_Card_Stack[National_Disaster].Card_Name);
                return;
                break;
            }
            }
        }
    }

}


