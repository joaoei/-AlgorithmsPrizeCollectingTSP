#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <climits>

struct v_tuple {
  int prize;
  int penalty;
};

struct solution {
    std::vector<int> v;
    v_tuple values;
};

v_tuple calc_prize_and_penaltys (
    const std::vector<int> &prizes, 
    const std::vector<int> &penaltys, 
    const std::vector<std::vector<int>> &travel_cost,
    const std::vector<int> &result_p) {

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

solution backtracking_alg (
    const std::vector<int> &prizes, 
    const std::vector<int> &penaltys, 
    const std::vector<std::vector<int>> &travel_cost,
    const std::vector<int> &result_p,
    const solution &result,
    const double &prize_min) {

    solution s = result;
    v_tuple r = calc_prize_and_penaltys(prizes, penaltys, travel_cost, result_p);
    
    /*
      Se o premio acumulado for maior ou igual que o premio minimo e 
      a penalidade for menor que a penalidade da solução atual
    */
    if (r.prize >= prize_min && r.penalty < s.values.penalty) {
        s.v = result_p;
        s.values = r;
    }
    
    //Chama o algoritmo de backtracking para cada possibilidade
    for (int i = 1; i < prizes.size(); i++) {
        if (!is_on_list(i, result_p)) {
            std::vector<int> r = result_p;
            r[ result_p.size()-1 ] = i;
            r.push_back (0);

            s = backtracking_alg (
                prizes, penaltys, travel_cost, 
                r, s, prize_min);
        }
    }

    return s; 
}

static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

int main (int argc, char *argv[]) {

    if (argc > 1) {
        std::string file_name = argv[1];
        std::ifstream infile(file_name);
        if(!infile) {
            std::cout << "Unable to open file!\n";
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
        // Ler valores dos prêmios
        std::getline(infile, line);
        std::getline(infile, line);
        std::istringstream prizes_line(line);
        int prize;
        std::vector<int> prizes;
        while (prizes_line >> prize) {
            prizes.push_back(prize);
        }
        num_vertices = prizes.size();

        // Ler valores das penalidades
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
    }

    std::vector<int> p (4, 0);
    p[0] = 0;
    p[1] = 39;
    p[2] = 1;
    p[3] = 62;

    std::vector<int> p2 (4, 0);
    p2[0] = 100000;
    p2[1] = 548;
    p2[2] = 475;
    p2[3] = 6;

    std::vector<std::vector<int>> t (4, std::vector<int>(4, 0) );
    t[0][0] = 0;   t[0][1] = 66;  t[0][2] = 820; t[0][3] = 889;
    t[1][0] = 66;  t[1][1] = 0;   t[1][2] = 505; t[1][3] = 56;
    t[2][0] = 820; t[2][1] = 505; t[2][2] = 0;   t[2][3] = 987;
    t[3][0] = 889; t[3][1] = 56;  t[3][2] = 987; t[3][3] = 0;


    std::vector<int> rp (2, 0);

    solution r1;
    v_tuple values;
    values.prize   = p[0];
    values.penalty = p2[0];
    r1.v = rp;
    r1.values = values;

    double alfa = 0.5;
    double p_min = 102*alfa;
    solution r = backtracking_alg(p, p2, t, rp, r1, p_min);

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