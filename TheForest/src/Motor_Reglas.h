
#pragma once
#include "Contratos.h"

inline ReglasL reglasDeEspecie(int especie)
{
    ReglasL r;
    r.axioma = "F";

    switch (especie)
    {
    case 0:
        // Arbol 1: copa amplia y ramas equilibradas
        r.iteraciones = 4;
        r.reglas.push_back({
            'F', {
                {0.60f, "F[+F]F[-F]F"},
                {0.40f, "F[+F][-F]F"}
            }
            });
        break;

    case 1:
        // Arbol 2: ramificacion hacia los lados
        r.iteraciones = 4;
        r.reglas.push_back({
            'F', {
                {0.55f, "F[+F][+F]F"},
                {0.45f, "F[-F]F[+F]"}
            }
            });
        break;

    case 2:
        // Arbol 3: crecimiento vertical
        r.iteraciones = 3;
        r.reglas.push_back({
            'F', {
                {0.70f, "FF[+F][-F]"},
                {0.30f, "F[+F]F"}
            }
            });
        break;

    case 3:
        // Arbol 4: copa irregular
        r.iteraciones = 4;
        r.reglas.push_back({
            'F', {
                {0.50f, "F[-F]F[+F]"},
                {0.30f, "F[+F][+F]"},
                {0.20f, "F[-F][-F]"}
            }
            });
        break;

    case 4:
        // Arbol 5: ramas abiertas
        r.iteraciones = 3;
        r.reglas.push_back({
            'F', {
                {0.65f, "F[+F][-F]F"},
                {0.35f, "F[+F]F[-F]"}
            }
            });
        break;

    case 5:
        // Arbol 6: estructura densa
        r.iteraciones = 4;
        r.reglas.push_back({
            'F', {
                {0.60f, "F[+F]F[-F][F]"},
                {0.40f, "F[-F]F[+F]F"}
            }
            });
        break;

    case 6:
        // Arbol 7: ramificacion asimetrica
        r.iteraciones = 4;
        r.reglas.push_back({
            'F', {
                {0.50f, "F[+F]F[+F]"},
                {0.50f, "F[-F]F[+F]"}
            }
            });
        break;

    case 7:
        // Arbol 8: copa compacta
        r.iteraciones = 3;
        r.reglas.push_back({
            'F', {
                {0.60f, "F[+F][-F]"},
                {0.40f, "F[+F]F[-F]"}
            }
            });
        break;

    case 8:
        // Arbol 9: ramas abundantes
        r.iteraciones = 4;
        r.reglas.push_back({
            'F', {
                {0.45f, "F[+F][-F][+F]"},
                {0.35f, "F[-F]F[+F]"},
                {0.20f, "F[+F]F[-F]F"}
            }
            });
        break;

    case 9:
        // Arbol 10: crecimiento extendido
        r.iteraciones = 4;
        r.reglas.push_back({
            'F', {
                {0.55f, "F[+F]F[-F]F"},
                {0.45f, "F[-F][-F]F[+F]"}
            }
            });
        break;

    default:
        // Regla de respaldo
        r.iteraciones = 3;
        r.reglas.push_back({
            'F', {
                {1.0f, "F[+F]F[-F]F"}
            }
            });
        break;
    }

    return r;
}
