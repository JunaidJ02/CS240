/* Name: Junaid Javed, alterations.c, CS 24000, Fall 2020
 * Last updated November 22, 2020
 */

/* Add any includes here */

#include "alterations.h"
#include <assert.h>
#include <stdlib.h>

/*
 * This function takes in an event pointer and a pointer to a number of octaves.
 * If the event is a note event (Note On, Note Off, Polyphonic Key Pressure),
 * it changes the octave of that note by the given number of octaves, unless
 * doing so would make the note value less than 0 or greater than 127. This
 * function returns 1 if the event was modified, and 0 otherwise.
 */

int change_event_octave(event_t *event_change, int *delta_octave) {

  /*
   * Check if the event is of type MIDI_EVENT. If it is of type MIDI_EVENT, it
   * also checks to make sure that it is a note event (Note On, Note Off,
   * Polyphonic Key Pressure).
   */
  if ((event_type(event_change) == MIDI_EVENT_T) &&
      (event_change->midi_event.status <= 0xAF)) {
    /*
     * Calculates the new note value and make sure that it is greater than 0
     * and less than 127.
     */
    int note_value = event_change->midi_event.data[0] +
     (*delta_octave) * OCTAVE_STEP;
    if ((note_value >= 0) && (note_value <= 127)) {
      /*
       * Changes the note to the value we just calculated. Returns 1 since it
       * was succesful.
       */
      event_change->midi_event.data[0] = (uint8_t)note_value;
      return 1;
    }
  }
  // Returns 0 if the calculated note value is less than 0 or greater than 127.
  return 0;
} /* change_event_octave() */

/*
 * This function takes in an event pointer and a pointer to a float multiplier.
 * This function should scale the delta-time of the event by the input
 * multiplier.
 *
 * This function should return the difference in bytes associated with the
 * variable length quantity representation of the event’s new delta-time
 * relative to its old delta-time.
 */

int change_event_time(event_t *event_change, float *delta_time) {
  int difference = 0;
  int bytes = 0;

  /*
   * Calculate the size of the delta_time byte. This is needed so we can
   * compare the sizes and return the difference.
   */
  if (event_change->delta_time < 0x80) {
    bytes = 1;
  } else if (event_change->delta_time < 0x4000) {
    bytes = 2;
  } else if (event_change->delta_time < 0x200000) {
    bytes = 3;
  } else {
    bytes = 4;
  }

  // Change the time by factor of delta_time, which was passed in
  event_change->delta_time = event_change->delta_time * (*delta_time);

  /*
   * Calculate the number of bytes used up by the new delta_time and subtract
   * the original number of bytes to get the difference.
   */
  if (event_change->delta_time < 0x80) {
    difference = 1 - bytes;
  } else if (event_change->delta_time < 0x4000) {
    difference = 2 - bytes;
  } else if (event_change->delta_time < 0x200000) {
    difference = 3 - bytes;
  } else {
    difference = 4 - bytes;
  }

  // Return the difference we just calculated
  return difference;

} /* change_event_time() */

/*
 * This function takes in an event pointer and a table mapping from current
 * instruments to the desired new instruments. If the event is a program change
 *  event (changing which instrument is in use), it modifies the instrument to
 * be the value mapped to in the remapping table.
 *
 * This function returns 1 if the event was a program change event, and 0
 * otherwise.
 */

int change_event_instrument(event_t *event_change, remapping_t remap) {
  // Check if the event is of type MIDI_EVENT_T
  if (event_type(event_change) == MIDI_EVENT_T) {

    // Check if the event is a program change event
    if ((event_change->midi_event.status >= 0xC0) &&
     (event_change->midi_event.status <= 0xCF)) {

      // Change the instrument to the instrument that was passed in
      event_change->midi_event.data[0] =
       remap[event_change->midi_event.data[0]];

      // The instrument was changed correctly, so we return 1
      return 1;
    }
  }
  /*
   * The event was either not a MIDI_EVENT_T or the event did not contain a
   * note. Therefore, we could not alter the insturemnt so we return 0.
   */
  return 0;
} /* change_event_instrument() */

/*
 * This function takes in an event pointer and a table mapping from current
 * notes to the desired new notes. If the event contains a note, it changes
 * the note to the value mapped to in the remapping table.
 *
 * This function returns 1 if the event contained a note, and 0 otherwise.
 */

int change_event_note(event_t *event_change, remapping_t remap) {
  // Check if the event is of type MIDI_EVENT_T
  if (event_type(event_change) == MIDI_EVENT_T) {

    // Check if the event contains a note
    if (event_change->midi_event.status <= 0xAF) {

      // Change the note to the note that was passed in
      event_change->midi_event.data[0] =
       remap[event_change->midi_event.data[0]];

      // The note was changed correctly, so we return 1
      return 1;
    }
  }
  /*
   * The event was either not a MIDI_EVENT_T or the event did not contain a
   * note. Therefore, we could not alter the insturemnt so we return 0.
   */
  return 0;
} /* change_event_note() */

/*
 * This function takes in a song and an integer number of octaves. Each note
 * in the song should have its octave shifted by the given number of octaves.
 *
 * This function should return the number of events that were modified.
 */

int change_octave(song_data_t *song_change, int delta_octave) {
  return apply_to_events(song_change, (event_func_t) change_event_octave,
   &delta_octave);
} /* change_octave() */

/*
 * This function takes in a song, a function pointer, and a piece of arbitrary
 * data, and applies that function with that piece of data to every event in
 * the given song.
 *
 * This function should return the sum of all the function return values over
 * events in the song.
 */

int apply_to_events(song_data_t *songs_change, event_func_t func, void *data) {
  // value will return the number of events that the change was applied to
  int value = 0;

  // Get the track list in the song so we can loop through all the tracks
  track_node_t *track_list = songs_change->track_list;

  // Loop through each of the tracks in the song
  while (track_list != NULL) {

    // Get the event list in the track so we can loop through all the events
    event_node_t *event_list = track_list->track->event_list;

    // Loop through each of the events in the song
    while (event_list != NULL) {

      /*
       * value will be incremented by the return value of the function if the
       * change was succesfull or not incremented if the event was not changed
       */
      value = value + func(event_list->event, data);

      // Go to the next event in the event list
      event_list = event_list->next_event;
    }

    // Go to the next track in the track list
    track_list = track_list->next_track;
  }

  // Return the value that was calculated within the while loop
  return value;
} /* apply_to_events() */

/*
 * This function takes in a song and a float multiplier. It should modify the
 * song so that the overall length of the song changes by the multiplier. For
 * example, if passed 0.5, the song should play twice as quickly as before.
 *
 * Additionally, the song should be left in a correct state with regard to
 * stated track lengths. That is, if the modified tracks will require more or
 * less space when written to a midi file, their length parameter should be
 * updated accordingly.
 *
 * This function should return the difference in the number of bytes between
 * the song’s new representation when expressed as a midi file, and its
 * original representation when expressed as a midi file.
 */

int warp_time(song_data_t *song_change, float delta_time) {

  /*
   * We need to store the byte difference for every track in order to update
   * the length of the track. We are also using a total byte difference
   * variable which we will return at the end.
   */
  int total_difference = 0;
  int difference = 0;

  /*
   * Create a temperory song variable and allocate the memory needed to store.
   * Set the path and format to math the song that was passed in but since we
   * only want to look at one track at a time, we will set the number of tracks
   * to 1.
   */
  song_data_t *tmp_song = (song_data_t *)malloc(sizeof(song_data_t));
  tmp_song->path = song_change->path;
  tmp_song->format = song_change->format;
  tmp_song->num_tracks = 1;

  /*
   * Create a temperory track list with one one track inside and set it to be
   * the track list of the temporary song that we just created.
   */
  track_node_t *tmp_track_list = (track_node_t *)malloc(sizeof(track_node_t));
  tmp_track_list->next_track = NULL;
  tmp_song->track_list = tmp_track_list;

  /*
   * Create a track list using the songs that were passed in. The track list
   * will be traversed through in the for loop
   */
  track_node_t *tmp_song_track_list = song_change->track_list;

  /*
   * We go through each track in the track list and change the time in the
   * event by delta_time which was passed in through the function
   */
  while (tmp_song_track_list != NULL) {
    /*
     * Using another track list to keep track of our tracks so that the \
     * function is left in the correct state
     */
    tmp_track_list->track = tmp_song_track_list->track;

    /*
     * Apply the change time function to all the events in the track and store
     * its return value, the byte differnce.
     */
    difference = apply_to_events(tmp_song, (event_func_t) change_event_time,
     &delta_time);

    /*
     * Update the length to account for the difference in bytes that chaning
     * the time brought. Also update the total difference
     */
    tmp_track_list->track->length += difference;
    total_difference += difference;

    // Go to the next track in the track list
    tmp_song_track_list = tmp_song_track_list->next_track;
  }

  // Free all the memory that we allocated for tmp_song and set it to null
  free(tmp_song);
  tmp_song = NULL;

  // Free all the memory that we allocated for tmp_song and set it to null
  free(tmp_track_list);
  tmp_track_list = NULL;

  // Return the sum of the difference in byte of each track
  return total_difference;
} /* warp_time() */

