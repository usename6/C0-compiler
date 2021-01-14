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
addi $t1 $zero 1
CYCLE0:
addi $t6 $zero 2
beq $t1 $t6 LABEL0
addi $t2 $t1 1
add $t1 $t2 $zero
j CYCLE0
LABEL0:
move $sp $fp
lw $ra 0($sp)
addi $sp $sp 4
lw $fp 0($sp)
jr $ra
maintail:
