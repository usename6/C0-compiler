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
addi $t1 $zero 12
addi $t2 $zero 2
li $t0 2
divu $t3 $t1 2
mflo $t3
add $t1 $t3 $zero
li $t0 12
li $s1 3
div $t0 $s1
mflo $t4
add $t1 $t4 $zero
div $t1 $t2
mflo $t3
add $t1 $t3 $zero
move $sp $fp
lw $ra 0($sp)
addu $sp $sp $4
lw $fp 0($sp)
jr $ra
maintail:
