#include "Listas.hpp"

//Imprime una casilla
std::ostream& operator<<(std::ostream &os, const Casilla& c)
{
    return os<<'{'<<c.get_x()<<','<<c.get_y()<<'}';
}

//Funciones auxiliares

//Comprueba si un camino dado es v�lido
bool valido(const Lista<Casilla>& lc)
{
    if (lc.get_const().size()<2)
        return true;//Los caminos de 0 o 1 casillas son v�lidos siempre (no hay saltos posibles)
    //Obten el primer y segundo elementos
    const Casilla c1=lc.head();
    const Casilla c2=lc.tail().head();
    return c1.salto(c2)&&valido(lc.tail());//Comprueba si existe un salto y se puede continuar el camino
}

//Dada la posici�n de un caballo (primer elemento del array, y un n�mero de casillas, comprueba todas las combinaciones de saltos posibles)
Lista<Lista<Casilla>> caballos(const Lista<Casilla> &lc)
{
    Lista<Casilla> head(std::move(lc.head_list()));//Posici�n del caballo
    Lista<Lista<Casilla>> rv;//Valor de retorno

    const auto& caminos=lc.tail().permutar();//Obt�n todos los posibles caminos

    for (const Lista<Casilla>& l : caminos.get_const())//Todos los posibles caminos
    {
        if (valido(head+l))//Si el camino es v�lido
            rv.get().push_back(head+l);//A��delo
    }

    return rv;
}
