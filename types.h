#ifndef TYPES_H
#define TYPES_H

#define Total_Players 4
#define Probability_Of_Landing (1.0/40.0)
#define Rounds_ROI 20
#define true 1
#define false 0



typedef enum {
    
    None = -1,
    Brown,
    Light_Blue,
    Pink,
    Orange,
    Red,
    Yellow,
    Green,
    Dark_Blue,
    Other}Property_Group_Type;

typedef enum {

   
    Owner_Aggressive_Investor,
    Owner_Conservative_Banker,
    Owner_Risk_Taker,
    Owner_Opportunistic_Trader,
    Owner_None,
    Owner_Bank,

}Owners_Property;

typedef enum{
    Mortgage_Unavailable = -1,
    Unmortgaged,
    Mortgaged
}Mortgage_Status;


typedef enum{

    Not_choosen,
    Sri_Lanka_Insurance,
    Ceylinco_Insurance

}Insurance_Companies;


typedef enum{

    Not_Insured,
    Basic_Property_Insurance,
    Comprehensive_Insurance,
    Business_Interruption_Insurance,
    Basic_Property_Insurance_Premium,
    Comprehensive_Insurance_Premium,
    Business_Interruption_Insurance_Premium

}Insurance_Packages;


typedef enum{

    Colombo_Fort_Railway_Station,
    Kandy_Railway_Station,
    Jaffna_Railway_Station,
    Galle_Railway_Station

}Railway_Names;


typedef enum{

    CEB,
    NWSDB,

}Utility_Names;


typedef enum{

    SQ_None = -1,
    SQ_GO,
    SQ_PETTAH,
    SQ_COMMUNITY_DEVELOPMENT_FUND,
    SQ_MARADANA,
    SQ_INCOME_TAX,
    SQ_COLOMBO_FORT_RAILWAY_STATION,
    SQ_BAMBALAPITIYA,
    SQ_NATIONAL_EVENT_CARD_1,
    SQ_Wellawatte,
    SQ_Mount_Lavinia,
    SQ_Jail,
    SQ_Nugegoda,
    SQ_CEB, //CEYLON ELECTRICITY BOARD
    SQ_Maharagama,
    SQ_Kottawa,
    SQ_Kandy_Railway_Station,
    SQ_Negombo,
    SQ_Sri_Lanka_Insurance,
    SQ_Katunayake,
    SQ_Ja_Ela,
    SQ_Free_Parking,
    SQ_Kandy_City,
    SQ_National_Event_Card_2,
    SQ_Peradeniya,
    SQ_Katugastota,
    SQ_Galle_Railway_Station,
    SQ_Galle_Fort,
    SQ_Unawatuna,
    SQ_NWSDB, //NATIONAL WATER SUPPLY
    SQ_Hikkaduwa,
    SQ_Go_To_Jail,
    SQ_Jaffna_Town,
    SQ_Nallur,
    SQ_Ceylinco_Insurance,
    SQ_Trincomalee,
    SQ_Jaffna_Railway_Station,
    SQ_National_Event_Card_3,
    SQ_Nuwara_Eliya,
    SQ_Bank_of_Ceylon,
    SQ_Galle_Face,
    SQ_Board_Size = 40

}Square_ID;


typedef enum{

    SQ_Type_Start,
    SQ_Type_Property,
    SQ_Type_Tax,
    SQ_Type_Event,
    SQ_Type_Railway,
    SQ_Type_Special,
    SQ_Type_Insurance,
    SQ_Type_Utility,
    SQ_Type_Bank


}Square_type;

typedef enum{

    Aggressive_Investor,
    Conservative_Banker,
    Risk_Taker,
    Opportunistic_Trader
    
}Player_Type;

typedef enum{

    No_Loans,
    Have_Loans

}Player_Loan;

typedef enum{

    Bankrupt = -1,
    Not_Bankrupt
}Player_Bankrupt;

typedef enum{

    In_Jail = -1,
    Not_In_Jail,
}Player_Jail;

