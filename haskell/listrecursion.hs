--Functions about lists and recursion.
--By: Abrothguer.

--The recursive_nthGP function finds, recursively the nth term
--of a GP starting at a and with commom ratio r. 
recursive_nthGP :: Int->Int->Int->Int

recursive_nthGP a r 1 = a

recursive_nthGP a r n = 
    r*recursive_nthGP a r (n-1)

--The recursive_nthAP function finds, recursively the nth term
--of a AP starting at a and with commom difference d.
recursive_nthAP :: Int->Int->Int->Int

recursive_nthAP a d 1 = a

recursive_nthAP a d n =
    d+recursive_nthAP a d (n-1) 

--The tailaux_nthGP function is an auxiliary function used to 
--calculate the nth term of a GP starting at a, with common 
--ratio r and accumulating the result on the variable t.
tailaux_nthGP :: Int->Int->Int->Int->Int

tailaux_nthGP a r 1 t = t

tailaux_nthGP a r n t = 
    tailaux_nthGP a r (n-1) (t*r)

--The tail_nthGP simply calls the tailaux_nthGP function.
tail_nthGP :: Int->Int->Int->Int

tail_nthGP a r n = tailaux_nthGP a r n a

--The tailaux_nthAP function is an auxiliary function used to 
--calculate the nth term of a AP starting at a, with common 
--difference d and accumulating the result on the variable t.
tailaux_nthAP :: Int->Int->Int->Int->Int

tailaux_nthAP a d 1 t = t

tailaux_nthAP a d n t = 
    tailaux_nthAP a d (n-1) (t+d)

--The tail_nthAP simply calls the tailaux_nthAP function.
tail_nthAP :: Int->Int->Int->Int

tail_nthAP a d n = tailaux_nthAP a d n a

--The recursive_sumGP function calculates the sum of the nth
--terms of a GP starting at a and with common ratio r.
recursive_sumGP :: Int->Int->Int->Int

recursive_sumGP a r 1 = a

recursive_sumGP a r n = 
    tail_nthGP a r n + recursive_sumGP a r (n-1)

--The recursive_sumAP function calculates the sum of the nth
--terms of a AP starting at a and with common difference d.
recursive_sumAP :: Int->Int->Int->Int

recursive_sumAP a d 1 = a

recursive_sumAP a d n = 
    tail_nthAP a d n + recursive_sumAP a d (n-1)

--The tailaux_sumGP function calculates the sum of the nth
--terms of a GP starting at a and with common ratio r,
--accumulating the sum in c and the current term in t.
tailaux_sumGP :: Int->Int->Int->Int->Int

tailaux_sumGP r 1 c t = c+t

tailaux_sumGP r n c t = 
    tailaux_sumGP r (n-1) (c+t) (t*r) 

--The tail_sumGP simply calls the tailaux_sumGP function.
tail_sumGP :: Int->Int->Int->Int

tail_sumGP a r n =
    tailaux_sumGP r n 0 a

--The tailaux_sumAP function calculates the sum of the nth
--terms of a AP starting at a and with common difference d,
--accumulating the sum in c and the current term in t.
tailaux_sumAP :: Int->Int->Int->Int->Int

tailaux_sumAP d 1 c t = c+t

tailaux_sumAP d n c t = 
    tailaux_sumAP d (n-1) (c+t) (t+d) 

--The tail_sumAP simply calls the tailaux_sumAP function.
tail_sumAP :: Int->Int->Int->Int

tail_sumAP a d n =
    tailaux_sumAP d n 0 a

--The recursive_fib function calculates the fibonacci of n.
recursive_fib :: Int->Int

recursive_fib 0 = 0

recursive_fib 1 = 1

recursive_fib n = 
    recursive_fib (n-1) + recursive_fib (n-2)

--The tailaux_fib function is an auxiliary function used to
--calculate the fibonacci of n, accumulating it on c, and storing
--the fibonacci of n-1 and n-2 on f1 and f2, respectively.
tailaux_fib :: Int->Int->Int->Int->Int

tailaux_fib 2 f2 f1 c = f1+f2

tailaux_fib n f2 f1 c = 
    tailaux_fib (n-1) (f2+f1) f2 c

--The tail_fib function simply calls tailaux_fib fucntion.
tail_fib :: Int->Int

tail_fib 0 = 0

