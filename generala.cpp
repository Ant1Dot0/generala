#include "rlutil.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <cstring>

#define  msnCordy 20
#define  msnCordX 80
using namespace std;
using namespace rlutil;


void anotaPuntuacion(char vNombre[14],int puntos);
int leerPuntuacion(char vNombre[14]);
void vaciarMat(int mat[][11]);
void mostrarTablaPuntos(int vpuntos[][11],int  jugador,int categoria);
void borraTodo(int ancho, int largo, int coordX, int coordY);
void mensajeria(int mensaje);
int azar();
int sumarVec(int vec[],int tam);
void dibujarBordes(int ancho, int largo, int coordX, int coordY,int colorFondo,int color);
bool validarIngNombre(char letra);
void vaciarVec(int vec[],int tam);
void dibujarDado(int ancho, int largo,int coordX,int coordY,int valor);
void mostrarDados(int tirada[],int cant);
void mostrarDadosReserva(int reservados[],int cant);
void mostrarMenu(int x,int y); ///Muestra el menu primero
int selectOptionHori(int coordX,int coordY, int cantOpc, char sym, int despl);
int selectOptionVert(int x, int y, int cantOpc, char letra, int despl);
void dibujarMarco(int ancho, int largo,int coordX, int coordY,int color);
void contar(int tirada[], int dados[]);
bool generala(int dados[]);
bool poker(int dados[]);
bool full(int dados[]);
bool escalera(int dados[]);
int selecTurno(char nombre[][14]);
void ordenarVec(int v[]);
int asignarPuntos(int vPuntos[][11],int vDados[], int valor,int jugador, bool servida );
void letraG(int x,int y,int t, char sym);
void letraE(int x,int y,int t, char sym);
void letraN(int x,int y,int t, char sym);
void letraR(int x,int y,int t, char sym);
void letraA(int x,int y,int t, char sym);
void letraL(int x,int y,int t, char sym);
void saludo();
void ingresoNombre(char nombre[][14], int tipoJuego);
void dibujarInterfaz(char nombre[][14], char categorias[][9], int tipoJuego);
int main ()
{
    //tonos(8);
    int puntos[2][11],tirada[5],buTirada[5],reservados[5]= {0},buReservados[5],dados[6],color, acum, modo,x, opcion, a, turno,i,tiro ;
    int cantReserv,buCantReserv, cantHabi,buCantHabi, dadoSelect, v, tipoJuego,cantRondas=10,opcionesX=34;
    int finTurno=1, maxPuntuacion=0;
    int cx=23,y=6, r=10, t=30;
    float ronda=1;
    char categorias[12][9]= {"AS","DOS","TRES","CUATRO","CINCO","SEIS","ESCALERA","FULL","POKER","GENERALA","TOTAL" };
    char s=169, nombre[2][14], letra, nombreMax[14],nombreGan[14];
    hidecursor();
    srand(time(NULL));
    do
    {
        saludo();

        mostrarMenu(43,15);
        modo = selectOptionVert(42,15,4,175,1);///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        switch(modo)
        {
        case 1:
            tipoJuego=1;
            break;
        case 2:
            tipoJuego=2;
            break;
        case 3:
            system("cls");
            gotoxy(40,15);
            maxPuntuacion=leerPuntuacion(nombreMax);
            if(maxPuntuacion==0)
                cout<<"todavía falta wee";
            else
            {
                setColor(10);
                gotoxy(54,10);
                cout<<"MAXIMA PUNTUACION";
                dibujarMarco(26,2,48,14,13);

                setColor(7);
                gotoxy(50,15);
                cout<<nombreMax;
                gotoxy(68,15);
                setColor(13);
                printf("%c ",221);
                setColor(7);
                cout<<maxPuntuacion;

                msleep(2000);
            }

            anykey();
            break;
        case 4:
            system("cls");
            gotoxy (58,15);
            cout<<"GAME OVER";
            msleep(3000);
            anykey();
            return 0;

        }///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        system("cls");
    }
    while(modo != 2 && modo != 1);


    ingresoNombre(nombre, tipoJuego);

    system("cls");

    dibujarInterfaz(nombre,categorias,tipoJuego);
    vaciarMat(puntos);
    vaciarVec(tirada,5);/// MOSTRAMOS DADOS EN CERO
    mostrarDados(tirada,5);
    puntos[0][10]=0;

    if(tipoJuego==2)
    {
        opcionesX=48;
        puntos[1][10]=0;
        turno=!selecTurno(nombre);
        cantRondas=20;
    }
    else
    {
        turno=0;
        cantRondas=10;
    }
    borraTodo(35,1,msnCordX,msnCordy);

    for(ronda=1; ronda <=cantRondas; ronda++)
    {
        vaciarVec(tirada,5);
        mostrarDados(tirada,5);
        gotoxy(msnCordX,msnCordy);
        if(tipoJuego== 2)
        {
            cout<<"TURNO DE "<<nombre[!turno];
            if(turno)
            {
                dibujarMarco(14,2,32,2,7);///cuadro nombre jugador 2
                dibujarMarco(14,22,32,4,7);///cuadro puntos jugador 2
                dibujarMarco(14,2,18,2,13);///cuadro nombre jugador 1
                dibujarMarco(14,22,18,4,13);///cuadro puntos jugador1
            }
            else
            {
                dibujarMarco(14,2,18,2,7);///cuadro nombre jugador 1
                dibujarMarco(14,22,18,4,7);///cuadro puntos jugador1
                dibujarMarco(14,2,32,2,13);///cuadro nombre jugador 2
                dibujarMarco(14,22,32,4,13);///cuadro puntos jugador 2
            }
        }
        borraTodo(30,6,msnCordX,msnCordy+1);
        borraTodo(30,1,76,4);
        setColor(12);
        gotoxy(100,3);
        printf("%0.f", ronda/tipoJuego);
        setColor(7);
        if(tipoJuego==2)
            msleep(2000);

        borraTodo(14,1,79,3);
        gotoxy(79,3);
        setColor(10);
        if(tipoJuego==2)
            cout<<nombre[!turno];
        else
            cout<<nombre[turno];
        setColor(7);
        if(ronda == 1)
        {
            borraTodo(8,1,20,25);
            borraTodo(8,1,34,25);
        }

        mostrarTablaPuntos(puntos,0,10);
        if(tipoJuego == 2)
            mostrarTablaPuntos(puntos,1,10);

        borraTodo(35,1,msnCordX,msnCordy);/// limpia pantalla de mensajes



        gotoxy(80,22);
        cout<<"TIRAR DADO";
        gotoxy(109,3);
        cout<<" "; /// deja el tiro en cero
        selectOptionVert(79,22,1,175,1);

        tiro=0;
        if(tipoJuego== 2)
            turno = !turno;
        finTurno = 1;
        cantHabi=5;
        cantReserv=0;
        borraTodo(14,1,79,3);
        gotoxy(79,3);
        setColor(10);
        cout<<nombre[turno];/// muestra el nombre del turno y la ronda
        setColor(7);
        do /// --------------INICIO DE JUGADA
        {

            gotoxy(109,3);
            setColor(14);
            cout<<tiro+1;/// muestra el tiro
            setColor(7);
            if(finTurno !=0 )
            {
                for(x=0; x<cantHabi; x++)/// GENERACION DE TIRADA
                    tirada[x] = azar();
                mostrarDados(tirada,5);
            }

            vaciarVec(dados,6);
            contar(tirada,dados);
            setColor(12);
            setBackgroundColor(11);
            if(generala(dados) && puntos[turno-1][9] < 0)
            {
                setBackgroundColor(0);
                setColor(14);
                cx=22;
                y=15;
                t=30;
                letraG(cx,y,t,s);
                cx+=r;
                letraE(cx,y,t,s);
                cx+=r;
                letraN(cx,y,t,s);
                cx+=r;
                letraE(cx,y,t,s);
                cx+=r;
                letraR(cx,y,t,s);
                cx+=r;
                letraA(cx,y,t,s);
                cx+=r;
                letraL(cx,y,t,s);
                cx+=r;
                letraA(cx,y,t,s);

                Sleep(2000);
                puntos[turno][10]+=250;
                setColor(7);
                goto FinDelJuego;
            }
            else if(poker(dados))
            {
                gotoxy(80,4);
                cout << "POKER!";
            }///----------------------------------------------  MUESTRA SI HUBO ALGUNA CATEGORIA PARA ANOTAR
            else if(full(dados))
            {
                gotoxy(80,4);
                cout << "FULL";
            }
            else if(escalera(dados))
            {
                gotoxy(80,4);
                cout << "ESCALERA";
            }

            else
            {
                setColor(7);
                setBackgroundColor(0);
                gotoxy(80,4);
                cout<<"                 ";///**************************************************
            }
            setColor(7);
            setBackgroundColor(0);
            do
            {
                do
                {
                    borraTodo(30,4,80,22);///***********************************************************************************
                    gotoxy(80,22);
                    cout<<"TIRAR DADOS";
                    gotoxy(80,23);
                    cout<<"RESERVAR DADOS";///                      MENÚ DE TIRO
                    gotoxy(80,24);
                    cout<<"ANOTAR CATEGORIA";
                    gotoxy(80,25);
                    cout<<"PONER EN CERO o FINALIZAR";
                    fflush(stdin);
                    opcion= selectOptionVert(79,22,4,175,1);///**************************************************************
                    fflush(stdin);
                    mensajeria(0);
                    switch(opcion)
                    {
                    case 1:
                        if(tiro == 2 )
                        {
                            mensajeria(1);
                            opcion=5;
                        }
                        break;
                    case 2:

                        borraTodo(30,6,msnCordX,msnCordy);/// ACCIONES DE RESERVAR DADOS
                        mensajeria(2);
                        for( a=0; a<5; a++) ///******************************************************
                        {
                            buTirada[a]=tirada[a];
                            buReservados[a]=reservados[a];
                        }///                                BACK UP PARA CANCELAR
                        buCantHabi=cantHabi;
                        buCantReserv=cantReserv;///***********************************************
                        do
                        {   fflush(stdin);
                            dadoSelect=(selectOptionHori(73,6,5,190,9))-1;
                            fflush(stdin);
                            if(dadoSelect == -2) /// **********************************para cancelar
                            {
                                cantHabi=buCantHabi;///         CANCELAR RESERVA
                                cantReserv=buCantReserv;///

                                borraTodo(30,6,msnCordX,msnCordy);///borro menu
                                borraTodo(45-(cantReserv*9),5,69+(cantReserv*9),14);///borro dados reservados recientemente
                                for( a=0; a<5; a++)
                                {
                                    tirada[a]=buTirada[a];
                                    reservados[a]=buReservados[a];
                                }
                                mostrarDados(tirada,5);

                            }///************************************************************* FIN CANCELAR RESERVA DE DADOS
                            if(dadoSelect >= 0)
                            {
                                if(tirada[dadoSelect] == 0) /// SI SELECCIONA UN DADO CERO
                                {
                                    borraTodo(30,1,msnCordX,msnCordy);
                                    mensajeria(1);
                                }
                                else if(cantReserv >= 5) /// SI SOBREPASA LA CANTIDAD DE DADOS SELECCIONADOS
                                {

                                    mensajeria(4);
                                }
                                else  /// SI SELECCIONA UN DADO DISPONIBLE
                                {
                                    reservados[cantReserv]=tirada[dadoSelect];
                                    tirada[dadoSelect]=0;
                                    cantHabi--;
                                    cantReserv++;
                                    mostrarDadosReserva(reservados, cantReserv);
                                    mostrarDados(tirada,5);
                                }

                            }

                        }
                        while(dadoSelect != -1 && dadoSelect != -2); /// FIN DOWHILE CASE 2

                        mensajeria(0);
                        break;
                    case 3:
                        if(finTurno != 0)

                        {
                            fflush(stdin);
                            i=selectOptionVert(opcionesX,5,10,174,2);
                            fflush(stdin);

                            if(cantReserv == 0)
                            {

                                contar(tirada,dados);
                                finTurno=    asignarPuntos(puntos,dados,i,turno,1);
                            }
                            else if(cantReserv == 5)
                            {

                                contar(reservados,dados);
                                finTurno = asignarPuntos(puntos,dados,i,turno,0);
                            }

                            else
                            {
                                for( a=0; a<5; a++) ///******************************************************
                                {
                                    buTirada[a]=tirada[a];
                                    buReservados[a]=reservados[a];
                                }
                                buCantHabi = cantHabi;
                                ordenarVec(buTirada);
                                for( a=cantReserv; a<5; a++)
                                {
                                    buCantHabi--;
                                    buReservados[a]=buTirada[buCantHabi];
                                }

                                contar(buReservados,dados);

                                finTurno = asignarPuntos(puntos,dados,i,turno,0);
                            }
                            for( v=0; v<tipoJuego; v++)
                            {
                                acum=0;
                                for( a=0; a<10; a++)
                                    if(puntos[v][a] >= 0 )
                                        acum+=puntos[v][a];
                                puntos[v][10]=acum;
                            }

                            for( a=0; a<tipoJuego; a++)
                                for(v=0; v<11; v++)
                                    if(puntos[a][v]!=-1)
                                        mostrarTablaPuntos(puntos,a,v);
                        }
                        else
                            mensajeria(1);
                        break;///FIN CASE 3
                    case 4:

                        fflush(stdin);
                        i=selectOptionVert(opcionesX,5,10,174,2);
                        fflush(stdin);
                        if(i>=1 && puntos[turno][i-1] == -1)
                        {
                            puntos[turno][i-1]=0;
                            finTurno = 0;
                            mostrarTablaPuntos(puntos,turno,i-1);

                        }

                        else if (i < 1)
                            break;
                        else
                            mensajeria(1);

                    }/// FIN SWITCH DE SELECCION DE MENU DE TIRO


                }
                while(opcion != 1 && finTurno != 0 );
            }
            while(tiro ==2 && opcion ==1  );

            ordenarVec(tirada);

            tiro++;

        }
        while(tiro<3 && finTurno != 0); ///fin FOR TIROS
        borraTodo(44,5,69,14);
    }///FIN FOR RONDA

    borraTodo(35,6,msnCordX,msnCordy);

FinDelJuego:
    mensajeria(5);
    msleep(1500);
    if(tipoJuego ==2 )
    {
        gotoxy(msnCordX-3,msnCordy+2);
        if(puntos[0][10] > puntos [1][10])
        {
            cout<<"EL GANADOR ES: "<<nombre[0];
            strcpy(nombreGan,nombre[0]);
            maxPuntuacion=puntos[0][10];

        }

        else if(puntos[0][10] < puntos [1][10])
        {
            cout<<"EL GANADOR ES: "<<nombre[1];
            strcpy(nombreGan,nombre[1]);
            maxPuntuacion=puntos[1][10];
        }
        else
        {
            cout<<"HUBO EMPATE";
            strcpy(nombreGan,nombre[0]);
            maxPuntuacion=puntos[0][10];
        }


    }
    else
    {
        strcpy(nombreGan,nombre[0]);
        maxPuntuacion=puntos[0][10];
    }
    if(maxPuntuacion > leerPuntuacion(nombreMax))
        anotaPuntuacion(nombreGan,maxPuntuacion);
    anykey();
    system("cls");
    setColor(10);
    gotoxy(54,10);
    cout<<"PUNTUACION FINAL";
    dibujarMarco(26,4,48,14,13);

    setColor(7);
    gotoxy(50,15);
    cout<<nombre[0];
    gotoxy(68,15);
    setColor(13);
    printf("%c ",221);
    setColor(7);
    cout<<puntos[0][10];
    if(tipoJuego== 2)
    {
        gotoxy(50,17);
        cout<<nombre[1];
        gotoxy(68,17);
        setColor(13);
        printf("%c ",221);
        setColor(7);
        cout<<puntos[1][10];
    }
    msleep(2000);
    anykey();
    system("cls");
    gotoxy (58,15);
    cout<<"GAME OVER";
    msleep(3000);
    anykey();
    return 0;



}

