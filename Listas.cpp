#include "Listas.hpp"

//Imprime una casilla
std::ostream& operator<<(std::ostream &os, const Casilla& c)
{
    return os<<'{'<<c.get_x()<<','<<c.get_y()<<'}';
}

//Funciones auxiliares

//Comprueba si un camino válido es dado
bool valido(const Lista<Casilla>& lc)
{
    if (lc.get_const().size()<2)
        return true;//Los caminos de 0 o 1 casillas son válidos siempre (no hay saltos posibles)
    //Obten el primer y segundo elementos
    const Casilla c1=lc.head();
    const Casilla c2=lc.tail().head();
    return c1.salto(c2)&&valido(lc.tail());//Comprueba si existe un salto y se puede continuar el camino
}

//Dada la posición de un caballo (primer elemento del array, y un número de casillas, comprueba todas las combinaciones de saltos posibles)
Lista<Lista<Casilla>> caballos(const Lista<Casilla> &lc)
{
    Lista<Casilla> head; head.get().push_back(lc.head());//Obtén la posición del caballo
    Lista<Lista<Casilla>> rv;//Valor de retorno
    for (const Lista<Casilla>& l : lc.tail().permutar().get_const())//Todos los posibles caminos
    {
        if (valido(head+l))//Si el camino es válido
            rv.get().push_back(head+l);//Añádelo
    }

    return rv;
}
