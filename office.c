#include "office.h"
#include "queue.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define MAX_QUEUE_SIZE 200


// Function Declarations
void remove_from_subordinate(struct employee* supervisor, struct employee* employee);

/**
 * Places an employee within the office, if the supervisor field is NULL
 *  it is assumed the employee will be placed under the next employee that is
 * not superivising any other employee (top-down, left-to-right).
 *
 * If the supervisor is not NULL, it will be added to the supervisor's subordinates list
 *  of employees (make sure the supervisor exists in hierarchy).
 * if the office or employee are null, the function not do anything.
 */
void office_employee_place(struct office* off, struct employee* supervisor,
  struct employee* emp) {

    if(emp == NULL || off == NULL){
      return;
    }

    // Check if supervisor is in the office

    if(off->department_head == NULL){
      // Place employee as the head of the department
      // off->department_head = emp;

      // Malloc space for departmenat_head
      off->department_head = (struct employee*)malloc(sizeof(struct employee));

      // Malloc space for name
      off->department_head->name = (char*)malloc(strlen(emp->name)+1);

      // MARK: Can also perform null check for subordinates and allocate accordingly

      if(emp->supervisor == NULL){
        off->department_head->supervisor = NULL;
      }

      if(emp->n_subordinates > 0){
        // emp already had subordinates
        // add these subordinates to emp using the employee place function

        for(size_t i = 0; i < emp->n_subordinates; i++){

          office_employee_place(off, off->department_head, &emp->subordinates[i]);

        }


      } else {

        // Else we still have to inistialise it
        off->department_head->n_subordinates = 0;
        off->department_head->subordinates = NULL;



      }

      // Now copy the name information into the new malloc'ed space
      memcpy(off->department_head->name, emp->name, strlen(emp->name)+1);
    

      // memcpy(&off->department_head, &emp, sizeof(struct employee*));
      return;
    }

    if(supervisor == NULL){

      // Supervisor is null

      // We are looking for the first employee top down left right
      struct Queue* queue = createQueue(MAX_QUEUE_SIZE);

      // CHANGE: Don't think we need to malloc here, we're just storing the pointer value
      struct employee* new_supervisor = NULL;
      
      enqueue(queue, off->department_head);


      while(!isEmpty(queue)){

        struct employee* cursor = dequeue(queue);


        if(cursor->n_subordinates == 0){


          // Found an employee with no subordinates
          new_supervisor = cursor;
          // break out of while loop
          break;

        } else {

          // If this employee does have subordinates, then we need to append the subordinates into the queue

          for(size_t i = 0; i < cursor->n_subordinates; i++){

            enqueue(queue, &(cursor->subordinates[i]));

          }


        }


      }

      if(new_supervisor == NULL){
        return;
      }

      // At this point we should have the new supervisor

      size_t str_length = strlen(emp->name)+1;
    
      // Malloc space
      new_supervisor->subordinates = (struct employee*)realloc(new_supervisor->subordinates, sizeof(struct employee));

      new_supervisor->subordinates[0].name = (char*)malloc(sizeof(char)*str_length);

      // Copy information over
      // memcpy(new_supervisor->subordinates[0].name, emp->name, strlen(emp->name)+1);
      strcpy(new_supervisor->subordinates[0].name, emp->name);

      new_supervisor->subordinates[0].supervisor = new_supervisor;

      if(emp->n_subordinates > 0){
        // emp already had subordinates
        // add these subordinates to emp using the employee place function

        for(size_t i = 0; i < emp->n_subordinates; i++){

          office_employee_place(off, &new_supervisor->subordinates[0], &emp->subordinates[i]);

        }


      } else {

        // Else we still have to inistialise it

        new_supervisor->subordinates[0].n_subordinates = 0;
        new_supervisor->subordinates[0].subordinates = NULL;



      }

      // We can accomodate for the subordinate's subordinates by calling
      // Place employee again, so if a test case requires, call that here

      new_supervisor->n_subordinates++;



      // Free the queue here
      freeQueue(queue);

    } else {

      // Supervisor not null

      int num_subordinate = supervisor->n_subordinates;

      // Maybe put this in later, for all we know, the employee struct they've given us might have already had space allocated
      // emp->subordinates = (struct employee*)malloc(sizeof(struct employee));

      // MARK: Add to supervisor's subordinates list
      // Realloc to enough space for n_subordinates
      supervisor->subordinates = (struct employee*)realloc(supervisor->subordinates, (num_subordinate+1) * sizeof(struct employee));

      supervisor->subordinates[num_subordinate].name = (char*)malloc(strlen(emp->name)+1);

      // memcpy(supervisor->subordinates[num_subordinate].name, emp->name, strlen(emp->name)+1);
      strcpy(supervisor->subordinates[num_subordinate].name, emp->name);

      supervisor->subordinates->supervisor = supervisor;

      // supervisor->n_subordinates++;

      if(emp->n_subordinates > 0){
        // emp already had subordinates
        // add these subordinates to emp using the employee place function

        for(size_t i = 0; i < emp->n_subordinates; i++){

          office_employee_place(off, &supervisor->subordinates[num_subordinate], &emp->subordinates[i]);

        }


      } else {

        // Else we still have to inistialise it

        supervisor->subordinates[num_subordinate].n_subordinates = 0;
        supervisor->subordinates[num_subordinate].subordinates = NULL;



      }


      // Append the new employee pointer into the subordinates array
      // supervisor->subordinates[num_subordinate] = *emp;
      // Perform memcpy instead
      // memcpy(&supervisor->subordinates[num_subordinate], emp, sizeof(struct employee));

      // Increment the number of subordinates the supervisor has
      supervisor->n_subordinates++;


    }





}