tail_fib 1 = 1

tail_fib n = tailaux_fib n 1 0 0   

--The rept function repeats every element on a list.
rept :: [Int]->[Int]

rept [] = []

rept (x:xs) = x:l
    where 
        l = x:rept xs

--The recursive_length function returns the length of a list.
recursive_length :: [Int]->Int

recursive_length [] = 0

recursive_length (x:xs) = 
    1+recursive_length xs

--The tailaux_length function returns the length of a list,
--accumulating it on n.
tailaux_length :: [Int]->Int->Int

tailaux_length [] n = n

tailaux_length (x:xs) n =
    tailaux_length xs (n+1)

--The tail_length simply calls the tailaux_length function.
tail_length :: [Int]->Int

tail_length x = 
    tailaux_length x 0 

--The interval function returns the interval [a,b].
interval :: Int->Int->[Int]

interval a b =
    if(a == b) then [a]
    else if(a < b) then [a..b]
    else []

--The merge function merges two list of integers in 
--ascending order.
merge :: [Int]->[Int]->[Int]->[Int]

merge [] [] l = l

merge [] (y:ys) l = 
    merge [] ys (y:l)

merge (x:xs) [] l =
    merge [] xs (x:l)

merge (x:xs) (y:ys) l =
    if(x < y) then 
        merge xs (y:ys) (x:l)
    else 
        merge (x:xs) ys (y:l)

--The mergesort function sorts a list of integers.
mergesort :: [Int]->[Int]

mergesort [] = []

mergesort [a] = [a]

mergesort x = 
    reverse (merge l1 l2 [])
    where 
        l1 = mergesort (take m x)
        l2 = mergesort (drop m x)
        m = div (length x) 2

--The tailaux_rev function reverses a list of integers.
tailaux_rev :: [Int]->[Int]->[Int]

tailaux_rev [] l = l

tailaux_rev (x:xs) l =
    tailaux_rev xs (x:l)

--The tail_rev simply calls tailaux_rev function.
tail_rev :: [Int]->[Int]

tail_rev l = tailaux_rev l []

--The tailaux_digits function returns a list of the digits,
--accumulated on an auxiliary list, of a given number n.
tailaux_digits :: Int->[Int]->[Int]

tailaux_digits 0 l = l

tailaux_digits n l = 
    tailaux_digits (div n 10) ((mod n 10):l)

--The tail_digits simply calls the tailaux_digits function.
tail_digits :: Int->[Int]

tail_digits n = 
    tailaux_digits n []

--The recursive_occurrences function returns the number of 
--occurrences of a number n on a list l.
recursive_occurrences :: Int->[Int]->Int

recursive_occurrences n [] = 0

recursive_occurrences n (x:xs) =
    if(n == x) then 
        1 + recursive_occurrences n xs
    else 
        recursive_occurrences n xs

--The tailaux_occurrences function returns the number of
--occurrences of a number n on a list l, accumulated on c.
tailaux_occurrences :: Int->[Int]->Int->Int

tailaux_occurrences n [] c = c

tailaux_occurrences n (x:xs) c =
    if(n == x) then 
        tailaux_occurrences n xs (c+1)
    else 
        tailaux_occurrences n xs c

--The tail_occurrences simply calls the tailaux_occurrences function.
tail_occurrences :: Int->[Int]->Int

tail_occurrences n l =
    tailaux_occurrences n l 0
    
--The nth function returns the nth element of a list l.
nth :: Int->[Int]->Int

nth 1 (x:xs) = x

nth n (x:xs) =
    nth (n-1) xs

--The belongs_to function returns true if the element n belongs
--to the list and false if it does not.
belongs_to :: Int->[Int]->Bool

belongs_to n [] = False

belongs_to n (x:xs) =
    if(n == x) then 
        True
    else 
        belongs_to n xs

--The recursive_rmrep function removes all the repeated elements 
--of a given list l.
recursive_rmrep :: [Int]->[Int]

recursive_rmrep [] = []

recursive_rmrep (x:xs) = 
    if(belongs_to x xs) then 
        recursive_rmrep xs
    else 
        x:recursive_rmrep xs

--The tailaux_rmrep function removes all the repeated elements
--of a given list l.
tailaux_rmrep :: [Int]->[Int]->[Int]

tailaux_rmrep [] l = l

