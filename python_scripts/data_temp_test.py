# -*- coding: utf-8 -*-
"""
Created on Fri Aug 28 13:57:46 2020

@author: erhan
"""


import pandas as pd
import numpy as np
import os.path
import matplotlib.pyplot as plt



# data from 2019.07 to 2020.08

for days in range(31):
    data_file_name = "../collected_data/2020 08 %02d_data_erhan.txt" % (days+1)
    if(os.path.isfile(data_file_name)):
        data = pd.read_csv(data_file_name,sep=':',header=None)
        data = data.drop([0], axis=1)
        data = data.drop([1], axis=1)
        sample_counts = data.shape[0]
        x=pd.Series(np.arange(0, sample_counts/60,1/60))
        data = pd.concat([x, data], axis=1)
        data.columns = ['Time(Minutes)','Voltage(V)', 'Current(A)','Velocity(km/h)','SoC']
    temp_file_name = "../collected_data/2020 08 %02d_temp_erhan.txt" % (days+1)
    if(os.path.isfile(temp_file_name)):
        temp = pd.read_csv(temp_file_name,sep=':',header=None)
        temp = temp.drop([0], axis=1)
        temp = temp.drop([1], axis=1)
        sample_counts = temp.shape[0]
        x=pd.Series(np.arange(0, sample_counts/60,1/60))
        temp = pd.concat([x, temp], axis=1)
        #temp.columns = ['Time(Minutes)','M1_1', 'M1_2','M1_3','M2_1', 'M2_2','M2_3','M3_1', 'M3_2','M3_3']
        fig, (ax1, ax2) = plt.subplots(nrows=2, ncols=1)
        fig.canvas.manager.full_screen_toggle() # toggle fullscreen mode
        mngr = plt.get_current_fig_manager()
        mngr.window.showMaximized()
        #mngr.window.setGeometry(50,50,500, 545)
        plot_cols = [1,2,3,4]
        data.plot(x=data.columns[0], y=data.columns[plot_cols], figsize=(10,20), grid=True,title='Smart Car Temperature Data '+data_file_name, ax=ax1)
        plot_cols = [1,2,3,4,5,6,7,8,9]
        temp.plot(x=temp.columns[0], y=temp.columns[plot_cols], figsize=(10,20), grid=True,title='Smart Car Temperature Data '+temp_file_name, ax=ax2)
        plt.tight_layout()

        

