#!/bin/bash

count=0

# Esempio di until loop
until [[ $count -gt 5 ]]; do
	echo Il valore della variabile count è: $count
	let count++
	sleep 0.5
done