tailaux_rmrep (x:xs) l = 
    if(belongs_to x l) then 
        tailaux_rmrep xs l
    else 
        tailaux_rmrep xs (x:l)

--The tail_rmrep simply calls the tailaux_rmrep funcion.
tail_rmrep :: [Int]->[Int]

tail_rmrep x =
    tailaux_rmrep x []

--The recursive_unionrep function returns the union of 
--two given lists.
recursive_unionrep :: [Int]->[Int]->[Int]

recursive_unionrep [] [] = []

recursive_unionrep [] l = l

recursive_unionrep l [] = l

recursive_unionrep (x:xs) (y:ys) =
    x:m
    where 
        m = y:recursive_unionrep xs ys

--The tailaux_unionrep function returns the union of 
--two given lists.
tailaux_unionrep :: [Int]->[Int]->[Int]->[Int]

tailaux_unionrep [] [] l = l

tailaux_unionrep [] (y:ys) l = 
    tailaux_unionrep [] ys (y:l)

tailaux_unionrep (x:xs) [] l = 
    tailaux_unionrep xs [] (x:l)

tailaux_unionrep (x:xs) y l =
    tailaux_unionrep xs y (x:l)

--The tail_unionrep simply calls the tailaux_unionrep funcion.
tail_unionrep :: [Int]->[Int]->[Int]

tail_unionrep x y =
    tailaux_unionrep x y []

--The union_comp function returns the union of two lists.
union_comp :: [Int]->[Int]->[Int]

union_comp x y = 
    x ++ [e | e<-y, not(belongs_to e x)]

--The recursive_union function returns the union of two given lists
--eliminating repeated elements.
recursive_union :: [Int]->[Int]->[Int]

recursive_union [] [] = []

recursive_union [] (y:ys) =
    if(belongs_to y l) then l
    else y:l
    where 
        l = recursive_union [] ys

recursive_union (x:xs) y =
    if(belongs_to x l) then l
    else x:l
    where 
        l = recursive_union xs y
        
--The tailaux_union function returns the union of two lists,
--eliminating repeated elements.
tailaux_union :: [Int]->[Int]->[Int]->[Int]

tailaux_union [] [] l = l

tailaux_union [] (y:ys) l = 
    if(belongs_to y l) then 
        tailaux_union [] ys l
    else 
        tailaux_union [] ys (y:l)

tailaux_union (x:xs) y l =
    if(belongs_to x l) then 
        tailaux_union xs y l
    else 
        tailaux_union xs y (x:l)

--The tail_union simply calls the tailaux_union function.
tail_union :: [Int]->[Int]->[Int]

tail_union x y = 
    tailaux_union x y []

--The recursive_intersecrep function returns the intersection
--of two lists.
recursive_intersecrep :: [Int]->[Int]->[Int]

recursive_intersecrep [] _ = []

recursive_intersecrep _ [] = []

recursive_intersecrep (x:xs) y = 
    if(belongs_to x y) then 
        x:recursive_intersecrep xs y
    else 
        recursive_intersecrep xs y 

--The tailaux_intersecrep function returns the intersection
--of two lists.
tailaux_intersecrep :: [Int]->[Int]->[Int]->[Int]

tailaux_intersecrep [] _ l = l

tailaux_intersecrep _ [] l = l

tailaux_intersecrep (x:xs) y l =
    if(belongs_to x y) then 
        tailaux_intersecrep xs y (x:l)
    else 
        tailaux_intersecrep xs y l

--The tail_intersecrep simply calls the tailaux_intersecrep funcion.
tail_intersecrep :: [Int]->[Int]->[Int]

tail_intersecrep x y =
    if(length x < length y) then 
        tailaux_intersecrep x y []
    else 
        tailaux_intersecrep y x []

--The intersec_comp function returns the intersection of two lists
--eliminating repeated elements.
intersec_comp :: [Int]->[Int]->[Int]

intersec_comp x y =
    [e | e<-t, (belongs_to e y)]
    where 
        t = tail_rmrep x

--The recursive_intersec function return the intersection
--of two lists eliminating repeated elements.
recursive_intersec :: [Int]->[Int]->[Int]

recursive_intersec [] _ = []

recursive_intersec (x:xs) y =
    if(belongs_to x y) then
        x:recursive_intersec xs y
    else
        recursive_intersec xs y

