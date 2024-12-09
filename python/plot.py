import numpy as np
import matplotlib.pyplot as plt
import argparse
import os


def read_data(filename, num_objects=3):
    all_positions = [[] for _ in range(num_objects)]

    with open(filename, "r") as f:
        for line_index, line in enumerate(f):
            line = line.strip()
            if not line:
                continue

            data = line.split(",")
            position = [
                float(data[0].strip()),
                float(data[1].strip()),
                float(data[2].strip()),
            ]

            object_index = line_index % num_objects
            all_positions[object_index].append(position)

    all_positions = [np.array(positions) for positions in all_positions]
    return all_positions


def plot_trajectory(all_positions, labels, output_path):
    if not all_positions:
        print("Error: No positions to plot.")
        return

    fig = plt.figure(figsize=(12, 8))
    ax = fig.add_subplot(111, projection="3d")

    colors = plt.cm.Set1.colors
    for i, positions in enumerate(all_positions):
        x, y, z = positions[:, 0], positions[:, 1], positions[:, 2]
        ax.scatter(x, y, z, label=labels[i], color=colors[i % len(colors)], s=20)

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Z")
    ax.legend(loc="center left", bbox_to_anchor=(1.1, 0.5))
    plt.title("3D Trajectories")
    plt.savefig(output_path, bbox_inches="tight")
    plt.close(fig)


def plot_2d_projection(all_positions, labels, output_path):
    if not all_positions:
        print("Error: No positions to plot.")
        return

    plt.figure(figsize=(12, 8))

    colors = plt.cm.Set1.colors
    for i, positions in enumerate(all_positions):
        x, y = positions[:, 0], positions[:, 1]
        plt.scatter(x, y, label=labels[i], color=colors[i % len(colors)], s=20)

    plt.xlabel("X")
    plt.ylabel("Y")
    plt.title("2D Projections (X vs Y)")
    plt.legend(loc="center left", bbox_to_anchor=(1.1, 0.5))
    plt.savefig(output_path, bbox_inches="tight")
    plt.close()


def main():
    parser = argparse.ArgumentParser(description="Visualize trajectory data")
    parser.add_argument(
        "--filename", type=str, required=True, help="Input data file path"
    )
    parser.add_argument(
        "--output", type=str, help="Output directory for plots (optional)"
    )
    parser.add_argument(
        "--labels",
        type=str,
        help="Comma-separated labels for the objects (optional). "
        "Example: 'Sun,Earth,Moon'",
    )

    args = parser.parse_args()

    output_dir = args.output or os.path.dirname(args.filename)
    os.makedirs(output_dir, exist_ok=True)

    all_positions = read_data(args.filename)
    num_objects = len(all_positions)

    if args.labels:
        labels = [label.strip() for label in args.labels.split(",")]
        if len(labels) != num_objects:
            print(
                f"Error: Number of labels ({len(labels)}) does not match "
                f"the number of objects ({num_objects})."
            )
            return
    else:
        labels = [f"Object {i+1}" for i in range(num_objects)]

    base_filename = os.path.splitext(os.path.basename(args.filename))[0]
    trajectory_plot_path = os.path.join(output_dir, f"{base_filename}_trajectory.png")
    projection_plot_path = os.path.join(
        output_dir, f"{base_filename}_2d_projection.png"
    )

    plot_trajectory(all_positions, labels, trajectory_plot_path)
    plot_2d_projection(all_positions, labels, projection_plot_path)

    print(f"Plots saved in {output_dir}")


if __name__ == "__main__":
    main()