void dibujarInterfaz(char nombre[][14], char categorias[][9], int tipoJuego)
{
    dibujarMarco(15,22,3,4,7);///categorías
    int i=0;
    for(int x=0; x<12; x++)
    {
        gotoxy(4,i+5);
        cout << categorias[x];
        i+=2;

    }

    dibujarMarco(14,2,18,2,7);///cuadro nombre jugador 1
    gotoxy(19,3);
    cout<<nombre[0];
    dibujarMarco(14,22,18,4,7);///cuadro puntos jugador1
    if(tipoJuego==2)
    {

        dibujarMarco(14,2,32,2,7);///cuadro nombre jugador 2
        gotoxy(33,3);
        cout<<nombre[1];
        dibujarMarco(14,22,32,4,7);///cuadro puntos jugador 2
    }

    dibujarBordes(120,35,1,1,4,2);/// //////////////////////////////////////////////////////////////////////////////////////////////////////////
    dibujarBordes(24,4,3,28,11,0);
    gotoxy(6,29);
    cout << "Aceptar:      ENTER";
    gotoxy(6,30);
    cout << "Seleccionar:  SPACE";
    gotoxy(6,31);
    cout << "Cancelar:     Supr";/// TABLA DE BOTONES DE ACCION/// ///////////////////////////////////////////////////////////////
    gotoxy(70,3);
    cout <<"Jugador:                Ronda:    Tiro:";
    dibujarBordes(46,7,68,5,0,11);/// BORDES DE DADOS
    dibujarBordes(46,7,68,12,0,11);
    setColor(11);
    setBackgroundColor(0);
    gotoxy(68,12);
    printf("%c",204);
    gotoxy(114,12);
    printf("%c",185);/// ESQUINAS MEDIAS  DE DADO

    setColor(7);
    setBackgroundColor(0);


}
void ingresoNombre(char nombre[][14],int tipoJuego)
{

    char letra;
    int x,color;
    for(int  i=0; i<2; i++) ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    {
        system("cls");
        gotoxy(35,14);
        color = saveDefaultColor();
        setColor(10);
        cout << "INGRESE NOMBRE JUGADOR "<<i+1<< " (usar '_' para separar)";
        setColor(color);
        dibujarMarco(14,3,49,16,12);
        gotoxy(50,17);
        x=0;
        letra=' ';
        while(x<=13 && letra != KEY_ENTER)
        {
            letra = getkey();

            if(x <13 && validarIngNombre(letra))
            {
                nombre[i][x]=letra;
                x++;
            }
            else if(letra == 8 &&  x>0)
            {
                cout << letra;
                setChar(' ');///                                    INGRESO NOMBRE DE JUGADOR/ES
                x--;
            }
            if(letra == KEY_ENTER)
            {
                nombre[i][x]= '\0';
                if(x==0)
                    letra= ' ';
            }
        }
        if(tipoJuego==1)
            i=3;
    }///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

}
void saludo()
{
    int cx=23,y=6, r=10, t=30;
    char s=169;
    setColor(10);
    letraG(cx,y,t,s);
    cx+=r;
    letraE(cx,y,t,s);
    cx+=r;
    letraN(cx,y,t,s);
    cx+=r;
    letraE(cx,y,t,s);
    cx+=r;
    letraR(cx,y,t,s);
    cx+=r;
    letraA(cx,y,t,s);
    cx+=r;
    letraL(cx,y,t,s);
    cx+=r;
    letraA(cx,y,t,s);
    setColor(7);
    msleep(1000);
    gotoxy(51,16);
    cout<<"PRESIONE ENTER";
    anykey();

}
void anotaPuntuacion(char vNombre[14],int puntos)
{
    FILE *pArchivo;
    pArchivo=fopen("puntuacion.txt","w");
    if(pArchivo!=NULL)
    {

        fprintf(pArchivo,"%s\t%d\t\n",
                vNombre,puntos);



    }
    fclose(pArchivo);

}
int leerPuntuacion(char vNombre[14])
{
    int punto;
    FILE *pArchivo;
    pArchivo=fopen("puntuacion.txt","r");
    if(pArchivo != NULL)
    {
        while(!feof(pArchivo))
        {
            fscanf(pArchivo,"%s\t%d\t",vNombre,&punto);

        }

    }
    else
    {
        punto =0;
    }
    fclose(pArchivo);
    return punto;
}
void vaciarMat(int mat[][11])
{
    int x, i;
    for(x=0; x<2; x++)
        for(i=0; i<11; i++)
            mat[x][i]=-1;

}
void mostrarTablaPuntos(int vpuntos[][11],int  jugador,int categoria)
{
    int coordX=24, coordY=5;
    setColor(10);
    gotoxy(coordX+(jugador*14),coordY+(categoria*2));
    cout << vpuntos[jugador][categoria];
    setColor(7);
}
void borraTodo(int ancho, int largo, int coordX, int coordY)
{
    int x,j;
    for(j=coordY; j<largo+coordY; j++)
    {
        gotoxy(coordX,j);
        for(x=coordX; x<ancho+coordX; x++)
            cout<<' ';
    }


}
void mensajeria(int mensaje)
{
    int color;
    borraTodo(30,1,msnCordX,msnCordy);
    color = saveDefaultColor();
    setColor(7);
    gotoxy(msnCordX,msnCordy);
    switch(mensaje)
    {
    case 0:
        break;
    case 1:
        cout<<" Opcion no valida";
        break;
    case 2:
        cout<<"SELECCIONAR DADOS";
        break;
    case 3:
        cout<<"FALTAN RESERVAR DADOS";
        break;
    case 4:
        cout<<"NO SE PUEDE RESERVAR MAS";
        break;
    case 5:
        cout<<"FIN DEL JUEGO";
    }
    setColor(color);
}
int azar()
{
    int num;
    msleep(10);
    num = 1 + rand() % (7 - 1);
    return num;
}
int sumarVec(int vec[],int tam)
{
    int x,suma=0;
    for(x=0; x<tam; x++)
        suma+=vec[x];

    return suma;
}
void dibujarBordes(int ancho, int largo, int coordX, int coordY,int colorFondo,int color)
{
    setColor(color);
    setBackgroundColor(colorFondo);

    for(int x=0; x<largo; x++)
    {
        gotoxy(coordX,x+coordY);
        printf("%c",186);
        gotoxy(coordX+ancho,x+coordY);
        printf("%c", 186);
    }
    for(int x=0; x<ancho; x++)
    {
        gotoxy(coordX+x,coordY);
        printf("%c",205);
        gotoxy(coordX+x,largo+coordY);
        printf("%c",205);
    }
    gotoxy(coordX,coordY);
    printf("%c",201);
    gotoxy(coordX,coordY+largo);
    printf("%c",200);
    gotoxy(coordX+ancho,coordY);
    printf("%c",187);
    gotoxy(coordX+ancho,coordY+largo);
    printf("%c",188);
    setColor(7);
    setBackgroundColor(0);
}
bool validarIngNombre(char letra)
{
    if(letra >= 'A' && letra <= 'Z' ||letra>= 'a' && letra <= 'z' || letra == '_' || letra== '-')
    {
        cout << letra;
        return true;
    }
    return false;
}
void vaciarVec(int vec[],int tam)
{
    for(int x=0; x<tam; x++)
    {
        vec[x]=0;
    }
}
void dibujarDado(int ancho, int largo,int coordX,int coordY,int valor)
{
    setColor(15);
    for(int x=0; x<largo; x++)
    {
        gotoxy(coordX,x+coordY);
        printf("%c",179);
        gotoxy(coordX+ancho,x+coordY);
        printf("%c", 179);
    }
    for(int x=0; x<ancho; x++)
    {
        gotoxy(coordX+x,coordY);
        printf("%c",196);
        gotoxy(coordX+x,largo+coordY);
        printf("%c", 196);
    }
    gotoxy(coordX,coordY);
    printf("%c",218);
    gotoxy(coordX,coordY+largo);
    printf("%c",192);
    gotoxy(coordX+ancho,coordY);
    printf("%c",191);
    gotoxy(coordX+ancho,coordY+largo);
    printf("%c",217);
    setColor(7);

    switch(valor)
    {
    case 0:
        gotoxy(coordX+1,coordY+1);
        cout<<"#####";
        gotoxy(coordX+1,coordY+2);
        cout<<"#####";
        gotoxy(coordX+1,coordY+3);
        cout<<"#####";
        break;
    case 1:
        gotoxy(coordX+1,coordY+1);
        cout<<"     ";
        gotoxy(coordX+1,coordY+2);
        cout<<"  *  ";
        gotoxy(coordX+1,coordY+3);
        cout<<"     ";
        break;
    case 2:
        gotoxy(coordX+1,coordY+1);
        cout<<"*    ";
        gotoxy(coordX+1,coordY+2);
        cout<<"     ";
        gotoxy(coordX+1,coordY+3);
        cout<<"    *";
        break;
    case 3:
        gotoxy(coordX+1,coordY+1);
        cout<<"*    ";
        gotoxy(coordX+1,coordY+2);
        cout<<"  *  ";
        gotoxy(coordX+1,coordY+3);
        cout<<"    *";
        break;
    case 4:
        gotoxy(coordX+1,coordY+1);
        cout<<"*   *";
        gotoxy(coordX+1,coordY+2);
        cout<<"     ";
        gotoxy(coordX+1,coordY+3);
        cout<<"*   *";
        break;
    case 5:
        gotoxy(coordX+1,coordY+1);
        cout<<"*   *";
        gotoxy(coordX+1,coordY+2);
        cout<<"  *  ";
        gotoxy(coordX+1,coordY+3);
        cout<<"*   *";
        break;
    case 6:
        gotoxy(coordX+1,coordY+1);
        cout<<"*   *";
        gotoxy(coordX+1,coordY+2);
        cout<<"*   *";
        gotoxy(coordX+1,coordY+3);
        cout<<"*   *";
        break;
    }
}

