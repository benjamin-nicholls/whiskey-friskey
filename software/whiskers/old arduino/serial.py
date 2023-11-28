import serial
import matplotlib.pyplot as plt
from drawnow import drawnow

# Function to plot data
def plot_data():
    plt.subplot(3, 1, 1)
    plt.plot(x_data, y_data1, label='X-axis')
    plt.title('Magnetic Field Strength')
    plt.ylabel('uT')
    plt.legend()

    plt.subplot(3, 1, 2)
    plt.plot(x_data, y_data2, label='Y-axis')
    plt.ylabel('uT')
    plt.legend()

    plt.subplot(3, 1, 3)
    plt.plot(x_data, y_data3, label='Z-axis')
    plt.xlabel('Time')
    plt.ylabel('uT')
    plt.legend()

# Initialize Serial Communication
ser = serial.serial('COM6', 115200)  

# Initialize data arrays
x_data = []
y_data1 = []
y_data2 = []
y_data3 = []

# Set up the plot
plt.ion()  # Turn on interactive mode
fig = plt.figure()

# Main loop
while True:
    try:
        # Read data from Arduino
        data = ser.readline().decode('utf-8').strip().split('\t')

        # Parse and append data
        if len(data) == 3:
            x_data.append(len(x_data) + 1)
            y_data1.append(float(data[0]))
            y_data2.append(float(data[1]))
            y_data3.append(float(data[2]))

            # Limit data points for better visualization
            if len(x_data) > 50:
                x_data.pop(0)
                y_data1.pop(0)
                y_data2.pop(0)
                y_data3.pop(0)

            # Plot the data
            drawnow(plot_data)

    except KeyboardInterrupt:
        break

# Close the serial connection
ser.close()
