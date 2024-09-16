# Juego Clásico - SDL

Este es un juego clásico creado en el lenguaje C utilizando las librerías **SDL** (Simple DirectMedia Layer) y **SDL_ttf**. El objetivo del juego es controlar un cuadro y destruyendo objetos que puede saltar, disparar, evitar obstáculos y recolectar ítems. También hay un jefe final que el jugador debe derrotar.

## Controles

- **Barra Espaciadora**: Saltar.
- **Clic Izquierdo del Ratón**: Disparar.
- **Enter**: Iniciar el juego desde el menú principal.
- **ESC**: Salir del juego.

## Estructura del Código

El código está estructurado de la siguiente manera:

Objetos del juego: El paddle, los obstáculos, recolectables, disparos, y el jefe son representados mediante estructuras (struct) que contienen su posición, tamaño, y velocidad.
Colisiones: Se detectan colisiones entre el paddle, los disparos, obstáculos, el jefe, y recolectables para determinar las interacciones.
Menú de Inicio: El juego comienza con un menú donde el jugador debe presionar "Enter" para empezar.
Ciclo de Juego: El juego corre en un ciclo de actualización y renderizado hasta que el jugador cierre el juego o pierda por colisiones.

## Recursos
El juego usa una fuente externa almacenada en la ruta C:/Users/USUARIO/OneDrive/Escritorio/sc-2420-eval-u1-Cristian171/GameClasic/GameCs/font.ttf. Asegúrate de incluir tu propia fuente o cambiar la ruta en el código.

2. Variables Globales
Se crean varias instancias de struct game_object para representar los objetos principales del juego:

paddle: Representa el paddle que el jugador controla, incluyendo su posición, velocidad y tamaño.
structures[MAX_STRUCTURES]: Un arreglo de obstáculos en el juego. Los obstáculos se mueven de derecha a izquierda y el jugador debe evitarlos.
shots[MAX_SHOTS]: Representa los disparos que el paddle puede lanzar cuando el jugador hace clic izquierdo.
collectibles[MAX_COLLECTIBLES]: Recolectables que caen del cielo y que el paddle puede recoger para aumentar el puntaje.
boss: Un objeto especial que representa el jefe final del juego, con su propia vida y velocidad.
3. Funciones Principales
void render_start_menu(void): Renderiza el menú de inicio que se muestra cuando el juego comienza. En este menú, el jugador debe presionar Enter para iniciar el juego.

void process_input(void): Procesa los eventos de entrada del usuario, como los movimientos del paddle, los saltos y los disparos. También maneja eventos como cerrar el juego al presionar ESC.

void setup(void): Inicializa los objetos del juego, incluyendo el paddle, los obstáculos, los recolectables y el jefe.

bool check_collision(struct game_object* a, struct game_object* b): Revisa si dos objetos del juego colisionan entre sí. Es fundamental para detectar cuando el paddle choca con un obstáculo o recoge un recolectable.

void update(void): Actualiza el estado del juego, incluyendo las posiciones de los objetos en función del tiempo y la lógica de colisión. También maneja la lógica del jefe y las interacciones con los disparos.

void render(void): Se encarga de renderizar (dibujar) todos los objetos del juego en pantalla: el paddle, los obstáculos, los disparos, los recolectables, el jefe, y el puntaje.

4. Variables Importantes
boss_health: Controla la vida del jefe. Cuando se reduce a 0, el jefe es derrotado y el juego lo refleja en el puntaje.
is_jumping: Indica si el paddle está en el aire (saltando). Sirve para restringir el salto del paddle hasta que vuelva a tocar el suelo.
shot_count: Lleva la cuenta del número de disparos activos en el juego. Controla cuántos disparos se pueden lanzar al mismo tiempo.
score: Guarda el puntaje actual del jugador, que aumenta al recoger objetos o derrotar al jefe.
5. Lógica del Juego
Saltos y gravedad: La variable gravity aplica una fuerza constante hacia abajo al paddle, mientras que jump_force controla cuánta fuerza se aplica para que el paddle salte.
Colisiones: La función check_collision() se usa para detectar interacciones entre objetos, como entre el paddle y los recolectables, o los disparos y el jefe.
Sistema de disparos: El jugador puede disparar con el clic izquierdo. La dirección del disparo se calcula en función de la posición del mouse.

## Dependencias

1. **SDL2**: Para gráficos, eventos y sonido.
2. **SDL_ttf**: Para renderizado de texto.