/**
 * Fires an employee, removing from the office
 * If employee is null, nothing should occur
 * If the employee does not supervise anyone, they will just be removed
 * If the employee is supervising other employees, the first member of that
 *  team will replace him.
 */
void office_fire_employee(struct employee* employee) {


  if(employee == NULL){
    return;
  }

  struct employee* supervisor = employee->supervisor;

  // Scenario: Empolyee does not supervise anyone
  if(employee->n_subordinates <= 0){

    // Since it's a tree structure, then I think we'll just simply remove their pointer
    // From their supervisor, then free the memory allocated to the employee

    // if(supervisor == NULL){
    //   return;
    // }


    remove_from_subordinate(supervisor, employee);

    // Remove employee from supervisor's subordinate's list
    // remove_from_subordinate(supervisor, employee);
    // MARK: Here is where we might free the employee pointer
    // However, we never allocated space to it, so I'm considering maybe we don't need to
    // But if we do, here's where we do it


  } else {


    // This employee does supervise

    // Replace this employee with their first team member

    // struct employee* replacement = (struct employee*)malloc(sizeof(struct employee));

    // strcpy()

    // memcpy(replacement, &(employee->subordinates[0]), sizeof(struct employee));

    // char* name = (char*)malloc(strlen(employee->subordinates[0].name)+1);

    strcpy(employee->name, employee->subordinates[0].name);

    struct employee* first_sub = &(employee->subordinates[0]);

    // Remove 'replacement' from the employee's subordinate's list
    // remove_from_subordinate(employee, first_sub);

    // Trying something funky
    // strcpy(employee->name, replacement->name);

    // free(replacement);

    // Now we want the replacement to have the same supervisor, same list of subordinates,
    // And the same number of subordinates as the employee had before they were fired

    // memcpy(replacement->supervisor, employee->supervisor, sizeof(struct employee*));
    // memcpy(&replacement->n_subordinates, &employee->n_subordinates, sizeof(size_t));
    // memcpy(replacement->subordinates, employee->subordinates, sizeof(struct employee*));

    // Update the employee's supervisor, to have the replacement replace employee's position

    // struct employee* supervisor = employee->supervisor;

    // for(size_t i = 0; i < supervisor->n_subordinates; i++){

    //   if(&(supervisor->subordinates[i]) == employee){
    //       // Found ex-employee's entry in the subordinates list
    //       // Replace with 'replacement'
    //       // supervisor->subordinates[i] = *replacement;

    //       memcpy(&supervisor->subordinates[i], replacement, sizeof(struct employee));

    //       break;

    //   }

    // }


    // // Update all of the ex-employee's subordinate's supervisor, to the replacement
    // for(size_t j = 0; j < replacement->n_subordinates; j++){

    //   struct employee* subordinate = &(replacement->subordinates[j]);

    //   subordinate->supervisor = replacement;
    //   // memcpy(subordinate->supervisor, replacement, sizeof(struct employee*));
    //   // Pointer operation probably won't need memcpy, but we'll see

    // }

    // After that, all the relevant changes should've been made




  }





}

