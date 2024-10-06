// Default
#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <stdlib.h> 

// Conio
#include <conio.h>
#include "./lib/meuconio.h"

// Headers
#include "./headers/figures.h"
#include "./headers/colors.h"
#include "./headers/actions.h"

struct Student {
  char RA[13];
  char name[80];
};

struct Subject {
  int code;
  char name[80];
};

struct StudentSubjects {
  char studentRA[13];
  int subjectCode;
  float grade;
};

// Menu Options
#define OPTIONS_FISIC_SIZE 5
#define CHAR_OPTION_FISIC_SIZE 300

// Students CONST's
#define STUDENTS_FISIC_SIZE 100

// Subjects CONST's
#define SUBJECTS_FISIC_SIZE 100

// StudentSubjects CONST's
#define STUDENTS_SUBJECTS_FISIC_SIZE 100

// Students
void studentsMenu(Student students[], int &studentsLogicSize);
void createStudent(Student students[], int &studentsLogicSize);
void updateStudent(Student students[], int studentsLogicSize);
void queryStudent(Student students[], int studentsLogicSize);
void deleteStudent(Student students[], int &studentsLogicSize);
void viewStudent(Student students);
int findStudentIndexByRA(Student students[], int studentsLogicSize, char RA[13]);
void studentsMenuTitle();

// Subject
void subjectsMenu(Subject subjects[], int &subjectsLogicSize);
void createSubject(Subject subjects[], int &subjectsLogicSize);
void querySubject(Subject subjects[], int subjectsLogicSize);
void deleteSubject(Subject subjects[], int &subjectsLogicSize);
void viewSubject(Subject subjects);
int findSubjectIndexByCode(Subject subjects[], int subjectsLogicSize, int code);
void subjectsMenuTitle();

// StudentSubjects
void studentSubjectsMenu(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize, Student students[], int studentsLogicSize, Subject subjects[], int subjectsLogicSize);
void createStudentSubject(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize, Student students[], int studentsLogicSize, Subject subjects[], int subjectsLogicSize);
void queryStudentSubjects(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize, Student students[], int studentsLogicSize, Subject subjects[], int subjectsLogicSize);
void deleteStudentSubject(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize);
void viewStudentSubject(StudentSubjects studentSubjects, Student student, int studentsLogicSize, Subject subjects[], int subjectsLogicSize);
int findStudentIndex(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize, char studentRA[13]);
int findStudentSubjectIndex(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize, char studentRA[13], int subjectCode);

// Menu
void reportsMenu();
void reportsMenuTitle();

void configMenu(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize, Student students[], int &studentsLogicSize, Subject subjects[], int &subjectsLogicSize);
void configMenuTitle();

void principalMenuTitle();
int menu(char options[][CHAR_OPTION_FISIC_SIZE], int studentsLogicSize);

// Others
int request(const char message[]);
void clearupline(int quantityOfUpLines);
void editInput(char string[]);
void frame(int width, int height);

int main() {
  SetConsoleOutputCP(CP_UTF8);

  int principalMenuOption;
  char principalOptions[OPTIONS_FISIC_SIZE][CHAR_OPTION_FISIC_SIZE] = { "Estudantes", "Disciplinas", "Disciplinas dos Estudante", "Relatórios", "Configuração" };

  Student students[STUDENTS_FISIC_SIZE];
  int studentsLogicSize = 0;

  Subject subjects[SUBJECTS_FISIC_SIZE];
  int subjectsLogicSize = 0;

  StudentSubjects studentSubjects[STUDENTS_SUBJECTS_FISIC_SIZE];
  int studentSubjectsLogicSize = 0;

  do {
    clrscr();
    principalMenuTitle();
    principalMenuOption = menu(principalOptions, OPTIONS_FISIC_SIZE);

    switch(principalMenuOption) {
      case 0:
        studentsMenu(students, studentsLogicSize);
        break;
      case 1:
        subjectsMenu(subjects, subjectsLogicSize);
        break;
      case 2:
        studentSubjectsMenu(
          studentSubjects,
          studentSubjectsLogicSize,
          students,
          studentsLogicSize,
          subjects,
          subjectsLogicSize
        );
        break;
      case 3:
        reportsMenu();
        break;
      case 4:
        configMenu(
          studentSubjects,
          studentSubjectsLogicSize,
          students,
          studentsLogicSize,
          subjects,
          subjectsLogicSize
        );
        break;
    }
  } while(principalMenuOption != -1);
}

void studentsMenu(Student students[], int &studentsLogicSize) {
  int studentsMenuOption;
  char studentsOptions[4][CHAR_OPTION_FISIC_SIZE] = { "Cadastrar", "Consultar", "Alterar", "Excluir" };

  do {
    clrscr();
    studentsMenuTitle();
    studentsMenuOption = menu(studentsOptions, 4);

    switch(studentsMenuOption) {
      case 0:
        createStudent(students, studentsLogicSize);
        break;
      case 1:
        queryStudent(students, studentsLogicSize);
        break;
      case 2:
        updateStudent(students, studentsLogicSize);
        break;
      case 3:
        deleteStudent(students, studentsLogicSize);
        break;
    }
  } while(studentsMenuOption != -1);
}

