//
// Created by Fran on 18/08/2024.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helper.h"
Nodo * newNodo(char id[12]){
    Nodo * aux = malloc(sizeof(Nodo));
    if (aux == NULL) {
        printf("No hay memoria disponible\n");
        exit(-1);
    }
    for (int i = 0; i < 12; i++) {
        aux->id[i] = id[i];
    }
    aux->sig = NULL;
    return aux;
}
Estudiante * newEstudiante(char id[12], char nombre[25]){
    Estudiante * aux = malloc(sizeof(Estudiante));
    if (aux == NULL) {
        printf("No hay memoria disponible\n");
        exit(-1);
    }
    for (int i = 0; i < 12; i++) {
        aux->id[i] = id[i];
    }
    for (int i = 0; i < 25; i++) {
        aux->nombre[i] = nombre[i];
    }
    aux->ant = NULL;
    aux->sig = NULL;
    aux->cursos = NULL;
    return aux;
}
RegistroEstudiantes * newRegistroEstudiantes(){
    RegistroEstudiantes * aux = malloc(sizeof(RegistroEstudiantes));
    if (aux == NULL) {
        printf("No hay memoria disponible\n");
        exit(-1);
    }
    aux->cabEst = NULL;
    return aux;
}
Curso * newCurso(char id[12], char nombre[25]){
    Curso * aux = malloc(sizeof(Curso));
    if (aux == NULL) {
        printf("No hay memoria disponible\n");
        exit(-1);
    }
    for (int i = 0; i < 12; i++) {
        aux->id[i] = id[i];
    }
    for (int i = 0; i < 25; i++) {
        aux->nombre[i] = nombre[i];
    }
    aux->estudiantes = NULL;
    return aux;
}
TablaHash * newTablaHash(){
    TablaHash * aux = malloc(sizeof(TablaHash));
    if (aux == NULL) {
        printf("No hay memoria disponible\n");
        exit(-1);
    }
    for (int i = 0; i < 100; i++) {
        aux->cursos[i] = NULL;
    }
    return aux;
}

