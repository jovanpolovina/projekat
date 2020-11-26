#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* dodavanje_naloga(int* isLoggedIn)
{
    char nickname[30], email[30], password[30], potvrda_password[30], ime[30], prezime[30];
int success = 0;
  char* nazivFajla = malloc(sizeof(char)*50);
while(success ==0){
         memset(nickname, 0, sizeof(char)*30);
        memset(password, 0, sizeof(char)*30);
        memset(ime, 0, sizeof(char)*30);
        memset(prezime, 0, sizeof(char)*30);
        memset(potvrda_password, 0, sizeof(char)*30);
        memset(email, 0, sizeof(char)*30);
        memset(nazivFajla, 0, sizeof(char)*50);
    printf("unesi nickname, email, ime, prezime");
    gets(nickname);
    gets(email);
    gets(ime);
    gets(prezime);
    printf("unesi sifru");
    gets(password);
    printf("unesi sifru jos jednom");
    gets(potvrda_password);
    while(strcmp(password, potvrda_password)!=0)
    {
        printf("sifre nisu iste, opet unesi sifru");
        gets(potvrda_password);
    }
  strcpy(nazivFajla, nickname);
strcat(nazivFajla, ".txt");
FILE* f1 = fopen(nazivFajla, "r");
 if(f1!=NULL)
        {
            printf("Nickname je vec u upotrebi!\n");
            fclose(f1);

            continue;
        }
        fclose(f1);
int brojac = 0;
email[strlen(email)] = '\n';
f1 = fopen("sviNalozi.txt", "r");
char red[65];
   while(fgets(red, 65, f1)!=NULL)
        {
            if(strcmp(red, email)==0)
            {
                ++brojac;
                break;
            }
        }
        if(strchr(email, '@')==NULL){
            ++brojac;
        }
        else if(strchr(strchr(email, '@'), '.')==NULL){
            ++brojac;
        }
          if(brojac!=0)
        {
            printf("Email je vec u upotrebi ili je neispravan!\n");
            fclose(f1);
            continue;
        }
        ++success;
        *isLoggedIn = 1;
        fclose(f1);

}
 FILE* f1 = fopen(nazivFajla, "w");
    fprintf(f1, "%s\n%s%s\n%s\n%s\n", nickname, email, password, ime, prezime);
    fclose(f1);
    f1 = fopen("sviNalozi.txt", "a");
    fprintf(f1, "%s%s\n", email, nickname);
    fclose(f1);
    return nazivFajla;
}
char* login(int* isLoggedIn)
{
    int success=0;
    while(success==0)
    {
        char username[30], password[30];
        char* nazivFajla = malloc(sizeof(char)*30);
        memset(nazivFajla, 0, sizeof(char)*30);
        printf("upisi nadimak ili imejl");
        gets(username);
        printf("upisi sifru");
        gets(password);
        password[strlen(password)] = '\n';
        strcpy(nazivFajla, username);
        strcat(nazivFajla, ".txt");
        FILE* f1 = fopen(nazivFajla, "r");
        username[strlen(username)] = '\n';
        if(f1==NULL)
        {
            fclose(f1);

            FILE* f2 = fopen("sviNalozi.txt", "r");
            fseek(f2, 0, SEEK_SET);
            int brojac = 0;
            char email[50];
            while(fgets(email, 50, f2)!=NULL)
            {
                if(strcmp(username, email)==0)
                {
                    ++brojac;

                    break;
                }
            }
            if(brojac == 0)
            {
                printf("Uneli ste pogresni nickname ili email\n");
                free(nazivFajla);
                fclose(f2);
                continue;
            }
            fgets(email, 50, f2);
            strcpy(nazivFajla, email);
            strcat(nazivFajla, ".txt");
            f1=fopen(nazivFajla, "r");

            fclose(f2);
        }
        char confirmPas[50];
        fseek(f1, 0, SEEK_SET);
        for(int i=0; i<3; ++i)
        {
            fgets(confirmPas, 50, f1);

        }
        if(strcmp(password, confirmPas)==0)
        {
            ++success;
        }
        if(success==0)
        {
            printf("Uneli ste pogresni password\n");
            free(nazivFajla);
            fclose(f1);
        }
        else
        {
            printf("Uspesno ste se ulogovali\n");
            *isLoggedIn = 1;
            fclose(f1);
            return nazivFajla;
        }

    }

}


