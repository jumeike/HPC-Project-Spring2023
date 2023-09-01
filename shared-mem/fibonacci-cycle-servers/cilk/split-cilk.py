import sys
import os

if len(sys.argv) < 2:
    print("Usage: python split_file.py <filename>")
    sys.exit(1)

filename = sys.argv[1]

if not os.path.isfile(filename):
    print(f"Error: {filename} does not exist.")
    sys.exit(1)

split_lines = []
split_index = 1

with open(filename, "r") as input_file:
    for line in input_file:
        if line.startswith("=========================="):
            # Write current split to file
            output_filename = f"{num_threads}-{fib_inputs}-{split_index}.txt"
            with open(output_filename, "w") as output_file:
                output_file.write("".join(split_lines))
            # Increment split index and reset split lines
            split_index += 1
            split_lines = []
        elif line.startswith("Number of threads:"):
            # Extract number of threads from line
            num_threads = line.strip().split(": ")[1]
        elif line.startswith("fib("):
            # Extract fib inputs from line
            fib_inputs = line.strip().split("(")[1].split(")")[0]
        else:
            split_lines.append(line)

# Write final split to file
output_filename = f"{num_threads}-{fib_inputs}-{split_index}.txt"
with open(output_filename, "w") as output_file:
    output_file.write("".join(split_lines))
