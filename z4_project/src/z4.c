#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "monopoly.h" // NEMENIT !!!



//funkcie na vypis

void vypisZaklad(int hodKocka, int tah, int hrac) {
    printf("R: %d\n", hodKocka);
    printf("Turn: %d\n", tah);
    printf("Player on turn: P%d\n\n", hrac);
}

void vypisPrepS(int gamebrd[], int gamemnpl[]) {
    printf("Game board:\n");
    for (int i = 0; i < 24; i++) {
        int player=0;
        char* s;
        printf("%2d.  ", i+1);
        if (gamebrd[i]!=0) {
            player=gamebrd[i];
            if (gamemnpl[i] == 1) { s="yes"; } else { s="no"; }
        }

        if (game_board[i].type == Property && player!=0) {
            printf("%-16s  %d  %-7s  P%d %s\n", game_board[i].property->name, game_board[i].property->price, (char *) property_colors[game_board[i].property->color], player, s);
        } else if (game_board[i].type == Property) {
            printf("%-16s  %d  %-7s\n", game_board[i].property->name, game_board[i].property->price, (char *) property_colors[game_board[i].property->color]);
        } else {
            printf("%s\n", space_types[game_board[i].type]);
        }
    }
}

void vypisPrepP(PLAYER playerr) {
    printf("%d. ", playerr.number);
    printf("S: %d, ", playerr.space_number);
    printf("C: %d, ", playerr.cash);
    printf("JP: %d, ", playerr.num_jail_pass);
    if (playerr.is_in_jail==0) { printf("IJ: no\n"); } else { printf("IJ: yes\n"); }

    for (int p=0; p<playerr.num_properties; p++) {
        for (int k=0; k<24; k++) {
            if (game_board[k].property->name==playerr.owned_properties[p]->name && game_board[k].type==Property) {
                printf("      %-18s %d  %-8s  S%d\n", playerr.owned_properties[p]->name, playerr.owned_properties[p]->price, (char *) property_colors[playerr.owned_properties[p]->color], k+1);
                break;
            }
        }

    }
}


//funkcia na urcenie vitaza
int winnerCash(PLAYER playerr[], int numPlay) {
    int winner=0, draw=0;
    for (int i=1; i<numPlay; i++) {
        if (playerr[i].cash>playerr[winner].cash) {
            winner=i;
            draw=0;
        } else if (playerr[i].cash==playerr[winner].cash) {
            draw=1;
        }
    }

    winner=draw==1 ? -1 : winner+1 ;
    return winner;
}

int winnerProperty(PLAYER playerr[], int numPlay) {
    int propSum[numPlay], maxHod=0;

    for (int i=0; i<numPlay; i++) { propSum[i]=playerr[i].cash; }
    for (int i=0; i<numPlay; i++) { if (propSum[i]>maxHod) { maxHod=propSum[i]; }}
    for (int i=0; i<numPlay; i++) {
        if (propSum[i]==maxHod) {
            for (int p=0; p<playerr[i].num_properties; p++) {
                propSum[i]+=playerr[i].owned_properties[p]->price;
            }
        }
    }
    maxHod=0;
    int draw=0, winner=0;
    for (int i=0; i<numPlay; i++) { if (propSum[i]>maxHod) { maxHod=propSum[i]; draw=0; winner=i; } else if (propSum[i]==maxHod) {draw=1;}}
    winner=draw==1 ? -1 : winner+1;
    return winner;
}










