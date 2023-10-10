import os
import glob
from plotly.subplots import make_subplots
import plotly.graph_objects as go
import re

def plotter():
    files       =  [txt for txt in glob.glob("results/*.txt")]
    # Log file format
    # num_threads = 4 computed pi = 3.141592653589683 in 0.071467046000180 seconds threads =  4 % error = -0.000000000003421
    pattern     =  re.compile("num_threads\s+=\s+(\d+).+in\s+(\d+.\d+).+error = (-*\d+.\d+)")
    total_tests = float(len(files))
    acc_runtimes = []
    acc_errors    = []
    acc_speedups   = []
    for txt in files:
        with open(txt) as fd:
            # get both time and thread lists
            threads, runtimes, errors  = zip(*[(float(match.group(1)), float(match.group(2)), float(match.group(3))) for line in fd.readlines() for match in [pattern.search(line)] if match])
            
            # speedup T(1)/Tn
            speed_ups = [runtimes[0]/runt for runt in runtimes]
                
            # first iteration acc and error are empty
            if len(acc_runtimes) == 0:
                acc_runtimes = [0.0]*len(runtimes)
                acc_errors = [0.0]*len(runtimes)
                acc_speedups = [0.0]*len(runtimes)

            # add previous runtime
            acc_runtimes = [sum(runt) for runt in zip(runtimes, acc_runtimes)]
            
            # add previous error
            acc_errors = [sum(error) for error in zip(errors, acc_errors)]

            # add previous speedup
            acc_speedups = [sum(speedup) for speedup in zip(speed_ups, acc_speedups)] 

    
    average_runtimes = [acc_time/total_tests for acc_time in acc_runtimes]
    average_errors = [acc_error/total_tests for acc_error in acc_errors]
    average_speedups = [acc_speedup/total_tests for acc_speedup in acc_speedups]

    fig = make_subplots(rows=3, cols=1, subplot_titles=("Threads and Avg Runtimes","Threads and Avg Error", 'Threads and Speedup'))

    fig.add_trace(
        go.Scatter(x=threads, y=average_runtimes),
        row=1, col=1
    )

    fig.add_trace(
        go.Scatter(x=threads, y=average_errors),
        row=2, col=1
    )

    fig.add_trace(
        go.Scatter(x=threads, y=average_speedups),
        row=3, col=1
    )

    # edit axis labels
    fig['layout']['xaxis']['title']='Num of Threads'
    fig['layout']['xaxis2']['title']='Num of Threads'
    fig['layout']['xaxis3']['title']='Num of Threads'
    fig['layout']['yaxis']['title']='Average Runtime (s)'
    fig['layout']['yaxis2']['title']='Average % Error'
    fig['layout']['yaxis3']['title']='Average Speedup'
    fig.show()

if __name__ == "__main__":
    plotter()
