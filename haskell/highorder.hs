--Implementation of various list function using recursion,
--compression and higher order functions.
--By: Abrothguer

--Find all the divisors of a given number x.
----------------------------------------------------------
div_rec :: Int->[Int]

div_rec n = 
    if(n <= 0) then []
    else div_recaux n n

div_recaux :: Int->Int->[Int]

div_recaux 1 n = [1]

div_recaux c n = 
    if(mod n c == 0) then c:div_recaux (c-1) n
    else div_recaux (c-1) n

----------------------------------------------------------
div_comp :: Int->[Int]

div_comp n = 
    [y | y <- [1..n], mod n y == 0]

----------------------------------------------------------
checkdiv :: Int->Int->Bool

checkdiv n x = 
    if(mod n x == 0) then True
    else False

div_high :: Int->[Int]

div_high n = 
    filter (checkdiv n) [1..n]

--Lenght of a list.
----------------------------------------------------------
unit :: Int->Int

unit _ = 1

leng_high :: [Int]->Int

leng_high x = 
    foldr1 (+) (map unit x)


----------------------------------------------------------
leng_comp :: [Int]->Int

leng_comp x =
    sum([unit y | y<-x])

--Separate even and odds integers on a list.
----------------------------------------------------------
even_odd_comp :: [Int]->[[Int]]

even_odd_comp x = 
    [[y | y<-x, mod y 2 == 0],[w | w<-x, mod w 2 == 1]] 

----------------------------------------------------------
even_odd_high :: [Int]->[[Int]]

even_odd_high x = 
    [filter (even) x, filter (odd) x]

--Sum of the squares of the natural numbers up to n.
----------------------------------------------------------
sum_square :: Int->Int

sum_square x =
    foldr1 (+) (map (^2) [1..x])

sum_square_comp :: Int->Int

sum_square_comp x = 
    sum [y^2 | y<-[1..x]]

--Elimitane consecutive duplicates on a list.
----------------------------------------------------------
group :: [Int]->[[Int]]

group [x] = [[x]]

group (x:xs) = 
    if(x == head (head y)) then (x: (head y)):(tail y)
    else [x]:y
    where
        y = group xs

compress :: [Int]->[Int]

compress x = 
    map (head) (group x)

--Reverse a list using foldr and foldl.
----------------------------------------------------------
revr :: Int->[Int]->[Int]

revr x l = l ++ [x]

rev_foldr :: [Int]->[Int]

rev_foldr x =
    foldr (revr) [] x

----------------------------------------------------------
revl :: [Int]->Int->[Int]

revl l x = [x] ++ l

rev_foldl :: [Int]->[Int]

rev_foldl x =
    foldl (revl) [] x

--Remove elements of the first list from the second list.
----------------------------------------------------------
beg_fst [] c l = c:l

beg_fst (lc:lcs) c l = 
    if(c == lc) then l
    else beg_fst lcs c l

rm_fst_snd :: String->String->String

rm_fst_snd x y = 
    foldr (beg_fst x) [] y

--Defining filter using foldr and foldl.
----------------------------------------------------------
fltr :: (Int->Bool)->Int->[Int]->[Int]

fltr f x l = 
    if(f x == True) then [x] ++ l
    else l

fdr_filter :: (Int->Bool)->[Int]->[Int]

fdr_filter f x = 
    foldr (fltr f) [] x

----------------------------------------------------------
fltl :: (Int->Bool)->[Int]->Int->[Int]

fltl f l x =
    if(f x == True) then l ++ [x]
    else l

fdl_filter :: (Int->Bool)->[Int]->[Int]

fdl_filter f x =
    foldl (fltl f) [] x

--Inits returns the initial segments of a list.
----------------------------------------------------------
ins_list :: Char->[[Char]]->[[Char]]

ins_list n [] = [[]]

ins_list n rt = (n:(head rt)):(ins_list n (tail rt))  

inits :: [Char]->[[Char]]

inits x =
    reverse(foldr (ins_list) [] x)

--Calculates the sum of 1/i! with i = 0->n
----------------------------------------------------------
fat :: Double->Double

fat 0 = 1

fat n = product[1..n]

approx_fat :: Double->Double

approx_fat n = l
    foldl (+) 0 l
    where
        l = map (1/) ln
        ln = [fat y | y<-[0..n]]