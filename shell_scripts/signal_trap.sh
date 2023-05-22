#!/bin/bash

# Definizione della trap per il segnale INT
trap intTrap INT

# Definizione della trap per il segnale ALRM
trap alrmTrap ALRM

# Definizione delle subrutine.
# Funzione eseguita al ricevimento del segnale INT
function intTrap()
{
    echo "CTRL+C (INT) ricevuto! Esecuzione della trap!"
}

# Funzione eseguita al ricevimento del segnale ALRM
function alrmTrap()
{
    echo "Segnale ALARM ricevuto! Esecuzione della trap!"
}

# Pulizia dello schermo
clear;

# Loop da 1/10 a 20/20
for iter in `seq 1 20`; do
    echo "$iter/20 to Exit."
    sleep 1;
done

echo "Uscita dell'esempio di gestione dei segnali!"
