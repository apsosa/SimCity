
#ifndef AED2_SIMCITY_H
#define AED2_SIMCITY_H

#include <iostream>
#include <set>
#include "aed2_Mapa.h"
#include <map>

using namespace std;

using Nat = unsigned int;
using Casas = map<Casilla, Nat>;
using Comercios = map<Casilla, Nat>;

using SimCity = tuple< aed2_Mapa, Nat, Casas, Comercios, set<Casilla>, set<Comercios>, set<tuple<set<Casilla>,Comercios>>, set<Mapa>, Nat, bool>; /* Completar con su clase implementada de SimCity */


class aed2_SimCity {
public:

    // Generadores:

    aed2_SimCity(aed2_Mapa m);

    // Precondicion: Se puede construir en la Casilla c
    void agregarCasa(Casilla c);

    // Precondicion: Se puede construir en la Casilla c
    void agregarComercio(Casilla c);

    // Precondicion: Hubo construccion en el turno actual
    void avanzarTurno();

    // Precondicion: No se solapan las construcciones con los rios
    //  ni las construcciones de nivel maximo de ambas partidas
    void unir(aed2_SimCity sc);

    // Observadores:

    Mapa mapa() const;

    set<Casilla> casas() const;

    set<Casilla> comercios() const;

    // Precondicion: Hay construccion en la Casilla p
    Nat nivel(Casilla c) const;

    bool huboConstruccion() const;

    Nat popularidad() const;

    Nat antiguedad() const;

    // Conversiones
    
    // Esta función sirve para convertir del SimCity de la cátedra al SimCity
    // implementado por ustedes
    SimCity simCity();

    //Auxiliares agregados por fede()
    map<Casilla, Nat> unirCasasPriorizandoMaximoNivel() const;
    set<Casilla> Union(set<Casilla>, set<Casilla>) const;
    map<Casilla,Nat>  unirCasas(map<Casilla,Nat>, map<Casilla,Nat>) const;
    map<Casilla,Nat> Union(map<Casilla,Nat>, map<Casilla,Nat>) const;

    //Auxiliares agregados por pato()
    Comercios unirComerciosPriozandoMaximoNivel() const;
    Comercios unirComercios(Comercios,Comercios) const;
    Nat darNivelAComercio(Casilla) const;
    Nat maxNivelManhattan(Casilla,Casas) const;
    set<Casilla> casasAdistancia_3Manhattan(set<Casilla>,Casilla) const;

    //auxiliares agregadas por elias()
    set<Casilla> claves(map<Casilla, Nat>) const;
    Nat distanciaManhattan(Casilla,Casilla) const;
    set<map<Casilla,Nat>> Union(set<map<Casilla,Nat>>,set<map<Casilla,Nat>>);
    set<Mapa> unionDeOtrosMapas(set<Mapa>, set<Mapa>);
    set<pair<set<Casilla>, Comercios>> Union(set<pair<set<Casilla>, Comercios>>,set<pair<set<Casilla>, Comercios>>) const;
    //para union??
    Nat turno() const;
    Casas casasU() const;
    Comercios comerciosU() const;
    set<Casilla> comerciosRecientesU() const;
    set<Comercios> comerciosDeOtrosSCU() const;
    set<pair<set<Casilla>, Comercios>> casasYcomerciosRecientesDeOtrosSCU() const;
    set<Mapa> mapasRecientesDeOtrosSCU() const;


private:
    aed2_Mapa _mapa;
    Nat _turno;
    Casas _casas;
    Comercios _comercios;
    set<Casilla> _comerciosRecientes;
    set<Comercios> _comerciosDeOtrosSC;
    set<pair<set<Casilla>, Casas> > _casasYcomerciosRecientesDeOtrosSC;
    set<Mapa> _mapasRecientesDeOtrosSC;
    Nat _popularidad;
    bool _huboConstruccion;


};


;


#endif // AED2_SIMCITY_H