void createStudent(Student students[], int &studentsLogicSize) {
  Student newStudent;

  do {
    if (studentsLogicSize < STUDENTS_FISIC_SIZE) {
      printf(RED "\nDados do novo estudante de número " NORMAL "#%d\n", studentsLogicSize + 1);

      printf("Nome: ");
      gets(newStudent.name);
      fflush(stdin);

      if (strlen(newStudent.name) >= 1) {
        printf("Registro do Estudante (EX: 26.24.1354-0): ");
        gets(newStudent.RA);
        fflush(stdin);

        if (findStudentIndexByRA(students, studentsLogicSize, newStudent.RA) >= 0) {
          printf(YELLOW "[AVISO] Registro de Estudante: \"%s\" já está cadastrado.\n" NORMAL, newStudent.RA);
          getch();
          clearupline(5);
        } else {
          if (request("Você realmente deseja criar esse estudante?")) {
            students[studentsLogicSize] = newStudent;
            studentsLogicSize++;
          }

          clearupline(7);
        }
      }
    } else { printf(RED "\n[ERROR] Não há mais capacidade de armazenamento para estudantes." NORMAL); getch(); }
  } while(studentsLogicSize < STUDENTS_FISIC_SIZE && strlen(newStudent.name) >= 1);
}

void queryStudent(Student students[], int studentsLogicSize) {
  char RA[13];
  int studentIndex;

  do {
    printf(NORMAL "\nRegistro do Estudante para consulta (EX: 26.24.1354-0): ");
    gets(RA);
    fflush(stdin);

    if (strlen(RA) >= 1) {
      studentIndex = findStudentIndexByRA(students, studentsLogicSize, RA);

      if (studentIndex >= 0) {
        viewStudent(students[studentIndex]);
        printf("\n\n\n");
        getch();
        clearupline(8);
      } else {
        printf(YELLOW "[AVISO] O Registro de Estudante: \"%s\" não existe.\n" NORMAL, RA);
        getch();
        clearupline(3);
      }
    }
  } while(strlen(RA) >= 1);
}

void updateStudent(Student students[], int studentsLogicSize) {
  char RA[13];
  int studentIndex, index;

  do {
    printf(NORMAL "\nRegistro do Estudante para edição (EX: 26.24.1354-0): ");
    gets(RA);
    fflush(stdin);

    if (strlen(RA) >= 1) {
      studentIndex = findStudentIndexByRA(students, studentsLogicSize, RA);

      if (studentIndex >= 0) {
        printf("Nome: ");
        editInput(students[studentIndex].name);
        printf("\n\n\n");
        clearupline(8);
      } else {
        printf(YELLOW "[AVISO] O Registro de Estudante: \"%s\" não existe.\n" NORMAL, RA);
        getch();
        clearupline(3);
      }
    }
  } while(strlen(RA) >= 1);
}

void deleteStudent(Student students[], int &studentsLogicSize) {
  char RA[13];
  int studentIndex, index;

  do {
    printf(NORMAL "\nRegistro do Estudante para exclusão (EX: 26.24.1354-0): ");
    gets(RA);
    fflush(stdin);

    if (strlen(RA) >= 1) {
      studentIndex = findStudentIndexByRA(students, studentsLogicSize, RA);

      if (studentIndex >= 0) {
        viewStudent(students[studentIndex]);
        printf("\n\n\n");
        if (request("Você realmente deseja remover esse estudante?")) {
          for(index = studentIndex; index < studentsLogicSize; index++)
            students[index] = students[index + 1];
          studentsLogicSize--;
        }
        clearupline(11);
      } else {
        printf(YELLOW "[AVISO] O Registro de Estudante: \"%s\" não existe.\n" NORMAL, RA);
        getch();
        clearupline(3);
      }
    }
  } while(strlen(RA) >= 1);
}

void viewStudent(Student student) {
  int x = wherex();
  int y = wherey();

  int width = 65, height = 5;
  frame(width, height);

  gotoxy(x + (width / 2) - ((23 + strlen(student.RA)) / 2), y + (height / 2));
  printf("Registro do Estudante: %s", student.RA);

  gotoxy(x + (width / 2) - ((19 + strlen(student.name)) / 2), y + (height / 2) + 1);
  printf("Nome do Estudante: %s", student.name);
}

int findStudentIndexByRA(Student students[], int studentsLogicSize, char RA[13]) {
  int index = 0;

  while(index < studentsLogicSize && stricmp(students[index].RA, RA))
    index++;

  if (index < studentsLogicSize) {
    return index;
  }

  return -1;
}

void subjectsMenu(Subject subjects[], int &subjectsLogicSize) {
  int subjectsMenuOption;
  char subjectsOptions[4][CHAR_OPTION_FISIC_SIZE] = { "Cadastrar", "Consultar", "Alterar", "Excluir" };

  do {
    clrscr();
    subjectsMenuTitle();
    subjectsMenuOption = menu(subjectsOptions, 4);

    switch(subjectsMenuOption) {
      case 0:
        createSubject(subjects, subjectsLogicSize);
        break;
      case 1:
        querySubject(subjects, subjectsLogicSize);
        break;
      case 2:
        break;
      case 3:
        deleteSubject(subjects, subjectsLogicSize);
        break;
    }
  } while(subjectsMenuOption != -1);
}

