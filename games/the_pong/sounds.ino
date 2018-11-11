void playTone(int pitch)
{ 
  tone(buzzerPin, pitch, 10);
}

void playTimedTone(int pitch, int time)
{ 
  tone(buzzerPin, pitch, time);
}

