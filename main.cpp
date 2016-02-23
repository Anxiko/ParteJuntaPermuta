#include <iostream>
#include <sstream>
#include <limits>

#include "Listas.hpp"

int lee_casilla (Casilla &c);//Lee una casilla del teclado
int lee_entero(int &i);//Lee un entero del teclado
void opc_caballos();//Problema del caballo
void opc_juntar();//Junta un par de listas
void opc_partir();//Calcula todas las posibles particiones de la lista en dos
void opc_permutar();//Calcula las permutaciones de una lista

enum Salida : int
{
    LEIDO=0,
    BLANCO,
    ERROR
};

int main()
{
    int opc;//Opción escogida en el menú

    while(true)
    {
        std::cout<<"\n\nOpciones\n\n";
        std::cout<<"1\tJuntar\n";
        std::cout<<"2\tPartir\n";
        std::cout<<"3\tPermutar\n";
        std::cout<<"4\tCaballos\n";
        std::cout<<"5\tSalir\n";
        std::cout<<"Opc: ";

        switch(lee_entero(opc))
        {
            case LEIDO:
            {
                switch (opc)
                {
                    case 1:
                    {
                        opc_juntar();
                        break;
                    }

                    case 2:
                    {
                        opc_partir();
                        break;
                    }

                    case 3:
                    {
                        opc_permutar();
                        break;
                    }

                    case 4:
                    {
                        opc_caballos();
                        break;
                    }

                    case 5:
                    {
                        std::cout<<"Fin del programa\n";
                        return 0;
                    }

                    default:
                    {
                        std::cout<<"ERROR: valor no reconocido\n";
                    }
                }

                break;
            }
            case BLANCO:
            case ERROR:
            {
                std::cout<<"ERROR: al leer el valor\n";
                break;
            }
        }
    }

    return 0;
}

void opc_juntar()
{
    Lista<int> listas[2];
    std::cout<<"Introduzca dos listas para juntarlas\n";
    std::cout<<"Introduzca enteros de 1 en 1, ENTER para terminar la lista\n";

    for (int cnt=0;cnt<2;++cnt)
    {
        std::cout<<"Lista "<<(cnt+1)<<'\n';
        int n_leidos=0;//Cantidad de números leidos
        bool leyendo=true;
        int i;//Entero leido
        while(leyendo)
        {
            std::cout<<'['<<(n_leidos+1)<<"]>";
            switch(lee_entero(i))
            {
                case LEIDO:
                {
                    ++n_leidos;
                    listas[cnt].get().push_back(i);
                    break;
                }

                case BLANCO:
                {
                    std::cout<<"Leidos "<<n_leidos<<" en lista "<<(cnt+1)<<'\n';
                    leyendo=false;
                    break;
                }
                case ERROR:
                {
                    std::cout<<"ERROR al leer el entero\n";
                    break;
                }
            }
        }
    }

    std::cout<<"Listas unidas:\n"<<(listas[0]+listas[1])<<'\n';
}

void opc_partir()
{
    Lista<int> lista;
    std::cout<<"Introduzca una lista para partirla\n";
    std::cout<<"Introduzca enteros de 1 en 1, ENTER para terminar la lista\n";

    int n_leidos=0;//Cantidad de números leidos
    bool leyendo=true;
    int i;//Entero leido
    while(leyendo)
    {
        std::cout<<'['<<(n_leidos+1)<<"]>";
        switch(lee_entero(i))
        {
            case LEIDO:
            {
                ++n_leidos;
                lista.get().push_back(i);
                break;
            }

            case BLANCO:
            {
                std::cout<<"Leidos "<<n_leidos<<'\n';
                leyendo=false;
                break;
            }
            case ERROR:
            {
                std::cout<<"ERROR al leer el entero\n";
                break;
            }
        }
    }

    std::cout<<"Particiones de la lista:\n";
    const Lista<Lista<int>> part(std::move(lista.partir()));
    for (unsigned int cnt=0;cnt<part.get_const().size()-1;cnt+=2)
    {
        std::cout<<'['<<((cnt/2)+1)<<"] "<<part[cnt]<<" + "<<part[cnt+1]<<'\n';
    }
}

void opc_permutar()
{
    Lista<int> lista;
    std::cout<<"Introduzca una lista para permutarla\n";
    std::cout<<"Introduzca enteros de 1 en 1, ENTER para terminar la lista\n";

    int n_leidos=0;//Cantidad de números leidos
    bool leyendo=true;
    int i;//Entero leido
    while(leyendo)
    {
        std::cout<<'['<<(n_leidos+1)<<"]>";
        switch(lee_entero(i))
        {
            case LEIDO:
            {
                ++n_leidos;
                lista.get().push_back(i);
                break;
            }

            case BLANCO:
            {
                std::cout<<"Leidos "<<n_leidos<<'\n';
                leyendo=false;
                break;
            }
            case ERROR:
            {
                std::cout<<"ERROR al leer el entero\n";
                break;
            }
        }
    }

    std::cout<<"Permutaciones de la lista:\n"<<lista.permutar()<<'\n';
}

void opc_caballos()
{
    Casilla input;//Entrada de teclado
    Casilla entrada;
    Lista<Casilla> tablero;

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
                return;
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

int lee_entero(int &i)
{
    int x;//Entero a leer
    std::string cadena_entrada;
    std::getline(std::cin,cadena_entrada);
    if (cadena_entrada.empty())
        return BLANCO;
    std::istringstream stream_entrada(cadena_entrada);
    if (stream_entrada>>x)//Intenta leer y comprueba si se produjo algún error
    {
        //No hubo error
        i=x;
        return LEIDO;
    }
    else
        return ERROR;
}
