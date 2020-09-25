from neuron import h
from functions import *



class Sim(object):
    """ Serial simulation object
    setup up environment with the setup_func, and run a trial function with each
    parameter in a parameter set
    """
    def __init__(self,cell, stimulator, output_filename):
        self.cell = cell
        self.stimulator = stimulator
        self.output_filename=output_filename
        open(output_filename,'w') # Erase output file
    def distance_threshold(self,param_set):
        """ Find the threshold at various distances
        """
        self.data=[]
        for param in param_set:
            distance=param['Distance (um)']
            self.stimulator.diameter=param['Fiber Optic Diameter (mm)']*1e3 # mm --> um
            self.stimulator.set_distance(self.cell.root,
                                               distance)
            param['Threshold (W/cm2)']=self.find_threshold()
            self.data.append(param)
    def main(self,param_set):
        h.tstop = 60
        self.distance_threshold(param_set)
        self.flush()
    def flush(self):
        # Write data results
        f=open(self.output_filename,'a')
        keys=self.data[0].keys()
        f.write(','.join(keys)+'\n')
        for data in self.data:
            vals=[]
            for key in keys:
                vals.append(str(data[key]))
            f.write(','.join(vals)+'\n')
        f.close()
    def find_threshold(self,upper_limit=1e4,error_threshold=1e-3,verbose=True,additional_aps=1):
        from numpy import log10
        if not self.stimulator.amplitude:
            self.stimulator.amplitude=1
        self.cell.set_tstop(h.tstop,self.stimulator,additional_aps)
        supra=upper_limit/0.9
        sub=0
        if verbose:print ("+ _SubT____, Amplitude, _SupraT__, _Error___ +")
        while (supra-sub)/self.stimulator.amplitude > error_threshold: # while error larger than threshold
            h.run()
            if self.cell.response:response='+'
            else:response='-'
            if verbose:print ("%s %0.3e, %0.3e, %0.3e, %0.3e : %s" % (response,
                                                                     sub,
                                                                     self.stimulator.amplitude,
                                                                     supra,
                                                                     (supra-sub)/self.stimulator.amplitude,
                                                                     (4+int(log10((supra-sub)/self.stimulator.amplitude)))*'*'))
            if self.cell.response:
                supra=self.stimulator.amplitude
                self.stimulator.amplitude = (supra+sub)/2.0
            else:
                if self.stimulator.amplitude >= upper_limit:
                    # Probably not going to reach upper
                    if verbose:print( "** Upper threshold reached **")
                    self.stimulator.amplitude=0
                    h.run()
                    return float('nan')
                sub=self.stimulator.amplitude
                self.stimulator.amplitude = min([(supra+self.stimulator.amplitude)/2.0,self.stimulator.amplitude*2,upper_limit])
        h.run()
        if not self.cell.response:
            self.stimulator.amplitude=supra
            h.run()
        if verbose:print( "** THRESHOLD: %g **" % self.stimulator.amplitude)
        return self.stimulator.amplitude


        
class Data(object):
    def __init__(self, filename, seperator=','):
        from numpy import array
        data={}
        for line in open(filename,'r'):
            data_list = [t.strip() for t in line.strip().split(seperator)]
            line_type = self.data_or_header(data_list)
            if line_type =='data':
                for ii,x in enumerate(data_list):
                    if ii not in data : data[ii]=[]
                    try:
                        data[ii].append(float(x))
                    except:
                        data[ii].append(x.strip())
            elif line_type == 'header':
                headers=data_list
        if not data:
            raise ValueError("Empty data file, or not seperated by %s" % seperator)
        for k in data.keys():
            data[k] = array(data[k])
        self.filename=filename
        self.data={}
        for ii,header in enumerate(headers):
            d = data[ii]
            try:
                f = d.astype(float)
                i = f.astype(int)
                if (f==i).all():
                    self.data[header]=i
                else:
                    self.data[header]=f
            except ValueError:
                self.data[header]=d
    def data_or_header(self,data_list):
        for x in data_list:
            try:
                float(x)
                return 'data'
            except ValueError:
                pass
        return 'header'
    def sort(self, cname):
        """ Sort data by column with header name <<cname>>
        """
        from numpy import array, argsort
        sorted_indices = argsort(self.data[cname])
        for k in self.data.keys():
            self.data[k] = array(self.data[k])[sorted_indices]
    def set_slice(self, mask):
        self.slice={}
        for k in self.headers:
            self.slice[k] = self.data[k][mask]
    def __str__(self):
        return str(self.data)
    def get_headers(self):
        return self.data.keys()
    headers = property(get_headers)