--The tailaux_intersec function return the intersecetion of two
--lists accumulating it on l
tailaux_intersec :: [Int]->[Int]->[Int]->[Int]

tailaux_intersec [] y l = l

tailaux_intersec (x:xs) y l = 
    if(belongs_to x y) then
        tailaux_intersec xs y (x:l)
    else
        tailaux_intersec xs y l

--The tail_intersec simply calls the tailaux_intersec function.
tail_intersec :: [Int]->[Int]->[Int]

tail_intersec x y =
    reverse(tailaux_intersec x y [])

--The reptposaux function is an auxiliary funtion for the
--reptpos function.
reptposaux :: [Int]->Int->Int->[Int]->[Int]

reptposaux [] _ _ l = l

reptposaux (x:xs) n p l =
    if(p == n) then
        reptposaux xs (n+1) 0 l
    else
        reptposaux (x:xs) n (p+1) (x:l) 

--The reptpos function repeats the nth term of a list n times.
reptpos :: [Int]->[Int]

reptpos x = 
    reverse(reptposaux x 1 0 [])

--The recursive_take_even function returns a list with all 
--even elements on a given list.
recursive_take_even :: [Int]->[Int]

recursive_take_even [] = []

recursive_take_even (x:xs) =
    if(mod x 2 == 0) then
        x:recursive_take_even xs
    else
        recursive_take_even xs

--The tailaux_take_even function returns a list with all 
--even elements on a given list.
tailaux_take_even :: [Int]->[Int]->[Int]

tailaux_take_even [] l = l

tailaux_take_even (x:xs) l = 
    if(mod x 2 == 0) then
        tailaux_take_even xs (x:l)
    else
        tailaux_take_even xs l

--The tail_take_even simply calls tailaux_take_even function.
tail_take_even :: [Int]->[Int]

tail_take_even x =
    reverse(tailaux_take_even x []) 

--The recursive_take_odd function returns a list with all
--odd elements on a given list.
recursive_take_odd :: [Int]->[Int]

recursive_take_odd [] = []

recursive_take_odd (x:xs) = 
    if(mod x 2 /= 0) then
        x:recursive_take_odd xs
    else
        recursive_take_odd xs

--The tailaux_take_odd function returns a list with all
--odd elements on a given list.
tailaux_take_odd :: [Int]->[Int]->[Int]

tailaux_take_odd [] l = l

tailaux_take_odd (x:xs) l = 
    if(mod x 2 /= 0) then
        tailaux_take_odd xs (x:l)
    else
        tailaux_take_odd xs l

--The tail_take_odd simply calls tailaux_take_odd function.
tail_take_odd :: [Int]->[Int]

tail_take_odd x =
    reverse(tailaux_take_odd x []) 

--The recursive_take_evenodd function returns a tuple which contais
--a list of odd and a list of even number taken from l.
recursive_take_evenodd :: [Int]->([Int],[Int])

recursive_take_evenodd [] = ([],[])

recursive_take_evenodd (x:xs) = 
    if(mod x 2 == 0) then
        (x:(fst tp), snd tp)
    else
        (fst tp, x:(snd tp))
    where
        tp = recursive_take_evenodd xs


--The tailaux_take_evenodd function returns a tuple which contais
--a list of odd and a list of even number taken from l.
tailaux_take_evenodd :: [Int]->[Int]->[Int]->([Int],[Int])

tailaux_take_evenodd [] e o = (reverse(e),reverse(o))

tailaux_take_evenodd (x:xs) e o =
    if(mod x 2 == 0) then
        tailaux_take_evenodd xs (x:e) o
    else
        tailaux_take_evenodd xs e (x:o)

--The tail_take_evenodd simply calls the tailaux_take_evenodd function.
tail_take_evenodd :: [Int]->([Int],[Int])

tail_take_evenodd x =
    tailaux_take_evenodd x [] []

--The recursive_repelem function removes all occurrences of
--an element n in a list l.
recursive_repelem :: Int->[Int]->[Int]

recursive_repelem n [] = []

recursive_repelem n (x:xs) = 
    if(n == x) then
        recursive_repelem n xs
    else 
        x:recursive_repelem n xs 

--The tailaux_repelem function removes all occurrences of
--an element n in a list l.
tailaux_repelem :: Int->[Int]->[Int]->[Int]

