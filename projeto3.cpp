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
	int escola_alocada;
	int prioridade_alocada;

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
						escola[j].professores_possiveis.push_back(k + 1); /*todos os professores serão possíveis*/
					}
					break;
				case 2:
					for(int k=0; k<100; k++){
						if(professor[k].habilitacoes >=2){
							escola[j].professores_possiveis.push_back(k + 1); /*todos os professores que tem 2 ou 3 habilitacoes*/
						}
					}
					break;
				case 3:
					for(int k=0; k<100; k++){
						if(professor[k].habilitacoes == 3){
							escola[j].professores_possiveis.push_back(k + 1); /*todos os professores que 3 habilitacoes*/
						}
					}
			}
			j++;
		}
	}
}
void Inicilizar_Flags(){
	int i;
	for(i=0;i<100;i++){
		professor[i].flag_professor =0;/*professor nao esta alocado em nenhuma escola ainda*/
		professor[i].escola_alocada = 0; 
	}
	for(i=0;i<50;i++){
		escola[i].flag_escola =2;/*inicializa a escola com duas vagas*/
	}
}

void emparelhamento(){
	int num_escolaAtual;
	int num_professor;/* mostra o numero do professor em que esta na lista do vetor das escolas*/
	int num_antiga_escola;
	int prioridade;
	int profs_alocados = 0;
	int achou;
	vector<int> teacher;
	vector<int> school;

	while (profs_alocados != 75) { /*Para parar quando todos os professores forem alocados(ta bugado)*/
		for(num_escolaAtual=0;num_escolaAtual<50;num_escolaAtual++){ /*fazer um loop para todas as escolas*/

			vector<int>::iterator aux_vetor = escola[num_escolaAtual].professores_possiveis.begin();
			while(escola[num_escolaAtual].flag_escola > 0 && aux_vetor != escola[num_escolaAtual].professores_possiveis.end()){ /*ira percorrer todo o vetor de escolas*/ 
				num_professor =*aux_vetor;															/*e verifica se ja tem os dois professores necessarios*/
				prioridade = 1;
				if(professor[num_professor - 1].flag_professor == 0){ /*Caso o professor ainda nao esteja alocado */
					vector<int>::iterator it = professor[num_professor - 1].escolas_prioridade.begin();
					
					professor[num_professor - 1].flag_professor = 1;/*Alocado mas pode ser mudado */
					professor[num_professor - 1].escola_alocada = escola[num_escolaAtual].cod_escola;
					escola[num_escolaAtual].flag_escola--;	
					achou = 0;
					while((it != professor[num_professor - 1].escolas_prioridade.end()) && (!achou) ){ /*ira percorrer todo o vetor dos professores para ver se a escola está na lista dele*/
						if(*it == escola[num_escolaAtual].cod_escola){
							professor[num_professor - 1].prioridade_alocada = prioridade;
							achou = 1;
						}
						prioridade++;
						it++;

						
					}
					if (!achou) {
						professor[num_professor - 1].prioridade_alocada = prioridade;
					} 

					profs_alocados++;
					
				}
				else { /*Caso o professor esteja alocado em uma escola que nao esta em sua lista */
					vector<int>::iterator it = professor[num_professor - 1].escolas_prioridade.begin(); /*Caso a escola esteja alocada mas em uma escola nao prioritaria */
					while(it != professor[num_professor - 1].escolas_prioridade.end() ){ /*ira percorrer todo o vetor dos professores para ver se a escola está na lista dele*/
						if(*it == escola[num_escolaAtual].cod_escola){
							if(prioridade < professor[num_professor - 1].prioridade_alocada) {
								num_antiga_escola = professor[num_professor - 1].escola_alocada;
								escola[num_antiga_escola - 1].flag_escola++; /*Abrindo uma vaga porque o professor foi realocado */
								professor[num_professor - 1].escola_alocada = escola[num_escolaAtual].cod_escola;
								professor[num_professor - 1].prioridade_alocada = prioridade;
								escola[num_escolaAtual].flag_escola--;	
							}
							
						}
						prioridade++;
						it++;
					}
				}
				aux_vetor++;
			}
			cout << profs_alocados << " ";
		}
		
	}

}
				
				

void escreve_resultado(){
	int i;
	
	for(i=0;i<100;i++) {
		cout << "Professor:" << professor[i].cod_professor << endl;
		cout << "Escolas preferidas:";
		vector<int>::iterator it = professor[i].escolas_prioridade.begin();
		while(it != professor[i].escolas_prioridade.end() ) {
			cout << " " <<*it;
			it++;
		}
		cout << endl;
		cout << "Escola alocada:" << professor[i].escola_alocada<< endl;
		/*getchar();*/
	}
}
void escreve_teste(){ /*Para ver quais escolas não alocaram ninguem */
	int i;
	
	for(i=0;i<50;i++) {
		cout << "Escola:" << escola[i].cod_escola << endl;
		cout << "professores possiveis:";
		vector<int>::iterator it = escola[i].professores_possiveis.begin();
		while(it != escola[i].professores_possiveis.end() ) {
			cout << " " <<*it;
			it++;
		}
		cout << endl;
		cout << "vagas:" << escola[i].flag_escola<< endl;
		getchar();
	}
}

/*Tentativa de fazer com o vetor ordenado
void ordena_vetor() {
	int trocou, i;
	t_escola aux;
	do {*/ /* Bubble sort */
	/*	trocou = 0;
		for (i = 0;i < 50; i++) {
			if (escola[i].habilitacoes_pretendidas < escola[i + 1].habilitacoes_pretendidas) {
				aux = escola[i];
				escola[i] = escola[i + 1];
				escola[i+1] = aux;
				trocou = 1;
			}
		}
	} while (trocou == 1);
}
	*/				
			
						
								

int main(){
	Fazer_grafo();
	Inicilizar_Flags();
	emparelhamento();
	escreve_teste();
	escreve_resultado();
	return 0;
}
