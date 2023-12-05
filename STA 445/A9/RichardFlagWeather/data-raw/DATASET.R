## code to prepare `DATASET` dataset goes here

usethis::use_data(DATASET, overwrite = TRUE)

library( tidyverse )
Flagstaff_Weather <- read_csv( "data-raw/Pulliam_Airport_Weather_Station.csv" )
Flagstaff_Weather <- Flagstaff_Weather[c('DATE', 'PRCP', 'SNOW', 'TMAX', 'TMIN')]

usethis::use_data(Flagstaff_Weather)
