Sorting with Mltiple Keys and Binary Search

-data link: https://www.csie.ntu.edu.tw/~cyshih/dsa_hw2/ 


1. Simple query: Find the data corresponding to the inputs of [date], [currency], and [exchange]. 
  input: query	[date]	[currency]	[exchange]
  output: [low] [high] [cap] 
  *[low] & [high] should be float, accurate to the 4th decimal places. Note that you need to use "float" in order to conform to our standard program, which might lose some precision though.

2. Daily min/max: Find the minimum or maximum on a given date of a given currency.
  input:  price	[min/max]	[date]	[currency] 
  output: [min/max of the currency on that date]
  *The output should be float, accurate to the 4th decimal places. Note that you need to use "float" in order to conform to our standard program, which might lose some precision though.

3. Total cap of all currencies, for a given date and a given exchange
  input: cap	[date]	[exchange] 
  output: [total_cap] 
  *The output should be long long int. 

4. End of query
  input: end
  action: exit the program
