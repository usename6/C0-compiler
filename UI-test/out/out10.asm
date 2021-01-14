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
addi $v0 $zero 5
syscall
add $t1 $zero $v0
addi $v0 $zero 5
syscall
add $t2 $zero $v0
addi $v0 $zero 1
add $a0 $zero $t1
syscall
addi $v0 $zero 1
add $a0 $zero $t2
syscall
move $sp $fp
lw $ra 0($sp)
addu $sp $sp $4
lw $fp 0($sp)
jr $ra
maintail:
