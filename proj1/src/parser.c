/* Name: Junaid Javed, parser.c, CS 24000, Fall 2020
 * Last updated November 8, 2020
 */

/* Add any includes here */

#include "parser.h"
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

// Keep track of the last status, used during parsing
uint8_t g_previous_status = 0;

/*
 * This function takes in the path of a MIDI file and returns the parsed
 * representation of that song. Assert that the input pointer is not null,
 * that the file can be read, and that, after your parsing logic has finished,
 * there is no additional data in the file.
 */

song_data_t *parse_file(const char *file_name) {

  // Open the file in order to read in binary mode
  assert(file_name != NULL);
  FILE *fptr = fopen(file_name, "rb");
  assert(fptr != NULL);

  // Allocate enough memory for the song
  song_data_t *song = (song_data_t *)(malloc(sizeof(song_data_t)));

  // Set the path to the file_name
  song->path = (char *)(malloc(strlen(file_name) + 1));
  strncpy(song->path, file_name, strlen(file_name) + 1);

  // Initialize the num_tracks and track_list
  song->num_tracks = 0;
  song->track_list = NULL;

  // Parse the header of the MIDI file
  parse_header(fptr, song);

  /*
   * Initialzie the total_tracks. The while loop will go through the file until
   * we run out tracks to parse.
   */
  int total_tracks = 0;
  while (!feof(fptr) && (total_tracks < song->num_tracks)) {
    parse_track(fptr, song);
    total_tracks++;
  }

  // Assert that we have reached the end of the file and return the parsed song
  assert(getc(fptr) == EOF);
  fclose(fptr);
  fptr = NULL;
  return song;
} /* parse_file() */

/*
 * This function should read a MIDI header chunk from the given file pointer
 * and update the given song_data_t pointer with the format, number of tracks,
 * and division information. Assert that the chunk type is correct
 * (i.e. that the first 4 bytes read from the file pointer are “MThd”),
 * that the format, number of tracks, and division information occupy 6 bytes
 * in total, and that the format is valid.
 */

void parse_header(FILE *in_file, song_data_t *curr_song) {

  // Read in the song header chunk type and assert that it is equal to "MThd"
  char song_id[4];
  assert(fread(song_id, 4, 1, in_file) == 1);
  assert(strncmp(song_id, "MThd", 4) == 0);

  // Read in the header chunck size and assert that is always equal to 6
  uint8_t head_chunk_size_split[4];
  assert(fread(&head_chunk_size_split[0], 1, 1, in_file) == 1);
  assert(fread(&head_chunk_size_split[1], 1, 1, in_file) == 1);
  assert(fread(&head_chunk_size_split[2], 1, 1, in_file) == 1);
  assert(fread(&head_chunk_size_split[3], 1, 1, in_file) == 1);
  uint32_t head_chunk_size = end_swap_32(head_chunk_size_split);
  assert(head_chunk_size == 6);

  /*
   * Read in the header format. The format should always be 0, 1, or 2. Set the
   * format of the song equal to the parsed format.
   */
  uint8_t head_format_split[2];
  assert(fread(&head_format_split[0], 1, 1, in_file) == 1);
  assert(fread(&head_format_split[1], 1, 1, in_file) == 1);
  uint16_t head_format = end_swap_16(head_format_split);
  assert(sizeof(head_format) == 2);
  assert((head_format == 0) || (head_format == 1) || (head_format == 2));
  curr_song->format = head_format;


  /*
   * Read in the number of tracks. Set the number of tracks of the song equal
   * to the parsed number.
   */
  uint8_t num_tracks_split[2];
  assert(fread(&num_tracks_split[0], 1, 1, in_file) == 1);
  assert(fread(&num_tracks_split[1], 1, 1, in_file) == 1);
  uint16_t num_tracks_combined = end_swap_16(num_tracks_split);
  assert(sizeof(num_tracks_combined) == 2);
  curr_song->num_tracks = num_tracks_combined;

  // Read in the time division from the file.
  uint8_t time_division_split[2];
  assert(fread(&time_division_split[0], 1, 1, in_file) == 1);
  assert(fread(&time_division_split[1], 1, 1, in_file) == 1);
  uint16_t time_division = end_swap_16(time_division_split);
  assert(sizeof(time_division) == 2);

  /*
   * Depending on the division that we read in, se either the ticks_per_qtr or
   * frames_per_sec and ticks_per_frame. This is done becaues of the way MIDI
   * file are set up
   */
  if ((time_division & 0x8000) == 0) {
    curr_song->division.uses_tpq = true;
    curr_song->division.ticks_per_qtr = time_division & 0x7FFF;
  } else {
    curr_song->division.uses_tpq = false;
    curr_song->division.frames_per_sec = (time_division & 0x7FFF) >> 8;
    curr_song->division.ticks_per_frame = (time_division & 0x7FFF) & 0x00FF;
  }
} /* parse_header() */

