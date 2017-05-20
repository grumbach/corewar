.name "see file name"
.comment "..."

l1:st r1, r2
live: live %2
	st r1, -50
	lldi r5, %-50, r3
	lfork %-50
	zjmp %:l1
