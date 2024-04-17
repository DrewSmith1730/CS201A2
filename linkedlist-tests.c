#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.asmith16.h"

int compareLists(Record *list, Record *expected, int count) {
  Record *curr;
  int i, fail;

  fail = 0;

  i = 0;
  curr = list;
  while (curr != NULL && i < count) {
    if (curr->id != expected[i].id) {
      printf("ERROR: mismatch in id: %d (expected %d)\n", curr->id, expected[i].id);
      fail = 1;
    }
    if ( strcmp(curr->name, expected[i].name) ) {
      printf("ERROR: mismatch in name: '%s' (expected '%s')\n", curr->name, expected[i].name);
      fail = 1;
    }

    curr = curr->next;
    ++i;
  }

  if (curr == NULL && i != count) {
    printf("ERROR: list is too short; length = %d (expected %d)\n", i, count);
    fail = 1;
  }

  if (curr != NULL && i == count) {
    printf("ERROR: list is too long; (expected length %d)\n", count);
    fail = 1;
  }

  if (fail == 0) {
    printf("pass compare: lists match\n");
  }

  return fail;
}

//------------------------------------------------------

int testInsert(char *testName, Record **list, char *name, int id, Record *expList, int expCount, int exprc) {
  int rc, fail;

  fail = 0;

  rc = insertStudent(list, name, id);
  if (rc != exprc) {
    printf("FAIL test %s: expected return code %d; got %d\n", testName, exprc, rc);
    fail = 1;
  } else {
    rc = compareLists(*list, expList, expCount);
    if (rc != 0) {
      fail = 1;
      printf("FAIL test %s: list comparison fails\n", testName);
    } else {
      printf("test %s: passed\n", testName);
    }
  }

  return fail;
}

//------------------------------------------------------

int testDelete(char *testName, Record **list, int id, Record *expList, int expCount, int exprc) {
  int rc, fail;

  fail = 0;

  rc = deleteStudent(list, id);
  if (rc != exprc) {
    printf("FAIL test %s: expected return code %d; got %d\n", testName, exprc, rc);
    fail = 1;
  } else {
    rc = compareLists(*list, expList, expCount);
    if (rc != 0) {
      fail = 1;
      printf("FAIL test %s: list comparison fails\n", testName);
    } else {
      printf("test %s: passed\n", testName);
    }
  }

  return fail;
}

//------------------------------------------------------

int getTest(char *testName, Record *list, char *name, int id, int exprc) {
  int rc, fail;
  char buffer[BUFLEN];

  fail = 0;

  rc = getStudent(list, id, buffer);
  if (rc != exprc) {
    printf("FAIL test %s: expected return code %d; got %d\n", testName, exprc, rc);
    fail = 1;
  } else {
    if (exprc == 0) {
      if ( strcmp(buffer, name) ) {
        printf("FAIL test %s: expected to get '%s' for id %d\n", testName, name, id);
        fail = 1;
      }
    }
  }

  if ( fail == 0 ) {
    printf("test %s: passed\n", testName);
  }

  return fail;
}

//------------------------------------------------------

int testCount(char *testName, Record *list, int expval) {
  int c;

  c = countStudents(list);
  if (c != expval) {
    printf("FAIL test %s: expected count %d; got %d\n", testName, expval, c);
    return 1;
  }

  printf("test %s: passed\n", testName);
  return 0;
}

//------------------------------------------------------

