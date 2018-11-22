#!/bin/bash

g++ -std=c++11 ./Grasp+VNS/main.cpp -o ./Grasp+VNS/grasp

# GRASP + VNS with VND
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v08.txt 0.2 > ./Results/Grasp+VNS/v08_02.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v08.txt 0.5 > ./Results/Grasp+VNS/v08_05.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v08.txt 0.8 > ./Results/Grasp+VNS/v08_08.txt

./Grasp+VNS/grasp ./Instances/Grasp+VNS/v09.txt 0.2 > ./Results/Grasp+VNS/v09_02.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v09.txt 0.5 > ./Results/Grasp+VNS/v09_05.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v09.txt 0.8 > ./Results/Grasp+VNS/v09_08.txt

./Grasp+VNS/grasp ./Instances/Grasp+VNS/v10.txt 0.2 > ./Results/Grasp+VNS/v10_02.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v10.txt 0.5 > ./Results/Grasp+VNS/v10_05.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v10.txt 0.8 > ./Results/Grasp+VNS/v10_08.txt

./Grasp+VNS/grasp ./Instances/Grasp+VNS/v11.txt 0.2 > ./Results/Grasp+VNS/v11_02.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v11.txt 0.5 > ./Results/Grasp+VNS/v11_05.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v11.txt 0.8 > ./Results/Grasp+VNS/v11_08.txt

./Grasp+VNS/grasp ./Instances/Grasp+VNS/v12.txt 0.2 > ./Results/Grasp+VNS/v12_02.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v12.txt 0.5 > ./Results/Grasp+VNS/v12_05.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v12.txt 0.8 > ./Results/Grasp+VNS/v12_08.txt

./Grasp+VNS/grasp ./Instances/Grasp+VNS/v13.txt 0.2 > ./Results/Grasp+VNS/v13_02.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v13.txt 0.5 > ./Results/Grasp+VNS/v13_05.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v13.txt 0.8 > ./Results/Grasp+VNS/v13_08.txt

./Grasp+VNS/grasp ./Instances/Grasp+VNS/v14.txt 0.2 > ./Results/Grasp+VNS/v14_02.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v14.txt 0.5 > ./Results/Grasp+VNS/v14_05.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v14.txt 0.8 > ./Results/Grasp+VNS/v14_08.txt

./Grasp+VNS/grasp ./Instances/Grasp+VNS/v15.txt 0.2 > ./Results/Grasp+VNS/v15_02.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v15.txt 0.5 > ./Results/Grasp+VNS/v15_05.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v15.txt 0.8 > ./Results/Grasp+VNS/v15_08.txt

# Testes do Artigo
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v20.txt 0.75 > ./Results/Grasp+VNS/v20_075.txt

./Grasp+VNS/grasp ./Instances/Grasp+VNS/v30a.txt 0.75 > ./Results/Grasp+VNS/v30a_075.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v30b.txt 0.75 > ./Results/Grasp+VNS/v30b_075.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v30c.txt 0.75 > ./Results/Grasp+VNS/v30c_075.txt

./Grasp+VNS/grasp ./Instances/Grasp+VNS/v50a.txt 0.75 > ./Results/Grasp+VNS/v50a_075.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v50b.txt 0.75 > ./Results/Grasp+VNS/v50b_075.txt

./Grasp+VNS/grasp ./Instances/Grasp+VNS/v100a.txt 0.75 > ./Results/Grasp+VNS/v100a_075.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v100b.txt 0.75 > ./Results/Grasp+VNS/v100b_075.txt

./Grasp+VNS/grasp ./Instances/Grasp+VNS/v250a.txt 0.75 > ./Results/Grasp+VNS/v250a_075.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v250b.txt 0.75 > ./Results/Grasp+VNS/v250b_075.txt

./Grasp+VNS/grasp ./Instances/Grasp+VNS/v500a.txt 0.75 > ./Results/Grasp+VNS/v500a_075.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v500b.txt 0.75 > ./Results/Grasp+VNS/v500b_075.txt

./Grasp+VNS/grasp ./Instances/Grasp+VNS/v1000a.txt 0.75 > ./Results/Grasp+VNS/v1000a_075.txt
./Grasp+VNS/grasp ./Instances/Grasp+VNS/v1000b.txt 0.75 > ./Results/Grasp+VNS/v1000b_075.txt