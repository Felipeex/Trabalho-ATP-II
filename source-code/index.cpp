// Default
#include <stdio.h>
#include <windows.h>
#include <ctype.h>

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
#define OPTIONS_FISIC_SIZE 4
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
void queryStudent(Student students[], int &studentsLogicSize);
void deleteStudent(Student students[], int &studentsLogicSize);
void viewStudent(Student students);
int findStudentIndexByRA(Student students[], int studentsLogicSize, char RA[13]);

// Subject
void subjectsMenu(Subject subjects[], int &subjectsLogicSize);
void createSubject(Subject subjects[], int &subjectsLogicSize);
void querySubject(Subject subjects[], int &subjectsLogicSize);
void deleteSubject(Subject subjects[], int &subjectsLogicSize);
void viewSubject(Subject subjects);
int findSubjectIndexByCode(Subject subjects[], int subjectsLogicSize, int code);

// StudentSubjects
void studentSubjectsMenu(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize);

// Menu
void reportsMenu();
void subjectsMenuTitle();
void studentsMenuTitle();
void reportsMenuTitle();
void principalMenuTitle();
int menu(char options[][CHAR_OPTION_FISIC_SIZE], int studentsLogicSize);

// Others
int request(char message[80]);
void clearupline(int quantityOfUpLines);
void editInput(char string[]);
void frame(int width, int height);

int main() {
  SetConsoleOutputCP(CP_UTF8);

  int principalMenuOption;
  char principalOptions[OPTIONS_FISIC_SIZE][CHAR_OPTION_FISIC_SIZE] = { "Alunos", "Disciplinas", "Disciplinas dos Alunos", "Relatórios" };

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
        studentSubjectsMenu(studentSubjects, studentSubjectsLogicSize);
        break;
      case 4:
        reportsMenu();
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
        editInput("Felipe");
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
      printf(RED "\nDados do novo aluno de número " NORMAL "#%d\n", studentsLogicSize + 1);

      printf("Nome: ");
      gets(newStudent.name);
      fflush(stdin);

      if (strlen(newStudent.name) >= 1) {
        printf("Registro do Aluno (EX: 26.24.1354-0): ");
        gets(newStudent.RA);
        fflush(stdin);

        if (findStudentIndexByRA(students, studentsLogicSize, newStudent.RA) >= 0) {
          printf(YELLOW "[AVISO] Registro de Aluno: \"%s\" já está cadastrado.\n" NORMAL, newStudent.RA);
          getch();
          clearupline(5);
        } else {
          if (request("Você realmente deseja criar esse aluno?")) {
            students[studentsLogicSize] = newStudent;
            studentsLogicSize++;
          }

          clearupline(7);
        }

      }
    } else { printf(RED "\n[ERROR] Não há mais capacidade de armazenamento para alunos." NORMAL); getch(); }
  } while(studentsLogicSize < STUDENTS_FISIC_SIZE && strlen(newStudent.name) >= 1);
}

void queryStudent(Student students[], int &studentsLogicSize) {
  char RA[13];
  int studentIndex;

  do {
    printf(NORMAL "\nRegistro do Aluno para consulta (EX: 26.24.1354-0): ");
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
        printf(YELLOW "[AVISO] O Registro de Aluno: \"%s\" não existe.\n" NORMAL, RA);
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
    printf(NORMAL "\nRegistro do Aluno para exclusão (EX: 26.24.1354-0): ");
    gets(RA);
    fflush(stdin);

    if (strlen(RA) >= 1) {
      studentIndex = findStudentIndexByRA(students, studentsLogicSize, RA);

      if (studentIndex >= 0) {
        viewStudent(students[studentIndex]);
        printf("\n\n\n");
        if (request("Você realmente deseja remover esse aluno?")) {
          for(index = studentIndex; index < studentsLogicSize; index++)
            students[index] = students[index + 1];
          studentsLogicSize--;
        }
        clearupline(11);
      } else {
        printf(YELLOW "[AVISO] O Registro de Aluno: \"%s\" não existe.\n" NORMAL, RA);
        getch();
        clearupline(3);
      }
    }
  } while(strlen(RA) >= 1);
}

void viewStudent(Student student) {
  int x = wherex();
  int y = wherey();

  int width = 50, height = 5;
  frame(width, height);

  gotoxy(x + (width / 2) - ((19 + strlen(student.RA)) / 2), y + (height / 2));
  printf("Registro do Aluno: %s", student.RA);

  gotoxy(x + (width / 2) - ((15 + strlen(student.name)) / 2), y + (height / 2) + 1);
  printf("Nome do Aluno: %s", student.name);
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
      printf(RED "\nDados do novo aluno de número " NORMAL "#%d\n", subjectsLogicSize + 1);

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
  } while(subjectsLogicSize < STUDENTS_FISIC_SIZE && strlen(newSubject.name) >= 1);
}

void querySubject(Subject subjects[], int &subjectsLogicSize) {
  int code, studentIndex;

  do {
    printf(NORMAL "\nCódigo da disciplina para consulta (EX: 210) ou zero para voltar: ");
    scanf("%d", &code);

    if (code > 0) {
      studentIndex = findSubjectIndexByCode(subjects, subjectsLogicSize, code);

      if (studentIndex >= 0) {
        viewSubject(subjects[studentIndex]);
        printf("\n\n\n");
        getch();
        clearupline(8);
      } else {
        printf(YELLOW "[AVISO] O Registro de Aluno: \"%d\" não existe.\n" NORMAL, code);
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
        if (request("Você realmente deseja remover esse aluno?")) {
          for(index = subjectIndex; index < subjectsLogicSize; index++)
            subjects[index] = subjects[index + 1];
          subjectsLogicSize--;
        }
        clearupline(11);
      } else {
        printf(YELLOW "[AVISO] O Registro de Aluno: \"%d\" não existe.\n" NORMAL, code);
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

void studentSubjectsMenu(StudentSubjects studentSubjects[], int &studentSubjectsLogicSize) {
  int reportsMenuOption;
  char reportsOptions[4][CHAR_OPTION_FISIC_SIZE] = { "Registrar", "Consultar", "Alterar", "Excluir" };

  do {
    clrscr();
    subjectsMenuTitle();
    reportsMenuOption = menu(reportsOptions, 4);
  } while(reportsMenuOption != -1);
}

void reportsMenu() {
  int reportsMenuOption;
  char reportsOptions[4][CHAR_OPTION_FISIC_SIZE] = { "Todos os Alunos", "Disciplinas com média geral abaixo de 6.0" };

  do {
    clrscr();
    reportsMenuTitle();
    reportsMenuOption = menu(reportsOptions, 4);
  } while(reportsMenuOption != -1);
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

  } while(action != 27 && action != 13);

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
  printf(" \\______|                                                                                                                     \n\n\n\n\n");
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
  printf("\\__|  \\__| \\_______|\\__| \\_______|  \\____/  \\______/ \\__|      \\__| \\______/ \\_______/ \n\n\n\n\n\n");
  textcolor(15);
}

int request(char message[80]) {
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

  do {
    printf("\33[2K\r"); // clear line
    for(int index = 0; index < stringLen; index++)
      printf("%c", string[index]);

    action = getch();

    switch(action) {
      case BACKSPACE_KEY_NUMBER:
        stringLen--;
        break;
      case 97:
        strcat(string, "a");
        break;
    }
  } while(action != 13);
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