/*
 * This function takes in a song and a table mapping from current instruments
 * to desired new instruments. It should modify the song so that all
 * instruments used are remapped according to the table.
 *
 * This function should return the number of events that were modified.
 */

int remap_instruments(song_data_t *song_change, remapping_t remap) {
  // Apply the change_event_instrument to all the events in the song
  return apply_to_events(song_change, (event_func_t) change_event_instrument,
   remap);
} /* remap_instruments() */

/*
 * This function takes in a song and a table mapping from current notes to new
 * notes. It should modify the song so that all notes are remapped according to
 * the table.
 *
 * This function should return the number of events that were modified.
 */

int remap_notes(song_data_t *song, remapping_t remap) {
  // Apply the change_event_node to all the events in the song
  return apply_to_events(song, (event_func_t) change_event_note, remap);
} /* remap_notes() */

/*
 * get_unused_channels is a helper function for add_round. This function finds
 * an empty channel and returns it for use in add_round.
 */

int get_unused_channel(song_data_t *song) {

  /*
   * Initialize a variable to store what channel we are currently on. Will be
   * reused to return what channel is not being used in the song.
   */
  int channel = 0;

  // Intiialize an array of channels and set them all to false
  bool channels[16] = {false, false, false, false, false, false, false, false,
                       false, false, false, false, false, false, false, false};

  // Get the track list in the song so we can loop through all the tracks
  track_node_t *track_list = song->track_list;

  // Loop through each of the tracks in the song
  while (track_list != NULL) {

    // Get the event list in the track so we can loop through all the events
    event_node_t *event_list = track_list->track->event_list;

    // Loop through each of the events in the song
    while (event_list != NULL) {

      // Check if the event is of type MIDI_EVENT_T
      if (event_type(event_list->event) == MIDI_EVENT_T) {

        // Check what channel the event is on and set the channel to being used
        if ((event_list->event->midi_event.status >= 0x80) &&
            (event_list->event->midi_event.status <= 0xDF)) {
          channel = event_list->event->midi_event.status & 0x0F;
          channels[channel] = true;
        }
      }

      // Go to the next event in the event list
      event_list = event_list->next_event;
    }

    // Go to the next track in the track list
    track_list = track_list->next_track;
  }

  /*
   * Go through all of the channels and find the first channel that is set to
   * false. If it is false, then we know that the channel is not being used and
   * we return it.
   */
  for (int i = 0; i < 16; i++) {
    if ((channels[i] == false)){
      return i;
    }
  }

  /*
   * This will be reached if all channels are being used, in that case, we will
   * return -1.
   */
  return -1;

} /* get_unused_channel() */

/*
 * Helper function for add_round. It will change the insturments in the event to
 * be the isntrumen that is passed in.
 */

int change_single_instrument(event_t *event_change, uint8_t *instrument) {
  int modification_result = 0;
  if (event_type(event_change) == MIDI_EVENT_T) {
    if ((event_change->midi_event.status >= 0xC0) &&
          (event_change->midi_event.status <= 0xCF)) {
      event_change->midi_event.data[0] = *instrument;
      modification_result = 1;
    }
  }
  return modification_result;
} /* change_single_instrument() */

/*
 *
 * This function is a helper function for add_round and copy_track. It will
 * take in a event that we wish to copy and return it. It is used to create a
 * new place in memory but still keep all the same information from that event
 * so we can traverse through them
 */

