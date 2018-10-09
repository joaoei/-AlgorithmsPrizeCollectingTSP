#!/bin/bash

g++ -std=c++11 ./Backtracking/main.cpp -o ./Backtracking/back_alg
g++ -std=c++11 ./Branch_And_Bound/main.cpp -o ./Branch_And_Bound/alg_b_and_b

# Backtracking
./Backtracking/back_alg ./Instances/Backtracking/v08.txt 0.2 > ./Results/Backtracking/v08_02.txt
./Backtracking/back_alg ./Instances/Backtracking/v08.txt 0.5 > ./Results/Backtracking/v08_05.txt
./Backtracking/back_alg ./Instances/Backtracking/v08.txt 0.8 > ./Results/Backtracking/v08_08.txt

./Backtracking/back_alg ./Instances/Backtracking/v09.txt 0.2 > ./Results/Backtracking/v09_02.txt
./Backtracking/back_alg ./Instances/Backtracking/v09.txt 0.5 > ./Results/Backtracking/v09_05.txt
./Backtracking/back_alg ./Instances/Backtracking/v09.txt 0.8 > ./Results/Backtracking/v09_08.txt

./Backtracking/back_alg ./Instances/Backtracking/v10.txt 0.2 > ./Results/Backtracking/v10_02.txt
./Backtracking/back_alg ./Instances/Backtracking/v10.txt 0.5 > ./Results/Backtracking/v10_05.txt
./Backtracking/back_alg ./Instances/Backtracking/v10.txt 0.8 > ./Results/Backtracking/v10_08.txt

./Backtracking/back_alg ./Instances/Backtracking/v11.txt 0.2 > ./Results/Backtracking/v11_02.txt
./Backtracking/back_alg ./Instances/Backtracking/v11.txt 0.5 > ./Results/Backtracking/v11_05.txt
./Backtracking/back_alg ./Instances/Backtracking/v11.txt 0.8 > ./Results/Backtracking/v11_08.txt

./Backtracking/back_alg ./Instances/Backtracking/v12.txt 0.2 > ./Results/Backtracking/v12_02.txt
./Backtracking/back_alg ./Instances/Backtracking/v12.txt 0.5 > ./Results/Backtracking/v12_05.txt
./Backtracking/back_alg ./Instances/Backtracking/v12.txt 0.8 > ./Results/Backtracking/v12_08.txt

# Branch and Bound
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v08.txt 0.2 > ./Results/Branch_and_Bound/v08_02.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v08.txt 0.5 > ./Results/Branch_and_Bound/v08_05.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v08.txt 0.8 > ./Results/Branch_and_Bound/v08_08.txt

./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v09.txt 0.2 > ./Results/Branch_and_Bound/v09_02.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v09.txt 0.5 > ./Results/Branch_and_Bound/v09_05.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v09.txt 0.8 > ./Results/Branch_and_Bound/v09_08.txt

./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v10.txt 0.2 > ./Results/Branch_and_Bound/v10_02.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v10.txt 0.5 > ./Results/Branch_and_Bound/v10_05.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v10.txt 0.8 > ./Results/Branch_and_Bound/v10_08.txt

./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v11.txt 0.2 > ./Results/Branch_and_Bound/v11_02.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v11.txt 0.5 > ./Results/Branch_and_Bound/v11_05.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v11.txt 0.8 > ./Results/Branch_and_Bound/v11_08.txt

./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v12.txt 0.2 > ./Results/Branch_and_Bound/v12_02.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v12.txt 0.5 > ./Results/Branch_and_Bound/v12_05.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v12.txt 0.8 > ./Results/Branch_and_Bound/v12_08.txt

./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v13.txt 0.2 > ./Results/Branch_and_Bound/v13_02.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v13.txt 0.5 > ./Results/Branch_and_Bound/v13_05.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v13.txt 0.8 > ./Results/Branch_and_Bound/v13_08.txt

./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v14.txt 0.2 > ./Results/Branch_and_Bound/v14_02.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v14.txt 0.5 > ./Results/Branch_and_Bound/v14_05.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v14.txt 0.8 > ./Results/Branch_and_Bound/v14_08.txt

./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v15.txt 0.2 > ./Results/Branch_and_Bound/v15_02.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v15.txt 0.5 > ./Results/Branch_and_Bound/v15_05.txt
./Branch_And_Bound/alg_b_and_b ./Instances/Branch_and_Bound/v15.txt 0.8 > ./Results/Branch_and_Bound/v15_08.txt
