from neuron import h
from functions import *

class Hu(object):
    def __init__(self, fiberD=2.0):
        """ Initialize Cell by loading hoc file """
        #-----------------------------------------------------------------------
        # Cell Parameters
        #-----------------------------------------------------------------------
        self.fiberD = fiberD
        #-----------------------------------------------------------------------
        # Optical properties of tissue
        #-----------------------------------------------------------------------
        # Scattering only Kubelka-Munk Model
        #scatter_coefficient      = 4.0 # fit from gradinaru et al
        # 10.3    # 1/mm #S = 10.3 # for rat # Aravanis et al JNE 2007 p s146
        # Kubelka-Munk General model:
        # *Ignoring* light spreading geometry in gradinaru data
        # Fit with matlab fit toolbox, nonlinear least square fit
        #
        # c(X) = (sqrt((1+K/S)^2-1)) / ((1+K/S) * sinh((sqrt((1+K/S)^2-1)) * S * X)
        #                 + (sqrt((1+K/S)^2-1)) * cosh((sqrt((1+K/S)^2-1)) *
        #                S * X))
        #
        # Coefficients (with 95% confidence bounds):
        h('absorbance_coefficient = 0.1249') # (1/mm) # Range: (0.05233, 0.1975)
        h('scatter_coefficient = 7.37')      # (1/mm) # Range: (6.679, 8.062)
        #-----------------------------------------------------------------------
        # Construct Cell
        #-----------------------------------------------------------------------
        self._construct_cell()
        #-----------------------------------------------------------------------
        # Create action potential counters
        #-----------------------------------------------------------------------
        self.apcs = []
        self._ap_counters()
        #-----------------------------------------------------------------------
        # Scaling
        #-----------------------------------------------------------------------
        self.current_scale=1
        #-----------------------------------------------------------------------
        # Visualization
        #-----------------------------------------------------------------------
        self.mlab_cell = None
        self._recordings = {}
    def __str__(self):
        return "HU"
    def _construct_cell(self):
        """ Layer V Pyramidal Cell Hu"""
        h.load_file("cell.hoc")
        self.root = h.soma
        h('number_of_apc = 1')
        h('required_aps = 1')
        h('axonnodes = 14')
    def _ap_counters(self):
        """ Create action potential counters, esp. useful for threshold
        calculation --> need to be corrected """
        self.apcs = []
        self.apc_times = []
        if h.number_of_apc > 0:
            try:
                sec = h.node[h.axonnodes.__int__()-2]
            except AttributeError:
                print("No node compartments!")
                return 0
            apc = h.APCount(0.5, sec=sec)
            apc.thresh = 0 # mV
            apc_time = h.Vector()
            apc.record(apc_time)
            self.apcs.append(apc)
            self.apc_times.append(apc_time)
        if h.number_of_apc == 2:
            sec = h.node[1]
            apc = h.APCount(0.5, sec=sec)
            apc.thresh = 0 # mV
            apc_time = h.Vector()
            apc.record(apc_time)
            self.apcs.append(apc)
            self.apc_times.append(apc_time)
        else:
            if h.number_of_apc>2:
                raise ValueError("Too many apc counters; only 1 or 2 allowed")
    def intensity(self,sec):
        return sec.irradiance_chanrhod * sec.Tx_chanrhod
    def photon_flux(self, sec):
        """ Determine the light intensity at a given section (photons/ms cm2)
        """
        return h.photons_chanrhod * sec.Tx_chanrhod #  photons/ms cm2
    def photons(self,sec):
        section_area = h.area(0.5,sec=sec) # um2
        section_intensity = self.intensity(sec) #  photons/ms cm2
    def root_section(self):
        return h.SectionRef().root
    def build_tree(self, func,segfunc=False):
        """ func must act on a neuron section
        """
        from numpy import array
        print("-"*100)
        def append_data(sec, xyzdv, parent_id, connections,func,segfunc):
            """ Append data to xyzdv
            """
            if not segfunc: v=func(sec)
            n = int(h.n3d(sec=sec))
            for ii in range(1, n):
                x = h.x3d(ii,sec=sec)
                y = h.y3d(ii,sec=sec)
                z = h.z3d(ii,sec=sec)
                d = h.diam3d(ii,sec=sec)
                if segfunc:
                    if n==1:v=func(sec(0.5))
                    else:v = func(sec(ii/float(n-1)))
                xyzdv.append([x,y,z,d,v])
                child_id = len(xyzdv)-1
                if len(xyzdv)>1:
                    connections.append([child_id, parent_id])
                parent_id = child_id
            return xyzdv, connections

        def append_children_data(parent, parent_id, xyzdv, connections, func, segfunc):
            sref = h.SectionRef(sec=parent)
            if sref.child:
                for child in sref.child:
                    xyzdv, connections = append_data(child, xyzdv, parent_id, connections, func, segfunc)
                    xyzdv, connections = append_children_data(parent = child,
                                                              parent_id = len(xyzdv)-1,
                                                              xyzdv = xyzdv,
                                                              connections = connections,
                                                              func = func,
                                                              segfunc = segfunc)
            return xyzdv, connections

        # Find data and connections
        root_section = self.root_section()
        if segfunc:
            if root_section.nseg==1:
                v = func(root_section(0.5))
            else:
                v = func(root_section(0.0))
        else:
            v=func(root_section)
        xyzdv = [[h.x3d(0,sec=root_section),h.y3d(0,sec=root_section),h.z3d(0,sec=root_section),h.diam3d(0,sec=root_section),v]]
        xyzdv, connections = append_data(root_section, xyzdv, 0, [],func,segfunc)
        xyzdv, connections = append_children_data(root_section,len(xyzdv)-1,xyzdv,connections,func,segfunc)
        self.xyzdv = array(xyzdv)
        self.connections = array(connections)
    def move(self, xyz, move_mlab=False):
        """ Move visualization and cell """
        from neuron import h
        if move_mlab:
            if self.mlab_cell:
                self.mlab_cell.mlab_source.x = self.mlab_cell.mlab_source.x + xyz[0]
                self.mlab_cell.mlab_source.y = self.mlab_cell.mlab_source.y + xyz[1]
                self.mlab_cell.mlab_source.z = self.mlab_cell.mlab_source.z + xyz[2]
        tree = h.SectionList()
        tree.wholetree(sec=self.root)
        for sec in tree:
            for ii in xrange(h.n3d(sec=sec).__int__()):
                x=h.x3d(ii,sec=sec)
                y=h.y3d(ii,sec=sec)
                z=h.z3d(ii,sec=sec)
                d=h.diam3d(ii,sec=sec)
                h.pt3dchange(ii,x+float(xyz[0]),y+float(xyz[1]),z+float(xyz[2]),d)
    def retrieve_coordinates(self, sec):
        xyzds = []
        for ii in xrange(int(h.n3d(sec=sec))):
            xyzds.append([h.x3d(ii,sec=sec),
                          h.y3d(ii,sec=sec),
                          h.z3d(ii,sec=sec),
                          h.diam3d(ii,sec=sec)])
        return xyzds
    def display(self, func, segfunc=False, scaling=1, replace=True, clim=None, colormap='jet'):
        ''' Display current cell in mayavi
        '''
        #from neuron import h
        from numpy import array, vstack
        try:
            from enthought.mayavi import mlab
            from enthought.mayavi.mlab import pipeline
        except:
            from mayavi import mlab
            from mayavi.mlab import pipeline
        if replace:
            try:self.mlab_cell.parent.parent.parent.parent.parent.parent.remove()
            except AttributeError:pass
        ### Turn off vtk warnings # # # # # # # # # # # # # # # # # # # # # # #
        from vtk import vtkObject
        o = vtkObject
        o.GetGlobalWarningDisplay()
        o.SetGlobalWarningDisplay(0) # Turn it off.

        self.build_tree(func, segfunc)
        xs = self.xyzdv[:,0]
        ys = self.xyzdv[:,1]
        zs = self.xyzdv[:,2]

        # don't want scaling for soma segments
        diams = self.xyzdv[:,3]
        nonsoma = (diams < 15) # non-somatic
        diams += diams*nonsoma*(scaling-1)
        #diams = self.xyzdv[:,3] * scaling # larger scaling makes neurons more visible
        data = self.xyzdv[:,4]
        edges = self.connections

        # Display in mayavi
        pts = pipeline.scalar_scatter(xs, ys, zs, diams/2.0,
                                      name=str(self))
        dataset = pts.mlab_source.dataset
        dataset.point_data.get_array(0).name = 'diameter'
        dataset.lines = vstack(edges)

        array_id = dataset.point_data.add_array(data.T.ravel())
        dataset.point_data.get_array(array_id).name = 'data'
        dataset.point_data.update()

        #### Create tube with diameter data
        src = pipeline.set_active_attribute(pts,
                                            point_scalars='diameter')
        stripper = pipeline.stripper(src)
        tube = pipeline.tube(stripper,
                             tube_sides = 8,
                             tube_radius = 1)
        tube.filter.capping = True
        tube.filter.use_default_normal = False
        tube.filter.vary_radius = 'vary_radius_by_absolute_scalar'
        #tube.filter.radius_factor = 90.0 # just for making movies
        src2 = pipeline.set_active_attribute(tube, point_scalars='data')

        lines = pipeline.surface(src2,colormap = colormap)
        if clim:
            from numpy import array
            lines.parent.scalar_lut_manager.use_default_range = False
            lines.parent.scalar_lut_manager.data_range = array(clim)
        self.mlab_cell = lines
    def plot(self, func, scaling = 1, segfunc=False, clim=None,cmap=None):
        """ plot cell in matplotlib line plot collection
        """
        from numpy import array, linspace
        from matplotlib.collections import LineCollection
        from matplotlib import pyplot
        self.build_tree(func,segfunc)
        pts   = self.xyzdv[:,:2]
        edges = self.connections
        diam  = self.xyzdv[:,3]
        data  = self.xyzdv[:,4]
        print( "DATA RANGE: ",data.min(),data.max())
        # Define colors
        if not cmap:
            from matplotlib.cm import jet as cmap
        if not clim:
            clim=[data.min(),data.max()]
        a = (data - clim[0])/(clim[1]-clim[0])
        # Define line segments
        segments = []
        for edge in edges:
            segments.append([pts[edge[0],:], pts[edge[1],:]])
        # Build Line Collection
        collection = LineCollection(segments = array(segments),
                                    linewidths = diam*scaling,
                                    colors=cmap(a))
        collection.set_array(data)
        collection.set_clim(clim[0], clim[1])
        pyplot.gca().add_collection(collection,autolim=True)
        pyplot.axis('equal')
        return collection
    def channels_in_list(self,seclist):
        channels = 0
        for sec in seclist:
            if h.ismembrane('chanrhod',sec = sec):
                for seg in sec:
                    rho  = seg.channel_density_chanrhod/1e8 # 1/cm2 --> 1/um2
                    area = h.area(seg.x, sec=sec) # um2
                    n = rho * area
                    channels += n
        return channels
    def area_in_list(self,seclist):
        area = 0
        for sec in seclist:
            if h.ismembrane('chanrhod',sec = sec):
                for seg in sec:
                    area += h.area(seg.x, sec=sec) # um2
        return area
    def illuminated_area_in_list(self,seclist,Tx_threshold = 0.001):
        area = 0
        for sec in seclist:
            if h.ismembrane('chanrhod',sec = sec):
                for seg in sec:
                    if seg.Tx_chanrhod>Tx_threshold:
                        area += h.area(seg.x, sec=sec) # um2
        return area
    def open_channels_in_list(self,seclist):
        open_channels = 0
        for sec in seclist:
            if h.ismembrane('chanrhod', sec = sec):
                for seg in sec:
                    rho  = seg.channel_density_chanrhod/1e8 # 1/cm2 --> 1/um2
                    area = h.area(seg.x, sec=sec) # um2
                    try:
                        f_open = seg.o2_chanrhod + seg.o1_chanrhod # open fraction # 4 state model
                    except:
                        f_open = seg.o1_chanrhod # open fraction # 3 state model
                    n = f_open * rho * area
                    open_channels += n
        return open_channels
    def get_axonal(self):
        """ Additional iseg compartment
        """
        secs = [h.hill]
        secs.extend([sec for sec in h.ais])
        secs.extend([h.nakeaxon])
        secs.extend([sec for sec in h.myelin])
        secs.extend([sec for sec in h.node])
        return secs
    def get_axonal_channels(self):
        return self.channels_in_list(self.axonal)
    def get_open_axonal_channels(self):
        return self.open_channels_in_list(self.axonal)
    def get_dendritic(self):
        secs = [sec for sec in h.somatodendritic]
        #secs.extend([h.hill])
        return secs
    def get_dendritic_channels(self):
        return self.channels_in_list(self.dendritic)
    def get_open_dendritic_channels(self):
        return self.open_channels_in_list(self.dendritic)
    def get_apical_tuft(self):
        """ Return a list of all sections which make up the apical tuft, starting
        at the branch point
        """
        secs=[]
        for ii in range(23,len(h.dend11)):
            secs.append(h.dend11[ii])
        return secs
    def get_apical_shaft(self):
        """ Return the sections which compose the apical shaft
        """
        secs=[]
        for ii in [0,4,10,16,18,20,22]:
            secs.append(h.dend11[ii])
        return secs
    def get_basilar_tuft(self):
        """ Return the dendritic sections which compose the basilar tuft
        """
        secs=[]
        for ii,dendrite in enumerate((h.dend1,h.dend2,h.dend3,h.dend4,h.dend5,h.dend6,
                                      h.dend7,h.dend8,h.dend9,h.dend10,h.dend11)):
            if ii==10:
                for jj,sec in enumerate(dendrite):
                    if jj < 23: # Apical Tuft
                        if jj not in [0,4,10,16,18,20,22]: # Apical Shaft
                            secs.append(sec)
            else:
                for sec in dendrite:
                    secs.append(sec)
        return secs
    def get_somatic(self):
        """ Return the sections which compose the Soma
        """
        return [h.soma]
    def set_density_distribution(self, distribution=0.5, n_channels = 1e7):
        """ Set density in dendritic compartments
        distribution: 0.0 - Higher Somatic density
                      0.5 - Uniform distribution
                      1.0 - Higher Apical density
        """
        # Find the maximal distance between the soma and all dendrities
        max_distance = 0
        for sec in self.dendritic:
            for seg in sec:
                max_distance = max([max_distance, self.seg_section_distance(seg)])

        for sec in self.dendritic:
            for seg in sec:
                distance=self.seg_section_distance(seg)
                s = (max_distance-distance)/(max_distance) # soma centric weighting
                a = (distance)/(max_distance)              # apical centric weighting
                W = distribution
                seg.channel_density_chanrhod  =  s*(1-W) + a*W
        scale = n_channels/self.dendritic_channels
        for sec in self.dendritic:
            for seg in sec:
                seg.channel_density_chanrhod = scale*seg.channel_density_chanrhod
        assert 0.001 > (n_channels - self.dendritic_channels)
    def get_open_channels(self):
        return self.open_channels_in_list(h.allsec())
    def get_total_channels(self):
        return self.channels_in_list(h.allsec())
    def get_icat(self):
        """ Determine the total amount of channelrhodopsin current in the cell
        """
        icat = 0
        for sec in h.allsec():
            if h.ismembrane('chanrhod',
                            sec = sec):
                for seg in sec:
                    i = seg.icat_chanrhod # (mA/cm2)
                    area = h.area(seg.x, sec=sec)/1e8      # cm2
                    icat += area * i # mA
        return icat
    def set_required_aps(self,stimulator,additional_aps=1):
        """ Determine the number of action potentials normally occuring, so that
        we can set a goal number of additional aps
        Also, we check to make sure that the stimulator's amplitude is set to 0
        """
        from neuron import h
        initial_amplitude=stimulator.amplitude
        stimulator.amplitude=0
        h.run()
        h.required_aps=0
        assert self.apc_times,'No action potential counters'
        for apct in self.apc_times:
            h.required_aps=max((h.required_aps,len(apct)))
        print ("** NO STIM APS: %d; Goal APS: %d **" % (h.required_aps,
                                                       h.required_aps+additional_aps))
        h.required_aps += additional_aps # usually require one additional ap
        stimulator.amplitude=initial_amplitude
    def set_tstop(self,tstop,stimulator,additional_aps=1):
        h.tstop=tstop
        self.set_required_aps(stimulator,additional_aps)
    def get_response(self):
        """ Determine if an action potential has occurred
        """
        # Determine if any of the counters saw less than the requisite number of action potentials
        for apct in self.apc_times:
            if len(apct) < h.required_aps:
                return False
        # If all counters saw the requisite number, than return True
        return True
    def seg_section_distance(self,seg,root_section=None):
        """ Returns the distance between each segment of section, and the
        root_section
        """
        if not root_section:root_section=self.root
        h.distance(0, root_section(0.5).x, sec=root_section)
        return h.distance(seg.x, sec=seg.sec)
    response = property(get_response)
    open_channels = property(get_open_channels)
    total_channels = property(get_total_channels)
    icat = property(get_icat)
    apical_tuft  = property(get_apical_tuft)
    apical_shaft = property(get_apical_shaft)
    basilar_tuft = property(get_basilar_tuft)
    dendritic = property(get_dendritic)
    dendritic_channels = property(get_dendritic_channels)
    open_dendritic_channels = property(get_open_dendritic_channels)
    somatic = property(get_somatic)
    axonal = property(get_axonal)
    axonal_channels = property(get_axonal_channels)
    open_axonal_channels = property(get_open_axonal_channels)