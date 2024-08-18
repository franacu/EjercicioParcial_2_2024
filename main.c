#include "helper.h"

int main()
{
    TablaHash * cursos = newTablaHash();
    RegistroEstudiantes * registroEstudiantes = newRegistroEstudiantes();
    agregarEstudiante(registroEstudiantes, "E1122333444", "Juan");
    agregarEstudiante(registroEstudiantes, "E2233444555", "Pedro");
    agregarEstudiante(registroEstudiantes, "E3344555666", "Raquel");
    agregarEstudiante(registroEstudiantes, "E4455666777", "Pepe");

    imprimirEstudiantes(registroEstudiantes, cursos);
    imprimirEstudiante(buscarEstudiante("E2233444555",registroEstudiantes ), cursos);
    imprimirEstudiante(buscarEstudiante("E2233123123",registroEstudiantes), cursos);


    agregarCurso(cursos, "C1122333444", "Matematica");
    agregarCurso(cursos, "C2233444555", "Fisica");

    imprimirCursos(cursos, registroEstudiantes);
    imprimirCurso(buscarCurso("2141522515",cursos), registroEstudiantes);
    imprimirCurso(buscarCurso("C2233123123",cursos), registroEstudiantes);

    inscribirCurso(registroEstudiantes, cursos, "E1122333444", "C1122333444");
    inscribirCurso(registroEstudiantes, cursos, "E1122333444", "C2233444555");
    inscribirCurso(registroEstudiantes, cursos, "E2233444555", "C1122333444");
    inscribirCurso(registroEstudiantes, cursos, "E3344555666", "C3344555666");

    imprimirEstudiantes(registroEstudiantes, cursos);
    imprimirCursos(cursos, registroEstudiantes);

    eliminarEstudiante(registroEstudiantes, cursos,"E1122333444");
    imprimirEstudiantes(registroEstudiantes, cursos);
    imprimirCursos(cursos, registroEstudiantes);

    return 0;
}
