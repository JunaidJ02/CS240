/* Name: Junaid Javed, hw9.c, CS24000, Fall 2020
 * Last updated November 11, 2020
 */

/* Add any includes here */

#include "hw9.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>

/*
 * This function should allocate and populate a new event_t node.
 */

void create_event(char *event_title, char *event_description,
time_struct_t start, time_struct_t end, event_t **event_pointer) {
  assert(event_title != NULL);
  assert(event_description != NULL);
  assert(event_pointer != NULL);
  assert(*event_pointer == NULL);
  assert(start.year > 0);
  assert(start.month >= 1);
  assert(start.month <= 12);
  assert(start.day >= 1);
  assert(start.day <= 31);
  assert(start.hour >= 0);
  assert(start.hour <= 23);
  assert(start.minute >= 0);
  assert(start.minute <= 59);
  assert(end.year > 0);
  assert(end.month >= 1);
  assert(end.month <= 12);
  assert(end.day >= 1);
  assert(end.day <= 31);
  assert(end.hour >= 0);
  assert(end.hour <= 23);
  assert(end.minute >= 0);
  assert(end.minute <= 59);

  event_info_t *new_event_info = malloc(strlen(event_title) +
                 strlen(event_description) + sizeof(start) +
                 sizeof(end) + 18);
  assert(new_event_info != NULL);
  new_event_info->title = event_title;
  new_event_info->description = event_description;
  new_event_info->start_time = start;
  new_event_info->end_time = end;

  int year_in_minutes = MONTHS_IN_YEAR * DAYS_IN_MONTH *
                         HOURS_IN_DAY * MINUTES_IN_HOUR;
  int month_in_minutes = DAYS_IN_MONTH * HOURS_IN_DAY * MINUTES_IN_HOUR;
  int day_in_minutes = HOURS_IN_DAY * MINUTES_IN_HOUR;

  int year_start_id = start.year;
  int month_start_id = start.month;
  int day_start_id = start.day;
  int hour_start_id = start.hour;
  int minute_start_id = start.minute;
  int start_id = (year_start_id * year_in_minutes) +
                 (month_start_id * month_in_minutes) +
                 (day_start_id * day_in_minutes) +
                 (hour_start_id * MINUTES_IN_HOUR) +
                 (minute_start_id);
  start.id = start_id;

  int year_end_id = end.year;
  int month_end_id = end.month;
  int day_end_id = end.day;
  int hour_end_id = end.hour;
  int minute_end_id = end.minute;
  int end_id = (year_end_id * year_in_minutes) +
               (month_end_id * month_in_minutes) +
               (day_end_id * day_in_minutes) +
               (hour_end_id * MINUTES_IN_HOUR) +
               (minute_end_id);
  end.id = end_id;

  event_t *new_event = malloc(sizeof(event_t));
  assert(new_event != NULL);
  new_event->info = new_event_info;
  new_event->prev_event = NULL;
  new_event->next_event = NULL;
  *event_pointer = new_event;
} /* create_event() */

/*
 * This function should deallocate a single doubly-linked list node and all
 * of its associated data.
 */

void delete_event(event_t **curr_event) {
  assert(curr_event != NULL);
  assert(*curr_event != NULL);
  assert((*curr_event)->info != NULL);
  assert((*curr_event)->prev_event == NULL);
  assert((*curr_event)->next_event == NULL);

  free((*curr_event)->info->title);
  free((*curr_event)->info->description);
  free((*curr_event)->info);
  free((*curr_event)->prev_event);
  free((*curr_event)->next_event);
  free(*curr_event);
  *curr_event = NULL;
} /* delete_event() */

/*
 * append_event is a helper function for add_event. This function takes in a
 * head, calendar, and adds the second paramter, curr_event, in front of it.
 */

void append_event(event_t *calendar, event_t *curr_event) {
  curr_event->prev_event = calendar;
  calendar->next_event = curr_event;
} /* append_event() */

/*
 * prepend_event is a helper function for add_event. This function takes in a
 * head, calendar, and adds the second paramter, curr_event, directly behind
 * of it.
 */

void prepend_event(event_t *calendar, event_t *curr_event) {
  curr_event->prev_event = calendar->prev_event;
  calendar->prev_event = curr_event;
  curr_event->next_event = calendar;
  if (curr_event->prev_event != NULL) {
    curr_event->prev_event->next_event = curr_event;
  }
} /* prepend_event() */

/*
 * double_booking is a helper_function for add_event. This function takes in
 * a head, calendar, and return true or false depending on if the second
 * paramater has an overlapping time or double booking.
 */

