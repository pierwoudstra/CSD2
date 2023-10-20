import simpleaudio as sa
import time
import turtle
import random


def draw_circle():
    turtle.pendown()
    turtle.fillcolor("royal blue")
    turtle.begin_fill()
    turtle.circle(70)
    turtle.end_fill()
    turtle.penup()


def draw_triangle():
    turtle.pendown()
    turtle.fillcolor("yellow")
    turtle.begin_fill()
    turtle.circle(50, steps = 3)
    turtle.end_fill()
    turtle.penup() 


def get_sounds(sound_choice):
    if sound_choice == 1:  # baile funk
        kick = sa.WaveObject.from_wave_file("samples/k1.wav")
        snare = sa.WaveObject.from_wave_file("samples/s1.wav")
        hihat = sa.WaveObject.from_wave_file("samples/h1.wav")
        openhat = sa.WaveObject.from_wave_file("samples/oh1.wav")
        silence = sa.WaveObject.from_wave_file("samples/silence.wav")
    elif sound_choice == 2:  # hyperpop
        kick = sa.WaveObject.from_wave_file("samples/k2.wav")
        snare = sa.WaveObject.from_wave_file("samples/s2.wav")
        hihat = sa.WaveObject.from_wave_file("samples/h2.wav")
        openhat = sa.WaveObject.from_wave_file("samples/oh2.wav")
        silence = sa.WaveObject.from_wave_file("samples/silence.wav")
    else:  # balkan traditional
        kick = sa.WaveObject.from_wave_file("samples/k3.wav")
        snare = sa.WaveObject.from_wave_file("samples/s3.wav")
        hihat = sa.WaveObject.from_wave_file("samples/h3.wav")
        openhat = sa.WaveObject.from_wave_file("samples/oh3.wav")
        silence = sa.WaveObject.from_wave_file("samples/silence.wav")

    return kick, snare, hihat, openhat, silence


def init_sound(silence):
    silence.play()
    time.sleep(1)


def play_sample(instrument):
    # Generate random coordinates for the circle
    x = random.randint(-200, 200)
    y = random.randint(-200, 200)
    turtle.goto(x, y)

    if instrument == "kick":
        draw_circle()
        kick.play()
    elif instrument == "snare":
        draw_triangle()
        snare.play()
    elif instrument == "hihat":
        hihat.play()
    elif instrument == "openhat":
        openhat.play()


def play_array(timestamps):
    turtle.screensize(400,400)
    turtle.bgcolor("bisque")
    turtle.speed(0)  # Set the fastest drawing speed
    turtle.width(None)
    turtle.pencolor("bisque")
    turtle.penup()
    turtle.hideturtle()


    # get starting time
    time_zero = time.time()

    # get first timestamp
    current_ts = timestamps.pop(0)

    while True:
        now = time.time() - time_zero

        # current timestamp - now to determine sleep time
        # got the idea from Jozef
        if now < current_ts["ts"]:
            time.sleep(current_ts["ts"] - now)
            now = time.time() - time_zero

        play_sample(current_ts["instrument"])

        if timestamps:
            current_ts = timestamps.pop(0)
        else:
            time.sleep(0.5)
            break



def play_timestamps(timestamps, sound_choice):
    # initialize samples
    global kick
    global snare
    global hihat
    global openhat
    global silence

    kick, snare, hihat, openhat, silence = get_sounds(sound_choice)

    # start audio engine
    init_sound(silence)

    # play through timestamps
    play_array(timestamps)

    # sleep at the end to make sure sample plays through
    time.sleep(1.5)

play_timestamps([{"ts": 0, "instrument": "kick"}, {"ts": 0.4, "instrument": "kick"}, {"ts": 0.8, "instrument": "snare"}, {"ts": 1.2, "instrument": "kick"}, {"ts": 1.6, "instrument": "kick"}], 2 )