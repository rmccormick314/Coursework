# Check to see if the output vector for fizzbuzz is the same length as the
# input vector
test_that('Vector Lengths correct', {
  expect_equal(length(c(2,5,6,15)), length(FizzBuzz(c(2,5,6,15))) )
  expect_error(FizzBuzz(c(2,5,-6,15)))
  expect_error(FizzBuzz(c(2,5,6.28,15)))
  expect_error(FizzBuzz(c(2,5,6/0,15)))
})
