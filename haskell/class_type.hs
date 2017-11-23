--Defining types and instances of classes including various ADTs.
--By: Abrothguer

--Defining type FullName and a function to compare names.

data FirstName = FName String deriving(Show,Eq,Ord)
data LastName = LName String deriving(Show,Eq,Ord)
type FullName = (FirstName, LastName)

compare_name :: FullName->FullName->Bool

compare_name (FName f1, LName l1) (FName f2, LName l2) = 
    if(f1==f2 && l1==l2) then True
    else False

--Defines the type expression and a function to evaluate.

data Exp a = Val a
           | Neg (Exp a)
           | Add (Exp a) (Exp a)
           | Sub (Exp a) (Exp a)
           | Mul (Exp a) (Exp a)
           | Div (Exp a) (Exp a) 

evaluate :: Fractional a=>Exp a->a

evaluate (Val a) = a
evaluate (Neg exp) = -(evaluate exp)
evaluate (Add e1 e2) = (evaluate e1) + (evaluate e2)
evaluate (Sub e1 e2) = (evaluate e1) - (evaluate e2)
evaluate (Mul e1 e2) = (evaluate e1) * (evaluate e2)
evaluate (Div e1 e2) = (evaluate e1) / (evaluate e2)

--Defines a type Geographic Coordanates made by Latitude and Longitude.

data GeoCoord = Latitude Int Int Int | Longitude Int Int Int deriving(Eq)

instance Show GeoCoord where 
    show (Latitude  a b c) = 
        "Latitude  = " ++ show a ++ "º " ++ show b ++ "' " ++ show c ++ "\"" 
    show (Longitude a b c) = 
        "Longitude = " ++ show a ++ "º " ++ show b ++ "' " ++ show c ++ "\""

type LocalPosition = (String, GeoCoord, GeoCoord)
type Cities = [LocalPosition]

--Determines if a city it's to the north of another.

north_from :: LocalPosition->LocalPosition->Bool

north_from (_, Latitude a1 b1 c1, _) (_, Latitude a2 b2 c2, _) = 
    if(a1 > a2) then True
    else if(a1 == a2 && b1 > b2) then True 
    else if(a1 == a2 && b1 == b2 && c1 > c2) then True
    else False

--Defines a list of cities and it's coordenates.

lcities::Cities
lcities =
    [("Rio Branco", Latitude 09 58 29, Longitude 67 48 36),
    ("Brasilia", Latitude (-15) 46 47, Longitude 47 55 47),
    ("Torres", Latitude (-29) 20 07, Longitude 49 43 37),
    ("Joao Pessoa", Latitude (-07) 06 54, Longitude 34 51 47),
    ("Uberlandia", Latitude (-18) 55 07, Longitude 48 16 38)]

--Returns the number of cities south of the equator.

south_equator :: Cities->Int
south_equator [] = 0
south_equator ((_,Latitude a _ _, _):xs) = 
    if(a < 0) then 1+south_equator xs
    else south_equator xs

--Function to add pairs only if the first is smaller than the second.

add_pairs :: [(Int,Int)]->[Int]

add_pairs x = 
    [m+n | (m,n) <- x, m<n]

add_pairs_lambda = 
    \x -> [m+n | (m,n) <- x, m<n]

--Defines a enum of the days of week, and seasons of year.

data Day = Sun | Mon | Tue | Wed | Thu | Fri | Sat deriving(Eq,Show)
data Season = Summer | Spring | Winter | Autumn deriving(Eq,Show)

weekend :: Day->Bool
weekend Sun = True
weekend Sat = True
weekend _   = False

climate :: Season->String
climate s = 
    if(s == Summer) then "hot"
    else if(s == Winter) then "cold"
    else "moderate"

--Defines a person.

data Person = Per {fstname :: String, lstname :: String, borndate :: String} deriving(Show)

--Implementation of a list type.

data List a = Null | Lt a (List a)

instance (Show a) => Show (List a) where
    show (Null) = "NULL"
    show (Lt d l) = show d ++ "-> " ++ show l

instance (Eq a) => Eq (List a) where
    Null == Null = True
    (Lt d1 l1) == (Lt d2 l2) = d1==d2 && l1==l2
    _ == _ = False
    
--Implementation of binary tree.

data BinTree a = Empty | Tree (BinTree a) a (BinTree a) 

instance (Show a) => Show (BinTree a) where
    show (Empty) = "<>"
    show (Tree l d r) = "<"++ show d ++ show l ++ show r ++ ">" 

instance (Eq a) => Eq (BinTree a) where
    Empty == Empty = True
    (Tree l1 d1 r1) == (Tree l2 d2 r2) = d1==d2 && l1==l2 && r1==r2
    _ == _ = False

--Makes a tree with the given values;
make_tree :: Ord a => a -> BinTree a

make_tree x = 
    Tree Empty x Empty

