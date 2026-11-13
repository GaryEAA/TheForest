#pragma once
#include "Contratos.h"

inline void dibujarHojas(const Esqueleto& esq, const EstiloArbol& estilo, float altura, float baseX, float baseY, Azar& az, Malla& m)
{
    for (const PuntaHoja& h : esq.puntas)
        circulo(m, baseX + h.x, baseY + h.y, 0.1f, 0.1f, estilo.hojaA, 12);
}

inline void dibujarArbustos(float x, float y, float alturaArbol, Azar& az, Malla& m)
{
    circulo(m, x + 0.12f, y + 0.04f, 0.06f, 0.06f, { 0.2f, 0.55f, 0.2f }, 12, y, 0.1f);
}
