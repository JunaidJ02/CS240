/* HW10 main function */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "hw9.h"

#define MAX_NAME_LEN (100)

#define CREATE_EVENT (1)
#define DELETE_EVENT (2)
#define ADD_EVENT (3)
#define PRINT_CALENDAR (4)
#define DELETE_CALENDAR (5)
#define FIND_EVENT (6)
#define REMOVE_EVENT (7)
#define CREATE_CALENDAR_FROM_EVENT (8)
#define GET_FINISHED_CALENDAR_LIST (9)
#define DELETE_LIST (10)
#define QUIT (0)

/*
 * This function is used for reading input
 */

int clean_stdin() {
  while (getchar() != '\n') {
  }
  return 1;
} /* clean_stdin() */


/*
 *  This function prints error codes and what type of error
 *  it was.
 */

void print_error(int error) {
  switch (error) {
    case DOUBLE_BOOKING:
      printf("ERROR: DOUBLE BOOKING\n\n");
      break;
    case EVENT_NOT_FOUND:
      printf("ERROR: EVENT NOT FOUND\n\n");
      break;
    default:
      printf("ERROR: unknown error   %d\n\n", error);
      break;
  }

  return;
} /* print_error() */

/*
 *  THis function displays the contents of the list, node by node.
 */

void print_list(event_t *list_ptr, int length, bool rewind) {
  int count = 0;
  if (list_ptr == NULL) {
    printf("Empty calender!\n");
    return;
  }
  if (rewind == true) {
    while (list_ptr->prev_event != NULL) {
      list_ptr = list_ptr->prev_event;
    }
  }
  while (list_ptr != NULL) {
    if (list_ptr->info == NULL) {
      printf("Current event does not have a correct information!!!\n\n");
      return;
    }
    printf("Title: %s\nDescription:%s\n", list_ptr->info->title,
                                          list_ptr->info->description);
    printf("Starting time:\n");
    printf("Year:%4d Month:%02d Day:%02d Hour:%02d Minute:%02d\n"
                             , list_ptr->info->start_time.year,
                             list_ptr->info->start_time.month,
                             list_ptr->info->start_time.day,
                             list_ptr->info->start_time.hour,
                             list_ptr->info->start_time.minute
                             );
    printf("Ending time:\n");
    printf("Year:%4d Month:%02d Day:%02d Hour:%02d Minute:%02d\n\n"
                             , list_ptr->info->end_time.year,
                             list_ptr->info->end_time.month,
                             list_ptr->info->end_time.day,
                             list_ptr->info->end_time.hour,
                             list_ptr->info->end_time.minute
                             );
    list_ptr = list_ptr->next_event;
    count++;
    if (count == length) {
      break;
    }
  }

} /* print_list() */

/*
 *  This function is used to run the functions in hw9.c. User input is used
 *  to determine which function to run and what input is passed to it. main()
 *  prints information related to running the chosen function.
 */

