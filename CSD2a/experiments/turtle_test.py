import turtle
import time

def draw_square():
    for _ in range(4):
        turtle.forward(100)
        turtle.right(90)

def draw_visualizer(bpm, rhythm):
    turtle.speed(0)  # Set the fastest drawing speed

    beat_duration = 60 / bpm  # Calculate the duration of one beat in seconds

    for rhythm_value in rhythm:
        draw_square()
        time.sleep(beat_duration * rhythm_value)

# Example usage
bpm = int(input("Enter BPM: "))
rhythm = list(map(int, input("Enter rhythm array (e.g., [2, 3, 3, 2]): ").strip('[]').split(',')))

draw_visualizer(bpm, rhythm)
