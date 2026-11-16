#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

typedef char str6 [6+1];
typedef char str50 [50+1];

struct tRegJugadores {
    long int DNI;
    str50 nombre;
    str50 apellido;
    int categoria; //seria el año de nacimiento 
    str6 codigoClub;
};

struct pNodoJugadores { 
    tRegJugadores informacion;
    pNodoJugadores * sgte;
};

struct tRegClubes {
    str6 codigoClub;
    str50 nombreEquipo;
    int cat1,cat2,cat3;

    int contadorCat1;
    int contadorCat2;
    int contadorCat3;

};

struct pNodoClubes {
    tRegClubes informacion;
    pNodoClubes * sgte; //despues fijate si la uso
    
    pNodoJugadores * pPrimerElementoCat1; //al primer elemento de la 1er categoria
    pNodoJugadores * pPrimerElementoCat2;
    pNodoJugadores * pPrimerElementoCat3;

};


void cargarClubes(char * arch, pNodoClubes *&ListaClubes);
void cargarJugadores (char * arch, pNodoClubes *&ListaClubes);
pNodoClubes * insertarClubes(pNodoClubes *&ListaClubes,tRegClubes informacion );
pNodoJugadores * insertarJugadores(pNodoJugadores *&ListaJugadores,tRegJugadores informacion);
pNodoClubes * buscarClub (pNodoClubes * ListaClubes, str6 codigoClub);
void mostrarP4(pNodoClubes * ListaClubes);
void mostrarP5 (pNodoClubes * ListaClubes);
void liberarMemoria(pNodoClubes * ListaClubes);


int main() {
pNodoClubes * ListaClubes=NULL;
cargarClubes("clubes.txt", ListaClubes);
cargarJugadores("jugadores.txt", ListaClubes);
mostrarP4(ListaClubes);
mostrarP5(ListaClubes);
liberarMemoria(ListaClubes);
}


void cargarClubes(char * arch, pNodoClubes *&ListaClubes) {
    tRegClubes club;

    FILE * fClubes = fopen(arch, "rb");
    fread(&club,sizeof(club),1,fClubes);
    while(!feof(fClubes)) {
        insertarClubes(ListaClubes, club);
        fread(&club,sizeof(club),1,fClubes);
    }
    fclose(fClubes);
}

void cargarJugadores(char * arch, pNodoClubes *&ListaClubes) {
    tRegJugadores jug;
    pNodoClubes * p;
    FILE * fJugadores = fopen(arch, "rb");

    fread(&jug,sizeof(jug),1,fJugadores);
    while(!feof(fJugadores)) {
        p=buscarClub(ListaClubes, jug.codigoClub);
        if (p!=NULL) {
            if (p->informacion.cat1==jug.categoria)
            {
                insertarJugadores(p->pPrimerElementoCat1,jug);
                p->informacion.contadorCat1++;
            }
            if (p->informacion.cat2==jug.categoria)
            {
                insertarJugadores(p->pPrimerElementoCat2,jug);
                p->informacion.contadorCat2++;
            }
            if (p->informacion.cat3==jug.categoria)
            {
                insertarJugadores(p->pPrimerElementoCat3,jug);
                p->informacion.contadorCat3++;
            }
            
        } else {
            cout<<"No existe equipo"<<endl;
        }
        fread(&jug,sizeof(jug),1,fJugadores);

    }
    fclose(fJugadores);
}

void mostrarP4(pNodoClubes * ListaClubes) {

    pNodoClubes * p = ListaClubes;
    
    while (p!=NULL) 
    {
        pNodoJugadores * q = p->pPrimerElementoCat1; //para mostrar todos los jugadores
        pNodoJugadores * q2= p->pPrimerElementoCat2;
        pNodoJugadores * q3 =p->pPrimerElementoCat3;
        cout<<"Club: "<<p->informacion.nombreEquipo<<endl;
        cout<<"Categoria "<<p->informacion.cat1<<endl;
        while(q!=NULL) {
        cout<<"Nombre de los jugadores de la categoria 1: "<<q->informacion.nombre<<endl;
        cout<<"Apellido de los jugadores de la categoria 1: "<<q->informacion.apellido<<endl;
        q=q->sgte; 
        }
        cout<<"Categoria "<<p->informacion.cat2<<endl;
        while(q2!=NULL) {
        
        cout<<"Nombre de los jugadores de la categoria 2: "<<q2->informacion.nombre<<endl;
        cout<<"Apellido de los jugadores de la categoria 2: "<<q2->informacion.apellido<<endl;
        q2=q2->sgte;
        }
        cout<<"Categoria "<<p->informacion.cat3<<endl;
        while(q3!=NULL) {

        cout<<"Nombre de los jugadores de la categoria 3: "<<q3->informacion.nombre<<endl;
        cout<<"Apellido de los jugadores de la categoria 3: "<<q3->informacion.apellido<<endl;
        q3=q3->sgte;
        }
        cout<<"Contador de jugadores en la categoria 1: "<<p->informacion.contadorCat1<<endl;
        cout<<"Contador de jugadores en la categoria 2: "<<p->informacion.contadorCat2<<endl;
        cout<<"Contador de jugadores en la categoria 3: "<<p->informacion.contadorCat3<<endl;
        p=p->sgte;
    }
}

void mostrarP5 (pNodoClubes * ListaClubes) {
    pNodoClubes * p =ListaClubes;

    while(p!=NULL) {
        if (p->informacion.contadorCat1>10) 
        {
          cout<<"Equipo: "<<p->informacion.nombreEquipo<<endl;
          cout<<"Categoria 1: "<<p->informacion.cat1<<endl;
        }
        if (p->informacion.contadorCat2>10) 
        {
        cout<<"Equipo: "<<p->informacion.nombreEquipo<<endl;
        cout<<"Categoria 2: "<<p->informacion.cat2<<endl;
        }
        if (p->informacion.contadorCat3>10)
        {
        cout<<"Equipo: "<<p->informacion.nombreEquipo<<endl;
        cout<<"Categoria 3: "<<p->informacion.cat3<<endl;
        }
        p=p->sgte;
    }


}