#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char * argv[]) {

    int encontrar=0,i=2;
    ifstream $aluno;
    string linha,sub,sep="$";

    $aluno.open(argv[1]);

    //Verifica se houve erro  ao arquivo foi aberto
    if (! $aluno.is_open()) {
        perror("Erro ao abrir o arquivo");
        return errno;
    }

    //lê as linhas do arquivo
    while (getline($aluno, linha)) {
        encontrar=linha.find_first_of(sep);
        while (encontrar!=string::npos){

            //separa a substring com o dado e o parametro a ser  na linha de argumentos
            //EX:argv[2]=cidade=São José.   substring com o parametro= cidade e dado=São José
            int enco_d1=0;
            string arg=argv[i],parametro,dado;
            enco_d1=arg.find("=");
            parametro=arg.substr(0,enco_d1);
            dado=arg.substr(enco_d1+1,linha.find_last_not_of(" "));

            /*substitu o dado do argumento da linha de comando de
            acordo com "$" e o tamanho  do parâmetro*/
            linha.replace(encontrar,parametro.size()+1,dado);
            i++;
            encontrar=linha.find_first_of(sep,encontrar);
        }
        cout << linha<<endl;
    }
}