bool double_booking(event_t *calendar, event_t *curr_event) {
  time_struct_t calendar_start = calendar->info->start_time;
  time_struct_t event_start = curr_event->info->start_time;

  if (calendar_start.year == event_start.year) {
    if (calendar_start.month == event_start.month) {
      if (calendar_start.day == event_start.day) {
        if (calendar_start.hour == event_start.hour) {
          if (calendar_start.minute == event_start.minute) {
            return true;
          }
        }
      }
    }
  }
  return false;
} /* double_booking() */

/*
 * prepend is a helper function that decides if the event should be added behind
 * calendar or in front. The function return true if it should be added behind,
 * and returns false if it should be added in front.
 */

bool prepend(event_t *calendar, event_t *curr_event) {
  time_struct_t calendar_start = calendar->info->start_time;
  time_struct_t event_start = curr_event->info->start_time;

  if (calendar_start.year > event_start.year) {
    return true;
  }

  if (calendar_start.year == event_start.year) {
    if (calendar_start.month > event_start.month) {
      return true;
    }
  }

  if (calendar_start.year == event_start.year) {
    if (calendar_start.month == event_start.month) {
      if (calendar_start.day > event_start.day) {
        return true;
      }
    }
  }

  if (calendar_start.year == event_start.year) {
    if (calendar_start.month == event_start.month) {
      if (calendar_start.day == event_start.day) {
        if (calendar_start.hour > event_start.hour) {
          return true;
        }
      }
    }
  }

  if (calendar_start.year == event_start.year) {
    if (calendar_start.month == event_start.month) {
      if (calendar_start.day == event_start.day) {
        if (calendar_start.hour == event_start.hour) {
          if (calendar_start.minute > event_start.minute) {
            return true;
          }
        }
      }
    }
  }

  return false;
} /* prepend() */

/*
 * This function should insert the singleton event_t (second argument) into
 * the calendar of events pointed to by the first argument. Insert the event
 * such that the calendar continues to be sorted by the event starting time.
 * The function should set the pointer pointed to by the first argument to
 * point to the head, if it does not already.
 */

int add_event(event_t **calendar_pointer, event_t *curr_event) {
  assert(calendar_pointer != NULL);
  assert(curr_event != NULL);
  event_t *calendar = *calendar_pointer;
  assert(calendar != NULL);

  while (calendar->prev_event != NULL) {
    calendar = calendar->prev_event;
  }

  while (calendar != NULL) {
    if (double_booking(calendar, curr_event)) {
      return DOUBLE_BOOKING;
    }

    if (prepend(calendar, curr_event)) {
      prepend_event(calendar, curr_event);
      break;
    } else if (calendar->next_event == NULL) {
      append_event(calendar, curr_event);
      break;
    }
    calendar = calendar->next_event;
  }

  while (calendar->prev_event != NULL) {
    calendar = calendar->prev_event;
  }

  int index = 1;
  while (calendar != NULL) {
    if (strcmp(calendar->info->title, curr_event->info->title) == 0) {
      return index;
    }
    calendar = calendar->next_event;
    index++;
  }
  return 0;
} /* add_event() */

/*
 * This function deallocates an entire calendar. The argument points somewhere
 * inside of the calendar (not necessarily the head). This function should
 * deallocate all internal data for each event as well as every events in the
 * calendar. On completion, the pointer pointed to by the first argument
 * should be set to NULL. The function should return the number of events
 * deallocated.
 */

int delete_calendar(event_t **calendar_pointer) {
  int counter = 0;
  assert(calendar_pointer != NULL);
  event_t *calendar = (*calendar_pointer);
  if (calendar == NULL) {
    return 0;
  }

  while (calendar->prev_event != NULL) {
    calendar = calendar->prev_event;
  }

  event_t *tmp = calendar;
  while (calendar->next_event != NULL) {
    tmp = calendar;
    calendar = calendar->next_event;
    tmp->prev_event = NULL;
    tmp->next_event = NULL;
    delete_event(&tmp);
    counter++;
  }

  tmp = NULL;
  calendar->prev_event = NULL;
  calendar->next_event = NULL;
  delete_event(&calendar);
  calendar = NULL;
  return ++counter;
} /* delete_calendar() */

/*
 * is_time_valid is a helper function for find_event and takes in an event. The
 * function returns true if the time is valid and false if it is not.
 */