void mostrarDados(int tirada[],int cant)
{
    int x=70,y=7;
    for(int i=0; i<cant; i++)
    {
        dibujarDado( 6,4,x,y,tirada[i]);
        x+=9;
    }
}
void mostrarDadosReserva(int reservados[],int cant)
{
    int x=70, y=14;
    for(int i=0; i<cant; i++)
    {
        dibujarDado(6,4,x,y,reservados[i]);
        x+=9;
    }
}
void mostrarMenu(int x,int y) ///Muestra el menu primero
{
    dibujarBordes(34,7,40,13,0,13);
    gotoxy(x,y);
    printf("JUEGO NUEVO PARA UN JUGADOR");
    gotoxy(x,y+1);
    printf("JUEGO NUEVO PARA DOS JUGADORES");
    gotoxy(x,y+2);
    printf("MOSTRAR LA PUNTUACION MAS ALTA");
    gotoxy(x,y+3);
    printf("SALIR");
}
int selectOptionHori(int coordX,int coordY, int cantOpc, char sym, int despl)
{
    int j=coordX, opcion, color;
    char tecla;
    color= saveDefaultColor();
    setColor(14);
    gotoxy(coordX,coordY);
    printf("%c",sym);
    do
    {
        if(kbhit())
        {
            tecla= getkey();
            gotoxy(coordX,coordY);
            printf(" ");
            if(tecla == KEY_LEFT && coordX > j)
                coordX-=despl;
            if(tecla == KEY_RIGHT && coordX < j+(cantOpc-1)*despl)
                coordX+=despl;
            gotoxy(coordX,coordY);
            printf("%c",sym);
        }
        msleep(30);
    }
    while(tecla != KEY_ENTER && tecla != KEY_SPACE && tecla != KEY_DELETE);
    gotoxy(coordX,coordY);
    setChar(' ');
    setColor(color);

    if(tecla == KEY_SPACE)
        opcion= 0;
    else if(tecla == KEY_DELETE)
        opcion= -1;
    else
        opcion = (coordX-j)/despl+1;

    return opcion;
}
int selectOptionVert(int x, int y, int cantOpc, char letra, int despl) ///Permite seleccionar una accion dentro de un menú. X e Y son las coordenadas-1 de la
{
    int i=y, opcion, color;                                     ///lista de opciones, cantOpc es la cantidad de opciones y letra es el caracter selector.
    char tecla;                                         ///Retorna la posicion elegida de la opcion respecto a su orden
    color = saveDefaultColor();
    setColor(11);
    gotoxy(x,y);
    printf("%c",letra);
    do
    {
        if(kbhit())
        {
            tecla= getkey();
            gotoxy(x,y);
            printf(" ");
            if(tecla == KEY_UP && y > i)
                y-=despl;
            if(tecla == KEY_DOWN && y < i+(cantOpc-1)*despl)
                y+=despl;
            gotoxy(x,y);
            printf("%c",letra);
        }
        msleep(30);

    }
    while(tecla != KEY_ENTER && tecla != KEY_SPACE && tecla != KEY_DELETE);
    gotoxy(x,y);
    setChar(' ');
    setColor(color);

    if(tecla == KEY_SPACE)
        opcion= 0;
    else if(tecla == KEY_DELETE)
        opcion= -1;
    else
        opcion = (y-i)/despl+1;

    return opcion;
}
void dibujarMarco(int ancho, int largo,int coordX, int coordY,int color) /// x e y son el tamaño del cuadrado, Y siempre tiene que ser par. a y b son el punto desde donde se empieza a dibujar.
{
    setColor(color);
    for(int i=coordY; i<largo+coordY; i++)  ///pinta marco Y
    {
        gotoxy(coordX,i);
        printf("%c", 186);
        gotoxy(ancho+coordX,i);
        printf("%c", 186);
    }
    for(int i=coordX; i<ancho+coordX; i++) ///pinta marco x
    {
        gotoxy(i,coordY);
        printf("%c", 205);
        gotoxy(i,largo+coordY);
        printf("%c", 205);
    }
    gotoxy(coordX,coordY);
    printf("%c", 207);///pinta esquinas////////////////////////
    gotoxy(coordX,largo+coordY);
    printf("%c", 207);///
    gotoxy(ancho+coordX,coordY);
    printf("%c", 207);///
    gotoxy(ancho+coordX,largo+coordY);
    printf("%c", 207);/// ////////////////////////////////////

    for(int j=coordY+2; j< largo+coordY; j+=2)
        for(int i=1+coordX; i<ancho+coordX; i++)
        {
            gotoxy(i,j);
            printf("-");
        }
    setColor(7);
}

