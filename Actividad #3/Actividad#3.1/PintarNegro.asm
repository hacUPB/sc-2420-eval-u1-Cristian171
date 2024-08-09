// Bucle infinito para leer las tecla y cambiar el color de la pantalla 
(LOOP_KBD)
        // Esperar a que se presione una tecla
        @KBD
        D=M   

        // Si se presiona la tecla A (valor 65), establecer la pantalla en negro
        @65
        D=D-A       
        @BLACK_SCREEN
        D;JEQ    

        @LOOP_KBD
        0;JMP


(BLACK_SCREEN)
        // Establecer el número de registros a pintar
        @160
        D=A 
        @counter
        M=D 

 (LOOP_SCR1)
        @counter
        D=M 
        @SCREEN
        A=A+D         

        M=-1            

        @counter     
        M=M+1

        D=M             
        @8032             
        D=A-D 

        @LOOP_SCR1     
        D;JGT

        // Volver al bucle de espera de teclas
        @LOOP_KBD
        0;JMP

        // Establecer el número de registros a pintar
        @160
        D=A 
        @counter
        M=D 

 (LOOP_SCR2)
        @counter
        D=M 
        @SCREEN
        A=A+D         

        M=0       

        @counter     
        M=M+1

        D=M             
        @8032            
        D=A-D 

        @LOOP_SCR2         
        D;JGT

        @LOOP_KBD
        0;JMP