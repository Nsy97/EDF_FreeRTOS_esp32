import altair as alt
import pandas as pd
from vega_datasets import data
#install vegadatasets, pandas, altair package

# Read the log file into a pandas dataframe
#df = pd.read_csv("EDF_Logz.csv",skiprows=3, names=['Ignore', 'Tickcount', 'Tasks'])
df = pd.read_csv("EDF_Log_example.csv")
df = df[['Tickcount', 'Tasks']]  # Drop the unwanted first column

print(df.to_string())

#column 1 (x-axis) = Tickcount, column 2 (y axis) = Tasks
chart = alt.Chart(df).mark_rect().encode(
    x=alt.X('Tickcount',type='nominal',title='Tickcount'),
    y=alt.Y('Tasks', type='nominal',title='Tasks',),
    color='Tasks:N',
).properties(
    title="Task scheduling",
    width=1000,
    height=100,
).configure_axisX(grid=True,gridColor='gray', gridWidth=0.3,bandPosition=0,
).configure_axisY(grid=False,bandPosition=0,
)

# Display the chart
chart.save('chart_Task4.html')
#chart.show()