void remove_from_subordinate(struct employee* supervisor, struct employee* employee){


  for(size_t i = 0; i < supervisor->n_subordinates; i++){


    if(&(supervisor->subordinates[i]) == employee){

      // Found the employee, remove this entry
      size_t j = i;

      // Pre-emptively decrement the number of subordinates
      // To make the following operation easier
      supervisor->n_subordinates--;

      // Would be 0 after decrement
      // the while statement wouldn't run because its both 0

      while(j < supervisor->n_subordinates){
        // We are going to move all the subordinate's up the list
        // To replace the gap from removing this employee
        // supervisor->subordinates[j] = supervisor->subordinates[j+1];
        memcpy(&supervisor->subordinates[j], &supervisor->subordinates[j+1], sizeof(struct employee));
        strcpy(supervisor->subordinates[j].name, supervisor->subordinates[j+1].name);

        j++;

      }


      // If n_sub was 0; the statement above wouldn't run
      // Hence we need to manually free up the subordinates array now
      if(supervisor->n_subordinates == 0){
        free(supervisor->subordinates[0].name);
        free(supervisor->subordinates);
      }



      // At this point we have a repeated entry of the last employee, we might need to remove him
      // But our code technically won't try to access him, we'll see how ed reacts to it
      // Since we found the employee we want to breka out of the for loop
      break;
    }



  }


}


/**
 * Retrieves the first encounter where the employee's name is matched to one in the office
 * If the employee does not exist, it must return NULL
 * if office or name are NULL, your function must do nothing
 */
struct employee* office_get_first_employee_with_name(struct office* office,
  const char* name) {


    if(office == NULL || name == NULL || office->department_head == NULL){
      return NULL;
    }

    // I believe we're suppose to do a BFS again here
    struct Queue* queue = createQueue(MAX_QUEUE_SIZE);

    enqueue(queue, office->department_head);

    while(!isEmpty(queue)){

      struct employee* cursor = dequeue(queue);

      if(strcmp(cursor->name, name) == 0){

        // Found an employee with corresponding name
        // break out of while loop

        freeQueue(queue);
        
        return cursor;

      } else {

        // Append their subordinates and continue the BFS

        for(size_t i =  0; i < cursor->n_subordinates; i++){

          enqueue(queue, &(cursor->subordinates[i]));

        }


      }


    }




  freeQueue(queue);

	return NULL;
}

/**
 * Retrieves the last encounter where the employee's name is matched to one in the office
 * If the employee does not exist, it must return NULL
 * if office or name are NULL, your function must do nothing
 */
struct employee* office_get_last_employee_with_name(struct office* office,
  const char* name) {

    if(office == NULL || name == NULL){
      return NULL;
    }

    // I believe we're suppose to do a BFS again here
    struct Queue* queue = createQueue(MAX_QUEUE_SIZE);

    struct employee* candidate_emp = NULL;

    enqueue(queue, office->department_head);

    while(!isEmpty(queue)){

      struct employee* cursor = dequeue(queue);

      if(strcmp(cursor->name, name) == 0){

        // Found an employee with corresponding name
        // Replace earlier entries
        candidate_emp = cursor;

      }

      // Append their subordinates and continue the BFS

      for(size_t i =  0; i < cursor->n_subordinates; i++){

        enqueue(queue, &(cursor->subordinates[i]));

      }


    }


  freeQueue(queue);

	return candidate_emp;
}


