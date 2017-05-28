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
	int cod_professor;
	int habilitacoes;
	vector<int> escolas_prioridade;
	int flag_professor; 

}t_professor;

typedef struct 
{	
	int cod_escola;
	int habilitacoes_pretendidas;
	vector<int> professores_possiveis;
	int flag_escola;

}t_escola;

/*VARIAVEIS GLOBAIS =====================================================*/
t_professor professor[101];
t_escola escola[51];
/*=======================================================================*/ 
void Fazer_grafo(){
	int j=0 , escola_leitura, i=0;
	string line;
	ifstream fp("arquivo.txt");
	string aux;/*Serve para pegar o que nao precisa no arquivo lido*/
	while(!fp.eof()){
		getline(fp, line);	/*pega uma linha inteira do .txt*/
		stringstream is(line);/* 'is' passa a ser um tipo de leitura para a string no arquivo*/
		if(i<100){ /*faz leitura até da centésima linha do arquivo*/
			is >> aux >>  professor[i].cod_professor >> aux >> professor[i].habilitacoes >> aux;		
			while(is >> escola_leitura != NULL ){
				professor[i].escolas_prioridade.push_back(escola_leitura);/*coloca em um vetor a lista de prioridades das escolas*/
			}
			i++;
		}
		else{
			is >> aux >> escola[j].cod_escola >> aux >> escola[j].habilitacoes_pretendidas;
			switch (escola[j].habilitacoes_pretendidas) {	/*criar ligacoes direcionadas do grafo de escola para possiveis professores que poderiam aderir a escola*/
				case 1 : 
					for(int k=0; k<100;k++){
						escola[j].professores_possiveis.push_back(k); /*todos os professores serão possíveis*/
					}
					break;
				case 2:
					for(int k=0; k<100; k++){
						if(professor[k].habilitacoes >=2){
						escola[j].professores_possiveis.push_back(k); /*todos os professores que tem 2 ou 3 habilitacoes*/
						}
					}
					break;
				case 3:
					for(int k=0; k<100; k++){
						if(professor[k].habilitacoes == 3){
						escola[j].professores_possiveis.push_back(k); /*todos os professores que 3 habilitacoes*/
						}
					}
			}
			j++;
		}
	}
}
void Inicilizar_Flags(){
	for(int i=0;i<100;i++){
		professor[i].flag_professor =0;/*professor nao esta alocado em nenhuma escola ainda*/
	}
	for(int i=0;i<50;i++){
		escola[i].flag_escola =2;/*inicializa a escola com duas vagas*/
	}
}

void emparelhamento(){
	int num_escolaAtual;
	int num_professor;/* mostra o numero do professor em que esta na lista do vetor das escolas*/
	vector<int> teacher;
	vector<int> school;


	for(num_escolaAtual=0;num_escolaAtual<50;num_escolaAtual++){ /*fazer um loop para todas as escolas*/
		school.push_back(num_escolaAtual);
		school.push_back(num_escolaAtual);/*é colocado duas vezes para facilitar visualizar o match qnd for colocado os professores*/

		vector<int>::iterator aux_vetor = escola[num_escolaAtual].professores_possiveis.begin();
		while(escola[num_escolaAtual].flag_escola > 0 && aux_vetor != escola[num_escolaAtual].professores_possiveis.end()){ /*ira percorrer todo o vetor de escolas*/ 
			num_professor =*aux_vetor;															/*e verifica se ja tem os dois professores necessarios*/
			if(professor[num_professor].flag_professor == 0){
				vector<int>::iterator it = professor[num_professor].escolas_prioridade.begin();
				while(it != professor[num_professor].escolas_prioridade.end() ){ /*ira percorrer todo o vetor dos professores para ver se a escola está na lista dele*/
					if(*it == num_escolaAtual){
						int aux = *it;
						teacher.push_back(aux);
						professor[num_professor].flag_professor = 1;
						break;/*sai do while atual*/
					}
					it++;
				}		
			}
			aux_vetor++;
		}
	}

}
int main(){
	Fazer_grafo();
	Inicilizar_Flags();
}
