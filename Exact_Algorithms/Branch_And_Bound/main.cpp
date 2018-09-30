#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

struct v_tuple {
  int prize;
  int penalty;
};

struct solution {
	std::vector<int> v;
	v_tuple values;
};

bool is_on_list (
	int element,
	std::vector<int> v) {

	bool is_element = false;
	int i = 0;

	while ( !is_element && (i < v.size()) ) {
		if (element == v[i]) {
			is_element = true;
		}

		i++;
	}

	return is_element;
}

v_tuple calc_prize_and_penaltys (
	std::vector<int> prizes, 
	std::vector<int> penaltys, 
	std::vector<std::vector<int>> travel_cost,
	std::vector<int> result_p) 
{

	int sum_penaltys = 0;
	int sum_prizes   = 0;

	//Soma todas as penalidades
	for(int i = 0; i < penaltys.size(); i++) {
		sum_penaltys += penaltys[i];
	}

	for(int j = 0; j < result_p.size() - 1; j++) {
		//Soma premio do no na posição j em result
		sum_prizes   += prizes[result_p[j]];
		sum_penaltys -= penaltys[result_p[j]];
		sum_penaltys += travel_cost[ result_p[j] ][ result_p[j+1] ];
	}

	v_tuple value;
	value.prize = sum_prizes;
	value.penalty = sum_penaltys;

	return value;
}

bool comp_desc (int i, int j) { return (i>j); }

int calc_prize_inf (
	std::vector<int> prizes, 
	std::vector<int> result_p,
	int num_vertices) {

	int prize = 0;
	for (int i = 0; i < result_p.size(); i++) {
			prize += prizes[ result_p[i] ];
	}

	for (int i = 0; i < result_p.size(); i++) {
		prizes[result_p[i]] = 0;
	}	

	std::sort(prizes.begin(), prizes.end(), comp_desc);

	int count = 0;
	int i = 0;
	
	while (count < num_vertices) {
		prize += prizes[i];
		count++;
		i++;
	}

	return prize;
}

int calc_penalty_inf (
	std::vector<int> penaltys, 
	std::vector<std::vector<int>> travel_cost,
	std::vector<int> result_p,
	int num_vertices) 
{

	int sum_penaltys = 0;
	for (int j = 0; j < penaltys.size(); j++) {
		if (!is_on_list(j, result_p)) {
			sum_penaltys += penaltys[j];
		}
	}
	// Soma os custos das arestas
	int min;
	int sum_travel = 0;
	for (int i = 0; i < result_p.size(); i++) {
		if (i == result_p.size()-1) {
			// Acha a aresta de menor valor e soma nas penalidades
			min = 10000;
			for (int j = 0; j < travel_cost[i].size(); j++) {
				if (travel_cost[ result_p[i] ][j] < min && travel_cost[ result_p[i] ][j] > 0) {
					min = travel_cost[ result_p[i] ][j];
				}
			}
			sum_travel += min;
		} else {
			sum_travel += travel_cost[result_p[i]][result_p[i+1]];
		}
	}

	//Custo de inclusão
	std::vector<int> inclusion_cost (1, 10000); 
	for (int i = 1; i < penaltys.size(); i++) {
		if (is_on_list(i, result_p)) {
			inclusion_cost.push_back(10000);
		} else {
			min = 10000;
			for (int j = 0; j < travel_cost[i].size(); j++) {
				if (travel_cost[i][j] < min && travel_cost[i][j] > 0) {
					min = travel_cost[i][j];
				}
			}
			inclusion_cost.push_back( (min - penaltys[i]) );
		}
	}

	//Ordenar pelos menores custos
	std::sort(inclusion_cost.begin(), inclusion_cost.end());

	//Adicionar os n menores na soma dos custos
	int count = 0;
	int i = 0;
	int sum = sum_penaltys + sum_travel;
	
	while (count < num_vertices) {
		sum += inclusion_cost[i];
		count++;
		i++;
	}

	//Retornar penalidades
	return sum; 
}

