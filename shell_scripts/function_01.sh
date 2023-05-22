#!/bin/bash

# Definizione delle funzioni.
# Possono essere dichiarate in qualsiasi ordine
function function_B {
        echo Function B.
}
function function_A {
        echo $1
}
function function_D {
        echo Function D.
}
function function_C {
        echo $1 $2
}
function function_E {
        echo $1
}

# Chamata alle funzioni

# La funzione A utilizza un parametro in ingresso
function_A "Function A."

# Funzione senza parametri
function_B

# La funzione C utilizza due parametri in ingresso
function_C "Function" "C."

# Se la funzione non utilizza nessun parametro, non restituisce un errore
# semplicemente il parametro non verrà utilizzato
function_D "Parametro non utilizzato"

# Se la funzione richiede un parametro, ma questo non viene passato
# la chiamata non da errore, semplicemente la funzione non si comporta
# come ci aspetteremmo
function_E