/**
 * This function will need to retrieve all employees at a level.
 * A level is defined as distance away from the boss. For example, all
 * subordinates of the boss are 1 level away, subordinates of the boss's subordinates
 * are 2 levels away.
 *
 * if office, n_employees or emplys are NULL, your function must do nothing
 * You will need to provide an allocation for emplys and specify the
 * correct number of employees found in your query.
 */
void office_get_employees_at_level(struct office* office, size_t level,
  struct employee** emplys, size_t* n_employees) {
    if(n_employees == NULL || emplys == NULL || office == NULL || office->department_head == NULL){
      return;
    }

    // emp_count stores how many employees are on the current level
    size_t emp_count = 1;
    // emp_count_next stores how many employees are on the next level
    size_t emp_count_next = 0;
    // The current level we are upto
    size_t current_lvl = 0;

    struct Queue* queue = createQueue(MAX_QUEUE_SIZE);

    enqueue(queue, office->department_head);



    while(current_lvl < level){
      // If the loop runs, that means we are not at the desired level yet

      for(size_t i = 0; i < emp_count; i++){
        // We are going to dequeue all employees on this level

        struct employee* emp = dequeue(queue);

        // Append the number of subordinates, to emp_count_next
        emp_count_next += emp->n_subordinates;

        // Enqueue all subordinates of this employee
        for(size_t j = 0; j < emp->n_subordinates; j++){
          enqueue(queue, &(emp->subordinates[j]));
        }


      }

      // Once the for loop is complete
      // We should have dequeued all employees from the current level
      // And enqueued all employees of the next level

      // Increment current_level
      current_lvl++;
      // Update emp_count variables
      emp_count = emp_count_next;
      emp_count_next = 0;


    }

    // After the while loop, the first emp_count number of employees should reside on level

    // We need to malloc space into emplys to store emp_count number of items of size (struct employee*)
    struct employee* emp_result = (struct employee*)malloc(emp_count*sizeof(struct employee));

    // Then we are going to dequeue emp_count number of items into
    // the emplys array pointer
    for(size_t k = 0; k < emp_count; k++){

      struct employee* candidate = dequeue(queue);

      memcpy(&emp_result[k], candidate, sizeof(struct employee));
  
      emp_result[k].name = strdup(candidate->name);


    }

    // Store emp_result at emplys
    // emplys = emp_result;
    // memcpy(emplys, emp_result, sizeof(struct employee*));
  
    *emplys = emp_result;

    memcpy(n_employees, &emp_count, sizeof(size_t));

    freeQueue(queue);


    return;

}

/**
 * Will retrieve a list of employees that match the name given
 * If office, name, emplys or n_employees is NULL, this function should do
 * nothing
 * if office, n_employees, name or emplys are NULL, your function must do
 * nothing.
 * You will need to provide an allocation to emplys and specify the
 * correct number of employees found in your query.
 */
void office_get_employees_by_name(struct office* office, const char* name,
  struct employee** emplys, size_t* n_employees) {

    if(office == NULL || name == NULL || emplys == NULL || n_employees == NULL){
      return;
    }

    // I believe we're suppose to do a BFS again here
    struct Queue* queue = createQueue(MAX_QUEUE_SIZE);

    // Keeps track of how many matching names were found
    size_t num_found = 0;

    struct employee* emp_result = (struct employee*)malloc(sizeof(struct employee));

    enqueue(queue, office->department_head);

    while(!isEmpty(queue)){

      struct employee* cursor = dequeue(queue);

      if(strcmp(cursor->name, name) == 0){

        // Found an employee with corresponding name

        emp_result = (struct employee*)realloc(emp_result, sizeof(struct employee)*(num_found+1));

        // After reallocating more space, we store the new employee pointer at the end of the array

        // emp_result[num_found] = cursor;
        memcpy(&emp_result[num_found], cursor, sizeof(struct employee));

        emp_result[num_found].name = strdup(cursor->name);

        // Realloc more space into emplys to store the new employee
        num_found++;


      }

      // Append their subordinates and continue the BFS

      for(size_t i =  0; i < cursor->n_subordinates; i++){

        enqueue(queue, &(cursor->subordinates[i]));

      }


    }

    *emplys = emp_result;

    // Lastly, store the num found into n_employees
    // n_employees = &num_found;
    memcpy(n_employees, &num_found, sizeof(size_t));

    freeQueue(queue);

    return;
}