void createSubject(Subject subjects[], int &subjectsLogicSize) {
  Subject newSubject;

  do {
    if (subjectsLogicSize < SUBJECTS_FISIC_SIZE) {
      printf(RED "\nDados do novo estudante de número " NORMAL "#%d\n", subjectsLogicSize + 1);

      printf("Nome da Disciplina (EX: ATP II): ");
      gets(newSubject.name);
      fflush(stdin);

      if (strlen(newSubject.name) >= 1) {
        printf("Código (EX: 210): ");
        scanf("%d", &newSubject.code);

        if (findSubjectIndexByCode(subjects, subjectsLogicSize, newSubject.code) >= 0) {
          printf(YELLOW "[AVISO] Código: \"%d\" já está cadastrado.\n" NORMAL, newSubject.code);
          getch();
          clearupline(5);
        } else {
          if (request("Você realmente deseja criar esse disciplina?")) {
            subjects[subjectsLogicSize] = newSubject;
            subjectsLogicSize++;
          }

          clearupline(7);
        }
      }
    } else { printf(RED "\n[ERROR] Não há mais capacidade de armazenamento para disciplinas." NORMAL); getch(); }
  } while(subjectsLogicSize < SUBJECTS_FISIC_SIZE && strlen(newSubject.name) >= 1);
}

void querySubject(Subject subjects[], int subjectsLogicSize) {
  int code, subjectIndex;

  do {
    printf(NORMAL "\nCódigo da disciplina para consulta (EX: 210) ou zero para voltar: ");
    scanf("%d", &code);

    if (code > 0) {
      subjectIndex = findSubjectIndexByCode(subjects, subjectsLogicSize, code);

      if (subjectIndex >= 0) {
        viewSubject(subjects[subjectIndex]);
        printf("\n\n\n");
        getch();
        clearupline(8);
      } else {
        printf(YELLOW "[AVISO] O Código da disciplina: \"%d\" não existe.\n" NORMAL, code);
        getch();
        clearupline(3);
      }
    }
  } while(code > 0);
}

void deleteSubject(Subject subjects[], int &subjectsLogicSize) {
  int code, subjectIndex, index;

  do {
    printf(NORMAL "\nCódigo da disciplina para exclusão (EX: 210) ou zero para voltar: ");
    scanf("%d", &code);

    if (code > 0) {
      subjectIndex = findSubjectIndexByCode(subjects, subjectsLogicSize, code);

      if (subjectIndex >= 0) {
        viewSubject(subjects[subjectIndex]);
        printf("\n\n\n");
        if (request("Você realmente deseja remover esse estudante?")) {
          for(index = subjectIndex; index < subjectsLogicSize; index++)
            subjects[index] = subjects[index + 1];
          subjectsLogicSize--;
        }
        clearupline(11);
      } else {
        printf(YELLOW "[AVISO] O Código da disciplina: \"%d\" não existe.\n" NORMAL, code);
        getch();
        clearupline(3);
      }
    }
  } while(code > 0);
}

void viewSubject(Subject subject) {
  int x = wherex();
  int y = wherey();

  int width = 50, height = 5;
  frame(width, height);

  gotoxy(x + (width / 2) - ((22 + 3) / 2), y + (height / 2));
  printf("Código da Disciplina: %d", subject.code);

  gotoxy(x + (width / 2) - ((20 + 3) / 2), y + (height / 2) + 1);
  printf("Nome da Disciplina: %s", subject.name);
}

int findSubjectIndexByCode(Subject subjects[], int subjectsLogicSize, int code) {
  int index = 0;

  while(index < subjectsLogicSize && subjects[index].code != code)
    index++;

  if (index < subjectsLogicSize) {
    return index;
  }

  return -1;
}

void studentSubjectsMenu(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize, Student students[], int studentsLogicSize, Subject subjects[], int subjectsLogicSize) {
  int studentSubjectsMenuOption;
  char studentSubjectsOptions[4][CHAR_OPTION_FISIC_SIZE] = { "Registrar", "Consultar", "Alterar", "Excluir" };

  do {
    clrscr();
    subjectsMenuTitle();
    studentSubjectsMenuOption = menu(studentSubjectsOptions, 4);

    switch(studentSubjectsMenuOption) {
        case 0:
          createStudentSubject(
            studentSubjects,
            studentSubjectsLogicSize,
            students,
            studentsLogicSize,
            subjects,
            subjectsLogicSize
          );
          break;
        case 1:
          queryStudentSubjects(
            studentSubjects,
            studentSubjectsLogicSize,
            students,
            studentsLogicSize,
            subjects,
            subjectsLogicSize
          );
          break;
        case 2:
          break;
        case 3:
          deleteStudentSubject(studentSubjects, studentSubjectsLogicSize);
          break;
      }
  } while(studentSubjectsMenuOption != -1);
}