void contar(int tirada[], int dados[]) ///Un vector que cuentas los dados de una tirada
{
    int x;
    vaciarVec(dados,6);
    for(x=0; x<5; x++)
        dados[tirada[x]-1]++;
}
bool generala(int dados[]) ///verifica si es generala
{
    bool result=false;
    int x = 0;
    while(!result && x<6)
    {
        result = (dados[x] == 5);
        x++;
    }
    return result;
}

bool poker(int dados[]) ///verifica si es poker
{
    bool result=false;
    int x = 0;
    while(!result && x<6)
    {
        result = (dados[x] == 4);
        x++;
    }
    return result;
}

bool full(int dados[]) ///verifica si es full
{
    bool resultTres = false, resultDos = false;
    int x = 0;
    while(!(resultTres && resultDos) && x<6)
    {
        if(dados[x] == 3)
            resultTres = true;
        else if(dados[x] == 2)
            resultDos = true;
        x++;
    }
    return resultDos * resultTres;
}

bool escalera(int dados[]) ///verifica si escalera
{
    bool result;
    result=((dados[0]==1 && dados[1]==1 && dados[2]==1 && dados[3]==1 && dados[4]==1)||(dados[1]==1 && dados[2]==1 &&dados[3]==1 &&dados[4]==1 && dados[5]==1));



    return result;
}

