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
addi $t6 $zero 1
bne $t1 $t6 LABEL1
addi $t3 $zero 2
LABEL1:
move $sp $fp
lw $ra 0($sp)
addu $sp $sp $4
lw $fp 0($sp)
jr $ra
maintail:
