import os
import cv2
import numpy as np
from PIL import Image, ImageTk
import tkinter as tk
from tkinter import simpledialog
import random

# Define the image file path
image_path = os.path.join('Valley Mills Waco Store Guide Cleared2 pdf.png')

# Scale factor for enlarging each pixel
scale_factor = 2

# Function to generate a random bright color
def generate_color():
    return tuple(random.randint(100, 255) for _ in range(3))

# Function to generate the color red
def generate_red_color():
    return (255, 0, 0)

# Check if the image file exists
if not os.path.exists(image_path):
    print(f"File not found: {image_path}")
    exit(1)

# Load the image
img = cv2.imread(image_path)
if img is None:
    print(f"Unable to read the image file: {image_path}")
    exit(1)

# Convert the image to grayscale
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# Resize the image to a fixed height and width
height, width = 400, 600
img_resized = cv2.resize(img_gray, (width, height), interpolation=cv2.INTER_AREA)

# Define the range for white and off-white colors with a more stringent upper bound
lower_white = np.array([220], dtype=np.uint8)
upper_white = np.array([255], dtype=np.uint8)

# Create a mask for white and off-white colors
mask = cv2.inRange(img_resized, lower_white, upper_white)

# Invert the mask to get black areas
binary_img = cv2.bitwise_not(mask)

# Convert the binary image to a 2D array of lists of characters ('1' for black, '0' for white)
array_2d = [['1'] if binary_img[j, i] == 0 else ['0'] for j in range(height) for i in range(width)]
array_2d = np.reshape(array_2d, (height, width)).tolist()

# Load coordinates from paths.txt
coordinates = []
if os.path.exists('paths.txt'):
    with open('paths.txt', 'r') as f:
        for line in f:
            parts = line.strip().split()
            if len(parts) == 2 and parts[0].isdigit() and parts[1].isdigit():
                x, y = int(parts[0]), int(parts[1])
                coordinates.append((x, y))

# Update the array with red color at specified coordinates
string_colors = {'0': (255, 255, 255), '1': (0, 0, 0)}  # Default colors for '0' and '1'
for x, y in coordinates:
    if 0 <= y < height and 0 <= x < width:
        array_2d[y][x] = list('2')
        string_colors['2'] = generate_red_color()

# Create an image from the 2D array
def array_to_image(array, scale_factor):
    height, width = len(array), len(array[0])
    scaled_height, scaled_width = height * scale_factor, width * scale_factor
    scaled_image = Image.new('RGB', (scaled_width, scaled_height))

    for i in range(width):
        for j in range(height):
            string = ''.join(array[j][i])
            if string not in string_colors:
                string_colors[string] = generate_color()
            color = string_colors[string]
            for di in range(scale_factor):
                for dj in range(scale_factor):
                    if 0 <= i * scale_factor + di < scaled_width and 0 <= j * scale_factor + dj < scaled_height:
                        scaled_image.putpixel((i * scale_factor + di, j * scale_factor + dj), color)

    return scaled_image

# GUI using tkinter
class StoreMapEditor(tk.Tk):
    def __init__(self, img, array, scale_factor):
        super().__init__()
        self.title("Store Map Editor")
        self.img = img
        self.array = array
        self.scale_factor = scale_factor

        # Ensure the window fits the entire image
        self.geometry(f"{scaled_image.width}x{scaled_image.height}")

        self.canvas = tk.Canvas(self, width=scaled_image.width, height=scaled_image.height)
        self.canvas.pack(side=tk.LEFT, expand=True, fill=tk.BOTH)

        self.photo_img = ImageTk.PhotoImage(scaled_image)
        self.canvas.create_image(0, 0, anchor=tk.NW, image=self.photo_img)

        self.canvas.bind("<Button-1>", self.on_click)

        # Ensure the window is not resizable
        self.resizable(False, False)

    def on_click(self, event):
        x, y = int(self.canvas.canvasx(event.x) // self.scale_factor), int(self.canvas.canvasy(event.y) // self.scale_factor)
        print(f"Clicked position: ({x}, {y})")
        if 0 <= x < width and 0 <= y < height:
            print(f"Valid position within bounds: ({x}, {y})")
            existing_string = ''.join(self.array[y][x])
            string = simpledialog.askstring("Input", f"Enter string for position ({x}, {y}):", initialvalue=existing_string)
            if string:
                print(f"Entered string: {string}")
                self.array[y][x] = list(string)
                if string not in string_colors:
                    string_colors[string] = generate_color()
                    print(f"Generated color for {string}: {string_colors[string]}")
                self.update_image()

    def update_image(self):
        global scaled_image
        scaled_image = array_to_image(self.array, self.scale_factor)

        self.photo_img = ImageTk.PhotoImage(scaled_image)
        self.canvas.create_image(0, 0, anchor=tk.NW, image=self.photo_img)
        self.canvas.update()

# Create and run the GUI
scaled_image = array_to_image(array_2d, scale_factor)
app = StoreMapEditor(scaled_image, array_2d, scale_factor)
app.mainloop()
