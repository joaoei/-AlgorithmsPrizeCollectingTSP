#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <stdlib.h>   

struct v_tuple {
  int prize;
  int penalty;
};

struct solution {
    std::vector<int> v;
    v_tuple values;
};

v_tuple calc_prize_and_penalties (
    const std::vector<int> &prizes, 
    const std::vector<int> &penalties, 
    const std::vector<std::vector<int>> &travel_cost,
    const std::vector<int> &result_p) {

    int sum_penalties = 0;
    int sum_prizes   = 0;

    //Soma todas as penalidades
    for(int i = 0; i < penalties.size(); i++) {
        sum_penalties += penalties[i];
    }

    for(int j = 0; j < result_p.size() - 1; j++) {
        //Soma premio do no na posição j em result
        sum_prizes   += prizes[result_p[j]];
        sum_penalties -= penalties[result_p[j]];
        sum_penalties += travel_cost[ result_p[j] ][ result_p[j+1] ];
    }

    v_tuple value;
    value.prize = sum_prizes;
    value.penalty = sum_penalties;

    return value;
}

bool is_on_list (
    int element,
    const std::vector<int> &v) {

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

// solution
void alg_genetico (
    const std::vector<int> &prizes, 
    const std::vector<int> &penalties, 
    const std::vector<std::vector<int>> &travel_cost,
    const double &prize_min) 
{

    /* 
     * GERAR POPULAÇÃO INICIAL (DECIDIR NUMERO DE SOLUÇÕES CRIADAS)
     * Criar 8 soluções passando por todos os vertices
     * Gerando randomicamente qual vertice inserir no caminho
     */

    //std::vector<solution> population;
    std::vector<std::vector<int>> population;

    // Cria vetor com todos as cidades
    std::vector<int> cities (prizes.size()-1, 0);
    for (int i = 0; i < cities.size(); i++) {
        cities[i] = i+1;
    }

    srand((unsigned)time(0));

    // Cria as 8 soluções
    for (int j = 0; j < 8; j++) {

        std::vector<int> available_cities = cities;

        std::vector<int> solution_n (prizes.size()+1, 0);
        
        // Adiciona as cidades no caminho
        for (int p = 1; p < solution_n.size() - 1; p++) {
            int n = rand()%( available_cities.size() );

            solution_n[p] = available_cities[n];

            available_cities.erase(available_cities.begin()+n);
        }

        // Adiciona a solução criada na população
        population.push_back(solution_n);
    }

    //while (condicao_de_parada) {
        // CALCULA O PREMIO E PENALIDADE DE CADA SOLUÇÃO DA POPULAÇÃO
        
        /*
         * SELECIONA OS PAIS PARA REPRODUZIR
         * Selecionar as 4 melhores soluções e outras 2 aleatoriamente
         */ 

        /* RECOMBINAR (TROCA DE MATERIAIS GENETICOS DOS PAIS)
         * Combina todos os pais ou se escolhe os pares?
         */

        /*
         * EFETUAR MUTAÇÃO NOS FILHOS
         * Escolher aleatoriamente uma posição do filho para ser modificada
         * Verificar se a solução continua sendo válida 
         * (sem nenhum vertice repetido e com o premio minimo coletado) 
         */

        /*
         * RENOVAR POPULAÇÃO 
         */
    //}

    // RETORNE MELHOR SOLUÇÃO

    for (int i = 0; i < population.size(); i++) {
        for (std::vector<int>::iterator it = population[i].begin(); it != population[i].end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }

    std::cout << '\n';
}


int main (int argc, char *argv[]) {
/*
    if (argc > 1) {
        std::string file_name = argv[1];
        std::ifstream infile(file_name);
        if(!infile) {
            std::cout << ">>> Unable to open file!\n";
            return EXIT_FAILURE;
        }

        // Pega o nome do arquivo sem diretórios
        std::string file_name_no_path = file_name;
        size_t i = file_name.rfind('/', file_name.length());
        if (i != std::string::npos) {
          file_name_no_path = file_name.substr(i+1, file_name.length() - i);
        }

        std::string line;
        if (file_name_no_path[0] == 'v') { // instancias-1
            std::getline(infile, line);
            std::getline(infile, line);
        }

        int num_vertices = 0;
        // Lê valores dos prêmios
        std::getline(infile, line);
        std::getline(infile, line);
        std::istringstream prizes_line(line);
        int prize;
        std::vector<int> prizes;
        while (prizes_line >> prize) {
            prizes.push_back(prize);
        }
        num_vertices = prizes.size();

        // Lê valores das penalidades
        std::getline(infile, line);
        std::getline(infile, line);
        std::getline(infile, line);
        std::istringstream penalties_line(line);
        int penalty; // valor do vértice
        std::vector<int> penalties;
        while (penalties_line >> penalty) {
            penalties.push_back(penalty);
        }

        if (prizes.size() != penalties.size()) {
            std::cout << ">>> Invalid instance: number of prizes and penalties don't match!" << '\n';
            return EXIT_FAILURE;
        }

        // Ler valores dos vértices
        std::getline(infile, line);
        std::getline(infile, line);
        std::vector<std::vector<int>> edges(num_vertices);
        int edge; // valor do vértice
        int curr_num = 0;
        for (int i = 0; i < num_vertices; ++i) {
            std::getline(infile, line);
            std::istringstream edges_line(line);
            while(edges_line >> edge) {
                edges[i].push_back(edge);
            }
            if (i > 0) {
                if (curr_num != edges[i].size()) {
                    std::cout << ">>> Invalid instance: incorrect number of edges!" << '\n';
                    return EXIT_FAILURE;
                }
            }
            curr_num = edges[i].size();
        }

        ///////////////////////////////////////////////////////
        std::vector<int> partial_sltn (1, 0);

        solution up_limit;
        double alpha = 0.5; // Alfa padrão
        if (argc > 2) { // Passou valor do alfa
            alpha = std::stod(argv[2]);
        }
        int prizes_sum = 0;
        for (int i = 0; i < prizes.size(); ++i) {
            prizes_sum += prizes[i];
        }
        double p_min = alpha * prizes_sum;
        
        int running_num = 3; // Número de vezes que a instância será executada para tirar a média 
        double average_time = 0;
        std::chrono::steady_clock::time_point begin;
        std::chrono::steady_clock::time_point end;
        solution r;
        for(int i = 0; i < running_num; i++) {
            // Medindo o tempo de execução
            begin = std::chrono::steady_clock::now();
            // r = branch_and_bound_alg(prizes, penalties, edges, partial_sltn, up_limit, prizes.size()-1, p_min);
            end = std::chrono::steady_clock::now();
            // average_time += (std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count()) / running_num;
        }

        if (r.values.prize == prizes[0] && r.values.penalty == penalties[0]) {
            std::cout << "\nNo solution found for the input instance!";
        } else {
            std::cout << ">>> Branch and Bound\n";
            std::cout << "Number of vertices\n  " << num_vertices << "\n";
            std::cout << "Minimum prize (alpha = " << alpha << ")\n  " << p_min << "\n\n";

            std::cout << "Travel\n  ";
            for (int i = 0; i < r.v.size() - 1; i++) {
                std::cout << "(" << r.v[i] << "," << r.v[i+1] << ") ";  
            }
            std::cout << "\n";

            std::cout << "Total prizes\n  " << r.values.prize << "\nTotal penalties\n  " << r.values.penalty << "\n";
            std::cout << "Average execution time on " << running_num << " executions (ms)\n  " << average_time << std::endl;
        }
    } else {
        std::cout << "Please, inform the input file name on execution!\n";
        return EXIT_FAILURE;
    }
*/  
    int myints[] = {0, 1, 2, 3};
    std::vector<int> pri (myints, myints + sizeof(myints) / sizeof(int) );
    std::vector<int> pen (myints, myints + sizeof(myints) / sizeof(int) );
    std::vector<std::vector<int>> t (2, std::vector<int> (3, 0));
    
    alg_genetico(pri, pen, t, 10);

    return 0;
}