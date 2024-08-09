// Definición de símbolos para la letra T
// T_WIDTH = 16
// T_HEIGHT = 16
// T_TOP_ROW = 0    // El valor de la fila superior de la T
// T_LEFT_COLUMN = 0 // El valor de la columna izquierda de la T

// Inicio del programa

// Bucle infinito para leer las teclas y cambiar el color de la pantalla según corresponda
(LOOP_KBD)
        // Esperar a que se presione una tecla
        @KBD
        D=M         // Cargar el valor de la dirección de memoria KBD (teclado) en D

        // Si se presiona la tecla A (valor 65), establecer la pantalla en negro
        @65
        D=D-A       // Comparar el valor de la tecla con el valor de A_KEY
        @BLACK_SCREEN
        D;JEQ       // Saltar a BLACK_SCREEN si son iguales (la tecla A fue presionada)

        // Si no, comprobar si se presionó la tecla B (valor 66), establecer la pantalla en blanco
        @66
        D=D-A       // Comparar el valor de la tecla con el valor de B_KEY
        @WHITE_SCREEN
        D;JEQ       // Saltar a WHITE_SCREEN si son iguales (la tecla B fue presionada)

        // Si no se presionó ni A ni B, comprobar si se presionó la tecla T (valor 84)
        @84
        D=D-A       // Comparar el valor de la tecla con el valor de T_KEY
        @DRAW_T
        D;JEQ       // Saltar a DRAW_T si la tecla T fue presionada

        // Si no se presionó ninguna tecla relevante, volver al bucle de espera de teclas
        @LOOP_KBD
        0;JMP

// Etiqueta para cambiar la pantalla a negro (BLACK_SCREEN)
(BLACK_SCREEN)
        // Establecer el número de registros a pintar
        @160
        D=A 
        @counter
        M=D 

 (LOOP_SCR_BLACK)
        @counter
        D=M 
        @SCREEN
        A=A+D           //sumo el contador al valor del puntero de la pantalla

        M=-1            //Escribo -1 que es negro

        @counter     //Incremento contador de ancho
        M=M+1

        D=M             
        @8032             //Comparo el contador  8192 - counter
        D=A-D 

        @LOOP_SCR_BLACK         //Si es menor que cero repito el bucle
        D;JGT

        // Volver al bucle de espera de teclas
        @LOOP_KBD
        0;JMP

// Etiqueta para cambiar la pantalla a blanco (WHITE_SCREEN)
(WHITE_SCREEN)
        // Establecer el número de registros a pintar
        @160
        D=A 
        @counter
        M=D 

 (LOOP_SCR_WHITE)
        @counter
        D=M 
        @SCREEN
        A=A+D           //sumo el contador al valor del puntero de la pantalla

        M=0            //Escribo 0 que es blanco

        @counter     //Incremento contador de registros
        M=M+1

        D=M             
        @8032             //Comparo el contador  8192 - counter
        D=A-D 

        @LOOP_SCR_WHITE         //Si es menor que cero repito el bucle
        D;JGT

        // Volver al bucle de espera de teclas
        @LOOP_KBD
        0;JMP

// Etiqueta para dibujar la letra T (DRAW_T)
(DRAW_T)
        // Definir las dimensiones de la T
        @16
        D=A
        @T_WIDTH
        M=D

        @16
        D=A
        @T_HEIGHT
        M=D

        // Establecer la posición inicial para la T
        @0
        D=A
        @T_TOP_ROW
        M=D

        @0
        D=A
        @T_LEFT_COLUMN
        M=D

        // Bucle para dibujar la T
        @T_TOP_ROW
        D=M
        @T_HEIGHT
        D=D+M           // Altura total de la T

        @T_WIDTH
        D=D-M           // Ancho total de la T

        @T_LEFT_COLUMN
        D=D+M           // Ancho de la T

        @DRAW_T_LOOP
        D;JGT

(DRAW_T_LOOP)
        @T_TOP_ROW
        D=M
        @SCREEN
        A=A+D           // Establece el puntero de la pantalla

        @T_WIDTH
        D=M
        @SCREEN
        A=A+D           // Ajusta el puntero

        M=0            // Escribe 0 (blanco) para la T

        @T_TOP_ROW
        M=M+1           // Incrementa fila superior de la T

        @T_HEIGHT
        D=M
        @DRAW_T_LOOP
        D;JGT

        // Volver al bucle de espera de teclas
        @LOOP_KBD
        0;JMP
