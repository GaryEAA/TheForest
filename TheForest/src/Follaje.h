
#pragma once
#include "Contratos.h"

// ============================================================
// FUNCIONES AUXILIARES DEL FOLLAJE
// ============================================================

// Calcula el peso de un vertice para el movimiento del viento.
inline float pesoFollaje(float y, float baseY, float altura)
{
    float alto = std::max(altura, 0.001f);
    return limitar((y - baseY) / alto, 0.0f, 1.0f);
}


// ============================================================
// DIBUJAR UNA HOJA PUNTIAGUDA O TIPO AGUJA
// ============================================================

inline void dibujarHojaPoligonal(
    Malla& m,
    float x,
    float y,
    float largo,
    float ancho,
    float direccion,
    Color color,
    float baseY,
    float altura)
{
    // Convertir grados a radianes.
    float rad = direccion * PI / 180.0f;

    // Direccion de crecimiento de la hoja.
    float dx = std::cos(rad);
    float dy = std::sin(rad);

    // Vector perpendicular para dar anchura.
    float px = -dy * ancho;
    float py = dx * ancho;

    // Cuatro vertices de la hoja.
    float bx = x - dx * largo * 0.5f;
    float by = y - dy * largo * 0.5f;

    float tx = x + dx * largo * 0.5f;
    float ty = y + dy * largo * 0.5f;

    float x1 = x + px;
    float y1 = y + py;

    float x2 = x - px;
    float y2 = y - py;

    // Pesos para el viento.
    float pb = pesoFollaje(by, baseY, altura);
    float pt = pesoFollaje(ty, baseY, altura);
    float p1 = pesoFollaje(y1, baseY, altura);
    float p2 = pesoFollaje(y2, baseY, altura);

    // Formar la hoja con dos triangulos.
    triangulo(
        m,
        bx, by,
        x1, y1,
        tx, ty,
        color,
        pb, p1, pt
    );

    triangulo(
        m,
        bx, by,
        tx, ty,
        x2, y2,
        color,
        pb, pt, p2
    );
}


// ============================================================
// 1. DIBUJAR HOJAS DE LOS ARBOLES
// ============================================================

