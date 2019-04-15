#ifndef GAMELIB_SOUND_H
#define GAMELIB_SOUND_H

#include <Arduino.h>
#include "input.h"

struct Song
{
    byte position;
    byte tempo;
    char notes[40];
    byte beats[40]; // must end with zero
};

class Sound
{
    private:
        static char notesNames[8];
        static int notesTones[8];
        
    public:
        void playTone(int pitch, int time = 10);
        void playSong(Song &song); // to be put in game loop
};

extern Sound sound;

#endif  /* GAMELIB_SOUND_H */
