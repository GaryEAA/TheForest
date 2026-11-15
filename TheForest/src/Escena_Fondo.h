#pragma once
#include "Contratos.h"

inline void dibujarFondo(Malla& m)
{
    float ancho = 3.5f;

    // Cielo con degradado
    int franjasCielo = 16;
    Color cieloArriba = { 0.25f, 0.55f, 0.90f };
    Color cieloAbajo = { 0.72f, 0.88f, 0.98f };

    for (int i = 0; i < franjasCielo; i++)
    {
        float t1 = (float)i / franjasCielo;
        float t2 = (float)(i + 1) / franjasCielo;
        float y1 = 1.0f + (HORIZONTE - 1.0f) * t1;
        float y2 = 1.0f + (HORIZONTE - 1.0f) * t2;
        Color c = mezclar(cieloArriba, cieloAbajo, (t1 + t2) * 0.5f);
        cuadrilatero(m, -ancho, y1, ancho, y1, ancho, y2, -ancho, y2, c);
    }

    // Sol
    float solX = 0.68f;
    float solY = 0.65f;
    circulo(m, solX, solY, 0.24f, 0.24f, { 0.98f, 0.94f, 0.78f }, 32);
    circulo(m, solX, solY, 0.14f, 0.14f, { 1.00f, 0.97f, 0.82f }, 32);
    circulo(m, solX, solY, 0.085f, 0.085f, { 1.00f, 0.98f, 0.90f }, 32);

    // Nubes
    auto dibujarNube = [&](float cx, float cy, float escala)
        {
            Color sombraNube = { 0.86f, 0.91f, 0.96f };
            Color luzNube = { 0.98f, 0.99f, 1.00f };

            circulo(m, cx, cy - 0.015f * escala, 0.18f * escala, 0.055f * escala, sombraNube, 24);
            circulo(m, cx - 0.11f * escala, cy, 0.09f * escala, 0.055f * escala, luzNube, 24);
            circulo(m, cx, cy + 0.025f * escala, 0.11f * escala, 0.075f * escala, luzNube, 24);
            circulo(m, cx + 0.11f * escala, cy - 0.005f * escala, 0.085f * escala, 0.05f * escala, luzNube, 24);
        };

    dibujarNube(-0.72f, 0.68f, 1.15f);
    dibujarNube(-0.10f, 0.78f, 0.85f);
    dibujarNube(0.28f, 0.52f, 0.70f);
    dibujarNube(1.05f, 0.72f, 1.00f);

    // Colinas
    Color colinaLejana = mezclar({ 0.26f, 0.48f, 0.34f }, COLOR_BRUMA, 0.55f);
    circulo(m, -0.85f, HORIZONTE - 0.05f, 0.85f, 0.34f, colinaLejana, 36);
    circulo(m, 0.15f, HORIZONTE - 0.08f, 0.95f, 0.30f, colinaLejana, 36);
    circulo(m, 1.05f, HORIZONTE - 0.05f, 0.80f, 0.36f, colinaLejana, 36);

    Color colinaMedia = mezclar({ 0.24f, 0.50f, 0.26f }, COLOR_BRUMA, 0.25f);
    circulo(m, -0.45f, HORIZONTE - 0.06f, 0.75f, 0.22f, colinaMedia, 36);
    circulo(m, 0.60f, HORIZONTE - 0.06f, 0.82f, 0.24f, colinaMedia, 36);

    // Pasto
    int franjasPasto = 12;
    Color pastoLejano = { 0.34f, 0.62f, 0.28f };
    Color pastoCercano = { 0.20f, 0.46f, 0.17f };

    for (int i = 0; i < franjasPasto; i++)
    {
        float t1 = (float)i / franjasPasto;
        float t2 = (float)(i + 1) / franjasPasto;
        float y1 = HORIZONTE + (-1.0f - HORIZONTE) * t1;
        float y2 = HORIZONTE + (-1.0f - HORIZONTE) * t2;
        Color c = mezclar(pastoLejano, pastoCercano, (t1 + t2) * 0.5f);
        cuadrilatero(m, -ancho, y1, ancho, y1, ancho, y2, -ancho, y2, c);
    }
}