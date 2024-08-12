- Objetivo:
En el primer trabajo se intento hacer que tocando la tecla A,b,T si se preciona A se empieza a pintar en negro si se preciona B para el porcedimiento de Color negro y se queda en 0
que es = a blanco y si se preciona T empieza a pintar en negro virticalmente.


- Procedimiento:
Se implemento de la siguente manera empezamos en el contador de pantalla que es "@16384" empezamos con un bucle que si sumo el contador al valor del puntero de la pantalla
M=-1  Escribo -1 que es negro esto lo repito en un bucle hasta pintar la selecion que yo necesito cumplir si el numero es 0 la pantalla se queda en blanco 



- Concluciones:
hasta ahora la implementacion genera un bucle que hace que se pinte uno a uno hasta llegar a la primera parte del bucle pero despues de que se pinta la primera parte.
El bucle hace que se pinte todo de negro 
Buscando posibles soluciones...
este es el bucle principal.
15	0;JMP
16	@160
17	D=A
18	@16
19	M=D
20	@16
21	D=M
22	@16384
23	A=D+A
24	M=-1
25	@16
26	M=M+1
27	D=M
para solucionarlo tengo que agregar que este bucle lea el teclado y al momento donde le de otro orden de memoria de teclado pare lo que esta haciendo y continue con la nueva orden
