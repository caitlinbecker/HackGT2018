import io
import os
import serial, time

# Imports the Google Cloud client library
from google.cloud import vision
from google.cloud.vision import types

from cv2 import *
# initialize the camera
cam = VideoCapture(1)   # 0 -> index of camera
s, img = cam.read()
if s:    # frame captured without any errors
    imwrite("test.jpg",img) #save image

# Instantiates a client
client = vision.ImageAnnotatorClient()

# The name of the image file to annotate
file_name = os.path.join(
    os.path.dirname(__file__),
    'test.jpg')

# Loads the image into memory
with io.open(file_name, 'rb') as image_file:
    content = image_file.read()

image = types.Image(content=content)

# Performs label detection on the image file
response = client.label_detection(image=image)
labels = response.label_annotations

flag = False;
print('Labels:')
ser = serial.Serial('COM7', 9600)

print(labels[0])

for label in labels:
    if(label.description.find("food") != -1):
	print("compost")
	ser.write("a")
	flag = True
	break
    elif(label.description.find("drink") != -1):
	print("recycle")
	ser.write("b")
	flag = True
	break

if(not flag):
    print("landfill")
    ser.write("c")