#include <stdio.h>
#include <string.h>
#include "types.h"

square board[SQ_Board_Size];

void Board_Initialization(void){

    board[SQ_GO] = (square){
        .Square_Name = "GO",
        .Location_ID = SQ_GO,
        .Cell_Type = SQ_Type_Start,
        .Cell_Data = {
            .Properties = {
                .Group = None,
                .Base_Price = 0,
                .Market_Price = 0,
                .Base_Rental = 0,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = None,
                .Number_of_Buildings = 0,
                .Mortgage = Mortgage_Unavailable,
                .Mortgage_Value = 0
            }
        },

        .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insurable
        }

    };


        board[SQ_PETTAH] = (square){
        .Square_Name = "Pettah",
        .Location_ID = SQ_PETTAH,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Brown,
                .Base_Price = 0,
                .Market_Price = 0,
                .Base_Rental = 0,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = None,
                .Number_of_Buildings = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

        .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }

    };

        board[SQ_COMMUNITY_DEVELOPMENT_FUND] = (square){
        .Square_Name = "Community Development Fund",
        .Location_ID = SQ_COMMUNITY_DEVELOPMENT_FUND,
        .Cell_Type = SQ_Type_Event,
        .Cell_Data = {
            .Properties = {
                .Group = None,
                .Base_Price = 0,
                .Market_Price = 0,
                .Base_Rental = 0,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = None,
                .Number_of_Buildings = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

        .Insurance_Details = {
            .Name = Sri_Lanka_Insurance,
            .Package = Not_Insured
        }
    };

    
        board[SQ_MARADANA] = (square){
        .Square_Name = "Maradana",
        .Location_ID = SQ_MARADANA,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Brown,
                .Base_Price = 0,
                .Market_Price = 0,
                .Base_Rental = 0,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = None,
                .Number_of_Buildings = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };

        board[SQ_INCOME_TAX] = (square){
        .Square_Name = "Income_Tax",
        .Location_ID = SQ_INCOME_TAX,
        .Cell_Type = SQ_Type_Tax,
        .Cell_Data = {
            .Properties = {
                .Group = None,
                .Base_Price = 0,
                .Market_Price = 0,
                .Base_Rental = 0,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = None,
                .Number_of_Buildings = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }

    };

        board[SQ_COLOMBO_FORT_RAILWAY_STATION] = (square){
        .Square_Name = "Colombo Fort Railway Station",
        .Location_ID = SQ_COLOMBO_FORT_RAILWAY_STATION,
        .Cell_Type = SQ_Type_Railway,
        .Cell_Data = {
            .Properties = {
                .Group = None,
                .Base_Price = 0,
                .Market_Price = 0,
                .Base_Rental = 0,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = None,
                .Number_of_Buildings = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };

        board[SQ_] = (square){
        .Square_Name = "Community Development Fund",
        .Location_ID = SQ_MARADANA,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Brown,
                .Base_Price = 0,
                .Market_Price = 0,
                .Base_Rental = 0,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = None,
                .Number_of_Buildings = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };








};