int selecTurno(char nombre[][14])
{
    int i=0, suma[2], x, pri, tirada[5];
    do
    {
        for(i=0; i<2; i++)
        {
            borraTodo(14,1,79,3);
            gotoxy(79,3);
            cout<<nombre[i];
            gotoxy(msnCordX+3,msnCordy);
            cout<<"SELECCION DE TURNO";/// SELECCCION DE TURNO
            gotoxy(80,22);
            cout<<"TIRAR DADO";
            selectOptionVert(79,22,1,175,1);

            /// GENERACION DE TIRADA
            for(x=0; x<5; x++)
                tirada[x] = azar();
            mostrarDados(tirada,5);
            suma[i]=sumarVec(tirada,5);
            setColor(10);
            gotoxy(24+(i*14),25);
            cout<<suma[i];
            setColor(7);
        }
        if(suma[0] > suma[1])
            pri=0;
        else if(suma[1] > suma [0])
            pri=1;
        else
        {
            borraTodo(24,1,msnCordX,msnCordy);
            gotoxy(msnCordX,msnCordy);
            cout<<"SUMAS IGUALES! REELEGIR TURNO";
            msleep(3000);
            mensajeria(0);
            borraTodo(8,1,20,25);
            borraTodo(8,1,34,25);
        }
    }
    while(suma[1] == suma [0]);

    return pri;

}

