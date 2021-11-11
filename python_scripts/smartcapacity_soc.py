#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Mar 13 14:41:06 2019

@author: erhan
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data_path = "../collected_data/2020 08 26_data_erhan.txt"
#data = pd.read_csv(data_path,sep=':',skiprows=520, nrows=50)
data = pd.read_csv(data_path,sep=':')


data.columns = ['Time(Minutes)','Counter','Voltage(V)', 'Current(A)','Velocity(km/h)','SoC']
data = data.drop(['Time(Minutes)'], axis=1)
data = data.drop(['Counter'], axis=1)
sample_counts = data.shape[0]
x=pd.Series(np.arange(0, sample_counts/60,1/60))
data = pd.concat([x, data], axis=1)
data.columns = ['Time(Minutes)','Voltage(V)', 'Current(A)','Velocity(km/h)','SoC']


fig = plt.figure()
ax = fig.add_subplot(111)
data.plot(x='Time(Minutes)', y=['Voltage(V)', 'Current(A)', 'Velocity(km/h)','SoC'], figsize=(10,20), grid=True,title='Smart Car Data '+data_path,ax=ax)

###################################
bbox = dict(boxstyle="round", fc="0.8")
arrowprops = dict(
    arrowstyle = "->",
    connectionstyle = "angle,angleA=0,angleB=90,rad=10")

ymax = data['Voltage(V)'].max()
xmax = data['Time(Minutes)'][data['Voltage(V)'].idxmax()]
text= "x={:.3f}, y={:.3f}".format(xmax, ymax)
ax.annotate(text,
            xy=(xmax, ymax), xytext=(xmax, ymax-350), textcoords='offset pixels',
            bbox=bbox, arrowprops=arrowprops)

ymin = data['Voltage(V)'].min()
xmin = data['Time(Minutes)'][data['Voltage(V)'].idxmin()]
text= "x={:.3f}, y={:.3f}".format(xmin, ymin)
ax.annotate(text,
            xy=(xmin, ymin), xytext=(xmin-300, ymin-350), textcoords='offset pixels',
            bbox=bbox, arrowprops=arrowprops)
#####################################
bbox = dict(boxstyle="round", fc="0.8")
arrowprops = dict(
    arrowstyle = "->",
    connectionstyle = "angle,angleA=0,angleB=90,rad=10")

ymax = data['Current(A)'].max()
xmax = data['Time(Minutes)'][data['Current(A)'].idxmax()]
text= "x={:.3f}, y={:.3f}".format(xmax, ymax)
ax.annotate(text,
            xy=(xmax, ymax), xytext=(xmax, ymax+50), textcoords='offset pixels',
            bbox=bbox, arrowprops=arrowprops)                                                                                                                                                                                                                                                           

ymin = data['Current(A)'].min()
xmin = data['Time(Minutes)'][data['Current(A)'].idxmin()]
text= "x={:.3f}, y={:.3f}".format(xmin, ymin)
ax.annotate(text,
            xy=(xmin, ymin), xytext=(xmin, ymin+120), textcoords='offset pixels',
            bbox=bbox, arrowprops=arrowprops)
#####################################
bbox = dict(boxstyle="round", fc="0.8")
arrowprops = dict(
    arrowstyle = "->",
    connectionstyle = "angle,angleA=0,angleB=90,rad=10")

ymax = data['Velocity(km/h)'].max()
xmax = data['Time(Minutes)'][data['Velocity(km/h)'].idxmax()]
text= "x={:.3f}, y={:.3f}".format(xmax, ymax)
ax.annotate(text,
            xy=(xmax, ymax), xytext=(xmax, ymax), textcoords='offset pixels',
            bbox=bbox, arrowprops=arrowprops)

ymin = data['Velocity(km/h)'].min()
xmin = data['Time(Minutes)'][data['Velocity(km/h)'].idxmin()]
text= "x={:.3f}, y={:.3f}".format(xmin, ymin)
ax.annotate(text,
            xy=(xmin, ymin), xytext=(xmin, ymin), textcoords='offset pixels',
            bbox=bbox, arrowprops=arrowprops)
#####################################

#####################################
bbox = dict(boxstyle="round", fc="0.8")
arrowprops = dict(
    arrowstyle = "->",
    connectionstyle = "angle,angleA=0,angleB=90,rad=10")

ymax = data['SoC'].max()
xmax = data['Time(Minutes)'][data['SoC'].idxmax()]
text= "x={:.3f}, y={:.3f}".format(xmax, ymax)
ax.annotate(text,
            xy=(xmax, ymax), xytext=(xmax, ymax-20), textcoords='offset pixels',
            bbox=bbox, arrowprops=arrowprops)

ymin = data['SoC'].min()
xmin = data['Time(Minutes)'][data['SoC'].idxmin()]
text= "x={:.3f}, y={:.3f}".format(xmin, ymin)
ax.annotate(text,
            xy=(xmin, ymin), xytext=(xmin-200, ymin), textcoords='offset pixels',
            bbox=bbox, arrowprops=arrowprops)
#####################################

plt.tight_layout()


