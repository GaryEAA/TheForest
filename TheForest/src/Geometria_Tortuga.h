#pragma once
#include <stack>
#include <map>
#include <utility>
#include "Contratos.h"

inline EstiloArbol crearEstilo(float angulo, float varAngulo, float varLongitud, float grosor, float radioHoja,
    float densidadHoja, Color tronco, Color hojaA, Color hojaB, TipoHoja tipoHoja)
{
    EstiloArbol e = EstiloArbol();
    e.angulo = angulo;
    e.varAngulo = varAngulo;
    e.varLongitud = varLongitud;
    e.grosor = grosor;
    e.radioHoja = radioHoja;
    e.densidadHoja = densidadHoja;
    e.tronco = tronco;
    e.hojaA = hojaA;
    e.hojaB = hojaB;
    e.tipoHoja = tipoHoja;
    return e;
}

inline EstiloArbol estiloDeEspecie(int especie)
{
    static const EstiloArbol tabla[NUM_ESPECIES] = {
        crearEstilo(28.0f, 10.0f, 0.25f, 0.035f, 0.045f, 0.6f, { 0.35f, 0.24f, 0.14f }, { 0.12f, 0.50f, 0.15f }, { 0.35f, 0.70f, 0.22f }, TipoHoja::Redonda),
        crearEstilo(55.0f, 8.0f, 0.2f, 0.03f, 0.04f, 0.7f, { 0.30f, 0.20f, 0.12f }, { 0.05f, 0.30f, 0.12f }, { 0.12f, 0.45f, 0.20f }, TipoHoja::Aguja),
        crearEstilo(32.0f, 12.0f, 0.25f, 0.035f, 0.05f, 0.65f, { 0.36f, 0.22f, 0.20f }, { 0.95f, 0.55f, 0.72f }, { 1.0f, 0.78f, 0.85f }, TipoHoja::Redonda),
        crearEstilo(30.0f, 12.0f, 0.3f, 0.035f, 0.045f, 0.65f, { 0.33f, 0.22f, 0.12f }, { 0.90f, 0.40f, 0.08f }, { 0.98f, 0.70f, 0.15f }, TipoHoja::Redonda),
        crearEstilo(35.0f, 10.0f, 0.25f, 0.035f, 0.045f, 0.65f, { 0.30f, 0.18f, 0.12f }, { 0.65f, 0.10f, 0.12f }, { 0.90f, 0.28f, 0.15f }, TipoHoja::Redonda),
        crearEstilo(14.0f, 6.0f, 0.2f, 0.03f, 0.04f, 0.8f, { 0.38f, 0.30f, 0.20f }, { 0.25f, 0.55f, 0.15f }, { 0.55f, 0.75f, 0.25f }, TipoHoja::Puntiaguda),
        crearEstilo(40.0f, 14.0f, 0.3f, 0.04f, 0.05f, 0.7f, { 0.32f, 0.26f, 0.16f }, { 0.40f, 0.65f, 0.25f }, { 0.65f, 0.82f, 0.35f }, TipoHoja::Puntiaguda),
        crearEstilo(48.0f, 10.0f, 0.3f, 0.04f, 0.055f, 0.55f, { 0.40f, 0.28f, 0.15f }, { 0.50f, 0.62f, 0.15f }, { 0.75f, 0.78f, 0.25f }, TipoHoja::Redonda),
        crearEstilo(22.0f, 9.0f, 0.25f, 0.03f, 0.04f, 0.65f, { 0.88f, 0.86f, 0.80f }, { 0.55f, 0.75f, 0.20f }, { 0.80f, 0.88f, 0.35f }, TipoHoja::Puntiaguda),
        crearEstilo(30.0f, 12.0f, 0.3f, 0.035f, 0.045f, 0.65f, { 0.28f, 0.20f, 0.30f }, { 0.10f, 0.55f, 0.65f }, { 0.30f, 0.80f, 0.80f }, TipoHoja::Redonda)
    };
    return tabla[especie % NUM_ESPECIES];
}

struct EstadoTortuga { float x, y, angulo; int prof; };

struct Rasgos
{
    float tropismo;
    float decaimiento;
    float ondulacion;
};

inline Rasgos rasgosDe(const EstiloArbol& e)
{
    Rasgos r;
    r.tropismo = (28.0f - e.angulo) * 0.010f;
    r.decaimiento = 0.88f;
    if (e.tipoHoja == TipoHoja::Puntiaguda && e.angulo >= 35.0f) r.tropismo -= 0.22f;
    if (e.tipoHoja == TipoHoja::Aguja) { r.tropismo -= 0.12f; r.decaimiento = 0.80f; }
    r.ondulacion = 2.0f + e.varAngulo * 0.3f;
    return r;
}

