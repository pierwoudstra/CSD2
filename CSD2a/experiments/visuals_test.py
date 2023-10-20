import turtle

def draw_moon():
    turtle.speed(0)

    turtle.bgcolor('dark blue')
    turtle.up()
    turtle.goto(0,-100)
    turtle.color('grey')
    turtle.begin_fill()
    turtle.circle(100)
    turtle.end_fill()

    turtle.up()
    turtle.goto(50,-100)
    turtle.color('dark blue')
    turtle.begin_fill()
    turtle.circle(100)
    turtle.end_fill()

draw_moon()