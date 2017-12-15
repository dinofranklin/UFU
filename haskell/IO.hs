--Using files and IO
--By.: Abrothguer

import System.IO(stdout, hSetBuffering, BufferMode(NoBuffering))

--Scans a string and checks if it is a palindrome.

palindrome :: Eq a => [a]->Bool
palindrome x = 
    if(x == reverse x) then True
    else False

check_palindrome :: IO()
check_palindrome = 
    do putStrLn "Digite uma frase para verificar se a mesma eh palindromo: "
       s <- getLine
       if(palindrome s) then putStrLn "Eh Palindromo"
       else putStrLn "Nao eh Palindromo"


--Scans a list.
scan_list :: IO [Int]
scan_list = 
    do hSetBuffering stdout NoBuffering
       s <- readLn
       if (s == 0) then return []
       else do t <- scan_list
               return (s:t)

--Prints a list.
print_list :: Show a => [a] -> IO ()
print_list x = 
    if(null x) then 
        do putStrLn ""
           return ()
    else
        do putStr ((show (head x))++" ")
           print_list (tail x)


--Sums a given list.
sum_list :: IO Int
sum_list =
    do hSetBuffering stdout NoBuffering
       s <- readLn
       if (s == 0) then return 0
       else do a <- sum_list
               return (s+a)

--Calculates the average. 
avg = 
    do hSetBuffering stdout NoBuffering
       s <- readLn
       if(s < 0) then return (0,0)
       else do a <- avg
               return (fst a + s, snd a + 1)