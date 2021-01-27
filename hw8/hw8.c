/* Name: Junaid Javed, hw8.c, CS24000, Fall 2020
 * Last updated Oct 22, 2020
 */

/* Add any includes here */

#include "hw8.h"
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * create_event takes in an event_title, event_description, event_start_time,
 * and event_end_time. It then allocates enough memory to store the event and
 * creates it. The id is calculated to represent the number of minutes away from
 * 00:00 on 00/00/00.
 */

event_t * create_event(char *event_title, char *event_description,
           time_struct_t event_start_time, time_struct_t event_end_time) {
  assert(event_title != NULL);
  assert(event_description != NULL);
  assert(event_start_time.year > 0);
  assert(event_start_time.month >= 1);
  assert(event_start_time.month <= 12);
  assert(event_start_time.day >= 1);
  assert(event_start_time.day <= 31);
  assert(event_start_time.hour >= 0);
  assert(event_start_time.hour <= 23);
  assert(event_start_time.minute >= 0);
  assert(event_start_time.minute <= 59);
  assert(event_end_time.year > 0);
  assert(event_end_time.month >= 1);
  assert(event_end_time.month <= 12);
  assert(event_end_time.day >= 1);
  assert(event_end_time.day <= 31);
  assert(event_end_time.hour >= 0);
  assert(event_end_time.hour <= 23);
  assert(event_end_time.minute >= 0);
  assert(event_end_time.minute <= 59);

  event_info_t *new_event_info = malloc(strlen(event_title) +
                 strlen(event_description) + sizeof(event_start_time) +
                 sizeof(event_end_time) + 18);
  assert(new_event_info != NULL);
  new_event_info->title = event_title;
  new_event_info->description = event_description;
  new_event_info->start_time = event_start_time;
  new_event_info->end_time = event_end_time;

  int year_in_minutes = MONTHS_IN_YEAR * DAYS_IN_MONTH *
                         HOURS_IN_DAY * MINUTES_IN_HOUR;
  int month_in_minutes = DAYS_IN_MONTH * HOURS_IN_DAY * MINUTES_IN_HOUR;
  int day_in_minutes = HOURS_IN_DAY * MINUTES_IN_HOUR;

  int year_start_id = event_start_time.year;
  int month_start_id = event_start_time.month;
  int day_start_id = event_start_time.day;
  int hour_start_id = event_start_time.hour;
  int minute_start_id = event_start_time.minute;
  int start_id = (year_start_id * year_in_minutes) +
                 (month_start_id * month_in_minutes) +
                 (day_start_id * day_in_minutes) +
                 (hour_start_id * MINUTES_IN_HOUR) +
                 (minute_start_id);
  event_start_time.id = start_id;

  int year_end_id = event_end_time.year;
  int month_end_id = event_end_time.month;
  int day_end_id = event_end_time.day;
  int hour_end_id = event_end_time.hour;
  int minute_end_id = event_end_time.minute;
  int end_id = (year_end_id * year_in_minutes) +
               (month_end_id * month_in_minutes) +
               (day_end_id * day_in_minutes) +
               (hour_end_id * MINUTES_IN_HOUR) +
               (minute_end_id);
  event_end_time.id = end_id;

  event_t *new_event = malloc(sizeof(event_t));
  assert(new_event != NULL);
  new_event->info = new_event_info;
  new_event->prev_event = NULL;
  new_event->next_event = NULL;

  return new_event;
} /* create_event() */

/*
 * delete_event takes in one parameter which represents an event. The function
 * then deletes the event and frees its memory.
 */

void delete_event(event_t *curr_event) {
  assert(curr_event != NULL);
  assert(curr_event->info != NULL);
  assert(curr_event->prev_event == NULL);
  assert(curr_event->next_event == NULL);

  free(curr_event->info->title);
  free(curr_event->info->description);
  free(curr_event->info);
  free(curr_event->prev_event);
  free(curr_event->next_event);
  free(curr_event);
  curr_event = NULL;
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
  // time_struct_t calendar_end = calendar->info->end_time;
  time_struct_t event_start = curr_event->info->start_time;
  // time_struct_t event_end = event->info->end_time;

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
 * add_event takes in a calendar and an event and adds it in the calendar in
 * the correct spot depnding on the time.
 */

int add_event(event_t *calendar, event_t *curr_event) {
  assert(calendar != NULL);
  assert(curr_event != NULL);

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
 * delete_calendar takes in one paramter, calendar, and itterates through the
 * entire calendar and frees the entire calendar from memory and makes it NULL
 */

void delete_calendar(event_t *calendar) {
  assert(calendar != NULL);

  while (calendar->prev_event != NULL) {
    calendar = calendar->prev_event;
  }

  event_t *tmp = calendar;
  while (calendar->next_event != NULL) {
    tmp = calendar;
    calendar = calendar->next_event;
    tmp->prev_event = NULL;
    tmp->next_event = NULL;
    delete_event(tmp);
  }

  tmp = NULL;
  calendar->prev_event = NULL;
  calendar->next_event = NULL;
  delete_event(calendar);
  calendar = NULL;
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
 * find_event takes in a calendar head, a title, and start_time. The function
 * then finds the event that matches the title and start_time if it can and
 * returns its index. If it can not find the event, it returns EVENT_NOT_FOUND
 */

int find_event(event_t *calendar, char *title, time_struct_t start_time) {
  assert(calendar != NULL);
  assert(title != NULL);
  assert(is_time_valid(start_time));

  while (calendar->prev_event != NULL) {
    calendar = calendar->prev_event;
  }

  int index = 1;
  while (calendar != NULL) {
    if (strcmp(calendar->info->title, title) == 0) {
      if (calendar->info->start_time.id == start_time.id) {
        return index;
      }
    }
    calendar = calendar->next_event;
    index++;
  }
  return EVENT_NOT_FOUND;
} /* find_event() */

/*
 * remove_event takes in an event and removes it from the calendar that it is
 * located in and updates the calendar. The function returns the updated head
 */

event_t *remove_event(event_t *curr_event) {
  if (curr_event == NULL) {
    return NULL;
  }

  event_t *calendar_head = curr_event;

  while (calendar_head->prev_event != NULL) {
    calendar_head = calendar_head->prev_event;
  }

  if (calendar_head == curr_event) {
    curr_event = curr_event->next_event;
    curr_event->prev_event = NULL;
    return curr_event;
  }

  if ((curr_event == NULL) ||
     ((curr_event->prev_event == NULL) &&
      (curr_event->next_event == NULL))) {
    return NULL;
  }

  if (curr_event->next_event != NULL) {
    curr_event->next_event->prev_event = curr_event->prev_event;
  }

  if (curr_event->prev_event != NULL) {
    curr_event->prev_event->next_event = curr_event->next_event;
  }

  return calendar_head;
} /* remove_event() */