#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

#include "./lib/meuconio.h"

#include "./headers/figures.h"
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

#define OPTIONS_FISIC_SIZE 3
#define CHAR_OPTION_FISIC_SIZE 300

#define STUDENTS_FISIC_SIZE 2

#define NORMAL  "\x1B[0m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define MAGENTA  "\x1B[35m"
#define WHITE   "\x1B[37m"

void studentsMenu(Student students[], int &studentsLogicSize);
void createStudent(Student students[], int &studentsLogicSize);

void subjectsMenu();
void reportsMenu();
void subjectsMenuTitle();
void studentsMenuTitle();
void reportsMenuTitle();
void principalMenuTitle();
int menu(char options[][CHAR_OPTION_FISIC_SIZE], int studentsLogicSize);

int request(char message[80]);

int main() {
  SetConsoleOutputCP(CP_UTF8);

  int principalMenuOption;
  char principalOptions[OPTIONS_FISIC_SIZE][CHAR_OPTION_FISIC_SIZE] = { "Alunos", "Disciplinas", "Relatórios" };

  Student students[STUDENTS_FISIC_SIZE];
  int studentsLogicSize = 0;

  do {
    clrscr();
    principalMenuTitle();
    principalMenuOption = menu(principalOptions, OPTIONS_FISIC_SIZE);

    switch(principalMenuOption) {
      case 0:
        studentsMenu(students, studentsLogicSize);
        break;
      case 1:
        subjectsMenu();
        break;
      case 2:
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
    }
  } while(studentsMenuOption != -1);
}

void createStudent(Student students[], int &studentsLogicSize) {
  Student newStudent;

  do {
    if (studentsLogicSize < STUDENTS_FISIC_SIZE) {
      printf(RED "\nDados do novo aluno de número " NORMAL "#%d\n", studentsLogicSize + 1);

      printf("Nome: ");
      fgets(newStudent.name, 80, stdin);
      fflush(stdin);

      if (strlen(newStudent.name) > 1) {
        printf("Registro do Aluno (EX: 26.24.1354-0): ");
        fgets(newStudent.RA, 13, stdin);
        fflush(stdin);

        if (request("Você realmente deseja criar esse aluno?")) {
          students[studentsLogicSize] = newStudent;
          studentsLogicSize++;
        }
      }
    } else { printf(RED "\nNão há mais capacidade de armazenamento para alunos." NORMAL); getch(); }
  } while(studentsLogicSize < STUDENTS_FISIC_SIZE && strlen(newStudent.name) > 1);
}

void subjectsMenu() {
  int subjectsMenuOption;
  char subjectsOptions[4][CHAR_OPTION_FISIC_SIZE] = { "Cadastrar", "Consultar", "Alterar", "Excluir" };

  do {
    clrscr();
    subjectsMenuTitle();
    subjectsMenuOption = menu(subjectsOptions, 4);
  } while(subjectsMenuOption != -1);
}

void reportsMenu() {
  int reportsMenuOption;
  char reportsOptions[4][CHAR_OPTION_FISIC_SIZE] = { "Cadastrar", "Consultar", "Alterar", "Excluir" };

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
    
    for(int index = 0; index < quantityOfOptions; index++) {
      printf("\x1b[1F"); // move line
      printf("\x1b[2K"); // clear line
    }

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