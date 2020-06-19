//PROGRAMA DE SISTEMA CONTROLE DE EMPRÉSTIMOS DE LIVROS//
//AUTOR:MATHEUS MEDEIROS//
//ESTILO DE INDENTAÇÃO: K&R STYLE//

//1 - Programa que, primeiramente faz o registro de usuários no sistema, //
//cadastramento de livros, desbloqueio de usuários, edição de livros, ciclo//
//para poder entrar no sistema de livros.//

//2 - Com relação a arquivos, programa reserva a quantidade de memória necessária usando “malloc”, então temos: //
//“Cadas_Livro=(struct Livro_Cadastro *) malloc(sizeof( struct Livro_Cadastro ));//
//que, é a alocação de memória necessária para alocar a quantidade de livros dinamicamente.//

//3- Usuário estourando o limites de 3 tentativas, o sistema automaticamente o bloqueia, sendo agora// 
//responsabilidade do adm para poder liberar o acesso novamente.//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_Tenta 3
#define TAM_Senha 6
#define TAM_codi 7
#define TAM_Char 25
#define TAM_Matri 8
#define TAM_cadas 5
#define TAM_inativo 3

struct Usuario_resgistro 
{
   char user_ID[TAM_Char];  
   char senha[TAM_Senha];
   int Ativo;  
};

struct Usuario_resgistro Usuario_Cadastro[TAM_cadas]={{"Julio","123abc",0},
                                                      {"Tiago","aei987",0},
                                                      {"Matheus","111111",0},
                                                      {"Maykon","456mak",0},
                                                      {"Ary","123abc",0}
                                                      };


struct Livro_registro 
{
    char codigo[TAM_codi];
    char Titulo[TAM_Char];
    char Autor[TAM_Char];
    char Editora[TAM_Char];
}Livro_Usuario;

void Adm_Listar_Livro();

char user_SN_auxi;
int funcao;
char Codi_auxi[TAM_codi];
char userID_auxi[TAM_Char];
char senha_auxi[TAM_Char];


void Menu_de_Entrada()
{
    printf("+=======================================================+\n");
    printf("|          CONTROLE DE EMPRÉSTIMOS DE LIVROS            |\n");
    printf("+=======================================================+\n\n");
    printf("Entre com seu User_ID para ter acesso ao sistema=>"); 
}