tailaux_repelem n [] l = l

tailaux_repelem n (x:xs) l = 
    if(n == x) then
        tailaux_repelem n xs l
    else
        tailaux_repelem n xs (x:l)

--The tail_repelem simply calls the tailaux_repelem function.
tail_repelem :: Int->[Int]->[Int]

tail_repelem n x =
    reverse(tailaux_repelem n x [])

--The takeposaux function returns a list of the elements of a list
--determined by a list p, of positions.
takeposaux :: [Int]->[Int]->[Int]->[Int]

takeposaux [] x l = l

takeposaux (p:ps) x l =
    takeposaux ps x ((nth p x):l)

--The takepos function simply calls the takeposaux function.
takepos :: [Int]->[Int]->[Int]

takepos p x = 
    reverse(takeposaux p x []) 

--The recursive_addonpos function add an element n in the
--position p of a given list.
recursive_addonpos :: Int->Int->[Int]->[Int]

recursive_addonpos n 1 x =
    n:x

recursive_addonpos n p (x:xs) =
    x:recursive_addonpos n (p-1) xs

--The tailaux_addonpos function add an element n in the 
--position p of a given list.
tailaux_addonpos :: Int->Int->[Int]->[Int]->[Int]

tailaux_addonpos n 1 x r =
    reverse(r)++[n]++x

tailaux_addonpos n p (x:xs) r =
    tailaux_addonpos n (p-1) xs (x:r) 

--The tail_addonpos simplys calls the tailaux_addonpos function.
tail_addonpos :: Int->Int->[Int]->[Int]

tail_addonpos n p x = 
    tailaux_addonpos n p x []

--The recursive_rmonpos function removes an element n in the
--position p of a given list.
recursive_rmonpos :: Int->[Int]->[Int]

recursive_rmonpos n (x:xs) = 
    if(n == 1) then
        xs
    else 
        x:recursive_rmonpos (n-1) xs

--The tailaux_rmonpos function removes an element n in the
--position p of a given list.
tailaux_rmonpos :: Int->[Int]->[Int]->[Int]

tailaux_rmonpos 1 (x:xs) l =
    reverse(l)++xs

tailaux_rmonpos n (x:xs) l =
    tailaux_rmonpos (n-1) xs (x:l)

--The tail_rmonpos simply calls the tailaux_rmonpos function.
tail_rmonpos :: Int->[Int]->[Int]

tail_rmonpos n x = 
    tailaux_rmonpos n x []

--The recursive_min function returns the smallest element
--on a list l.
recursive_min :: [Int]->Int

recursive_min [x] = x

recursive_min (x:xs) = 
    if(x < b) then x
    else b
    where
        b = recursive_min xs

--The tailaux_min function returns the smallest element
--on a list l.
tailaux_min :: [Int]->Int->Int

tailaux_min [] b = b

tailaux_min (x:xs) b =
    if(x < b) then 
        tailaux_min xs x
    else
        tailaux_min xs b

--The tail_min function simply calls the tailaux_min function.
tail_min :: [Int]->Int

tail_min (x:xs) = 
    tailaux_min xs x 

--The recursive_max function returns the biggest element
--on a list l.
recursive_max :: [Int]->Int

recursive_max [x] = x

recursive_max (x:xs) = 
    if(x > b) then x
    else b
    where
        b = recursive_max xs

--The tailaux_max function returns the biggest element
--on a list l.
tailaux_max :: [Int]->Int->Int

tailaux_max [] b = b

tailaux_max (x:xs) b =
    if(x > b) then 
        tailaux_max xs x
    else
        tailaux_max xs b

--The tail_max function simply calls the tailaux_max function.
tail_max :: [Int]->Int

tail_max (x:xs) = 
    tailaux_max xs x 

--The average function returns the average of a list l.
average :: [Double]->Double

average [] = 0

average x = 
    (sum x)/fromIntegral (length x)

--The median function returns the median of a list l.
median :: [Int]->Int

median x =
    if(mod (length x) 2 == 1) then
        nth (div (length x) 2 + 1) x
    else
        div (nth (div (length x) 2) x + nth (div (length x) 2 + 1) x) 2

--The mode_aux function returns a list of modes of a list l.
mode_aux :: [Int]->Int->[Int]->[Int]

mode_aux [] _ l = l

mode_aux (x:xs) b l = 
    if(belongs_to x l) then 
        mode_aux xs b l
    else if(ocx == b) then
        mode_aux xs b (x:l)
    else if(ocx > b) then
        mode_aux xs ocx [x]
    else
        mode_aux xs b l    
    where 
        ocx = tail_occurrences x (x:xs)

--The mode function simply calls the mode_aux function.
mode :: [Int]->[Int]

mode x = 
    mode_aux x 2 []

--The palindrome function returns true if a list is a
--palindrome and false if it is not.
palindrome :: [Int]->Bool

palindrome [] = True

palindrome [_] = True

palindrome (x:xs) = 
    if(x == l) then 
        palindrome (take (length xs -1) xs)
    else 
        False
    where 
        l = last xs

--The recursive_addtoallaux_lists function adds n to the 
--ith positon in a list.
recursive_addtoallaux_lists :: Int->[[Int]]->Int->Int->[[Int]]

recursive_addtoallaux_lists n [] _ _ = []

recursive_addtoallaux_lists n (l:ls) c i =
    if(i > c+1) then
        recursive_addtoallaux_lists n ls c 1
    else
        (tail_addonpos n i l):(recursive_addtoallaux_lists n (l:ls) c (i+1))

--The recursive_addtoall_lists simply calls recursive_addtoallaux_lists
recursive_addtoall_lists :: Int->[[Int]]->[[Int]]

recursive_addtoall_lists n (x:xs) =
    recursive_addtoallaux_lists n (x:xs) (length x) 1

--The addtoall_tailaux_lists function adds n to the ith position
--in a all sublists of l.
addtoall_tailaux_lists :: Int->[[Int]]->Int->Int->[[Int]]->[[Int]]

addtoall_tailaux_lists n [] _ _ r = r

addtoall_tailaux_lists n (l:ls) c i r =
    if(i > c+1) then
        addtoall_tailaux_lists n ls c 1 r
    else
        addtoall_tailaux_lists n (l:ls) c (i+1) ((tail_addonpos n i l):r)

--The addtoall_tail_lists simply calls addtoall_tailaux_lists.
addtoall_tail_lists :: Int->[[Int]]->[[Int]]

addtoall_tail_lists n [] = [[n]]

addtoall_tail_lists n (l:ls) =
    addtoall_tailaux_lists n (l:ls) (length l) 1 []

--The recursive_permute function returns a list of permutations
--of a list x.
recursive_permute :: [Int]->[[Int]]

recursive_permute [] = []

recursive_permute (x:xs) =
    addtoall_tail_lists x (recursive_permute xs)

--The tailaux_permute function returns a list of permutations of
--of a given list.
tailaux_permute :: [Int]->[[Int]]->[[Int]]

tailaux_permute [] l = l

tailaux_permute (x:xs) l = 
    tailaux_permute xs (addtoall_tail_lists x l)

--The tail_permute simply calls tailaux_permute function.
tail_permute :: [Int]->[[Int]]

tail_permute l =
    tailaux_permute l []

--The quicksort_comp function returns a sorted list.
quicksort_comp :: [Int]->[Int]

quicksort_comp [] = []

quicksort_comp (x:xs) = 
    (quicksort_comp l) ++ (x:quicksort_comp b)
    where 
        l = [e | e<-xs, e <= x]
        b = [e | e<-xs, e > x]

--The getsubaux function is an auxiliary function for the
--getsublists function.
getsubaux :: [Int]->[Int]->[[Int]]->[[Int]]

getsubaux [] l s = s 

getsubaux (x:xs) l s =
    getsubaux xs (x:l) ((reverse(x:l)):s) 

--The getsublists function returns all sublists of a list.
getsublists :: [Int]->[[Int]]

getsublists [] = [[]]

getsublists (x:xs) = 
    getsubaux (x:xs) [] [] ++ getsublists xs

--The recursiveaux_divisors function returns a list of all
--the divisors of n.
recursiveaux_divisors :: Int->Int->Int->[Int]

recursiveaux_divisors n m c =
    if(m == c) then []
    else if(mod n c == 0) then
        [c]++recursiveaux_divisors n m (c+1)
    else
        recursiveaux_divisors n m (c+1) 

--The recursive_divisors simply calls recursionaux_divisors.
recursive_divisors :: Int->[Int]

