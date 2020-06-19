#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

//Função que recebe uma string e retorna uma char com o diretório para remover o arquivo que não existe
char arq_nao_existe(string caminho, char retorno[500]) {

    retorno[caminho.size() + 1];
    caminho.copy(retorno, caminho.size() +1);
    retorno[caminho.size()] = '\0';

}

int main() {

    int i=1;
    string arquivos,destino,diretorio_arq,linha;
    queue<string>arquivo_cop;
    queue<string>copy_diretorio_arq;
    fstream arq;
    ofstream copia;

    //recebe o diretório de destino dos arquivos
    cout<<"Diretório de destino dos arquivos=>";
    getline(cin,destino) ;
    cout<<endl;

    //loop para informar o nome dos arquivos a serem copiados e diretório atual do mesmo
    do{
        cout<<"Arquivo "<<i<<" =>";
        getline(cin,arquivos) ;

        //entra apenas se arquivo for diferente de espaço
        if(arquivos!=" ") {
            cout<<"Diretorio atual do arquivo "<<i<<" =>";
            getline(cin,diretorio_arq);
            //armazena os dados em fila
            arquivo_cop.push(arquivos);
            copy_diretorio_arq.push(diretorio_arq);
            cout<<"-----------------------------------"<<endl;
            i++;
        }
    }while(arquivos!=" ");

    //loop para copiar os arquivos
    while (!arquivo_cop.empty()){

        //verifica se o diretório de destino do arquivo existe
        copia.open(destino+'/'+arquivo_cop.front());
        if (copia.is_open()) {
            //verifica se arquivo a ser copiado existe
            arq.open(copy_diretorio_arq.front()+arquivo_cop.front());
            if (!arq.is_open()) {
                //arquivo não existente e diretorio de destino aberto no modo ofstream então necessita ser removido,
                cout<<"\33[1m"<<"ERRO arquivo "<<copy_diretorio_arq.front()+arquivo_cop.front()<<" não existe, não foi copiado "<< "\33[0m"<<endl;
                arq.close();
                char retorno[500];
                arq_nao_existe(destino+'/'+arquivo_cop.front(),retorno);
                remove(retorno);
            }
        } else{
            cout<<"\33[1m"<<"ERRO diretório de destino "<<destino<< "\33[0m"<<endl;
            return 0;
        }

        //copiar o arquivo
        while(getline(arq, linha)){
            copia << linha << endl;
        }

        arq.close();
        copia.close();
        arquivo_cop.pop();
        copy_diretorio_arq.pop();
    }

}





