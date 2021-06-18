#include "aed2_Mapa.h"

aed2_Mapa::aed2_Mapa(){}

aed2_Mapa::aed2_Mapa(set<Casilla>h, set<Casilla>v): _horizontales(h), _verticales(v){
    _horizontales = h;
    _verticales = v;

}

void aed2_Mapa::agregarRio(Direccion d, int p){
    if(d == Horizontal){
        Casilla  c = make_pair(0,p);
        this->_horizontales.insert(c);
    } else{
        Casilla c = make_pair(p,0);
        this->_verticales.insert(c);
    }
}

bool aed2_Mapa::hayRio(Casilla c) const{
    auto hor = _horizontales;
    for(auto it = hor.begin(); it != hor.end(); it++){
        if(c.second == it.operator*().second){
            return true;
        }
    }
    auto ver = _verticales;
    for(auto it = ver.begin(); it != ver.end(); it++){
        if(c.first == it.operator*().first){
            return true;
        }
    }
    return false;
}

void aed2_Mapa::unirMapa(aed2_Mapa m2){
    auto hor = m2._horizontales;
    auto ver = m2._verticales;
    for(auto it = hor.begin(); it != hor.end(); it++){
        _horizontales.insert(it.operator*());
    }
    for(auto it = ver.begin(); it != ver.end(); it++){
        _verticales.insert(it.operator*());
    }
}

//No estoy seguo de las sgts funciones

Mapa aed2_Mapa::mapa(){
    Mapa m = make_tuple(this->_horizontales,this->_verticales);
    return m;
}


aed2_Mapa::aed2_Mapa(Mapa m){
    this->_horizontales = get<0>(m);
    this->_verticales = get<1>(m);
}