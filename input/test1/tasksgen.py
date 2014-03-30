import sys
import random

f = open('tasks', 'w')
f.write('# SensorID: rate, sensorID: rate, ...\n')
f.write('0:1,1:2\n')
f.write('# Id time num_sub sensor input output compute delay\n')

id = 0
time = 0
step = 600
compute = 3200
delay = 1000
for i in range (0, 40):
  f.write('%(id)d %(time)lf 32 0 1 1 %(compute)d %(delay)d\n' 
      %{"id":id,"time":time,"compute":compute,"delay":delay})
  id = id + 1
  f.write('%(id)d %(time)lf 32 1 1 1 %(compute)d %(delay)d\n' 
      %{"id":id,"time":time,"compute":compute,"delay":delay})
  id = id + 1
  f.write('%(id)d %(time)lf 32 1 1 1 %(compute)d %(delay)d\n' 
      %{"id":id,"time":time,"compute":compute,"delay":delay})
  time += step
  id = id + 1

f.close()

