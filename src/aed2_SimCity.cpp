#include "aed2_SimCity.h"

// Completar

aed2_SimCity::aed2_SimCity(aed2_Mapa m): _mapa(m),_turno(),_casas(),_comercios(),_comerciosRecientes(),_comerciosDeOtrosSC(),_casasYcomerciosRecientesDeOtrosSC(),_mapasRecientesDeOtrosSC(),_popularidad(),_huboConstruccion(){
	_mapa = m;
	_turno = 0;
	_popularidad = 0;
	_huboConstruccion = false;
}


void aed2_SimCity::agregarCasa(Casilla c)
{
	this->_casas.insert({c,0});
	this->_huboConstruccion = true;
}


void  aed2_SimCity::agregarComercio(Casilla c)
{
	this->_comerciosRecientes.insert(c);
	this->_huboConstruccion = true;
}


void aed2_SimCity::avanzarTurno(){
    _turno++;
    if(!this->_comerciosRecientes.empty()){
        for(auto it = this->_comerciosRecientes.begin(); it != _comerciosRecientes.end(); it++){
            Nat max = this->darNivelAComercio(it.operator*());
            this->_comercios.insert(make_pair(it.operator*(),max));
        }
    }
    _comerciosRecientes.clear();
    this->_casas = unirCasasPriorizandoMaximoNivel();
    this->_comercios = unirComerciosPriozandoMaximoNivel();
    for(auto it = _casas.begin(); it!= _casas.end(); it++){
        if(_comercios.count(it.operator*().first)==1){
            _comercios.erase(it.operator*().first);
        }
    }
    _comerciosDeOtrosSC.clear();

    for(auto it = this->_casasYcomerciosRecientesDeOtrosSC.begin(); it != this->_casasYcomerciosRecientesDeOtrosSC.end(); it++){
        for(auto itComR = it.operator*().first.begin(); itComR != it.operator*().first.end() && this->_casas.count(itComR.operator*())!=1; itComR++){
            _comercios.insert(make_pair(itComR.operator*(),darNivelAComercio(itComR.operator*())));  //     Fijarse esto porque no matchea
        }
      //  _casasYcomerciosRecientesDeOtrosSC.erase(it.operator*());
    }
    _casasYcomerciosRecientesDeOtrosSC.clear();

    for(auto it = _comercios.begin(); it!=_comercios.end(); it++){
        if(!(casasAdistancia_3Manhattan(claves(_casas),it.operator*().first).empty())){
            _comercios[it.operator*().first]=max(nivel(it.operator*().first),darNivelAComercio(it.operator*().first));
        }
    }
    for(auto it = this->_casas.begin(); it != _casas.end(); it++){
        it.operator*().second++;
    }
    for(auto it = this->_comercios.begin(); it != _comercios.end(); it++){
        it.operator*().second++;
    }
    for(auto it = this->_mapasRecientesDeOtrosSC.begin(); it != this->_mapasRecientesDeOtrosSC.end();it++){
         _mapa.unirMapa(it.operator*());  //Fijarse porque no funca unirMapa
    }
    _mapasRecientesDeOtrosSC.clear();
    _huboConstruccion = false;
}

void aed2_SimCity::unir(aed2_SimCity sc){
    if(_turno < sc.turno()){
        _turno = sc.turno();
    }
    _comerciosDeOtrosSC.insert(sc.comerciosU());
    _popularidad = _popularidad + sc.popularidad() + 1;
    _comerciosDeOtrosSC = Union(_comerciosDeOtrosSC, sc.comerciosDeOtrosSCU());
    _casasYcomerciosRecientesDeOtrosSC = Union(_casasYcomerciosRecientesDeOtrosSC,sc.casasYcomerciosRecientesDeOtrosSCU());
    _casasYcomerciosRecientesDeOtrosSC.insert(make_pair(sc.comerciosRecientesU(),sc.casasU()));
    _mapasRecientesDeOtrosSC = unionDeOtrosMapas(_mapasRecientesDeOtrosSC,sc.mapasRecientesDeOtrosSCU());
    _mapasRecientesDeOtrosSC.insert(sc.mapa());
    _huboConstruccion = _huboConstruccion || sc.huboConstruccion();
}

Mapa  aed2_SimCity::mapa() const
{
	aed2_Mapa m = this->_mapa;
	for(auto it = this->_mapasRecientesDeOtrosSC.begin(); it != this->_mapasRecientesDeOtrosSC.end();it++){
	    m.unirMapa(it.operator*());
	}

	return m.mapa();

}

