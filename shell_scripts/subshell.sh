#!/bin/bash
# Utilizziamo la subshell per riportare la versione attuale del
# kernel
echo "La versione del kernel attualmente in uso è:"
echo $(uname -r)

# Se invece utilizzassimo il comando echo senza la subshell
echo "La versione del kernel attualmente in uso è:"
echo uname -r
