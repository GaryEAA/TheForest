#pragma once
#include <algorithm>
#include "Contratos.h"

struct Plantado { int especie; float x; float profundidad; float altura; };

inline std::vector<Plantado> crearDistribucion()
{
    return { { 0, 0.0f, 0.0f, 0.9f } };
}

inline void plantarArbol(const Plantado& pl, unsigned semillaGlobal, Malla& m)
{
    float baseY = -0.7f;
    Azar az((pl.especie + 1) * 799919u + semillaGlobal);

    ReglasL reglas = reglasDeEspecie(pl.especie);
    EstiloArbol estilo = estiloDeEspecie(pl.especie);

    std::string cadena = generarCadena(reglas, az);
    Esqueleto esqueleto = interpretar(cadena, estilo, pl.altura, az);
    dibujarRamas(esqueleto, estilo, pl.altura, pl.x, baseY, az, m);
    dibujarHojas(esqueleto, estilo, pl.altura, pl.x, baseY, az, m);
    dibujarArbustos(pl.x, baseY, pl.altura, az, m);
}

inline Malla construirBosque(unsigned semilla)
{
    Malla m;
    dibujarFondo(m);
    for (const Plantado& pl : crearDistribucion())
        plantarArbol(pl, semilla, m);
    return m;
}