av_cur = data["Current(A)"].mean()
av_vol = data["Voltage(V)"].mean()
av_speed = data["Velocity(km/h)"].mean()

data['Power'] = data['Voltage(V)']*data['Current(A)']
data['BattEnergy(kWh)'] = -data['Power'].cumsum()/3600/1000

data['RegCurrent'] = (abs(data['Current(A)']) + data['Current(A)'])/2
data['Regenerated(kWh)'] = data['Voltage(V)']*data['RegCurrent']
data['Regenerated(kWh)'] = data['Regenerated(kWh)'].cumsum()/3600/1000

data['BattCurrent'] = (abs(data['Current(A)']) - data['Current(A)'])/2
data['TotalEnergy(kWh)'] = data['Voltage(V)']*data['BattCurrent']
data['TotalEnergy(kWh)'] = data['TotalEnergy(kWh)'].cumsum()/3600/1000

data = data[['Time(Minutes)','Velocity(km/h)','Voltage(V)','Current(A)','Power','BattCurrent','RegCurrent','TotalEnergy(kWh)','BattEnergy(kWh)','Regenerated(kWh)','SoC']]


fig, (ax1, ax2) = plt.subplots(nrows=2, ncols=1)

# Use ax1 to plot Bhutan
data.plot(x='Time(Minutes)', y='SoC', legend=True, ax=ax1)
ax1.set_title("SoC "+data_path)

# Use ax2 to plot Iran
data.plot(x='Time(Minutes)', y='Current(A)', legend=True, ax=ax2)
ax2.set_title('Current')

#####################################
bbox = dict(boxstyle="round", fc="0.8")
arrowprops = dict(
    arrowstyle = "->",
    connectionstyle = "angle,angleA=0,angleB=90,rad=10")

ymax = data['Current(A)'].max()
xmax = data['Time(Minutes)'][data['Current(A)'].idxmax()]
text= "x={:.3f}, y={:.3f}".format(xmax, ymax)
ax2.annotate(text,
            xy=(xmax, ymax), xytext=(xmax+20, ymax-50), textcoords='offset pixels',
            bbox=bbox, arrowprops=arrowprops)

ymin = data['Current(A)'].min()
xmin = data['Time(Minutes)'][data['Current(A)'].idxmin()]
text= "x={:.3f}, y={:.3f}".format(xmin, ymin)
ax2.annotate(text,
            xy=(xmin, ymin), xytext=(xmin-200, ymin+50), textcoords='offset pixels',
            bbox=bbox, arrowprops=arrowprops)

ymax = data['SoC'].max()
xmax = data['Time(Minutes)'][data['SoC'].idxmax()]
text= "x={:.3f}, y={:.3f}".format(xmax, ymax)
ax1.annotate(text,
            xy=(xmax, ymax), xytext=(xmax, ymax-50), textcoords='offset pixels',
            bbox=bbox, arrowprops=arrowprops)

ymin = data['SoC'].min()
xmin = data['Time(Minutes)'][data['SoC'].idxmin()]

text= "x={:.3f}, y={:.3f}".format(xmin, ymin)
ax1.annotate(text,
            xy=(xmin, ymin), xytext=(xmin-250, ymin), textcoords='offset pixels',
            bbox=bbox, arrowprops=arrowprops)

plt.tight_layout()

#####################################


fig, (ax1, ax2, ax3) = plt.subplots(nrows=3, ncols=1)

data.plot(x='Time(Minutes)', y='TotalEnergy(kWh)', legend=True, ax=ax1)
ax1.set_title("Total Energy(kWh) "+data_path)

ymax = data['TotalEnergy(kWh)'].max()
xmax = data['Time(Minutes)'][data['TotalEnergy(kWh)'].idxmax()]
text= "{:.3f}".format(ymax)
ax1.annotate(text,
            xy=(xmax, ymax), xytext=(xmax-250, ymax+30), textcoords='offset pixels',
            bbox=bbox, arrowprops=arrowprops)

data.plot(x='Time(Minutes)', y='BattEnergy(kWh)', legend=True, ax=ax2)
ax2.set_title('Battery Energy (kWh)')

ymax = data['BattEnergy(kWh)'].max()
xmax = data['Time(Minutes)'][data['BattEnergy(kWh)'].idxmax()]
text= "{:.3f}".format(ymax)
ax2.annotate(text,
            xy=(xmax, ymax), xytext=(xmax-250, ymax+30), textcoords='offset pixels',
            bbox=bbox, arrowprops=arrowprops)

data.plot(x='Time(Minutes)', y='Regenerated(kWh)', legend=True, ax=ax3)
ax3.set_title('Regenerated Energy (kWh)')

ymax = data['Regenerated(kWh)'].max()
xmax = data['Time(Minutes)'][data['Regenerated(kWh)'].idxmax()]
text= "{:.3f}".format( ymax)
ax3.annotate(text,
            xy=(xmax, ymax), xytext=(xmax-250, ymax+30), textcoords='offset pixels',
            bbox=bbox, arrowprops=arrowprops)

plt.tight_layout()

