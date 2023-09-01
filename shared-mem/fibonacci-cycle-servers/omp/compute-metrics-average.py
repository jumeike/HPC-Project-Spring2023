import sys

inst_retired = 0.0
cycles = 0.0
branches = 0.0
branch_misses = 0.0
cpu_clk_unhalted = 0.0
cycle_activity_stalls_total = 0.0
cpu_clk_unhalted_thread = 0.0

def parse_perf_output(filename):
    with open(filename, 'r') as f:
        data = f.readlines()
    ipc = None
    bmr = None
    cpu_stalled_cycles = None
    elapsed_time = None 

    for line in data:
        if 'inst_retired.any' in line:
            try:
                global inst_retired
                global cycles
                inst_retired += float(line.split()[0].replace(',', ''))
                cycles += float(data[data.index(line) + 1].split()[0].replace(',', ''))
                ipc = inst_retired / cycles
                #print(f'ipc: {ipc}')
            except ValueError:
                pass
        elif 'branch-misses' in line:
            try:
                global branches
                global branch_misses
                branches += float(data[data.index(line) - 1].split()[0].replace(',', ''))
                branch_misses += float(line.split()[0].replace(',', ''))
                bmr = round(branch_misses / branches * 100, 4)
                #print(f'bmr: {bmr}')
            except ValueError:
                pass
        elif 'cpu_clk_unhalted.thread' in line:
            try:
                global cpu_clk_unhalted
                global cycle_activity_stalls_total
                cpu_clk_unhalted += float(line.split()[0].replace(',', ''))
                cycle_activity_stalls_total += float(data[data.index(line) + 1].split()[0].replace(',', ''))
                cpu_stalled_cycles = round(cycle_activity_stalls_total / cpu_clk_unhalted * 100, 4)
                #print(f'cpu_stalled_cycles: {cpu_stalled_cycles}')
            except ValueError:
                pass
        elif 'Elapsed time:' in line:
            try:
                elapsed_time = float(line.split()[2])
            except ValueError:
                pass

    return ipc, bmr, cpu_stalled_cycles, elapsed_time

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: python perf_analysis.py <perf_output_filename1> <perf_output_filename2> ...')
        sys.exit(1)

    total_ipc = 0
    total_bmr = 0
    total_cpu_stalled_cycles = 0
    total_elapsed_time = 0
    num_files = len(sys.argv) - 1

    for i in range(1, len(sys.argv)):
        perf_output_filename = sys.argv[i]
        ipc, bmr, cpu_stalled_cycles, elapsed_time = parse_perf_output(perf_output_filename)

        if ipc is not None:
            total_ipc = ipc
        if bmr is not None:
            total_bmr = bmr
        if cpu_stalled_cycles is not None:
            total_cpu_stalled_cycles = cpu_stalled_cycles
        if elapsed_time is not None:
            total_elapsed_time += elapsed_time

    avg_ipc = total_ipc
    avg_bmr = total_bmr
    avg_cpu_stalled_cycles = cpu_stalled_cycles
    avg_elapsed_time = round(total_elapsed_time / num_files,6)

    print(f'Average IPC: {avg_ipc:.4f}')
    print(f'Average Branch Misprediction Rate: {avg_bmr:.4f}%')
    #print(f'Average CPU Stalled Cycles: {avg_cpu_stalled_cycles:.4f}%')
    print(f'Average Elapsed Time: {avg_elapsed_time:.6f} seconds')
