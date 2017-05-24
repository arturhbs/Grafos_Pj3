/*Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao

Teroria e aplicação de grafos - 01/2017

Alunos(a): Artur Henrique Brandao de Souza	- 15/0118783 
		   Marcos Paulo Batalha Bispo - 15/O154208
							
Versão do compilador: gcc(GCC) 4.8.1

Descricao:	Projeto3
*/


#include <sstream> 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
typedef struct 
{
	string cod_professor;
	int habilitacoes;
	vector<string> escolas_prioridade; 
}t_professor;

typedef struct 
{	
	string cod_escola;
	int habilitacoes_pretendidas;
}t_escola;

/*VARIAVEIS GLOBAIS =====================================================*/
t_professor professor[101];
t_escola escola[51];
/*=======================================================================*/

void leitura_arquivo(){
	int j=0;
	string line;
	ifstream fp("arquivo.txt");
	string escola_leitura;
	int i =0;
	while(!fp.eof()){
		getline(fp, line);	/*pega uma linha inteira do .txt*/
		stringstream is(line);/* 'is' passa a ser um tipo de leitura para a string no arquivo*/
		if(i<100){ /*faz leitura até da centésima linha do arquivo*/
			is >>  professor[i].cod_professor >> professor[i].habilitacoes;
			while(is >> escola_leitura != NULL ){
				professor[i].escolas_prioridade.push_back(escola_leitura);/*coloca em um vetor a lista de prioridades das escolas*/
				cout << "escola = " << escola_leitura << endl;		
			}
			cout << "cod_professor == "<< professor[i].cod_professor <<endl << "habilitacoes == " <<  professor[i].habilitacoes<<endl;
			i++;
			cout << " -------------" << endl;
		}
		else{
			is >> escola[j].cod_escola >> escola[j].habilitacoes_pretendidas;
			cout << "cod_escola = " <<  escola[j].cod_escola<< endl << "habilitacoes_pretendidas =  " << escola[j].habilitacoes_pretendidas << endl << "============" << endl; 
			j++;
		}

	}
}
int main(){
	leitura_arquivo();
}