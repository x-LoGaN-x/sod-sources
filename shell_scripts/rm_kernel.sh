#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "Lo script richiede la versione del kernel da eliminare."
	echo "Es. 6.3.2-defconf"
	exit 1
fi

kernVer=$1
kernPath="/boot"
kernFiles="config initrd.img System.map vmlinuz"
modulesPath="/lib/modules"

echo "Rimozione della versione $kernVer in corso..."

for suf in $kernFiles; do
	file="$kernPath/$suf-$kernVer"
	if [[ -e $file ]]; then
		echo "Rimozione del file $file"
		rm -f $file
	else
		echo "Il file $file non esiste"
	fi
	
	if [[ $? -ne 0 ]]; then
		echo "Errore nella rimozione dei file relativi al kernel!"
		exit 1
	fi
done

echo "Rimozione dei moduli relativi al kernel $kernVer in corso..."

dir="$modulesPath/$kernVer"

if [[ -d $dir ]]; then
	echo "Rimozione dei moduli $dir"
	rm -rf $dir
else
	echo "La directori dei moduli $dir non esiste"
fi

if [[ $? -ne 0 ]]; then
	echo "Errore nella rimozione dei file relativi al kernel!"
	exit 1
fi

echo "Aggiornamento del menu di avvio GRUB..."
sudo update-grub

#config-6.3.2-original-config
#initrd.img-6.3.2-original-config
#System.map-6.3.2-original-config
#vmlinuz-6.3.2-original-config


