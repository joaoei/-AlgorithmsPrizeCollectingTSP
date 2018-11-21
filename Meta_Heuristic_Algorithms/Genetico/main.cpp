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
    //TESTES
    int a_pri[] = {0, 5, 7, 6};
    int a_pen[] = {900, 35, 2, 20};
    std::vector<int> pri (a_pri, a_pri + sizeof(a_pri) / sizeof(int) );
    std::vector<int> pen (a_pen, a_pen + sizeof(a_pen) / sizeof(int) );
    
    std::vector<std::vector<int>> t (4, std::vector<int> (4, 0));
    t[0][0] = 0;  t[0][1] = 5; t[0][2] = 5;  t[0][3] = 20;
    t[1][0] = 5; t[1][1] = 0;  t[1][2] = 7;  t[1][3] = 10;
    t[2][0] = 5;  t[2][1] = 7;  t[2][2] = 0;  t[2][3] = 17;
    t[3][0] = 20; t[3][1] = 10; t[3][2] = 17; t[3][3] = 0;
    
    solution s = alg_genetico(10, pri, pen, t, 7);

    for (std::vector<int>::iterator it = s.v.begin(); it != s.v.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << " - Prize: " << s.values.prize << " Penalty: " << s.values.penalty << '\n';

    return 0;
}