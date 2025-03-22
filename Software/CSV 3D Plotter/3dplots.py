import plotly
from plotly.offline import plot  # Import the offline plot function
import plotly.graph_objs as go
import pandas as pd

# Load the CSV file
df = pd.read_csv('datalog-copy.csv')
df.head()

# Extract data from the CSV
lat = df['GPS LATITUDE'].values
lon = df['GPS LONGITUDE'].values
altitude = df['GPS ALTITUDE'].values

# Define the 3D scatter plot
trace = go.Scatter3d(
    x=lat, y=lon, z=altitude,
    marker=dict(
        size=3,
        color=altitude,  # Color markers based on altitude
        colorscale='Viridis',
        opacity=0.5
    ),
    line=dict(
        color='#1f77b4',
        width=2
    )
)

data = [trace]

# Define the layout for the plot
layout = dict(
    width=800,
    height=700,
    autosize=False,
    title='GPS 3D PLOT',
    scene=dict(
        xaxis=dict(
            title='Latitude(degree)',
            gridcolor='rgb(255, 255, 255)',
            zerolinecolor='rgb(255, 255, 255)',
            showbackground=True,
            backgroundcolor='rgb(230, 230,230)'
        ),
        yaxis=dict(
            title='Longitude(degree)',
            gridcolor='rgb(255, 255, 255)',
            zerolinecolor='rgb(255, 255, 255)',
            showbackground=True,
            backgroundcolor='rgb(230, 230,230)'
        ),
        zaxis=dict(
            title='Altitude(m)',
            gridcolor='rgb(255, 255, 255)',
            zerolinecolor='rgb(255, 255, 255)',
            showbackground=True,
            backgroundcolor='rgb(230, 230,230)'
        ),
        camera=dict(
            up=dict(
                x=0,
                y=0,
                z=1
            ),
            eye=dict(
                x=-1.7428,
                y=1.0707,
                z=0.7100,
            )
        ),
        aspectratio=dict(x=1, y=1, z=0.7),
        aspectmode='manual'
    ),
)

# Create the figure
fig = dict(data=data, layout=layout)

# Generate and open the plot in the browser
plot(fig, filename='gps_3d_plot.html')  # This saves the plot and opens it in your browser