recursive_divisors n =
    (recursiveaux_divisors n (div n 2 +1) 1) ++ [n]

--The tailaux_divisors function returns a list of all
--the divisors of n.
tailaux_divisors :: Int->Int->Int->[Int]

tailaux_divisors n m c =
    if(m == c) then []
    else if(mod n c == 0) then
        [c]++tailaux_divisors n m (c+1)
    else
        tailaux_divisors n m (c+1)

--The tail_divisors simply calls the tailaux_divisors function.
tail_divisors :: Int->[Int]

tail_divisors n = 
    (tailaux_divisors n (div n 2 + 1) 1)++[n]

--The divisors_comp function returns a list of all
--the divisors of n.
divisors_comp :: Int->[Int]

divisors_comp n = 
    [x | x<-[1..n], mod n x == 0]

--The recursiveaux_primes function returns a list with all
--the primes from 1 to n.
recursiveaux_primes :: Int->Int->[Int]

recursiveaux_primes n c =
    if(c > n) then []
    else if(length(tail_divisors c) == 2) then
        [c]++recursiveaux_primes n (c+1)
    else
        recursiveaux_primes n (c+1)

--The recursive_primes simply calls recursiveaux_primes.
recursive_primes :: Int->[Int]

recursive_primes n =
    recursiveaux_primes n 2

--The tailaux_primes function returns a list with all the primes
--from 1 to n.
tailaux_primes :: Int->Int->[Int]->[Int]

tailaux_primes n c l =
    if(c > n) then l
    else if(length(tail_divisors c) == 2) then
        tailaux_primes n (c+1) (l++[c])
    else
        tailaux_primes n (c+1) l

--The tail_primes simply calls the tailaux_primes function.
tail_primes :: Int->[Int]

tail_primes n =
    tailaux_primes n 2 []

--The primes_comp function returns a list with all the primes
--from 1 to n
primes_comp :: Int->[Int]

primes_comp n =
    [x | x<-[1..n], length(tail_divisors x) == 2]

--The recursive_insertsort function inserts an element in a 
--sorted list.
recursive_insertsort :: Int->[Int]->[Int]

recursive_insertsort n [] = [n]

recursive_insertsort n (x:xs) =
    if(n <= x) then
        [n]++(x:xs)
    else
        x:recursive_insertsort n xs

--The tailaux_insertsort function inserts an element in a 
--sorted list.
tailaux_insertsort :: Int->[Int]->[Int]->[Int]

tailaux_insertsort n [] l = 
    reverse(l)++[n]

tailaux_insertsort n (x:xs) l =
    if(n <= x) then
        reverse(l)++[n]++(x:xs)
    else
        tailaux_insertsort n xs (x:l)

--The tail_insertsort simply calls tailaux_insertsort.
tail_insertsort :: Int->[Int]->[Int]

tail_insertsort n x =
    tailaux_insertsort n x [] 

--The recsort_insert function sorts a list of integers.
recsort_insert :: [Int]->[Int]

recsort_insert [] = []

recsort_insert (x:xs) = 
    tail_insertsort x (recsort_insert xs)

--The tailauxsort_insert function sorts a list of integers.
tailauxsort_insert :: [Int]->[Int]->[Int]

tailauxsort_insert [] l = l

tailauxsort_insert (x:xs) l =
    tailauxsort_insert xs (tail_insertsort x l)

--The tailsort_insert simply calls tailauxsort_insert.
tailsort_insert :: [Int]->[Int]

tailsort_insert x =
    tailauxsort_insert x []

--The sort_tuples function sorts a list of tuples.
sort_tuples :: [(Int,Int)]->[(Int,Int)]

sort_tuples [] = []

sort_tuples [x] = [x]

sort_tuples ((lx,ly):ls) = 
    (sort_tuples t1)++(sort_tuples t3)++((lx,ly):t5)++(sort_tuples t4)++(sort_tuples t2)
    where 
        t1 = [(x,y) | (x,y)<-ls, x<lx]
        t2 = [(x,y) | (x,y)<-ls, x>lx]
        t3 = [(x,y) | (x,y)<-ls, x==lx, y<ly]
        t4 = [(x,y) | (x,y)<-ls, x==lx, y>ly]
        t5 = [(x,y) | (x,y)<-ls, x==lx, y==ly]