void Menu_Usuarios(int controle)
{
    int i;
    i=controle;
   
    if(Usuario_Cadastro[i].Ativo<3){
        printf("Entre com a senha=>");
        scanf("%s",senha_auxi);
        if(strcmp(senha_auxi,Usuario_Cadastro[i].senha)==0){
            printf("\nCampo de pegar livro\n");
            sleep(3);
            main();
        }else{
            Usuario_Cadastro[i].Ativo++;
            printf("\nSENHA INVÁLIDA, RESTAM APENAS %d-3 TENTATIVAS\n",Usuario_Cadastro[i].Ativo);
            sleep(3);
            main();
        }
    }else{
        printf("\nUSUÁRIO BLOQUEADO VOCÊ EXCEDEU O NUMERO DE 3 TENTATIVAS\n");
        sleep(3);
        main(); 
    }
}
void Adm_Desbloquear_Usuario()
{
    int i=0,j=0;
    int user_Incon=1;
    
    for(j=0;j<3;j++){
        printf("UserID a ser desbloqueado=>");
        scanf("%s",userID_auxi);
        for(i = 0; i < TAM_cadas;i++){
            if(strcmp(userID_auxi,Usuario_Cadastro[i].user_ID)==0){
                Usuario_Cadastro[i].Ativo=0;
                printf("\n%s DESBLOQUEADO\n",userID_auxi);
                sleep(2);
                main();         
            }
        }
        printf("UserID NÃO EXISTE\n\n");
    }
}          
void Adm_Add_Livro()
{
    FILE *AQ_Cadas_livro;
    struct Livro_registro *Cadastro;
    Cadastro = &Livro_Usuario;
    int cont=0;
    
    AQ_Cadas_livro= fopen("Livro.txt", "a+");

    if(AQ_Cadas_livro==NULL){
        printf("ERRO DE ABERTURA DE ARQUIVO");   
        exit(1); 
    }

    Cadastro=(struct Livro_registro*) malloc(sizeof( struct Livro_registro ));
    if (Cadastro==NULL){
        printf("ERRO DE ALOCAÇÃO");  
        exit(1);
    }

    do{
        system("clear");

        printf("+===========================+\n");
        printf("|       Cadastro livro      |\n");
        printf("+===========================+\n\n");
        scanf("%*[^\n]"); scanf("%*c");
        printf("Entre com o código=>");
        fgets(Cadastro->codigo,TAM_Char,stdin);
        Cadastro->codigo[strlen(Cadastro->codigo) - 1]= '\0';
        printf("Entre com o Título=>");
        fgets(Cadastro->Titulo,TAM_Char,stdin);
        Cadastro->Titulo[strlen(Cadastro->Titulo) - 1]= '\0';
        printf("Entre com Autor=>");
        fgets(Cadastro->Autor,TAM_Char,stdin);
        Cadastro->Autor[strlen(Cadastro->Autor) - 1]= '\0';
        printf("Entre com a Editora=>");    
        fgets(Cadastro->Editora,TAM_Char,stdin);
        Cadastro->Editora[strlen(Cadastro->Editora) - 1]= '\0';
        
        printf("\nRevisão de cadastro\n\n");
        
        printf("código= %s     Título= %s\n",Cadastro->codigo,Cadastro->Titulo);
        printf("Autor= %s     Editora= %s\n",Cadastro->Autor,Cadastro->Editora);

        fseek(AQ_Cadas_livro,SEEK_END,1);
       
        fprintf(AQ_Cadas_livro,"%s %s %s %s\n",Cadastro->codigo,Cadastro->Titulo,Cadastro->Autor,Cadastro->Editora);

        printf("\nGRAVADO COM SUSESSO\n");
        printf("Deseja continuar cadastrando mais livros S/N\n=>");
        scanf("%c",&user_SN_auxi);
    }while((user_SN_auxi=='S')||(user_SN_auxi=='s'));
    fclose(AQ_Cadas_livro);

}

void Adm_remover_Livro()
{
    FILE *AQ_Cadas_livro,*AQ_Cadas_auxi;
    struct Livro_registro *Cadastro;
    Cadastro = &Livro_Usuario;
    int cont=0;
    char Codi_auxi[TAM_codi];
    
    AQ_Cadas_livro= fopen("Livro.txt", "r");
    if(AQ_Cadas_livro==NULL){
        printf("ERRO DE ABERTURA DE ARQUIVO");   
        exit(1); 
    }

    AQ_Cadas_auxi= fopen("auxi.txt", "w");
    if(AQ_Cadas_auxi==NULL){
        printf("ERRO DE ABERTURA DE ARQUIVO");   
        exit(1); 
    }

    system("clear");
    Adm_Listar_Livro();
    scanf("%*[^\n]"); scanf("%*c");
    fflush(stdin);
    printf("Digite o código do Livro a ser removido=> ");
    fgets(Codi_auxi,TAM_codi,stdin);
    
    fseek(AQ_Cadas_livro,SEEK_SET,1);
    while ((fscanf(AQ_Cadas_livro,"%s %s %s %s\n",Cadastro->codigo,Cadastro->Titulo,Cadastro->Autor,Cadastro->Editora))!=EOF){
        if(strcmp(Codi_auxi,Cadastro->codigo)==0){
            cont++;
        }
    }

    if(cont==0){
    printf("LIVRO NÃO EXISTE\n");
    sleep(3);
    fclose(AQ_Cadas_livro);
    fclose(AQ_Cadas_auxi);
    main();
    }

    rewind(AQ_Cadas_livro);
    while ((fscanf(AQ_Cadas_livro,"%s %s %s %s\n",Cadastro->codigo,Cadastro->Titulo,Cadastro->Autor,Cadastro->Editora))!=EOF){
        if(strcmp(Codi_auxi,Cadastro->codigo)!=0){
             fprintf(AQ_Cadas_auxi,"%s %s %s %s\n",Cadastro->codigo,Cadastro->Titulo,Cadastro->Autor,Cadastro->Editora);
        }
    }
    fclose(AQ_Cadas_livro);
    fclose(AQ_Cadas_auxi);

    remove("Livro.txt");
    rename("auxi.txt", "Livro.txt");
    printf("LIVRO EXCLUIDO\n");
    system("read -p 'Pressione enter para continuar...' var");


}

