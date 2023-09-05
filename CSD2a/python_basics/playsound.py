import simpleaudio

snare = "snare.wav"
kick = "kick.wav"

wave_object = simpleaudio.WaveObject.from_wave_file(snare)

i = 1
while i < 6:
  print(i)
  play_object = wave_object.play()
  play_object.wait_done()
  i += 1