.data
.text
move $t8 $gp
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
addi $t2 $zero 2
add $t3 $t1 $t2
add $t1 $t3 $zero
move $sp $fp
lw $ra 0($sp)
addu $sp $sp $4
lw $fp 0($sp)
jr $ra
maintail:
