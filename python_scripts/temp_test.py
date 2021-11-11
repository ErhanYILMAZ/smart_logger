# -*- coding: utf-8 -*-
"""
Created on Mon Jul  6 18:42:53 2020

@author: erhan
"""

import pandas as pd
import numpy as np
import os.path

for days in range(31):
    data_file_name = "../collected_data/2020 03 %02d_temp_erhan.txt" % (days+1)
    if(os.path.isfile(data_file_name)):
        data = pd.read_csv(data_file_name,sep=':',header=None)
        data = data.drop([0], axis=1)
        data = data.drop([1], axis=1)
        sample_counts = data.shape[0]
        x=pd.Series(np.arange(0, sample_counts/60,1/60))
        data = pd.concat([x, data], axis=1)
        data.columns = ['Time(Minutes)','M1_1', 'M1_2','M1_3','M2_1', 'M2_2','M2_3','M3_1', 'M3_2','M3_3']
        plot_cols = [1,2,3,4,5,6,7,8,9]
        data.plot(x=data.columns[0], y=data.columns[plot_cols], figsize=(10,20), grid=True,title='Smart Car Temperature Data '+data_file_name)
