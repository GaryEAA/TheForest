#pragma once
#include "Contratos.h"

const size_t LONGITUD_MAXIMA = 200000;

struct TablaReglas
{
    const Regla* porSimbolo[256] = {};
};

inline TablaReglas armarTabla(const ReglasL& reglas)
{
    TablaReglas tabla;
    for (const Regla& r : reglas.reglas)
    {
        if (!r.opciones.empty())  
            tabla.porSimbolo[(unsigned char)r.simbolo] = &r;
    }
    return tabla;
}

inline const std::string& elegirOpcion(const Regla& regla, Azar& az)
{
    
    float total = 0.0f;
    for (const Opcion& o : regla.opciones)
        total += std::max(0.0f, o.probabilidad);

    if (total <= 0.0f)                       
        return regla.opciones[0].reemplazo;

    float dado = az.unidad() * total;        
    float acumulado = 0.0f;
    for (const Opcion& o : regla.opciones)
    {
        acumulado += std::max(0.0f, o.probabilidad);
        if (dado < acumulado)
            return o.reemplazo;
    }
    return regla.opciones.back().reemplazo;
}

inline std::string reescribir(const std::string& cadena, const TablaReglas& tabla, Azar& az)
{
    std::string nueva;
    nueva.reserve(cadena.size() * 4); 

    for (char c : cadena)
    {
        const Regla* regla = tabla.porSimbolo[(unsigned char)c];
        if (regla)
            nueva += elegirOpcion(*regla, az);
        else
            nueva += c;
    }
    return nueva;
}

inline std::string generarCadena(const ReglasL& reglas, Azar& az)
{
    TablaReglas tabla = armarTabla(reglas);
    std::string cadena = reglas.axioma;

    for (int i = 0; i < reglas.iteraciones; i++)
    {
        std::string siguiente = reescribir(cadena, tabla, az);
        if (siguiente.size() > LONGITUD_MAXIMA)
            break;
        cadena = siguiente;
    }
    return cadena;
}
