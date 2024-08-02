@0
D=M         
@3
M=D         

@2
M=0          

(LOOP)
@3
D=M          
@1
D=D-M        
@END
D;JGT       

@3
D=M          
@2
D=D+M        
@2
M=D          

@3
M=M+1        
@LOOP
0;JMP        

(END)
@HALT
0;JMP        

//
este archivo suma 1 numero en la ram 2 y 3. inicia en 0 y en la ranura 2 le suma 1 y luego 