#pragma once
#include <algorithm>
#include "Contratos.h"

struct Plantado { int especie; float x; float profundidad; float altura; };

inline std::vector<Plantado> crearDistribucion()
{
    return {
        { 5, -1.3f, 1.0f, 1.05f }, { 1, -0.35f, 0.95f, 1.0f }, { 9, 0.75f, 0.9f, 0.85f },
        { 3, -0.8f, 0.55f, 0.85f }, { 4, 0.0f, 0.5f, 0.9f }, { 6, 1.05f, 0.45f, 0.8f },
        { 0, -1.15f, 0.1f, 0.95f }, { 2, -0.4f, 0.15f, 0.8f }, { 7, 0.35f, 0.05f, 0.85f }, { 8, 1.2f, 0.12f, 0.9f }
    };
}

inline void plantarArbol(const Plantado& pl, unsigned semillaGlobal, Malla& m)
{
    float altura = pl.altura * (1.0f - 0.45f * pl.profundidad);
    float baseY = -0.74f + 0.4f * pl.profundidad;

    Azar az((pl.especie + 1) * 799919u + semillaGlobal);
    int inicio = m.vertices();

    ReglasL reglas = reglasDeEspecie(pl.especie);
    EstiloArbol estilo = estiloDeEspecie(pl.especie);

    std::string cadena = generarCadena(reglas, az);
    Esqueleto esqueleto = interpretar(cadena, estilo, altura, az);
    dibujarRamas(esqueleto, estilo, altura, pl.x, baseY, az, m);
    dibujarHojas(esqueleto, estilo, altura, pl.x, baseY, az, m);
    dibujarArbustos(pl.x, baseY, altura, az, m);

    aplicarBruma(m, inicio, COLOR_BRUMA, pl.profundidad * 0.55f);
}

inline Malla construirBosque(unsigned semilla)
{
    Malla m;
    dibujarFondo(m);

    std::vector<Plantado> plantados = crearDistribucion();
    std::sort(plantados.begin(), plantados.end(),
        [](const Plantado& a, const Plantado& b) { return a.profundidad > b.profundidad; });

    for (const Plantado& pl : plantados)
        plantarArbol(pl, semilla, m);

    return m;
}