void logout(char* nazivFajla, int* isLoggedIn)
{
    free(nazivFajla);
    nazivFajla = NULL;
    *isLoggedIn = 0;
    printf("Good bye!\n");
}




void meni(){

int isLoggedIn = 0;
char* nazivFajla;
while(1==1){
    if(isLoggedIn == 0){
           printf("1. Registruj se\n");
            printf("2. Prijavi se\n");
            printf("3. Close Google drive\n");
            int e=0;
            scanf("%i", &e);
             getchar();
              while(e!=1 && e!=2 && e!=3)
            {
                printf("Izabrali ste nepostojecu opciju!\n");
                printf("1. Registruj se\n");
                printf("2. Prijavi se\n");
                printf("3. Close Google drive\n");

                scanf("%i", &e);
                getchar();
            }
              if(e==1)
            {
                nazivFajla = dodavanje_naloga(&isLoggedIn);
            }
            else if(e==2)
            {
                nazivFajla = login(&isLoggedIn);
            }
            else if(e==3)
            {
                break;
            }
    }
    else if(isLoggedIn==1)
        {
            int e=0;
            printf("1. Izmeni profil\n");
            printf("2. Obrisi profil\n");
            printf("3. Odjavi se\n");
            scanf("%i", &e);
            getchar();
            while(e!=1 && e!=2 && e!=3)
            {
                printf("Izabrali ste nepostojecu opciju!\n");
                printf("1. Izmeni profil\n");
                printf("2. Obrisi profil\n");
                printf("3. Odjavi se\n");
                scanf("%i", &e);
                getchar();
            }
            if(e==1)
            {
                izmeniProfil(nazivFajla);
            }
            else if(e==2)
            {
                obrisiProfil(nazivFajla, &isLoggedIn);
            }
            else if(e==3)
            {
                logout(nazivFajla, &isLoggedIn);
            }
        }
}

}
void obrisiProfil(char* nazivFajla, int* isLoggedIn)
{
    FILE* f1 = fopen(nazivFajla, "r");
    fseek(f1, 0, SEEK_SET);
    int success = 0;
    char confirmPas[50];
    for(int i=0; i<3; ++i)
    {
        fgets(confirmPas, 50, f1);

    }
    while(success==0)
    {
        char password[50]={0};
        printf("Unesite password da biste obrisali profil: ");
        gets(password);
        password[strlen(password)]='\n';
        if(strcmp(password, confirmPas)==0)
        {
            ++success;
        }
        if(success==0)
        {
            printf("Uneli ste pogresnu sifru!\n");
        }
    }

    char email[50];
    fseek(f1, 0, SEEK_SET);
    fgets(email, 50, f1);
    fgets(email, 50, f1);
    FILE* f2 = fopen("sviNalozi.txt", "r");
    FILE* f3 = fopen("izmena.txt", "w");
    char red[50];
    int count = 0;
    while(fgets(red, 50, f2)!=NULL)
    {
        if(strcmp(email, red)==0)
        {
            ++count;
            continue;
        }
        if(count==1)
        {
            ++count;
            continue;
        }
        fprintf(f3, "%s", red);
    }
    fclose(f2);
    fclose(f3);
    remove("sviNalozi.txt");
    rename("izmena.txt", "sviNalozi.txt");
    fclose(f1);
    remove(nazivFajla);
    logout(nazivFajla, isLoggedIn);
}

