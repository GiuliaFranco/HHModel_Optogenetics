import plotly.graph_objects as go
from plotly.offline import plot
import matplotlib.pyplot as plt
import numpy as np
import HH

class Plot_Maker():
    
    def __init__(self,HH):
        self.HH=HH
    
    
    def Plot_n_m_h(self):
        self.HH.Runge_Kutta(self.HH.t)
        #plt.plot(self.HH.t,self.HH.V)
        plt.plot(self.HH.t,self.HH.n)
        plt.plot(self.HH.t,self.HH.m)
        plt.plot(self.HH.t,self.HH.h)
        plt.legend(("n","m","h"))
        plt.xlabel("time (ms)")
        plt.ylabel("Channel openess")
        plt.title("m,n,h functions")
        plt.savefig('../graphs/HH1.png')
        plt.show()

    def Plot_Methods(self):
        self.HH.Forward_Euler()
        plt.plot(self.HH.t,self.HH.V)
        self.HH.Clearer()
        self.HH.Runge_Kutta(len(self.HH.t))
        plt.plot(self.HH.t,self.HH.V)
        self.HH.Clearer()
        self.HH.Predictor_Corrector()
        plt.plot(self.HH.t,self.HH.V)
        plt.legend(("Euler","Runge-Kutta","PC"))
        plt.xlabel("time (ms)")
        plt.ylabel("V (mV)")
        plt.title("HH solution (Methods comparison, Dirac impulse (I=0.15 mA))")
        #plt.savefig('../graphs/HH_Comparison_Dirac_1.png')
        plt.show()


    def Interactive_Plot(self):
        fig = go.Figure()
        for step in range(0,101):
            self.HH.I.I_0=step
            self.HH.Clearer()
            self.HH.Runge_Kutta(len(self.HH.t))
            fig.add_trace(
                          go.Scatter(
                                     visible=False,
                                     line=dict(color="#00CED1", width=6),
                                     name="I =  " + str(step),
                                     x=self.HH.t,
                                     y=self.HH.V))
        
        fig.data[100].visible = True
        
        # Create and add slider
        steps = []
        for i in  range(0,101):
            step = dict(
                        method="restyle",
                        args=["visible", [False] * len(fig.data)])
            step["args"][1][i] = True
            steps.append(step)
        
        sliders = [dict(
                        active=10,
                        currentvalue={"prefix": "Intensity (µA): "},
                        pad={"t": 50},
                        steps=steps
                        )]

        fig.update_layout(
                          sliders=sliders
                        )
                        
        fig.update_layout(
                          title="HH equation solution (Runge-Kutta Method)",
                          xaxis_title="Time (ms)",
                          yaxis_title="Voltage (mV)",
                                          )
                            
        for i in range(0,101):
            fig['layout']['sliders'][0]['steps'][i]['label']=i
        plot(fig, filename='HH_I.html')


    def Current_plot(self):
        f=self.HH.I.Rect( np.asarray(self.HH.t, dtype=np.float32))
        plt.plot(self.HH.t, f)
        plt.xlabel('time. (ms)', fontsize=18)
        plt.ylabel('I(t). (µA/cm^2)', fontsize=16)
        return plt
        #plt.show()

    def Frequency_plot(self):
        self.HH.Runge_Kutta(len(self.HH.t))
        f=self.HH.Peak_Detection()
        plt.plot(self.HH.t, f)
        plt.xlabel('time. (ms)', fontsize=18)
        plt.ylabel('Output', fontsize=16)
        return plt
        #plt.show()

    def Multiplot(self):
        self.HH.Runge_Kutta(len(self.HH.t))
        fig, axs = plt.subplots(2)
        fig.suptitle('Input-Output (Runge_Kutta method,Dirac impulse)')
        f=self.HH.I.Dirac( np.asarray(self.HH.t, dtype=np.float32))
        axs[0].plot(self.HH.t,f)
        axs[0].set(xlabel='',ylabel='I(t). (µA/cm^2)')
        f=self.HH.Peak_Detection()
        axs[1].plot(self.HH.t, f,'tab:orange')
        axs[1].set(xlabel='time. (ms)',ylabel='Output')
        plt.savefig('../graphs/In_Out_D1.png')
        plt.show()

model=HH.HH(0.3)
plotter=Plot_Maker(model)
#plotter.Plot_n_m_h()
#plotter.Plot_Methods()
#plotter.Current_plot()
#plotter.Frequency_plot()
#plotter.Interactive_Plot()
plotter.Multiplot()