set<Casilla> aed2_SimCity::casas() const
{
    if(_casasYcomerciosRecientesDeOtrosSC.empty()){
         return claves(_casas);
    }else {
        set<Casilla> res = claves(_casas);
        for(auto it = _casasYcomerciosRecientesDeOtrosSC.begin(); it != _casasYcomerciosRecientesDeOtrosSC.end(); it++){
            set<Casilla> temp = claves(it.operator*().second);
            res = Union(temp,res);
        }
        return res;
    }
}

set<Casilla> aed2_SimCity::comercios() const
{
	set<Casilla> c = Union(claves(_comercios),_comerciosRecientes);
	for(auto it = _comerciosDeOtrosSC.begin(); it != _comerciosDeOtrosSC.end(); it++ ){
	    c = Union(c, claves(it.operator*()));
	}
	for(auto it = _casasYcomerciosRecientesDeOtrosSC.begin(); it != _casasYcomerciosRecientesDeOtrosSC.end(); it++){
	    c = Union(c,it.operator*().first);
	}
	set<Casilla> prueba = this->casas();

	for(auto it = prueba.begin() ; it != prueba.end();it++ ){
	    if(c.count(it.operator*())==1){
	        c.erase(it.operator*());
	    }
	}

	return c;

}



Nat aed2_SimCity::nivel(Casilla c) const {
    if (this->casas().count(c) == 1) {
        Casas casasActuales = unirCasasPriorizandoMaximoNivel();
        return casasActuales[c];
    } else {
        	Comercios comerciosActuales = unirComerciosPriozandoMaximoNivel();
            Nat maximo = 0;
            auto casasYcomerciosRecientesDeOtrosSC = this->_casasYcomerciosRecientesDeOtrosSC;
            for (auto it = casasYcomerciosRecientesDeOtrosSC.begin(); it != casasYcomerciosRecientesDeOtrosSC.end() ; it++){
                if (get<0>(it.operator*()).count(c)==1){
                    if (darNivelAComercio(c) > maximo){
                        maximo = darNivelAComercio(c);
                    }

                }

            }
            if(_comerciosRecientes.count(c)==1 && comerciosActuales.count(c)==1){
            return max(max(darNivelAComercio(c),comerciosActuales[c]),maximo);
            }
            else {
                if(_comerciosRecientes.count(c)==1 && comerciosActuales.count(c)!=1){
                return max(darNivelAComercio(c),maximo);
                } else{
                    return max(comerciosActuales[c],maximo);
                }
            }

        }

}


bool  aed2_SimCity::huboConstruccion() const
{
	return this->_huboConstruccion;

}


Nat aed2_SimCity::popularidad() const
{
	return this->_popularidad;

}

Nat aed2_SimCity::antiguedad() const
{
	return this->_turno;
}

//Funciones Auxiliares

map<Casilla, Nat> aed2_SimCity::unirCasasPriorizandoMaximoNivel() const{
    Casas res = this->_casas;
    for(auto itCasDeOtrosSC = this->_casasYcomerciosRecientesDeOtrosSC.begin();itCasDeOtrosSC != this->_casasYcomerciosRecientesDeOtrosSC.end(); itCasDeOtrosSC++){
         res = Union(unirCasas(res,(itCasDeOtrosSC.operator*().second)),unirCasas((itCasDeOtrosSC.operator*().second),res));
    }
    return res;
}

Comercios aed2_SimCity::unirComerciosPriozandoMaximoNivel() const
{
	auto comerciosActuales  = this->_comercios;
	for (auto itCoDeOtrosSC = this->_comerciosDeOtrosSC.begin(); itCoDeOtrosSC != this->_comerciosDeOtrosSC.end() ; itCoDeOtrosSC++)
	{
		comerciosActuales = Union(unirComercios(comerciosActuales,itCoDeOtrosSC.operator*()),unirComercios(itCoDeOtrosSC.operator*(),comerciosActuales));

	}
	return comerciosActuales;

}


set<Casilla> aed2_SimCity::Union(set<Casilla> c1, set<Casilla> c2) const{
    for(auto it = c2.begin(); it != c2.end(); it++){
        c1.insert(it.operator*());
    }
    return c1;
}

map<Casilla,Nat> aed2_SimCity::Union(map<Casilla, Nat> d1, map<Casilla, Nat> d2) const{
    for(auto it = d2.begin(); it != d2.end(); it++){
        d1.insert(make_pair(it.operator*().first, d2[it.operator*().first]));
    }
    return d1;
}



