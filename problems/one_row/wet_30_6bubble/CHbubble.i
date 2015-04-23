# This output simulates 2 bubble caps coalescing together at a boundary with varying BCs
# Simulation is 2-D
# Mesh adaptivity and time step adaptivity is used

[Mesh]
  # Mesh block.  Meshes can be read in or automatically generated
  # Initial uniform refinement of the mesh
  type = FileMesh
  file = 6_wet_large.e
[]

[Variables]
  [./c]
    order = FIRST # order for element shape function
    family = LAGRANGE # shape function type
    [./InitialCondition]
      type = SmoothCirclesIC # Initial condition creates 2 circles  
      x1 = -55
      y1 = 0
      z1= -22
      invalue = 1.2
      outvalue = -1
      radius = 10
      numbub = 6
      bubspac = 22
      z2 = 40
    [../]
  [../]
  [./w]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Functions]
  [./bc_func]
    type = ParsedFunction
    value = sqrt(2*.1)/2*cos(pi/6)*(1-c^2)
    vars = c
  [../]
[]

[AuxVariables]
  [./c_aux]
    order = FIRST
    family = LAGRANGE
  [../]
  [./c_en]
   order = FIRST
   family = LAGRANGE
 [../]
[]

[Preconditioning]
  active = 'SMP'
  [./PBP]
    type = PBP
    solve_order = 'w c'
    preconditioner = 'AMG ASM'
    off_diag_row = 'c '
    off_diag_column = 'w '
  [../]
  [./SMP]
    type = SMP
    off_diag_row = 'w c'
    off_diag_column = 'c w'
  [../]
[]

[Kernels]
  [./cres]
    type = SplitCHMath
    variable = c
    kappa_name = kappa_c
    w = w
  [../]
  [./wres]
    type = SplitCHWRes
    variable = w
    mob_name = M
  [../]
  [./time]
    type = CoupledImplicitEuler
    variable = w
    v = c
  [../]
[]

[AuxKernels]
  [./c_growth]
    type = CoupledFunctionAux
    variable = c_aux
    value = 1.2
    coupled = c
  [../]
  [./c_energy]
    type = EnergyCoupledAux
    variable = c_en
    coupled = c
  [../]
[]

[BCs]
  active = 'WetNeumann NeumannW NeumannC'
  [./WetNeumann]
    type = FunctionNeumannBC
    variable = c
    boundary = 'wetting'
    function = bc_func
  [../]
  [./NeumannW]
    type = NeumannBC
    variable = w
    boundary ='wetting non_wetting'
    value = 0
  [../]
 [./NeumannC]
    type = DirichletBC
    variable = c
    boundary = 'non_wetting'
    value = -1
 [../]
[]

[Materials]
  [./constant]
    type = PFMobility
    block = 1
    mob = 2.0
    kappa = 0.1
  [../]
[]

[Adaptivity]
  initial_steps = 3
  marker = errorfrac
  max_h_level = 3
  [./Indicators]
    [./error]
      stop_time = 2000.0
      type = GradientJumpIndicator
      variable = c
    [../]
  [../]
  [./Markers]
    [./errorfrac]
      stop_time = 2000.0
      type = ErrorFractionMarker
      refine = 0.5
      coarsen = 0.2
      indicator = error
    [../]
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  # petsc options = '-snes -ksp_monitor'
  type = Transient
  scheme = BDF2
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -ksp_grmres_restart -sub_ksp_type -sub_pc_type -pc_asm_overlap'
  petsc_options_value = 'asm         31   preonly   lu      1'
  l_max_its = 30
  l_tol = 1.0e-3
  nl_max_its = 10
  nl_rel_tol = 1.0e-9
  end_time = 2000.0
  [./TimeStepper]
    type = DT2
    dt = .4
    e_max = 6.0e2
    e_tol = 1.0e-1
    max_increase = 1.5
  [../]
[]

[Postprocessors]
  [./total_phase]
    type = ElementIntegralVariablePostprocessor
    variable = c
   [../]
  [./residual]
    type = Residual
  [../]
  [./total_energy]
    type = ElementIntegralVariablePostprocessor
    variable = c_en
   [../]
  [./interface_energy]
    type = ElementIntegralGradPostprocessor
    variable = c
  [../]
  [./max_time_derivative]
    type = ElementMaxTimeDerivative
    variable = c
  [../]
[]

[Outputs]
  file_base = out1
  [./exodus]
  type = Exodus
  output_initial = true
  output_final = true
  interval = 4
  [../]
  [./CSV]
  type = CSV
  file_base = out1
  output_initial = true
  output_final = true
  interval = 2
  [../]
  [./console]
    type = Console
    perf_log = true
    linear_residuals = true
  [../]
  [./out]
    type = XDA
   output_final = true
   output_intermediate = false 
  [../]
[]

