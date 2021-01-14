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
addi $t1 $zero 5
addi $t2 $zero 1
sub $t3 $t1 $t2
add $t1 $t3 $zero
addi $t4 $t1 -2
add $t1 $t4 $zero
li $t0 3
addi $t2 $t0 -2
add $t1 $t2 $zero
move $sp $fp
lw $ra 0($sp)
addu $sp $sp $4
lw $fp 0($sp)
jr $ra
maintail:
