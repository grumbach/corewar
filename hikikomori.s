.name "hikikomori"
.comment "months spent watching anime : it's over 9000!!"

home:		sti		r1, %:watchanime, %1
			sti		r1, %:akihabara, %1
			sti		r1, %:anime, %1
			and		r16, %0, r16
			fork	%:akihabara

watchanime:	live 	%42
			zjmp 	%:watchanime

akihabara:	live 	%42
			fork	%:anime
			zjmp	%:akihabara

anime:		live	%42
			ld		%57672451, r2
			ld		%57672451, r3
			ld		%57672451, r4
			ld		%57672451, r5
			ld		%57672451, r6
			st		r6, 100
			st		r5, 109
			st		r4, 118
			st		r3, 127
			st		r2, 136
