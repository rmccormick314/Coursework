# Author: JM Mihaljevic
# Project Description:
## Eigenvalues of jacobian (SIR w/ Demography)

#-------------------------------------------------------
#-------------------------------------------------------

# Define parameter values:
beta = 0.08
gamma = 1/10
mu = (1/70) * (1/365)

# Calculate R_0:
R_naught = beta/(mu + gamma)

print(paste0("R0: ", R_naught))

#-------------------------------------------------------
#-------------------------------------------------------
#########################
# Disease-free EQUILIBRIUM
########################

# Build the jacobian matrix:
J = matrix(0, nrow = 3, ncol = 3)

# Row 1
J[1,1] = 
J[1,2] = 
J[1,3] = 

# Row 2
J[2,1] = 
J[2,2] = 
J[2,3] = 

# Row 3
J[3,1] = 
J[3,2] = 
J[3,3] =

# Calculate the eigenvalues:
sir_eigen = eigen(J)

sir_eigen$values[1]
sir_eigen$values[2]
sir_eigen$values[3]

#####
# When R_naught < 1 
#####

# Real parts:
# Imaginary parts:
# Conclusion: 


#####
# When R_naught > 1 
#####

# Real parts:
# Imaginary parts:
# Conclusion: 

#-------------------------------------------------------
#-------------------------------------------------------
#########################
# Endemic EQUILIBRIUM
########################

# Build the jacobian matrix:
J = matrix(0, nrow = 3, ncol = 3)

# Row 1
J[1,1] = 
J[1,2] = 
J[1,3] = 
  
# Row 2
J[2,1] = 
J[2,2] = 
J[2,3] = 
  
# Row 3
J[3,1] = 
J[3,2] = 
J[3,3] =
  
# Calculate the eigenvalues:
sir_eigen = eigen(J)

sir_eigen$values[1]
sir_eigen$values[2]
sir_eigen$values[3]

#####
# When R_naught < 1 
#####

# Real parts:
# Imaginary parts:
# Conclusion: 


#####
# When R_naught > 1 
#####

# Real parts:
# Imaginary parts:
# Conclusion: 
