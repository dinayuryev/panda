# Simulation is 2-D
# Mesh adaptivity and time step adaptivity is used

[Mesh]
  # Mesh block.  Meshes can be read in or automatically generated
  # Initial uniform refinement of the mesh
  type = FileMesh
  file = out1_0001_mesh.xda
[]

[Functions]
  [./bc_func]
    # type=ParsedFunction
    # value = .1*cos(7*pi/18)
    # value = 3/4*cos(9*pi/18)*(1-c^2)
    type = PiecewiseLinear
    data_file = pattern.txt
    format = rows
    axis = 0
  [../]
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
    value = 1.1
    coupled = c
  [../]
[]

[BCs]
  active = 'top left right bottom'
  [./bottom]
    type = WettingNeumannBC
    variable = c
    boundary = bottom
    function = bc_func
  [../]
  [./bottwo]
    type = NeumannBC
    variable = w
    boundary = bottom
    value = 0
  [../]
  [./top]
    type = NeumannBC
    variable = c
    boundary = top
    value = 0
  [../]
  [./left]
    type = NeumannBC
    variable = c
    boundary = left
    value = 0
  [../]
  [./right]
    type = NeumannBC
    variable = c
    boundary = right
    value = 0
  [../]
[]

[Materials]
  [./constant]
    type = PFMobility
    block = 0
    mob = 2.0
    kappa = 0.1
  [../]
[]

[UserObjects]
  [./solution]
    type = SolutionUserObject
    mesh = out1_0001_mesh.xda
    nodal_variables = c_aux
    execute_on = initial
    es = out1_0001.xda
    system = aux0
  [../]
[]

[Adaptivity]
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
      refine = 0.3
      coarsen = 0.3
      indicator = error
    [../]
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  scheme = BDF2
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -ksp_grmres_restart -sub_ksp_type -sub_pc_type -pc_asm_overlap'
  petsc_options_value = 'asm         31   preonly   lu      1'
  l_max_its = 30
  l_tol = 1.0e-3
  nl_max_its = 10
  nl_rel_tol = 1.0e-9
  end_time = 20.0
  [./TimeStepper]
    type = DT2
    dt = .5
    e_max = 6.0e2
    e_tol = 1.0e-1
    max_increase = 1.4
  [../]
[]

[Outputs]
  file_base = out2
  output_initial = true
  exodus = true
 # checkpoint = true
 # xda = true
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

[ICs]
  [./c_func]
    function = sol
    variable = c
    type = FunctionIC
  [../]
[]

