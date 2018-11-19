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

    std::vector<solution> population;
    //std::vector<std::vector<int>> population;

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


    //while (condicao_de_parada) {
        // CALCULA O PREMIO E PENALIDADE DE CADA SOLUÇÃO DA POPULAÇÃO
        
        //Ordena pelo prize
        std::sort (population.begin(), population.end(), sort_function);

        /*
         * SELECIONA OS PAIS PARA REPRODUZIR
         * Selecionar as 4 melhores soluções e outras 2 aleatoriamente
         */

        int s1 = rand()%(population.size() - 4) + 4; 

        int s2 = s1;
        while (s1 == s2) {
            s2 = rand()%(population.size() - 4) + 4; 
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

/*
        for (int i = 0; i < population.size(); i++) {
            for (std::vector<int>::iterator it = population[i].v.begin(); it != population[i].v.end(); ++it)
                std::cout << ' ' << *it;
            std::cout << " Prize: " <<  population[i].values.prize << " Penaltys: " <<  population[i].values.penalty <<  '\n';
        }
        std::cout << '\n';
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
}


int main (int argc, char *argv[]) {
/*
*/  
    int a_pri[] = {0, 5, 7, 6};
    int a_pen[] = {900, 35, 2, 20};
    std::vector<int> pri (a_pri, a_pri + sizeof(a_pri) / sizeof(int) );
    std::vector<int> pen (a_pen, a_pen + sizeof(a_pen) / sizeof(int) );
    
    std::vector<std::vector<int>> t (4, std::vector<int> (4, 0));
    t[0][0] = 0;  t[0][1] = 13; t[0][2] = 5;  t[0][3] = 20;
    t[1][0] = 13; t[1][1] = 0;  t[1][2] = 7;  t[1][3] = 10;
    t[2][0] = 5;  t[2][1] = 7;  t[2][2] = 0;  t[2][3] = 17;
    t[3][0] = 20; t[3][1] = 10; t[3][2] = 17; t[3][3] = 0;
    
    alg_genetico(pri, pen, t, 7);

    return 0;
}