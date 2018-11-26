#!/bin/bash

g++ -std=c++11 ./Genetic/main.cpp -o ./Genetic/genetic

# Genetic
./Genetic/genetic ./Instances/Genetic/v08.txt 0.2 > ./Results/Genetic/v08_02.txt
./Genetic/genetic ./Instances/Genetic/v08.txt 0.5 > ./Results/Genetic/v08_05.txt
./Genetic/genetic ./Instances/Genetic/v08.txt 0.8 > ./Results/Genetic/v08_08.txt

./Genetic/genetic ./Instances/Genetic/v09.txt 0.2 > ./Results/Genetic/v09_02.txt
./Genetic/genetic ./Instances/Genetic/v09.txt 0.5 > ./Results/Genetic/v09_05.txt
./Genetic/genetic ./Instances/Genetic/v09.txt 0.8 > ./Results/Genetic/v09_08.txt

./Genetic/genetic ./Instances/Genetic/v10.txt 0.2 > ./Results/Genetic/v10_02.txt
./Genetic/genetic ./Instances/Genetic/v10.txt 0.5 > ./Results/Genetic/v10_05.txt
./Genetic/genetic ./Instances/Genetic/v10.txt 0.8 > ./Results/Genetic/v10_08.txt

./Genetic/genetic ./Instances/Genetic/v11.txt 0.2 > ./Results/Genetic/v11_02.txt
./Genetic/genetic ./Instances/Genetic/v11.txt 0.5 > ./Results/Genetic/v11_05.txt
./Genetic/genetic ./Instances/Genetic/v11.txt 0.8 > ./Results/Genetic/v11_08.txt

./Genetic/genetic ./Instances/Genetic/v12.txt 0.2 > ./Results/Genetic/v12_02.txt
./Genetic/genetic ./Instances/Genetic/v12.txt 0.5 > ./Results/Genetic/v12_05.txt
./Genetic/genetic ./Instances/Genetic/v12.txt 0.8 > ./Results/Genetic/v12_08.txt

./Genetic/genetic ./Instances/Genetic/v13.txt 0.2 > ./Results/Genetic/v13_02.txt
./Genetic/genetic ./Instances/Genetic/v13.txt 0.5 > ./Results/Genetic/v13_05.txt
./Genetic/genetic ./Instances/Genetic/v13.txt 0.8 > ./Results/Genetic/v13_08.txt

./Genetic/genetic ./Instances/Genetic/v14.txt 0.2 > ./Results/Genetic/v14_02.txt
./Genetic/genetic ./Instances/Genetic/v14.txt 0.5 > ./Results/Genetic/v14_05.txt
./Genetic/genetic ./Instances/Genetic/v14.txt 0.8 > ./Results/Genetic/v14_08.txt

./Genetic/genetic ./Instances/Genetic/v15.txt 0.2 > ./Results/Genetic/v15_02.txt
./Genetic/genetic ./Instances/Genetic/v15.txt 0.5 > ./Results/Genetic/v15_05.txt
./Genetic/genetic ./Instances/Genetic/v15.txt 0.8 > ./Results/Genetic/v15_08.txt

# Testes do Artigo
./Genetic/genetic ./Instances/Genetic/v20.txt 0.75 > ./Results/Genetic/v20_075.txt

./Genetic/genetic ./Instances/Genetic/v30a.txt 0.75 > ./Results/Genetic/v30a_075.txt
./Genetic/genetic ./Instances/Genetic/v30b.txt 0.75 > ./Results/Genetic/v30b_075.txt
./Genetic/genetic ./Instances/Genetic/v30c.txt 0.75 > ./Results/Genetic/v30c_075.txt

./Genetic/genetic ./Instances/Genetic/v50a.txt 0.75 > ./Results/Genetic/v50a_075.txt
./Genetic/genetic ./Instances/Genetic/v50b.txt 0.75 > ./Results/Genetic/v50b_075.txt

./Genetic/genetic ./Instances/Genetic/v100a.txt 0.75 > ./Results/Genetic/v100a_075.txt
./Genetic/genetic ./Instances/Genetic/v100b.txt 0.75 > ./Results/Genetic/v100b_075.txt

./Genetic/genetic ./Instances/Genetic/v250a.txt 0.75 > ./Results/Genetic/v250a_075.txt