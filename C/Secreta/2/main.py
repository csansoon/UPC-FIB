from Polynomial import *
import time
import matplotlib.pyplot as plt
import numpy as np

def measure_time(func, *args, tables=None):
    if tables == None:
        start_time = time.perf_counter_ns()
        func(*args)
        total_time = time.perf_counter_ns() - start_time
    else:
        start_time = time.perf_counter_ns()
        func(*args, tables=tables)
        total_time = time.perf_counter_ns() - start_time
    return total_time


tests = []
p_results = []
t_results = []

a = Polynomial(0b01010111)
b = Polynomial(0b10000011)

tables = GF_tables(2) # Precalcular las tablas previamente usando un generador válido cualquiera


#! GF product p vs GF product t
tests.append('GF_product(a,b)')
p_results.append(measure_time(GF_product_p, a, b))
t_results.append(measure_time(GF_product_t, a, b, tables=tables))

#! GF_product_p(a,0x02) vs GF_product_t(a,0x02)
tests.append('GF_product(a,0x02)')
p_results.append(measure_time(GF_product_p, a, Polynomial(0x02)))
t_results.append(measure_time(GF_product_t, a, Polynomial(0x02), tables=tables))

#! GF_product_p(a,0x03) vs GF_product_t(a,0x03)
tests.append('GF_product(a,0x03)')
p_results.append(measure_time(GF_product_p, a, Polynomial(0x03)))
t_results.append(measure_time(GF_product_t, a, Polynomial(0x03), tables=tables))

#! GF_product_p(a,0x09) vs GF_product_t(a,0x09)
tests.append('GF_product(a,0x09)')
p_results.append(measure_time(GF_product_p, a, Polynomial(0x09)))
t_results.append(measure_time(GF_product_t, a, Polynomial(0x09), tables=tables))

#! GF_product_p(a,0x0B) vs GF_product_t(a,0x0B)
tests.append('GF_product(a,0x0B)')
p_results.append(measure_time(GF_product_p, a, Polynomial(0x0B)))
t_results.append(measure_time(GF_product_t, a, Polynomial(0x0B), tables=tables))

#! GF_product_p(a,0x0D) vs GF_product_t(a,0x0D)
tests.append('GF_product(a,0x0D)')
p_results.append(measure_time(GF_product_p, a, Polynomial(0x0D)))
t_results.append(measure_time(GF_product_t, a, Polynomial(0x0D), tables=tables))

#! GF_product_p(a,0x0E) vs GF_product_t(a,0x0E)
tests.append('GF_product(a,0x0E)')
p_results.append(measure_time(GF_product_p, a, Polynomial(0x0E)))
t_results.append(measure_time(GF_product_t, a, Polynomial(0x0E), tables=tables))


#* GRAPHS

x = np.arange(len(tests))  # the label locations
width = 0.35  # the width of the bars

fig, ax = plt.subplots()
rects1 = ax.bar(x - width/2, p_results, width, label='GF_product_p')
rects2 = ax.bar(x + width/2, t_results, width, label='GF_product_t')

# Add some text for labels, title and custom x-axis tick labels, etc.
ax.set_ylabel('Time (ns)')
ax.set_title('Difference between GF_product_p and GF_product_t execution times')
ax.set_xticks(x)
ax.set_xticklabels(tests)
ax.legend()

ax.bar_label(rects1, padding=3)
ax.bar_label(rects2, padding=3)

fig.tight_layout()

plt.show()