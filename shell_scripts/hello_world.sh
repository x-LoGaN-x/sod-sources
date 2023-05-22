#!/bin/bash
# Queste sono variabili globali
sender="pluto"
receiver="paperino"

function pippo {
# Mediante la dicitura local definiamo che una variabile
# è locale alla funzione dove è definita.
local sender="pippo"
local receiver="topolino"

echo "Il mittente è $sender"
echo "Il destinario è $receiver"
echo ""
}

pippo
msg="Hello World!"

echo $(ps)

ps

echo $msg
echo "Da $sender a $receiver"
