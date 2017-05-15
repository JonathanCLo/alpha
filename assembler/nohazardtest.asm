home:
    PAL NOOP
    STL     $zero   $zero   600
    ADDL    $1      12      $2
    S4ADDL  $3      34      $4
    S8ADDL  $5      56      $6
    SUBL    $7      78      $8
    S4SUBL  $9      90      $10
    S8SUBL  $11     12      $12
    AND     $zero   3       $13
    BIC     $zero   3       $14
    BIS     $zero   3       $15
    EQV     $zero   3       $16
    ORNOT   $zero   3       $17
    XOR     $zero   3       $18
    CMOVEQ  $zero   3       $19
    CMOVGE  $zero   3       $20
    CMOVGT  $zero   3       $21
    CMOVLBC $zero   3       $22
    CMOVLBS $zero   3       $23
    CMOVLE  $zero   3       $24
    CMOVLT  $zero   3       $25
    CMOVNE  $zero   3       $26
    LDA     $1      $zero   600
    PAL NOOP
    NOOP
    PAL HALT