int main(int argc, char *argv[]) {


    int s=0, p=0, g=0, numPlayers=0;
    int c;


    while ((c=getopt(argc, argv, ":n:spg"))!=-1) {
        switch (c) {
            case 'n':
                sscanf(optarg, "%d", &numPlayers);
                break;
            case 's':
                s=1;
                break;
            case 'p':
                p=1;
                break;
            case 'g':
                g=1;
                break;
            case ':':   //missing argument
                numPlayers=2;
            case '?':   //unknown option
                numPlayers=2;
        }
    }


    int ownedPropertiesByGame[24];
    for (int i=0; i<24; i++) { ownedPropertiesByGame[i]=0; }
    int isMonopol[24];
    for (int i=0; i<24; i++) { isMonopol[i]=0; }

    printf("Players:\n");
    PLAYER player[numPlayers];
    for (int i=0; i<numPlayers; i++) {
        player[i].number=i+1;
        printf("%d. ", player[i].number);
        player[i].space_number=1;
        printf("S: %d, ", player[i].space_number);
        if (numPlayers==2) { player[i].cash=20; } else if (numPlayers==3) { player[i].cash=18; } else if (numPlayers==4) { player[i].cash=16; };
        printf("C: %d, ", player[i].cash);
        player[i].num_jail_pass=0;
        printf("JP: %d, ", player[i].num_jail_pass);
        player[i].is_in_jail=0;
        printf("IJ: no\n");
        player[i].num_properties=0;
    }

    printf("Game board:\n");
    for (int i = 0; i < 24; i++) {
        printf("%2d.  ", i+1);
        if (game_board[i].type == Property) {
            printf("%-16s  %d  %-s\n",(char *) game_board[i].property->name, game_board[i].property->price, (char *) property_colors[game_board[i].property->color]);
        } else {
            printf("%s\n", space_types[game_board[i].type]);
        }
    }
    printf("Winner: -\n");



    int hodCislo, hracNaRade=0, gameBreak=0, turn=1;
    while (gameBreak!=1) {
        scanf("%d", &hodCislo);


        if (player[hracNaRade].is_in_jail==0 || (player[hracNaRade].is_in_jail==1 && player[hracNaRade].cash-1>=0)) {
            //ak je vo vazani odcita sa 1e
            if (player[hracNaRade].is_in_jail==1) { player[hracNaRade].cash-=1; player[hracNaRade].is_in_jail=0; }

            //moving on the board
            //ak prejde kolo, posunie sa na start + ostavajuce pozicie a prirataju sa 2e
            if (player[hracNaRade].space_number+hodCislo>24) {
                player[hracNaRade].space_number=player[hracNaRade].space_number+hodCislo-24;
                player[hracNaRade].cash+=2;
            } else {
                player[hracNaRade].space_number+=hodCislo;
            }

            //adding jail passes
            if (player[hracNaRade].space_number==4 || player[hracNaRade].space_number==10 || player[hracNaRade].space_number==16 || player[hracNaRade].space_number==22) { player[hracNaRade].num_jail_pass+=1; };
            //go to jail
            if (player[hracNaRade].space_number==19 && player[hracNaRade].num_jail_pass==0) {
                player[hracNaRade].space_number=7;
                player[hracNaRade].is_in_jail=1;
            } else if (player[hracNaRade].space_number==19 && player[hracNaRade].num_jail_pass>0) { player[hracNaRade].num_jail_pass-=1; }


            //overenie majitela a nasledne zaplatenie najomneho alebo kupenie property
            //ak vstupi na dane pole a pole je property
            if (game_board[player[hracNaRade].space_number-1].property!=NULL) {
                //ak vstupi na dane pole a pole ma majitela ide zaplatenie najomneho
                if (ownedPropertiesByGame[player[hracNaRade].space_number-1]!=player[hracNaRade].number && ownedPropertiesByGame[player[hracNaRade].space_number-1]!=0) {
                    //player[hracNaRade].space_number-1] - aktualna poloha hraca


                    //odcitanie penazi, ak nema na zaplatenie je koniec
                    if (isMonopol[player[hracNaRade].space_number-1]==1) {
                        player[hracNaRade].cash-=2*game_board[player[hracNaRade].space_number-1].property->price;
                    } else {
                        player[hracNaRade].cash-=game_board[player[hracNaRade].space_number-1].property->price;
                    }

                    if (player[hracNaRade].cash<0) {
                        gameBreak=1;
                        if (isMonopol[player[hracNaRade].space_number-1]==1) {
                            player[hracNaRade].cash+=2*game_board[player[hracNaRade].space_number-1].property->price;
                        } else {
                            player[hracNaRade].cash+=game_board[player[hracNaRade].space_number-1].property->price;
                        }
                    } else {
                        //pricitaju sa peniaze majitelovi
                        if (isMonopol[player[hracNaRade].space_number-1]==1) {
                            player[ownedPropertiesByGame[player[hracNaRade].space_number-1]-1].cash+=2*game_board[player[hracNaRade].space_number-1].property->price;
                        } else {
                            player[ownedPropertiesByGame[player[hracNaRade].space_number-1]-1].cash+=game_board[player[hracNaRade].space_number-1].property->price;
                        }
                    }

                } else if (ownedPropertiesByGame[player[hracNaRade].space_number-1]==0) {
                    //kupenie property
                    //odcita sumu z uctu, ak nema na zaplatenie je koniec
                    player[hracNaRade].cash-=game_board[player[hracNaRade].space_number-1].property->price;
                    if (player[hracNaRade].cash<0) {
                        gameBreak=1;
                        player[hracNaRade].cash+=game_board[player[hracNaRade].space_number-1].property->price;
                    } else {
                        //pridanie property do osobneho portfolia (owned_properties)
                        player[hracNaRade].owned_properties[player[hracNaRade].num_properties]=game_board[player[hracNaRade].space_number-1].property;
                        //prirata sa pocet vlastenych properties
                        player[hracNaRade].num_properties++;
                        //pridanie hraca do registra vlastnenych nehnutelnosti
                        ownedPropertiesByGame[player[hracNaRade].space_number-1]=player[hracNaRade].number;

                        //overenie monopolu, ak vlastni obe properties prida sa 1 do monopolu
                        if (ownedPropertiesByGame[player[hracNaRade].space_number-1]==player[hracNaRade].number && ownedPropertiesByGame[player[hracNaRade].space_number-2]==player[hracNaRade].number) {
                            isMonopol[player[hracNaRade].space_number-1]=1;
                            isMonopol[player[hracNaRade].space_number-2]=1;
                        } else if (ownedPropertiesByGame[player[hracNaRade].space_number-1]==player[hracNaRade].number && ownedPropertiesByGame[player[hracNaRade].space_number]==player[hracNaRade].number) {
                            isMonopol[player[hracNaRade].space_number-1]=1;
                            isMonopol[player[hracNaRade].space_number]=1;
                        }

                    }

                }

            }




        } else {
            //ak hrac nema na zaplatenie 1e, pri vychode z vazenia
            gameBreak=1;
        }




        printf("\n");
        vypisZaklad(hodCislo, turn, player[hracNaRade].number);


        if (gameBreak!=1) {
            //V Y P I S Y   P R E P I N A C O V
            if (s==1) { vypisPrepS(ownedPropertiesByGame, isMonopol); }
            if (p==1) {
                printf("Players:\n");
                for (int i=0; i<numPlayers; i++) { vypisPrepP(player[i]); }
            }
            if (g==1) {
                printf("Players:\n");
                for (int i=0; i<numPlayers; i++) { vypisPrepP(player[i]); }
                vypisPrepS((int *) ownedPropertiesByGame, (int *) isMonopol);
                printf("Winner: -\n");
            }
        }
        /*
        printf("\nregister nehnutelnosti\n");
        for (int i=0; i<24; i++) {
            printf("%d ", ownedPropertiesByGame[i]);
        }
        printf("\nregister monopolu\n");
        for (int i=0; i<24; i++) {
            printf("%d ", isMonopol[i]);
        }*/

        hracNaRade = hracNaRade+1==numPlayers ? 0 : hracNaRade+1;
        turn++;
    }



    //vypis na konci hry
    printf("Players:\n");
    for (int i=0; i<numPlayers; i++) { vypisPrepP(player[i]); }
    vypisPrepS((int *) ownedPropertiesByGame, (int *) isMonopol);

    //urcenie vitaza
    if (winnerCash(player, numPlayers)!=-1) {
        printf("Winner: P%d", winnerCash(player, numPlayers));
    } else if (winnerProperty(player, numPlayers)!=-1){
        printf("Winner: P%d", winnerProperty(player, numPlayers));
    } else {
        printf("Winner: ?");
    }

    return 0;
}
