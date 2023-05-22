#!/bin/bash

count=10

echo "I file di configurazione presenti nella directory etc sono:"

# For loop che esegue un numero di iterazioni pari a count
for (( i=0;i<$count;i++ )); do
    echo "Iterazione #$i"
    sleep 0.2
done
