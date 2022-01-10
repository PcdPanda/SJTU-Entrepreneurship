# Blob Detection and uart transport
import sensor, image, time
from pyb import UART
# For color tracking to work really well you should ideally be in a very, very,
# very, controlled enviroment where the lighting is constant...
black_threshold   = (100,150)
# You may need to tweak the above settings for tracking green things...
# Select an area in the Framebuffer to copy the color settings.

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # use RGB565.
sensor.set_framesize(sensor.QVGA) # use QQVGA for speed.
sensor.skip_frames(10) # Let new settings take affect.
sensor.set_auto_whitebal(False) # turn this off.
clock = time.clock() # Tracks FPS.

uart = UART(3, 19200)

while(True):
    clock.tick() # Track elapsed milliseconds between snapshots().
    for i in range(100):
        img = sensor.snapshot()
        #img.binary([black_threshold],invert=True) # Take a picture and return the image.

    blobs = img.find_blobs([black_threshold])
    if blobs:
        print('sum : %d'% len(blobs))
        out_str = '['
        for b in blobs:
            # Draw a rect around the blob.
            img.draw_rectangle(b[0:4]) # rect
            img.draw_cross(b[5], b[6]) # cx, cy
            x = b[5]
            y = b[6]
            out_str += '(%d,%d)' % (x,y)

        out_str += ']'

        #[(1,22)(-3,33)(22222,0)(9999,12)(0,0)]
        uart.write(out_str+'\r\n')
        print(out_str)
        uart.write('1')

    #print(clock.fps()) # Note: Your OpenMV Cam runs about half as fast while
    # connected to your computer. The FPS should increase once disconnected
