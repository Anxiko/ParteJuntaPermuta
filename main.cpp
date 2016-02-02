#include <iostream>
#include <limits>

#include "Listas.hpp"

Casilla lee_casilla (std::istream& in,std::ostream& out);

int main()
{
    std::cout<<"Introduzca la casilla inicial\n";
    Casilla inicial=lee_casilla(std::cin,std::cout);
    std::cout<<"\nIntroduzca el tablero casilla a casilla, introduzca la inicial para finalizar\n";
    Lista<Casilla>tablero;
    while (true)
    {
        Casilla casilla=lee_casilla(std::cin,std::cout);
        if (casilla==inicial)
            break;
        else
            tablero.get().push_back(casilla);
    }

    std::cout<<"\nCaminos posibles\n"<<caballos(Lista<Casilla>({inicial})+tablero)<<'\n';

    return 0;
}

Casilla lee_casilla (std::istream& in,std::ostream& out)
{
    static int casillas=0;
    int valores=0;
    int x,y,buff;
    while(true)
    {
        out<<casillas<<" : ";
        bool read=true;
        while(read&&in>>buff)
        {
            switch(++valores)
            {
                case 1:
                    x=buff;
                    break;
                case 2:
                    y=buff;
                    read=false;
                    break;
            }
        }

        if (read)
        {
            out<<"ERROR, Introduzca otra vez\n";
            valores=0;
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            ++casillas;
            return Casilla(x,y);
        }
    }
}
