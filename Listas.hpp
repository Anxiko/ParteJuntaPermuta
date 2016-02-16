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

        Lista() = default;//Defecto

        //Vector

        Lista(const std::vector<T>& nvect)//Copia
        :lista(nvect)
        {}

        Lista(std::vector<T>&& nvect)//Mover
        :lista(nvect)
        {}

        //Lista

        Lista(const Lista<T>& nlista)//Copia
        :lista(nlista.lista)
        {}

        Lista(Lista<T>&& nlista)//Mover
        :lista(nlista.lista)
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

        void set(std::vector<T>&& nlista)
        {
            lista.swap(nlista);
        }

        Lista<T>& operator= (const Lista<T>&) = default;

        Lista<T>& operator= (Lista<T> &&nlista)
        {
            lista.swap(nlista);
        }

    //M�todos
    public:

        //Parte esta lista de todas las formas posibles
        Lista<Lista<T>> partir() const
        {
            Lista<Lista<T>> rv;//Valor de retorno

            for (unsigned int i=0; i<=lista.size();++i)//Recorre los elementos del vector
            {
                Lista<T>principio(std::vector<T>(lista.begin(),lista.begin()+i)),
                fin(std::vector<T>(lista.begin()+i,lista.end()));//Partici�n de esta lista
                rv.get().push_back(principio);
                rv.get().push_back(fin);
            }

            return rv;
        }

        //Concatena dos listas y las devuelve en una nueva
        Lista<T> operator+(Lista<T> nl) const
        {
            Lista<T> rv(*this);//Valor de retorno
            rv.get().insert(rv.get().end(),std::make_move_iterator(nl.get().begin()),std::make_move_iterator(nl.get().end()));
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

        Lista<T> head_list() const
        {
            return Lista<T>({head()});
        }

        Lista<T> tail() const
        {
            return Lista<T>(std::vector<T>(lista.begin()+1,lista.end()));
        }

        //Permutar
        Lista<Lista<T>> permutar() const
        {
            if (lista.empty())
                return Lista<Lista<T>>({Lista<T>()});

            Lista<Lista<T>> rv;//Valor de retorno
            Lista<Lista<T>> cola_permutada(std::move(tail().permutar()));//Obtiene una lista con las permutaciones de la cola
            for (const Lista<T>& permutacion_cola : cola_permutada.get_const())//Para cada permutaci�n de la cola
            {
                Lista<Lista<T>> particion(std::move(permutacion_cola.partir()));//Obt�n su partici�n
                Lista<T> cabeza(std::move(head_list()));//Cebeza de esta lista
                for (unsigned int i=0;i+1<particion.get_const().size();i+=2)//Para cada partici�n, inserta la cabeza en medio y a�adela a las soluciones
                    rv.get().push_back(particion[i]+cabeza+particion[i+1]);
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

    //M�todos
    public:

        //Verifica si el salto entre dos casilla es v�lido
        bool salto(const Casilla& nc) const
        {
            unsigned int diff_x=std::abs(x-nc.x),diff_y=std::abs(y-nc.y);
            return (diff_x==2&&diff_y==1)||(diff_x==1&&diff_y==2);
        }

        //Get/set

        int get_x() const
        {
            return x;
        }

        int get_y() const
        {
            return y;
        }

        void set_x(int nx)
        {
            x=nx;
        }

        void set_y(int ny)
        {
            y=ny;
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

//Comprueba si un camino v�lido es dado
bool valido(const Lista<Casilla>& lc);

//Dada la posici�n de un caballo (primer elemento del array, y un n�mero de casillas, comprueba todas las combinaciones de saltos posibles)
Lista<Lista<Casilla>> caballos(const Lista<Casilla> &lc);

#endif // _LISTAS_