inline float suave(Azar& az, float amplitud)
{
    return (az.rango(-1.0f, 1.0f) + az.rango(-1.0f, 1.0f)) * 0.5f * amplitud;
}

inline Esqueleto interpretar(const std::string& cadena, const EstiloArbol& estilo, float altura, Azar& az)
{
    Esqueleto e;
    std::stack<EstadoTortuga> pila;
    Rasgos r = rasgosDe(estilo);

    float inclinacion = az.rango(-4.0f, 4.0f);
    float rumbo = 90.0f + inclinacion;
    float sesgo = az.rango(0.88f, 1.12f);
    EstadoTortuga t = { 0.0f, 0.0f, rumbo, 0 };

    for (size_t i = 0; i < cadena.size(); i++)
    {
        char c = cadena[i];
        if (c == 'F' || c == 'f')
        {
            float largo = std::pow(r.decaimiento, (float)t.prof) * az.rango(1.0f - estilo.varLongitud, 1.0f + estilo.varLongitud);
            float rad = t.angulo * PI / 180.0f;
            float nx = t.x + largo * std::cos(rad);
            float ny = t.y + largo * std::sin(rad);

            if (c == 'F')
            {
                e.ramas.push_back({ t.x, t.y, nx, ny, t.prof });

                bool punta = (i + 1 == cadena.size()) || cadena[i + 1] == ']';
                if (!punta && t.prof >= 1 && az.unidad() < estilo.densidadHoja * 0.25f) punta = true;
                if (punta) e.puntas.push_back({ nx, ny, t.angulo, t.prof });
            }

            t.x = nx;
            t.y = ny;

            if (t.prof == 0)
            {
                t.angulo += suave(az, r.ondulacion);
                t.angulo += (rumbo - t.angulo) * 0.35f;
            }
            else
            {
                float desviacion = std::sin((90.0f - t.angulo) * PI / 180.0f);
                t.angulo += r.tropismo * 25.0f * desviacion;
            }
        }
        else if (c == '+') t.angulo -= (estilo.angulo + az.rango(-estilo.varAngulo, estilo.varAngulo)) * sesgo;
        else if (c == '-') t.angulo += (estilo.angulo + az.rango(-estilo.varAngulo, estilo.varAngulo)) * (2.0f - sesgo);
        else if (c == '|') t.angulo += 180.0f;
        else if (c == '[') { pila.push(t); t.prof++; }
        else if (c == ']' && !pila.empty()) { t = pila.top(); pila.pop(); }
    }

    float maxY = 0.001f, maxX = 0.001f;
    for (const Segmento& s : e.ramas)
    {
        maxY = std::max(maxY, std::max(s.y1, s.y2));
        maxX = std::max(maxX, std::max(std::fabs(s.x1), std::fabs(s.x2)));
    }
    float escala = std::min(altura / maxY, altura * 0.9f / maxX);

    for (Segmento& s : e.ramas) { s.x1 *= escala; s.y1 *= escala; s.x2 *= escala; s.y2 *= escala; }
    for (PuntaHoja& h : e.puntas) { h.x *= escala; h.y *= escala; }
    return e;
}

inline Color tono(Color c, float k)
{
    return { limitar(c.r * k, 0.0f, 1.0f), limitar(c.g * k, 0.0f, 1.0f), limitar(c.b * k, 0.0f, 1.0f) };
}

inline std::vector<float> calcularAnchos(const Esqueleto& esq, const EstiloArbol& estilo, float altura, std::vector<float>& anchoFinal)
{
    int n = (int)esq.ramas.size();
    std::map<std::pair<float, float>, std::vector<int>> inicios;
    for (int i = 0; i < n; i++) inicios[{ esq.ramas[i].x1, esq.ramas[i].y1 }].push_back(i);

    std::vector<float> carga(n, 1.0f);
    for (int i = n - 1; i >= 0; i--)
    {
        auto it = inicios.find({ esq.ramas[i].x2, esq.ramas[i].y2 });
        if (it == inicios.end()) continue;
        float suma = 0.0f;
        for (int j : it->second) if (j > i) suma += carga[j];
        if (suma > 0.0f) carga[i] = suma;
    }

    float raiz = 1.0f;
    for (float c : carga) raiz = std::max(raiz, c);

    float ancho0 = estilo.grosor * altura;
    std::vector<float> ancho(n);
    for (int i = 0; i < n; i++)
        ancho[i] = std::max(ancho0 * std::pow(carga[i] / raiz, 0.55f), 0.0035f);

    anchoFinal.assign(n, 0.0f);
    for (int i = 0; i < n; i++)
    {
        auto it = inicios.find({ esq.ramas[i].x2, esq.ramas[i].y2 });
        float fin = ancho[i] * 0.7f;
        if (it != inicios.end())
        {
            fin = 0.0f;
            for (int j : it->second) if (j > i) fin = std::max(fin, ancho[j]);
            if (fin <= 0.0f) fin = ancho[i] * 0.7f;
        }
        anchoFinal[i] = std::min(std::max(fin, 0.0030f), ancho[i]);
    }
    return ancho;
}