void Adm_Listar_Livro()
{
    FILE *AQ_Cadas_livro;
    struct Livro_registro *Cadastro;
    Cadastro = &Livro_Usuario;
    
    AQ_Cadas_livro= fopen("Livro.txt", "r");

    if(AQ_Cadas_livro==NULL){
        printf("ERRO DE ABERTURA DE ARQUIVO");   
        exit(1); 
    }

    system("clear");
    printf("+===================================+\n");
    printf("|       Cadastro listar livros      |\n");
    printf("+===================================+\n\n");       

    fseek(AQ_Cadas_livro,SEEK_SET,1);
    while ((fscanf(AQ_Cadas_livro,"%s %s %s %s\n",Cadastro->codigo,Cadastro->Titulo,Cadastro->Autor,Cadastro->Editora))!=EOF){
        printf("código= %s     Título= %s\n",Cadastro->codigo,Cadastro->Titulo);
        printf("Autor= %s      Editora= %s\n",Cadastro->Autor,Cadastro->Editora);
        printf("\n");
    }
    system("read -p 'Pressione enter para continuar...' var");
    fclose(AQ_Cadas_livro);
}

void Menu_Administrador()
{
    char auxi_senha[TAM_Senha];
    int i;

    
    for(i=0;i<TAM_Tenta;i++){
        printf("\nVocê é o administrador\n"); 
        printf("Entre com a sua senha=>");
        scanf("%s",auxi_senha);
        if(strcmp(auxi_senha,"1")==0){
            for(;;){
                system("clear");
                printf("\n       FUNÇÕES\n\n");
                printf("1-Desbloquear usuarios.\n");
                printf("2-Cadastrar livro.\n");       
                printf("3-Remover livros.\n");
                printf("4-Listar livros cadastrados.\n");
                printf("0-Sair.\n"); 
                printf("\nEntre com a função=>");
                scanf("%d",&funcao);
                system("clear"); 
               
                switch (funcao)
                {
                case 0:
                    main();
                    break;
                case 1:
                    Adm_Desbloquear_Usuario();
                    break;
                case 2:     
                    Adm_Add_Livro();
                    break;
                case 3:     
                    Adm_remover_Livro();
                    break;
                case 4:     
                    Adm_Listar_Livro();
                    break;
                default:
                    printf("\nFUNÇÃO NÃO EXISTE\n");
                    break;
                }
            
            }
        }
        if(i==2){
            printf("\nVOCÊ ESTOUROU O LIMITE DE 3 TENTATIVAS\n");
            sleep (2);
            main();
 
        }else{
            printf("\nSENHA INCORRETA\n");
        }
    }       
}

int main()
{
    int i;
    char ID_auxi[TAM_Char];
    system("clear");
    for(;;)
    {
    system("clear");   
    Menu_de_Entrada();
    scanf("%s",userID_auxi);
        if(strcmp(userID_auxi,"adm")==0){
            Menu_Administrador();
        }else{
            for(i = 0; i < TAM_cadas;i++){
                if(strcmp(userID_auxi,Usuario_Cadastro[i].user_ID)==0){
                    Menu_Usuarios(i);                                   
                    system("clear");
                }
            }
        }
    }
}

