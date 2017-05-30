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
	vector<int> professores_possiveis_ordenado;

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
						escola[j].professores_possiveis_ordenado.push_back(k + 1); /*todos os professores serão possíveis*/
					}
					break;
				case 2:
					for(int k=0; k<100; k++){
						if(professor[k].habilitacoes >=2){
							escola[j].professores_possiveis.push_back(k + 1); /*todos os professores que tem 2 ou 3 habilitacoes*/
							escola[j].professores_possiveis_ordenado.push_back(k + 1); /*todos os professores que tem 2 ou 3 habilitacoes*/
						}
					}
					break;
				case 3:
					for(int k=0; k<100; k++){
						if(professor[k].habilitacoes == 3){
							escola[j].professores_possiveis.push_back(k + 1); /*todos os professores que 3 habilitacoes*/
							escola[j].professores_possiveis_ordenado.push_back(k + 1); /*todos os professores que 3 habilitacoes*/
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

	while (profs_alocados != 81) { /*Para parar quando todos os professores forem alocados(ta bugado)*/
		for(num_escolaAtual=0;num_escolaAtual<50;num_escolaAtual++){ /*fazer um loop para todas as escolas*/

			vector<int>::iterator aux_vetor = escola[num_escolaAtual].professores_possiveis_ordenado.begin();
			while(escola[num_escolaAtual].flag_escola > 0 && aux_vetor != escola[num_escolaAtual].professores_possiveis_ordenado.end()){ /*ira percorrer todo o vetor de escolas*/ 
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
		}
	}

}
void Alocar_Restante_Preferencia_Professor(){ /*Alocar os professores que querem uma escola, mesmo ela não aceitando devido as suas habilitações*/
	vector<int> professores_restante;
	vector<int> escolas_restante;
	int i ,tamanho_prof_restante,entrou=0, tamanho2, j, marca_vetor, valor_escola_k, k, tamanho_esc_restante;
	for(i=0;i<100;i++){	/*pega todos os professores restantes*/
		if(professor[i].escola_alocada == 0){
			professores_restante.push_back(i);	
		}
	}
	for(i=0;i<50;i++){	/*pega todas as escolas restantes*/
		if(escola[i].flag_escola > 0){
			escolas_restante.push_back(i);
		}
	}

	tamanho_prof_restante =  professores_restante.size();	/*gravar tamanho para loop*/
	tamanho_esc_restante = escolas_restante.size();			/*gravar tamanho para loop*/	
	
	for(i=0;i<tamanho_prof_restante;i++){
		marca_vetor = professores_restante[i];
		tamanho2 = professor[marca_vetor].escolas_prioridade.size(); /*gravar tamanho para loop*/
		for(j=0;j<tamanho2;j++){
			for(k=0;k<tamanho_esc_restante;k++){
				valor_escola_k = escolas_restante[k];
				if(escolas_restante[k] == professor[marca_vetor].escolas_prioridade[j] && escola[valor_escola_k].flag_escola >0){/*verifica se a escola contem a area do professor e se a escola ainda tem vaga*/
					escola[valor_escola_k].flag_escola = escola[valor_escola_k].flag_escola -1;
					professor[marca_vetor].escola_alocada = valor_escola_k;
					professor[marca_vetor].flag_professor =1;
			
 					entrou =1;
 					break;
				}
			}
			if(entrou == 1){
				entrou=0;
				break;
			}
		}
	}
}				

void escreve_resultado(){
	int i, l;
	
	for(i=0;i<100;i++) {
		cout << "Professor:" << professor[i].cod_professor << endl;
		cout << "Escolas preferidas:";
		vector<int>::iterator it = professor[i].escolas_prioridade.begin();
		while(it != professor[i].escolas_prioridade.end() ) {
			cout << " " <<*it;
			it++;
		}
		cout << endl;
		cout << "Escola alocada:" << professor[i].escola_alocada<< endl <<endl;
		/*getchar();*/
		if(professor[i].escola_alocada == 0){
			l++;
		}
	}
	cout << "\n\n l == " << l << endl;
}

						
void Ordena_Professor(){
	int trocou =1, i, aux, tamanho, valor1, valor2, j;

	for(j=0;j<50;j++){
		tamanho = escola[j].professores_possiveis_ordenado.size(); 
		while(trocou ==1){
	
			trocou =0;
		
			for(i=0;i<tamanho-2;i++){
				valor1 = escola[j].professores_possiveis_ordenado[i];	
				valor2 = escola[j].professores_possiveis_ordenado[i+1]; 
				if(professor[valor1-1].habilitacoes > professor[valor2-1].habilitacoes ){
					aux = escola[j].professores_possiveis_ordenado[i];
					escola[j].professores_possiveis_ordenado[i] = escola[j].professores_possiveis_ordenado[i+1];
					escola[j].professores_possiveis_ordenado[i+1] = aux;
					trocou=1;
				}
			}
		}
		trocou =1;
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
int main(){
	Fazer_grafo();
	Inicilizar_Flags();
	Ordena_Professor();
	emparelhamento();
	Alocar_Restante_Preferencia_Professor();	
	escreve_resultado();
	return 0;
}
