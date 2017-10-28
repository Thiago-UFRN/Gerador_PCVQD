#!/bin/bash

typeset -i ID;
let ID=1;

for i in 0 1; do # tipo da instancia
    let ID=1
    for j in 3 5; do # capacidade do carro
        for k in 1000; do # tamanho da instancia
            for l in {1..3}; do # numero de instancias
                if [ $i == 0 ]
        		then
        			./main $k 250 100 $j 2 0 $i > instancia/assimetrica/$k.$ID.in;
                else
        			./main $k 250 100 $j 2 0 $i > instancia/simetrica/$k.$ID.in;
        		fi;
        		let ID++;
            done
        done
    done
done
