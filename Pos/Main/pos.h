#include <stdio.h>
#include <stdlib.h>
#include "dcl.h"
#include "files.h"
void SlPrint(sale *);
void getMData();
char* sscan();
void Init();
void InventoryInit();
void SalesmanInit();
void qtyset()
{
    int i;
    for(i=0;i<50;i++)qty[i]=0;
}
int slen(char*p)
{
    int i=0;
    while (p[i]!='\0')
    {
        i++;
    }
    return i;
    
}
int cslen(const char*p)
{
    int i=0;
    while (p[i]!='\0')
    {
        i++;
    }
    return i;
    
}
void space(int n)
{
    while(n--)putchar(' ');
}
void fspace(int n,FILE* fp)
{
    while(n--)putc(' ',fp);
}
char* sscan()
{ char *p;
    p= (char*) malloc(sizeof(char));
    p[0]='\0';
    int i=0,c;
    while ((c=getchar())!='\n'&&c!=EOF)
    { p = (char*) realloc(p,sizeof(char)*(i+2)); 
      p[i]=(char)c;
      p[i+1]='\0';
      i++;
    }
    return p;
    
}
char* fscan(FILE *fp)
{ char *p;
    p= (char*) malloc(sizeof(char));
    p[0]='\0';
    int i=0,c;
    while ((c=getc(fp))!='\n'&&c!=EOF)
    { p = (char*) realloc(p,sizeof(char)*(i+2)); 
      p[i]=(char)c;
      p[i+1]='\0';
      i++;
    }
    return p;
    
}

void Init()
{ FILE* fp;
  fp = fopen("./DB/config.txt","a+");
  fscanf(fp,"%d",&MarketData);
  fscanf(fp,"%d",&Salermans);
  fscanf(fp,"%d",&Products);
  if(!MarketData){getMData();}
  //Salermans =1;
  InventoryInit();
  SalesmanInit();
  fclose(fp);
}
void getMData()
{ system("cls");
  char *p;
  FILE *fp;
  fp= fopen("./DB/market.txt","w");
  printf("______________________\n");
  printf("Denumire magazin:");
     p=sscan();
  fprintf(fp,"%s\n",p);
    Mk.denumire=p;
    free(p);
  printf("\nAdresa:");
  p=sscan();
  fprintf(fp,"%s\n",p);
  Mk.adresa=p;
  free(p);
  printf("\nAdministrator:");
  p=sscan();
  fprintf(fp,"%s\n",p);
  Mk.admin=p;
  free(p);
  printf("\nManager:");
  p=sscan();
  fprintf(fp,"%s\n",p);
  Mk.manager=p;
  free(p);
  fclose(fp);
  replacel("./DB/config.txt","1",0);

}
void InventoryInit()
{ int i;
  FILE* fp;

  fp=fopen("./DB/depo.txt","r+");
  for(i=0;i<Products;i++)
  { 
    depo[i].productr= fscan(fp);
    fscanf(fp,"%d",&depo[i].idctg);
     fscanf(fp,"%d",&depo[i].pid);
     getc(fp);
     depo[i].denumire = fscan(fp);
     fscanf(fp,"%f",&depo[i].pret);
     getc(fp);
     depo[i].barcode=fscan(fp);
     
       
  }
 fclose(fp);
}
void MarketDataGet()
{int i;
  FILE* fp;
  fp =fopen("./DB/market.txt","r+");
  Mk.denumire = fscan(fp);
  Mk.adresa = fscan(fp);
  Mk.manager = fscan(fp);
  Mk.admin =fscan(fp);
  fclose(fp);

}
void SalesmanInit()
{ int i;
  FILE* fp;
  fp=fopen("./DB/Salesman.txt","r+");
  for(i=0;i<Salermans;i++)
  {//printf("I ii :%d si Salerman :%d",i,Salermans);
    fscanf(fp,"%d",&salesmanlist[i].smid);
    getc(fp);
    salesmanlist[i].nume=fscan(fp); 
    salesmanlist[i].prenume=fscan(fp);   
    fscanf(fp,"%d",&salesmanlist[i].cnp);
    getc(fp);
    salesmanlist[i].password=fscan(fp); 
       
  }
 fclose(fp);
}
int scmp(char*s, char*p)
{
    int i=0;
    //if(s=="\0"||p=="\0")return -2;
    //if(s==NULL||p==NULL)return -1;
    while (s[i]!='\0'&&p[i]!='\0')
    {
       if(p[i]!=s[i])return 0;
       i++;
    }
     if(p[i]!=s[i])return 0;
    return 1;
}
salesman* Logvalid(int id, char* p)
{ int i;
    for ( i = 0; i < Salermans; i++)
    { if(salesmanlist[i].smid==id)
         { 
            if(scmp(p,salesmanlist[i].password)==1)return &salesmanlist[i];
         }
    }
 return NULL;
    
}
int NSale(salesman* );
void LogMenu()
{ int id,lin,opt;
char *pass;
    system("cls");
    printf("<<<<<<<<<<<<<< LOG IN >>>>>>>>>>>>>>>>\n");
    printf("ID:");
    scanf("%d",&id);
    printf("\nPassword:");
    getchar();
    pass=sscan();
    salesman* sl;
    sl=Logvalid(id,pass);
    lin =1;
    if(sl!=NULL)
    {
        while (lin)
        { system("cls");
          printf("<<<<<<<<<<<<< Buna, %s >>>>>>>>>>>>\n",sl->prenume);
          printf("1.Vanzare noua\n");
          printf("2.Iesi din tura\n");
          printf("_____________________________________\n");
          printf("optiunea dvs:");
          scanf("%d",&opt);
          switch (opt)
          {
          case 1:
            NSale(sl);
            break;
          case 2:lin=0; break;
          default:printf("Nu exista!");system("pause");
            break;
          }
        }
        
    }
    else{printf("Wrong user!");
    system("pause");}
}
produs * BarodeProd(char* b)
{
    int i=0;
    for(i=0;i<Products;i++)
    {
        if(scmp(depo[i].barcode,b)==1){return &depo[i];}
        
    }
    return NULL;
}
void Discount(sale *s)
{

}
produs * FindByID(int id)
{
  int i;
   for(i=0;i<Products;i++)
   {
      if(depo[i].pid==id)return &depo[i];
   }
   return NULL;
}
int ListFind(sale *k,produs *p)
{
  int i=0;
  for(i=0;i<k->np;i++)
  {
    if(k->prodlist[i].pid==p->pid)return i;
  }
  return -1;
}
int AddToCart(sale *k, produs *p)
{ int i,q; 
sale s;
s=*k;
 
  SlPrint(k);
   if(q<=0)return 0;
 if(p!=NULL)
 { printf("\nqty:");
        scanf("%d",&q);
 if(ListFind(k,p)>=0)
      { qty[ListFind(k,p)]+=q;
      }
      else{ 
        s.prodlist= (produs*) realloc(s.prodlist,sizeof(produs)*(s.np+1));
        s.prodlist[s.np]=*p ;s.np++;
        qty[s.np-1]=q;
        k->data=s.data;
        k->np=s.np;
        k->prodlist=s.prodlist; 
        SlPrint(k);
      }
 }     
 
    return 1;
}
void PrintProdList()
{
  system("cls");
  int i=0;
  printf("____________Lista Produse____________\n");
  for(i=0;i<Products;i++)
  {
    printf("%d.%s %s id:%d barcode:%s  pret:%.2f.\n",i+1,depo[i].denumire,depo[i].productr,depo[i].pid, depo[i].barcode,depo[i].pret);
  }
  system("pause");
}

