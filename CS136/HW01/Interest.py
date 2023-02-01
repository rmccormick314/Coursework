import math

account = 1000
interest = 0.05

def yearly_interest(account):
    yearsInterest = account * interest
    newBalance = account + yearsInterest
    return newBalance

print('Account Balance: ' + str(account))

yearOne = yearly_interest(account)
yearTwo = yearly_interest(yearOne)
yearThree = yearly_interest(yearTwo)

print('Year One Balance: ' +str(yearOne))
print('Year Two Balance: ' +str(yearTwo))
print('Year Three Balance: ' +str(yearThree))