void agregarEstudiante(RegistroEstudiantes * registroEstudiantes, char * id, char * nombre){
    Estudiante * nuevo = newEstudiante(id, nombre);
    if (registroEstudiantes->cabEst == NULL) {
        registroEstudiantes->cabEst= nuevo;
    } else {
        Estudiante * aux = registroEstudiantes->cabEst;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
        nuevo->ant = aux;
    }
}
void eliminarEstudiante(RegistroEstudiantes *registroEstudiantes,TablaHash *cursos,char *ID)
{
    Estudiante * estudiante = buscarEstudiante(ID,registroEstudiantes);
    if (estudiante == NULL) {
        printf("\nEstudiante no encontrado\n");
        return;
    }
    Nodo * aux = estudiante->cursos;
    while (aux != NULL) {
        Curso * curso = buscarCurso(aux->id,cursos);
        if (curso != NULL) {
            Nodo * aux2 = curso->estudiantes;
            Nodo * ant = NULL;
            while (aux2 != NULL) {
                if (strcmp(aux2->id, ID) == 0) {
                    if (ant == NULL) {
                        curso->estudiantes = aux2->sig;
                    } else {
                        ant->sig = aux2->sig;
                    }
                    free(aux2);
                    break;
                }
                ant = aux2;
                aux2 = aux2->sig;
            }
        }
        aux = aux->sig;
    }
    if (estudiante->ant == NULL) {
        registroEstudiantes->cabEst = estudiante->sig;
    } else {
        estudiante->ant->sig = estudiante->sig;
    }
    if (estudiante->sig != NULL) {
        estudiante->sig->ant = estudiante->ant;
    }
    free(estudiante);
}
void inscribirCurso(RegistroEstudiantes * registroEstudiantes, TablaHash* cursos, char * idEstudiante, char * idCurso){
    Estudiante * estudiante = buscarEstudiante(idEstudiante, registroEstudiantes);
    Curso * curso = buscarCurso(idCurso,cursos);
    if (estudiante == NULL) {
        printf("\nEstudiante no encontrado\n");
        return;
    }
    if (curso == NULL) {
        agregarCurso(cursos, idCurso, "Curso nuevo");
        curso = buscarCurso(idCurso,cursos);
    }
    Nodo * nuevo = newNodo(idCurso);
    if (estudiante->cursos == NULL) {
        estudiante->cursos = nuevo;
    } else {
        Nodo * aux = estudiante->cursos;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
    if (curso->estudiantes == NULL) {
        curso->estudiantes = newNodo(idEstudiante);
    } else {
        Nodo * aux = curso->estudiantes;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = newNodo(idEstudiante);
    }
}
Estudiante *buscarEstudiante(char *ID,RegistroEstudiantes *registroEstudiantes)
{
    Estudiante * aux = registroEstudiantes->cabEst;
    while (aux != NULL) {
        if (strcmp(aux->id, ID) == 0) {
            return aux;
        }
        aux = aux->sig;
    }
    return NULL;
}
void imprimirEstudiantes(RegistroEstudiantes * registroEstudiantes, TablaHash * cursos){
    printf("\nEstudiantes:\n");
    Estudiante * aux = registroEstudiantes->cabEst;
    while (aux != NULL) {
        imprimirEstudiante(aux, cursos);
        aux = aux->sig;
    }
}
void imprimirEstudiante(Estudiante * estudiante, TablaHash * cursos){
    if (estudiante == NULL) {
        printf("\nEstudiante no encontrado\n");
        return;
    }
    printf("\nID: %s\t", estudiante->id);
    printf("Nombre: %s\n", estudiante->nombre);
    printf("Cursos:\n");
    Nodo * aux = estudiante->cursos;
    int i = 1;
    while (aux != NULL) {
        printf ("Materia %d: %s\t",i, buscarCurso(aux->id,cursos)->nombre);
        aux = aux->sig;
        i++;
    }
    printf("\n");
}
int hash(char * id){
    int suma = 0;
    for (int i = 0; i < 12; i++) {
        suma += id[i];
    }
    return suma % TAM;
}
void agregarCurso(TablaHash * tablaHash, char * id, char * nombre){
    Curso * nuevo = newCurso(id, nombre);
    int pos = hash(id);
    while (tablaHash->cursos[pos] != NULL) {
        pos =(pos +1)%TAM;
    }
    tablaHash->cursos[pos] = nuevo;
}

Curso *buscarCurso(char *ID,TablaHash *cursos)
{
    int pos = hash(ID);
    while (cursos->cursos[pos] != NULL) {
        if (strcmp(cursos->cursos[pos]->id, ID) == 0) {
            return cursos->cursos[pos];
        }
        pos =(pos +1)%TAM;
    }
    return NULL;
}

void imprimirCurso(Curso * curso, RegistroEstudiantes * registroEstudiantes){
    if (curso == NULL) {
        printf("\nCurso no encontrado\n");
        return;
    }
    printf("\nID: %s\t", curso->id);
    printf("Nombre: %s\n", curso->nombre);
    printf("Estudiantes:\n");
    Nodo * aux = curso->estudiantes;
    int i =1;
    while (aux != NULL) {
        printf("Estudiante %d: %s\t",i, buscarEstudiante( aux->id,registroEstudiantes)->nombre);
        aux = aux->sig;
        i++;
    }
    printf("\n");
}
void imprimirCursos(TablaHash * tablaHash, RegistroEstudiantes * registroEstudiantes){
    printf("\nCursos:\n");
    for (int i = 0; i < TAM; i++) {
        if (tablaHash->cursos[i] != NULL) {
            imprimirCurso(tablaHash->cursos[i], registroEstudiantes);
        }
    }
}
