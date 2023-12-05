#' A function that plays the fizz buzz game.
#'
#' The user inputs a vector of poa=sitive integers. The fuction
#' returns a vector of values. It checks to see if the number is divisible
#' by 3, 5, or both 3 and five, and responds with
#' fizz buzz if divisible by 3 and 5, fizz if divisible by 3, buzz, if
#' divisible by 5, or just the nummber if not divisible by either 3 or 5.
#'
#' @param vector a vector of values
#' @return a vector of fizz buzz results
#' @examples
#' FizzBuzz(1:30)
#' FizzBuzz(c(2,5,3,15,8))
#' @export

FizzBuzz <- function(vector){
  library(dplyr)
  fizzbuzz = NULL
  for(i in 1:length(vector)){
    ifelse(round(vector[i],0)!=vector[i]|vector[i]<=0|is.infinite(vector[i
    ])|is.character(vector[i]),
    stop(paste('Entry ',toString(i),' is not a positive integer')),
    #stop("BLAH"),
    fizzbuzz[i] <- case_when(vector[i] %% 3 != 0 & vector[i] %% 5
                             != 0 ~ toString(vector[i]),
                             vector[i] %% 3 == 0 & vector[i] %% 5
                             == 0 ~ 'Fizz Buzz',
                             vector[i] %% 3 == 0 ~ 'Fizz',
                             vector[i] %% 5 == 0 ~ 'Buzz'))
  }
  return(fizzbuzz)
}
