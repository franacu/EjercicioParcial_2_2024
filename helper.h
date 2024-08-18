//
// Created by Fran on 18/08/2024.
//

#ifndef EJPARCIAL2024_HELPER_H
#define EJPARCIAL2024_HELPER_H
#define TAM 100

typedef struct nodo {
    char id[12];
    struct nodo* sig;
}Nodo;

typedef struct estudiante{
    char id[12];
    char nombre[25];
    struct estudiante * ant;
    struct estudiante * sig;
    Nodo * cursos;
}Estudiante;

typedef struct registro{
    Estudiante * cabEst;
}RegistroEstudiantes;

typedef struct curso
{
    char id[12];
    char nombre[25];
    Nodo *estudiantes;
}Curso;
typedef struct tablaHash
{
    Curso *cursos[TAM];
}TablaHash;

Nodo *newNodo(char id[12]);
Estudiante *newEstudiante(char id[12],char nombre[25]);
RegistroEstudiantes *newRegistroEstudiantes();
Curso *newCurso(char id[12],char nombre[25]);
TablaHash *newTablaHash();

void agregarEstudiante(RegistroEstudiantes *registroEstudiantes,char *id,char *nombre);
Estudiante *buscarEstudiante(char *ID,RegistroEstudiantes *registroEstudiantes);
Curso *buscarCurso(char *ID,TablaHash *cursos);
void eliminarEstudiante(RegistroEstudiantes *registroEstudiantes,TablaHash *cursos,char *ID);
void agregarCurso(TablaHash *cursos,char *IDcurso,char *nombre);
void inscribirCurso(RegistroEstudiantes * registroEstudiantes, TablaHash* cursos, char * IDestudiante, char * IDcurso);
void imprimirEstudiante(Estudiante * estudiante,TablaHash*cursos);
void imprimirEstudiantes(RegistroEstudiantes * registroEstudiantes, TablaHash * cursos);
void imprimirCurso(Curso * curso, RegistroEstudiantes * registroEstudiantes);
void imprimirCursos(TablaHash * tablaHash, RegistroEstudiantes * registroEstudiantes);


#endif //EJPARCIAL2024_HELPER_H
