#include <iostream>
#include <fstream>
#include <sstream>
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

bool comp_desc (int i, int j) { return (i>j); }

int calc_prize_inf (
    std::vector<int> prizes, 
    const std::vector<int> &result_p,
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
    const std::vector<int> &penalties, 
    const std::vector<std::vector<int>> &travel_cost,
    const std::vector<int> &result_p,
    int num_vertices) 
{

    int sum_penalties = 0;
    for (int j = 0; j < penalties.size(); j++) {
        if (!is_on_list(j, result_p)) {
            sum_penalties += penalties[j];
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
    for (int i = 1; i < penalties.size(); i++) {
        if (is_on_list(i, result_p)) {
            inclusion_cost.push_back(10000);
        } else {
            min = 10000;
            for (int j = 0; j < travel_cost[i].size(); j++) {
                if (travel_cost[i][j] < min && travel_cost[i][j] > 0) {
                    min = travel_cost[i][j];
                }
            }
            inclusion_cost.push_back( (min - penalties[i]) );
        }
    }

    //Ordenar pelos menores custos
    std::sort(inclusion_cost.begin(), inclusion_cost.end());

    //Adicionar os n menores na soma dos custos
    int count = 0;
    int i = 0;
    int sum = sum_penalties + sum_travel;
    
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
    std::vector<int> penalties, 
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
        v_tuple up_limit_values = calc_prize_and_penalties(prizes, penalties, travel_cost, up_limit_v);

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

        v_tuple r = calc_prize_and_penalties(prizes, penalties, travel_cost, result_p);
    
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
                //Calcular penalties inferior
                int penalties_inf = calc_penalty_inf(penalties, travel_cost, result_p, i);

                if (penalties_inf < s.values.penalty) {
                    for (int j = 0; j < prizes.size(); j++) {
                        if (!is_on_list(j, result_p)) {
                            std::vector<int> r = result_p;
                            r.push_back(j);
                        
                            s = branch_and_bound_alg(
                                prizes, penalties, travel_cost,
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
            r = branch_and_bound_alg(prizes, penalties, edges, partial_sltn, up_limit, prizes.size()-1, p_min);
            end = std::chrono::steady_clock::now();
            average_time += (std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count()) / running_num;
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
    
    return 0;
}