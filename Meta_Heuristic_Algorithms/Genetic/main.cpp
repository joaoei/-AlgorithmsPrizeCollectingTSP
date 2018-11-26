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

bool sort_function (solution i, solution j) { 
    return (i.values.penalty < j.values.penalty); 
}

v_tuple calc_prize_and_penalties (
    const std::vector<int> &prizes, 
    const std::vector<int> &penalties, 
    const std::vector<std::vector<int>> &travel_cost,
    const std::vector<int> &result_p) 
{

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

void remove_repeated_item(solution &s) {
    //Verifica se existe algum valor repetido
    for (int i = s.v.size()-2; i > 0; i--) {
        for (int j = i-1; j > 0; j--) {
            if (s.v[i] == s.v[j]) {
                s.v.erase (s.v.begin()+j);
            }
        }
    }
}


void combine_vector(
    solution &s1, 
    solution &s2,
    solution &c1,
    solution &c2,
    int cutoff) 
{
    //Cria os filhos combinando pedaços dos pais
    c1 = s1;
    c2 = s2;

    c1.v.erase (c1.v.begin()+cutoff, c1.v.end());
    for (std::vector<int>::iterator it = s2.v.begin()+cutoff; it != s2.v.end(); ++it) { 
        c1.v.push_back(*it);
    }

    c2.v.erase (c2.v.begin()+cutoff, c2.v.end());
    for (std::vector<int>::iterator it = s1.v.begin()+cutoff; it != s1.v.end(); ++it) { 
        c2.v.push_back(*it);
    }

    //Verifica se existe algum valor repetido
    remove_repeated_item(c1);

    //Verifica se existe algum valor repetido
    remove_repeated_item(c2);
}

solution alg_genetico (
    int max_seconds,
    const std::vector<int> &prizes, 
    const std::vector<int> &penalties, 
    const std::vector<std::vector<int>> &travel_cost,
    const double &prize_min) 
{
    double max_seconds_milli = max_seconds * 1000;

    /* 
     * GERAR POPULAÇÃO INICIAL (DECIDIR NUMERO DE SOLUÇÕES CRIADAS)
     * Criar 8 soluções passando por todos os vertices
     * Gerando randomicamente qual vertice inserir no caminho
     */

    std::vector<solution> population;

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
        solution s;
        s.v = solution_n;
        s.values = calc_prize_and_penalties (prizes, penalties, travel_cost, solution_n);
        
        population.push_back(s);
    }

    solution s = population[0];

    std::chrono::steady_clock::time_point time_count;
    time_count = std::chrono::steady_clock::now();

    while ((std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::steady_clock::now() - time_count).count()) < max_seconds_milli) {
        //Ordena pelo prize
        std::sort (population.begin(), population.end(), sort_function);

        if ( population[0].values.penalty < s.values.penalty) {
            s = population[0];
            time_count = std::chrono::steady_clock::now();
        }

        /*
         * SELECIONA OS PAIS PARA REPRODUZIR
         * Selecionar as 4 melhores soluções e outras 2 aleatoriamente
         */

        int s1 = rand()%(population.size() - 5) + 5; 

        int s2 = s1;
        while (s1 == s2) {
            s2 = rand()%(population.size() - 5) + 5; 
        }

        if (s1 < s2) {
            population.erase (population.begin()+s2, population.end());
            population.erase (population.begin()+s1, population.begin()+s2-1);
            population.erase (population.begin()+4,  population.begin()+s1-1);
        } else {
            population.erase (population.begin()+s1, population.end());
            population.erase (population.begin()+s2, population.begin()+s1-1);
            population.erase (population.begin()+4,  population.begin()+s2-1);
        }

        /* RECOMBINAR (TROCA DE MATERIAIS GENETICOS DOS PAIS)
         * Combina todos os pais ou se escolhe os pares?
         * Selecionar os pares de pais (0, 3) (1, 4) e (2, 5)
         */
        for (int i = 0; i < 3; i++) {
            
            //Escolhe onde erá feita a divisão
            int m = population[i].v.size() < population[i+3].v.size() ? population[i].v.size() : population[i+3].v.size(); 
            int ponto_div = rand()%(m-2) + 2;

            //Definindo os dois filhos
            solution c1;
            solution c2;

            // Combinando os dados geneticos 
            combine_vector(population[i], population[i+3], c1, c2, ponto_div);

            /*
             * EFETUAR MUTAÇÃO NOS FILHOS
             * Escolher aleatoriamente uma posição do filho para ser modificada
             * Verificar se a solução continua sendo válida 
             * (sem nenhum vertice repetido e com o premio minimo coletado) 
             */
            int vert_mut = rand()%(c1.v.size()-2) + 1;
            int value = rand()%(prizes.size()-1) + 1;
            c1.v[vert_mut] = value;
            remove_repeated_item(c1);

            int vert_mut2 = rand()%(c2.v.size()-2) + 1;
            int value2 = rand()%(prizes.size()-1) + 1;
            c2.v[vert_mut2] = value2;
            remove_repeated_item(c2);

            //Verifica se os filhos continuam sendo soluções válidas
            c1.values = calc_prize_and_penalties (prizes, penalties, travel_cost, c1.v);
            while (c1.values.prize < prize_min) {
                int v = rand()%(prizes.size()-1) + 1;
                
                if (!is_on_list(v, c1.v)) {
                    c1.v[c1.v.size()-1] = v;
                    c1.v.push_back(0);
                    c1.values = calc_prize_and_penalties (prizes, penalties, travel_cost, c1.v);
                }
            }

            c2.values = calc_prize_and_penalties (prizes, penalties, travel_cost, c2.v);
            while (c2.values.prize < prize_min) {
                int v = rand()%(prizes.size()-1) + 1;
                
                if (!is_on_list(v, c2.v)) {
                    c2.v[c2.v.size()-1] = v;
                    c2.v.push_back(0);
                    c2.values = calc_prize_and_penalties (prizes, penalties, travel_cost, c2.v);
                }
            }

            /*
             * RENOVAR POPULAÇÃO 
             */
            population.push_back(c1);
            population.push_back(c2);
        }
    }

    // RETORNE MELHOR SOLUÇÃO
    return s;
}


