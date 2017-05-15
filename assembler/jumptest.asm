;file: jumptest.asm
;description: exercises several variations of jumps
;Should not have any data hazards

home: ;first in pipeline
    JMP @episodei
disney:
    PAL HALT

episodeii: ; let's forget about this one
    JMP @episodeiii

episodei: ;fill up the pipeline with annoying characters
    ADDL    $zero   10      $1
    ADDL    $zero   20      $1
    ADDL    $zero   30      $1
    ADDL    $zero   40      $1
    ADDL    $zero   50      $1
    JMP     @episodeii

episodev: 
    JSR     @episodevi
episodevr:
    ADDL    $9      0       $8
    JSRC    @episodevir
episodeiii: ; execute order 66
    SUBL    $1      $1      $1
    SUBL    $2      $2      $2
    SUBL    $3      $3      $3
    SUBL    $4      $4      $4
    SUBL    $5      $5      $5
    JMP     @episodeiv ;tests that JUMP to next value doesn't break

episodeiv: ;I ran out of inspiration
    ADDL    $30     5       $30
    ADDL    $29     10      $29
    ADDL    $28     15      $28
    ADDL    $27     20      $27
    ADDL    $26     25      $25
    RET     @episodev

episodevi: ;
    ADDL    $zero   0       $15
    ADDL    $zero   0       $14
episodevir:
    ADDL    $zero   0       $13
    ADDL    $zero   0       $12
    JMP     @disney