void APMenu(sale *s)
{ int opt,ok=1;
  
  SlPrint(s);
   printf("\n1.Checkout\n");
   printf("2.ById\n");
   printf("3.List Viewer\n");
   printf("4.Product Info\n");
   printf("5.Anuleaza plata\n");
   printf("0.Barode\n");
   printf("<O>:");
   scanf("%d",&opt);
   int id;
   switch (opt)
   { case 0: ok=0;break;
   case 1: 
     CKT =1;
     getchar();
     Checkout(s);
    break;
    case 2:
    SlPrint(s);
    printf("\nID Produs:");
    scanf("%d",&id);
    if(FindByID(id)!=NULL)AddToCart(s,FindByID(id));
    else {printf("Produsul nu a fost gasit!!\n");system("pause");}
    break;
    case 3:PrintProdList(); break;
    case 5:CKT=3;break;

   default:
    break;
   }

}
void *scpy(char*s,char*p)
{ s=p;
}
char * scat(const char s[], const char p[])
{ char t[256];
   sprintf(t,"%s%s",s,p);
   return t;
}
char * ToChar(int k)
{ int i=0,a,c=0;
char *s;
a=k;
while (a)
{ c=c*10+(a% 10);
 a/=10;
}
k=c;

s= (char*) malloc(sizeof(char));
s[i]='\0';
   while(k)
   { s=(char*) realloc(s,sizeof(char)*(i+2));
    s[i]=(char)(k%10 + 48);
     s[i+1]='\0';
     i++;
     k/=10;
   }
   return s;
}
void SlBonPrint(sale *s,FILE* fp)
{ 
   fprintf(fp,"_______________________________________________________________\n");
   fprintf(fp,"   Denumire produs");fspace(SPACE,fp); fprintf(fp,"  Pret       Qty\n");
   fprintf(fp,"___________________________________________________________________\n");
   int i;float stot=0,tot=0;
   for(i=0;i<s->np;i++)
   {  fprintf(fp,"%d.%s",i+1,s->prodlist[i].denumire);
      fspace(SPACE- slen(s->prodlist[i].denumire)+18,fp);
      fprintf(fp,"%.2f",s->prodlist[i].pret);
      fprintf(fp,"       %d",qty[i]);
      putc('\n',fp);
      stot+= qty[i]* s->prodlist[i].pret;
      s->total=stot;
   }
   putc('\n',fp);
   fspace(SPACE+18,fp);
   fprintf(fp,"Subtotal:%.2f\n",stot);
   tot = stot;
   fprintf(fp,"--------------------------------------------------------------------\n");
   
   fspace(SPACE+18,fp);
   fprintf(fp,"Total:%.2f\n",tot);
   
}
void GetBon(sale s)
{FILE* fp;
 char t[256];
 sprintf(t,"%s%d%s","./Bonuri/Bon_Fiscal_NO",15,".txt");
MarketDataGet();
  fp=fopen(t,"w+");
  fprintf(fp,"##########################################################\n");
  fprintf(fp,"____________________________ BON FISCAL ___________________\n\n");
  SlBonPrint(&s,fp);
  fprintf(fp,"\n\n");
  fprintf(fp,">Emis la data de: %s\n",__DATE__);
  fprintf(fp,"Casier : %s %s.\n",s.sm->nume,s.sm->prenume);
   fprintf(fp,"   %s %s , Manager executiv: %s, Administrator : %s\n",Mk.denumire,Mk.adresa,Mk.manager, Mk.admin);
   fclose(fp);
}
void Checkout(sale *s)
{ char c;float f=0;int ok=0;
   SlPrint(s);
   printf("\nCheckout type (c/d):");
   c=(char) getchar();
   if(c=='c')
   {
      printf("\nPlatit:");
      scanf("%f",&f);
      printf("\nRest:%.2f",f- s->total);
      if(f>s->total)ok=1;
   }
   else if(c=='d')printf("\nOptiune indisponibila, momentan!");
if(ok==1){GetBon(*s);printf("\nPlata a fost efectuata cu succes\n"); CKT=2;}
}
void SlPrint(sale *s)
{ system("cls");
   printf("##################################################################\n");
   printf("   Denumire produs");space(SPACE); printf("  Pret       Qty\n");
   printf("___________________________________________________________________\n");
   int i;float stot=0,tot=0;
   for(i=0;i<s->np;i++)
   {  printf("%d.%s",i+1,s->prodlist[i].denumire);
      space(SPACE- slen(s->prodlist[i].denumire)+18);
      printf("%.2f",s->prodlist[i].pret);
      printf("       %d",qty[i]);
      putchar('\n');
      stot+= qty[i]* s->prodlist[i].pret;
      s->total=stot;
   }
   putchar('\n');
   space(SPACE+18);
   printf("Subtotal:%.2f\n",stot);
   tot = stot;
   printf("--------------------------------------------------------------------\n");
   if(CKT==1)
   {
   space(SPACE+18);
   printf("Total:%.2f\n",tot);
   }
}
int NSale(salesman* sm)
{ sale s;
   s.sm=sm;
produs* p;
 s.sid = 15;
  int ok=1,q,kq=0;
  char *bcd;
  s.prodlist = (produs *) malloc(sizeof(produs));
  s.np=0;
  char ck;
  qtyset();
  CKT = -1;
  while (ok)
  {  SlPrint(&s);
    CKT=0;
    kq=0;
        getchar();
      printf("\nbarcode:");
      bcd = sscan();
      if(!scmp(bcd,"\0")){p=BarodeProd(bcd);kq=1;}
      else if(scmp(bcd,"\0")==1){APMenu(&s);kq=0;} else break;
      if(CKT==2){Plata+=s.total; break;}
      if(CKT==3){break;}
      if(p!=NULL&&kq==1)
      {  printf("\nqty:");
        scanf("%d",&q);
        if(ListFind(&s,p)>=0)
          { qty[ListFind(&s,p)]+=q;
          }
          else {
        s.prodlist= (produs*) realloc(s.prodlist,sizeof(produs)*(s.np+1));
        s.prodlist[s.np]=*p ;s.np++;
        qty[s.np-1]=q;}
      }
      else {if(kq==1){printf(">Produs inexistent!\n");
      system ("pause");}}
  }
  
   system("pause");
}