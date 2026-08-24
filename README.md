# SEDS-INDUCTION
A repo for all seds inductions

This is my submission for the avionics Induction task 2026-2027

Task - 1:
  This is a simple data fetching and filtering program for a depth sensor that then plots the cleaned data. The difficulties in this 
  task were the corrupted values and the random noise that was there in the data given.

  The non numeric values were removed easily, and the values which were obviously erratic in nature were removed by setting a maximum
  delta between two consecutive values. The value I decided was 100, since the maximum delta that occurred from the obvious anomalies
  were all less than 60, most of them being below 20 aside from a few values. For the values that did exceed 40, I decided they were
  legitimate because the following readings followed the trend that the big changes set, meaning that those fast changes reflected an 
  actual change in depth, whereas for the other erratic changes, they reverted back to around the previous values, meaning they were
  not significant.

  A simple way of cleaning random noise is just to take the average of the readings. There was either the option of median or mean. The 
  median turned out to be too flat and rigid, which did not reflect the changes in the depth, whereas the mean followed the direction 
  of the graph a lot better while eliminating the noise. I also centered the averages instead of taking them from the last 5 readings 
  since the graph was shifted when I didn't.

Task - 2:
  This is a Tinkercad project that uses two sensors, and various instruments to communicate. This is a simulated ship that is sailing,
  that encounters various conditions such as storm or obstacles. There is an anchor to protect against such conditions. You have to 
  ensure to use the anchor within 5 seconds or else the ship will get wrecked which is an irreversible state.
  
  I have defined a data type States that can take all the different states as it's value. This seemed better than using if conditions
  changing the states as there were a lot of potential transitions between the different states and it seemed more appropriate for a
  state machine such as this.

  Everything else is standard. I used an photoresistor, ultrasonic sensor for the readings, and a buzzer, LCD, and LCD for
  communication. I used an I2C LCD since it requires less connections to work with. The wiring is a little messy but I tried to make it
  as clean as possible.


Link to my Tinkercad file:
https://www.tinkercad.com/things/k8rqJn9iLHG/editel?returnTo=%2Fdashboard&sharecode=-VXjKoFIaHMbg7tFNxXQUxBd1Gnz-eK7gC6xNXFL5iw
    
    
      
    
   

  
