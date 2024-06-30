import numpy as np

from EconModel import EconModelClass
from consav.grids import nonlinspace
from consav import quadrature

class ModelClass(EconModelClass):
    
    def settings(self):
        """ fundamental settings """

        self.cpp_filename = 'example.cpp'
        self.cpp_options = {'compiler':'vs'}
        
    def setup(self):
        """ set baseline parameters """
        par = self.par
        
        par.R = 1.03
        
        # Utility: 
        par.rho = 2.0   # CRRA
        par.beta = 0.98 # Discount factor

        ###################
        # state variables #
        par.T = 3
        
        # wealth
        par.num_M = 50
        par.max_M = 10.0

        # income shocks
        par.sigma_psi = 0.1
        par.sigma_xi = 0.1

        par.num_psi = 5
        par.num_xi = 5

        # simulation
        par.simN = 1000
        
    def allocate(self):
        par = self.par
        sol = self.sol
        sim = self.sim

        # a. setup grids
        self.setup_grids()

        # b. memory for solution
        shape_sol = (par.T,par.num_M)
        sol.V = np.nan + np.ones(shape_sol) 
        sol.C = np.nan + np.ones(shape_sol) 
        
        # c. memory for simulation
        shape_sim = (par.simN,par.T)
        sim.M = np.nan + np.ones(shape_sim)
        sim.C = np.nan + np.ones(shape_sim)
        
    def setup_grids(self):
        par = self.par
        
        # a. wealth grid with more mass at lower values.
        par.grid_M = nonlinspace(1.0e-6,par.max_M,par.num_M,1.1) 

        # b. transitory and permanent income shocks (Gauss Hermite quadrature)
        shocks = quadrature.create_PT_shocks(par.sigma_psi,par.num_psi,par.sigma_xi,par.num_xi)
        par.psi,par.psi_w,par.xi,par.xi_w,par.Nshocks = shocks

    def solve(self):
        sol = self.sol
        par = self.par 

        # call c++ file usinge the current model.cpp.NAME, where NAME is the name of the function and must have "EXPORT" in front of it in the cpp file.
        self.cpp.solve(par,sol)

    def simulate(self):
        sol = self.sol
        par = self.par 
        sim = self.sim 

        # call c++ file usinge the current model.cpp.NAME, where NAME is the name of the function and must have "EXPORT" in front of it in the cpp file.
        self.cpp.simulate(par,sol,sim)


    