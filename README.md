# Office

Welcome to The Office, you will need to write a simple office management program. This will involve structuring the data and and constructing queries and creation. The office is structured as a hierarchy where the boss is at the top and everyone else is below. Each employee can be in charge of other employees and will be ordered from first added to last.

Your program will not only have to support a tree data structure but it will need to support many different queries.

Each employee will have a name, supervisor and subordinates. Unlike most startups, this is not a "flat management" style company. You will need to implement all queries listed in the functions and documentation section.

Structure
Use the following structures within your code base. You are not allowed to modify the structures.

struct employee {
  char* name;
  struct employee* supervisor;
  struct employee* subordinates;
  size_t n_subordinates;
};


struct office {
  struct employee* department_head;
};

Functions and Documentation
/**
 * Places an employee within the office, if the supervisor field is NULL
 *  it is assumed the employee will be placed under the next employee that is
 * not superivising any other employee (top-down, left-to-right).
 * 
 * If the supervisor is not NULL, it will be added to the supervisor's list
 *  of employees (make sure the supervisor exists in hierarchy).
 * if the office or employee are null, the function not do anything.
 */
void office_employee_place(struct office* off, struct employee* supervisor,
  struct employee* emp);


/**
 * Fires an employee, removing from the office
 * If employee is null, nothing should occur
 * If the employee does not supervise anyone, they will just be removed
 * If the employee is supervising other employees, the first member of that 
 *  team will replace him.
 */
void office_fire_employee(struct employee* employee);


/**
 * Retrieves the first encounter where the employee's name is matched to one in the office
 * If the employee does not exist, it must return NULL
 * if office or name are NULL, your function must do nothing
 */ 
struct employee* office_get_first_employee_with_name(struct office* office,
  const char* name);

/**
 * Retrieves the last encounter where the employee's name is matched to one in the office
 * If the employee does not exist, it must return NULL
 * if office or name are NULL, your function must do nothing
 */ 
struct employee* office_get_last_employee_with_name(struct office* office,
  const char* name);


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
  struct employee** emplys, size_t* n_employees);

/**
 * Will retrieve a list of employees that match the name given
 * If office, name, emplys or n_employees is NULL, this function should do nothing
 * 
 * if office, n_employees, name or emplys are NULL, your function must do nothing
 * You will need to provide an allocation to emplys and specify the
 * correct number of employees found in your query.
 */
void office_get_employees_by_name(struct office* office, const char* name,
  struct employee** emplys, size_t* n_employees);

/**
 * You will traverse the office and retrieve employees using a postorder traversal
 * If off, emplys or n_employees is NULL, this function should do nothing
 *
 * You will need to provide an allocation to emplys and specify the
 * correct number of employees found in your query.
 */
void office_get_employees_postorder(struct office* off, struct employee** emplys,
  size_t* n_employees);

/**
 * The employee will be promoted to the same level as their supervisor and will join
 *  their supervisor's team.
 * If the employee has subordinates, the first subordinate will
 *  be promoted to manage that team.
 * if emp is NULL, this function will do nothing
 * if the employee is at level 0 or level 1, they cannot be promoted
 */
void office_promote_employee(struct employee* emp);

/**
 * Demotes an employee, placing them under the supervision of another employee.
 * If supervisor or emp is null, nothing should occur
 * If the employee does not supervise anyone, they will not be demoted as they are
 *  already at the lowest position
 * If an employee is to be demoted but their new position level is less than their current one
 *   nothing will happen. (Attempting to promote through demotion)
 * Otherwise, the employee should be assigned at the end the supervisor's team and
 *  the first employee from the previously managed team will be promoted.
 *
 * Edge case:
 * if the supervisor use to be an subordinate to the demoted employee (and they will get promoted)
 * the demoted employee will be attached to subordinate's new subordinates list
 * not their previous list.
 */
void office_demote_employee(struct employee* supervisor, struct employee* emp);

/**
 * The office disbands
 * (You will need to free all memory associated with employees attached to
 *   the office and the office itself)
 */
void office_disband(struct office* office);
 Expand (107 lines) 
Tips
Consider using a queue to traverse the office

Consider how you will deallocate all employees in your office, consider what traversal you could use to deallocate the tree

