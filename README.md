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

### Pareja 1: Motor L-System (solo texto)
* **Integrante A:** _nombre_ 
  * *Archivo asignado:* ``Motor_Cadenas.h``
* **Integrante B:** _nombre_ 
  * *Archivo asignado:* ``Motor_Reglas.h``

### Pareja 2: Geometría y follaje
* **Integrante A:** ``Gary Añanga``
  * *Archivo asignado:* ``Geometria_Tortuga.h``
* **Integrante B:** ``Jadhe Sotelo``
  * *Archivo asignado:* ``Follaje.h``

### Pareja 3: Escena y renderizado
* **Integrante A:** _nombre_ 
  * *Archivo asignado:* ``Escena_Bosque.h``
* **Integrante B:** _nombre_ 
  * *Archivos asignados:* ``Escena_Fondo.h`` y ``main.cpp``

## Regla de oro

Cada pareja trabaja en su rama y solo toca sus propios archivos. Los archivos `Comun.h`, `Contratos.h` y `Shader.*` no se modifican sin avisar a todos.