event_t *copy_event(event_t *event_copy) {

  uint8_t *data = NULL;
  event_t *new_event = (event_t *)malloc(sizeof(event_t));

  // Check what event type the event is and copy the event accordingly
  switch (event_type(event_copy)) {
    // The event was of type META_EVENT_T so we need to copy the meta event
    case META_EVENT_T:
      // Copy the type
      new_event->type = event_copy->type;

      // Copy the name of the event
      new_event->meta_event.name = event_copy->meta_event.name;

      // Copy the data length of the event
      new_event->meta_event.data_len = event_copy->meta_event.data_len;

      // Special case for META_EVENT because it can be 0. We check if it not 0
      if (new_event->meta_event.data_len != 0) {
        // Allocate enough memory for the data using the length we just got
        data = (uint8_t *) malloc(event_copy->meta_event.data_len *
         sizeof(uint8_t));

        // Go through the data and store it in a variable so we can set it later
        for (int i = 0; i < new_event->meta_event.data_len; i++) {
          data[i] = event_copy->meta_event.data[i];
        }

        // Copy the data of the event
        new_event->meta_event.data = data;
      } else {
        // If it is 0, then we set it to NULL
        new_event->meta_event.data = NULL;
      }
      break;
    // The event was of type SYS_EVENT_T so we need to copy the sys event
    case SYS_EVENT_T:
      // Copy the type
      new_event->type = event_copy->type;

      // Copy the data length of the event
      new_event->sys_event.data_len = event_copy->sys_event.data_len;

      // Allocate enough memory for the data using the length we just got
      data = (uint8_t *) malloc(event_copy->sys_event.data_len *
       sizeof(uint8_t));

      // Go through the data and store it in a variable so we can set it later
      for (int i = 0; i < new_event->sys_event.data_len; i++) {
        data[i] = event_copy->sys_event.data[i];
      }

      // Copy the data of the event
      new_event->sys_event.data = data;
      break;

    // The event was of type MIDI_EVENT so we need to copy the midi event
    default:
      // Copy the type
      new_event->type = event_copy->type;

      // Copy the name of the event
      new_event->midi_event.name = event_copy->midi_event.name;

      // Copy the status of the event
      new_event->midi_event.status = event_copy->midi_event.status;

      // Copy the data length of the event
      new_event->midi_event.data_len = event_copy->midi_event.data_len;

      // Allocate enough memory for the data using the length we just got
      data = (uint8_t *) malloc(event_copy->midi_event.data_len *
       sizeof(uint8_t));

      // Go through the data and store it in a variable so we can set it later
      for (int i = 0; i < new_event->midi_event.data_len; i++) {
        data[i] = event_copy->midi_event.data[i];
      }

      // Copy the data of the event
      new_event->midi_event.data = data;
      break;
  }

  // Set the delta time to match the delta time of the event we wish to copy
  new_event->delta_time = event_copy->delta_time;

  // Return the event that was just copied
  return new_event;
} /* copy_event() */


/*
 * This function is a helper function for add_round. It will take in a track
 * that we wish to copy and return it. It is used to create a new place in
 * memory but still keep all the same information from that track so we can
 * traverse through them
 */

track_t *copy_track(track_t *track_copy) {

  /*
   * Initialize and allocate enough memory for the track that we will copy
   * everything into. We set the length to be the length of the track we are
   * copying
   */
  track_t *return_track = (track_t *)malloc(sizeof(track_t));
  return_track->length = track_copy->length;
  return_track->event_list = NULL;

  // Initalize all the variable that we need in order to copy over the track
  event_node_t *event_listing = NULL;
  event_node_t *last_event = NULL;
  event_node_t *song_event_list = track_copy->event_list;

  // Loop through all the event in the track
  while (song_event_list != NULL) {
    // Allocate enough memory for the event list
    event_listing = (event_node_t *)malloc(sizeof(event_node_t));

    // Copy the event into the listing. We will use the help of copy_event
    event_listing->event = copy_event(song_event_list->event);

    /*
     * If the event list is empty then we set it to the list we just created.
     * Otherwise, we will set the list to go in the end
     */
    if (return_track->event_list == NULL) {
      return_track->event_list = event_listing;
    } else {
      last_event->next_event = event_listing;
    }
    /*
     * Set the last event to the event list we just made since it is the most
     * current event list
     */
    last_event = event_listing;

    // Go to the next event and go through the loop again
    song_event_list = song_event_list->next_event;
  }

  // Set the ending of the track to be NULL to show that it is the end
  last_event->next_event = NULL;

  // Return the track
  return return_track;
} /* copy_track() */


/*
 * This function takes in a song, a track index (int), an octave differential
 * (int), a time delay (unsigned int), and an instrument (represented as a
 * uint8 t per appendix 1.4 of the website), and uses them to turn the song
 * into a round of sorts. To accomplish this, duplicate the track at the
 * corresponding index in the song’s track list (assume the list is 0
 * indexed), change its octave by the specified quantity, delay it by
 * the specified value, and convert all of its instrumentation to use
 * the specified instrument, then add it to the end of the song’s track list.
 *
 * Make sure to update the song’s metadata appropriately (number of tracks and
 * format), as well as the created track’s length. Hint: what operation might
 * change the length of the track?
 *
 * Additionally, to allow both the added track and the prior tracks to be
 * heard, you should change the channel of all MIDI channel events
 * (see appendix 1.1) in the new track to be the smallest channel value not
 * found in the song. Assert that the track index may be found within the
 * song, that the song is not of format 2 (in which case adding a round
 * doesn’t really make sense), and that the song has not already used all
 * of its channel values.
 */

