#pragma once
#include "Contratos.h"

inline EstiloArbol estiloDeEspecie(int especie)
{
    return { 28.0f, 10.0f, 0.25f, 0.035f, 0.045f, 0.6f,
        { 0.35f, 0.24f, 0.14f }, { 0.12f, 0.50f, 0.15f }, { 0.35f, 0.70f, 0.22f }, TipoHoja::Redonda };
}

inline Esqueleto interpretar(const std::string& cadena, const EstiloArbol& estilo, float altura, Azar& az)
{
    Esqueleto e;
    e.ramas.push_back({ 0.0f, 0.0f, 0.0f, altura, 0 });
    e.puntas.push_back({ 0.0f, altura, 90.0f, 0 });
    return e;
}

inline void dibujarRamas(const Esqueleto& esq, const EstiloArbol& estilo, float altura, float baseX, float baseY, Azar& az, Malla& m)
{
    for (const Segmento& s : esq.ramas)
    {
        float a = 0.015f;
        cuadrilatero(m, baseX + s.x1 - a, baseY + s.y1, baseX + s.x1 + a, baseY + s.y1,
            baseX + s.x2 + a, baseY + s.y2, baseX + s.x2 - a, baseY + s.y2, estilo.tronco);
    }
}
