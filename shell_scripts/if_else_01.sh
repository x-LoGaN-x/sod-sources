#!/bin/bash

path="./dir1"

# Check se la directory esiste
if [ -d $path ]; then
	echo "La directory $path esistente"
else
	echo "La directory $path non esiste"
fi