void createStudentSubject(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize, Student students[], int studentsLogicSize, Subject subjects[], int subjectsLogicSize) {
  int studentIndex, subjectIndex;
  StudentSubjects newStudentSubject;

  do {
    if (studentSubjectsLogicSize < STUDENTS_SUBJECTS_FISIC_SIZE) {
      printf(NORMAL "\nRegistro do Estudante para o Registro (EX: 26.24.1354-0): ");
      gets(newStudentSubject.studentRA);
      fflush(stdin);

      if (strlen(newStudentSubject.studentRA) >= 1) {
        studentIndex = findStudentIndexByRA(students, studentsLogicSize, newStudentSubject.studentRA);

        if (studentIndex >= 0) {
          printf(NORMAL "\nCódigo da disciplina para o Registro (EX: 210): ");
          scanf("%d", &newStudentSubject.subjectCode);

          if (newStudentSubject.subjectCode > 0) {
            subjectIndex = findSubjectIndexByCode(subjects, subjectsLogicSize, newStudentSubject.subjectCode);

            if (subjectIndex >= 0) {
              printf(NORMAL "\nNota do estudante na Disciplina (EX: 8.0): ");
              scanf("%f", &newStudentSubject.grade);

              if (request("Você realmente deseja adicionar essa disciplina ao estudante?")) {
                studentSubjects[studentSubjectsLogicSize] = newStudentSubject;
                studentSubjectsLogicSize++;
              }
            } else {
              printf(YELLOW "[AVISO] O Código da disciplina: \"%d\" não existe.\n" NORMAL, newStudentSubject.subjectCode);
              getch();
              clearupline(3);
            }
          }
        } else {
          printf(YELLOW "[AVISO] O Registro de Estudante: \"%s\" não existe.\n" NORMAL, newStudentSubject.studentRA);
          getch();
          clearupline(3);
        }
      }
    } else { printf(RED "\n[ERROR] Não há mais capacidade de armazenamento para estudantes." NORMAL); getch(); }
  } while(studentSubjectsLogicSize < STUDENTS_SUBJECTS_FISIC_SIZE && strlen(newStudentSubject.studentRA) >= 1);
}

void queryStudentSubjects(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize, Student students[], int studentsLogicSize, Subject subjects[], int subjectsLogicSize) {
  char studentRA[13];
  int studentIndex, studentSubjectIndex, subjectCode;

  do {
    printf(NORMAL "\nRegistro do Estudante para consulta de suas materias (EX: 26.24.1354-0): ");
    gets(studentRA);
    fflush(stdin);

    if (strlen(studentRA) >= 1) {
      studentIndex = findStudentIndex(studentSubjects, studentSubjectsLogicSize, studentRA);

      if (studentIndex >= 0) {
        printf(NORMAL "\nCódigo da Disciplina (EX: 210): ");
        scanf("%d", &subjectCode);

        studentSubjectIndex = findStudentSubjectIndex(studentSubjects, studentSubjectsLogicSize, studentRA, subjectCode);

        if (studentSubjectIndex >= 0) {
          viewStudentSubject(studentSubjects[studentSubjectIndex], students[studentIndex], studentsLogicSize, subjects, subjectsLogicSize);
          getch();
        } else {
          printf(YELLOW "[AVISO] O Registro de Estudante: \"%s\" não tem a disciplina de código \"%d\" \n" NORMAL, studentRA, subjectCode);
          getch();
          clearupline(3);
        }
      } else {
        printf(YELLOW "[AVISO] O Registro de Estudante: \"%s\" não tem nenhuma disciplina registrada.\n" NORMAL, studentRA);
        getch();
        clearupline(3);
      }
    }
  } while(strlen(studentRA) >= 1);
}

void deleteStudentSubject(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize) {}

void viewStudentSubject(StudentSubjects studentSubjects, Student student, int studentsLogicSize, Subject subjects[], int subjectsLogicSize) {
  int subjectIndex = findSubjectIndexByCode(subjects, studentsLogicSize, studentSubjects.subjectCode);

  printf("RA: %s\t Nome: %s\n", studentSubjects.studentRA, student.name);
  printf("Disciplina: %d - %s\t Nota: %f\t Situação: Não sei ainda", studentSubjects.subjectCode, subjects[subjectIndex].name, studentSubjects.grade);
}

int findStudentIndex(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize, char studentRA[13]) {
  int index = 0;

  while(index < studentSubjectsLogicSize && stricmp(studentSubjects[index].studentRA, studentRA))
    index++;

  if (index < studentSubjectsLogicSize) {
    return index;
  }

  return -1;
}

int findStudentSubjectIndex(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize, char studentRA[13], int subjectCode) {
  int index = 0;

  while(index < studentSubjectsLogicSize && stricmp(studentSubjects[index].studentRA, studentRA) || studentSubjects[index].subjectCode != subjectCode)
    index++;

  if (index < studentSubjectsLogicSize) {
    return index;
  }

  return -1;
}

void reportsMenu() {
  int reportsMenuOption;
  char reportsOptions[7][CHAR_OPTION_FISIC_SIZE] = { 
    "Consultar Estudantes",
    "Consultar Disciplinas",
    "Consultar Disciplinas dos Estudantes",
    "Estudantes reprovados em 2 ou mais disciplinas",
    "Estudantes cujo nome começa com uma determinada letra",
    "Disciplinas que contêm um termo (palavra) específico.",
    "Disciplinas com média geral abaixo de 6.0"
  };

  do {
    clrscr();
    reportsMenuTitle();
    reportsMenuOption = menu(reportsOptions, 7);
  } while(reportsMenuOption != -1);
}

