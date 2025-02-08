# Conway's Game of Life

Este proyecto es una implementación del **Juego de la Vida de Conway** en C utilizando la biblioteca **SDL2** para la representación gráfica.

## Descripción

El Juego de la Vida es un autómata celular ideado por John Conway. Consiste en una cuadrícula de celdas que pueden estar vivas o muertas. La evolución de las celdas se determina según reglas simples basadas en el número de vecinos vivos.

## Características

- Interfaz gráfica con SDL2.
- Inicialización aleatoria de celdas.
- Capacidad para pausar/reanudar la simulación.
- Edición manual del estado de las celdas con el ratón.

## Dependencias

- **SDL2**: Para instalar SDL2 en Debian:

```bash
sudo apt-get install libsdl2-dev
```

## Compilación

Usa `gcc` para compilar el programa:

```bash
gcc -o gol main.c -lSDL2
```

## Ejecución

```bash
./gol [cell_width]
```

- `cell_width` (opcional): Tamaño de las celdas (entre 5 y 100). Si no se especifica, el valor por defecto es 20.

### Ejemplos

```bash
./gol 10   # Celdas pequeñas
./gol 50   # Celdas más grandes
```

## Opciones de Línea de Comandos

- `--help`: Muestra el menú de ayuda.
- `--keys`: Muestra las teclas de control disponibles.

## Controles

- **Espacio**: Pausar/reanudar la simulación.
- **Enter**: Generar una configuración aleatoria.
- **Backspace**: Borrar todas las celdas.
- **Clic del ratón**: Cambiar el estado de una celda individual.

## Reglas del Juego

1. **Subpoblación:** Una celda viva con menos de dos vecinos vivos muere.
2. **Supervivencia:** Una celda viva con dos o tres vecinos vivos sobrevive.
3. **Sobrepoblación:** Una celda viva con más de tres vecinos vivos muere.
4. **Reproducción:** Una celda muerta con exactamente tres vecinos vivos se convierte en una celda viva.


