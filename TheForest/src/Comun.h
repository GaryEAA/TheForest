#pragma once
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

const float PI = 3.14159265359f;

struct Color { float r, g, b; };

struct Malla
{
    std::vector<float> datos;
    int vertices() const { return (int)datos.size() / 7; }
};

struct Azar
{
    std::mt19937 gen;
    explicit Azar(unsigned semilla) : gen(semilla) {}
    float rango(float a, float b) { return std::uniform_real_distribution<float>(a, b)(gen); }
    float unidad() { return rango(0.0f, 1.0f); }
};

inline float limitar(float v, float minimo, float maximo)
{
    return v < minimo ? minimo : (v > maximo ? maximo : v);
}

inline Color mezclar(Color a, Color b, float t)
{
    return { a.r + (b.r - a.r) * t, a.g + (b.g - a.g) * t, a.b + (b.b - a.b) * t };
}

inline Color variar(Color c, Azar& az, float cantidad)
{
    float d = az.rango(-cantidad, cantidad);
    return { limitar(c.r + d, 0.0f, 1.0f), limitar(c.g + d, 0.0f, 1.0f), limitar(c.b + d, 0.0f, 1.0f) };
}

inline void vertice(Malla& m, float x, float y, Color c, float peso = 0.0f)
{
    m.datos.push_back(x); m.datos.push_back(y); m.datos.push_back(0.0f);
    m.datos.push_back(c.r); m.datos.push_back(c.g); m.datos.push_back(c.b);
    m.datos.push_back(peso);
}

inline void triangulo(Malla& m, float x1, float y1, float x2, float y2, float x3, float y3, Color c,
    float p1 = 0.0f, float p2 = 0.0f, float p3 = 0.0f)
{
    vertice(m, x1, y1, c, p1);
    vertice(m, x2, y2, c, p2);
    vertice(m, x3, y3, c, p3);
}

inline void cuadrilatero(Malla& m, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, Color c)
{
    triangulo(m, x1, y1, x2, y2, x3, y3, c);
    triangulo(m, x1, y1, x3, y3, x4, y4, c);
}

inline void circulo(Malla& m, float cx, float cy, float rx, float ry, Color c, int lados,
    float baseY = 0.0f, float alto = 0.0f)
{
    auto peso = [&](float y) { return alto > 0.0f ? limitar((y - baseY) / alto, 0.0f, 1.0f) : 0.0f; };
    for (int i = 0; i < lados; i++)
    {
        float a1 = 2.0f * PI * i / lados;
        float a2 = 2.0f * PI * (i + 1) / lados;
        float x1 = cx + rx * std::cos(a1), y1 = cy + ry * std::sin(a1);
        float x2 = cx + rx * std::cos(a2), y2 = cy + ry * std::sin(a2);
        triangulo(m, cx, cy, x1, y1, x2, y2, c, peso(cy), peso(y1), peso(y2));
    }
}

inline void aplicarBruma(Malla& m, int desdeVertice, Color bruma, float t)
{
    for (size_t i = (size_t)desdeVertice * 7; i < m.datos.size(); i += 7)
    {
        Color c = mezclar({ m.datos[i + 3], m.datos[i + 4], m.datos[i + 5] }, bruma, t);
        m.datos[i + 3] = c.r; m.datos[i + 4] = c.g; m.datos[i + 5] = c.b;
    }
}
