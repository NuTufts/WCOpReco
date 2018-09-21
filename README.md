# WCOpReco

This repository is designed to port Wire-Cell's Light Reconstruction code into Larsoft with the goals of: 
  - Make the code general for use by each analysis group
  - Create a conversion tool between Wire-cell and our code
  - Incorporate time variant parameters (e.g. PMT gain)
  - Replace hard-coded values with programmable parameters
  - Make Waveform Prep, Ophit finding, Opflash building algos modular

Much of this code is based on Wire Cell's Light reconstruction algorithms (Brooke Russell et al.)

The originial WC code can be found at:

Top level code:
  - https://github.com/BNLIF/wire-cell

Specific functions:
  - https://github.com/BNLIF/wire-cell-data/tree/master/src
    - Opflash.cxx
    - COphit.cxx
  - https://github.com/BNLIF/wire-cell-2dtoy/tree/master/src
    - ToyLightReco.cxx
  - https://github.com/BNLIF/wire-cell-ress/tree/0011db58a633c62dd091b62312046c962ddb0470/src
    - LassoModel.cxx
    - LinearModel.cxx
    - ElasticNetModel.cxx

