
# Irregular Rhythm Generator

Generates and plays a rhythm using **simpleaudio** in Python 3

## Main focus

The main focus of this assignment for me was to explore various built-in libraries and possibilities of the Python language (mostly regarding visuals or GUI's), this is not necessarily visible in the final result but various uses can be found in the *experiments* folder.

## Implemented generation strategy

To generate the rhythm the meter (time signature) gets divided into 2's and 3's. This simple technique works well with irregular time signatures and generates rhythms often seen in folk music.

For example:

    time signature: 11/8

    rhythm (in eighth notes): 2+2+3+2+2

This generated rhythm is coincidentally one already present in traditional music from the Balkans:
[Examples of Macedonian rhythms](https://en.wikipedia.org/wiki/Music_of_North_Macedonia)

## Reflection

Generally I am happy with the result although I would have liked to implement visuals or a TUI (terminal graphical user interface). Using the standard Python libraries to make visuals slowed down the program too much even with multithreading. The issue I had does make me more curious about lower level programming and DSP.

The assignment probably took around 8 hours on it's own but 12 with all the experiments involved.
