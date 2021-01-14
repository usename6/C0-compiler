.data
.text
move $s0 $gp
jal main
j maintail
functsum:
subu $sp $sp 4
sw $fp 0($sp)
subu $sp $sp 4
move $fp $sp
sw $ra 0($sp)
subu $sp $sp 4
subu $sp $sp 4
subu $sp $sp 4
add $s3 $a0 $a1
add $s4 $zero $s3
move $sp $fp
lw $ra 0($sp)
addi $sp $sp 4
lw $fp 0($sp)
jr $ra
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
add $a0 $zero $t1
add $a1 $zero $t2
jal functsum
move $sp $fp
lw $ra 0($sp)
addi $sp $sp 4
lw $fp 0($sp)
jr $ra
maintail:
