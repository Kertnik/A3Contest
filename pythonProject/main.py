import numpy as np
import matplotlib.pyplot as plt


# Load data from the txt file
def load_data(file_path):
    with open(file_path, 'r') as file:
        data = file.read()
        points = []
        for point in data.split(')')[:-1]:  # Split by ')' and ignore the last empty part
            point = point.replace('(', '').strip()  # Remove '(' and extra spaces
            x, y, z = map(float, point.split(','))  # Split by comma and convert to float
            points.append((x, y, z))
        return np.array(points)


# Create a structured grid for surface plotting
def create_grid(points):
    x = points[:, 0]
    y = points[:, 1]
    z = points[:, 2]

    # Create a grid
    xi = np.linspace(x.min(), x.max(), 100)
    yi = np.linspace(y.min(), y.max(), 100)
    xi, yi = np.meshgrid(xi, yi)

    # Interpolate Z values to fit the grid
    from scipy.interpolate import griddata
    zi = griddata((x, y), z, (xi, yi), method='cubic')

    return xi, yi, zi


# Plot the 3D surface
def plot_surface(xi, yi, zi):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(xi, yi, zi, cmap='viridis', edgecolor='none')
    ax.set_xlabel('X axis')
    ax.set_ylabel('Y axis')
    ax.set_zlabel('Z axis')
    plt.colorbar(surf)
    #rotate the axes and create a video
    ax.view_init(elev=30, azim=30)
    plt.show()



# Path to your txt file
file_path = 'result.txt'

# Load and process data
points = load_data(file_path)
xi, yi, zi = create_grid(points)

# Plot the 3D surface
plot_surface(xi, yi, zi)