void izmeniProfil(char* nazivFajla)
{

    while(1==1)
    {
        printf("1. Izmeni nickname\n");
        printf("2. Izmeni email\n");
        printf("3. Izmeni password\n");
        printf("4. Izmeni ime\n");
        printf("5. Izmeni prezime\n");
        printf("6.. Sacuvaj\n");
        int e;
        scanf("%i", &e);
        getchar();
        while(e<1 || e>6)
        {
            printf("Izabrali ste pogresnu opciju!\n");
            printf("1. Izmeni nickname\n");
            printf("2. Izmeni email\n");
            printf("3. Izmeni password\n");
            printf("4. Izmeni ime\n");
            printf("5. Izmeni prezime\n");
            printf("6. Sacuvaj\n");
            scanf("%i", &e);
            getchar();
        }
        if(e==1)
        {
            printf("Unesi novi nickname: ");
            izmena(nazivFajla, 0);
        }
        else   if(e==2)
        {
            printf("Unesi novi email: ");
            izmena(nazivFajla, 1);
        }
        else if(e==3)
        {
            int success = 0;
            FILE* f1 = fopen(nazivFajla, "r");

            char confirmPas[50];

            fseek(f1, 0, SEEK_SET);
            for(int i=0; i<3; ++i)
            {
                fgets(confirmPas, 50, f1);

            }
            while(success==0)
            {
                char password[50]={0};
                printf("Unesite stari password: ");
                gets(password);
                password[strlen(password)]='\n';
                if(strcmp(password, confirmPas)==0)
                {
                    ++success;
                }
                if(success==0)
                {
                    printf("Uneli ste pogresni password!\n");
                }
            }
            fclose(f1);
            printf("Unesi novi password: ");
            izmena(nazivFajla, 2);
        }
        else if(e==4)
        {
            printf("Unesi novo ime: ");
            izmena(nazivFajla, 3);
        }
        else if(e==5)
        {
            printf("Unesi novo prezime: ");
            izmena(nazivFajla, 4);
        }
        else if(e==6)
        {
            break;
        }

    }
}


void izmena(char* nazivFajla, int i)
{
    FILE* f1 = fopen(nazivFajla, "r");
    fseek(f1, 0, SEEK_SET);
    char izmeniString[50];
    gets(izmeniString);
    FILE* f2 = fopen("izmena.txt", "w");
    int e=0;
    char red[50];
    char pretraga[50];
    if(i==0){
            int success = 0;
    while(success==0){
        char nicknameFile[50];
    strcpy(nicknameFile, izmeniString);
strcat(nicknameFile, ".txt");
FILE* f2 = fopen(nicknameFile, "r");
 if(f2!=NULL)
        {
            printf("Nickname je vec u upotrebi!\n");
            fclose(f2);
memset(izmeniString, 0, sizeof(char)*50);
gets(izmeniString);
            continue;
        }
        fclose(f2);
        ++success;
    }
    }
    if(i==1){
        int success = 0;
            while(success==0){
int brojac = 0;
char email[100] = {0};
strcpy(email, izmeniString);
email[strlen(email)] = '\n';
FILE* f2 = fopen("sviNalozi.txt", "r");
fseek(f2, 0, SEEK_SET);
char red[65];
   while(fgets(red, 65, f2)!=NULL)
        {
            if(strcmp(red, email)==0)
            {
                ++brojac;
                break;
            }
        }
        if(strchr(email, '@')==NULL){
            ++brojac;
        }
        else if(strchr(strchr(email, '@'), '.')==NULL){
            ++brojac;
        }
          if(brojac!=0)
        {
            printf("Email je vec u upotrebi ili je neispravan!\n");
            fclose(f2);
            memset(izmeniString, 0, sizeof(char)*50);
gets(izmeniString);
            continue;
        }
        ++success;
        fclose(f2);
    }
    }
    while(fgets(red, 50, f1)!=NULL)
    {
        if(e==i)
        {
            fprintf(f2, "%s\n", izmeniString);
            sscanf(red, "%s", pretraga);
            ++e;
            continue;
        }
        ++e;
        fprintf(f2, "%s", red);
    }
    fclose(f1);
    fclose(f2);
    remove(nazivFajla);
    rename("izmena.txt", nazivFajla);
    if(i==0 || i==1)
    {
        f1 = fopen("sviNalozi.txt", "r");
        fseek(f1, 0, SEEK_SET);
        f2 = fopen("izmenaa.txt", "w");
        fseek(f2, 0, SEEK_SET);
        pretraga[strlen(pretraga)]='\n';
        while(fgets(red, 50, f1)!=NULL)
        {
            if(strcmp(pretraga, red)==0)
            {
                fprintf(f2, "%s\n", izmeniString);
                continue;
            }
            fprintf(f2, "%s", red);

        }
        fclose(f1);
        fclose(f2);
        remove("sviNalozi.txt");
        rename("izmenaa.txt", "sviNalozi.txt");

        if(i==0)
        {
            char noviNaziv[54];
            sscanf(izmeniString, "%s", noviNaziv);
            strcat(noviNaziv, ".txt");
            rename(nazivFajla, noviNaziv);
        }
    }

}


int main(){
meni();
}
