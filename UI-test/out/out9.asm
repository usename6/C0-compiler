.data
.text
move $s0 $gp
jal main
j maintail
main:
subu $sp $sp 4
sw $fp 0($sp)
subu $sp $sp 4
move $fp $sp
sw $ra 0($sp)
subu $sp $sp 4
subu $sp $sp 4
addi $t1 $zero 1
CASEIN1:
addi $t5 $zero 1
bne $t1 $t5 CASEOUT1
addi $t3 $t2 1
add $t2 $t3 $zero
j DEFAULTIN
CASEOUT1:
CASEIN2:
addi $t5 $zero 2
bne $t1 $t5 CASEOUT2
addi $t4 $t1 1
add $t1 $t4 $zero
j DEFAULTIN
CASEOUT2:
DEFAULTIN:
addi $t2 $t1 2
add $t1 $t2 $zero
DEFAULTOUT:
move $sp $fp
lw $ra 0($sp)
addu $sp $sp $4
lw $fp 0($sp)
jr $ra
maintail:
