# Simulation is 3-D
# Mesh adaptivity and time step adaptivity is used

[Mesh]
  # Mesh block. Read in generated mesh from previous simulation
  # Initial uniform refinement of the mesh
  type = FileMesh
  file = out1_0000_mesh.xda
[]

[Functions]
  [./sol]
    type = SolutionFunction
    solution = solution
  [../]
[]


[Variables]
  [./c]
  [../]
  [./w]
    order = FIRST
    family = LAGRANGE
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

[AuxKernels]
  [./c_growth]
    type = CoupledFunctionAux
    variable = c_aux
    value= 1.03
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

#Read in modified c_aux values for initial condition on c
[UserObjects]
  [./solution]
    type = SolutionUserObject
    mesh = out1_0000_mesh.xda
    system_variables = c_aux
    execute_on = initial
    es = out1_0000.xda
    system = aux0
  [../]
[]

[Adaptivity]
  marker = errorfrac
  max_h_level = 4
  [./Indicators]
    [./error]
      type = GradientJumpIndicator
      variable = c
    [../]
  [../]
  [./Markers]
    [./errorfrac]
      type = ErrorFractionMarker
      refine = 0.48
      coarsen = 0.2
      indicator = error
    [../]
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  scheme = BDF2
  solve_type = PJFNK
  # petsc_options_iname = '-pc_type -ksp_grmres_restart -sub_ksp_type -sub_pc_type -pc_asm_overlap'
  # petsc_options_value = 'asm         31   preonly   lu      1'

  petsc_options_iname = '-pc_type -pc_asm_overlap  -sub_pc_type -sub_pc_factor_levels'
  petsc_options_value = 'asm      1                ilu          2'

  l_max_its = 30
  l_tol = 1.0e-3
  nl_max_its = 10
  nl_rel_tol = 1.0e-9
  end_time = 5
  [./TimeStepper]
    type = SolutionTimeAdaptiveDT
    dt = .4
    percent_change = .5
  [../]
[]



[Outputs]
  file_base = out2
  [./exodus]
  type = Exodus
  execute_on = 'initial timestep_end'
  interval = 2
  [../]
  [./console]
    type = Console
    perf_log = true
    output_linear = true
  [../]
  [./out]
    type = XDA
   execute_on = 'final'
  [../]
[]

#Initial condition is solution function
[ICs]
  [./c_func]
    function = sol
    variable = c
    type = FunctionIC
  [../]
[]