void post_order_recursion(struct employee* employee, struct Queue* queue){
  // Call the recursion function on all subordinates from left to right
  for(size_t i = 0; i < employee->n_subordinates; i++){

    post_order_recursion(&(employee->subordinates[i]), queue);

  }

  enqueue(queue, employee);


  return;

}

/**
 * You will traverse the office and retrieve employees using an postorder
 * traversal
 * If office, employees, n_employees or capacity is NULL, this function should do
 * nothing
 * If the employess may be larger than capacity, you are required to resize the
 * array.
 * n_employees should be reflective of the number of employees within the
 * office
 */
void office_get_employees_postorder(struct office* off,
  struct employee** emplys,
  size_t* n_employees) {


    struct Queue* queue = createQueue(MAX_QUEUE_SIZE);

    post_order_recursion(off->department_head, queue);

    size_t num_emps = queue->size;

    // n_employees = &queue->size;
    memcpy(n_employees, &queue->size, sizeof(size_t));

    // Allocate space to store all employee pointers
    // emplys = (struct employee**)malloc(sizeof(struct employee*)*queue->size);
    struct employee* emp_result = (struct employee*)malloc(num_emps*sizeof(struct employee));

    for(size_t k = 0; k < num_emps; k++){

      struct employee* candidate = dequeue(queue);
      
      memcpy(&emp_result[k], candidate, sizeof(struct employee));

      // Also strdup the name of employee across

      emp_result[k].name = strdup(candidate->name);

    }

    *emplys = emp_result;

    freeQueue(queue);

    return;

}


void promote_first_sub(struct employee* emp){

  struct employee* first_sub = &(emp->subordinates[0]);
  // This employee has subordinates
  // Promote the first subordinate from the team to manage the team
  remove_from_subordinate(emp, first_sub);

  // Give_first sub the same subordinates as emp had

  first_sub->subordinates = emp->subordinates;
  first_sub->n_subordinates = emp->n_subordinates;
  // memcpy(first_sub->subordinates, emp->subordinates, sizeof(struct employee*));
  // memcpy(first_sub->n_subordinates, emp->n_subordinates, sizeof(size_t));

  // Updae first_sub's supervisor
  first_sub->supervisor = emp->supervisor;
  // memcpy(first_sub->supervisor = emp->supervisor, sizeof(struct employee*));

  // Promotion for first subordinate complete


}



/**
 * The employee will be promoted to the same level as their supervisor and will
 *  join their supervisor's team.
 * If the employee has members on their team, the first employee from that team
 *   will be promoted to manage that team.
 * if emp is NULL, this function will do nothing
 * if the employee is at level 0 or level 1, they cannot be promoted
 */
void office_promote_employee(struct employee* emp) {

  if(emp == NULL){
    return;
  }

  // Check if emp is at level 0 or level 1
  if(emp->supervisor == NULL || emp->supervisor->supervisor == NULL){
    return;
  }


  if(emp->n_subordinates > 0){

    promote_first_sub(emp);

  }


  // Promote emp into supervisor's team
  struct employee* new_supervisor = emp->supervisor->supervisor;

  emp->supervisor = new_supervisor;

  // memcpy(emp->supervisor, new_supervisor, sizeof(struct employee*));

  // Clear emp's subordinates list
  emp->n_subordinates = 0;

  emp->subordinates = NULL;

  // Next update the supervisor's subordinates list to include emp
  new_supervisor->n_subordinates += 1;

  new_supervisor->subordinates = (struct employee*)realloc(new_supervisor->subordinates, sizeof(struct employee)*new_supervisor->n_subordinates);

  // new_supervisor->subordinates[new_supervisor->n_subordinates - 1] = *emp;
  memcpy(&new_supervisor->subordinates[new_supervisor->n_subordinates - 1], emp, sizeof(struct employee));


}

