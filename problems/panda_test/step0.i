# This output simulates 6 bubbles coalescing together on position dependant BCs

[Mesh]
  # Mesh block.  Meshes is read in
  # Initial uniform refinement of the mesh
  type = FileMesh
  file = 6patch_space5_coarse.e
[]

[Variables]
  [./c]
    order = FIRST # order for element shape function
    family = LAGRANGE # shape function type
    [./InitialCondition]
      # Initial condition creates 6 circles
      type = SpecifiedSmoothCircleIC
      variable = c
      x_positions = '-62.5 -37.5 -12.5 12.5 37.5 62.5'
      y_positions = '0 0 0 0 0 0'
      z_positions= '-22 -22 -22 -22 -22 -22'
      radii= '10 10 10 10 10 10'
      invalue = 1
      outvalue = -1
      int_width=.5
    [../]
  [../]
  [./w]
    order = FIRST
    family = LAGRANGE
  [../]
[]

#Generate auxvariables for changing BCs for next run and postprocessors
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
  [./SMP]
    type = SMP
    off_diag_row = 'w c'
    off_diag_column = 'c w'
  [../]
[]

[Kernels]
  [./cres]
    type = SplitCHParsed
    variable = c
    kappa_name = kappa_c
    w = w
    f_name = F
  [../]
  [./wres]
    type = SplitCHWRes
    variable = w
    mob_name = M
    args = c
  [../]
  [./time]
    type = CoupledTimeDerivative
    variable = w
    v = c
  [../]
[]

#Modify c value for next simulation initial condition
[AuxKernels]
  [./c_growth]
    type = CoupledFunctionAux
    variable = c_aux
    value = 1.2
    coupled = c
  [../]
[]


[BCs]
  active = 'WetNeumann NeumannW DirichletC'
  [./WetNeumann]
    type = WettingAngleNeumannBC
    variable = c
    boundary = 'wetting'
    value = .274
  [../]
  [./NeumannW]
    type = NeumannBC
    variable = w
    boundary ='wetting non-wetting'
    value = 0
  [../]
 [./DirichletC]
    type = DirichletBC
    variable = c
    boundary = 'non-wetting'
    value = -1
 [../]
[]

[Materials]
  [./kappa]
    type = GenericConstantMaterial
    block = 1
    prop_names = 'kappa_c'
    prop_values = '.1'
  [../]
  [./mob]
    type = DerivativeParsedMaterial
    block = 1
    f_name = M
    args = c
    function = 'tanh(4*c+1.5)+1'
    outputs = exodus
    derivative_order = 1
  [../]
  [./free_energy]
    type = MathEBFreeEnergy
    block = 1
    f_name = F
    c = c
  [../]
[]

[Adaptivity]
  initial_steps = 2
  marker = errorfrac
  max_h_level = 3
  [./Indicators]
    [./error]
      type = GradientJumpIndicator
      variable = c
    [../]
  [../]
  [./Markers]
    [./errorfrac]
      type = ErrorFractionMarker
      refine = 0.45
      coarsen = 0.2
      indicator = error
    [../]
  [../]
[]

[Executioner]
  type = Transient
  scheme = BDF2

  solve_type = 'PJFNK'

  # Original PETSC options.
  # petsc_options_iname = '-pc_type -ksp_grmres_restart -sub_ksp_type -sub_pc_type -pc_asm_overlap'
  # petsc_options_value = 'asm         31   preonly   lu      1'

  petsc_options_iname = '-pc_type -pc_asm_overlap  -sub_pc_type -sub_pc_factor_levels'
  petsc_options_value = 'asm      1                ilu          2'

  l_max_its = 30
  l_tol = 1.0e-3
  nl_max_its = 10
  nl_rel_tol = 1.0e-9
  end_time = 2000.0
  [./TimeStepper]
    type = SolutionTimeAdaptiveDT
    dt = .2
    percent_change = .5
  [../]
[]

[Outputs]
  file_base = out1
  [./exodus]
  type = Exodus
  execute_on = 'initial timestep_end'
  interval = 6
  [../]
  [./CSV]
  type = CSV
  file_base = out1
  interval = 2
  [../]
  [./console]
    type = Console
    perf_log = true
    output_linear = true
  [../]
  [./out]
    type = XDA
    execute_on = 'timestep_end'
  [../]
[]
