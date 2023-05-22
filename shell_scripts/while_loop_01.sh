#!/bin/bash

count=6

# Esempio di while loop
while [[ $count -gt 0 ]]; do
	echo Il valore della variabile count è: $count
	let count--
	sleep 0.5
done
