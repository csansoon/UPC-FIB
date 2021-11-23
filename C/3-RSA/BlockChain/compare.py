from random import randint
from blockchain import *
import time
import plotly.express as px
from plotly.subplots import make_subplots
import plotly.graph_objects as go

import dash
#! import dash_core_components as dcc
#! import dash_html_components as html
from dash import dcc
from dash import html
import pandas as pd

print('Initializing keys and messages...', end='\r')

messages = []
for i in range(100):
    messages.append(randint(2**512,  2**1024))

claus = {
    '512': rsa_key(bits_modulo=512),
    '1024': rsa_key(bits_modulo=1024),
    '2048': rsa_key(bits_modulo=2048),
    '4096': rsa_key(bits_modulo=4096)}

data = []

print('Signing messages...                       ', end='\r')

for bits, clau in claus.items():
    start = time.perf_counter()
    for msg in messages:
        clau.sign(msg)
    total_time = time.perf_counter() - start
    data.append({
        'clau': bits,
        'time (seconds)': total_time,
        'sign': 'fast'
    })
    start = time.perf_counter()
    for msg in messages:
        clau.sign_slow(msg)
    total_time = time.perf_counter() - start
    data.append({
        'clau': bits,
        'time (seconds)': total_time,
        'sign': 'slow'
    })

print('Creating plot...     ', end='\r')

fig = px.bar(data, x='clau', y='time (seconds)', color='sign', barmode='group')
fig.update_layout(
    autosize=True,
    height=800
)

print('Initializing internal server...     ', end='\r')

app = dash.Dash(__name__)
app.layout = html.Div(
    children=[
        html.H1(children='Comparació de signatures'),
        dcc.Graph(
            id='data',
            figure=fig
        ),
    ])
app.run_server(debug=False)
print('Done                                    ')