int main() {
  char c = ' ';
  int read = 0;
  event_t *list_ptr = NULL;
  event_t *node_ptr = NULL;
  event_t *schedule_list_ptr = NULL;
  time_struct_t start_time = {0};
  time_struct_t end_time = {0};
  char title[MAX_NAME_LEN] = "";
  char description[MAX_NAME_LEN] = "";
  int response = 0;
  int count = 0;

  // Disable buffering to suppress memory leaks
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);

  /* begin the main program */
  while (true) {
    printf("\n\nTest Menu\n");
    printf("1. create_event()\n");
    printf("2. delete_event()\n");
    printf("3. add_event()\n");
    printf("4. Print Current Calender\n");
    printf("5. delete_calendar()\n");
    printf("6. find_event()\n");
    printf("7. remove_event()\n");
    printf("8. Create Calender From Event\n");
    printf("9. get_finished_calendar_list()\n");
    printf("10. delete_list()\n");
    printf("0. Quit\n");
    printf("Enter your choice: ");

    read = scanf("%d%c", &response, &c);
    while (((read != 2) || (c != '\n')) && (clean_stdin())) {
      printf("Invalid selection.\n");
      printf("Enter your choice: ");
      read = scanf("%d%c", &response, &c);
    }
    printf("\n");

    switch (response) {
      case CREATE_EVENT:
        if (node_ptr != NULL) {
          printf("WARNING: You've already allocated a event.\n");
          printf("Deallocating it now.\n");
          node_ptr->next_event = NULL;
          node_ptr->prev_event = NULL;
          delete_event(&node_ptr);
          node_ptr = NULL;
        }
        printf("Enter title: ");
        scanf("%[^\n]%*c", title);

        printf("Enter description: ");
        scanf("%[^\n]%*c", description);

        printf("Enter year for the start time: ");
        read = scanf("%d%c", &(start_time.year), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter year for the start time: ");
          read = scanf("%d%c", &(start_time.year), &c);
        }

        printf("Enter month for the start time: ");
        read = scanf("%d%c", &(start_time.month), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter month for the start time: ");
          read = scanf("%d%c", &(start_time.month), &c);
        }

        printf("Enter day for the start time: ");
        read = scanf("%d%c", &(start_time.day), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter day for the start time: ");
          read = scanf("%d%c", &(start_time.day), &c);
        }

        printf("Enter hour for the start time: ");
        read = scanf("%d%c", &(start_time.hour), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter hour for the start time: ");
          read = scanf("%d%c", &(start_time.hour), &c);
        }

        printf("Enter minute for the start time: ");
        read = scanf("%d%c", &(start_time.minute), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter minute for the start time: ");
          read = scanf("%d%c", &(start_time.minute), &c);
        }

        printf("Enter year for the end time: ");
        read = scanf("%d%c", &(end_time.year), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter year for the end time: ");
          read = scanf("%d%c", &(end_time.year), &c);
        }

        printf("Enter month for the end time: ");
        read = scanf("%d%c", &(end_time.month), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter month for the end time: ");
          read = scanf("%d%c", &(end_time.month), &c);
        }

        printf("Enter day for the end time: ");
        read = scanf("%d%c", &(end_time.day), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter day for the end time: ");
          read = scanf("%d%c", &(end_time.day), &c);
        }

        printf("Enter hour for the end time: ");
        read = scanf("%d%c", &(end_time.hour), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter hour for the end time: ");
          read = scanf("%d%c", &(end_time.hour), &c);
        }

        printf("Enter minute for the end time: ");
        read = scanf("%d%c", &(end_time.minute), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter minute for the end time: ");
          read = scanf("%d%c", &(end_time.minute), &c);
        }

        create_event(title, description, start_time, end_time, &node_ptr);
        printf("The structure looks like:\n\n");
        print_list(node_ptr, 0, false);
        break;
      case DELETE_EVENT:
        if (node_ptr == NULL) {
          printf("Sorry.  You need to use option 1 first...\n");
          break;
        }
        printf("Deleting event:\n");
        print_list(node_ptr, 0, false);
        node_ptr->next_event = NULL;
        node_ptr->prev_event = NULL;
        delete_event(&node_ptr);
        node_ptr = NULL;
        break;
      case ADD_EVENT:
        if (node_ptr == NULL) {
          printf("Sorry.  You need to use option 1 or 8 first...\n");
          break;
        }
        if (list_ptr == NULL) {
          printf("Sorry.  You need to use option 8 first...\n");
          break;
        }
        printf("Adding the event (in order) to calender\n");
        count = add_event(&list_ptr, node_ptr);
        node_ptr = NULL;
        if (count < 0) {
          print_error(count);
        }
        else {
          printf("Value returned %d.\n", count);
        }
        break;
      case PRINT_CALENDAR:
        printf("Printing entire calender....\n\n");
        print_list(list_ptr, 0, true);
        break;
      case DELETE_CALENDAR:
        printf("Deleting entire calender....\n\n");
        count = delete_calendar(&list_ptr);
        printf("Value returned %d.\n", count);
        list_ptr = NULL;
        break;
      case FIND_EVENT:
        printf("Enter year for the start time: ");
        read = scanf("%d%c", &(start_time.year), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter year for the start time: ");
          read = scanf("%d%c", &(start_time.year), &c);
        }

        printf("Enter month for the start time: ");
        read = scanf("%d%c", &(start_time.month), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter month for the start time: ");
          read = scanf("%d%c", &(start_time.month), &c);
        }

        printf("Enter day for the start time: ");
        read = scanf("%d%c", &(start_time.day), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter day for the start time: ");
          read = scanf("%d%c", &(start_time.day), &c);
        }

        printf("Enter hour for the start time: ");
        read = scanf("%d%c", &(start_time.hour), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter hour for the start time: ");
          read = scanf("%d%c", &(start_time.hour), &c);
        }

        printf("Enter minute for the start time: ");
        read = scanf("%d%c", &(start_time.minute), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter minute for the start time: ");
          read = scanf("%d%c", &(start_time.minute), &c);
        }

        printf("Enter the title of the event:");
        scanf("%s", title);
        count = find_event(&list_ptr, title, start_time);
        if (count < 0) {
          print_error(count);
        }
        else {
          printf("Value returned %d.\n", count);
        }
        break;
      case REMOVE_EVENT:
        if (list_ptr == NULL) {
          printf("Sorry.  You need to select a event first...\n");
          printf(" (Is there a calender in memory?)\n");
          break;
        }
        node_ptr = list_ptr;
        if (list_ptr->next_event != NULL) {
          list_ptr = list_ptr->next_event;
        }
        else {
          list_ptr = list_ptr->prev_event;
        }
        remove_event(node_ptr);
        printf("Removed the following event from the calender:\n");
        print_list(node_ptr, 0, false);
        break;
      case CREATE_CALENDAR_FROM_EVENT:
        printf("You have created calender from the event.");
        list_ptr = node_ptr;
        node_ptr = NULL;
        break;
      case GET_FINISHED_CALENDAR_LIST:
        if (list_ptr == NULL) {
          printf("You must first create the calender.\n");
          break;
        }
        if (schedule_list_ptr) {
          printf("Deleting the old finished calender list\n");
          delete_list(&schedule_list_ptr);
        }
        printf("Enter year for the start time: ");
        read = scanf("%d%c", &(start_time.year), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter year for the start time: ");
          read = scanf("%d%c", &(start_time.year), &c);
        }

        printf("Enter month for the start time: ");
        read = scanf("%d%c", &(start_time.month), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter month for the start time: ");
          read = scanf("%d%c", &(start_time.month), &c);
        }

        printf("Enter day for the start time: ");
        read = scanf("%d%c", &(start_time.day), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter day for the start time: ");
          read = scanf("%d%c", &(start_time.day), &c);
        }

        printf("Enter hour for the start time: ");
        read = scanf("%d%c", &(start_time.hour), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter hour for the start time: ");
          read = scanf("%d%c", &(start_time.hour), &c);
        }

        printf("Enter minute for the start time: ");
        read = scanf("%d%c", &(start_time.minute), &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input.\n");
          printf("Enter minute for the start time: ");
          read = scanf("%d%c", &(start_time.minute), &c);
        }

        count = get_finished_calendar_list(list_ptr, start_time
                                           , &schedule_list_ptr);
        printf("Value returned %d.\n\n", count);
        print_list(schedule_list_ptr, 0, false);
        break;

      case DELETE_LIST:
        if (schedule_list_ptr == NULL) {
          printf("You must first create a finished calender list.\n");
          break;
        }
        count = delete_list(&schedule_list_ptr);
        printf("Value returned %d.\n\n", count);
        print_list(schedule_list_ptr, 0, false);
        schedule_list_ptr = NULL;
        break;

      case QUIT:
        printf("\n\nGoodbye!!\n");
        if (list_ptr != NULL) {
          delete_calendar(&list_ptr);
          list_ptr = NULL;
        }
        if (node_ptr != NULL) {
          node_ptr->next_event = NULL;
          node_ptr->prev_event = NULL;
          delete_event(&node_ptr);
          node_ptr = NULL;
        }
        return 0;

      default:
        printf("Invalid selection.\n");
        break;
    }
  }
  return 0;

} /* main() */

