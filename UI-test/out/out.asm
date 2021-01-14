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
addi $t/ $zero 1
CASEIN1:
addi $t5 $zero 1
bne $t1 $t5 CASEOUT1
addi $t/ $t2 1
add $t2 $t3 $zero
CASEOUT1:
CASEIN2:
addi $t5 $zero 2
bne $t1 $t5 CASEOUT2
addi $t/ $t1 1
add $t1 $t4 $zero
CASEOUT2:
DEFAULTIN:
addi $t/ $t1 2
sw $t2 0($s0)
add $t1 $t2 $zero
DEFAULTOUT:
move $sp $fp
lw $ra 0($sp)
addu $sp $sp $4
lw $fp 0($sp)
jr $ra
maintail:
