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

solution grasp_vns () {
    // solução = vazio
    // penalidade = infinito

    // FASE DE CONSTRUÇÃO
    for (int i = 0; i < maxInter; i++) {
        //s - solução parcial = vazio
        // 0 inserido como nó inicial em s 
        
        // todo k não pertencente a s
        for (int i2 = 0; i2 < nos.size(); i2++) {
            // calcula a economia nas inserções
        }

        while (premio < premio_min || existe economia positiva) {
            // LRC - Lista dos vertices com maior economia
            // Dado um alfa selecionar os n mais economicos
            // Selecionar um aleatoriamente
            // s <- s U {v}
            // Recalcula a economia nas inserções
        }

        if (penalidade(s) < penalidade(solucao) ) {
            solucao = s;
            penalidade(solucao) = penalidade(s)
        }
    }

    VNS(solucao);
    return solucao;
}

solution VNS (solution s) {
    // r = numero de vizinhanças 
    while (tempo sem melhora < maxTempo) {
        int k = 1;
        while (k <= r) {
            // Selecione um vizinho s_ qualquer da vizinhança N_k(s)
            s__ = VND(s_)
            if (penalidade(s__) < penalidade(s_)) {
                s = s__;
                k = 1;
            } else {
                k++;
            }
        }
    }

    return s;
}

solution VND (solution s) {
    // r = n de procedimentos de refinamento
    k = 1;
    while (k < r) {
        // seja s_ um otimo local segundo o k-esimo procedimento de refinamento
        if (penalidade(s_) < penalidade(s)) {
            s = s_;
            k = 1;
        } else {
            k++;
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
    
    return 0;
}