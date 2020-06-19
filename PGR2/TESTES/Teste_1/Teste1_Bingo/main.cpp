#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_JOGADRES 100 //define o número máximo de jogadores
#define MAX_NS 100       //define o número máximo do sorteios
#define MAX_NC 5        //define o número máximo linha e coluna da cartela

int funcao;
int quant_joga;
int n_sorteados[MAX_NS];
int auxi_sair=0;

struct jogador {
    char n_jogador[30];
    int Cartela_joga[MAX_NC][MAX_NC];
}cartela[MAX_JOGADRES];



void ganhador(int i);

void numeros_sorteio(){

    srand((unsigned)time(NULL));
    int i=0,valor=0,j=0,cont=0;

    for(i=0;i<MAX_NS;i++){
        valor= 0+rand() % (MAX_NS);

        for(j = 0;j<i;j++){
            if(n_sorteados[j]==valor)   //Vector randômicos não repetido com a sequência dos números do sorteio

                cont++;
        }
        if(cont==0){
            n_sorteados[i]=valor;
        }else{
            i=i-1;
            cont=0;
        }
    }
}


void gerar_cartelas(){

    srand((unsigned)time(NULL));
    int i=0,j=0,k=0,l=0,m=0,valor,cont=0;

    for (i = 0; i < quant_joga;i++) {
        for (j = 0; j< MAX_NC ;j++) {               //matriz randômicos não repetido com as cartelas de cada jogador

            for (k = 0; k< MAX_NC ;k++) {
                valor = rand() %(MAX_NS-1+1)+1;

                for (m = 0; m < k; m++) {
                    if (cartela[i].Cartela_joga[j][m] == valor) {
                        cont++;
                    }
                }
                if (cont == 0) {
                    cartela[i].Cartela_joga[j][k] = valor;

                } else {
                    k = k - 1;
                    cont = 0;
                }

            }
        }
    }

    printf("\33[1m");
    printf("\nCartela dos jogadores");
    printf("\33[0m");

    for (i = 0; i < quant_joga;i++) {
        printf("     \n\n  Jogador %s",cartela[i].n_jogador);  //mostra as cartelas de cada jogador
        for (j = 0; j< MAX_NC ;j++) {
            printf("\n\n");
            for (k = 0; k< MAX_NC ;k++) {
                printf(" %.2d  ", cartela[i].Cartela_joga[j][k]);
            }
        }
    }

    printf("\n\n");
    system("read -p 'Pressione enter para continuar...' var");

}

void jogo(){

    int h=0,i=0,j=0,k=0,l=0,m=0,n=0;

    for (int h = 0; h < MAX_NS; h++) {
        for (i = 0; i < quant_joga; i++) {      //verifica se a o número sorteado na cartela de algum jogador
            for (j = 0; j < MAX_NC; j++) {
                for (k = 0; k < MAX_NC; k++) {
                    if(n_sorteados[h]==cartela[i].Cartela_joga[j][k]){
                        cartela[i].Cartela_joga[j][k]=00;
                    }
                }
            }
        }
        printf("\33[1m");
        printf("\n+==========================================+\n");
        printf("|    Rodada=>%d    Número sorteado=>%d     |",h+1,n_sorteados[h]);
        printf("\n+========================================+\n");
        printf("\33[0m");

        for (l = 0; l < quant_joga; l++) {
            printf("     \n\n    Jogador %s",cartela[l].n_jogador);
            for (m = 0; m < MAX_NC; m++) {
                printf("\n\n");                                          //mostra a rodada e se contém na cartela de algum jogador
                for (n = 0; n < MAX_NC; n++) {
                    printf(" %.2d  ", cartela[l].Cartela_joga[m][n]);
                }
            }

        }
        ganhador(h);
        h=auxi_sair+h;
    }
}

void ganhador(int rodada) {
    int i=0,j=0,k=0,cont=0;
    //verifica se o jogador completou a cartela
    for (i = 0; i < quant_joga; i++) {
        cont=0;
        for (j = 0; j < MAX_NC; j++) {
            for (k = 0; k < MAX_NC; k++) {
                if(cartela[i].Cartela_joga[j][k]==00){
                    cont++;
                }
                if(cont==(MAX_NC*MAX_NC)){
                    printf("\n                    >>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>JOGADOR %s È O CAMPEÂO NA RODADA %d<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n",cartela[i].n_jogador,rodada);
                    printf("                    >>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n\n\n");
                    auxi_sair=1+MAX_NS;
                    sleep(2);
                }
            }
        }
    }
}

int main() {

    int i=0;
    for (;;){

        printf("\33[1m");
        printf("+==========================================+\n");
        printf("|                  Bingo                   |\n");
        printf("+==========================================+\n\n");
        printf("\33[0m");

        printf("FUNÇÕES\n1-Jogar\n2-Instruções\n\n");
        printf("\nEntre com a função=>");
        scanf("%d", &funcao);

        switch (funcao)
        {
            case 1:
                do
                {
                    printf("\nQuantidade de jogadores=>");
                    scanf("%d", &quant_joga);
                    if (quant_joga<=1)
                        printf("\n\n\tQUANTIDADE INVALIDA!!\n");
                }while(quant_joga<2);

                for (i=0; i<quant_joga; i++)
                {
                    printf("\nNome do jogador %d=>", i+1);
                    scanf("%s", cartela[i].n_jogador);
                }
                numeros_sorteio();
                gerar_cartelas();
                jogo();
                break;
            case 2:
                printf("\33[1m");
                printf("\n\n====================================================================================================");
                printf("\n\tINSTRUÇÕES\n");
                printf("\n\t1. Deve ser informado a quantidade de participantes do jogo.");
                printf("\n\t2. Os participantes recebem uma cartela para cada jogador que são geradas aleatoriamente.");
                printf("\n\t3. vencedor será o primeiro que completar a cartela, se houver empate o ganhador será na \n\tordem em que foi cadastrado.\n");
                printf("====================================================================================================\n\n\n");
                printf("\33[0m");
                sleep(2);

                break;
            default:

                printf("\nFUNÇÃO NÃO EXISTE\n");
                sleep(1);
                break;
        }

    }

}
