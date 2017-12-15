--Simple functions using monads and lambda calculus.
--By.: Abrothguer


--Expression data type
data Exp = Cte Int 
         | Add Exp Exp
         | Sub Exp Exp
         | Mul Exp Exp
         | Div Exp Exp
         deriving(Show, Read)


--Used to evaluate expression using monads.
evaluate :: Exp -> Maybe Int

evaluate (Cte x) = Just x

evaluate (Add a b) = 
    evaluate a >>= \x ->
    evaluate b >>= \y ->
    Just (x+y)

evaluate (Sub a b) = 
    evaluate a >>= \x ->
    evaluate b >>= \y ->
    Just (x-y)

evaluate (Mul a b) =
    evaluate a >>= \x ->
    evaluate b >>= \y ->
    Just (x*y)

evaluate (Div a b) = 
    case evaluate a of
        Nothing -> Nothing
        Just x -> case evaluate b of
            Nothing -> Nothing
            Just y -> divide x y


divide :: Int -> Int -> Maybe Int

divide x y = 
    if(y == 0) then Nothing
    else Just (div x y)

--Used to evaluate expression using do blocks.
evaluate_do (Cte x) = Just x

evaluate_do (Div a b) = 
    do x <- evaluate_do a
       y <- evaluate_do b
       if(y == 0) then Nothing
       else Just (div x y)


--Lambda calculus.

twotimes :: (a->a)->a->a

twotimes f x =
    f (f x)

mymap :: (a->b)->[a]->[b]

mymap f [] = []
mymap f (x:xs) = 
    (f x) : (mymap f xs)

inter :: a->[a]->[[a]]

inter x [] = [[x]]

inter x (l:ls) = 
    [x:l:ls]++ map (l:) (inter x ls)
