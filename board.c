#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "types.h"




void Board_Initialization(square board[])
{

    board[SQ_GO] = (square){
        .Square_Name = "GO",
        .Location_ID = SQ_GO,
        .Cell_Type = SQ_Type_Start,
        
    };


        board[SQ_PETTAH] = (square){
        .Square_Name = "Pettah",
        .Location_ID = SQ_PETTAH,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Brown,
                .Base_Price = 1500,
                .Market_Price = 0,
                .Base_Rental = 100,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
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
        
    };

    
        board[SQ_MARADANA] = (square){
        .Square_Name = "Maradana",
        .Location_ID = SQ_MARADANA,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Brown,
                .Base_Price = 1800,
                .Market_Price = 0,
                .Base_Rental = 120,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
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
        

    };

        board[SQ_COLOMBO_FORT_RAILWAY_STATION] = (square){
        .Square_Name = "Colombo Fort Railway Station",
        .Location_ID = SQ_COLOMBO_FORT_RAILWAY_STATION,
        .Cell_Type = SQ_Type_Railway,
        .Cell_Data = {
            .Railway = {
                .Name = Colombo_Fort_Railway_Station,
                .Railway_Owner = Owner_Bank,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0,
                .Base_Price = 999,
                .Base_Rental = 250 
            }
        },
        
    };

        board[SQ_BAMBALAPITIYA] = (square){
        .Square_Name = "Bambalapitiya",
        .Location_ID = SQ_BAMBALAPITIYA,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Light_Blue,
                .Base_Price = 2500,
                .Market_Price = 0,
                .Base_Rental = 180,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };

      
        board[SQ_NATIONAL_EVENT_CARD_1] = (square){
        .Square_Name = "National Event Card",
        .Location_ID = SQ_NATIONAL_EVENT_CARD_1,
        .Cell_Type = SQ_Type_Event,
        
    };


        board[SQ_Wellawatte] = (square){
        .Square_Name = "Wellawatte",
        .Location_ID = SQ_Wellawatte,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Light_Blue,
                .Base_Price = 2700,
                .Market_Price = 0,
                .Base_Rental = 200,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };

        board[SQ_Mount_Lavinia] = (square){
        .Square_Name = "Mount Lavinia",
        .Location_ID = SQ_Mount_Lavinia,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Light_Blue,
                .Base_Price = 3000,
                .Market_Price = 0,
                .Base_Rental = 220,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_Jail] = (square){
        .Square_Name = "Jail / Just Visiting",
        .Location_ID = SQ_Jail,
        .Cell_Type = SQ_Type_Special,
        
    };


        board[SQ_Nugegoda] = (square){
        .Square_Name = "Nugegoda",
        .Location_ID = SQ_Nugegoda,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Pink,
                .Base_Price = 3500,
                .Market_Price = 0,
                .Base_Rental = 260,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_CEB] = (square){
        .Square_Name = "Ceylon Electricity Board",
        .Location_ID = SQ_CEB,
        .Cell_Type = SQ_Type_Utility,
        .Cell_Data ={
            .Utility = {
                .Company = CEB,
                .Company_Owner = Owner_Bank,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0,
                .Base_Price = 999,
                .Base_Rental = 99 

            }
        },
        
    };


        board[SQ_Maharagama] = (square){
        .Square_Name = "Maharagama",
        .Location_ID = SQ_Maharagama,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Pink,
                .Base_Price = 3800,
                .Market_Price = 0,
                .Base_Rental = 280,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_Kottawa] = (square){
        .Square_Name = "Kottawa",
        .Location_ID = SQ_Kottawa,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Pink,
                .Base_Price = 4000,
                .Market_Price = 0,
                .Base_Rental = 300,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_Kandy_Railway_Station] = (square){
        .Square_Name = "Kandy Railway Station",
        .Location_ID = SQ_Kandy_Railway_Station,
        .Cell_Type = SQ_Type_Railway,
        .Cell_Data = {
            .Railway = {
                .Name = Kandy_Railway_Station,
                .Railway_Owner = Owner_Bank,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0,
                .Base_Price = 999,
                .Base_Rental = 250 
            }
        },
        
    };


        board[SQ_Negombo] = (square){
        .Square_Name = "Negombo",
        .Location_ID = SQ_Negombo,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Orange,
                .Base_Price = 4500,
                .Market_Price = 0,
                .Base_Rental = 350,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_Sri_Lanka_Insurance] = (square){
        .Square_Name = "Sri Lanka Insurance",
        .Location_ID = SQ_Sri_Lanka_Insurance,
        .Cell_Type = SQ_Type_Insurance,
        
    };


        board[SQ_Katunayake] = (square){
        .Square_Name = "Katunayake",
        .Location_ID = SQ_Katunayake,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Orange,
                .Base_Price = 4700,
                .Market_Price = 0,
                .Base_Rental = 370,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_Ja_Ela] = (square){
        .Square_Name = "Ja-Ela",
        .Location_ID = SQ_Ja_Ela,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Orange,
                .Base_Price = 5000,
                .Market_Price = 0,
                .Base_Rental = 400,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_Free_Parking] = (square){
        .Square_Name = "Free_Parking",
        .Location_ID = SQ_Free_Parking,
        .Cell_Type = SQ_Type_Special,
        
    };


        board[SQ_Kandy_City] = (square){
        .Square_Name = "Kandy City",
        .Location_ID = SQ_Kandy_City,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Red,
                .Base_Price = 5500,
                .Market_Price = 0,
                .Base_Rental = 450,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_National_Event_Card_2] = (square){
        .Square_Name = "National Event Card",
        .Location_ID = SQ_National_Event_Card_2,
        .Cell_Type = SQ_Type_Event,
        

    };


        board[SQ_Peradeniya] = (square){
        .Square_Name = "Peradeniya",
        .Location_ID = SQ_Peradeniya,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Red,
                .Base_Price = 5800,
                .Market_Price = 0,
                .Base_Rental = 480,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_Katugastota] = (square){
        .Square_Name = "Katugastota",
        .Location_ID = SQ_Katugastota,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Light_Blue,
                .Base_Price = 6000,
                .Market_Price = 0,
                .Base_Rental = 500,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_Galle_Railway_Station] = (square){
        .Square_Name = "Galle Railway Station",
        .Location_ID = SQ_Galle_Railway_Station,
        .Cell_Type = SQ_Type_Railway,
        .Cell_Data = {
            .Railway = {
                .Name = Galle_Railway_Station,
                .Railway_Owner = Owner_Bank,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0,
                .Base_Price = 999,
                .Base_Rental = 250 
            }
        },
        
    };


        board[SQ_Galle_Fort] = (square){
        .Square_Name = "Galle Fort",
        .Location_ID = SQ_Galle_Fort,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Yellow,
                .Base_Price = 6500,
                .Market_Price = 0,
                .Base_Rental = 600,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_Unawatuna] = (square){
        .Square_Name = "Unawatuna",
        .Location_ID = SQ_Unawatuna,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Yellow,
                .Base_Price = 6800,
                .Market_Price = 0,
                .Base_Rental = 620,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_NWSDB] = (square){
        .Square_Name = "National Water Supply And Drainage Board",
        .Location_ID = SQ_NWSDB,
        .Cell_Type = SQ_Type_Utility,
        .Cell_Data ={
            .Utility = {
                .Company = NWSDB,
                .Company_Owner = Owner_Bank,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0,
                .Base_Price = 999,
                .Base_Rental = 99 

            }
        },
        
    };


        board[SQ_Hikkaduwa] = (square){
        .Square_Name = "Hikkaduwa",
        .Location_ID = SQ_Hikkaduwa,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Yellow,
                .Base_Price = 7000,
                .Market_Price = 0,
                .Base_Rental = 650,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_Go_To_Jail] = (square){
        .Square_Name = "Go to Jail",
        .Location_ID = SQ_Go_To_Jail,
        .Cell_Type = SQ_Type_Special,
        
    };


        board[SQ_Jaffna_Town] = (square){
        .Square_Name = "Jaffna Town",
        .Location_ID = SQ_Jaffna_Town,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Green,
                .Base_Price = 8000,
                .Market_Price = 0,
                .Base_Rental = 750,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_Nallur] = (square){
        .Square_Name = "Nallur",
        .Location_ID = SQ_Nallur,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Green,
                .Base_Price = 8300,
                .Market_Price = 0,
                .Base_Rental = 780,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_Ceylinco_Insurance] = (square){
        .Square_Name = "Ceylinco Insurance",
        .Location_ID = SQ_Ceylinco_Insurance,
        .Cell_Type = SQ_Type_Insurance,
        
        
    };


        board[SQ_Trincomalee] = (square){
        .Square_Name = "Trincomalee",
        .Location_ID = SQ_Trincomalee,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Green,
                .Base_Price = 8500,
                .Market_Price = 0,
                .Base_Rental = 800,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_Jaffna_Railway_Station] = (square){
        .Square_Name = "Jaffna Railway Station",
        .Location_ID = SQ_Jaffna_Railway_Station,
        .Cell_Type = SQ_Type_Railway,
        .Cell_Data = {
            .Railway = {
                .Name = Jaffna_Railway_Station,
                .Railway_Owner = Owner_Bank,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0,
                .Base_Price = 999,
                .Base_Rental = 250 
            }
        },
        
    };


        board[SQ_National_Event_Card_3] = (square){
        .Square_Name = "National Event Card",
        .Location_ID = SQ_National_Event_Card_3,
        .Cell_Type = SQ_Type_Special,
        
    };


        board[SQ_Nuwara_Eliya] = (square){
        .Square_Name = "Nuwara Eliya",
        .Location_ID = SQ_Nuwara_Eliya,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Dark_Blue,
                .Base_Price = 10000,
                .Market_Price = 0,
                .Base_Rental = 1000,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };


        board[SQ_Bank_of_Ceylon] = (square){
        .Square_Name = "Bank of Ceylon",
        .Location_ID = SQ_Bank_of_Ceylon,
        .Cell_Type = SQ_Type_Bank,
        
    };


        board[SQ_Galle_Face] = (square){
        .Square_Name = "Galle Face",
        .Location_ID = SQ_Galle_Face,
        .Cell_Type = SQ_Type_Property,
        .Cell_Data = {
            .Properties = {
                .Group = Dark_Blue,
                .Base_Price = 12000,
                .Market_Price = 0,
                .Base_Rental = 1200,
                .House_Construction_Cost = 0,
                .Hotel_Construction_Cost = 0,
                .Property_Owner = Owner_Bank,
                .Number_of_Hotels = 0,
                .Number_of_Houses = 0,
                .Mortgage = Unmortgaged,
                .Mortgage_Value = 0
            }
        },

            .Insurance_Details = {
            .Name = Not_choosen,
            .Package = Not_Insured
        }
    };
}

  

