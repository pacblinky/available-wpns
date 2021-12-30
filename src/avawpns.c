#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
 #include <windows.h>
#endif

#define WPNS_COUNT 21
#define ON '2'
#define OFF '0'
#define INPUT_BUFFER 169

void toggleWPN(char* wpn, char toggle);
void output();

char availableWPNS[WPNS_COUNT + 1] = "200000000000000000000";
const char wpns[WPNS_COUNT][8] = {"knife", "gpistol", "spistol", "shotgun", "uzi", "m3a1", "usas12", "m4", "ak74", "sniper", "m60", "mm1", "rpg", "none", "flash", "none", "none", "none", "frag", "fire", "smoke"};
const char wpns_name[WPNS_COUNT][22] = {"Knife", "M1911A", "USSOCOM", "M590 Shotgun", "Micro Uzi", "M3A1", "USAS12", "M4 Assault Rifle", "AK74 Assault Rifle", "MSG90A1 Sniper Rifle", "M6O Machinegun", "MM1 Grenade Launcher", "RPG-7 Rocket Launcher", "none", "M84 (Flash grenade)", "none", "none", "none", "SMOH92 (Frag grenade)", "ANM14 (Fire grenade)", "M15 (Smoke grenade)"};

int main(void)
{
    char input[INPUT_BUFFER];
    char toggle;
    #ifdef _WIN32
        SetConsoleTitle("availableWeapons");
    #else
        printf("%c]0;%s%c", '\033', "availableWeapons", '\007');
    #endif
    printf("\n Enter help for commands list\n\n");
    while(1)
    {
        printf("> ");
        fgets(input, INPUT_BUFFER, stdin);
        input[strcspn(input, "\n")] = '\0';
        strlwr(input);
        char* wpn;
        char* cmd = strtok_r(input, " ",&wpn);
        if (!strcmp(cmd, "add") || !strcmp(cmd, "remove"))
        {
            if (!strcmp(cmd, "add")) toggle = ON;
            else toggle = OFF;
            printf("\n");
            while (wpn != NULL)
            {
                toggleWPN(strtok_r(NULL," ",&wpn), toggle);
            }
        }
        else if(!strcmp(cmd,"output")) output();
        else if(!strcmp(cmd,"clear") || !strcmp(cmd,"cls"))
        {
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        }
        else if(!strcmp(cmd,"exit") || !strcmp(cmd,"quit")){ printf("\n"); exit(0);}
        else if(!strcmp(cmd,"wpns"))
        {
            printf("\nWeapons list:\n\n");
            for(int i = 0; i < WPNS_COUNT; i++)
            {
                if(!strcmp("none",wpns[i])){continue;}
                printf("- %s = %s\n\n",wpns[i],wpns_name[i]);
            }
        }
        else if(!strcmp(cmd,"help") || !strcmp(cmd,"cmds"))
        {
            printf("\n help/cmds = This message.\n add/remove <weapon> = Add/Remove weapon from weapons list and you can add/remove multipe weapons at once.\n wpns = Weapons list.\n output = Print availableWeapons out to the screen.\n copy - Copy availableWeapons (Windows only).\n selected = Selected weapons list.\n clear/cls = Clear the console.\n exit/quit Close the program.\n\n");
        }
        else if(!strcmp(cmd,"selected"))
        {
            printf("\nSelected weapons list:\n\n");
            for(int i = 0 ; i < WPNS_COUNT; i++)
            {
                if(availableWPNS[i] == ON){printf("- %s\n",wpns_name[i]);}
            }
             printf("\n");
        }
        #ifdef _WIN32
            else if(!strcmp(cmd,"copy"))
            {
                OpenClipboard(0);
                EmptyClipboard();
                char str[41];
                snprintf(str,41,"availableWeapons \"%s\"",availableWPNS);
                HGLOBAL copy_str = GlobalAlloc(GMEM_MOVEABLE,41);
                memcpy(GlobalLock(copy_str),str,41);
                GlobalUnlock(copy_str);
                SetClipboardData(CF_TEXT,copy_str);
                CloseClipboard();
                printf("\n Successfully copied availableWeapons to the clipboard\n\n");
            }
        #endif
    }
    return 0;
}

void toggleWPN(char* wpn, char toggle)
{
    if (!strcmp("none", wpn)) {return;}
    if (!strcmp("all", wpn))
    {
        memset(availableWPNS,toggle,WPNS_COUNT);
        availableWPNS[13] = availableWPNS[15] = availableWPNS[16] = availableWPNS[17] = OFF;
        printf(" %s all weapons\n\n", atoi(&toggle)? "Added" : "Removed");
        return;
    }
    for (int i = 0; i < WPNS_COUNT; i++)
    {
        if (!strcmp(wpns[i], wpn))
        {
            if (availableWPNS[i] == toggle)
                printf(" %s is already %s\n\n", wpns_name[i], toggle ? "added" : "removed");
            else    
            {
                availableWPNS[i] = toggle;
                printf(" %s: %s\n\n", atoi(&toggle)? "Added" : "Removed", wpns_name[i]);
            }
            break;
        }
        else
        {
            if (i == WPNS_COUNT - 1)
            {
                printf("%s is not a valid weapon\n");
            }
        }
    }
}

void output()
{
    printf("\navailableWeapons \"");
    for (int i = 0; i < WPNS_COUNT; i++)
    {
        printf("%c",availableWPNS[i]);
    }
    printf("\"\n\n");
}
