import cv2
import os
from ultralytics import YOLO

# Load the YOLO model
model = YOLO(r'C:\Users\asus\Desktop\Robotics\Iran Open 2024\best.pt')

# Define the directory to save the output text files
output_dir = r'C:\Users\asus\Desktop\Robotics\Iran Open 2025'  # Change this to your desired folder path
os.makedirs(output_dir, exist_ok=True)  # Create the directory if it doesn't exist

# Open the webcam (change 0 to 1 if using an external camera)
cap = cv2.VideoCapture(0)

# Set camera resolution (Width x Height)
WIDTH, HEIGHT = 1280, 720
cap.set(cv2.CAP_PROP_FRAME_WIDTH, WIDTH)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, HEIGHT)

frame_counter = 0  # Initialize a counter for naming the frame text files

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        print("Failed to grab frame")
        break
    
    # Run YOLO inference on the frame with the desired confidence threshold (0.8 in this case)
    results = model(frame, conf=0.1)  # Run inference

    # Create a new text file for each frame
    frame_counter += 1
    frame_text_file = os.path.join(output_dir, f"frame_{frame_counter}.txt")  # Name the file uniquely per frame

    with open(frame_text_file, 'w') as file:
        # Write detection results for this frame to the text file
        for result in results:
            for box in result.boxes:
                x1, y1, x2, y2 = map(int, box.xyxy[0])  # Bounding box coordinates
                confidence = box.conf[0].item()  # Confidence score
                class_id = int(box.cls[0])  # Class ID

                # Write the detection details to the text file
                file.write(f"{class_id} {x1} {y1} {x2} {y2} {confidence:.2f}\n")

    # Draw the detections on the frame
    for result in results:
        for box in result.boxes:
            x1, y1, x2, y2 = map(int, box.xyxy[0])  # Bounding box coordinates
            confidence = box.conf[0].item()  # Confidence score
            class_id = int(box.cls[0])  # Class ID

            # Draw rectangle and label on the frame
            cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
            cv2.putText(
                frame, f"{model.names[class_id]}: {confidence:.2f}", (x1, y1 - 10),
                cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2
            )

    # Resize and display the window properly
    cv2.namedWindow("YOLO Detection", cv2.WINDOW_NORMAL)  # Allows resizing
    cv2.resizeWindow("YOLO Detection", WIDTH, HEIGHT)  # Set to match camera resolution
    cv2.imshow("YOLO Detection", frame)

    # Press 'q' to exit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the webcam and close windows
cap.release()
cv2.destroyAllWindows()
