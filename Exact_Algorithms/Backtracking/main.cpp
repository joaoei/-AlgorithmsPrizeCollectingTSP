#include <iostream>
#include <vector>
#include <chrono>

std::vector<int> alg_backtracking(
	std::vector<int> prizes, 
	std::vector<int> penaltys, 
	std::vector<std::vector<int>> travel_cost,
	std::vector<int> &result_p,
	int result_p_prize, 
	int result_p_penalty, 
	double prize_min) {

	
}

int main (int argc, char *argv[]) {
	/*
	  Receber parametros de qual instancia usar (10, 20, 30a, 30b, 30c, 50a, 50b, 100a, 100b, 
	  250a, 250b, 500a, 500b, 1000a, 1000b) e do alfa (entre 0.2, 0.5 e 0.8), 
	  caso não seja informado ou informado com um valor não suportado usar valores padrões
	*/

	/*
	  Ler dados do arquivo do arquivo informado pela operação acima
	  Escrever os premios em um vetor, as penalidades em outro vetor e os custos de locomoção em
	  uma matriz
	*/

	//Determinar prize_min = [Somatório dos premios] * alfa

	/*
	  DEPOIS DO ALGORITMO FUNCIONAR
	  - Executar algoritmo 
	  - Determinar tempo gasto para executar o algoritmo
	  - Exibir resultado (Arestas, o bonus e a penalidade)

 	return 0;
}