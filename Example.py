import numpy as np

from EconModel import EconModelClass
from consav.grids import nonlinspace
from consav import quadrature

class ModelClass(EconModelClass):
    
    def settings(self):
        """ fundamental settings """

        self.cpp_filename = 'cppfuncs/cpp_link_file.cpp'
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
        par.T = 15
        par.num_kids = 2 # Number Children // Note: max_para must always be greater by one than the actual grid, so the Final Period = 14 ==> par.T = 15 [weird C++ thing]

        # wealth
        par.num_m = 100
        par.max_m = 20.0

        # income shocks
        par.G = 1.02 # growth factor

        par.sigma_psi = 0.1 # permanent income shock std
        par.sigma_xi = 0.1 # transitory income shock std

        par.prob_arrival_kids = 1.00 # Probability of having a kid // Test with = 0.0 as you never get any kid...

        par.num_psi = 5
        par.num_xi = 5

        # simulation
        par.simN = 1000
        par.seed = 9210

        # parallization
        par.num_threads = 4
        
    def allocate(self):
        par = self.par
        sol = self.sol
        sim = self.sim

        # a. setup grids
        self.setup_grids()

        # b. memory for solution
        shape_sol = (par.T, par.num_kids,par.num_m)     # Need to update this whenever I change the model: Needs to have the form (States, Choices)
        sol.V = np.nan + np.ones(shape_sol)             # Given shape_sol, this automatically takes the form of an array with dimensions (States, Choices)
        sol.c = np.nan + np.ones(shape_sol) 
        
        # c. memory for simulation
        shape_sim = (par.simN,par.T)
        sim.c = np.nan + np.zeros(shape_sim)
        sim.m = np.nan + np.zeros(shape_sim)
        sim.a = np.nan + np.zeros(shape_sim)
        sim.C = np.nan + np.zeros(shape_sim)
        sim.M = np.nan + np.zeros(shape_sim)
        sim.A = np.nan + np.zeros(shape_sim)
        sim.P = np.nan + np.zeros(shape_sim)
        sim.Y = np.nan + np.zeros(shape_sim)
        sim.Kids = np.zeros(shape_sim, dtype = ('int')) # Gives you a float: np.nan + np.zeros(shape_sim, dtype = ('int')) # NEW
        
        # d. initialization, no assets and permanent income of 1
        sim.a_init = np.zeros(par.simN)
        sim.P_init = np.ones(par.simN)

        # e. random log-normal, mean one income shocks
        np.random.seed(par.seed)
        sim.xi = np.exp(par.sigma_xi*np.random.normal(size=shape_sim) - 0.5*par.sigma_xi**2)
        sim.psi = np.exp(par.sigma_psi*np.random.normal(size=shape_sim) - 0.5*par.sigma_psi**2)

        # f. initialization, no kids:
        sim.kids_init = np.zeros(par.simN, dtype =('int'))  # NEW
        sim.kids_update = np.random.uniform(low=0, high=1, size=shape_sim)

    def setup_grids(self):
        par = self.par
        
        # a. wealth grid with more mass at lower values.
        par.grid_m = nonlinspace(1.0e-6,par.max_m,par.num_m,1.1) 

        # b. transitory and permanent income shocks (Gauss Hermite quadrature)
        shocks = quadrature.create_PT_shocks(par.sigma_psi,par.num_psi,par.sigma_xi,par.num_xi)
        par.grid_psi,par.psi_w,par.grid_xi,par.xi_w,par.num_shocks = shocks

    def solve(self):
        sol = self.sol
        par = self.par 

        # call c++ file usinge the current model.cpp.NAME, where NAME is the name of the function and must have "EXPORT" in front of it in the cpp file.
        self.cpp.solve(sol,par)

    def simulate(self):
        sol = self.sol
        par = self.par 
        sim = self.sim 

        # call c++ file usinge the current model.cpp.NAME, where NAME is the name of the function and must have "EXPORT" in front of it in the cpp file.
        self.cpp.simulate(sim,sol,par)


    