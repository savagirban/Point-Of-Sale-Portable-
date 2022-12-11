#define SPACE 32
typedef struct salesman
{ int smid;
  char* nume;
  char* prenume;
  unsigned int cnp[14];
  char *password;
}salesman;
typedef struct date
{ int zi;
  int luna;
  int an;
}date;
int slm;
typedef struct market
{ char *denumire;
  char * adresa;
  float profit;
  char * admin;
  char* manager;
}market;
typedef struct producator
{   
    char * denumire;
}producator;

typedef struct produs
{ char * productr;
  int idctg;
  int pid;
  char* denumire;
  float pret;
  char* barcode;
}produs;
typedef struct categorie
{ char* denumire;
   produs * prds;
}categorie;
 struct inventar
{ produs prod;
  int qty;
  produs * next;
}inventar;


typedef struct sale
{ salesman* sm;
  date data;
  int np;
  produs *prodlist;
  float total;
  char type;
  int sid;
}sale;

int MarketData,Salermans,lprft,Products,qty[50], CKT=-1, ID;
int Plata;
salesman  salesmanlist[6];
produs depo[50];
market Mk;