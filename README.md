# smart_logger
OBDII Can Bus Data Logger Project for Smart Fortwo Electric Car

# What is Smart Logger

Smart Logger project is data logger project that collects data such from Smart fortwo electric car such Battery voltage, current, SoC, Velocity, temperature and so on. This data is stored in SD card. 

I have derived my project from the below preoject and implemented it on the [XMC4500 Relax Kit](https://www.infineon.com/cms/en/product/evaluation-boards/kit_xmc45_relax_v1/)

https://hackaday.com/2017/02/28/reverse-engineering-the-smart-fortwo-can-bus

https://hackaday.io/project/19931-smart-fortwo-can-bus-reverse-engineering

It has 4x20 Character LCD as well. Unfortunately I don't have schematic because I build it up it dev kit. However, it only requires only 4x20 I2C display externally and the pins for all connections can be easily determined from the source code.

Apart from that I have collected data from the smart which is drived in Berlin for almost one year. All data is included in the repo as well.

Data might be used for AI, analyze or scientific purpose. I was planning to analyze this data and maybe train a AI model for research paper during my Phd. However I didn't have time to deal yet. You can use freely also we might do colloboration. Everthing is possible. Don't hesitate to ask me. :)


# Python Scripts

Repo also includes some python scripts to plot data from smart those are stored in csv format. below you can see some of the plots from collected data.

![alt text](https://github.com/ErhanYILMAZ/smart_logger/blob/main/figures/fig5.png)

![alt text](https://github.com/ErhanYILMAZ/smart_logger/blob/main/figures/fig2.png)

![alt text](https://github.com/ErhanYILMAZ/smart_logger/blob/main/figures/fig7.png)

![alt text](https://github.com/ErhanYILMAZ/smart_logger/blob/main/figures/fig6.png)

![alt text](https://github.com/ErhanYILMAZ/smart_logger/blob/main/figures/fig1.png)

![alt text](https://github.com/ErhanYILMAZ/smart_logger/blob/main/figures/fig3.png)

![alt text](https://github.com/ErhanYILMAZ/smart_logger/blob/main/figures/fig4.png)
