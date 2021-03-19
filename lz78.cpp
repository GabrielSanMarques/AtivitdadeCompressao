#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "windows.h"

using namespace std;

//Estrutura para representar um Nó.
//Um dicionário é uma lista encadeada de Nós.
struct No
{
    int indice;
    std::string data;
    No *proximo;
};

//Preenche os campos do Nó.
void stNo(No *head, int indice, string data)
{
    head->indice = indice;
    head->data = data;
    head->proximo = nullptr;
}

//Insere um novo Nó na lista encadeada.
void insereNo(No *head, int indice, string data)
{
    No *novoNo = new No;
    novoNo->indice = indice;
    novoNo->data = data;
    novoNo->proximo = nullptr;

    No *atual = head;
    while(atual != nullptr)
    {
        if(atual->proximo == nullptr)
        {
            atual->proximo = novoNo;
            return;
        }
        atual = atual->proximo;
    }
}

//Procura um Nó pela data.
No *buscaNo(No *head, string data)
{
    No *atual = head;
    while(atual != nullptr)
    {
        if(data.compare(atual->data) == 0)
            return atual;
        else   
            atual = atual->proximo;
    }
    return nullptr;
}

//Override: procura um Nó pelo índice.
No *buscaNo(No *head, int indice)
{
    No *atual = head;
    while(atual != nullptr)
    {
        if(indice == atual->indice)
            return atual;
        else
            atual = atual->proximo;
    }
    return nullptr;
}

//Remove um Nó da lista encadeada.
bool deletaNo(No *head, No *deletar)
{
    if(deletar == nullptr)
        return false;
    else if(deletar == head)
    {
        head = deletar->proximo;
        delete deletar;
        return true;
    }
    else
    {
        No *atual = head;
        while(atual)
        {
            if(atual->proximo == deletar)
            {
                atual->proximo = deletar->proximo;
                delete deletar;
                return true;
            }
            atual = atual->proximo;
        }
        return false;
    }
}

//Divide uma string em um vetor de substrings com base em um caractere delimitador.
vector<string> divide(string str, char delimitador)
{
    vector<string> interno;
    stringstream ss(str);
    string tok;

    while(getline(ss, tok, delimitador))
        interno.push_back(tok);

    return interno;
}

//Faz a codificação de uma string pelo método LZ-78.
string codifica_LZ78(string input)
{
    No *dicionario = new No;
    string palavra, resultado;
    int comprimento, ultimo, indice = 1;

    //Inicializa o dicionário e codifica o primeio caracter.
    comprimento = (int)input.length();
    palavra = input[0];
    stNo(dicionario, 1, palavra);
    resultado += "0," + palavra;

    //Codifica todos os caracteres do input.
    for(int i = 1; i < comprimento; i++)
    {
        string data;
        data = input[i];
    re_check:
        No *busca = buscaNo(dicionario, data);

        if(busca)
        {
            i++;
            data += input[i];
            ultimo = busca->indice;
            goto re_check;
        }
        else
        {
            char zero;
            if(input[i] == ' ')
                zero = '0';
            else
                zero = input[i];

            if((int)data.length() < 2)
                resultado += " " + to_string(0) + "," + zero;
            else
                resultado += " " + to_string(ultimo) + "," + zero;
            
            indice++;
            if(i != comprimento)
                insereNo(dicionario, indice, data);
        }
    }
    return resultado;
}

int main(int argc, char* argv[])
{    
    string file, resultado, frase;
    int i = 1;

    //entrada.txt é o arquivo de entrada padrão
    if(argc == 1)
        file = "entrada.txt";
    else
        file = argv[1];

    fstream entrada(file);

    ofstream saida("saida.txt");
    
    cout << "Imprimindo compressao em console e no arquivo 'saida.txt'" << endl;
    while(getline(entrada, frase))
    {
        resultado = resultado = codifica_LZ78(frase);
        cout << "\tLinha " << i << ": " << resultado << endl;
        saida << "Linha " << i << ": " << resultado << "\n";
        i++;
    }
}