int main() {
  Record *list;
  int rc, failCount;

  list = NULL;
  failCount = 0;

  Record explist1[] = { {"Harriet", 56, NULL} };
  rc = testInsert("I1", &list, "Harriet", 56, explist1, 1, 0);
  failCount = failCount + rc;

  Record explist2[] = { {"Thomas", 6, NULL}, {"Harriet", 56, NULL} };
  rc = testInsert("I2", &list, "Thomas", 6, explist2, 2, 0);
  failCount = failCount + rc;

  Record explist3[] = { {"Thomas", 6, NULL}, {"Harriet", 56, NULL}, {"Elizabeth", 67, NULL} };
  rc = testInsert("I3", &list, "Elizabeth", 67, explist3, 3, 0);
  failCount = failCount + rc;

  Record explist4[] = { {"Thomas", 6, NULL}, {"Harriet", 56, NULL}, {"Henry", 60, NULL}, {"Elizabeth", 67, NULL} };
  rc = testInsert("I4", &list, "Henry", 60, explist4, 4, 0);
  failCount = failCount + rc;

  Record explist5[] = { {"Thomas", 6, NULL}, {"Harriet", 56, NULL}, {"Henry", 60, NULL}, {"Elizabeth", 67, NULL}, {"Roxanne", 69, NULL} };
  rc = testInsert("I5", &list, "Roxanne", 69, explist5, 5, 0);
  failCount = failCount + rc;

  rc = testInsert("I6", &list, "Tony", 6, explist5, 5, 1);
  failCount = failCount + rc;

  rc = testInsert("I7", &list, NULL, 6, explist5, 5, 1);
  failCount = failCount + rc;

  rc = testInsert("I8", &list, "John", -6, explist5, 5, 1);
  failCount = failCount + rc;

  printStudents(list);

  rc = testDelete("D1", &list, 80, explist5, 5, 1);
  failCount = failCount + rc;

  Record explist6[] = { {"Harriet", 56, NULL}, {"Henry", 60, NULL}, {"Elizabeth", 67, NULL}, {"Roxanne", 69, NULL} };
  rc = testDelete("D2", &list, 6, explist6, 4, 0);
  failCount = failCount + rc;

  Record explist7[] = { {"Harriet", 56, NULL}, {"Henry", 60, NULL}, {"Elizabeth", 67, NULL} };
  rc = testDelete("D3", &list, 69, explist7, 3, 0);
  failCount = failCount + rc;

  Record explist8[] = { {"Harriet", 56, NULL}, {"Henry", 60, NULL}, {"Elizabeth", 67, NULL}, {"John", 80, NULL} };
  rc = testInsert("I9", &list, "John", 80, explist8, 4, 0);
  failCount = failCount + rc;

  Record explist9[] = { {"Anna", 2, NULL}, {"Harriet", 56, NULL}, {"Henry", 60, NULL}, {"Elizabeth", 67, NULL}, {"John", 80, NULL} };
  rc = testInsert("I10", &list, "Anna", 2, explist9, 5, 0);
  failCount = failCount + rc;

  printStudents(list);

  rc = getTest("F1", list, "John", 80, 0);
  failCount = failCount + rc;
  rc = getTest("F2", list, NULL, 100, 1);
  failCount = failCount + rc;
  rc = getTest("F3", list, "Anna", 2, 0);
  failCount = failCount + rc;

  rc = testCount("C1", list, 5);
  failCount = failCount + rc;

  Record explist10[] = { {"Anna", 2, NULL}, {"Henry", 60, NULL}, {"Elizabeth", 67, NULL}, {"John", 80, NULL} };
  rc = testDelete("D4", &list, 56, explist10, 4, 0);
  failCount = failCount + rc;

  Record explist11[] = { {"Anna", 2, NULL}, {"Henry", 60, NULL}, {"John", 80, NULL} };
  rc = testDelete("D5", &list, 67, explist11, 3, 0);
  failCount = failCount + rc;

  Record explist12[] = { {"Anna", 2, NULL}, {"John", 80, NULL} };
  rc = testDelete("D6", &list, 60, explist12, 2, 0);
  failCount = failCount + rc;

  Record explist13[] = { {"John", 80, NULL} };
  rc = testDelete("D7", &list, 2, explist13, 1, 0);
  failCount = failCount + rc;

  Record explist14[] = { };
  rc = testDelete("D8", &list, 80, explist14, 0, 0);
  failCount = failCount + rc;

  rc = testDelete("D9", &list, 40, explist14, 0, 1);
  failCount = failCount + rc;

  if (failCount == 0)
    printf("all tests pass\n");
  else
    printf("%d tests fail\n", failCount);

  return failCount;
}
