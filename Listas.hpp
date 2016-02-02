#ifndef _LISTAS_
#define _LISTAS_

#include <vector>//Vectores

#include <ostream>//Streams de salida

#include <cstdlib>//abs

#include <iostream>//Salida a pantalla

template<typename T>
class Lista//Lista de elementos de tipo T
{
    //Atributos
    private:

        //Lista de elementos
        std::vector<T> lista;

    //Constructor
    public:

        Lista() = default;

        Lista(const std::vector<T> nlista)
        :lista(nlista)
        {}

    //Get/Set
    public:

        const std::vector<T>& get_const() const
        {
            return lista;
        }

        std::vector<T>& get()
        {
            return lista;
        }

        void set(const std::vector<T>& nlista)
        {
            lista=nlista;
        }

        Lista<T>& operator= (const Lista&) = default;

    //Métodos
    public:

        //Parte esta lista de todas las formas posibles
        Lista<Lista<T>> partir() const
        {
            Lista<Lista<T>> rv;//Valor de retorno

            for (unsigned int i=0; i<=lista.size();++i)//Recorre los elementos del vector
            {
                Lista<T>principio,fin;//Partición de esta lista
                for (unsigned int i1=0;i1<i;++i1)
                    principio.lista.push_back(lista[i1]);
                for (unsigned int i2=i;i2<lista.size();++i2)
                    fin.lista.push_back(lista[i2]);
                rv.get().push_back(principio);
                rv.get().push_back(fin);
            }

            return rv;
        }

        //Concatena dos listas y las devuelve en una nueva
        Lista<T> operator+(Lista<T> nl) const
        {
            Lista<T> rv(*this);//Valor de retorno
            for (const T& t : nl.get_const())
                rv.get().push_back(t);
            return rv;
        }

        //Acceso
        const T& operator[] (int n) const
        {
            return lista[n];
        }

        T& operator[] (int n)
        {
            return lista[n];
        }

        const T& head() const
        {
            return lista[0];
        }

        Lista<T> tail() const
        {
            Lista<T> rv;
            for (unsigned int i=1;i<lista.size();++i)
                rv.get().push_back(lista[i]);

            return rv;
        }

        //Permutar
        Lista<Lista<T>> permutar() const
        {
            if (lista.empty())
                return Lista<Lista<T>>({Lista<T>()});

            Lista<Lista<T>> rv;//Valor de retorno
            Lista<Lista<T>> cola_permutada(tail().permutar());//Obtiene una lista con las permutaciones de la cola
            for (const Lista<T>& permutacion_cola : cola_permutada.get_const())//Para cada permutación de la cola
            {
                Lista<Lista<T>> particion(permutacion_cola.partir());//Obtén su partición
                for (unsigned int i=0;i+1<particion.get_const().size();i+=2)//Para cada partición, inserta la cabeza en medio y añadela a las soluciones
                    rv.get().push_back(particion[i]+Lista<T>({head()})+particion[i+1]);
            }

            return rv;
        }
};

class Casilla
{
    //Atributos
    private:

        int x,y;

    //Constructores
    public:

        Casilla() = default;

        Casilla(int ix,int iy)
        :x(ix),y(iy)
        {}

        Casilla(const Casilla&) = default;

        Casilla& operator= (const Casilla&) = default;

    //Métodos
    public:

        //Verifica si el salto entre dos casilla es válido
        bool salto(const Casilla& nc) const
        {
            unsigned int diff_x=std::abs(x-nc.x),diff_y=std::abs(y-nc.y);
            return (diff_x==2&&diff_y==1)||(diff_x==1&&diff_y==2);
        }

        //Get

        int get_x() const
        {
            return x;
        }

        int get_y() const
        {
            return y;
        }

        //Igualdad/desigualdad

        bool operator==(const Casilla& c)
        {
            return x==c.x&&y==c.y;
        }

        bool operator!=(const Casilla &c)
        {
            return !(operator==(c));
        }
};

//Imprime la lista
template<typename T>
std::ostream& operator<<(std::ostream &os, const Lista<T>& l)
{
    os<<'[';
    bool coma=false;
    for (const T& t : l.get_const())
    {
        if (coma)
            os<<',';
        else
            coma=true;
        os<<t;
    }
    os<<']';
    return os;
}

//Imprime una casilla
std::ostream& operator<<(std::ostream &os, const Casilla& c);

//Funciones auxiliares

//Comprueba si un camino válido es dado
bool valido(const Lista<Casilla>& lc);

//Dada la posición de un caballo (primer elemento del array, y un número de casillas, comprueba todas las combinaciones de saltos posibles)
Lista<Lista<Casilla>> caballos(const Lista<Casilla> &lc);

#endif // _LISTAS_
