#define BUFLEN 32
typedef struct RecordStruct {
    char name[BUFLEN];
    int id;
    struct RecordStruct *next;
} Record;

int insertStudent(Record **list, char *name, int id);
int deleteStudent(Record **list, int id);
int getStudent(Record *list, int id, char *buffer);
int countStudents(Record *list);
int printStudents(Record *list);