/**
 * Demotes an employee, placing them under the supervision of another employee.
 * If supervisor or emp is null, nothing should occur
 * If the employee does not supervise anyone, they will not be demoted as they
 *  are already at the lowest position
 * If an employee is to be demoted but their new distance from the boss is less
 *  than the previous position, nothing will happen.
 * Otherwise, the employee should be assigned at the end the supervisor's team
 *  and the first employee from the previously managed team will be promoted.
 *
 * Edge case:
 * if the supervisor use to be an subordinate to the demoted employee
 *   (they will get promoted)
 * the demoted employee will be attached to subordinate's new subordinate's
 *   list not their previous list.
 */
void office_demote_employee(struct employee* supervisor, struct employee* emp){

  if(supervisor == NULL || emp == NULL){
    return;
  }

  // Emp not supervising anyone; not demoted
  if(emp->n_subordinates <= 0){
    return;
  }

  // Determine the distance of the employee from boss
  int old_dist = 0;
  int new_dist = 1;

  struct employee* cursor = emp;
  while(cursor->supervisor != NULL){

    cursor = cursor->supervisor;
    old_dist++;

  }

  while(cursor->supervisor != NULL){
    cursor = cursor->supervisor;
    new_dist++;

  }

  // New position is closer to boss than before, do nothing
  if(new_dist < old_dist){
    return;
  }


  // First check for edge case
  if(supervisor->supervisor == emp){

    // New supervisor is subordinate of emp

    // Begin by removing supervisor from emp's subordinates list
    remove_from_subordinate(emp, supervisor);

    // Give emp's info to the new supervisor
    supervisor->n_subordinates = emp->n_subordinates;
    supervisor->subordinates = emp->subordinates;
    supervisor->supervisor = emp->supervisor;

    // memcpy(supervisor->n_subordinates, emp->n_subordinates, sizeof(size_t));
    // memcpy(supervisor->subordinates, emp->subordinates, sizeof(struct employee*));
    // memcpy(supervisor->supervisor = emp->supervisor, sizeof(struct employee*));



    // Clean up emp's info

    emp->supervisor = supervisor;
    // memcpy(emp->supervisor, supervisor, sizeof(struct employee*));

    emp->n_subordinates = 0;

    emp->subordinates = NULL;

    // Lastly, append emp into the back of supervisor's subordinates list

    supervisor->n_subordinates++;

    supervisor->subordinates = (struct employee*)realloc(supervisor->subordinates, sizeof(struct employee)*supervisor->n_subordinates);

    // supervisor->subordinates[supervisor->n_subordinates-1] = *emp;
    memcpy(&supervisor->subordinates[supervisor->n_subordinates-1], emp, sizeof(struct employee));

    return;
  }




  // Promote first sub from emp's team into emp's position
  promote_first_sub(emp);

  // Then we move emp into the end of supervisor's team
  supervisor->n_subordinates++;
  // Allocate space for emp
  supervisor->subordinates = (struct employee*)realloc(supervisor->subordinates, sizeof(struct employee)*supervisor->n_subordinates);

  // supervisor->subordinates[supervisor->n_subordinates-1] = *emp;
  memcpy(&supervisor->subordinates[supervisor->n_subordinates-1], emp, sizeof(struct employee));

  return;


}

/**
 * The office disbands
 * (You will need to free all memory associated with employees attached to
 *   the office and the office itself)
 */
void office_disband(struct office* office) {

// We should be able to use a post order traversal to free from the bottom up

if(office == NULL){
  return;
}
if(office->department_head == NULL){
  free(office);
  return;
}

struct Queue* queue = createQueue(MAX_QUEUE_SIZE);

post_order_recursion(office->department_head, queue);


while(!isEmpty(queue)){

  struct employee* cursor = dequeue(queue);

  // Cursor points to employee with no sub / free-ed subordinates
  if(cursor == NULL){
    continue;
  }

  // Free name
  free(cursor->name);

  if(cursor->n_subordinates > 0){
    // Had subordinates
    // Free subordinates array
    free(cursor->subordinates);
  }


}
free(office->department_head);
free(office);
freeQueue(queue);





}