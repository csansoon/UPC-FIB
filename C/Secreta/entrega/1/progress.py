from colored import fg, bg, attr

def printProgressBar (iteration, total, prefix = '', suffix = '', decimals = 1, length = 100, fill = f'█', empty = f'█', printEnd = "\r"):
    """
    ████░░░░
    Call in a loop to create terminal progress bar
    @params:
        iteration   - Required  : current iteration (Int)
        total       - Required  : total iterations (Int)
        prefix      - Optional  : prefix string (Str)
        suffix      - Optional  : suffix string (Str)
        decimals    - Optional  : positive number of decimals in percent complete (Int)
        length      - Optional  : character length of bar (Int)
        fill        - Optional  : bar fill character (Str)
        printEnd    - Optional  : end character (e.g. "\r", "\r\n") (Str)
    """
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filledLength = int(length * iteration // (total - 1))
    bar = fg('dark_olive_green_3a') + fill * filledLength + fg('dark_gray') + empty * (length - filledLength) + attr(0)
    print(f'\r{prefix} {bar} {percent}% {suffix}', end = printEnd)
    # Print New Line on Complete
    if iteration == total: 
        print()