void configMenu(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize, Student students[], int &studentsLogicSize, Subject subjects[], int &subjectsLogicSize) {
  int configMenuOption, indexToSubject, indexToStudent;
  char configOptions[1][CHAR_OPTION_FISIC_SIZE] = { 
    "Inserir dados falsos."
  };

  do {
    clrscr();
    configMenuTitle();
    configMenuOption = menu(configOptions, 1);
    if (configMenuOption >= 0) {
      if (request("Você realmente deseja adicionar os dados falsos?")) {
        // add students
        strcpy(students[studentsLogicSize].RA, "26.24.1819-7");
        strcpy(students[studentsLogicSize++].name, "Andre Junior Da Silva Santos");

        strcpy(students[studentsLogicSize].RA, "26.23.1864-4");
        strcpy(students[studentsLogicSize++].name, "Andressa Felisberto Ferreira Diniz");

        strcpy(students[studentsLogicSize].RA, "26.24.1194-6");
        strcpy(students[studentsLogicSize++].name, "Andrey Pereira Miotto");

        strcpy(students[studentsLogicSize].RA, "26.20.1281-2");
        strcpy(students[studentsLogicSize++].name, "Arthur Torres De Souza");

        strcpy(students[studentsLogicSize].RA, "26.23.1792-9");
        strcpy(students[studentsLogicSize++].name, "Bhreno Gabriel Moraes Ferreira");

        strcpy(students[studentsLogicSize].RA, "26.24.1250-0");
        strcpy(students[studentsLogicSize++].name, "Bryan Dos Santos Cruz");

        strcpy(students[studentsLogicSize].RA, "26.24.1675-5");
        strcpy(students[studentsLogicSize++].name, "Caio Victor Rodrigues");

        strcpy(students[studentsLogicSize].RA, "26.24.1395-2");
        strcpy(students[studentsLogicSize++].name, "Caroliny Vitoria Martins");

        strcpy(students[studentsLogicSize].RA, "26.24.12438-0");
        strcpy(students[studentsLogicSize++].name, "Christiano Rodrigues Galindo De Oliveira");

        strcpy(students[studentsLogicSize].RA, "26.24.13167-7");
        strcpy(students[studentsLogicSize++].name, "Daniel Lopes Tavares");

        strcpy(students[studentsLogicSize].RA, "26.24.13051-5");
        strcpy(students[studentsLogicSize++].name, "Douglas MatiazzI Aguiar");

        strcpy(students[studentsLogicSize].RA, "26.24.11741-2");
        strcpy(students[studentsLogicSize++].name, "Erika Tanoue Tarumoto");

        strcpy(students[studentsLogicSize].RA, "26.24.14622-5");
        strcpy(students[studentsLogicSize++].name, "Felipe Alves Barbosa");

        strcpy(students[studentsLogicSize].RA, "26.24.13787-3");
        strcpy(students[studentsLogicSize++].name, "Felipe Furlan Santos");

        strcpy(students[studentsLogicSize].RA, "26.24.13540-5");
        strcpy(students[studentsLogicSize++].name, "Felipe Lima Santos");

        strcpy(students[studentsLogicSize].RA, "26.23.10104-3");
        strcpy(students[studentsLogicSize++].name, "Gabriel Da Silva Ferrari");

        strcpy(students[studentsLogicSize].RA, "26.24.13655-2");
        strcpy(students[studentsLogicSize++].name, "Gabriel De Carvalho Mariano");

        strcpy(students[studentsLogicSize].RA, "26.24.13515-7");
        strcpy(students[studentsLogicSize++].name, "Gabriel Delanhese Lorente");

        strcpy(students[studentsLogicSize].RA, "26.24.13574-6");
        strcpy(students[studentsLogicSize++].name, "Gabriel Oliveira Mora Da Silva");

        strcpy(students[studentsLogicSize].RA, "26.32.1300-0");
        strcpy(students[studentsLogicSize++].name, "Giovane Jose Capeloti");

        strcpy(students[studentsLogicSize].RA, "26.24.12136-3");
        strcpy(students[studentsLogicSize++].name, "Guilherme Henrique Santos Scarmagnani");

        strcpy(students[studentsLogicSize].RA, "26.32.0690-0");
        strcpy(students[studentsLogicSize++].name, "Gustavo Martins Goncalves");

        strcpy(students[studentsLogicSize].RA, "26.32.0667-4");
        strcpy(students[studentsLogicSize++].name, "Gustavo Scorpioni Mantovanelli Trevisanuto");

        strcpy(students[studentsLogicSize].RA, "26.24.13043-9");
        strcpy(students[studentsLogicSize++].name, "Heitor Franzo Justo");

        strcpy(students[studentsLogicSize].RA, "26.24.11962-8");
        strcpy(students[studentsLogicSize++].name, "Heitor Hayashi Ferrairo");

        strcpy(students[studentsLogicSize].RA, "26.24.12020-8");
        strcpy(students[studentsLogicSize++].name, "Humberto Alcantara Arruda");

        strcpy(students[studentsLogicSize].RA, "26.22.8386-0");
        strcpy(students[studentsLogicSize++].name, "Jessica Pinheiro Da Silva");

        strcpy(students[studentsLogicSize].RA, "26.24.11997-4");
        strcpy(students[studentsLogicSize++].name, "Joao Emanuel Santos Silva");

        strcpy(students[studentsLogicSize].RA, "26.24.11911-3");
        strcpy(students[studentsLogicSize++].name, "Jose Carlos Goncalves Neto");

        strcpy(students[studentsLogicSize].RA, "26.24.11733-0");
        strcpy(students[studentsLogicSize++].name, "Luane De Paula Kasprzak");

        strcpy(students[studentsLogicSize].RA, "26.24.13531-8");
        strcpy(students[studentsLogicSize++].name, "Lucas Augusto Correia Da Silva");

        strcpy(students[studentsLogicSize].RA, "26.24.12284-1");
        strcpy(students[studentsLogicSize++].name, "Lucas Filipe Camargo Giraldino");

        strcpy(students[studentsLogicSize].RA, "26.23.1687-2");
        strcpy(students[studentsLogicSize++].name, "Luigi Sardelari Scaliante");

        strcpy(students[studentsLogicSize].RA, "26.24.12128-8");
        strcpy(students[studentsLogicSize++].name, "Luis Gustavo Goncalves Silva");

        strcpy(students[studentsLogicSize].RA, "26.24.11083-5");
        strcpy(students[studentsLogicSize++].name, "Luiz Fabio Torres Justi");

        strcpy(students[studentsLogicSize].RA, "26.24.11768-8");
        strcpy(students[studentsLogicSize++].name, "Matheus Borges Gabriel");

        strcpy(students[studentsLogicSize].RA, "26.24.13868-5");
        strcpy(students[studentsLogicSize++].name, "Matheus CavalI De Paulo");

        strcpy(students[studentsLogicSize].RA, "26.32.1017-3");
        strcpy(students[studentsLogicSize++].name, "Matheus De Oliveira Lima");

        strcpy(students[studentsLogicSize].RA, "26.24.13264-5");
        strcpy(students[studentsLogicSize++].name, "Murilo Henrique Santos Da Silva");

        strcpy(students[studentsLogicSize].RA, "26.32.0282-1");
        strcpy(students[studentsLogicSize++].name, "Murilo Santana Alcantara");

        strcpy(students[studentsLogicSize].RA, "26.24.12594-1");
        strcpy(students[studentsLogicSize++].name, "Nicolas Lima Gomes Conehero");

        strcpy(students[studentsLogicSize].RA, "26.32.0983-0");
        strcpy(students[studentsLogicSize++].name, "Paulo Rodrigues Da Rocha");

        strcpy(students[studentsLogicSize].RA, "26.24.13116-6");
        strcpy(students[studentsLogicSize++].name, "Pedro Henrique Marteli Bolque");

        strcpy(students[studentsLogicSize].RA, "26.24.12942-4");
        strcpy(students[studentsLogicSize++].name, "Pedro Henrique Trevisi Strabelli");

        strcpy(students[studentsLogicSize].RA, "26.24.11920-5");
        strcpy(students[studentsLogicSize++].name, "Pedro Todesco Bezerra Rocha");

        strcpy(students[studentsLogicSize].RA, "26.32.0762-5");
        strcpy(students[studentsLogicSize++].name, "Rafael Fritschy Hain");

        strcpy(students[studentsLogicSize].RA, "26.24.13361-6");
        strcpy(students[studentsLogicSize++].name, "Rafael Lorente Padovan");

        strcpy(students[studentsLogicSize].RA, "26.24.11601-4");
        strcpy(students[studentsLogicSize++].name, "Renan Gustavo Santos Silva");

        strcpy(students[studentsLogicSize].RA, "26.32.0681-5");
        strcpy(students[studentsLogicSize++].name, "Renan Henrique Pereira Lira");

        strcpy(students[studentsLogicSize].RA, "26.24.1295-0");
        strcpy(students[studentsLogicSize++].name, "Rodolpho Moreira Coller");

        strcpy(students[studentsLogicSize].RA, "26.23.1031-7");
        strcpy(students[studentsLogicSize++].name, "Tatiane Camille Terencio Benedito");

        strcpy(students[studentsLogicSize].RA, "26.24.1283-7");
        strcpy(students[studentsLogicSize++].name, "Thiago Marques Cristino");

        strcpy(students[studentsLogicSize].RA, "26.24.1388-8");
        strcpy(students[studentsLogicSize++].name, "Victor Eiji Leao Sassaki");

        strcpy(students[studentsLogicSize].RA, "26.24.1310-0");
        strcpy(students[studentsLogicSize++].name, "Vitor Micael De Araujo");

        strcpy(students[studentsLogicSize].RA, "26.23.2073-8");
        strcpy(students[studentsLogicSize++].name, "Vitor Trevelin Silva");

        strcpy(students[studentsLogicSize].RA, "26.23.0460-0");
        strcpy(students[studentsLogicSize++].name, "Yan Prioste Oliveira");

        // add subjects
        subjects[subjectsLogicSize].code = 210;
        strcpy(subjects[subjectsLogicSize++].name, "Algoritmos e técnicas de programação II");

        subjects[subjectsLogicSize].code = 110;
        strcpy(subjects[subjectsLogicSize++].name, "Ambientes de programação II");

        subjects[subjectsLogicSize].code = 250;
        strcpy(subjects[subjectsLogicSize++].name, "Arquitetura de computadores");

        subjects[subjectsLogicSize].code = 300;
        strcpy(subjects[subjectsLogicSize++].name, "Ciência de dados");

        subjects[subjectsLogicSize].code = 220;
        strcpy(subjects[subjectsLogicSize++].name, "Fundamentos de sistemas de informação");

        subjects[subjectsLogicSize].code = 443;
        strcpy(subjects[subjectsLogicSize++].name, "Gestão financeira");

        subjects[subjectsLogicSize].code = 341;
        strcpy(subjects[subjectsLogicSize++].name, "Sala do coordenador");

        for (indexToSubject = 0; indexToSubject < subjectsLogicSize; indexToSubject++)
          for (indexToStudent = 0; indexToStudent < studentsLogicSize; indexToStudent++) {
            printf("%s\n", students[indexToStudent].RA);
            getch();
            strcpy(studentSubjects[studentSubjectsLogicSize].studentRA, students[indexToStudent].RA);
            studentSubjects[studentSubjectsLogicSize].subjectCode = subjects[indexToSubject].code;
            // studentSubjects[studentSubjectsLogicSize].grade = rand() % 10;
/*             studentSubjectsLogicSize++; */
          }

        configMenuOption = -1;
      }
    }
  } while(configMenuOption != -1);
}

