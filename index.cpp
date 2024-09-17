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