map<Casilla,Nat> aed2_SimCity::unirCasas(map<Casilla, Nat> d1, map<Casilla, Nat> d2) const{
    set<Casilla> keysd1 = claves(d1);
    for(auto it = keysd1.begin(); it != keysd1.end(); it++){
        if(d2.count(it.operator*()) == 0 || (d2.count(it.operator*())==1 && d1[it.operator*()] >= d2[it.operator*()])){
            true;
        }else{
            d1.erase(it.operator*());
        }
    }
    return d1;
}



Comercios aed2_SimCity::unirComercios(Comercios c1,Comercios c2) const{
	/*Genero las claves de c2*/
	set<Casilla> clavesC1 = claves(c1);

    /*Recorro las claves de c2 para agregarlas a c1*/
    for(auto it = clavesC1.begin(); it != clavesC1.end(); it++){
        if(c2.count(it.operator*()) == 0 || ( c2.count(it.operator*()) == 1 && c1[it.operator*()] >= c2[it.operator*()]))
        {
            true;
        }
        else
        {
            c1.erase(it.operator*());
        }
    }
    return c1;

}

Nat aed2_SimCity::darNivelAComercio( Casilla c) const{
    if(!(casasAdistancia_3Manhattan(this->casas(),c).empty())){
        Nat prueba = maxNivelManhattan(c,this->unirCasasPriorizandoMaximoNivel());
        return prueba;
    }
    return 0;
}

Nat aed2_SimCity::maxNivelManhattan(Casilla c,Casas c1) const
{
	Nat nivel = 0;
	set<Casilla> casasAdis_3 = casasAdistancia_3Manhattan(claves(c1),c);
	for (auto it = casasAdis_3.begin(); it != casasAdis_3.end(); it++)
	{
		nivel = max(nivel,c1[it.operator*()]);
	}
	return nivel;
}

set<Casilla> aed2_SimCity::casasAdistancia_3Manhattan(set<Casilla> s,Casilla c) const
{
	set<Casilla> casasAdis_3;
    for(auto it = s.begin(); it != s.end(); it++){
        if(distanciaManhattan(it.operator*(),c) <= 3){
            casasAdis_3.insert(it.operator*());
        }
    }
	return casasAdis_3;
}



set<Casilla> aed2_SimCity::claves(map<Casilla, Nat> m) const {
    set<Casilla> res;
    for(auto it = m.begin(); it != m.end(); it++){
        res.insert(it.operator*().first);
    }
    return res;
}

Nat aed2_SimCity::distanciaManhattan(Casilla x, Casilla y) const {
    return (abs(x.first - y.first) + abs(x.second - y.second));
}


set<map<Casilla,Nat>> aed2_SimCity::Union(set<map<Casilla, Nat>> s1, set<map<Casilla, Nat>> s2){
    for(auto it = s2.begin(); it != s2.end(); it++){
        s1.insert(it.operator*());
    }
    return s1;
}

set<Mapa> aed2_SimCity::unionDeOtrosMapas(set<Mapa> s1, set<Mapa> s2){
    for(auto it = s2.begin(); it != s2.end(); it++){
        s1.insert(it.operator*());
    }
    return s1;
}
set<pair<set<Casilla>, Comercios>> aed2_SimCity::Union(set<pair<set<Casilla>, Comercios>> s1,
                                                       set<pair<set<Casilla>, Comercios>> s2) const {
    for(auto it = s2.begin(); it != s2.end(); it++){
        s1.insert(it.operator*());
    }
    return s1;
}


Nat aed2_SimCity::turno() const {
    return this->_turno;
}



Casas aed2_SimCity::casasU() const {
    return this->_casas;
}

Comercios aed2_SimCity::comerciosU() const{
    return _comercios;
}
set<Casilla> aed2_SimCity::comerciosRecientesU() const{
    return _comerciosRecientes;
}
set<Comercios> aed2_SimCity::comerciosDeOtrosSCU() const{
    return _comerciosDeOtrosSC;
}
set<pair<set<Casilla>, Comercios>> aed2_SimCity::casasYcomerciosRecientesDeOtrosSCU() const{
    return _casasYcomerciosRecientesDeOtrosSC;
}
set<Mapa> aed2_SimCity::mapasRecientesDeOtrosSCU() const{
    return _mapasRecientesDeOtrosSC;
}

