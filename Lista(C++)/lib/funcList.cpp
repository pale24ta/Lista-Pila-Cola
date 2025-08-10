#include<iostream>
#include "funcList.hpp"

int longestZigZagSublist(Lista<int> target)
{
    int acumulador = 0;
    int acum_anterior = 0;
    int zigzag = 0;
    int anterior = 0;
    int dato;

    while(!target.esVacia())
    {
        dato = target.consultar(1);

        if(dato > anterior && zigzag != 1){
            acumulador += 1;
            zigzag = 1;
        }
        else
        if(dato < anterior && zigzag != -1){
            acumulador +=1;
            zigzag = -1;
        }else{
            if(acumulador > acum_anterior){
                acum_anterior = acumulador;
            }
            zigzag = 0;
        }

        anterior = dato;
        target.remover(1);
    }
    return acum_anterior;
}

Lista<int> trendChangesInWindows(Lista<int> target, int k)
{
    Lista<bool> cambios;
    Lista<int> frecuencias;
    Cola<int> ventana;
    int acum = 0;
    int anterior;

    while(!target.esVacia()){

        anterior = target.consultar(1);
        ventana.encolar(anterior);
        target.remover(1);

        if(ventana.getLength() >= k){
            frecuencias.insertar(acum,frecuencias.getLength() + 1);
            acum -=1;
            ventana.desencolar();
        }

        if(!target.esVacia()){
            if(anterior > target.consultar(1)){
                cambios.insertar(false,cambios.getLength()+1);
            }else if(anterior < target.consultar(1)){
                cambios.insertar(true,cambios.getLength()+1);
            }
        }

        if(cambios.getLength() > 1){
            if(cambios.consultar(1) != cambios.consultar(2)){
                acum += 1;
            }
            cambios.remover(1);
        }
    }

    return frecuencias;
}

