import matplotlib.pyplot as plt
import numpy as np
import os
import re
from collections import defaultdict


def read_and_plot_by_prefix(file_pattern="*_res*.txt"):
    # Get list of matching files
    files = [f for f in os.listdir('.') if re.match(file_pattern.replace('*', '.*'), f)]
    if not files:
        print("No matching files found.")
        return

    # Group files by prefix
    file_groups = defaultdict(list)
    for file in files:
        prefix = file.split('_res')[0]
        file_groups[prefix].append(file)

    for prefix, file_list in file_groups.items():
        plt.figure(figsize=(10, 6))
        for file in sorted(file_list):
            with open(file, 'r') as f:
                content = f.read()
            # Extract points (x, y)
            points = re.findall(r'\(([^,]+),\s*([^)]+)\)', content)
            x, y = zip(*[(float(px), float(py)) for px, py in points])

            # Plot the data with the file name as the label
            plt.plot(x, y, marker='o', label=file)

        # Customize the plot for this prefix
        plt.title(f"Graphs for {prefix}")
        plt.xlabel("X-axis")
        plt.ylabel("Y-axis")
        plt.legend(title="File Names")  # Include legend with file names
        plt.grid(True)
        plt.show()


# Run the function
read_and_plot_by_prefix()
