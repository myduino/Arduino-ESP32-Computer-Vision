import asyncio
import websockets
import binascii
import cv2
import numpy as np
from io import BytesIO

from PIL import Image, UnidentifiedImageError

async def process_image(file_path):
    # Read the image from the saved file
    image = cv2.imread(file_path)

    # Use for normal camera (comment this area when using fisheye)
    flipped_image = cv2.flip(image, 1) #flip horizontal
    flipped_image = cv2.flip(flipped_image, 0) #flip vertical
    hsv_image = cv2.cvtColor(flipped_image, cv2.COLOR_BGR2HSV)
    
    # Convert the image to HSV color space
    # This line use for fisheye camera
    #hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV) 

    l_h = 20
    l_s = 100
    l_v = 140
    u_h = 70
    u_s = 255
    u_v = 255
    
    # Define a mask (example: keeping the hue values between 50 and 100)
    lower_bound = np.array([l_h, l_s, l_v])
    upper_bound = np.array([u_h, u_s, u_v])
    mask = cv2.inRange(hsv_image, lower_bound, upper_bound)
    
    # Apply the mask to the HSV image
    masked_image = cv2.bitwise_and(hsv_image, hsv_image, mask=mask)
    
    # Convert masked image back to BGR for Gaussian blur and edge detection
    # masked_image_bgr = cv2.cvtColor(masked_image, cv2.COLOR_HSV2BGR)
    
    # Apply Gaussian blur
    blurred_image = cv2.GaussianBlur(mask, (5, 5), 0)
    
    # Detect edges using Canny edge detector
    edges = cv2.Canny(blurred_image, 100, 200)

    horizon_line_upper = 440
    midline = 400 #Half screen - constant value (800)
    index_pixel_centre_upper = 0
    segment_positive_1 = 30
    segment_positive_2 = 200
    segment_negative_1 = -30
    segment_negative_2 = -200

    #Horizon-Line Upper
    horizon_line_pixels = np.asarray(edges)
    horizon_line_white_pixel_upper = np.where(horizon_line_pixels[horizon_line_upper - 1] == 255)
        
    white_pixel_index = np.asarray(horizon_line_white_pixel_upper[0])
    if white_pixel_index.size > 0:
        index_pixel_left = white_pixel_index[0]
        index_pixel_right = white_pixel_index[-1]
        index_pixel_centre_upper = int(((index_pixel_right - index_pixel_left)/2) + index_pixel_left)
    
    ############################################################################################################################

    line_thickness = 3

    #Calculation only on X-axis
    ############################################################################################################################
    upper_calculation = index_pixel_centre_upper - midline

    ############################################################################################################################

    #Using indicator dot      x   y    (Middle of the screen)
    cv2.circle(masked_image, (midline, horizon_line_upper), 6, (0, 0, 255), 3) #cv2.circle(image,coordinate,radius,color,thickness)
    cv2.line(masked_image,(midline, 340),(midline,540), (0,0,255), line_thickness)
    cv2.line(masked_image,(0, horizon_line_upper),(800,horizon_line_upper), (0,0,255), line_thickness)
    cv2.line(masked_image,(midline-segment_positive_1, 390),(midline-segment_positive_1,490), (0,0,255), line_thickness)
    cv2.line(masked_image,(midline-segment_positive_2, 390),(midline-segment_positive_2,490), (0,0,255), line_thickness)
    cv2.line(masked_image,(midline-segment_negative_1, 390),(midline-segment_negative_1,490), (0,0,255), line_thickness)
    cv2.line(masked_image,(midline-segment_negative_2, 390),(midline-segment_negative_2,490), (0,0,255), line_thickness)
    

    #indicator Line Upper
    cv2.circle(masked_image, (index_pixel_centre_upper, horizon_line_upper), 8, (255, 255, 255), 5)
    cv2.putText(masked_image, str(upper_calculation), (index_pixel_centre_upper + 15,horizon_line_upper - 15), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2, cv2.LINE_AA)
    cv2.line(masked_image, (midline, horizon_line_upper), (index_pixel_centre_upper, horizon_line_upper), (255, 255, 255), line_thickness)
    cv2.line(masked_image,(index_pixel_centre_upper, 390),(index_pixel_centre_upper,490), (255,255,255), line_thickness)

    processed_image_path = 'image_processed.jpg'
    cv2.imwrite(processed_image_path, masked_image)

    stack_image = np.hstack(image,masked_image)
    cv2.imshow("Live transmission", stack_image)
    
    return str(upper_calculation)


def map_value(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max-out_min) / (in_max-in_min)+out_min
    
def PID(center):
    Kp = 1.0
    Ki = 0.1 #0.1
    Kd = 0.05 #0.05
    setpoint = 0
    previous_error = 0
    integral = 0

    error = setpoint - center
    integral += error
    derivative = error - previous_error

    output = Kp * error + Ki * integral + Kd * derivative
    previous_error = error

    return str(int(output))

def is_valid_image(image_bytes):
    try:
        Image.open(BytesIO(image_bytes))
        # print('image OK')
        return True
    except UnidentifiedImageError:
        print('image invalid')
        return False

async def handle_connection(websocket, path):
    while True:
        try:
            message = await websocket.recv()
            # print(len(message))
            if len(message) > 5000:
                if is_valid_image(message):
                    #print(message)
                    image_path = 'image_raw.jpg'
                    with open(image_path, 'wb') as f:
                        f.write(message)

                    response = await process_image(image_path)
                    
                else:
                    response = 'Invalid image.'
            else:
                response = 'Not an image.'

            print(response)
            await websocket.send(response)
            
        except websockets.exceptions.ConnectionClosed:
            break

async def main():
    server = await websockets.serve(handle_connection, '0.0.0.0', 3001)
    await server.wait_closed()

asyncio.run(main())