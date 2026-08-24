import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation


df=pd.read_csv("myenv/Depth Data.csv")  #reads data from the csv file

points=df["Point"]  # Creates to series from the dataframe
data=df["Depth (m)"]

data=pd.to_numeric(data,errors="coerce")  #Converts the data series which is string to float while turning all non numeric numbers to NaN
change=data.diff().abs()  #Outputs a series of the absolute difference between consecutive values of the series
data[change>100]=np.nan  #Converts all values with a delta of over 100 to NaN

data=data.ffill() #Fills all the NaN values to be the same as the previous reading

cleaned_data=data.rolling(window=5,min_periods=1,center=True).mean()  #Creates a new series that is the mean of five values around it in the original series
fig, axis=plt.subplots() #Setting up the graph
axis.set_xlim(0,len(points))
axis.set_ylim(min(data)-50,0)

line, = axis.plot([],[]) 

def update_frames(frames): #function to update frames that updates the graph each second
    x=range(frames+1)
    y=cleaned_data.iloc[:frames+1]

    line.set_data(x,y)
    return line,

animation=FuncAnimation(  
    fig=fig,func=update_frames,frames=len(data),interval=1000,blit=True,repeat=False #This is he function that creates the animation
)

plt.show()
