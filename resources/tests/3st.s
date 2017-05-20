.name "see file name"
.comment "..."

l1:st r1, r2
live: live %2
	st r1, -500
	live %3
	add r12,r13,r14
	zjmp %:l1
