#!/bin/bash
# Queste sono variabili globali
sender="Sheldon"
receiver="Leonard"

function subFun {
# Mediante la parola chiave local definiamo che una
# variabile è locale alla funzione dove è definita.
local sender
sender="Raj"
local receiver="Howard"

echo "Il mittente è $sender"
echo "Il destinario è $receiver"
echo ""
}

# Richiamo la funzione
subFun

msg="Hello World!"

echo $msg
echo "Da $sender a $receiver"