solution branch_and_bound_alg (
	std::vector<int> prizes, 
	std::vector<int> penaltys, 
	std::vector<std::vector<int>> travel_cost,
	std::vector<int> result_p,
	solution up_limit,
	int num_vertices,
	double prize_min) {
	solution s;

	//calcular a up limit
	if (num_vertices == prizes.size()-1) 
	{
		//Cria vetor com com vertices (0, 1, ..., N, 0)
		std::vector<int> up_limit_v (1, 0);
		for (int i = 1; i < prizes.size(); i++) {
			up_limit_v.push_back(i);
		}
		up_limit_v.push_back(0);

		//Calcula o prêmio e as penalidades dessa solução
		v_tuple up_limit_values = calc_prize_and_penaltys(prizes, penaltys, travel_cost, up_limit_v);

		//Cria uma solução que será o limite superior
		solution limit;
		limit.v = up_limit_v;
		limit.values = up_limit_values;
		s = limit;
	} else {
		s = up_limit;
	}
	
	if (num_vertices == 0) {
		result_p.push_back(0);

		v_tuple r = calc_prize_and_penaltys(prizes, penaltys, travel_cost, result_p);
	
		/*
		  Se o premio acumulado for maior ou igual que o premio minimo e 
		  a penalidade for menor que a penalidade da solução atual
		*/
		if (r.prize >= prize_min && r.penalty < s.values.penalty) {
			s.v = result_p;
			s.values = r;
		}
	} else {
		int c = (num_vertices == prizes.size()-1 ) ? 1 : num_vertices;
		for (int i = c; i <= num_vertices; i++) {
			int prize_inf = calc_prize_inf(prizes, result_p, i);
			
			if (prize_inf >= prize_min) {
				//Calcular penaltys inferior
				int penaltys_inf = calc_penalty_inf(penaltys, travel_cost, result_p, i);

				if (penaltys_inf < s.values.penalty) {
					for (int j = 0; j < prizes.size(); j++) {
						if (!is_on_list(j, result_p)) {
							std::vector<int> r = result_p;
							r.push_back(j);
						
							s = branch_and_bound_alg(
								prizes, penaltys, travel_cost,
								r, s, i - 1, prize_min
							);
						}
					}
				}
			}
			
		}
	}

	return s;

}

int main (int argc, char *argv[]) {

	//Prêmios
	std::vector<int> p (4, 0);
	p[0] = 0;
	p[1] = 39;
	p[2] = 1;
	p[3] = 62;

	//Penalidades
	std::vector<int> p2 (4, 0);
	p2[0] = 100000;
	p2[1] = 548;
	p2[2] = 475;
	p2[3] = 6;

	//Custo de trajeto do vertice i ao j
	std::vector<std::vector<int>> t (4, std::vector<int>(4, 0) );
	t[0][0] = 0;   t[0][1] = 66;  t[0][2] = 820; t[0][3] = 889;
	t[1][0] = 66;  t[1][1] = 0;   t[1][2] = 505; t[1][3] = 56;
	t[2][0] = 820; t[2][1] = 505; t[2][2] = 0;   t[2][3] = 987;
	t[3][0] = 889; t[3][1] = 56;  t[3][2] = 987; t[3][3] = 0;

	//Cria vetor com 2 valores 0 para a solução parcial
	std::vector<int> rp (1, 0);

	solution up_limit;

	double alfa = 0.3;
	double p_min = 102*alfa;
	solution r = branch_and_bound_alg(p, p2, t, rp, up_limit, p.size()-1, p_min);

	if (r.values.prize == p[0] && r.values.penalty == p2[0]) {
		std::cout << "\nSem resolução para o problema";
	} else {
		std::cout << "\nResult: ";
		
		for (int i = 0; i < r.v.size() - 1; i++) {
			std::cout << "(" << r.v[i] << "," << r.v[i+1] << ") ";	
		}
		
		std::cout << "\n";	

		std::cout << "Prize min: " << p_min << "\n";
		std::cout << "Prize: " << r.values.prize << " | Penaltys: " << r.values.penalty << "\n";
	}

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
	*/
	
 	return 0;
}