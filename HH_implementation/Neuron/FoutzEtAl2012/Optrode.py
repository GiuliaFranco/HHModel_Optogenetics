from neuron import h
from functions import *


class Optrode(object):
    """ xyz0 is the base, and xyz1 is the tip """
    def __init__(self,origin,delay=1,duration=5,initial_amplitude=38.0,distance=1000,pulses=1,frequency=1):
        from numpy import pi
        self.origin=h.secname(sec=origin)
        self.sec=h.Section(name=str(self))
        self.sec.L=1000
        self.sec.diam=200 # um # Aravanis: 200 um # Gradinaru: 400 um
        self.stim=h.ostim(0.5,sec=self.sec)
        self.delay=delay
        self.pulses=pulses
        self.frequency=frequency
        self.duration=duration
        self.amplitude=initial_amplitude
        h.setpointer(h._ref_source_irradiance_chanrhod, 'irradiance',self.stim)
        h.setpointer(h._ref_source_photons_chanrhod,   'photons',self.stim)
        h.setpointer(h._ref_source_flux_chanrhod,      'flux',self.stim)
        h.setpointer(h._ref_tstimon_chanrhod,      'tstimon',self.stim)
        h.setpointer(h._ref_tstimoff_chanrhod,      'tstimoff',self.stim)
        self.stim.radius=self.sec.diam/2.0
        self.stim.pulses=self.pulses
        self.stim.isi = 1000 / self.frequency - self.duration #in ms
        self.stim.amp=initial_amplitude
        self.absorbance_coefficient = 0.1249 # (1/mm) # Range: (0.05233, 0.1975)
        self.scatter_coefficient = 7.37      # (1/mm) # Range: (6.679, 8.062)
        self.n = 1.36        # index of refraction of gray matter
        self.NA = 0.37        # numerical aperture of the optical fiber
        #self.NA = 0.48
        self.set_distance(origin, distance)
    def __str__(self):
        return "Fiber Optic"
    def __info__(self):
        info=str(self)
        info+="\n-Section: %s" % self.origin
        xyz0,xyz1=self.xyz
        info+="\n-Base: %g,%g,%g" % (xyz0[0],xyz0[1],xyz0[2])
        info+="\n-Tip: %g,%g,%g" % (xyz1[0],xyz1[1],xyz1[2])
        info+="\n-Delay: %s" % self.delay
        info+="\n-Duration: %s" % self.duration
        info+="\n-Amplitude: %s" % self.amplitude
        info+="\n-Length: %g" % self.length
        info+="\n-Diameter: %g" % self.diameter
        info+="\n-closest_section: %s" % h.secname(sec=self.closest_section)
        return info
    def _find_axon_trajectory(self, center):
        """ Find the normalized vector which describes axon trajectory """
        from numpy import sqrt
        most_distant_node = find_mean_section_coordinates(h.node[-2])
        trajectory = most_distant_node - center
        trajectory /= sqrt(sum(trajectory**2))  # Normalize
        return trajectory
    def interpxyz(self):
        """ interpolated data, spaced at regular intervals
        """
                # First, need to interpolate centers unto all compartments; from interpxyz.hoc
        for sec in h.allsec():
            #if h.ismembrane('chanrhod',sec=sec):
            if h.ismembrane('chanrhod',sec=sec):
                nn = h.n3d(sec=sec).__int__()
                xx = h.Vector(nn)
                yy = h.Vector(nn)
                zz = h.Vector(nn)
                length = h.Vector(nn)
                for ii in range(nn):
                    xx.x[ii] = h.x3d(ii,sec=sec)
                    yy.x[ii] = h.y3d(ii,sec=sec)
                    zz.x[ii] = h.z3d(ii,sec=sec)
                    length.x[ii] = h.arc3d(ii,sec=sec)
                # to use Vector class's .interpolate() must first scale the
                # independent variable i.e. normalize length along centroid
                length.div(length.x[nn-1])
                # initialize the destination "independent" vector
                rr = h.Vector(sec.nseg+2)
                rr.indgen(1./sec.nseg)
                rr.sub(1./(2.*sec.nseg))
                rr.x[0]=0.
                rr.x[sec.nseg+1]=1.
                # length contains the normalized distances of the pt3d points
                # along the centroid of the section.  These are spaced at
                # irregular intervals.
                # range contains the normalized distances of the nodes along the
                # centroid of the section.  These are spaced at regular intervals.
                # Ready to interpolate.
                xint = h.Vector(sec.nseg+2)
                yint = h.Vector(sec.nseg+2)
                zint = h.Vector(sec.nseg+2)
                xint.interpolate(rr, length, xx)
                yint.interpolate(rr, length, yy)
                zint.interpolate(rr, length, zz)
                # for each node, assign the xyz values to x_xtra, y_xtra, z_xtra
                # don't bother computing coords of the 0 and 1 ends
                # also avoid writing coords of the 1 end into the last internal node's coords
                for ii in range(1,sec.nseg+1):
                    xr = rr.x[ii]
                    #sec(xr).x_chanrhod = xint.x[ii]
                    #sec(xr).y_chanrhod = yint.x[ii]
                    #sec(xr).z_chanrhod = zint.x[ii]
                    sec(xr).x_chanrhod = xint.x[ii]
                    sec(xr).y_chanrhod = yint.x[ii]
                    sec(xr).z_chanrhod = zint.x[ii]
    def find_illumination(self,X,Y,Z,spreading=True,scattering=True):
        from numpy import sqrt
        def gaussian(r,radius):
            """ r is displacement from center
            95.4 % of light is within the radius (2 standard deviations)
            constant energy in distribution
            """
            from numpy import array, pi,sqrt, exp
            r = 2*array(r)/array(radius)
            dist = (1/sqrt(2*pi)) * exp((r**2)/(-2))
            return dist/0.4
        def kubelka_munk(distance):
            """
            distance to center of optrode, approximates mean distance to all points along surface of optrode
            distance in um
            """
            from numpy import sqrt,sinh,cosh
            #K = 0.1248e-3 # 1/um
            #S = 7.37e-3   # 1/um
            K = self.absorbance_coefficient * 1e-3 # (1/um) # Range: (0.05233, 0.1975)
            S = self.scatter_coefficient * 1e-3    # (1/um) # Range: (6.679, 8.062)
            a = 1 + K / S                # unitless
            b = sqrt(a ** 2 - 1)         # unitless
            Tx = b / (a * sinh(b * S * distance) + b * cosh(b * S * distance)) # distance in um - losses due to absorption and scattering through the tissue on top of losses due to beam quality?
            Tx[distance<0]=0 # negative values set to zero
            return Tx
        def apparent_radius(z,radius):
            """ Find the apparent radius at a distance z
            """
            from numpy import tan
            return radius + z*tan(self.theta_div)
        def spread(z):
            """ irradiance loss due to spreading
            """
            from numpy import sqrt,pi
            rho = self.radius * sqrt(((self.n/self.NA)**2) - 1)
            return rho**2 / ((z + rho)**2)
        r,z = find_cylindrical_coords(X,Y,Z,self.xyz)
        if scattering: # kubelka-munk scattering
            Kx = kubelka_munk(sqrt(r**2+z**2))
        else:
            Kx = 1
        if spreading: # conservation of energy spreading
            Sx = spread(z)
            radius = apparent_radius(z,self.radius)
        else:
            Sx = 1
            radius = self.radius
        return Sx * Kx * gaussian(r,radius)
    def calc_tx(self):
        """ Set the fractional illumionation for all sections which have chanrhod
        density mechanisms """
        from numpy import sqrt, sinh, cosh, arccos, tan, array, dot, isnan, pi
        self.interpxyz()

        # !All units should be in um
        #---------------------------------------------------------------------------
        # Location of each segment
        #---------------------------------------------------------------------------
        seg_xyz = []
        for sec in h.allsec():
            #if h.ismembrane('chanrhod', sec=sec):
            if h.ismembrane('chanrhod', sec=sec):
                for seg in sec:
                    xyz = seg.x_chanrhod, seg.y_chanrhod, seg.z_chanrhod
                    seg_xyz.append(xyz)
        seg_xyz = array(seg_xyz)
        Tx = self.find_illumination(seg_xyz[:,0],seg_xyz[:,1],seg_xyz[:,2])
        #---------------------------------------------------------------------------
        # Set Tx_chanrhod
        #---------------------------------------------------------------------------
        ii = 0
        #for sec in h.allsec():
            #if h.ismembrane('chanrhod', sec=sec):
                #for seg in sec:
                    #seg.Tx_chanrhod = Tx[ii]
                    #ii+=1
        for sec in h.allsec():
            if h.ismembrane('chanrhod', sec=sec):
                for seg in sec:
                    seg.Tx_chanrhod = Tx[ii]
                    ii+=1
    def rotate_optrode(self, angle, distance, sec, axis_defining_plane='z'):
        """ rotate optrode around a given sec,
        to a given angle,
        at a given distance
        in the plane defined by the axon and the given vectro
        """
        from numpy import cross, sqrt, array

        # Determine center of rotation
        center = find_mean_section_coordinates(sec)

        # Determine starting position
        xyz0 = self._find_axon_trajectory(center) * (distance+1000)  # end optrode along axon
        xyz1 = self._find_axon_trajectory(center) * distance         # start optrode along axon

        # Find vector perpendicular to axon and given axis
        if axis_defining_plane=='x':
            uvw = cross(xyz1, array([1,0,0]))
        elif axis_defining_plane=='y':
            uvw = cross(xyz1, array([0,1,0]))
        elif axis_defining_plane=='z':
            uvw = cross(xyz1, array([0,0,1]))
        else:
            raise ValueError('No such plane: %s' % axis_defining_plane)
        uvw /= sqrt(sum(uvw**2))  # Normalize

        # Rotate the optrode around the vector
        new_xyz0 = rotate_point_around_vector(xyz0,
                                              uvw,
                                              angle)
        new_xyz1 = rotate_point_around_vector(xyz1,
                                              uvw,
                                              angle)

        # Redefine optrode position
        self.set_position([float(new_xyz0[0]),float(new_xyz1[0])],
                         [float(new_xyz0[1]),float(new_xyz1[1])],
                         [float(new_xyz0[2]),float(new_xyz1[2])])
    def draw(self):
        """ Draw a visual representation of the optrode """
        from neuron import gui
        if not hasattr(self,'gOpt'):
            from numpy import pi
            self.gOpt=h.Shape(0)
            self.gOpt.view(-2100, -2100, 4200, 4200, 230, 450, 200.64, 200.32)
            self.gOpt.rotate(0, 0, 0, pi/2, 0, 0)
        h.pt3dclear(sec = self.sec)
        h.pt3dadd(self.x[0],
                  self.y[0],
                  self.z[0],
                  self.diameter,
                  sec = self.sec)
        h.pt3dadd(self.x[1],
                  self.y[1],
                  self.z[1],
                  self.diameter,
                  sec = self.sec)
        self.pOpt0 = h.IClamp(0,
                              sec = self.sec)
        self.pOpt1 = h.IClamp(1,
                              sec = self.sec)

        self.gOpt.point_mark(self.pOpt0, 1)  # make start black
        self.gOpt.point_mark(self.pOpt1, 3)  # make output blue
        self.gOpt.exec_menu("Show Diam")
        self.gOpt.exec_menu("3D Rotate")
    def display(self,show_illum=True,dvol=50,cladding=None,scattering=True,spreading=True,bounds = None):
        """ Display optrode in mayavi
        """
        if not bounds:
            if hasattr(self,"bounds"):
                bounds = self.bounds
            else:
                bounds = [[-500,500],[-500,500],[-500,500]]
        self.bounds = bounds
        if cladding==None:
            if hasattr(self,'mlab_cladding'):
                cladding = True
            else:
                cladding = False
        if hasattr(self,'mlab_tube'):
            self.mlab_tube.parent.parent.remove()
        if hasattr(self,'mlab_illum'):
            self.mlab_illum.parent.parent.remove()
        if hasattr(self,'mlab_cladding'):
            self.mlab_cladding.parent.parent.remove()
        try:
            from enthought.mayavi import mlab
        except:
            from mayavi import mlab
        cyl = mlab.plot3d(self.x,
                          self.y,
                          self.z,
                          name='optrode',
                          color=(.9,.9,.9))
        self.mlab_tube = cyl.parent.parent
        self.mlab_tube.filter.capping = True
        self.mlab_tube.filter.number_of_sides = 20
        self.mlab_tube.filter.radius = self.radius
        if cladding:
            from numpy import array
            clad= mlab.plot3d(self.x,
                              self.y,
                              self.z-array([0.1,0.1]),
                              name='cladding',
                              color=(0.5,0.5,0.5),
                              opacity = 0.5)
            self.mlab_cladding = clad.parent.parent
            self.mlab_cladding.filter.capping = True
            self.mlab_cladding.filter.number_of_sides = 20
            self.mlab_cladding.filter.radius = self.radius*2
            self.mlab_cladding.children[0].children[0].actor.property.backface_culling = True
        if show_illum:
            from numpy import diff, mgrid,array,matrix,c_,cos,sin,arctan,ones
            from numpy.linalg import norm
            x = self.xyz[1,0]
            y = self.xyz[1,1]
            z = self.xyz[1,2]
            X,Y,Z = mgrid[x+bounds[0][0]:x+bounds[0][1]:dvol*1j,
                          y+bounds[1][0]:y+bounds[1][1]:dvol*1j,
                          z+bounds[2][0]:z+bounds[2][1]:dvol*1j]

            Tx = self.find_illumination(X,Y,Z,spreading,scattering)
            self.mlab_illum = mlab.contour3d(X,Y,Z,Tx,
                                             #opacity=0.8,
                                             transparent=True,
                                             vmin=0.001,
                                             vmax=0.1,
                                             contours=[t for t in [0.1,0.01,0.001]])
            self.mlab_illum.parent.scalar_lut_manager.use_default_range = False
            self.mlab_illum.parent.scalar_lut_manager.data_range = array([ 0.001,  0.1   ])
            self.mlab_illum.parent.scalar_lut_manager.lut.scale='log10'
            #self.mlab_illum.actor.property.backface_culling = True
            self.mlab_illum.actor.property.frontface_culling = True
    def record(self,args=('i',)):
        self._recording={'t':h.Vector()}
        self._recording['t'].record(h._ref_t)
        for k in args:
            self._recording[k]=h.Vector()
            exec('self._recording[k].record(self.stim._ref_%s)' % k)
    def plot(self,show=False):
        from matplotlib.pyplot import plot,legend
        recordings=self.recordings
        t=recordings['t']
        for k,v in recordings.items():
            if k != 't':
                plot(t,v,label=k)
        legend()
        if show:
            from matplotlib.pyplot import show as shw
            shw()
    def get_duration(self):
        return self.stim.dur
    def set_duration(self,duration):
        self.stim.dur=duration
    def get_amplitude(self):
        return self.stim.amp
    def set_amplitude(self,amplitude):
        self.stim.amp=amplitude
    def get_delay(self):
        return self.stim.delay
    def set_delay(self,delay):
        self.stim.delay=delay
    def get_recordings(self):
        from numpy import array
        recordings={}
        for k in self._recording.keys():
            recordings[k]=array(self._recording[k].to_python())
        return recordings
    def set_position(self, x, y, z):
        """ Move electrode to new coordinates:
            x0, y0, z0: optrode input
            x1, x1, z1: optrode output
        """
        from numpy.linalg import norm
        self._x=x
        self._y=y
        self._z=z
        xyz0,xyz1=self.xyz
        #self.sec.L=dist(xyz0,xyz1)
        self.sec.L = norm(xyz1-xyz0)
        h.pt3dclear(sec=self.sec)
        h.pt3dadd(float(x[0]), float(y[0]), float(z[0]),
                  self.radius * 2, sec=self.sec)
        h.pt3dadd(float(x[1]), float(y[1]), float(z[1]),
                  self.radius * 2, sec=self.sec)
        self.calc_tx()
        if hasattr(self, "gOpt"): self.draw()
        if hasattr(self, "mlab_tube"): self.display()
    def set_longitudinal_radial(self, longitudinal_percent, radial_distance, center, terminal_node=None):
        from numpy import array, sign
        from numpy.linalg import norm

        if not terminal_node:
            try:
                terminal_node = h.node[-1]
            except:
                raise StandardError('No h.node[-1] compartment!')

        # Place electrode along length of neuron
        fraction_length = longitudinal_percent / 100.0
        xyz_soma = find_mean_section_coordinates(center)
        xyz_terminal_node = find_mean_section_coordinates(terminal_node)
        xyz_optrode = xyz_soma + \
                    fraction_length * (xyz_terminal_node - xyz_soma) + \
                    array([0, 0, -1 * radial_distance])

        # Find displacement from underneath center (for analysis)
        # essentially, when plotting, it is more useful to demonstrate the
        # displacement in mm rather than the  fractional longitudinal distance
        longitudinal_displacement = sign(longitudinal_percent) * norm(fraction_length * (xyz_terminal_node - xyz_soma))

        # Set optrode at location
        self.set_position([xyz_optrode[0], xyz_optrode[0]],
                         [xyz_optrode[1], xyz_optrode[1]],
                         [xyz_optrode[2] - self.length, xyz_optrode[2]])
        return xyz_optrode, longitudinal_displacement
    def get_distance(self, sec):
        """ Helper method to find the distance between the optrode tip and a
        given compartment (section)
        """
        from numpy.linalg import norm
        from numpy import array
        from neuron import nrn
        optrode_output = self.xyz[1]
        if isinstance(sec,nrn.Section):
            return norm(find_mean_section_coordinates(sec) -
                        optrode_output)
        elif isinstance(sec,nrn.Segment):
            seg = sec
            print(find_section_coordinates(seg.sec),seg.x)
            raise StandardError("Not yet implemented")
        else:
            raise TypeError("Wrong type: %s" % type(sec))
    def set_distance(self, sec, z_distance):
        """ Set optrode a certain distance in z-direction below the given section
        directed upwards """
        x, y, z = find_mean_section_coordinates(sec)
        self.set_position([x,x],
                          [y,y],
                          [z - z_distance - self.length,
                           z - z_distance])
        assert (z_distance == self.get_distance(sec))
    def get_x(self):
        return self._x
    def set_x(self, val):
        from numpy import array
        assert len(val)==2
        self._x=array([float(val[0]),
                       float(val[1])])
        from numpy.linalg import norm
        xyz0,xyz1=self.xyz
        self.length = norm(xyz1-xyz0)
    def get_y(self):
        return self._y
    def set_y(self, val):
        from numpy import array
        assert len(val)==2
        self._y=array([float(val[0]),
                       float(val[1])])
        from numpy.linalg import norm
        xyz0,xyz1=self.xyz
        self.length = norm(xyz1-xyz0)
    def get_z(self):
        return self._z
    def set_z(self, val):
        from numpy import array
        assert len(val)==2
        self._z=array([float(val[0]),
                       float(val[1])])
        from numpy.linalg import norm
        xyz0,xyz1=self.xyz
        self.length = norm(xyz1-xyz0)
    def get_xyz(self):
        from numpy import array
        x=self.x
        y=self.y
        z=self.z
        return array([[x[0],y[0],z[0]],[x[1],y[1],z[1]]])
    def set_xyz(self,val):
        from numpy import array
        val = array(val).astype(float)
        #print "SHAPE: ",val.shape
        if val.shape == (3,2):
            self.set_position(val[0,:],val[1,:],val[2,:])
        elif val.shape == (2,3):
            self.set_position(val[:,0],val[:,1],val[:,2])
        else:
            raise ValueError("Trying to set xyz with inappropriate array %s" % str(val))
    def get_length(self):
        return self.sec.L
    def set_length(self,val):
        self.sec.L = val
        x0, x1 = self.x
        y0, y1 = self.y
        z0, z1 = self.z
        new_x0, new_y0, new_z0 = point_along_vector([x1, y1, z1],
                                                    [x0-x1, y0-y1, z0-z1],
                                                    val)
        self.set_position([new_x0, x1],
                         [new_y0, y1],
                         [new_z0, z1])
        from numpy import array
        from numpy.linalg import norm
        xyz0,xyz1=self.xyz
        dist = norm(xyz1-xyz0)
        assert(approx_equal(self.length, dist))
    def get_diameter(self):
        """ Diameter in um
        """
        assert self.sec.diam==self.stim.radius*2
        return self.sec.diam
    def set_diameter(self,diameter):
        """ Diameter in um
        """
        self.radius=diameter/2.0
    def get_radius(self):
        return self.stim.radius
    def set_radius(self,radius):
        self.sec.diam=radius * 2.0
        self.stim.radius=radius
    def get_closestsection(self):
        """ Find the closest chanrhod+ section """
        closest_sec=None
        closest_sec_distance=1e9
        for sec in h.allsec():
            #if h.ismembrane('chanrhod', sec = sec):
            if h.ismembrane('chanrhod', sec = sec):
                sec_distance = self.get_distance(sec)
                if sec_distance<closest_sec_distance:
                    closest_sec=sec
                    closest_sec_distance=sec_distance
        return closest_sec
    def get_intensity(self):
        return self.stim.intensity
    def radiant_power(self,seclist):
        """ Find the radiant power integrated over all sections in seclist
        """
        p = 0
        for sec in seclist:
            for seg in sec:
                area = h.area(seg.x, sec=sec)*1e-8 # um2 --> cm2
                #p += (area * self.amplitude * sec.Tx_chanrhod) # Add section's radiant power
                p += (area * self.amplitude * sec.Tx_chanrhod)
        return p
    def get_sec(self):
        return self._sec
    def set_sec(self,sec):
        self._sec = sec
    def get_theta_div(self):
        from numpy import arcsin
        return arcsin(self.NA/self.n)
    duration=property(get_duration,set_duration)
    amplitude=property(get_amplitude,set_amplitude)
    delay=property(get_delay,set_delay)
    recordings=property(get_recordings)
    theta_div = property(get_theta_div)
    sec = property(get_sec,set_sec)
    x = property(get_x, set_x)
    y = property(get_y, set_y)
    z = property(get_z, set_z)
    xyz = property(get_xyz,set_xyz)
    length = property(get_length, set_length)
    closest_section = property(get_closestsection)
    diameter=property(get_diameter,set_diameter)
    radius=property(get_radius,set_radius)
    intensity=property(get_intensity)
    info=property(__info__)