int menu(char options[][CHAR_OPTION_FISIC_SIZE], int quantityOfOptions) {
  int selectedOption = 0;
  int action;

  do {
    printf("\e[?25l"); // hide cursor
    clearupline(quantityOfOptions);

    for(int index = 0; index < quantityOfOptions; index++) {

      if (index == selectedOption) {
        textcolor(15);
        printf("%c %s\n", POINTER, options[selectedOption]);
        textcolor(8);
      } else {
        textcolor(8);
        printf("  %s\n", options[index]);
        textcolor(15);
      }
    }

    action = getch();
    
    switch(action) {
      case ARROW_UP_KEY_NUMBER:
        if (selectedOption + 1 < quantityOfOptions)
          selectedOption++;
        break;
      case ARROW_DOWN_KEY_NUMBER:
        if (selectedOption > 0)
          selectedOption--;
      break;
    }

  } while(action != ESC_KEY_NUMBER && action != ENTER_KEY_NUMBER);

  printf("\e[?25h"); // show cursor
  textcolor(15);

  if (action != 27) {
    return selectedOption;
  }

  return -1;
}

void principalMenuTitle() {
  clrscr();
  textcolor(2);
  printf("                                                            $$\\                                              $$\\               \n");
  printf("                                                            \\__|                                             $$ |              \n");
  printf(" $$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$\\  $$$$$$$\\   $$$$$$$\\ $$\\  $$$$$$\\  $$$$$$\\$$$$\\   $$$$$$\\  $$$$$$$\\ $$$$$$\\    $$$$$$\\  \n");
  printf("$$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  _____|$$ | \\____$$\\ $$  _$$  _$$\\ $$  __$$\\ $$  __$$\\\\_$$  _|  $$  __$$\\ \n");
  printf("$$ /  $$ |$$$$$$$$ |$$ |  \\__|$$$$$$$$ |$$ |  $$ |$$ /      $$ | $$$$$$$ |$$ / $$ / $$ |$$$$$$$$ |$$ |  $$ | $$ |    $$ /  $$ |\n");
  printf("$$ |  $$ |$$   ____|$$ |      $$   ____|$$ |  $$ |$$ |      $$ |$$  __$$ |$$ | $$ | $$ |$$   ____|$$ |  $$ | $$ |$$\\ $$ |  $$ |\n");
  printf("\\$$$$$$$ |\\$$$$$$$\\ $$ |      \\$$$$$$$\\ $$ |  $$ |\\$$$$$$$\\ $$ |\\$$$$$$$ |$$ | $$ | $$ |\\$$$$$$$\\ $$ |  $$ | \\$$$$  |\\$$$$$$  |\n");
  printf(" \\____$$ | \\_______|\\__|       \\_______|\\__|  \\__| \\_______|\\__| \\_______|\\__| \\__| \\__| \\_______|\\__|  \\__|  \\____/  \\______/ \n");
  printf("$$\\   $$ |                                                                                                                     \n");
  printf("\\$$$$$$  |                                                                                                                     \n");
  printf(" \\______|                                                                                                                     \n\n\n\n\n\n\n");
  textcolor(15);
}