--Inserts a new node on a given tree.
insert_node :: Ord a => BinTree a -> BinTree a -> BinTree a

insert_node (Tree l d r) (Empty) = 
    (Tree l d r)

insert_node (Tree l d r) (Tree lr dr rr) = 
    if(d < dr) then (Tree (insert_node (Tree l d r) lr) dr rr)
    else (Tree lr dr (insert_node (Tree l d r) rr))

--Finds the height of a tree.
height :: Ord a => BinTree a -> Int

height Empty = 0

height (Tree l d r) = 
    1 + max (height l) (height r)

--Removes an element from a tree.
find_max_right :: Ord a => BinTree a -> a

find_max_right (Tree _ d r) = 
    if(r == Empty) then d
    else find_max_right r

remove_node :: Ord a => BinTree a -> a -> BinTree a

remove_node Empty x = Empty

remove_node (Tree l d r) x = 
    if(x > d) then (Tree l d (remove_node r x))
    else if(x < d) then (Tree (remove_node l x) d r)
    else if(x == d && l == Empty) then r
    else if(x == d && r == Empty) then l
    else (Tree (remove_node l mr) mr r)
    where
        mr = find_max_right l
    
--Searches for an element on a tree.
search_node :: Ord a => BinTree a -> a -> Bool 

search_node Empty x = False

search_node (Tree l d r) x= 
    if(d == x) then True
    else if(search_node l x == True) then True
    else search_node r x

--Implementation of a queue.
data Queue a = EmptyQueue | Qu a (Queue a)

instance (Show a) => Show (Queue a) where
    show (EmptyQueue) = "last..."
    show (Qu d q) = show d ++ " " ++ show q
    
instance (Eq a) => Eq (Queue a) where
    EmptyQueue == EmptyQueue = True
    (Qu d1 q1) == (Qu d2 q2) = d1==d2 && q1==q2
    _ == _ = False

--Makes an queue.
make_queue :: Ord a => a -> Queue a

make_queue x = 
    Qu x EmptyQueue

--Enqueue an element.
enqueue :: Ord a => Queue a -> a -> Queue a

enqueue EmptyQueue x = 
    Qu x EmptyQueue

enqueue (Qu d q) x =
    Qu d (enqueue q x)

--Dequeue an element.
dequeue :: Ord a => Queue a -> Queue a

dequeue EmptyQueue = EmptyQueue

dequeue (Qu d q) = q

--Returns the front element.
front :: Ord a => Queue a -> a

front (Qu d q) = d

--Implementation of a Stack.
data Stack a = EmptyStk | Stk a (Stack a)

instance (Show a) => Show (Stack a) where
    show (EmptyStk) = ""
    show (Stk d s) = show d ++ "\n" ++ show s
    
instance (Eq a) => Eq (Stack a) where
    EmptyStk == EmptyStk = True
    (Stk d1 s1) == (Stk d2 s2) = d1==d2 && s1==s2
    _ == _ = False

--Makes a stack.
make_stack :: Ord a => a -> Stack a

make_stack x = 
    Stk x EmptyStk

--Push an element in the stack
push :: Ord a => Stack a -> a -> Stack a

push s n = 
    Stk n s

--Pop an element in the stack
pop :: Ord a => Stack a -> Stack a

pop EmptyStk = EmptyStk

pop (Stk d s) = s

--Returns the top value of a stack
top :: Ord a => Stack a -> a

top (Stk d s) = d

--Implementation of Adjacency List and Graph structure

data AdjList a = EL | Adj (a,a) (AdjList a)

instance (Show a) => Show (AdjList a) where
    show (EL) = "Null"
    show (Adj p l) = show p ++ "-> " ++ show l

instance (Eq a) => Eq (AdjList a) where
    EL == EL = True 
    (Adj p1 l1) == (Adj p2 l2) = (p1==p2 && l1==l2)

data Graph a = EG | Grp a (AdjList a) (Graph a) deriving(Eq)

instance (Show a) => Show (Graph a) where
    show(EG) = "End"
    show(Grp d l g) = show d ++ " = " ++ show l ++ "\n" ++ show g

--Makes an empty graph.

make_graph :: Ord a => Graph a
make_graph = EG

--Insert a node on a graph.

insert_gnode :: Ord a => Graph a -> a -> Graph a

insert_gnode EG d = 
    Grp d EL EG

insert_gnode (Grp d l g) n = 
    if(d == n) then (Grp d l g)
    else Grp d l (insert_gnode g n)

--Inserts an edge on the graph.

insert_edge :: Ord a => Graph a -> a -> a -> a -> Graph a

insert_edge EG _ _ _ = EG

insert_edge (Grp d l g) v1 v2 w = 
    if(d == v1) then Grp d (Adj (v2,w) l) g
    else Grp d l (insert_edge g v1 v2 w)
