#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include "./lib/meuconio.h"

#include "./headers/figures.h"
#include "./headers/actions.h"

struct Student {
  int RA;
  char name[80];
};

struct Subject {
  int code;
  char name[80];
};

struct StudentSubjects {
  int studentRA;
  int subjectCode;
  float grade;
};

#define OPTIONS_FISIC_SIZE 3
#define CHAR_OPTION_FISIC_SIZE 300

void students();
void subjects();
void reports();
void subjectsMenuTitle();
void studentsMenuTitle();
void reportsMenuTitle();
void principalMenuTitle();
int menu(char options[][CHAR_OPTION_FISIC_SIZE], int quantityOfOptions);

int main() {
  SetConsoleOutputCP(CP_UTF8);

  int principalMenuOption;
  char principalOptions[OPTIONS_FISIC_SIZE][CHAR_OPTION_FISIC_SIZE] = { "Alunos", "Disciplinas", "Relatórios" };

  do {
    clrscr();
    principalMenuTitle();
    principalMenuOption = menu(principalOptions, OPTIONS_FISIC_SIZE);

    switch(principalMenuOption) {
      case 0:
        students();
        break;
      case 1:
        subjects();
        break;
      case 2:
        reports();
        break;
    }
  } while(principalMenuOption != -1);
}

void students() {
  int studentsMenuOption;
  char studentsOptions[4][CHAR_OPTION_FISIC_SIZE] = { "Cadastrar", "Consultar", "Alterar", "Excluir" };

  do {
    clrscr();
    studentsMenuTitle();
    studentsMenuOption = menu(studentsOptions, 4);
  } while(studentsMenuOption != -1);
}

void subjects() {
  int subjectsMenuOption;
  char subjectsOptions[4][CHAR_OPTION_FISIC_SIZE] = { "Cadastrar", "Consultar", "Alterar", "Excluir" };

  do {
    clrscr();
    subjectsMenuTitle();
    subjectsMenuOption = menu(subjectsOptions, 4);
  } while(subjectsMenuOption != -1);
}

void reports() {
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