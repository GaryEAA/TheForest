#pragma once
#include "Contratos.h"

inline ReglasL reglasDeEspecie(int especie)
{
    ReglasL r;
    r.axioma = "F";
    r.iteraciones = 1;
    r.reglas.push_back({ 'F', { { 1.0f, "F[+F]F[-F]F" } } });
    return r;
}
