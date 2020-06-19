#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "algorithm"
using namespace std;

// Tipo estudante: representa uma estudante com seu nome e matricula
struct estudante : public error_code {
    string nome;
    string matricula;

    estudante(const string & umNome, string umMatricula) {
        nome = umNome;
        matricula = umMatricula;
    }
};

// sobrecarga do operador< para o tipo estudante
bool operator<(const estudante & este, const estudante & outro) {
    if (este.nome == outro.nome) {
        return este.matricula < outro.matricula;
    }
    return este.nome < outro.nome;
}



int main(int argc, char *argv[]) {

    string linha,nome,matricula;
    list<estudante>dado;
    list<estudante>lista_estudantes_final;


    for(int i=1;i!=argc;i++){
        ifstream arq(argv[i]);
        if(arq.is_open()){
            while (getline(arq,linha)){
                dado.push_back(estudante(linha.substr(9,linha.size()-8),linha.substr(0,8)));
                dado.sort();
            }
        } else{
            cout<<"Arquivo "<<argv[i]<<" não existe"<<endl;
        }
    }

    for(auto &verificar_dados: dado){
        cout <<verificar_dados.matricula << " "<< verificar_dados.nome << endl;
    }

    for(auto &verificar_dados: dado){
        if((verificar_dados.nome!=nome)||(verificar_dados.matricula!=matricula)){
            lista_estudantes_final.push_back(verificar_dados);
            lista_estudantes_final.sort();
        }
        nome=verificar_dados.nome;
        matricula=verificar_dados.matricula;
    }
    cout<<endl<<"---------------------------------------------------------------------------"<<endl<<endl;

    for(auto &verificar_dados: lista_estudantes_final){
        cout <<verificar_dados.matricula << " "<< verificar_dados.nome << endl;
    }
    find (lista_estudantes_final.begin(), lista_estudantes_final.end(),35);


    cout<<endl<<"---------"<<dado.size()<<"-----------"<<lista_estudantes_final.size()<<endl<<endl;


}


