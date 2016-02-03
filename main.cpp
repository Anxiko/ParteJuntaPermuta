#include <iostream>
#include <sstream>
#include <limits>

#include "Listas.hpp"

int lee_casilla (Casilla &c);
void limpia_teclado();

enum Salida : int
{
    LEIDO=0,
    BLANCO,
    ERROR
};

int main()
{
    Casilla input;//Entrada de teclado
    Casilla entrada;
    Lista<Casilla> tablero;

    for (;;)
    {
        //Leer la primera posición
        bool leyendo=true;
        std::cout<<"Introduzca la casilla del caballo, ENTER para finalizar el programa\n";
        while (leyendo)
        {
            std::cout<<"\nEntrada: ";
            switch (lee_casilla(input))
            {
                case LEIDO:
                {
                    entrada=input;
                    leyendo=false;
                    break;
                }

                case BLANCO:
                {
                    std::cout<<"Fin del programa\n";
                    return 0;
                }

                case ERROR:
                {
                    //Problema al leer
                    std::cout<<"\nERROR al leer la entrada inicial\n";
                    break;
                }

                default:
                    break;
            }
        }

        //Leer las casillas del tablero
        int val=1;
        leyendo=true;
        std::cout<<"\nIntroduzca las casillas del tablero, ENTER para finalizar\n";
        while(leyendo)
        {
            std::cout<<'['<<val<<']'<<">: ";
            //Leer una posición
            switch(lee_casilla(input))
            {
                case LEIDO:
                {
                    tablero.get().push_back(input);
                    ++val;
                    break;
                }

                case BLANCO:
                {
                    leyendo=false;
                    break;
                }

                case ERROR:
                {
                    //Problema al leer
                    std::cout<<"\nERROR al leer la casilla\n";
                    break;
                }

                default:
                    break;
            }
        }

        std::cout<<"\nDatos\n";
        std::cout<<"Caballo: "<<entrada<<'\n';
        std::cout<<"Tablero: \n"<<tablero<<'\n';
        std::cout<<"Salida:\n";
        std::cout<<caballos(Lista<Casilla>({entrada})+tablero)<<"\n";
    }

    return 0;
}

void limpia_teclado()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int lee_casilla (Casilla &c)
{
    int x,y;//Posiciones a leer
    std::string cadena_entrada;
    std::getline(std::cin,cadena_entrada);
    if (cadena_entrada.empty())
        return BLANCO;
    std::istringstream stream_entrada(cadena_entrada);
    if (stream_entrada>>x>>y)//Intenta leer y comprueba si se produjo algún error
    {
        //No hubo error
        c.set_x(x);
        c.set_y(y);
        return LEIDO;
    }
    else
        return ERROR;
}
