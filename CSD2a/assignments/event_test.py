#
# Opdracht​:
# Maak een sequencer die een percussieve loop van minimaal 16 events afspeelt op de momenten die worden aangegeven door hun timestamps.
# Gebruik drie verschillende samples. Experimenteer met gelijktijdige en sequentiële events.
# 
# Maak een functie die één event afhandelt en roep deze aan op het moment dat door de timestamp van de event wordt aangegeven.
# Zo’n functie wordt een ​event handler​ genoemd.

rhythm = [
    {timestamp: 0.0, instrument: kick},
    {timestamp: 0.0, instrument: hihat},
    {timestamp: 0.75, instrument: snare},
    {timestamp: 1.0, instrument: snare}
]