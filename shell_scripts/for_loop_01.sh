#!/bin/bash

list=$(ls /etc/*.conf)

echo "I file di configurazione presenti nella directory etc sono:"

# For loop che scorre tutti gli elementi nella variabile list
for file in $list; do
	echo ${file#"/etc/"}
done
