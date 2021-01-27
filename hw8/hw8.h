#ifndef HW8_H
#define HW8_H

/* Constant definitions */
#define MONTHS_IN_YEAR  (12)
#define DAYS_IN_MONTH   (31)
#define HOURS_IN_DAY    (24)
#define MINUTES_IN_HOUR (60)

/* Error codes */
#define EVENT_NOT_FOUND (-1)
#define DOUBLE_BOOKING  (-2)

/* Structure Definitions */
typedef struct time_struct {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int id;
} time_struct_t;

typedef struct event_info {
  char *title;
  char *description;
  time_struct_t start_time;
  time_struct_t end_time;
} event_info_t;

typedef struct event {
  struct event_info *info;
  struct event *prev_event;
  struct event *next_event;
} event_t;

/* Function prototypes */
event_t * create_event(char *, char *, time_struct_t, time_struct_t);
void delete_event(event_t *) ;
int add_event(event_t *, event_t *);
void delete_calendar(event_t *);
int find_event(event_t *, char *, time_struct_t);
event_t *remove_event(event_t *);

#endif // HW8_H