void ordenarVec(int v[])
{
    int i, j, aux,N=5;
    bool intercambio;
    for (i=0; i<N-1; i++)
    {
        intercambio = false;
        for (j=0; j<N-1-i; j++)
        {
            if (v[j]<v[j+1])
            {
                aux = v[j];
                v[j] = v[j+1];
                v[j+1]= aux;
                intercambio = true;
            }
        }
        // Si no ha habido ningún intercambio la tabla ya está ordenada
        if ( ! intercambio )
        {
            break;
        }
    }

}

int asignarPuntos(int vPuntos[][11],int vDados[], int valor,int jugador, bool servida )
{
    int coordX=24, coordY=5;
    int turno=1;

    switch(valor)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        if(vDados[valor-1] == 0)
            mensajeria(1);
        else if(vPuntos[jugador][valor-1] >= 0)
            mensajeria(1);
        else if(vPuntos[jugador][valor-1] == -1)
        {
            vPuntos[jugador][valor-1] = vDados[valor-1] * valor;
            turno=0;
        }
        break;
    case 7:
        if(escalera(vDados) && vPuntos[jugador][valor-1] == -1)
        {
            vPuntos[jugador][valor-1] = 20;
            if(servida)
                vPuntos[jugador][valor-1]+= 5;
            turno=0;
        }
        else
            mensajeria(1);
        break;
    case 8:
        if(full(vDados) && vPuntos[jugador][valor-1] == -1)
        {
            vPuntos[jugador][valor-1] = 30;
            if(servida)
                vPuntos[jugador][valor-1]+= 5;
            turno=0;
        }
        else
            mensajeria(1);
        break;
    case 9:
        if(poker(vDados) && vPuntos[jugador][valor-1] == -1)
        {
            vPuntos[jugador][valor-1] = 40;
            if(servida)
                vPuntos[jugador][valor-1]+= 5;
            turno=0;
        }
        else
            mensajeria(1);
        break;
    case 10:
        if(generala(vDados) && vPuntos[jugador][valor-1] == -1)
        {
            vPuntos[jugador][valor-1] = 60;
            turno=0;


        }
        else
            mensajeria(1);

    }

    return turno;
}
void letraG(int x,int y,int t, char sym)
{

    gotoxy(x+1,y);
    printf("%c",sym);
    msleep(t);///********************************
    gotoxy(x+2,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+3,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+4,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+5,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+4,y+2);
    printf("%c",sym);
    msleep(t);///             G
    gotoxy(x+5,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+5,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+2,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+3,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+4,y+4);
    printf("%c",sym);
    msleep(t);///*****************

}
void letraE(int x,int y,int t, char sym)
{
    gotoxy(x,y);
    printf("%c",sym);
    msleep(t);///************************************
    gotoxy(x+1,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+2,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+3,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+4,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+5,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+2,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+2);
    printf("%c",sym);
    msleep(t);///         E
    gotoxy(x+2,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+3,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+4,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+2,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+3,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+4,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+5,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y+4);
    printf("%c",sym);
    msleep(t);///*************************
}

