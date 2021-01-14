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
subu $sp $sp 4
subu $sp $sp 4
addi $t1 $zero 1
addi $t2 $zero 2
addi $t3 $zero 3
addi $t4 $zero 4
sw $t1 0($s0)
add $t1 $t2 $t3
lw $t2 0($s0)
add $t2 $t1 $zero
add $t1 $t4 $t2
add $t4 $t1 $zero
move $sp $fp
lw $ra 0($sp)
addu $sp $sp $4
lw $fp 0($sp)
jr $ra
maintail:
