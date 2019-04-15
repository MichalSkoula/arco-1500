#include "sound.h"

void Sound::playTone(int pitch, int time)
{
    tone(BUZZER_PIN, pitch, time);
}

char Sound::notesNames[8] = { 
    'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' 
};

int Sound::notesTones[8] = {
    1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 
};

void Sound::playSong(Song &song)
{
    for (int i = 0; i < 8; i++) {
        if (notesNames[i] == song.notes[song.position]) {
            playTone(notesTones[i], song.beats[song.position] * song.tempo);
            break;
        }
    }  

    delay(song.tempo / 4);

    song.position++;
    if (song.beats[song.position] == 0) {
        song.position = 0;
    }
}

Sound sound;
