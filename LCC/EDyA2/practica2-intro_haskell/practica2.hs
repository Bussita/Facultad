-- EJERCICIO 1
test f x = f x == x + 2

test :: (Eq a, Num a) => (a -> a) -> a -> Bool

esMenor :: Ord a => a -> a -> Bool
esMenor y z = y < z

eq :: Eq a => a -> a -> Bool
eq a b = a == b

--showVal :: Show a => a -> String--

showVal x = "Valor:" ++ show x

-- EJERCICIO 2
-- (+5) :: Num a => a -> a -- 
-- (0 < ) :: Ord a, Num a => a -> Bool
-- ('a':) :: [Char] -> [Char] --
-- (++ '\n') :: [Char] -> [Char] --
-- filter :: (a -> Bool) -> [a] -> [a] --
-- map (++[1]) :: Num => a -> [a] -> [a] -- 

-- EJERCICIO 3

-- (Int -> Int) -> Int

f :: Int -> Int
f n = n + 3
mostrarResultadoen0 f = f 0

-- Int -> (Int -> Int)

--sumaCurrificada :: Int -> (Int -> Int)

sumaCurrificada x = (+x)

-- (Int -> Int) -> (Int -> Int)

identidad :: (Int -> Int) -> (Int -> Int)
identidad f = f

dosEquis :: (Int -> Int) -> (Int -> Int)
dosEquis f a = 2 * f a

-- Int -> Bool
esCero :: Int -> Bool
esCero n = n == 0

esPar :: Int -> Bool
esPar n = mod n 2 == 0

-- Bool -> (Bool -> Bool)

orCurrificado :: Bool -> (Bool -> Bool)
orCurrificado a = (a ||)

andCurrificado :: Bool -> (Bool -> Bool)
andCurrificado a = (a &&) 

-- (Int, Char) -> Bool
primeraEsCero :: (Int, Char) -> Bool
primeraEsCero (a,b) = a == 0

esA :: (Int, Char) -> Bool
esA (a,b) = b == 'A'

-- (Int, Int) -> Int
suma :: (Int, Int) -> Int

suma (x, y) = x + y

primera :: (Int, Int) -> Int
primera (x,y) = x

-- Int -> (Int, Int)

tc :: Int -> (Int, Int)

tc x = (0, x)

tuplaGraciosa :: Int -> (Int, Int)
tuplaGraciosa x = (2*x, x)

-- a -> Bool

siempreVerdad a = True

siempreFalse a = False

-- a -> a

loMismo a = a

-- Pensar

-- EJERCICIO 4

falso =if true then false else true where 
                                true = False
                                false = True
              
x = if fst p then fst p else snd p where p = (True, False)

-- EJERCICIO 5
--a)
func :: p -> p
func x = x
--b)
greater :: Ord a => (a,a)-> Bool
greater (x,y)
            | x > y = True
            | otherwise = False

--c)

funC :: Num a => (a,a) -> a
funC (x,y) = x

-- EJERCICIO 6
-- smallest: \x y z -> if (x <= y && x <= z) then x else if (y <= x && y <= z) then y else z
    
second x = \x -> x -- \y -> \y -> y

andThen True y = y
andThen False y = False
at = \x y -> if x then y else x

twice f x = f (f x)

tw = (\f x-> f (f x)) (+1) 3

flip f x y = f y x
fl = \f x y -> f y x

inc = (+1)
increme = \x -> x + 1

-- EJERCICIO 7
iff :: Bool -> Bool -> Bool
iff x y
        | x = not y
        | otherwise = y

alpha :: a -> a
alpha a = a

-- EJERCICIO 8
{-
fa :: Bool -> Char
fa _ = 'a'

ga :: Int -> Int -> Bool
ga n m = True
-}
{-
h = fa.ga
Aqui h x y evalua de manera (fa.ga) x y = (fa (ga x)) y = fa (ga x) y lo cual nos da un error de tipo,
ya que ga x :: Int->Bool y fa espera un Bool
-}

{-
h x = f. (g x) Aqui h = fa (ga x) por lo que h x y = (fa.(ga x)) y = fa.(ga x y) = h x y
-}

{-
h x y = (f.g) x y = (f (g x)) y = f (g x) y != h
-}

-- (.) :: (b->c) -> (a->b) -> (a->c)

-- EJERCICIO 9
zip3mia :: [a] -> [b] -> [c] -> [(a,b,c)]
zip3mia [] _ _ = []
zip3mia _ [] _ = []
zip3mia _ _ [] = []
zip3mia (x:xs) (y:ys) (z:zs) = (x,y,z) : zip3mia xs ys zs

desentuplo ((a,b),c) = (a,b,c)
zip3_2 :: [a] -> [b] -> [c] -> [(a,b,c)]
zip3_2 xs ys zs = map desentuplo (zip (zip xs ys) zs)

-- EJERCICIO 10
-- [[]] ++ xs = xs no tiene sentido, concatenar [[a]] con [a]
-- [[]] ++ xs = [xs]
-- MALISIMO

-- EJERCICIO 11
-- sqrt :: Float -> Float
modulus :: [Float] -> Float
modulus = sqrt.sum.map(^2)

vmod :: [[Float]] -> [Float]
vmod [] = []
vmod (v:vs) = modulus v : vmod vs

--EJERCICIO 12

type NumBin = [Bool]

-- a)
sumaBin :: NumBin -> NumBin -> NumBin
sumaBin [] ys = ys
sumaBin xs [] = xs
sumaBin  (b1:xs) (b2:ys)
                        | b1 == True && b2 == True = False : []
--EJERCICIO 13

divisors :: Integral a => a -> [a]
divisors x = [m | m<-[0..x], mod x m == 0]

matches :: Integral a => a -> [a] -> [a]
matches x xs = [m | m<-xs, m == x]

cuadrupla :: Integral n => n -> [(n,n,n,n)]
cuadrupla n = [(a,b,c,d) | a<-[0..n], b<-[0..n], c<-[0..n], d<-[0..n], a*a + b*b == c*c + d*d]

-- unique :: 

factorial 0 = 1
factorial n = n * factorial (n - 1)