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
## Dependencias

1. **SDL2**: Para gráficos, eventos y sonido.
2. **SDL_ttf**: Para renderizado de texto.

### Instalación en Linux

```bash
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-ttf-dev
