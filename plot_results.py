import matplotlib.pyplot as plt
import csv
import argparse
import os

parser = argparse.ArgumentParser(description='Plot results based on test condition.')
parser.add_argument('--test_condition', choices=['n', 'k', 't'], default=None, help='The test condition to plot: n, k, or t.')
args = parser.parse_args()

n_values = []
run_times = []
t_values = []
k_values = []

with open('results.csv', 'r') as csvfile:
    reader = csv.reader(csvfile)
    next(reader)  
    for row in reader:
        n_values.append(int(row[0]))
        t_values.append(int(row[1]))
        k_values.append(int(row[2]))
        run_times.append(float(row[3]))


if args.test_condition == 'n':  # n is NOT fixed 
    plt.plot(n_values, run_times, marker='o')
    plt.title(f'Running Time vs. String Length (n)\nFixed t={t_values[0]}, k={k_values[0]}')
    plt.xlabel('String Length (n)')

elif args.test_condition == 't':   # t is NOT fixed
    plt.plot(t_values, run_times, marker='o')
    plt.title(f'Running Time vs. Number of Deletions (t)\nFixed k={k_values[0]}, n={n_values[0]}')
    plt.xlabel('Number of Deletions (t)')

elif args.test_condition == 'k':   # k is NOT fixed
    plt.plot(k_values, run_times, marker='o')
    plt.title(f'Running Time vs. Number of Strings (k)\nFixed t={t_values[0]}, n={n_values[0]}')
    plt.xlabel('Number of Strings (k)')


plt.ylabel('Running Time (nanoseconds)')
plt.grid(True)

output_directory = 'empirical_results'
if not os.path.exists(output_directory):
    os.makedirs(output_directory)

file_name = f"{output_directory}/result_{args.test_condition}.png"


plt.savefig(file_name)

plt.close()  