void add_round(song_data_t *song, int index, int delta_octave,
 unsigned int delay, uint8_t instrument) {
  // Assert that the index is within the song
  assert(index < song->num_tracks);

  /*
   * Assert that the song format is not 2 because adding a round would not make
   * any sense
   */
  assert(song->format != 2);

  /*
   * Get an unused channel and assert that there is an unused channel in the
   * song. If get_unused_channel returns 17, then there is not a free channel
   * in the song
   */
  int unused_channel = get_unused_channel(song);
  printf("Channel: %d", unused_channel);
  assert(unused_channel != -1);

  /*
   * Allocate enough memory to hold a song. We should set the song to be the
   * same as the song that was passed in, but it should only have one track.
   */
  song_data_t *tmp_song = (song_data_t *)malloc(sizeof(song_data_t));
  tmp_song->path = song->path;
  tmp_song->format = song->format;
  tmp_song->num_tracks = 1;

  /*
   * Allocate enough memory to hold a track. The track will be the one that is
   * being altered by this functon
   */
  track_node_t *new_track_list = (track_node_t *)malloc(sizeof(track_node_t));
  new_track_list->track = NULL;
  new_track_list->next_track = NULL;

  /*
   * Create a track list and move to the index'th position that was passed in
   * from the function
   */
  track_node_t *tmp_track_list = song->track_list;
  for (int i = 0; i < index; i++) {
    tmp_track_list = tmp_track_list->next_track;
  }

  /*
   * Copy the track at the index'th position and set it to the first track
   * of new_track_list. The set the track to be the track list of tmp_song
   */
  new_track_list->track = copy_track(tmp_track_list->track);
  tmp_song->track_list = new_track_list;

  /*
   * Loop through all the event in the track. Since theres a special case for
   * MIDI_EVENT_T's, then we must check if the event is of type MIDI_EVENT_T
   */
  event_node_t *event_list = new_track_list->track->event_list;
  while (event_list != NULL) {
    if (event_type(event_list->event) == MIDI_EVENT_T) {
      /*
       * If the event is of type MIDI_EVENT_T, then we must check if it is
       * within the correct range
       */
      if ((event_list->event->midi_event.status >= 0x80) &&
          (event_list->event->midi_event.status <= 0xEF)) {

        // We must update the status bytes using bitwise opperators
        event_list->event->midi_event.status =
        (event_list->event->midi_event.status & 0xF0) |
         ((uint8_t) unused_channel);
        event_list->event->type = event_list->event->midi_event.status;
      }
    }
    // Go to the next event and go through the loop again
    event_list = event_list->next_event;
  }

  // Update the time to include the delay that was passed in from the function
  new_track_list->track->event_list->event->delta_time =
   new_track_list->track->event_list->event->delta_time + delay;

  // Update the octave of the song
  change_octave(tmp_song, delta_octave);

  // Update the insturments in the song using the instrument that was passed in
  apply_to_events(tmp_song, (event_func_t) change_single_instrument,
   &instrument);

  // Go to the last track in the song
  track_node_t *tracks = song->track_list;
  while (tracks->next_track != NULL) {
    tracks = tracks->next_track;
  }

  // Update the track list from the song and add the track list we just created
  new_track_list->next_track = NULL;
  tracks->next_track = new_track_list;

  // Update the mumber of tracks in the song
  song->num_tracks++;

  // Free the song and set it to NULL
  free(tmp_song);
  tmp_song = NULL;

} /* add_round() */

/*
 * Function called prior to main that sets up random mapping tables
 */

void build_mapping_tables() {
  for (int i = 0; i <= 0xFF; i++) {
    I_BRASS_BAND[i] = 61;
  }

  for (int i = 0; i <= 0xFF; i++) {
    I_HELICOPTER[i] = 125;
  }

  for (int i = 0; i <= 0xFF; i++) {
    N_LOWER[i] = i;
  }
  //  Swap C# for C
  for (int i = 1; i <= 0xFF; i += 12) {
    N_LOWER[i] = i - 1;
  }
  //  Swap F# for G
  for (int i = 6; i <= 0xFF; i += 12) {
    N_LOWER[i] = i + 1;
  }
} /* build_mapping_tables() */