inline void dibujarBase(float x, float y, float ancho, Color corteza, Malla& m)
{
    Color oscuro = tono(corteza, 0.7f);
    triangulo(m, x - ancho * 1.8f, y - 0.006f, x - ancho * 0.45f, y + ancho * 1.9f, x + ancho * 0.1f, y, oscuro);
    triangulo(m, x + ancho * 1.8f, y - 0.006f, x + ancho * 0.45f, y + ancho * 1.9f, x - ancho * 0.1f, y, tono(corteza, 0.85f));
    triangulo(m, x - ancho * 0.7f, y - 0.004f, x + ancho * 0.7f, y - 0.004f, x, y + ancho * 1.3f, tono(corteza, 0.9f));
}

inline void dibujarRamas(const Esqueleto& esq, const EstiloArbol& estilo, float altura, float baseX, float baseY, Azar& az, Malla& m)
{
    std::vector<float> anchoFin;
    std::vector<float> ancho = calcularAnchos(esq, estilo, altura, anchoFin);
    Color ramita = { 0.45f, 0.35f, 0.25f };
    float ancho0 = estilo.grosor * altura;

    for (int i = 0; i < (int)esq.ramas.size(); i++)
    {
        const Segmento& s = esq.ramas[i];
        float dx = s.x2 - s.x1, dy = s.y2 - s.y1;
        float largo = std::sqrt(dx * dx + dy * dy);
        if (largo < 0.00001f) continue;

        float nx = -dy / largo, ny = dx / largo;
        float curva = largo * suave(az, 0.12f);
        float cx = (s.x1 + s.x2) * 0.5f + nx * curva;
        float cy = (s.y1 + s.y2) * 0.5f + ny * curva;

        float finura = 1.0f - std::sqrt(ancho[i] / ancho0);
        Color base = variar(mezclar(estilo.tronco, ramita, limitar(finura * 0.6f + s.prof * 0.04f, 0.0f, 0.6f)), az, 0.02f);
        Color sombra = tono(base, 0.78f);
        Color luz = tono(base, 1.08f);

        int tramos = ancho[i] > 0.012f ? 5 : 3;
        float izqX0 = 0, izqY0 = 0, medX0 = 0, medY0 = 0, derX0 = 0, derY0 = 0;

        for (int k = 0; k <= tramos; k++)
        {
            float u = (float)k / tramos;
            float a = (1.0f - u) * (1.0f - u), b = 2.0f * (1.0f - u) * u, c = u * u;
            float mx = a * s.x1 + b * cx + c * s.x2;
            float my = a * s.y1 + b * cy + c * s.y2;
            float tx = 2.0f * (1.0f - u) * (cx - s.x1) + 2.0f * u * (s.x2 - cx);
            float ty = 2.0f * (1.0f - u) * (cy - s.y1) + 2.0f * u * (s.y2 - cy);
            float tl = std::sqrt(tx * tx + ty * ty);
            if (tl < 0.000001f) { tx = dx; ty = dy; tl = largo; }
            float ox = -ty / tl, oy = tx / tl;
            float w = (ancho[i] + (anchoFin[i] - ancho[i]) * u) * 0.5f;

            float izqX = baseX + mx + ox * w, izqY = baseY + my + oy * w;
            float medX = baseX + mx, medY = baseY + my;
            float derX = baseX + mx - ox * w, derY = baseY + my - oy * w;

            if (k > 0)
            {
                cuadrilatero(m, izqX0, izqY0, medX0, medY0, medX, medY, izqX, izqY, sombra);
                cuadrilatero(m, medX0, medY0, derX0, derY0, derX, derY, medX, medY, luz);
            }
            izqX0 = izqX; izqY0 = izqY; medX0 = medX; medY0 = medY; derX0 = derX; derY0 = derY;
        }

        float wf = anchoFin[i] * 0.5f;
        if (wf > 0.0035f)
            circulo(m, baseX + s.x2, baseY + s.y2, wf, wf, base, 8);
    }

    if (!esq.ramas.empty())
        dibujarBase(baseX + esq.ramas[0].x1, baseY + esq.ramas[0].y1, ancho[0], estilo.tronco, m);
}