typedef enum{

    Not_Passed = -1,
    Passed_Go,
}Player_Go;

typedef enum{

    Couldnt_Buy = -2,
    Didnt_Buy,
    No_Auctions,
    Bought,
    Player_Selling,
    Bank

}Auction;

typedef enum{

    No = -1,
    Yes,
}Player_Choice;

typedef enum{
    Recession,
    Inflation,
    Normal
}Economic;

typedef enum{
    Housing_Subsidy,
}Government_Regulations;

typedef enum{

    Not_Bidding,
    Bidding

}Player_Bid;



typedef struct{

    Property_Group_Type Group;
    int Base_Price;
    int Market_Price;
    int Base_Rental;
    int House_Construction_Cost;
    int Hotel_Construction_Cost;
    Owners_Property Property_Owner;
    short Number_of_Houses;
    short Number_of_Hotels;
    Mortgage_Status Mortgage;
    int Mortgage_Value;

}Property;


typedef struct{
    
    Insurance_Companies Name;
    Insurance_Packages Package;

}Insurance;


typedef struct{

    Railway_Names Name;
    Owners_Property Railway_Owner;
    Mortgage_Status Mortgage;
    int Mortgage_Value;
    int Base_Price;
    int Base_Rental;

}Railway_Stations;


typedef struct{

    Utility_Names Company;
    Owners_Property Company_Owner;
    Mortgage_Status Mortgage;
    int Mortgage_Value;
    int Base_Price;
    int Base_Rental;

}Utility_Companies;




typedef struct{

    char Square_Name[50];
    Square_ID Location_ID;
    Square_type Cell_Type;
    
    union{
        Property Properties;
        Railway_Stations Railway;
        Utility_Companies Utility;
        
    }Cell_Data;

    Insurance Insurance_Details;

}square;

typedef struct {
    
    char Player_Name[24];
    Player_Type Player_ID;
    //Square_ID Player_Owns[30];
    int Player_Cash;
    int Player_Assets;
    Player_Loan Loan_status;
    int Player_Loan;
    int Player_Tax_Due;
    Square_ID Player_Position;
    short Player_Roll_Order;
    short Temp_Dice_Value;
    short Total_Dice_Value;
    Property_Group_Type Has_Partial_Monopoly[9];
    Property_Group_Type Has_Monopoly[9];
    Player_Bankrupt Is_Bankrupt;
    Player_Jail Jail_Status;
    Player_Bid Bidding_Status;
    int Jail_Counter;
    Player_Go Player_Passed_Go;
    


}Players;

typedef struct {

    int Total_No_Prop_Owned;
    int Net_Worth;
    int No_of_Hotels;
    int Outstanding_Loan;
    int Railways_Owned;

}Player_Status;

typedef struct{

    int Dice_Sum;
    int Is_Double;
}Dice_Type;


void Board_Initialization(square board[]);
//void Value_Sort(int arr[],int size);
void Player_Initialization(Players Player_List[]);
Dice_Type Dice_Roll(void);
void Start_Game(void);
Auction Player_Buys_Property(Players player_list[], square board[], int player_id,Economic economic_status);
void Player_Pays_Rent(Players player_list[],square board[],int player_id,Auction *auction_status,short final_order[],Economic econ_status);
Player_Status Player_Assessing(Players player_list[],square board[],int player_id);
void Player_Builds(Players player_list[],square board[],int player_id,Economic economic_status,Government_Regulations current_regulations);
void Player_Monopoly_Count(Players player_list[],square board[]);
int Player_In_Jail(Players player_list[],square board[],int player_id,int *turn_count,Dice_Type dice);
void Player_Pays_Tax(Players player_list[],square board[],int player_id,double income_tax_rate);
int Round_Off(double value);
int Players_Bid(Players player_list[],square bidding_property,int player_id,int *highest_bid,Economic econ_status);
void Property_Auctions(Players player_list[],square board[],int player_id,int auction_status,short final_order[],Economic Econ_Status);
int Game_Over_Check(Players player_list[],int *game_winner);







#endif