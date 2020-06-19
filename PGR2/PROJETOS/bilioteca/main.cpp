#include <iostream>
#include <fstream>
#include <list>
#include <string>

using namespace std;
int funcao;

void Menu_Administrador();
void Menu_de_Entrada();

void Cadastro_usuarios();
int main();

void Menu_de_Entrada(   )
{
    cout<<"+=======================================================+"<<endl;
    cout<<"|          CONTROLE DE EMPRÉSTIMOS DE LIVROS            |"<<endl;
    cout<<"+=======================================================+"<<endl;
    cout<<"Entre com seu User_ID para ter acesso ao sistema=>";
}
void Menu_Administrador()
{

    cout<<"       FUNÇÕES "<<endl;
    cout<<"1-Cadastrar usuário"<<endl;
    cout<<"2-Cadastrar livros"<<endl;
    cout<<"3-Desbloquear usuário"<<endl;
    cout<<"4-Remover usuário"<<endl;
    cout<<"5-listar livros"<<endl;
    cout<<"0-sair"<<endl;

    cin >> funcao;

    switch (funcao){
        case 0:
            main();
            break;
        case 1:
            Cadastro_usuarios();
        default:
            cout<<"\nFUNÇÃO NÃO EXISTE"<<endl;
            break;
        }
}
struct estudante : public error_code {
    string user_Id;
    string senha;

    estudante(const string & umUser_Id, string umSenha) {
        user_Id = umUser_Id;
        senha = umSenha;
    }
};

bool operator<(const estudante & este, const estudante & outro) {
    if (este.senha == outro.senha) {
        return este.user_Id < outro.user_Id;
    }
    return este.senha < outro.senha;
}

void Cadastro_usuarios() {

    ofstream arq("Cadastro_usuarios.txt");
    if (not arq.is_open()) {
        cout << "Algum erro ao abrir o arquivo ..." << endl;
        return ;
    }
    list<estudante>cadastro;
    string cad_senha, cad_user_Id;
    cout<<"Use Id e senha devem conter 8 carácteres";
    while ((funcao == 'n') || (funcao == 'N')) {
        cout<<"User ID =>";
        getline(cin,cad_user_Id);
        cout<<"senha =>";
        getline(cin,cad_senha);

        if (cad_user_Id.size()!=8){
            cout<<"User Id com mais de 8 carácteres";
            Cadastro_usuarios();
        }if (cad_senha.size()!=8){
            cout<<"Senha com mais de 8 carácteres";
            Cadastro_usuarios();
        }

        for (auto &dados: cadastro) {
            cout << dados.user_Id << "---------" << dados.senha << endl;
        }

        cout<<"DESEJA CONTINUAR CADASTRANDO:S/N"<<endl<<"FUNÇÕA=>";cin>>funcao;
    }
}

int main()
{
    int i=0,tenta=0;
    Menu_de_Entrada();
    string User_ID,adm_senha;
    while(i < 3){
        getline(cin, User_ID);
        if(User_ID=="adm"){
            while(tenta < 3) {
                cout << "Entre com a senha Adm =>";
                getline(cin, adm_senha);
                if(adm_senha=="1"){
                    Menu_Administrador();
                } else{
                    cout<<"SENHA INCORRETA TENTATIVA "<<tenta+1<<"-3"<<endl;
                    return 0;
                }
                tenta++;
            }
            }
        }
        i++;
    }
