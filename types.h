#ifndef TYPES_H
#define TYPES_H

typedef enum {
    Brown = 1,
    Light_Blue,
    Pink,
    Orange,
    Red,
    Yellow,
    Green,
    Dark_Blue}Property_Group_Type;

typedef enum {

    Owner_Bank,
    Owner_Aggressive_Investor,
    Owner_Conservative_Banker,
    Owner_Risk_Taker,
    Owner_Opportunistic_Trader

}Owners_Property;

typedef enum{
    Mortgage_Unavailable = -1,
    Unmortgaged,
    Mortgaged
}Mortgage_Status;


typedef enum{

    Sri_Lanka_Insurance,
    Ceylinco_Insurance

}Insurance_Companies;


typedef enum{

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

    SQ_GO = 0,
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


typedef struct{

    Property_Group_Type Group;
    int Base_Price;
    int Market_Price;
    int Base_Rental;
    int House_Construction_Cost;
    int Hotel_Construction_Cost;
    Owners_Property Property_Owner;
    short Number_of_Buildings;
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

}Railway_Stations;


typedef struct{

    Utility_Names Company;
    Owners_Property Company_Owner;

}Utility_Companies;


typedef struct{
    
    char Bank_Name[24];

}Bank;

typedef struct{

    char Square_Name[50];
    Square_ID Location_ID;
    Square_type Cell_Type;
    
    union{
        Property Properties;
        Railway_Stations Railway;
        Utility_Companies Utility;
        Bank Bank;
    }Cell_Data;

    Insurance Insurance_Details;

}square;






















#endif