/*
 * This function should read a MIDI track chunk from the given file pointer
 * and update the given song_data_t pointer’s track_list with the track_t
 * extracted from the file. Assert that the chunk type is correct.
 */

void parse_track(FILE *in_file, song_data_t *song) {
  // Allocate all the memory we need for every track
  track_t *curr_track = (track_t *)malloc(sizeof(track_t));
  track_node_t *new_track = (track_node_t *)malloc(sizeof(track_node_t));
  event_node_t *events = NULL;
  event_node_t *curr_node = NULL;
  event_node_t *prev_node = NULL;
  event_t *curr_event = NULL;
  track_node_t *last_track_node = NULL;
  bool end_of_track = false;


  // Read in the track header and assert that it is always equal to "MTrk"
  char track_id[4] = "";
  assert(fread(track_id, 4, 1, in_file) == 1);
  assert(strncmp(track_id, "MTrk", 4) == 0);

  // Read in the track chunk size and set it equal to the tracks length
  uint8_t track_chunk_size_split[4];
  assert(fread(&track_chunk_size_split[0], 1, 1, in_file) == 1);
  assert(fread(&track_chunk_size_split[1], 1, 1, in_file) == 1);
  assert(fread(&track_chunk_size_split[2], 1, 1, in_file) == 1);
  assert(fread(&track_chunk_size_split[3], 1, 1, in_file) == 1);
  uint32_t track_chunk_size = end_swap_32(track_chunk_size_split);
  assert(sizeof(track_chunk_size) == 4);
  curr_track->length = track_chunk_size;

  //Parse every event in the track until the track ends.
  while (!end_of_track) {
    curr_event = parse_event(in_file);

    /*
     * This is for the first event we read in. Since there is not prev_node, it
     * needs its own if statement.
     */
    if (events == NULL) {
      curr_node = (event_node_t *)(malloc(sizeof(event_node_t)));
      events = curr_node;
      events->next_event = NULL;
      events->event = curr_event;
      prev_node = events;

    /*
     * For every event except the first one. There is a prev_node so it needs
     * its own if statment
     */
    } else {
      curr_node = (event_node_t *)(malloc(sizeof(event_node_t)));
      curr_node->next_event = NULL;
      prev_node->next_event = curr_node;
      prev_node = curr_node;
      curr_node->event = curr_event;
    }
    /*
     * If the event is a meta event and says "End of Track", then we know that
     * the track has ended so we set end_of_track equal to true which will end
     * the while loop and finish the parsing of the track
     */
    if ((event_type(curr_node->event) == META_EVENT_T) &&
        (strcmp(curr_node->event->meta_event.name, "End of Track") == 0)) {
      end_of_track = true;
    }
  }

  // Set the event and track equal to the songs tracks and event.
  new_track->next_track = NULL;
  new_track->track = curr_track;
  curr_track->event_list = events;

  /*
   * If the songs doesn't have any tracks then set the track equal to the track
   * list else add the parsed track to the end of the track_list
   */
  if (song->track_list == NULL) {
    song->track_list = new_track;
  } else {
    last_track_node = song->track_list;
    while (last_track_node->next_track != NULL) {
      last_track_node = last_track_node->next_track;
    }

    last_track_node->next_track = new_track;
  }
} /* parse_track() */