void studentsMenuTitle() {
  clrscr();
  textcolor(2);
  printf("          $$\\                                          \n");
  printf("          $$ |                                         \n");
  printf(" $$$$$$\\  $$ |$$\\   $$\\ $$$$$$$\\   $$$$$$\\   $$$$$$$\\ \n");
  printf(" \\____$$\\ $$ |$$ |  $$ |$$  __$$\\ $$  __$$\\ $$  _____|\n");
  printf(" $$$$$$$ |$$ |$$ |  $$ |$$ |  $$ |$$ /  $$ |\\$$$$$$\\  \n");
  printf("$$  __$$ |$$ |$$ |  $$ |$$ |  $$ |$$ |  $$ | \\____$$\\ \n");
  printf("\\$$$$$$$ |$$ |\\$$$$$$  |$$ |  $$ |\\$$$$$$  |$$$$$$$  |\n");
  printf(" \\_______|\\__| \\______/ \\__|  \\__| \\______/ \\_______/ \n\n\n\n\n\n");
  textcolor(15);
}

void subjectsMenuTitle() {
  clrscr();
  textcolor(2);
  printf("$$$$$$$\\  $$\\                     $$\\           $$\\ $$\\                               \n");
  printf("$$  __$$\\ \\__|                    \\__|          $$ |\\__|                              \n");
  printf("$$ |  $$ |$$\\  $$$$$$$\\  $$$$$$$\\ $$\\  $$$$$$\\  $$ |$$\\ $$$$$$$\\   $$$$$$\\   $$$$$$$\\ \n");
  printf("$$ |  $$ |$$ |$$  _____|$$  _____|$$ |$$  __$$\\ $$ |$$ |$$  __$$\\  \\____$$\\ $$  _____|\n");
  printf("$$ |  $$ |$$ |\\$$$$$$\\  $$ /      $$ |$$ /  $$ |$$ |$$ |$$ |  $$ | $$$$$$$ |\\$$$$$$\\  \n");
  printf("$$ |  $$ |$$ | \\____$$\\ $$ |      $$ |$$ |  $$ |$$ |$$ |$$ |  $$ |$$  __$$ | \\____$$\\ \n");
  printf("$$$$$$$  |$$ |$$$$$$$  |\\$$$$$$$\\ $$ |$$$$$$$  |$$ |$$ |$$ |  $$ |\\$$$$$$$ |$$$$$$$  |\n");
  printf("\\_______/ \\__|\\_______/  \\_______|\\__|$$  ____/ \\__|\\__|\\__|  \\__| \\_______|\\_______/ \n");
  printf("                                      $$ |                                            \n");
  printf("                                      $$ |                                            \n");
  printf("                                      \\__|                                            \n\n\n");
  textcolor(15);
}

