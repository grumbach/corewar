#!/bin/sh

cp ../../corewar .
echo start:
read s
echo number iterations:
read n
echo player name:
read p
for ((i=$s;i<=$n;i++))
do
	./corewar -dump $i warriors/$p.cor > me
	./corewar_zaz -d $i warriors/$p.cor > zaz
	if ! cmp me zaz
	then
		echo dumpfail $i
	else
		echo dump success $i
	fi
done
#rm me
#rm zaz
# rm corewar