/*
 * This function should read and return a pointer to an event_t struct from
 * the given MIDI file pointer. For meta events, the type attribute of the
 * event should be META_EVENT; for sysex events, the type should be either
 * SYS_EVENT_1 or SYS_EVENT_2; for midi events, the type should be set to the
 * status of the event. Based on the type of the event, its union member should
 * be set accordingly.
 */

event_t *parse_event(FILE *in_file) {
  // Allocate the memory needed to store the event
  event_t *return_event = (event_t*)(malloc(sizeof(event_t)));

  /*
   * The delta_time is stored in variable length fromat. Parse the file and
   * store it into the events delta time
   */
  return_event->delta_time = parse_var_len(in_file);

  // Read in the event type from the file and set it equal to the event type
  assert(fread(&return_event->type, 1, 1, in_file) == 1);

  // If the event is of type META_EVENT then parse the meta event and return it
  if (return_event->type == META_EVENT) {
    return_event->meta_event = parse_meta_event(in_file);
    return return_event;
  }

  // If the event is of type MIDI_EVENT then parse the midi event and return it
  if (((return_event->type >= 0x80) && (return_event->type <= 0xEF))
    || (return_event->type < 0x80)) {
    return_event->midi_event = parse_midi_event(in_file, return_event->type);
    return return_event;
  }

  /*
   * If the event is of type SYS_EVENT_1 or SYS_EVENT_2 then parse the meta
   * event and return it
   */
  if ((return_event->type == SYS_EVENT_1) ||
     (return_event->type == SYS_EVENT_2)) {
    return_event->sys_event = parse_sys_event(in_file);
    return return_event;
  }
  // Return statment for good measure, will never reach this far
  return return_event;
} /* parse_event() */

/*
 * This function should read and return a sys_event_t struct from the given
 * MIDI file pointer. Be sure to allocate enough space in the data pointer to
 * house all of the event data (event data starts after the length
 * specification). data_len should encode the size of the data array.
 */

sys_event_t parse_sys_event(FILE *in_file) {
  // Initalize the event that we will return
  sys_event_t return_event = {0};

  /*
   * The event length is store as a variable length, parse and read the length
   * and set it equal to the events data_len
   */
  return_event.data_len = parse_var_len(in_file);

  // Initialize local event data to NULL
  uint8_t *event_data = NULL;

  /*
   * If the data length is greater than 0, which means it exists, then we read
   * in all the data and set it equal to the local events data
   */
  if (return_event.data_len > 0) {
    event_data = (uint8_t *)malloc(return_event.data_len * sizeof(uint8_t));
    for (int i = 0; i < return_event.data_len; i++) {
      assert(fread(&event_data[i], 1, 1, in_file) == 1);
      assert(sizeof(event_data[i]) == 1);
    }
  }
  // Set the local data equal to the events data and return it
  return_event.data = event_data;
  return return_event;
} /* parse_sys_event() */


/*
 * This function should read and return a meta_event_t struct from the given
 * MIDI file pointer. Be sure to allocate an appropriate amount of space in
 * the data pointer. However, given that event names should not change, you
 * should leave the name pointer as the default value so as not to waste space.
 * For meta event types that have a known, fixed length, you should assert that
 * the length specified in the file is equal to the known length. Additionally,
 *  you should assert that the event found is of a valid meta event type.
 * Invalid events have no entry in META_TABLE. Hint: What is the value of
 * the name attribute for events not present in the META_TABLE?
 */

