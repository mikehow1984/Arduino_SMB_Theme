/*
Exploring Arduino - Code Listing 5-1: Arduino Music Player
http://www.exploringarduino.com/content/ch5

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.

Modified by Michael Howard for the Super Mario Bros. theme Arduino sketch

*/

//Plays a song on a speaker

#include "pitches.h" //Header file with pitch definitions

const int SPEAKER=9;  //Speaker Pin

//Note Array
int notes_start[] = {
 NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0, 
 NOTE_G5, 0, NOTE_G4, 0
};
 
int notes_tune1[] = {
 NOTE_C5, 0, NOTE_G4, 0, NOTE_E4, 0, NOTE_A4, 0, 
 NOTE_B4, 0, NOTE_AS4, NOTE_A4, 0, NOTE_G4, NOTE_E4, NOTE_G5,
 
 NOTE_A5, 0, NOTE_F5, NOTE_G5, 0, NOTE_E5, 0, NOTE_C5,
 NOTE_D5, NOTE_B4, 0,
};
 
int notes_tune2[] = {
  0, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, 0, NOTE_E5, 
  0, NOTE_GS4, NOTE_A4, NOTE_C5, 0, NOTE_A4, NOTE_C5, NOTE_D5,
 
  0, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, 0, NOTE_E5,
  0, NOTE_C6, 0, NOTE_C6, NOTE_C6, 0,

 
 0, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, 0, NOTE_E5, 
 0, NOTE_GS4, NOTE_A4, NOTE_C5, 0, NOTE_A4, NOTE_C5, NOTE_D5,
 
 0, NOTE_DS5, 0, NOTE_D5, 0,
 NOTE_C5, 0,
};
 
int bridge[] = {
  NOTE_C5, NOTE_C5, 0, NOTE_C5, 0, NOTE_C5, NOTE_D5, 0, 
  NOTE_E5, NOTE_C5, 0, NOTE_A4, NOTE_G4, 0,
 
  NOTE_C5, NOTE_C5, 0, NOTE_C5, 0, NOTE_C5, NOTE_D5, NOTE_E5,
  0,
 
  NOTE_C5, NOTE_C5, 0, NOTE_C5, 0, NOTE_C5, NOTE_D5, 0,
  NOTE_E5, NOTE_C5, 0, NOTE_A4, NOTE_G4, 0,
 
  NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0,
  NOTE_G5, 0, NOTE_G4, 0,
};
 
 int switchup[] = {
 NOTE_E5, NOTE_C5, 0, NOTE_G4, 0, NOTE_GS4, 0, 
 NOTE_A4, NOTE_F5, 0, NOTE_F5, NOTE_A4, 0,
 
 NOTE_B4, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,
 NOTE_E5, NOTE_C5, 0, NOTE_A4, NOTE_G4, 0,

 
 NOTE_E5, NOTE_C5, 0, NOTE_G4, 0, NOTE_GS4, 0,
 NOTE_A4, NOTE_F5, 0, NOTE_F5, NOTE_A4, 0,
 
 NOTE_B4, NOTE_F5, 0, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5,
 NOTE_C5, NOTE_E4, 0, NOTE_E4, NOTE_C4, 0
};
 
 int fanfare[] = {
 NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3, NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4,
 NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4, NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5,
 NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5, NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, 0, 
 
 NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_E5,
 NOTE_G5, NOTE_E5,
 
 NOTE_GS3, NOTE_C4, NOTE_DS4, NOTE_GS4, NOTE_C5, NOTE_DS5,
 NOTE_GS5, NOTE_DS5,
 
 NOTE_AS3, NOTE_D4, NOTE_F4, NOTE_AS4, NOTE_D5, NOTE_F5,
 NOTE_AS5, NOTE_B5, NOTE_B5, NOTE_B5, 
 NOTE_C6
};

//The Duration of each note (in ms)
int times_start[] = {
 150, 150, 150, 150, 150, 150, 150, 150,
 150, 450, 150, 450
};
 
int times_tune1[] = {
 150, 300, 150, 300, 150, 300, 150, 150, 
 150, 150, 150, 150, 150, 200, 200, 200,
 
 150, 150, 150, 150, 150, 150, 150, 150,
 150, 150, 300,
};
 
int times_tune2[] = {
 300, 150, 150, 150, 150, 150, 150,
 150, 150, 150, 150, 150, 150, 150, 150,
 
 300, 150, 150, 150, 150, 150, 150,
 150, 150, 150, 150, 150, 450,

 300, 150, 150, 150, 150, 150, 150,
 150, 150, 150, 150, 150, 150, 150, 150,
 
 300, 150, 300, 150, 300,
 150, 1050
};
 
int times_bridge[] = {
 150, 150, 150, 150, 150, 150, 150, 150, 
 150, 150, 150, 150, 150, 450,
 
 150, 150, 150, 150, 150, 150, 150, 150,
 1200,

 
 150, 150, 150, 150, 150, 150, 150, 150, 
 150, 150, 150, 150, 150, 450,
 
 150, 150, 150, 150, 150, 150, 150, 150, 
 150, 450, 150, 450
};
 
int times_switch_up[] = {
 150, 150, 150, 150, 300, 150, 150,
 150, 150, 150, 150, 150, 450,
 
 200, 200, 200, 200, 200, 200,
 150, 150, 150, 150, 150, 450,
 
 150, 150, 150, 150, 300, 150, 150,
 150, 150, 150, 150, 150, 450,
 
 150, 150, 150, 150, 200, 200, 200,
 150, 150, 150, 150, 150, 450
};
 
int times_fanfare[] = {
 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 
 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 
 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 946,
 
 167, 167, 167, 167, 167, 167,
 500, 500,
 
 167, 167, 167, 167, 167, 167,
 500, 500,
 
 167, 167, 167, 167, 167, 167,
 500, 167, 167, 167,
 1000,
};



void setup()
{
	//Play each note for the right duration
	sheet_music(notes_start, times_start, sizeof(notes_start) / sizeof(notes_start[0]));
	sheet_music(notes_tune1, times_tune1, sizeof(notes_tune1) / sizeof(notes_tune1[0]));
	sheet_music(notes_tune1, times_tune1, sizeof(notes_tune1) / sizeof(notes_tune1[0]));
	sheet_music(notes_tune2, times_tune2, sizeof(notes_tune2) / sizeof(notes_tune2[0]));
	sheet_music(notes_tune2, times_tune2, sizeof(notes_tune2) / sizeof(notes_tune2[0]));
	sheet_music(bridge, times_bridge, sizeof(bridge) / sizeof(times_bridge[0]));
	sheet_music(notes_tune1, times_tune1, sizeof(notes_tune1) / sizeof(notes_tune1[0]));
	sheet_music(notes_tune1, times_tune1, sizeof(notes_tune1) / sizeof(notes_tune1[0]));
	sheet_music(switchup, times_switch_up, sizeof(switchup) / sizeof(switchup[0]));
	sheet_music(switchup, times_switch_up, sizeof(switchup) / sizeof(switchup[0]));
	sheet_music(bridge, times_bridge, sizeof(bridge) / sizeof(times_bridge[0]));
	sheet_music(switchup, times_switch_up, sizeof(switchup) / sizeof(switchup[0]));
	sheet_music(fanfare, times_fanfare, sizeof(fanfare) / sizeof(times_fanfare[0]));
}

void loop()
{
  //Press the reset button to play again.
}

void sheet_music(int notes[], int times[], size_t arr_size)
{
	for (int i = 0; i < arr_size; i++) //start loop
	{
		tone(SPEAKER, notes[i], times[i]);
		delay(times[i]);
	}
}
