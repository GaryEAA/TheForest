#pragma once
#include "Contratos.h"

inline void dibujarFondo(Malla& m)
{
    float ancho = 3.5f;
    cuadrilatero(m, -ancho, 1.0f, ancho, 1.0f, ancho, HORIZONTE, -ancho, HORIZONTE, { 0.4f, 0.7f, 0.95f });
    cuadrilatero(m, -ancho, HORIZONTE, ancho, HORIZONTE, ancho, -1.0f, -ancho, -1.0f, { 0.3f, 0.6f, 0.25f });
}
