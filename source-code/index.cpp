#include <stdio.h>
#include <windows.h>
#include <conio.h>

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

void principalMenuTitle();
int menu(char options[][300], int quantityOfOptions);
void textcolor(int newcolor);

int main() {
  SetConsoleOutputCP(CP_UTF8);

  char principalOptions[3][300] = { "Alunos", "Disciplinas", "Relatório" };
  int principalMenuOption = menu(principalOptions, 3);

  char subOptions[3][300] = { "Cadastrar", "Alterar", "Excluir" };
  int subMenuOption;

  switch(principalMenuOption) {
    case 0:
      printf("Selecionou Alunos");
      menu(subOptions, 3);
      break;
    case 1:
      printf("Selecionou Disciplinas");
      menu(subOptions, 3);
      break;
    case 2:
      printf("Selecionou Relatório");
      break;
  }
}

int menu(char options[][300], int quantityOfOptions) {
  int selectedOption = 0;
  int action;

  do {
    printf("\e[?25l"); // hide cursor
    system("cls");
    
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
      case ARROW_UP_NUMBER:
        if (selectedOption + 1 < quantityOfOptions)
          selectedOption++;
        break;
      case ARROW_DOWN_NUMBER:
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
  system("cls");
  textcolor(8);
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
  printf(" \\______|                                                                                                                     \n\n");
  textcolor(15);
}

void textcolor(int newcolor) {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (csbi.wAttributes & 0xf0) | newcolor);
}