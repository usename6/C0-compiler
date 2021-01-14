.data
.text
move $s0 $gp
jal main
j maintail
functsolve:
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
add $v0 $zero $s4
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
jal functsolve
add $t1 $zero $v0
move $sp $fp
lw $ra 0($sp)
addi $sp $sp 4
lw $fp 0($sp)
jr $ra
maintail:
