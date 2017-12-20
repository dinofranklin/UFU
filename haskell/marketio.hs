module Main(main) where

import System.IO


type Nome = String
type Preco = Int
type CodBar = Int
type Receipt = [(Nome,Preco)]
type BaseDeDados = [(CodBar,Nome,Preco)]
type CodList = [CodBar]


main = do putStrLn "Lendo dados do arquivo dados.dat\n\n"
          dados <- readListFile "dados.dat"
          codes <- readProducts
          putStrLn "\n\nSeu recibo foi salvo no arquivo recibo.dat\n\n"
          writeFile "recibo.dat" (execute codes dados)
          putStrLn "Done!"


readListFile :: String -> IO BaseDeDados

readListFile fname = do contents <- readFile fname
                        return (read contents)

readProducts :: IO CodList

readProducts = do putStr "Digite o codigo de barras de um produto (0 para terminar): "
                  x <- readLn
                  if x == 0
                    then return []
                    else do 
                        r <- readProducts
                        return (x:r)




lineSize :: Int
lineSize = 30

searchList :: CodBar->BaseDeDados->(Nome,Preco)
searchList cod ((x,y,z):xs) = 
    if(cod == x) then (y,z)
    else searchList cod xs


takeTuple :: BaseDeDados->CodBar->(Nome,Preco)
takeTuple l cod = 
    searchList cod l


makeReceipt :: CodList->BaseDeDados->Receipt
makeReceipt x l = 
    map (takeTuple l) x


generateDots :: Int->String
generateDots 0 = ""
generateDots n = 
    '.':generateDots (n-1)


formatCents :: (Nome,Preco)->(Nome,String)
formatCents (x,y) = 
    if(length aux > 1) then (x,"$"++show(div y 100) ++ "." ++aux)
    else (x,"$"++show(div y 100) ++ "." ++ "0"++ show(mod y 100))
    where
        aux = show(mod y 100)


formatLine :: (Nome,String)->String
formatLine (x,y) = 
    x++spc++y++"\n"
    where
        spc = generateDots (lineSize - t)
        t = length x + length y

generateAllLines :: Receipt->String
generateAllLines x = 
    foldr1 (++) (map formatLine (map formatCents x))


searchPrice :: CodBar->BaseDeDados->Preco
searchPrice cd ((x,y,z):xs) = 
    if(cd == x) then z
    else searchPrice cd xs


takePrice :: BaseDeDados->CodBar->Preco
takePrice l cd = 
    searchPrice cd l


generateTotal :: CodList->BaseDeDados->String
generateTotal x l =
    s2++(generateDots (lineSize - t))++s1++"\n"
    where
        s2 = "Total:"
        s1 = "$"++show(div tot 100)++"."++show(mod tot 100)
        t = length s2 + length s1
        tot = sum (map (takePrice l) x)

        
makeString :: CodList->BaseDeDados->String
makeString cd l = 
    generateAllLines (makeReceipt cd l)


execute :: CodList->BaseDeDados->String
execute cd l = 
    s1 ++ generateTotal cd l ++ "\n"
    where  
        s1 = s ++ makeString cd l
        s = "\nSeu Recibo:                 \n"