inline void dibujarHojas(
    const Esqueleto& esq,
    const EstiloArbol& estilo,
    float altura,
    float baseX,
    float baseY,
    Azar& az,
    Malla& m)
{
    if (esq.puntas.empty())
        return;

    // Control de densidad.
    float densidad = limitar(
        estilo.densidadHoja,
        0.2f,
        1.0f
    );

    // Tamano de las hojas segun la especie.
    float radio = std::max(
        estilo.radioHoja,
        altura * 0.025f
    );

    // Distancia maxima de distribucion alrededor de cada punta.
    float dispersion = radio * (1.0f + densidad * 1.4f);

    // Recorrer todas las puntas del arbol.
    for (const PuntaHoja& punta : esq.puntas)
    {
        float centroX = baseX + punta.x;
        float centroY = baseY + punta.y;

        // Variacion del color segun la especie.
        Color colorBase = mezclar(
            estilo.hojaA,
            estilo.hojaB,
            0.5f
        );

        // ----------------------------------------------------
        // HOJAS REDONDAS
        // ----------------------------------------------------

        if (estilo.tipoHoja == TipoHoja::Redonda)
        {
            // Masa central de follaje.
            circulo(
                m,
                centroX,
                centroY,
                radio * 0.85f,
                radio * 0.75f,
                variar(colorBase, az, 0.045f),
                12,
                baseY,
                altura
            );

            // Cantidad de hojas alrededor de la punta.
            int cantidad = 5 + (int)(densidad * 7.0f);

            for (int i = 0; i < cantidad; i++)
            {
                float angulo = az.rango(0.0f, 2.0f * PI);

                float distancia = az.rango(
                    dispersion * 0.25f,
                    dispersion
                );

                float x = centroX + std::cos(angulo) * distancia;
                float y = centroY + std::sin(angulo) * distancia;

                float rx = radio * az.rango(0.45f, 0.85f);
                float ry = rx * az.rango(0.75f, 1.15f);

                Color color = mezclar(
                    estilo.hojaA,
                    estilo.hojaB,
                    az.unidad()
                );

                color = variar(color, az, 0.06f);

                circulo(
                    m,
                    x,
                    y,
                    rx,
                    ry,
                    color,
                    12,
                    baseY,
                    altura
                );
            }
        }

        // ----------------------------------------------------
        // HOJAS PUNTIAGUDAS
        // ----------------------------------------------------

        else if (estilo.tipoHoja == TipoHoja::Puntiaguda)
        {
            // Pequena masa vegetal en la punta.
            circulo(
                m,
                centroX,
                centroY,
                radio * 0.45f,
                radio * 0.4f,
                variar(colorBase, az, 0.04f),
                10,
                baseY,
                altura
            );

            int cantidad = 6 + (int)(densidad * 7.0f);

            for (int i = 0; i < cantidad; i++)
            {
                float direccion = punta.dir +
                    az.rango(-180.0f, 180.0f);

                float angulo = az.rango(0.0f, 2.0f * PI);

                float distancia = az.rango(
                    0.0f,
                    dispersion
                );

                float x = centroX + std::cos(angulo) * distancia;
                float y = centroY + std::sin(angulo) * distancia;

                float largo = radio * az.rango(1.0f, 1.8f);
                float ancho = radio * az.rango(0.22f, 0.42f);

                Color color = mezclar(
                    estilo.hojaA,
                    estilo.hojaB,
                    az.unidad()
                );

                color = variar(color, az, 0.05f);

                dibujarHojaPoligonal(
                    m,
                    x,
                    y,
                    largo,
                    ancho,
                    direccion,
                    color,
                    baseY,
                    altura
                );
            }
        }

        // ----------------------------------------------------
        // HOJAS TIPO AGUJA
        // ----------------------------------------------------

        else if (estilo.tipoHoja == TipoHoja::Aguja)
        {
            int cantidad = 9 + (int)(densidad * 9.0f);

            for (int i = 0; i < cantidad; i++)
            {
                float direccion = punta.dir +
                    az.rango(-180.0f, 180.0f);

                float angulo = az.rango(0.0f, 2.0f * PI);

                float distancia = az.rango(
                    0.0f,
                    dispersion
                );

                float x = centroX + std::cos(angulo) * distancia;
                float y = centroY + std::sin(angulo) * distancia;

                float largo = radio * az.rango(1.2f, 2.0f);
                float ancho = radio * az.rango(0.08f, 0.18f);

                Color color = mezclar(
                    estilo.hojaA,
                    estilo.hojaB,
                    az.unidad()
                );

                color = variar(color, az, 0.045f);

                dibujarHojaPoligonal(
                    m,
                    x,
                    y,
                    largo,
                    ancho,
                    direccion,
                    color,
                    baseY,
                    altura
                );
            }
        }
    }
}


// ============================================================
// 2. DIBUJAR ARBUSTOS
// ============================================================

inline void dibujarArbustos(
    float x,
    float y,
    float alturaArbol,
    Azar& az,
    Malla& m)
{
    // Altura del terreno.
    float suelo = std::max(y, HORIZONTE);

    // Tamano proporcional al arbol.
    float radioBase = limitar(
        alturaArbol * 0.07f,
        0.035f,
        0.075f
    );

    // Paleta de verdes para los arbustos.
    Color verdeOscuro = { 0.08f, 0.32f, 0.10f };
    Color verdeMedio = { 0.16f, 0.46f, 0.15f };
    Color verdeClaro = { 0.27f, 0.58f, 0.20f };

    // Tres grupos que forman un arbusto continuo.
    for (int grupo = -1; grupo <= 1; grupo++)
    {
        float centroX = x + grupo * radioBase * 1.15f;

        // Varias masas vegetales por grupo.
        int cantidad = 6;

        for (int i = 0; i < cantidad; i++)
        {
            float desplazamientoX = az.rango(
                -radioBase * 0.65f,
                radioBase * 0.65f
            );

            float rx = radioBase * az.rango(0.50f, 0.90f);
            float ry = radioBase * az.rango(0.55f, 0.95f);

            float centroY = suelo + ry * az.rango(0.45f, 0.70f);

            // Variar tonalidades de verde.
            float mezcla = az.unidad();

            Color color;

            if (mezcla < 0.5f)
            {
                color = mezclar(
                    verdeOscuro,
                    verdeMedio,
                    mezcla * 2.0f
                );
            }
            else
            {
                color = mezclar(
                    verdeMedio,
                    verdeClaro,
                    (mezcla - 0.5f) * 2.0f
                );
            }

            color = variar(color, az, 0.035f);

            circulo(
                m,
                centroX + desplazamientoX,
                centroY,
                rx,
                ry,
                color,
                12,
                suelo,
                alturaArbol * 0.18f
            );
        }
    }
}
