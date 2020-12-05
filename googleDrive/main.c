#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* dodavanje_naloga(int* isLoggedIn)
{
    char nickname[30], email[30], password[30], potvrda_password[30], ime[30], prezime[30];
    int success = 0;
    char* nazivFajla = malloc(sizeof(char)*50);
    while(success ==0)
    {
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
        if(strchr(email, '@')==NULL)
        {
            ++brojac;
        }
        else if(strchr(strchr(email, '@'), '.')==NULL)
        {
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
    fprintf(f1, "%s\n%s%s\n%s\n%s\nFolderi\n", nickname, email, password, ime, prezime);
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
        char password[50]= {0};
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
                char password[50]= {0};
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
    if(i==0)
    {
        int success = 0;
        while(success==0)
        {
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
    if(i==1)
    {
        int success = 0;
        while(success==0)
        {
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
            if(strchr(email, '@')==NULL)
            {
                ++brojac;
            }
            else if(strchr(strchr(email, '@'), '.')==NULL)
            {
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



void dodajFolder(char* path, char* nazivFajla)
{
    srand(time(0));
    char nazivfoldera[100]= {0};
    gets(nazivfoldera);
    char folderPath[150]= {0};
    char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    int success = 0;
    char randomString[6];
    while(success==0)
    {
        memset(randomString, 0, sizeof(char)*5);
        memset(folderPath, 0, sizeof(char)*150);
        int stringLen = strlen(string);
        for (int n = 0; n<5; n++)
        {
            int key = rand() % stringLen;
            randomString[n] = string[key];
        }
        randomString[5]='\0';
               if(strlen(path)>0)
        {
            strcpy(folderPath, path);
            strcat(folderPath, "/");
            strcat(folderPath, randomString);
        }
        else
        {
            strcpy(folderPath, randomString);

        }
        if(!mkdir(folderPath))
        {
            ++success;

        }
    }
    FILE* f1 = fopen(nazivFajla, "r");
    fseek(f1, 0, SEEK_SET);
    char nickname[100];
    fgets(nickname, 100, f1);
    fclose(f1);
    if(strlen(path)>0)
    {
        char folderTxt[100];
        strcpy(folderTxt, path);
        strcat(folderTxt, "/folder.txt");
        FILE* f2 = fopen(folderTxt, "r");
        FILE* f3 = fopen("izmena.txt", "w");
        fseek(f2, 0, SEEK_SET);
        char linija[100];
        while(fgets(linija, 100, f2)!=NULL)
        {
            fprintf(f3, linija);
            if(strcmp(linija, "Subfolders\n")==0)
            {
                fprintf(f3, "%s\n", randomString);
            }

        }

        fclose(f2);
        fclose(f3);
        remove(folderTxt);
        rename("izmena.txt", folderTxt);
        char newfolderTxt[150];
        strcpy(newfolderTxt, folderPath);
        strcat(newfolderTxt, "/folder.txt");
        f2 = fopen(folderTxt, "r");
        fseek(f2, 0, SEEK_SET);
        f3 = fopen(newfolderTxt, "w");
        fprintf(f3,"%s\nFajlovi\nSubfolders\nKreator\n", nazivfoldera);
        while(fgets(linija, 100, f2)!=NULL)
        {
            if(strcmp(linija, "Kreator\n")==0)
            {
                break;
            }
        }
        int kreator = 0;
        while(fgets(linija, 100, f2)!=NULL)
        {
            if(strcmp(linija, nickname)==0)
            {
                ++kreator;
            }
            if(strcmp(linija, "Administratori\n")==0 && kreator == 0)
            {
                fprintf(f3,"%s", nickname);
            }
            fprintf(f3,linija);
        }
        fclose(f2);
        fclose(f3);
    }
    else
    {

        FILE* f2 = fopen(nazivFajla, "a");
        fprintf(f2, "%s\n", folderPath);
        fclose(f2);
        char folderTxt[150];
        strcpy(folderTxt, folderPath);
        strcat(folderTxt, "/folder.txt");
        f2 = fopen(folderTxt, "w");
        fprintf(f2,"%s\nFajlovi\nSubfolders\nKreator\n%sAdministratori\nOstali\n", nazivfoldera, nickname);
        fclose(f2);
    }

}


void podeliFolderRec(char* path, char* nickname, int admin)
{
    char folderPath[100];
    strcpy(folderPath, path);
    folderPath[strlen(folderPath)] = '/';
    char folderTxt[100];
    strcpy(folderTxt, path);
    strcat(folderTxt, "/folder.txt");
    FILE* f1 = fopen(folderTxt, "r");
    fseek(f1, 0, SEEK_SET);
    char linija[100];
    while(fgets(linija, 100, f1)!=NULL)
    {
        if(strcmp(linija, "Subfolders\n")==0)
        {
            break;
        }
    }
    while(fgets(linija, 100, f1)!=NULL)
    {
        if(strcmp(linija, "Kreatori\n")==0)
        {
            break;
        }
        char subFolder[200]= {0};
        strcpy(subFolder, folderPath);
        char nastavak[100];
        sscanf(linija, "%[^\n]", nastavak);
        strcat(subFolder, nastavak);
        podeliFolderRec(subFolder, nickname, admin);
    }
    fclose(f1);
    f1 = fopen(folderTxt, "r");
    fseek(f1, 0, SEEK_SET);
    FILE* f2 = fopen("izmena.txt", "w");
    while(fgets(linija, 100, f1)!=NULL)
    {
        fprintf(f2, linija);
        if(admin==1 && strcmp(linija, "Administratori\n")==0)
        {
            fprintf(f2,"%s", nickname);
        }
        if(admin==2 && strcmp(linija, "Ostali\n")==0)
        {
            fprintf(f2, "%s", nickname);
        }
    }
    fclose(f1);
    fclose(f2);
    remove(folderTxt);
    rename("izmena.txt", folderTxt);
}




void podeliFolder(char* path)
{
    int success = 0;
    char nazivFajla[100];
    char nickname[100];
    int admin = -1;
    while(success == 0)
    {
        printf("Unesite email adresu osobe sa kojom hocete da podelite folder: ");
        char email[100] = {0};
        gets(email);
        while(admin!=1 && admin!=2)
        {
            printf("Da li je osoba admin? 1. DA 2. NE");
            scanf("%i", &admin);
            getchar();
        }
        email[strlen(email)] = '\n';
        if(strchr(email, '@')==NULL)
        {
            printf("Email je neispravan!\n");
            continue;
        }
        else if(strchr(strchr(email, '@'), '.')==NULL)
        {
            printf("Email je neispravan!\n");
            continue;
        }
        FILE* f1 = fopen("sviNalozi.txt", "r");
        fseek(f1, 0, SEEK_SET);
        char linija[100];
        memset(nazivFajla, 0, sizeof(char)*100);
        while(fgets(linija, 100, f1)!=NULL)
        {
            if(strcmp(email, linija)==0)
            {
                fgets(linija, 100, f1);
                sscanf(linija, "%s", nazivFajla);
                strcpy(nickname, linija);
                strcat(nazivFajla, ".txt");
                ++success;
                break;
            }
        }
        if(success==0)
        {
            printf("Osoba sa ovom email adresom ne postoji\n");
        }
        fclose(f1);
    }

    FILE* f1 = fopen(nazivFajla, "a");
    fprintf(f1, "%s\n", path);
    fclose(f1);
    podeliFolderRec(path, nickname, admin);
}




void ograniciPristupRec(char* path, char* nickname, int pozicija)
{
    char folderPath[100];
    strcpy(folderPath, path);
    folderPath[strlen(folderPath)] = '/';
    char folderTxt[100];
    strcpy(folderTxt, path);
    strcat(folderTxt, "/folder.txt");
    FILE* f1 = fopen(folderTxt, "r");
    fseek(f1, 0, SEEK_SET);
    char linija[100];
    while(fgets(linija, 100, f1)!=NULL)
    {
        if(strcmp(linija, "Subfolders\n")==0)
        {
            break;
        }
    }
    while(fgets(linija, 100, f1)!=NULL)
    {
        if(strcmp(linija, "Kreatori\n")==0)
        {
            break;
        }
        char subFolder[200]= {0};
        strcpy(subFolder, folderPath);
        char nastavak[100];
        sscanf(linija, "%s", nastavak);
        strcat(subFolder, nastavak);
        ograniciPristupRec(subFolder, nickname, pozicija);
    }
    fclose(f1);
    f1 = fopen(folderTxt, "r");
    fseek(f1, 0, SEEK_SET);
    FILE* f2 = fopen("izmena.txt", "w");
    while(fgets(linija, 100, f1)!=NULL)
    {
        if(strcmp(linija, nickname)==0)
        {
            continue;
        }
        fprintf(f2, linija);

    }
    fclose(f1);
    fclose(f2);
    remove(folderTxt);
    rename("izmena.txt", folderTxt);
}




void ograniciPristup(char* path, int pozicija)
{
    if(pozicija==3){
        printf("Nemate prava da ogranicite pristup u ovom folderu!\n");
        return;
    }

    int success = 0;
    char nickname[100];
    char folderTxt[100];
    strcpy(folderTxt, path);
    strcat(folderTxt, "/folder.txt");
    while(success == 0)
    {
        printf("Unesite email adresu osobe sa kojoj hocete da ogranicite pristup ovom folderu: ");
        char email[100] = {0};
        gets(email);
        email[strlen(email)] = '\n';

        if(strchr(email, '@')==NULL)
        {
            printf("Email je neispravan!\n");
            continue;
        }
        else if(strchr(strchr(email, '@'), '.')==NULL)
        {
            printf("Email je neispravan!\n");
            continue;
        }
        FILE* f1 = fopen("sviNalozi.txt", "r");
        fseek(f1, 0, SEEK_SET);
        char linija[100];
        memset(nickname, 0, sizeof(char)*100);
        while(fgets(linija, 100, f1)!=NULL)
        {

            if(strcmp(email, linija)==0)
            {
                fgets(linija, 100, f1);
                strcpy(nickname, linija);
                break;
            }
        }
        fclose(f1);
        f1 = fopen(folderTxt, "r");
        fseek(f1, 0, SEEK_SET);
        while(fgets(linija, 100, f1)!=NULL)
        {
            if(pozicija == 1 && strcmp(linija, "Administratori\n")==0)
            {
                break;
            }
            if(pozicija == 2 && strcmp(linija, "Ostali\n")==0)
            {
                break;
            }
        }
        while(fgets(linija, 100, f1)!=NULL)
        {

            if(strcmp(linija, "Administratori\n")==0)
            {
                continue;
            }
            if(strcmp(linija, "Ostali\n")==0)
            {
                continue;
            }
            if(strcmp(linija, nickname)==0)
            {
                ++success;
                break;
            }
        }
        fclose(f1);
        if(success==0)
        {
            printf("Osoba sa ovom email adresom ne postoji ili nemate prava da je izbacite!\n");
        }
    }
    ograniciPristupRec(path, nickname, pozicija);
    char nazivfajla[150];
    sscanf(nickname, "%s", nazivfajla);
    strcat(nazivfajla, ".txt");
    FILE* f1 = fopen(nazivfajla, "r");
    FILE* f2 = fopen("izmena.txt", "w");
    char linija[100];
    while(fgets(linija, 100, f1)!=NULL)
    {
        if(strncmp(linija, path, sizeof(path))==0)
        {
            continue;
        }
        fprintf(f2, linija);
    }
    fclose(f1);
    fclose(f2);
    remove(nazivfajla);
    rename("izmena.txt", nazivfajla);
}
struct folderiIFajlovi
{
    char path[200], naziv[100];
};
typedef struct folderiIFajlovi folderFiles;
void prikaziFoldere(char* path, char* nazivFajla)
{
    folderFiles* folderiiFajloviArr;
    int i;
    if(strlen(path)>0)
    {
        char folderTxt[100];
        strcpy(folderTxt, path);
        strcat(folderTxt, "/folder.txt");
        FILE* f1 = fopen(folderTxt, "r");
        fseek(f1, 0, SEEK_SET);
        char linija[100];
        while(fgets(linija, 100, f1)!=NULL)
        {
            if(strcmp(linija, "Fajlovi\n")==0)
            {
                break;
            }
        }
        i = 0;
        while(fgets(linija, 100, f1)!=NULL)
        {
            if(strcmp(linija, "Subfolders\n")==0)
            {
                continue;
            }
            if(strcmp(linija, "Kreator\n")==0)
            {
                break;
            }
            ++i;
        }
        folderiiFajloviArr =(folderFiles*)malloc(sizeof(folderFiles)*i);
        memset(folderiiFajloviArr, 0, sizeof(folderFiles)*i);
        fseek(f1, 0, SEEK_SET);
        while(fgets(linija, 100, f1)!=NULL)
        {
            if(strcmp(linija, "Fajlovi\n")==0)
            {
                break;
            }
        }
        i=0;
        while(fgets(linija, 100, f1)!=NULL)
        {
            if(strcmp(linija, "Subfolders\n")==0)
            {
                break;
            }
            strcpy(folderiiFajloviArr[i].naziv, linija);
            char imeFajla[50];
            sscanf(linija, "%[^\n]", imeFajla);
            char fajlPath[150];
            strcpy(fajlPath, path);
            strcat(fajlPath, "/");
            strcat(fajlPath, imeFajla);
            strcpy(folderiiFajloviArr[i].path, fajlPath);
            fgets(linija, 100, f1);
            ++i;
        }
        while(fgets(linija, 100, f1)!=NULL)
        {
            if(strcmp(linija, "Kreator\n")==0)
            {
                break;
            }
            char folderPath[200]= {0};
            strcpy(folderPath, path);
            char nastavak[100]= {0};
            sscanf(linija, "%s", nastavak);
            strcat(folderPath, "/");
            strcat(folderPath, nastavak);
            strcpy(folderiiFajloviArr[i].path, folderPath);
            strcat(folderPath, "/folder.txt");
            FILE* f2 = fopen(folderPath, "r");
            fseek(f2, 0, SEEK_SET);
            char naziv[100]= {0};
            fscanf(f2, "%[^\n]", naziv);
            fclose(f2);
            strcpy(folderiiFajloviArr[i].naziv, naziv);
            ++i;
        }
        fclose(f1);
    }
    else
    {
        FILE* f1 = fopen(nazivFajla, "r");
        fseek(f1, 0, SEEK_SET);
        char linija[100];
        while(fgets(linija, 100, f1)!=NULL)
        {
            if(strcmp(linija, "Folderi\n")==0)
            {
                break;
            }
        }
        i = 0;
        while(fgets(linija, 100, f1)!=NULL)
        {
            ++i;
        }
        folderiiFajloviArr =(folderFiles*)malloc(sizeof(folderFiles)*i);
        memset(folderiiFajloviArr, 0, sizeof(folderFiles)*i);
        fseek(f1, 0, SEEK_SET);
        i = 0;
        while(fgets(linija, 100, f1)!=NULL)
        {
            if(strcmp(linija, "Folderi\n")==0)
            {
                break;
            }
        }
        while(fgets(linija, 100, f1)!=NULL)
        {
            char newfolderTxt[200]= {0};
            sscanf(linija, "%s", newfolderTxt);
            strcpy(folderiiFajloviArr[i].path, newfolderTxt);
            strcat(newfolderTxt, "/folder.txt");
            FILE* f2 = fopen(newfolderTxt, "r");
            fseek(f2, 0, SEEK_SET);
            char naziv[100]= {0};
            fscanf(f2, "%[^\n]", naziv);
            strcpy(folderiiFajloviArr[i].naziv, naziv);

            ++i;
            fclose(f2);

        }
        fclose(f1);

    }
    while(1==1)
    {
        int opcija = -1;
        while(opcija<1 || opcija>i+1)
        {
            for(int j=0; j<i; ++j)
            {
                printf("%i. %s\n", j+1, folderiiFajloviArr[j].naziv);
            }
            printf("%i. Nazad\n", i+1);
            scanf("%i", &opcija);
            getchar();
        }
        if(opcija==i+1)
        {
            break;
        }
        FILE* f1 = fopen(folderiiFajloviArr[opcija-1].path, "r");
        if(f1!=NULL)
        {
            fclose(f1);
            int e = akcijeUFajlu(&(folderiiFajloviArr[opcija-1]));
            if(e==2)
            {
                free(folderiiFajloviArr);
                break;
            }
        }
        else
        {
            fclose(f1);
            int e = akcijeUfolderu(&(folderiiFajloviArr[opcija-1]), nazivFajla);
            if(e==5 || e==i+1)
            {
                free(folderiiFajloviArr);
                break;
            }
        }
    }
}

void preimenujFolder(folderFiles* f)
{
    char noviNaziv[100];
    printf("Upisite novi naziv foldera: ");
    gets(noviNaziv);
    sscanf(noviNaziv, "%s", f->naziv);
    char folderTxt[100];
    strcpy(folderTxt, f->path);
    strcat(folderTxt, "/folder.txt");
    FILE* f1 = fopen(folderTxt, "r");
    fseek(f1, 0, SEEK_SET);
    FILE* f2 = fopen("izmena.txt", "w");
    char linija[100];
    fgets(linija, 100, f1);
    fprintf(f2, "%s\n", noviNaziv);
    while(fgets(linija, 100, f1)!=NULL)
    {
        fprintf(f2, linija);
    }
    fclose(f1);
    fclose(f2);
    remove(folderTxt);
    rename("izmena.txt", folderTxt);
}



void obrisiFolder(char* path, int pozicija)
{
    if(pozicija!=1)
    {
        printf("Nemate pravo da obrisete ovaj folder!");
        return;
    }
    if(strchr(path, '/')!=NULL)
    {
        int i = strlen(path)-1;
             while(path[i]!='/')
        {
            --i;
        }
        char parentFolderTxt[100];
        strncpy(parentFolderTxt, path, i);
        parentFolderTxt[strlen(parentFolderTxt)-1]='\0';
        strcat(parentFolderTxt, "/folder.txt");
printf("\t%s", parentFolderTxt);
        FILE* f2 = fopen(parentFolderTxt, "r");
        FILE* f3 = fopen("izmena.txt", "w");

        char red[100];
        while(fgets(red, 100, f2)!=NULL)
        {
            fprintf(f3, red);
            if(strcmp(red, "Subfolders\n")==0)
            {
                break;
            }
        }
        while(fgets(red, 100, f2)!=NULL)
        {
            char linkFoldera[10]= {0};
            sscanf(red, "%s", linkFoldera);
            if(strstr(path, linkFoldera)!=NULL)
            {
                continue;
            }
            fprintf(f3, red);
            if(strcmp(red, "Kreator\n")==0)
            {
                break;
            }

        }
        while(fgets(red, 100, f2)!=NULL)
        {
            fprintf(f3, red);
        }
        fclose(f2);
        fclose(f3);
        remove(parentFolderTxt);
        rename("izmena.txt", parentFolderTxt);
    }
    char folderTxt[100];
    strcpy(folderTxt, path);
    strcat(folderTxt, "/folder.txt");
    FILE* f1 = fopen(folderTxt, "r");
    fseek(f1, 0, SEEK_SET);
    char linija[100];
    while(fgets(linija, 100, f1)!=NULL)
    {
        if(strcmp(linija, "Fajlovi\n")==0)
        {
            break;
        }
    }
    while(fgets(linija, 100, f1)!=NULL)
    {
        if(strcmp(linija, "Subfolders\n")==0)
        {
            break;
        }
        char nazivFajla[100]= {0};
        sscanf(linija, "%s", nazivFajla);
        char fajlPath[150]= {0};
        strcpy(fajlPath, path);
        strcat(fajlPath, "/");
        strcat(fajlPath, nazivFajla);
        remove(fajlPath);
    }
    while(fgets(linija, 100,f1)!=NULL)
    {
        if(strcmp(linija, "Kreator\n")==0)
        {
            break;
        }
        char linkFoldera[100]= {0};
        sscanf(linija, "%s", linkFoldera);
        char folderPath[150]= {0};
        strcpy(folderPath, path);
        strcat(folderPath, "/");
        strcat(folderPath, linkFoldera);
        obrisiFolder(folderPath, pozicija);

    }
    while(fgets(linija, 100, f1)!=NULL)
    {
        if(strcmp(linija, "Administratori\n")==0)
        {
            continue;
        }
        if(strcmp(linija, "Ostali\n")==0)
        {
            continue;
        }
        char nazivFajla[100];
        sscanf(linija, "%s", nazivFajla);
        strcat(nazivFajla, ".txt");
        FILE* f2 = fopen(nazivFajla, "r");
        fseek(f2, 0, SEEK_SET);
        FILE* f3 = fopen("izmena.txt", "w");
        char red[100];
        while(fgets(red, 100, f2)!=NULL)
        {
            fprintf(f3, red);
            if(strcmp(red, "Folderi\n")==0)
            {
                break;
            }
        }
        while(fgets(red, 100, f2)!=NULL)
        {
            if(strncmp(red, path, strlen(path))==0)
            {
                continue;
            }
            fprintf(f3, red);
        }
        fclose(f3);
        fclose(f2);
        remove(nazivFajla);
        rename("izmena.txt", nazivFajla);
    }
    fclose(f1);
    remove(folderTxt);
    rmdir(path);
}

struct Node
{
        folderFiles f;
    float procenat;
    struct Node* next;
};
void insertnewNode(struct Node** head, float procenat, char* naziv, char* path)
{
    struct Node* newNode = malloc(sizeof(struct Node));
    memset(newNode, 0, sizeof(struct Node));
    strcpy(newNode->f.naziv,naziv);
    strcpy(newNode->f.path, path);
    newNode->procenat = procenat;
    newNode->next = NULL;
    if(*head==NULL)
    {
        *head = newNode;
        (*head)->next = NULL;
        return;
    }
    if((*head)->procenat <= procenat)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    struct Node* help = *head;
     while(help->procenat >= procenat)
    {
        if(help->next==NULL){
            newNode->next=NULL;
                help->next=newNode;
                return;
           }
           if(help->next->procenat<procenat){
            break;
           }
           help = help->next;
    }

    newNode->next = help->next;
    help->next = newNode;
}
void deleteSearchList(struct Node* head)
{
    while(head!=NULL)
    {
        struct Node* help = head;
        head = head->next;
        free(help);
    }
}
struct Node* searchNode(struct Node* head, int j)
{
    int i = 1;
    while(i!=j)
    {
        head = head->next;
        ++i;
    }
    return head;
};
int printList(struct Node* head)
{
    int i = 0;
    while(head!=NULL)
    {
        ++i;
        printf("%i. %s\n",i, head->f.naziv);
        head = head->next;
    }
    return i;
}
void searchRec(char* path, char* pretraga, struct Node** head)
{
    char folderTxt[100];
    strcpy(folderTxt, path);
    strcat(folderTxt, "/folder.txt");
    FILE* f1 = fopen(folderTxt, "r");
    fseek(f1, 0, SEEK_SET);
    char linija[100];
    while(fgets(linija, 100, f1)!=NULL)
    {
        if(strcmp(linija, "Fajlovi\n")==0)
        {
            break;
        }
    }
    while(fgets(linija, 100, f1)!=NULL)
    {
        if(strcmp(linija, "Subfolders\n")==0)
        {
            break;
        }
         if(strstr(linija, pretraga)!=NULL)
        {
            char nazivFajla[100]= {0};
            sscanf(linija, "%[^\n]", nazivFajla);
            char pathFajla[150] = {0};
            strcpy(pathFajla, path);
            strcat(pathFajla, "/");
            strcat(pathFajla, nazivFajla);
            float a = strlen(pretraga);
            float b = strlen(nazivFajla);
            float procenat = (a/b)*100;
            insertnewNode(head, procenat, nazivFajla, pathFajla);
        }
        fgets(linija,100, f1);
    }
    while(fgets(linija, 100, f1)!=NULL)
    {
        if(strcmp(linija, "Kreator\n")==0)
        {
            break;
        }
        char linkFoldera[150]= {0};
        sscanf(linija, "%s", linkFoldera);
        char pathFoldera[200]= {0};
        strcpy(pathFoldera, path);
        strcat(pathFoldera, "/");
        strcat(pathFoldera, linkFoldera);
     searchRec(pathFoldera, pretraga, head);
        char newfolderTxt[250]={0};
        strcpy(newfolderTxt, pathFoldera);
       strcat(newfolderTxt, "/folder.txt");
        char nazivFoldera[100]= {0};
        FILE* f2 = fopen(newfolderTxt, "r");
        fseek(f2,0,SEEK_SET);
        fscanf(f2, "%[^\n]", nazivFoldera);
        fclose(f2);
        if(strstr(nazivFoldera, pretraga)!=NULL)
        {

            float a = strlen(pretraga);
            float b = strlen(nazivFoldera);
            float procenat = (a/b)*100;
            insertnewNode(head, procenat, nazivFoldera, pathFoldera);
        }
    }
    fclose(f1);
}
void search(char* nazivFajla)
{
    struct Node* head = NULL;
    printf("Pretraga: ");
    char pretraga[200];
    gets(pretraga);
    FILE* f1 = fopen(nazivFajla, "r");
    fseek(f1, 0, SEEK_SET);
    char linija[100];
    while(fgets(linija, 100, f1)!=NULL)
    {
        if(strcmp(linija, "Folderi\n")==0)
        {
            break;
        }
    }
    while(fgets(linija, 100, f1)!=NULL)
    {
        char pathFoldera[150]= {0};
        sscanf(linija, "%s", pathFoldera);
   searchRec(pathFoldera, pretraga, &head);
        char folderTxt[150]= {0};
        strcpy(folderTxt, pathFoldera);
        strcat(folderTxt, "/folder.txt");
        FILE* f2 = fopen(folderTxt, "r");
        fseek(f2, 0, SEEK_SET);
        char nazivFoldera[100]= {0};
        fscanf(f2, "%[^\n]", nazivFoldera);
        fclose(f2);
        if(strstr(nazivFoldera, pretraga)!=NULL)
        {
            float a = strlen(pretraga);
            float b = strlen(nazivFoldera);
            float procenat = (a/b)*100;
            insertnewNode(&head, procenat, nazivFoldera, pathFoldera);
        }

    }
    fclose(f1);
    while(1==1)
    {
        int e = printList(head);
        printf("%i. Nazad\n", e+1);
        int opcija;
        scanf("%i", &opcija);
        getchar();
        while(opcija<1 || opcija>e+1)
        {
            printList(head);
            printf("%i. Nazad\n", e+1);
            scanf("%i", &opcija);
            getchar();
        }

        if(opcija==e+1)
        {
            deleteSearchList(head);
            break;
        }
      f1 = fopen(searchNode(head, opcija)->f.path, "r");
        if(f1!=NULL)
        {
            fclose(f1);
            int q = akcijeUFajlu(&((searchNode(head, opcija))->f));
            if(q==2)
            {
                deleteSearchList(head);
                break;
            }
        }
        else
        {
            fclose(f1);
            int q = akcijeUfolderu(&((searchNode(head, opcija))->f), nazivFajla);
            if(q==5)
            {
                deleteSearchList(head);
                break;
            }
        }
    }
}
void dodajFajl(char* path)
{
    printf("Unesite naziv fajla zajedno sa ekstenzijom: ");
    char nazivFajla[100]= {0};
    gets(nazivFajla);
    while(strchr(nazivFajla, '.')==NULL)
    {
        printf("Naziv fajla mora da sadrzi i ekstenziju!\n");
        printf("Unesite naziv fajla zajedno sa ekstenzijom: ");
        memset(nazivFajla, 0, sizeof(char)*100);
        gets(nazivFajla);
    }
    char fajlPath[200];
    strcpy(fajlPath, path);
    strcat(fajlPath, "/");
    strcat(fajlPath, nazivFajla);
    time_t t;
    time(&t);
    FILE* f1 = fopen(fajlPath, "w");
    fclose(f1);
    char folderTxt[200];
    strcpy(folderTxt, path);
    strcat(folderTxt, "/folder.txt");
    f1 = fopen(folderTxt, "r");
    fseek(f1,0,SEEK_SET);
    FILE* f2 = fopen("izmena.txt", "w");
    char linija[100];
    while(fgets(linija, 100, f1)!=NULL)
    {
        fprintf(f2, linija);
        if(strcmp(linija, "Fajlovi\n")==0)
        {
            break;
        }
    }
    fprintf(f2, "%s\n%s", nazivFajla, ctime(&t));
    while(fgets(linija, 100, f1)!=NULL)
    {
        fprintf(f2, linija);
    }
    fclose(f1);
    fclose(f2);
    remove(folderTxt);
    rename("izmena.txt", folderTxt);
}
void obrisiFajl(char* path)
{

    int i = strlen(path)-1;
        while(path[i]!='/')
    {
        --i;
    }
    char parentFolderTxt[100];
    strncpy(parentFolderTxt, path, i);
    strcat(parentFolderTxt, "/folder.txt");

    FILE* f1 = fopen(parentFolderTxt, "r");
    fseek(f1, 0, SEEK_SET);
    FILE* f2 = fopen("izmena.txt", "w");
    char linija[100];
    while(fgets(linija, 100, f1)!=NULL)
    {
        fprintf(f2, linija);
        if(strcmp(linija, "Fajlovi\n")==0)
        {
            break;
        }
    }
    while(fgets(linija, 100, f1)!=NULL)
    {
        char nazivFajla[100]= {0};
        sscanf(linija, "%s", nazivFajla);
        if(strstr(path, nazivFajla)!=NULL)
        {
            fgets(linija, 100, f1);
            continue;
        }
        fprintf(f2, linija);
        if(strcmp(linija, "Subfolders\n")==0)
        {
            break;
        }
    }
    while(fgets(linija, 100, f1)!=NULL)
    {
        fprintf(f2, linija);
    }
    fclose(f1);
    fclose(f2);
    remove(parentFolderTxt);
    rename("izmena.txt", parentFolderTxt);
    remove(path);
}
void detaljiFajla(char* path)
{
    int i = strlen(path)-1;
    char folderLink[10];
    while(path[i]!='/')
    {
        --i;
    }
    char parentFolderTxt[100];
    strncpy(parentFolderTxt, path, i);
    strcat(parentFolderTxt, "/folder.txt");
    FILE* f1 = fopen(parentFolderTxt, "r");
    fseek(f1, 0, SEEK_SET);
    char linija[100];
    while(fgets(linija, 100, f1)!=NULL)
    {
        if(strcmp(linija, "Fajlovi\n")==0)
        {
            break;
        }
    }
    while(fgets(linija, 100, f1)!=NULL)
    {
        char nazivFajla[100]= {0};
        sscanf(linija, "%s", nazivFajla);
        if(strstr(path, nazivFajla)!=NULL)
        {
            printf("%s", fgets(linija, 100, f1));
        }
        if(strcmp(linija, "Subfolders\n")==0)
        {
            break;
        }
    }
    fclose(f1);
}
int akcijeUFajlu(folderFiles* f)
{
    int opcija = -1;
    while(opcija<1 || opcija>2)
    {
        printf("1. Detalji\n");
        printf("2. Obrisi fajl\n");
        scanf("%i", &opcija);
        getchar();
        if(opcija == 1)
        {
            detaljiFajla(f->path);
        }
        if(opcija==2)
        {
            obrisiFajl(f->path);
            return 2;
        }
        return 0;
    }
}
int akcijeUfolderu(folderFiles* f, char* nazivFajla)
{
    char folderTxt[100];
    strcpy(folderTxt, f->path);
    strcat(folderTxt, "/folder.txt");
    FILE* f1 = fopen(folderTxt, "r");
    fseek(f1, 0, SEEK_SET);
    FILE* f2 = fopen(nazivFajla, "r");
    fseek(f2, 0, SEEK_SET);
    char nickname[100]= {0};
    fgets(nickname, 100, f2);
    fclose(f2);
    char linija[100];
    int pozicija = 1;
    while(fgets(linija, 100, f1)!=NULL)
    {
        if(strcmp(linija, nickname)==0)
        {
            break;
        }
        if(strcmp(linija, "Administratori\n")==0)
        {
            ++pozicija;
            continue;
        }
        if(strcmp(linija, "Ostali\n")==0)
        {
            ++pozicija;
            continue;
        }
    }
    fclose(f1);
    int opcija = -1;
    while(opcija<1 || opcija>7)
    {
        printf("1. Prikazi sadrzaj foldera\n");
        printf("2. Kreiraj fajl\n");
        printf("3. Kreiraj subfolder\n");
        printf("4. Preimenuj folder\n");
        printf("5. Obrisi folder\n");
        printf("6. Podeli folder\n");
        printf("7. Ogranici pristup\n");
        printf("8. Nazad\n");
        scanf("%i", &opcija);
        getchar();
        if(opcija == 1)
        {
            prikaziFoldere(f->path, nazivFajla);
        }
        if(opcija==2)
        {
            dodajFajl(f->path);
        }
        if(opcija==3)
        {
            dodajFolder(f->path, nazivFajla);
        }
        if(opcija==4)
        {
            preimenujFolder(f);
        }
        if(opcija==5)
        {
            obrisiFolder(f->path, pozicija);
            return 5;
        }
        if(opcija==6)
        {
            podeliFolder(f->path);
        }
        if(opcija==7)
        {
            ograniciPristup(f->path, pozicija);
        }
        if(opcija == 8)
        {
            return 0;
        }
    }

    return 0;
}


void meni()
{

    int isLoggedIn = 0;
    char* nazivFajla;
    char* path = "";
    while(1==1)
    {
        if(isLoggedIn == 0)
        {
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
            printf("1. Google Drive\n");
            printf("2. Izmeni profil\n");
            printf("3. Obrisi profil\n");
            printf("4. Kreiraj folder\n");
            printf("5. Pretraga\n");
            printf("6. Odjavi se\n");
            scanf("%i", &e);
            getchar();
            while(e!=1 && e!=2 && e!=3 && e!=4 && e!=5 && e!=6)
            {
                printf("Izabrali ste nepostojecu opciju!\n");
                printf("1. Google Drive\n");
                printf("2. Izmeni profil\n");
                printf("3. Obrisi profil\n");
                printf("4. Kreiraj folder\n");
                printf("5. Pretraga\n");
                printf("6. Odjavi se\n");
                scanf("%i", &e);
                getchar();
            }
            if(e==1)
            {
                prikaziFoldere(path, nazivFajla);
            }

            if(e==2)
            {
                izmeniProfil(nazivFajla);
            }
            else if(e==3)
            {
                obrisiProfil(nazivFajla, &isLoggedIn);
            }
            else if(e==4)
            {
                dodajFolder(path, nazivFajla);
            }
            else if(e==5)
            {
                search(nazivFajla);
            }
            else if(e==6)
            {
                logout(nazivFajla, &isLoggedIn);
            }
        }
    }

}



int main()
{
    meni();
}
