#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "office.h"

typedef struct command command_t;

struct command {
	char* str;
	int (*exe)();
};


int test_office_place_1() {
  int pass = 0;
  const int p_match = 2;
  struct office* off = malloc(sizeof(struct office));
  off->department_head = NULL;

  struct employee emp = {
    .name = "Employee1",
    .supervisor = NULL,
    .subordinates = NULL,
    .n_subordinates = 0
  };

  office_employee_place(off, NULL, &emp);

  if(off->department_head != NULL) {
    pass++;
    if(strcmp("Employee1", off->department_head->name) == 0) {
    	pass++;
    } else {
      fputs(off->department_head->name, stdout);
    	fputs("Name does not match expected",
       stdout);
    }
  } else {
  	fputs("Department Head is NULL",
       stdout);
  }
  printf("Pass: %d\n", pass);
  free(off->department_head->name);
  printf("Finished freeing name\n");
  free(off->department_head);
  printf("Finished freeing head\n");
  free(off);
  printf("Finished freeing office\n");
  return pass == p_match;
}

int test_office_place_2() {
  int pass = 0;
  const int p_match = 3;
  struct office* off = malloc(sizeof(struct office));
  off->department_head = NULL;

  struct employee emp1 = {
    .name = "Employee1",
    .supervisor = NULL,
    .subordinates = NULL,
    .n_subordinates = 0
  };

  office_employee_place(off, NULL, &emp1);
  if(off->department_head != NULL) {
    printf("Passed first checkpoint\n");
    pass++;
  } else {
    fputs("Department Head is NULL",
       stdout);
  }

  struct employee emp2 = {
    .name = "Employee2",
    .supervisor = NULL,
    .subordinates = NULL,
    .n_subordinates = 0
  };

  struct employee emp3 = {
    .name = "Employee3",
    .supervisor = NULL,
    .subordinates = NULL,
    .n_subordinates = 0
  };

    struct employee emp4 = {
    .name = "Employee4",
    .supervisor = NULL,
    .subordinates = NULL,
    .n_subordinates = 0
  };


  office_employee_place(off, off->department_head, &emp2);
  office_employee_place(off, off->department_head, &emp3);
  office_employee_place(off, &off->department_head->subordinates[0], &emp4);
  if(off->department_head->subordinates != NULL) {
    printf("Second checkpoint\n");
    pass++;
    if(strcmp(off->department_head->subordinates[0].name,
      "Employee2") == 0) {

      pass++;
    } else {
      fputs("Object did not match expected", stdout);
    }

  } else {
    printf("Address of the name array %p\n", &off->department_head->subordinates[0].name);
    fputs("Check if your subordinates list is initialised\n",
       stdout);
  }

  printf("Before placing emp 3\n");
  if(strcmp(off->department_head->subordinates[1].name, "Employee3") == 0){
    pass++;
  }

  if(strcmp(off->department_head->subordinates[0].subordinates[0].name, "Employee4") == 0){
    pass++;
  }

  printf("Passed %d\n", pass);

  free(off->department_head->subordinates->name);
  printf("Free check point 1\n");
  free(off->department_head->subordinates);
  printf("Free check point 2\n");
  free(off->department_head->name);
  printf("Free check point 3\n");
  free(off->department_head);
  free(off);
  return pass == p_match;
}

int test_free(){

  int pass = 0;
  const int p_match = 3;
  struct office* off = malloc(sizeof(struct office));
  off->department_head = NULL;

  struct employee emp1 = {
    .name = "Employee1",
    .supervisor = NULL,
    .subordinates = NULL,
    .n_subordinates = 0
  };

  office_employee_place(off, NULL, &emp1);
  if(off->department_head != NULL) {
    printf("Passed first checkpoint\n");
    pass++;
  } else {
    fputs("Department Head is NULL",
       stdout);
  }

  struct employee emp2 = {
    .name = "Employee2",
    .supervisor = NULL,
    .subordinates = NULL,
    .n_subordinates = 0
  };

  struct employee emp3 = {
    .name = "Employee3",
    .supervisor = NULL,
    .subordinates = NULL,
    .n_subordinates = 0
  };

    struct employee emp4 = {
    .name = "Employee4",
    .supervisor = NULL,
    .subordinates = NULL,
    .n_subordinates = 0
  };


  office_employee_place(off, off->department_head, &emp2);
  office_employee_place(off, off->department_head, &emp3);
  office_employee_place(off, &off->department_head->subordinates[0], &emp4);
  if(off->department_head->subordinates != NULL) {
    printf("Second checkpoint\n");
    pass++;
    if(strcmp(off->department_head->subordinates[0].name,
      "Employee2") == 0) {

      pass++;
    } else {
      fputs("Object did not match expected", stdout);
    }

  } else {
    printf("Address of the name array %p\n", &off->department_head->subordinates[0].name);
    fputs("Check if your subordinates list is initialised\n",
       stdout);
  }

  printf("Before placing emp 3\n");
  if(strcmp(off->department_head->subordinates[1].name, "Employee3") == 0){
    pass++;
  }

  if(strcmp(off->department_head->subordinates[0].subordinates[0].name, "Employee4") == 0){
    pass++;
  }

  struct employee** emplys;

  size_t* n_emp = (size_t*)malloc(sizeof(size_t));

  size_t level = 1;

  office_get_employees_at_level(off, level, emplys, n_emp);

  printf("Found %zu emps\n", *n_emp);

  for(size_t i = 0; i < *n_emp; i++){
    printf("Emp found: %p\n", emplys[i]);
  }

  office_disband(off);

  printf("Passed %d\n", pass);



  // free(off->department_head->subordinates->name);
  // printf("Free check point 1\n");
  // free(off->department_head->subordinates);
  // printf("Free check point 2\n");
  // free(off->department_head->name);
  // printf("Free check point 3\n");
  // free(off->department_head);
  // free(off);
  return pass == p_match;



}