meta_event_t parse_meta_event(FILE *in_file) {

  /*
   * Initialize meta_type, parse the meta type from the file and set it equal
   * to meta_type. Then initialize a meta_event that we will return and set it
   * using the META_TABLE provided. Assert that the event was in the META_TABLE
   * by checking the name of the event and making sure it is not NULL
   */
  uint8_t meta_type = 0;
  assert(fread(&meta_type, 1, 1, in_file) == 1);
  assert(sizeof(meta_type) == 1);
  meta_event_t return_event = META_TABLE[meta_type];
  assert(return_event.name != NULL);

  /*
   * event_length is stored in variable length format, read in the event length
   * and set it equal to event_length. If the event_length is defined, not 0,
   * we need to assert that the event length we got from the META_TABLES is the
   * same as the one we parsed from the file. Set the events data length to the
   * length that we just parsed in the case that the stored length is 0
   */
  uint32_t event_length = parse_var_len(in_file);
  if (return_event.data_len > 0) {
    assert(return_event.data_len == event_length);
  }
  return_event.data_len = event_length;

  /*
   * Initialize event_data and read all the data in the event and store it in
   * event_data.
   */

  uint8_t *event_data = NULL;
  if (event_length > 0) {
    event_data = (uint8_t *)(malloc(event_length * sizeof(uint8_t)));
    for (int i = 0; i < event_length; i++) {
      assert(fread(&event_data[i], 1, 1, in_file) == 1);
      assert(sizeof(event_data[i]) == 1);
    }
  }

  // Set the events data equal to the data we just parsed and return the event
  return_event.data = event_data;
  return return_event;
} /* parse_meta_event() */

/*
 * This function should read and return a midi_event_t struct from the given
 * MIDI file pointer. Be sure to allocate an appropriate amount of space in
 * the data pointer. However, given that event names should not change, you
 * should leave the name pointer as the default value so as not to waste space.
 * Assert that the event found is of a valid type. Invalid events have no entry
 *  in MIDI_TABLE.
 */

midi_event_t parse_midi_event(FILE *in_file, uint8_t status) {
  // Initialize the local variables that we will be using inside the function
  uint8_t value = 0;
  bool use_previous_status = false;

  /*
   * If there is not status, then we use the status of the previous event. This
   * is just the nature of how MIDI files and MIDI events are set up
   */
  if (status < 0x80) {
    value = status;
    status = g_previous_status;
    use_previous_status = true;
  }

  /*
   * Initialize the return event using the MIDI tables provided. Assert that
   * the event was in the MIDI table by checking that the name of the event
   * is not NULL
   */
  midi_event_t return_event = MIDI_TABLE[status];
  assert(return_event.name != NULL);

  uint8_t *event_data = malloc(return_event.data_len);

  /*
   *  If we had to use the previous status then we don't have to set the status
   * of event_data. Therefore, an if statment is used to split up the work
   */

  // Status was empty and we had to use the previous status
  if (use_previous_status) {
    event_data[0] = value;
    return_event.status = g_previous_status;
    for (int i = 1; i < return_event.data_len; i++) {
      assert(fread(&value, 1, 1, in_file) == 1);
      assert(sizeof(value) == 1);
      event_data[i] = value;
    }

  // Status was not empty
  } else {
    for (int i = 0; i < return_event.data_len; i++) {
      assert(fread(&value, 1, 1, in_file) == 1);
      assert(sizeof(value) == 1);
      event_data[i] = value;
    }
  }

  // Set the return events data equal to the data we just parsed
  return_event.data = event_data;

  /*
   * Set the previous status equal to the current status in case we need it
   * for the next event. Then return the event
   */
  g_previous_status = status;
  return return_event;
} /* parse_midi_event() */

/*
 * This function should read a variable length integer from the given
 * MIDI file pointer and return it as a fixed-size uint32_t.
 */

uint32_t parse_var_len(FILE *in_file) {
  uint32_t value = 0;
  uint8_t byte = 0;

  // Read in the first byte
  assert(fread(&value, sizeof(uint8_t), 1, in_file) == 1);
  /*
   * While the first bit is 1, continue reading in the next byte and
   * combining it with the previous one
   */
  if (value & 0x80) {
    value &= 0x7F;
    do {
      assert(fread(&byte, sizeof(uint8_t), 1, in_file) == 1);
      value = (value << 7) | (byte & 0x7F);
    } while (byte & 0x80);
  }
  return value;
} /* parse_var_len() */

/*
 * This function takes in a pointer to an event, and should return either
 * SYS_EVENT_T, META_- EVENT_T, or MIDI_EVENT_T, based on the type of the event.
 */