void reportsMenuTitle() {
  clrscr();
  textcolor(2);
  printf("$$$$$$$\\            $$\\            $$\\                         $$\\                     \n");
  printf("$$  __$$\\           $$ |           $$ |                        \\__|                    \n");
  printf("$$ |  $$ | $$$$$$\\  $$ | $$$$$$\\ $$$$$$\\    $$$$$$\\   $$$$$$\\  $$\\  $$$$$$\\   $$$$$$$\\ \n");
  printf("$$$$$$$  |$$  __$$\\ $$ | \\____$$\\\\_$$  _|  $$  __$$\\ $$  __$$\\ $$ |$$  __$$\\ $$  _____|\n");
  printf("$$  __$$< $$$$$$$$ |$$ | $$$$$$$ | $$ |    $$ /  $$ |$$ |  \\__|$$ |$$ /  $$ |\\$$$$$$\\  \n");
  printf("$$ |  $$ |$$   ____|$$ |$$  __$$ | $$ |$$\\ $$ |  $$ |$$ |      $$ |$$ |  $$ | \\____$$\\ \n");
  printf("$$ |  $$ |\\$$$$$$$\\ $$ |\\$$$$$$$ | \\$$$$  |\\$$$$$$  |$$ |      $$ |\\$$$$$$  |$$$$$$$  |\n");
  printf("\\__|  \\__| \\_______|\\__| \\_______|  \\____/  \\______/ \\__|      \\__| \\______/ \\_______/ \n\n\n\n\n\n\n\n\n");
  textcolor(15);
}

void configMenuTitle() {
  clrscr();
  textcolor(2);
  printf("                               $$$$$$\\  $$\\           \n");
  printf("                              $$  __$$\\ \\__|          \n");
  printf(" $$$$$$$\\  $$$$$$\\  $$$$$$$\\  $$ /  \\__|$$\\  $$$$$$\\  \n");
  printf("$$  _____|$$  __$$\\ $$  __$$\\ $$$$\\     $$ |$$  __$$\\ \n");
  printf("$$ /      $$ /  $$ |$$ |  $$ |$$  _|    $$ |$$ /  $$ |\n");
  printf("$$ |      $$ |  $$ |$$ |  $$ |$$ |      $$ |$$ |  $$ |\n");
  printf("\\$$$$$$$\\ \\$$$$$$  |$$ |  $$ |$$ |      $$ |\\$$$$$$$ |\n");
  printf(" \\_______| \\______/ \\__|  \\__|\\__|      \\__| \\____$$ |\n");
  printf("                                            $$\\   $$ |\n");
  printf("                                            \\$$$$$$  |\n");
  printf("                                             \\______/ \n\n\n");
  textcolor(15);
}

int request(const char message[]) {
  printf("\n%s" GREEN "\n[S] Sim" RED " [N] Não\n" NORMAL, message);

  int answer;

  do {
    answer = toupper(getch());
  } while(answer != 'S' && answer != 'N');

  if (answer == 'S') {
    return 1;
  }

   return 0;
}

void clearupline(int quantityOfUpLines) {
  for(int index = 0; index < quantityOfUpLines; index++) {
    printf("\x1b[1F"); // move line
    printf("\33[2K\r"); // clear line
  }
}

void editInput(char string[]) {
  int stringLen = strlen(string), action;

  printf("%s", string);

  do {
    action = getch();

    switch(action) {
      case BACKSPACE_KEY_NUMBER:
        if (stringLen > 0) {
          stringLen--;
          printf("\b \b"); // back cursor and delete
        }
        break;
      default:
        putchar(action);
        string[stringLen] = action;
        stringLen++;
    }
  } while(action != ENTER_KEY_NUMBER);

  string[stringLen] = '\0';
}

void frame(int width, int height) {
  int index;
  int x = wherex();
  int y = wherey();

  // arc left top
  gotoxy(x, y);
  printf("%s", ARC_DOWN_RIGHT);

  // arc right top
  gotoxy(width, y);
  printf("%s", ARC_DOWN_LEFT);

  // arc right bottom
  gotoxy(width, height + y);
  printf("%s", ARC_UP_LEFT);

  // arc left bottom
  gotoxy(x, height + y);
  printf("%s", ARC_UP_RIGHT);

  // top line
  for (index = x + 1; index < width + x - 1; index++) {
    gotoxy(index, y);
    printf("%s", HORIZONTAL_LINE);
  }

  // bottom line
  for (index = x + 1; index < width + x - 1; index++) {
    gotoxy(index, y + height);
    printf("%s", HORIZONTAL_LINE);
  }

  // left line
  for (index = y + 1; index < height + y; index++) {
    gotoxy(x, index);
    printf("%s", VERTICAL_LINE);
  }

  // right line
  for (index = y + 1; index < height + y; index++) {
    gotoxy(width, index);
    printf("%s", VERTICAL_LINE);
  }
}