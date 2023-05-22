#!/bin/bash

# Definizione di un array di 4 elementi
array=('Sheldon Cooper' 'Leonard Hofstadter' 'Rajesh Koothrappali' 'Howard Wolowitz')

# Lettura del numero di elementi nell'array
elements=${#array[@]}

# Scansione degli elmenti dell'array mediante
# ciclo for
for (( i=0;i<$elements;i++ )); do
    echo $i. ${array[${i}]}
done