void letraN(int x,int y,int t, char sym)
{
    gotoxy(x,y);
    printf("%c",sym);
    msleep(t);///*************************************
    gotoxy(x+1,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+5,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+2,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+5,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+2);
    printf("%c",sym);
    msleep(t);///       N
    gotoxy(x+1,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+3,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+5,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+4,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+5,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+5,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y+4);
    printf("%c",sym);
    msleep(t);///*********************
}

void letraR(int x,int y,int t, char sym)
{
    gotoxy(x,y);
    printf("%c",sym);
    msleep(t);///*************************************
    gotoxy(x+1,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+2,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+3,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+4,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+5,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+2);
    printf("%c",sym);
    msleep(t);///       R
    gotoxy(x+1,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+2,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+3,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+4,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+5,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+7,y+4);
    printf("%c",sym);
    msleep(t);///******************
}

void letraA(int x,int y,int t, char sym)
{
    gotoxy(x,y);
    printf("%c",sym);
    msleep(t);///***********************************
    gotoxy(x+1,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+2,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+3,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+4,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+5,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+2);
    printf("%c",sym);
    msleep(t);///           A
    gotoxy(x+1,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+2,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+3,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+4,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+5,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y+4);
    printf("%c",sym);
    msleep(t);///*************************
}
void letraL(int x,int y,int t, char sym)
{
    gotoxy(x,y);
    printf("%c",sym);
    msleep(t);///*************************************
    gotoxy(x+1,y);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+1);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+2);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+3);
    printf("%c",sym);
    msleep(t);///                                L
    gotoxy(x+1,y+3);
    printf("%c",sym);
    msleep(t);
    gotoxy(x,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+1,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+2,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+3,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+4,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+5,y+4);
    printf("%c",sym);
    msleep(t);
    gotoxy(x+6,y+4);
    printf("%c",sym);
    msleep(t);///***********************
}
