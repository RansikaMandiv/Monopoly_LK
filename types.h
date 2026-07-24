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

    None = -1,
    Bank_of_Ceylon,
    Aggressive_Investor,
    Conservative_Banker,
    Risk_Taker,
    Opportunistic_Trader

}Owners_Property;

typedef enum{
    Cant_Be_Mortgaged = -1,
    Unmortgaged,
    Mortgaged
}Mortgage_Status;



typedef struct{

    int Base_Price;
    int Market_Price;
    int Base_Rental;
    int House_Construction_Cost;
    int Hotel_Construction_Cost;
    Owners_Property Property_Owner;
    short Number_of_Buildings;

}Property;


typedef struct{

Mortgage_Status Status;
int Mortgage_Value; 

}Mortgage;


typedef struct{

}Insurance;

typedef struct{

    char Square_Name[50];
    short Square_ID;
    Property Properties;
    Mortgage Type;
}square;






















#endif