bool is_time_valid(time_struct_t curr_event) {
  if ((curr_event.year > 0) && (curr_event.month >= 1)
      && (curr_event.month <= 12)) {
    if ((curr_event.day >= 1) && (curr_event.day <= 31)
      && (curr_event.hour >= 0)) {
      if ((curr_event.hour <= 23) && (curr_event.minute >= 0) &&
           (curr_event.minute <= 59)) {
        return true;
      }
    }
  }
  return false;
} /* is_time_valid() */

/*
 * This function should search through the calendar pointed to by the first
 * argument (again, not necessarily the head) and identify the first event of
 * the specified title (second argument) and starting time (third argument). If
 * an event is found, this function should return the event “placement”
 * number – the number of events traversed from the head of the calendar
 *  to the first matching event. The head event is considered position #1.
 *  Otherwise, the function should return EVENT_NOT_FOUND.
 */

int find_event(event_t **calendar_pointer, char *event_title,
 time_struct_t start) {

  assert(calendar_pointer != NULL);
  event_t *calendar = *calendar_pointer;
  assert(calendar != NULL);
  assert(event_title != NULL);
  assert(is_time_valid(start));

  while (calendar->prev_event != NULL) {
    calendar = calendar->prev_event;
  }

  int index = 1;
  while (calendar != NULL) {
    if (strcmp(calendar->info->title, event_title) == 0) {
      if (calendar->info->start_time.id == start.id) {
        return index;
      }
    }
    calendar = calendar->next_event;
    index++;
  }
  return EVENT_NOT_FOUND;
} /* find_event() */

/*
 * This function removes the event pointed to by the first argument from the
 * doubly-linked list in which it currently resides. Do not free() the event.
 * Only remove it. If the argument is NULL, do nothing. Be sure to set the
 * removed event’s next_event and prev_event to NULL.
 */

void remove_event(event_t *curr_event) {

  if (curr_event == NULL) {
    return;
  }

  event_t *calendar_head = curr_event;

  while (calendar_head->prev_event != NULL) {
    calendar_head = calendar_head->prev_event;
  }

  if (calendar_head == curr_event) {
    calendar_head = curr_event->next_event;
    curr_event->prev_event = NULL;
    curr_event->next_event = NULL;
    return;
  }

  if ((curr_event == NULL) ||
     ((curr_event->prev_event == NULL) &&
      (curr_event->next_event == NULL))) {
    return;
  }

  if (curr_event->next_event != NULL) {
    curr_event->next_event->prev_event = curr_event->prev_event;
  }

  if (curr_event->prev_event != NULL) {
    curr_event->prev_event->next_event = curr_event->next_event;
  }
  curr_event->next_event = NULL;
} /* remove_event() */

/*
 * This function should search through the provided calendar (pointed to by the
 * first argument — not necessarily the head) for all events finished before a
 * specified time (second argument). This function should build a new list of
 * event_ts without duplicating the actual data payload of each event_t. Put
 * anther way, the info pointer for each event_t should point to already
 * allocated data. The value at the address pointed to by the third argument
 * should be set to the head of this list. The function returns the number of
 * events found. If no event is found, the function should return 0 and set the
 * pointer pointed to by the third argument to NULL.
 */

int get_finished_calendar_list(event_t *calendar,
time_struct_t start, event_t **event_pointer) {
  assert(calendar != NULL);
  assert(is_time_valid(start));
  assert(event_pointer != NULL);
  assert(*event_pointer == NULL);
  int counter = 0;

  while (calendar->prev_event != NULL) {
    calendar = calendar->prev_event;
  }


  while (calendar->info->end_time.id < start.id) {
    counter++;
    calendar = calendar->next_event;
  }

  return counter;

} /* get_finished_calendar_list() */

/*
 * This function performs the opposite of get_finished_calendar_list(). Since
 * get_finished_- calendar_list() generates a doubly-linked list that contains
 * payloads that point to data in the calendar, delete_list() should delete and
 * deallocate the entire list of event_ts without deallocating the actual
 * payloads. This function differs from delete_calendar() in that the latter
 * deallocates the nodes AND associated payloads while delete_list() only
 * deallocates the node.
 */

int delete_list(event_t **event_pointer) {
  assert(event_pointer != NULL);
  event_t *event_pointed = (*event_pointer);
  assert(event_pointed != NULL);
  int counter = 0;

  while (event_pointed->prev_event != NULL) {
    event_pointed = event_pointed->prev_event;
  }

  event_t *tmp = event_pointed;
  while (event_pointed != NULL) {
    tmp = event_pointed;
    event_pointed = event_pointed->next_event;
    tmp->next_event = NULL;
    tmp->prev_event = NULL;
    free(tmp);
    counter++;
  }
  return counter;
} /* delete_list() */
