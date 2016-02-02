#include <iostream>
#include <sstream>
#include <limits>

#include "Listas.hpp"

bool lee_casilla (Casilla &c);
void limpia_teclado();

int main()
{
    Casilla input;//Entrada de teclado
    Casilla entrada;
    Lista<Casilla> tablero;

    for (;;)
    {
        //Leer la primera posición
        std::cout<<"Introduzca la casilla del caballo\n";
        for (;;)
        {
            std::cout<<"\nEntrada: ";
            if (lee_casilla(input))
            {
                //Problema al leer
                std::cout<<"\nERROR al leer la entrada inicial, ¿reintentar[S/N]?: ";
                char rein;
                std::cin>>rein;
                if(rein=='n'||rein=='N')
                    return 0;
            }
            else
            {
                //Se leyo la entrada
                entrada=input;
                break;
            }
        }

        //Leer las casillas del tablero
        int val=1;
        std::cout<<"\nIntroduzca las casillas del teclado, enter para salir\n";
        for(;;)
        {
            std::cout<<'['<<val<<']'<<">: ";
            //Leer una posición
            if (lee_casilla(input))
            {
                //Problema al leer
                std::cout<<"\nERROR al leer la casilla, ¿procesar los datos?[S/N]?: ";
                char rein;
                std::cin>>rein;
                if(!(rein=='n'||rein=='N'))
                    break;
            }
            else
            {
                //Se leyo la entrada
                tablero.get().push_back(input);
                ++val;
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

bool lee_casilla (Casilla &c)
{
    int x,y;//Posiciones a leer
    std::string cadena_entrada;
    std::getline(std::cin,cadena_entrada);
    if (cadena_entrada.empty())
        return false;
    std::istringstream stream_entrada(cadena_entrada);
    if (stream_entrada>>x>>y)//Intenta leer y comprueba si se produjo algún error
    {
        //No hubo error
        c.set_x(x);
        c.set_y(y);
        return false;
    }
    else
        return true;
}
