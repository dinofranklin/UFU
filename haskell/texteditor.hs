--A simple text editor using Haskell
--By: Abrothguer

--Definition of types and globals used in the program.

type MyWord = String
type Line = [MyWord]

spaces_characters :: [Char]
spaces_characters = ['\n','\t',' ']

lineSize :: Int
lineSize = 30

--The belongs function returns true if a character c
--belongs to a string and false if does not.
belongs :: Char->[Char]->Bool
belongs c [] = False
belongs c (x:xs) = 
    if(c == x) then True
    else belongs c xs

--The getWord function returns the first word of a 
--string.

getWord :: String->String
getWord [] = []
getWord (x:xs) = 
    if(belongs x spaces_characters == True) then []
    else x:getWord xs

--The removeWord function returns a strings without
--its first word.

removeWord :: String->String
removeWord [] = []
removeWord (x:xs) =
    if(belongs x spaces_characters == True) then xs
    else removeWord xs

--The removeSpaces function returns removes all space
--character from the beggining of a string.

removeSpaces :: String->String
removeSpaces [] = []
removeSpaces (x:xs) =
    if(belongs x spaces_characters == True) then removeSpaces xs
    else (x:xs)

--The getAllWords function returns all words in a string.

getAllWords :: String->[MyWord]
getAllWords [] = []
getAllWords x =
    if(ft == []) then getAllWords(removeSpaces(removeWord x))
    else ft:(getAllWords(removeSpaces(removeWord x)))
    where
        ft = getWord x

--The getLines function takes a list of words and returns
--a line. 

getLines :: Int->[MyWord]->Line
getLines _ [] = []
getLines n (x:xs) = 
    if(length x > n) then []
    else x: getLines (n - length x -1) xs

--The removeLines function takes a list of words and
--returns it without its first line.

removeLines :: Int->[MyWord]->[MyWord]
removeLines _ [] = []
removeLines n (x:xs) = 
    if(length x > n) then (x:xs)
    else removeLines (n - length x -1) xs

--The getAllLines takes a list of words and returns all
--the lines from it.

getAllLines :: [MyWord]->[Line]
getAllLines [] = []
getAllLines x = 
    (getLines lineSize x):(getAllLines (removeLines lineSize x))

--The generateLines takes a string and returns lines
--from it.

generateLines :: String->[Line]
generateLines [] = []
generateLines x = 
    getAllLines (getAllWords x)

--the lineToString fucntion takes a line and returns
--a string.

lineToString :: Line->String
lineToString [] = "\n"
lineToString (x:xs) =
    if(rst == "\n") then x++rst
    else x++" "++rst
    where
        rst = lineToString xs

--The joinLines function takes a list of lines and
--puts them togheter in a string, formating it.

joinLines :: [Line]->String
joinLines [] = []
joinLines (x:xs) = 
    (lineToString (justify x))++joinLines xs

--The lineLength fucntion returns the legth of a line.

lineLength :: Line->Int
lineLength [] = 0
lineLength [x] = length x;
lineLength (x:xs) =
    1+(length x) + (lineLength xs) 

--The insertSpaces function inserts a space at the end
--of a given word.

insertSpaces :: MyWord->MyWord
insertSpaces [] = []
insertSpaces x = x++" "

--The justifyAux function insert spaces in a line.

justifyAux :: Int->Line->Line
justifyAux _ [] = []
justifyAux _ [x] = [x]
justifyAux n (x:xs) = 
    if(n == lineSize) then (x:xs)
    else (insertSpaces x):(justifyAux (n+1) xs)

--The justify function calls justifyAux until the
--line is jutified.

justify :: Line->Line
justify [] = []
justify x =
    if(lineLength j == lineSize) then j
    else justify j
    where
        j = justifyAux (lineLength x) x

--Function used to execute the code.

execute :: String->IO()
execute [] = putStr []
execute x =
    putStr (joinLines(generateLines x))