Dataset by Matt Huenerfauth, Bruno Miranda Artacho, Andreas Savakis and teams (RIT)

Both images and labels are inside folder in the following format:
p01_ROW01 -> Where p01 represents subject 1 and ROW01 is the “narrative” of the video as labelled by Matt Huenerfauth’s team. There are a total of 14 subjects in the dataset.

The labels are in “.mat” files distribute in a array of size Nx75, where N is the number of frames in the video and folder of the same name. There are 25 keypoints for the joints distributed as follows:
[ 0,   1,  2] = spineBase [x,y,z]
[ 3,   4,  5] = spineMid [x,y,z]
[ 6,   7,  8] = neck [x,y,z]
[ 9, 10, 11] = head [x,y,z]
[12,13, 14] = shoulderLeft [x,y,z]
[15,16, 17] = elbowLeft [x,y,z]
[18,19, 20] = wristLeft [x,y,z]
[21,22, 23] = handPalmLeft [x,y,z]
[24,25, 26] = shoulderRight [x,y,z]
[27,28, 29] = elbowRight [x,y,z]
[30,31, 33] = wristRight [x,y,z]
[33,34, 35] = handPalmRight [x,y,z]
[36,37, 38] = hipLeft [x,y,z]
[39,40, 41] = kneeLeft [x,y,z]
[42,43, 44] = ankleLeft [x,y,z]
[45,46, 47] = footLeft [x,y,z]
[48,49, 50] = hipRight [x,y,z]
[51,52, 53] = kneeRight [x,y,z]
[54,55, 56] = ankleRight [x,y,z]
[57,58, 59] = footRight [x,y,z]
[60,61, 62] = spineShoulder [x,y,z]
[63,64, 65] = handTipLeft [x,y,z]
[66,67, 68] = thumbLeft [x,y,z]
[69,70, 71] = handTipRight [x,y,z]
[72,73, 74] = thumbRight. [x,y,z]

The coordinates x and y are in pixels for horizontal and vertical coordinates, respectively. The depth z is in meters away from the camera. The subjects were positioned approximately 6ft (~2m) away from the camera.

I am discarding keypoints for knee, ankle, and foot since they are out of the frame in my use of the dataset. Hand keypoints have a higher amount of noise in the Kinect detection.

Participant demographic information:

ID#     Age     Weight  Height Kg       Meters 
P01     22      156     5'9"   70.67    1.7526
P02     24      170     5'7"
P03     23      183.7   5'3"
P04     24      140     5'2"
P05     35      139     5'6"
P06     35      89      4'10"
P07     22      180     5'9"
P08     24      280     5'6"
P09     21      155     5'4"
P10     23      120     5'11"
P12     21      120     5'5"
P13     26      200     5'5"
P15     21      187     6'0"
P16     25      180     6'3"






