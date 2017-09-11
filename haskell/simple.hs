--The double function finds the double of a number.
double :: Int->Int
double x = x*2

--The triple function finds the triple of a number.
triple :: Int->Int
triple x = x*3

--The greater_3 function finds the largest of 3 numbers.
greater_3 :: Int->Int->Int->Int
greater_3 x y z = 
    if(x>=y && x>=z) then x 
    else if(y>=x && y>=z) then y
    else if(z>=x && z>=y) then z
    else -1

--The smaller_3 function finds the lesser of 3 numbers.
smaller_3 :: Int->Int->Int->Int
smaller_3 x y z =
    if(x<=y && x<=z) then x
    else if(y<=x && y<=z) then y
    else if(z<=x && z<=y) then z
    else -1

--The sum_until function returns the sum of all natural
--numbers up to n.
sum_until :: Int->Int
sum_until n = sum [1..n]

--The nth_AP function returns the nth term of a AP 
--starting in 'a' with commom difference 'd'.
nth_AP :: Int->Int->Int->Int
nth_AP a d n = a+(n-1)*d

--The nth_GP function returns the nth term of a GP
--starting at 'a' with commom ratio 'r'.
nth_GP :: Int->Int->Int->Int
nth_GP a r n = a*r^(n-1)

--The sum_AP function returns the sum of the nth terms
--in a AP starting at 'a' with commom difference 'd'.
sum_AP :: Int->Int->Int->Int
sum_AP a d n = div (n*(a+an)) 2
    where an = nth_AP a d n

--The sum_GP function returns the sum of the nth terms
--in a GP starting at 'a' with commom ratio 'r'.
sum_GP :: Int->Int->Int->Int
sum_GP a r n =
    if(r>1) then div (a*(r^n-1)) (r-1)
    else if(r<1) then div (a*(1-r^n)) (1-r)
    else a*n

--The fibonacci function returns the fibonacci of n.
fibonacci :: Int->Int
fibonacci n = 
    if(n==1 || n==2) then 1
    else (fibonacci (n-1)) + (fibonacci (n-2))

--The leap_year function returns true if n is a leap
--year and false if it isn't.
leap_year :: Int->Bool
leap_year n =
    if((mod n 400==0) || (mod n 4==0 && mod n 100/=0)) then True
    else False

--The factorial function returns the factorial of n.
factorial :: Int->Int
factorial n = 
    if(n==0) then 1
    else product [1..n]

--The average function returns the round average of a list.
average :: [Int]->Int
average n = div (sum n) (length n)

--The test_dividers function returns the numbers of dividers
--of a number 'n', in the function, 'd'(starts at 1) is a 
--possible divisor and 'ac'(starts at 0) is an accumulator.
test_dividers :: Int->Int->Int->Int
test_dividers n d ac =
    if(d > div n 2) then ac
    else if(mod n d == 0) then test_dividers n (d+1) (ac+1)
    else test_dividers n (d+1) ac

--The dividers function returns the number of dividers of 
--a number 'n'.
dividers :: Int->Int
dividers n =
    test_dividers n 1 0

--The prime function returns true if x is a prime number
--and false if it is not.
prime :: Int->Bool
prime x =
    if(d == 1) then True
    else False
    where d = dividers x

--The is_upper function returns true if c is a uppercase
--letter and false if it is not.
is_upper :: Char->Bool
is_upper c =
    if(c>='A' && c<='Z') then True
    else False

--The is_lower function returns true if c is a lowercase
--letter and false if it is not.
is_lower :: Char->Bool
is_lower c =
    if(c>='a' && c<='z') then True
    else False

--The is_digit function returns true if c is a digit
--and false if it is not.
is_digit :: Char->Bool
is_digit c =
    if(c>='0' && c<='9') then True
    else False

--The repeat_string_aux function returns the string s
--repeated n times.
repeat_string :: String->Int->String
repeat_string s n =
    if(n==1) then s
    else s ++ repeat_string s (n-1)

--The n_spaces function returns a string with n spaces.
n_spaces :: Int->String
n_spaces n = 
    if(n==0) then ""
    else " " ++ n_spaces (n-1)

--The spaces_until_length function adds space characters in a
--string s until it reaches the size n.
spaces_until_length :: String->Int->String
spaces_until_length s n =
    if(length s >= n) then s
    else " " ++ spaces_until_length s (n-1)

--The pair_gs function takes x y z and returns a pair
--made by the greatest and the smallest of them.
pair_gs :: Int->Int->Int->(Int,Int)
pair_gs x y z = (smaller_3 x y z, greater_3 x y z)

--The my_gcd function returns the greatest commom divisor
--of two numbers x and y.
my_gcd :: Int->Int->Int
my_gcd x y =
    if(x<0 || y<0) then -1
    else if(x==0 || y==0) then 0
    else if(m==0) then y
    else my_gcd y m
    where m = mod x y

--The my_lcm function returns the lowest commom multiple
--of two numbers x and y.
my_lcm :: Int->Int->Int
my_lcm x y =
    if(x<0 || y<0) then -1
    else if(x==0 || y==0) then 0
    else div (x*y) (my_gcd x y)

--The make_triplet_asc function takes x y z and returns a
--a triplet in ascending order.
make_triplet_asc :: Int->Int->Int->(Int,Int,Int)
make_triplet_asc x y z = 
    if(smaller_3 x y z == x) then
        if(y<=z) then (x,y,z)
        else (x,z,y)
    else if(smaller_3 x y z == y) then
        if(x<=z) then (y,x,z)
        else (y,z,x)
    else
        if(x<=y) then (z,x,y)
        else (z,y,x)

--The make_triplet_des function takes x y z and returns a
--a triplet in descending order.
make_triplet_des :: Int->Int->Int->(Int,Int,Int)
make_triplet_des x y z =
    if(greater_3 x y z == x) then
        if(y>=z) then (x,y,z)
        else (x,z,y)
    else if(greater_3 x y z == y) then
        if(x>=z) then (y,x,z)
        else (y,z,x)
    else
        if(x>=y) then (z,x,y)
        else (z,y,x)

--Definition of types point and line,
--where line can be defined by two values or two points.
type Point = (Double,Double)
type Line_Values = (Double,Double)
type Line_Points = (Point,Point)

--The make_line function takes two points and returns the
--line (value) formed by them.
make_line :: Point->Point->Line_Values
make_line (xa,ya) (xb,yb) = (m,m*(-xb)+yb)
        where m = (yb-ya)/(xb-xa)

--The is_vertical function takes a line (2 points) and
--returns true if the line is vertical and false if it is not.
is_vertical :: Line_Points->Bool
is_vertical ((xa,ya),(xb,yb)) = 
    if(xa==xb && ya/=yb) then True
    else False

--The is_horizontal function takes a line (2 points) and returns
--true if the line is horizontal and false if it is not.
is_horizontal :: Line_Points->Bool
is_horizontal ((xa,ya),(xb,yb)) =
    if(ya==yb && xa/=xb) then True
    else False

--The line_intersection function takes two lines and returns
--the point of intersection.
line_intersection :: Line_Values->Line_Values->Point
line_intersection (a1,b1) (a2,b2) = (x,y)
    where x = (b1-b2)/(a2-a1)
          y = b1 + a1*x
