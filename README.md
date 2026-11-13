# Proyecto TheForest

Bosque dibujado con OpenGL donde cada árbol nace de una "receta" de letras (L-System). Hay 10 árboles distintos, con hojas, arbustos en la base que se mueven con el viento y un paisaje de fondo.

## Teclas

| Tecla | Acción |
|---|---|
| W A S D | Mover la vista |
| Q / E | Alejar / acercar |
| R | Crear un bosque nuevo |
| Esc | Salir |

## Quién hace qué

| Pareja | Parte | Integrante A | Integrante B |
|---|---|---|---|
| 1 | Motor L-System (solo texto) | `Motor_Cadenas.h` – _nombre_ | `Motor_Reglas.h` – _nombre_ |
| 2 | Geometría y follaje | `Geometria_Tortuga.h` – _nombre_ | `Follaje.h` – _nombre_ |
| 3 | Escena y renderizado | `Escena_Bosque.h` – _nombre_ | `Escena_Fondo.h` y `main.cpp` – _nombre_ |

## Regla de oro

Cada pareja trabaja en su rama y solo toca sus propios archivos. Los archivos `Comun.h`, `Contratos.h` y `Shader.*` no se modifican sin avisar a todos.
