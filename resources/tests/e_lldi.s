.name "see file name"
.comment "..."

ldi r1,%65,r2
ldi r1,%22,r3
sub r2,r3,r1
aff r1

ld %75, r2
ld %22, r3
sub r2,r3,r1
aff r1