int test_2(){

  int pass = 0;
  const int p_match = 3;
  struct office* off = malloc(sizeof(struct office));
  off->department_head = NULL;

  struct employee emp1 = {
    .name = "Employee1",
    .supervisor = NULL,
    .subordinates = NULL,
    .n_subordinates = 0
  };

  office_employee_place(off, NULL, &emp1);
  if(off->department_head != NULL) {
    printf("Passed first checkpoint\n");
    pass++;
  } else {
    fputs("Department Head is NULL",
       stdout);
  }

  struct employee emp2 = {
    .name = "Employee2",
    .supervisor = NULL,
    .subordinates = NULL,
    .n_subordinates = 0
  };

  struct employee emp3 = {
    .name = "Employee3",
    .supervisor = NULL,
    .subordinates = NULL,
    .n_subordinates = 0
  };

    struct employee emp4 = {
    .name = "Employee4",
    .supervisor = NULL,
    .subordinates = NULL,
    .n_subordinates = 0
  };

    struct employee emp5 = {
    .name = "Employee5",
    .supervisor = NULL,
    .subordinates = NULL,
    .n_subordinates = 0
  };

    struct employee emp6 = {
    .name = "Employee6",
    .supervisor = NULL,
    .subordinates = NULL,
    .n_subordinates = 0
  };



  office_employee_place(off, off->department_head, &emp2);
  office_employee_place(off, off->department_head, &emp3);
  office_employee_place(off, &off->department_head->subordinates[0], &emp4);
  office_employee_place(off, &off->department_head->subordinates[0], &emp5);
  office_employee_place(off, off->department_head, &emp6);
  if(off->department_head->subordinates != NULL) {
    printf("Second checkpoint\n");
    pass++;
    if(strcmp(off->department_head->subordinates[0].name,
      "Employee2") == 0) {

      pass++;
    } else {
      fputs("Object did not match expected", stdout);
    }

  } else {
    printf("Address of the name array %p\n", &off->department_head->subordinates[0].name);
    fputs("Check if your subordinates list is initialised\n",
       stdout);
  }

  if(strcmp(off->department_head->subordinates[1].name, "Employee3") == 0){
    pass++;
  }

  if(strcmp(off->department_head->subordinates[0].subordinates[0].name, "Employee4") == 0){
    pass++;
  }

  struct employee* emplys = NULL;

  size_t n_emp = 0;

  size_t level = 1;

  // office_get_employees_at_level(off, level, &emplys, &n_emp);
  // office_get_employees_by_name(off, "Employee3", &emplys, &n_emp);
  // struct employee* result = office_get_first_employee_with_name(off, "Employee5");
  // office_get_employees_postorder(off, &emplys, &n_emp);

  printf("Name of supervisor %s\n", off->department_head->subordinates[1].supervisor->name);

  office_fire_employee(&off->department_head->subordinates[1]);

  // Check subordinates[1] should be emp 6 now
  printf("Emp at sub[1] %s\n", off->department_head->subordinates[1].name);


  office_disband(off);

  printf("Passed %d\n", pass);

  return pass == p_match;



}


command_t tests[] = {
  { "test_office_place_1", test_office_place_1 },
  { "test_office_place_2", test_office_place_2 }
};


int main(int argc, char** argv) {
  int test_n = sizeof(tests) / sizeof(command_t);



  // test_office_place_2();
  test_2();

  // if(argc >= 2) {
	// 	for(int i = 0; i < test_n; i++) {
	// 		if(strcmp(argv[1], tests[i].str) == 0) {
	// 			if(tests[i].exe()) {
	// 			  fprintf(stdout, "%s Passed\n", tests[i].str);
	// 			} else {
	// 			  fprintf(stdout, "%s Failed\n", tests[i].str);
	// 			}
	// 		}
	// 	}
	// }
}