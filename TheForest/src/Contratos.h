#pragma once
#include <string>
#include "Comun.h"

const int NUM_ESPECIES = 10;
const float HORIZONTE = -0.25f;
const Color COLOR_BRUMA = { 0.78f, 0.88f, 0.97f };

struct Opcion { float probabilidad; std::string reemplazo; };
struct Regla { char simbolo; std::vector<Opcion> opciones; };

struct ReglasL
{
    std::string axioma;
    std::vector<Regla> reglas;
    int iteraciones;
};

enum class TipoHoja { Redonda, Puntiaguda, Aguja };

struct EstiloArbol
{
    float angulo;
    float varAngulo;
    float varLongitud;
    float grosor;
    float radioHoja;
    float densidadHoja;
    Color tronco;
    Color hojaA;
    Color hojaB;
    TipoHoja tipoHoja;
};

struct Segmento { float x1, y1, x2, y2; int prof; };
struct PuntaHoja { float x, y, dir; int prof; };

struct Esqueleto
{
    std::vector<Segmento> ramas;
    std::vector<PuntaHoja> puntas;
};

inline ReglasL reglasDeEspecie(int especie);
inline std::string generarCadena(const ReglasL& reglas, Azar& az);

inline EstiloArbol estiloDeEspecie(int especie);
inline Esqueleto interpretar(const std::string& cadena, const EstiloArbol& estilo, float altura, Azar& az);
inline void dibujarRamas(const Esqueleto& esq, const EstiloArbol& estilo, float altura, float baseX, float baseY, Azar& az, Malla& m);

inline void dibujarHojas(const Esqueleto& esq, const EstiloArbol& estilo, float altura, float baseX, float baseY, Azar& az, Malla& m);
inline void dibujarArbustos(float x, float y, float alturaArbol, Azar& az, Malla& m);

inline Malla construirBosque(unsigned semilla);
inline void dibujarFondo(Malla& m);
inline float calcularViento(float tiempo);
