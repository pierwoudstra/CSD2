import tkinter as tk

time_signature_scale = None
bpm_scale = None


def generate_rhythm():
    global time_signature_scale, bpm_scale

    time_signature = time_signature_scale.get()
    bpm = bpm_scale.get()

    # TODO rhythm generator logic

    print(time_signature, bpm)


def play_rhythm():
    global timestamps

    # TODO insert rhythm player
    pass


def save_rhythm():
    # TODO midi export function
    pass


def create_gui():
    global time_signature_scale, bpm_scale

    # main window
    root = tk.Tk()
    root.title("rhythm generator")
    root.resizable(False, False)
    root.configure(bg="blue")
    root.geometry("500x320")

    # background image
    background_image = tk.PhotoImage(file="./background.png")
    background_label = tk.Label(root, image=background_image)
    background_label.place(relwidth=1, relheight=1)

    # time signature scale
    time_signature_label = tk.Label(
        root, text="meter:", font=("InstrumentSerif-Italic", 64), fg="white", bg="blue"
    )
    time_signature_label.grid(row=0, column=0, padx=7, pady=7)

    time_signature_scale = tk.Scale(
        root,
        from_=5,
        to=13,
        orient="horizontal",
        font=("Instrument Serif", 56),
        fg="grey",
        bg="blue",
        highlightbackground="blue",
    )
    time_signature_scale.set(7)  # default value
    time_signature_scale.grid(row=0, column=1, padx=7, pady=7)

    time_signature_eight = tk.Label(
        root, text="/ 8", font=("InstrumentSerif-Italic", 64), fg="white", bg="blue"
    )
    time_signature_eight.grid(row=0, column=2, padx=7, pady=7)

    # bpm scale
    bpm_label = tk.Label(
        root,
        text="bpm:",
        font=("InstrumentSerif-Italic", 64),
        fg="white",
        bg="blue",
    )
    bpm_label.grid(row=1, column=0, padx=7, pady=7)

    bpm_scale = tk.Scale(
        root,
        from_=70,
        to=199,
        orient="horizontal",
        font=("Instrument Serif", 56),
        fg="grey",
        bg="blue",
        highlightbackground="blue",
    )
    bpm_scale.set(100)  # default value
    bpm_scale.grid(row=1, column=1, padx=7, pady=7)

    # generate, play and save buttons
    generate_button = tk.Button(
        root,
        text="generate",
        command=generate_rhythm,
        font=("InstrumentSerif-Italic", 56),
        fg="blue",
        highlightbackground="blue",
    )
    generate_button.grid(row=2, column=0, padx=7, pady=7)

    play_button = tk.Button(
        root,
        text="play",
        command=play_rhythm,
        font=("InstrumentSerif-Italic", 56),
        fg="blue",
        highlightbackground="blue",
    )
    play_button.grid(row=2, column=1, padx=7, pady=7)

    save_button = tk.Button(
        root,
        text="save",
        command=save_rhythm,
        font=("InstrumentSerif-Italic", 56),
        fg="blue",
        highlightbackground="blue",
    )
    save_button.grid(row=2, column=2, padx=7, pady=7)

    # start the main loop
    root.mainloop()


create_gui()
