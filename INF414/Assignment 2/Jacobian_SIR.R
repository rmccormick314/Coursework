# Author: JM Mihaljevic
# Project Description:
## Eigenvalues of jacobian (SIR w/ Demography)

#-------------------------------------------------------
#-------------------------------------------------------

# Define parameter values:
beta = 1*365   #1/time
gamma = 1/10*365  #1/time
mu = (1/70)

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
J[1,1] = -mu
J[1,2] = -beta
J[1,3] = 0

# Row 2
J[2,1] = 0
J[2,2] = beta-(gamma + mu)
J[2,3] = 0

# Row 3
J[3,1] = 0
J[3,2] = gamma
J[3,3] = -mu

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
J[1,1] = -mu*(R_naught-1)-mu
J[1,2] = -beta*(1/R_naught)
J[1,3] = 0
  
# Row 2
J[2,1] = mu*(R_naught-1)
J[2,2] = beta*(1/R_naught) - (gamma + mu)
J[2,3] = 0
  
# Row 3
J[3,1] = 0
J[3,2] = gamma
J[3,3] = -mu
  
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