int main (int argc, char *argv[]) {
    
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
        
        double alpha = 0.5; // Alfa padrão
        if (argc > 2) { // Passou valor do alfa
            alpha = std::stod(argv[2]);
        }
        int prizes_sum = 0;
        for (int i = 0; i < prizes.size(); ++i) {
            prizes_sum += prizes[i];
        }
        double p_min = alpha * prizes_sum;
        
        int running_num = 50; // Número de vezes que a instância será executada para tirar a média 
        int seconds_genetic = 12; // Número de segundos que o algortimo genético será executado
        double average_time = 0;
        std::chrono::steady_clock::time_point begin;
        std::chrono::steady_clock::time_point end;
        
        solution sol;
        solution best_sol;
        solution worst_sol;
        int best_sol_count = 0;
        for(int i = 0; i < running_num; i++) {
            // Medindo o tempo de execução
            begin = std::chrono::steady_clock::now();
            sol = alg_genetico(seconds_genetic, prizes, penalties, edges, p_min);
            end = std::chrono::steady_clock::now();
            average_time += ((std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count()) - (seconds_genetic * 1000)) / running_num;
            
            if(i == 0){
                best_sol = sol;
                worst_sol = sol;
                best_sol_count = 1;
                continue;
            }
            
            if(sol.values.penalty == best_sol.values.penalty) {
                best_sol_count++;
            } else if(sol.values.penalty < best_sol.values.penalty) {
                best_sol = sol;
                best_sol_count = 1;
            }
            
            if(sol.values.penalty > worst_sol.values.penalty) {
                worst_sol = sol;
            }
            
        }
        
        if (best_sol.values.prize == prizes[0] && best_sol.values.penalty == penalties[0]) {
            std::cout << "\nNo solution found for the input instance!";
        } else {
            std::cout << ">>> GENETIC ALGORITHM\n";
            std::cout << ">>> BEST SOLUTION\n";
            std::cout << "Number of vertices\n  " << num_vertices << "\n";
            std::cout << "Minimum prize (alpha = " << alpha << ")\n  " << p_min << "\n\n";

            std::cout << "Travel\n  ";
            for (int i = 0; i < best_sol.v.size() - 1; i++) {
                std::cout << "(" << best_sol.v[i] << "," <<best_sol.v[i+1] << ") ";  
            }
            std::cout << "\n";

            std::cout << "Total prizes\n  " << best_sol.values.prize << "\nTotal penalties\n  " << best_sol.values.penalty << "\n";
            std::cout << "Average execution time on " << running_num << " executions (ms)\n  " << average_time << std::endl;
            std::cout << "This solution was achieved on " << best_sol_count << " out of " << running_num << " executions" << std::endl;
            std::cout << ">>> WORST SOLUTION\n";
            std::cout << "Total penalties\n " << worst_sol.values.penalty << std::endl;
        }
    
    } else {
        std::cout << "Please, inform the input file name on execution!\n";
        return EXIT_FAILURE;
    }

    return 0;
}