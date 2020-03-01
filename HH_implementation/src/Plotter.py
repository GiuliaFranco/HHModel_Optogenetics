import plotly.graph_objects as go
from plotly.offline import plot
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import seaborn as sns
from IPython.display import HTML
import matplotlib.animation as animation
import HH
import Integrator 

class Plot_Maker():
    
    def __init__(self,HH):
        self.HH=HH
        self.Integrator=Integrator.Solver(HH)
        print(len(self.Integrator.t))
    def Plot_n_m_h(self):
        self.Integrator.Runge_Kutta(len(self.Integrator.t))
        plt.plot(self.Integrator.t,self.Integrator.s1)
        plt.plot(self.Integrator.t,self.Integrator.s2)
        #plt.plot(self.Integrator.t,self.Integrator.h)
        self.Integrator.Clearer()
        plt.legend(("s1","s2"))
        plt.xlabel("time (ms)")
        #plt.ylabel("Channel openess")
        #plt.title("m,n,h functions")
        #plt.savefig('../graphs/WB_HH/HH1.png')
        #plt.show()

    def Plot_Methods(self):
        self.Integrator.Forward_Euler()
        plt.plot(self.Integrator.t,self.Integrator.V)
        #self.Integrator.Clearer()
        #self.Integrator.Runge_Kutta(len(self.Integrator.t))
        #plt.plot(self.Integrator.t,self.Integrator.V)
        #self.Integrator.Clearer()
        #self.Integrator.Predictor_Corrector()
        #plt.plot(self.Integrator.t,self.Integrator.V)
        #plt.legend(("Runge-Kutta","PC"))
        plt.xlabel("time (ms)")
        plt.ylabel("V (mV)")
        #plt.title("Initial HH observed (Rect impulse (I=15 µA,T=20ms))")
        #plt.savefig('../graphs/WB_HH/Initial_Gal.png')
        #plt.show()


    def Interactive_Plot(self):
        fig = go.Figure()
        for step in range(0,101):
            self.Integrator.model.I.I_0=step
            self.Integrator.Clearer()
            self.Integrator.Runge_Kutta(len(self.Integrator.t))
            fig.add_trace(
                          go.Scatter(
                                     visible=False,
                                     line=dict(color="#00CED1", width=6),
                                     name="I =  " + str(step),
                                     x=self.Integrator.t,
                                     y=self.Integrator.V))
        
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
        plot(fig, filename='../graphs/WB_HH/HH_I.html')


    def Current_plot(self):
        f=self.Integrator.model.I.Rect( np.asarray(self.HH.t, dtype=np.float32))
        plt.plot(self.Integrator.t, f)
        plt.xlabel('time. (ms)', fontsize=18)
        plt.ylabel("I(t). (µA/cm^2)", fontsize=16)
        return plt
        #plt.show()

    def Frequency_plot(self):
        self.Integrator.Runge_Kutta(len(self.HH.t))
        f=self.Integrator.Peak_Detection()
        plt.plot(self.Integrator.t, f)
        plt.xlabel('time. (ms)', fontsize=18)
        plt.ylabel('Output', fontsize=16)
        return plt
        #plt.show()

    def Multiplot(self):
        #self.Integrator.Runge_Kutta(len(self.Integrator.t))
        self.Integrator.Forward_Euler()
        print("done!")
        fig, axs = plt.subplots(2)
        fig.suptitle('Input-Output (Runge_Kutta method,Rect impulse)')
        f=self.Integrator.model.I.Rect( np.asarray(self.Integrator.t, dtype=np.float32))
        axs[0].plot(self.Integrator.t,f)
        axs[0].set(xlabel='',ylabel='I(t). (µA/cm^2)')
        f=self.Integrator.Peak_Detection()
        axs[1].plot(self.Integrator.t, f,'tab:orange')
        axs[1].set(xlabel='time. (ms)',ylabel='Output')
        plt.savefig('../graphs/WB_HH/Long.png')
        #plt.show()


    def Latencyplot_2d(self):
        s1_values=np.arange(0, 1.6,0.05).tolist()
        lat=[]
        I_values=[5,10,15,20,25,30]
        for j in I_values:
            self.Integrator.model.I.I_0=j
            for i in s1_values:
                self.Integrator.model.s1_const=i
                self.Integrator.Runge_Kutta(len(self.Integrator.t))
                lat.append(self.Integrator.Latency())
                self.Integrator.Clearer()
            plt.plot(s1_values,lat)
            lat=[]

        plt.legend(("I= 5 µA","I= 10 µA","I= 15 µA","I= 20 µA","I= 25 µA","I= 30 µA"))
        plt.xlabel("s1")
        plt.ylabel("AP Latency (mV)")
        plt.title("AP latency (s1=const, s2=0, (ɑ,β) using WB_HH)")
        plt.savefig('../graphs/WB_HH/Latency_s1On.png')

    def Latencyplot_3d(self):
        s1_values=np.arange(0, 1,0.1).tolist()
        lat=[]
        s1=[]
        s2=[]
        s2_values=np.arange(0, 1,0.1).tolist()
        #s2_values.reverse()
       
        for j in s2_values:
            for i in s1_values:
                self.Integrator.model.s1_const=i
                self.Integrator.model.s2_const=j
                self.Integrator.Runge_Kutta(len(self.Integrator.t))
                lat.append(self.Integrator.Latency())
                s1.append(i)
                s2.append(j)
                self.Integrator.Clearer()
        fig = plt.figure()
        ax = fig.gca(projection='3d')
        ax.plot_trisurf(s2, s1,lat, cmap=plt.cm.viridis, linewidth=0.2)
        ax.set_xlabel('s2')
        ax.set_ylabel('s1')
        ax.set_zlabel('AP Latency (mV)')
        ax.view_init(30, 20)
        plt.title("AP latency (s1=const, s2=const, (ɑ,β) using WB_HH)")


model=HH.HH(40)
plotter=Plot_Maker(model)
#plotter.Plot_n_m_h()
#plotter.Plot_Methods()
#plotter.Current_plot()
#plotter.Frequency_plot()
#plotter.Interactive_Plot()
#plotter.Multiplot()
#plotter.Latencyplot_3d()
plt.show()
