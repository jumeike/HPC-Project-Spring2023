import sys

def parse_perf_output(filename):
    with open(filename, 'r') as f:
        data = f.readlines()

    ipc = None
    bmr = None
    cpu_stalled_cycles = None
    elapsed_time = None

    for line in data:
        if 'inst_retired.any' in line:
            inst_retired = float(line.split()[0].replace(',', ''))
            cycles = float(data[data.index(line) + 1].split()[0].replace(',', ''))
            ipc = inst_retired / cycles
        elif 'branch-misses' in line:
            branches = float(data[data.index(line) - 1].split()[0].replace(',', ''))
            branch_misses = float(line.split()[0].replace(',', ''))
            bmr = round(branch_misses / branches * 100, 2)
        elif 'cpu_clk_unhalted.thread' in line:
            cpu_clk_unhalted = float(line.split()[0].replace(',', ''))
            cycle_activity_stalls_total = float(data[data.index(line) + 1].split()[0].replace(',', ''))
            cpu_stalled_cycles = round(cycle_activity_stalls_total / cpu_clk_unhalted * 100, 2)
        elif 'cycles:u' in line:
            cpu_clk_unhalted = float(line.split()[0].replace(',', ''))
            cpu_clk_unhalted_thread = float(data[data.index(line) + 1].split()[0].replace(',', ''))
            cycle_activity_stalls_total = float(data[data.index(line) + 3].split()[0].replace(',', ''))
            cpu_stalled_cycles = round((cycle_activity_stalls_total / cpu_clk_unhalted_thread) * 100, 2)
        elif 'seconds time elapsed' in line:
            elapsed_time = float(line.split()[0])
            
    return ipc, bmr, cpu_stalled_cycles, elapsed_time

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Usage: python perf_analysis.py <perf_output_filename>')
        sys.exit(1)

    perf_output_filename = sys.argv[1]
    ipc, bmr, cpu_stalled_cycles, elapsed_time = parse_perf_output(perf_output_filename)

    if ipc is not None:
        print(f'IPC: {ipc:.2f}')
    else:
        print('Could not compute IPC')

    if bmr is not None:
        print(f'Branch Misprediction Rate: {bmr:.2f}%')
    else:
        print('Could not compute Branch Misprediction Rate')

    if cpu_stalled_cycles is not None:
        print(f'CPU Stalled Cycles: {cpu_stalled_cycles:.2f}%')
    else:
        print('Could not compute CPU Stalled Cycles')
        
    if elapsed_time is not None:
        print(f'Elapsed Time: {elapsed_time:.2f} seconds')
    else:
        print('Could not compute Elapsed Time')