uint8_t event_type(event_t *curr_event) {
  // The passed event is of type META_EVENT_T;
  if (curr_event->type == META_EVENT) {
    return META_EVENT_T;
  // The passed event is of type SYS_EVENT_T;
  } else if ((curr_event->type == SYS_EVENT_1) ||
             (curr_event->type == SYS_EVENT_2)) {
    return SYS_EVENT_T;
  }
  /*
   * If we reach this, then the event is neither META_EVENT_T nor SYS_EVENT_T,
   * so it is MIDI_EVENT_T
   */
  return MIDI_EVENT_T;
} /* event_type() */

/*
 * This function should free all memory associated with the given song
 * (including the track list).
 */

void free_song(song_data_t *curr_song) {
  // The passed data should contain some data
  assert(curr_song != NULL);

  /*
   * Set the tracks to the songs track list and a tmp variable equal to 0.
   * The tmp variable will be used to remeber the event that was just freed
   */
  track_node_t *tracks = curr_song->track_list;
  track_node_t *tmp = NULL;

  // Keep freeing the track until we run out of tracks
  while (tracks != NULL) {
    // Store in tmp variable so we know what tracks are yet to be freed
    tmp = tracks->next_track;
    free_track_node(tracks);
    tracks = tmp;
  }
  // Freed the songs path and the song that was passed in
  free(curr_song->path);
  free(curr_song);
} /* free_song() */

/*
 * This function should free all memory associated with the given track node
 * (including the track and its associated events).
 */

void free_track_node(track_node_t *track_node) {
  // The passed data should contain some data
  assert(track_node != NULL);

  /*
   * Set the events to the tracks event list and a tmp variable equal to 0.
   * The tmp variable will be used to remeber the event that was just freed
   */
  event_node_t *events = track_node->track->event_list;
  event_node_t *tmp = 0;

  // Keep freeing the event until we run out of events
  while (events != NULL) {
    // Store in tmp variable so we know what events are yet to be freed
    tmp = events->next_event;
    free_event_node(events);
    events = tmp;
  }

  // Freed the entire track and the track node that was passed in
  free(track_node->track);
  free(track_node);
} /* free_track_node() */

/*
 * This function should free all memory associated with the given event node
 * (including the event and any allocated data arrays).
 */

void free_event_node(event_node_t *event_node) {
  // The passed data should contain some data
  assert(event_node != NULL);

  /*
   * Since every event has different data, the function find the event and frees
   * the corresponding data.
   */
  switch (event_type(event_node->event)) {
    // In the case that the event is of type META_EVENT
    case META_EVENT_T:
      free(event_node->event->meta_event.data);
      break;

    // In the case that the event is of type MIDI_EVENT
    case MIDI_EVENT_T:
      free(event_node->event->midi_event.data);
      break;

    // Otherwise the event will be of SYS_EVENT
    default:
      free(event_node->event->sys_event.data);
      break;
  }

  // Free the event and the node that was passed in
  free(event_node->event);
  free(event_node);

} /* free_event_node() */

/*
 * This function takes in a buffer of two uint8_ts representing a uint16_t,
 * and should return a uint16_t with opposite endianness. This function will be
 * useful for parsing certain numbers from the file, as the endianness used by
 * MIDI does not always align with that of modern systems.
 */

uint16_t end_swap_16(uint8_t byte[2]) {
  uint16_t uint16 = ((byte[0] & 0xff ) << 8) + (byte[1] & 0xff);
  return uint16;
} /* end_swap_16() */

/*
 * This function takes in a buffer of four uint8_ts representing a uint32_t,
 * and should return a uint32_t with opposite endianness. This function will be
 * useful for parsing certain numbers from the file, as the endianness used by
 * MIDI does not always align with that of modern systems.
 */

uint32_t end_swap_32(uint8_t byte[4]) {
  uint32_t uint32 = 0L;
  uint32 = (byte[0] & 0xff);
  uint32 = (uint32 << 8) + (byte[1] & 0xff);
  uint32 = (uint32 << 8) + (byte[2] & 0xff);
  uint32 = (uint32 << 8) + (byte[3] & 0xff);
  return uint32;
} /* end_swap_32() */
