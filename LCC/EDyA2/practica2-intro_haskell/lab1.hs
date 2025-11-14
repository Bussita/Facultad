module Lab01 where

import Data.List
import Distribution.Simple.Utils (xargs)
import Data.Char (isAlpha)
{-
{-
1) Corregir los siguientes programas de modo que sean aceptados por GHCi.
-}

-- a)
not b = case b of
      True -> False
      False -> True

-- b)
eliminar [x]         =  []
eliminar (x:xs)      =  x : eliminar xs
eliminar []          =  error "empty list"

-- c)
long []        =  0
long (_:l)     =  1 + long l

-- d)
list123 = 1 :( 2 : (3 : []))

-- e)
[]     ++! ys = ys
(x:xs) ++! ys = x : xs ++! ys

-- f)
map toma f: a->b y lista de a y te devuelve lista de b

addToTail x xs = map +x (tail xs)

-- g)
listmin xs = head . sort xs

-- h) (*)
smap f [] = []
smap f [x] = [f x]
smap f (x:xs) = f x : smap (smap f) xs

{-
-}
2. Definir las siguientes funciones y determinar su tipo:

a) five, que dado cualquier valor, devuelve 5

-}
five :: Num a => b -> a
five b = 5


{-
b) apply, que toma una función y un valor, y devuelve el resultado de
aplicar la función al valor dado
-}

apply :: (a->b) -> a -> b
apply f x = f x

{-
c) ident, la función identidad
-}
ident :: a -> a
ident a = a
{-
d) first, que toma un par ordenado, y devuelve su primera componente
-}
first :: (a,b) -> a
first (a,b) = a
{-
e) derive, qfilterue aproxima la derivada de una función dada en un punto dado
-}

{-
f) sign, la función signo
-}
sign :: (Num a, Ord a) => a -> a
sign n
      | n > 0 = 1
      | n == 0 = 0
      | otherwise = -1
{-
g) vabs, la función valor absoluto (usando sign y sin usarla)
-}
vabs1 :: (Num a, Ord a) => a -> a
vabs1 n
        | sign n >= 0 = n
        | otherwise = -n
{-
h) pot, que toma un entero y un número, y devuelve el resultado de
elevar el segundo a la potencia dada por el primero
-}
pot :: Fractional t => Int -> t -> t
pot 0 x = 1
pot a x
    | a < 0 = 1 / pot (-a) x
    | otherwise = x * pot (a-1) x

{-
i) xor, el operador de disyunción exclusiva
-}

xor :: Bool -> Bool -> Bool
xor True False = True
xor False True = True
xor _ _ = False
{-
j) max3, que toma tres números enteros y devuelve el máximo entre llos
-}
max3 :: (Int, Int, Int) -> Int
max3 (a,b,c)
          | a >= b && a >= c = a
          | b >= a && b >= c = b
          | c >= a && c >= b = c 
{-
k) swap, que toma un par y devuelve el par con sus componentes invertidas
-}

swap :: (a, b) -> (b, a)
swap (a, b) = (b, a) 
{- 
3) Definir una función que determine si un año es bisiesto o no, de
acuerdo a la siguiente definición:

año bisiesto 1. m. El que tiene un día más que el año común, añadido al mes de febrero. Se repite
cada cuatro años, a excepción del último de cada siglo cuyo número de centenas no sea múltiplo
de cuatro. (Diccionario de la Real Academia Espaola, 22ª ed.)

¿Cuál es el tipo de la función definida?
-}

bisiesto :: Integral a => a -> Bool
bisiesto n = mod n 4 == 0 && (mod n 100 /= 0 || mod n 400 == 0) 
{-
4)

Defina un operador infijo *$ que implemente la multiplicación de un
vector por un escalar. Representaremos a los vectores mediante listas
de Haskell. Así, dada una lista ns y un número n, el valor ns *$ n
debe ser igual a la lista ns con todos sus elementos multiplicados por
n. Por ejemplo,

[ 2, 3 ] *$ 5 == [ 10 , 15 ].

El operador *$ debe definirse de manera que la siguiente
expresión sea válida:

-}
(*$) :: Num t => [t] -> t -> [t]
[] *$ n = []
(x:xs) *$ n = (x*n) : xs *$ n
v = [1, 2, 3] *$ 2 *$ 4


{-
5) Definir las siguientes funciones usando listas por comprensión:

a) 'divisors', que dado un entero positivo 'x' devuelve la
lista de los divisores de 'x' (o la lista vacía si el entero no es positivo)
-}
divisors :: Integral n => n -> [n]
divisors n
            | n < 0 = []
            | n == 0 = [1..]
            | n > 0 = [x | x<-[1..n], mod n x == 0] 
{-
b) 'matches', que dados un entero 'x' y una lista de enteros descarta
de la lista los elementos distintos a 'x'
-}
matches :: Integral t => t -> [t] -> [t]
matches n = filter(== n)

{-
c) 'cuadrupla', que dado un entero 'n', devuelve todas las cuadruplas
'(a,b,c,d)' que satisfacen a^2 + b^2 = c^2 + d^2,
donde 0 <= a, b, c, d <= 'n'
-}

cuadrupla :: Integral n => n -> [(n,n,n,n)]
cuadrupla n = [(a,b,c,d) | a<-[0..n], b<-[0..n], c<-[0..n], d<-[0..n], a*a + b*b == c*c + d*d]

{-
(d) 'unique', que dada una lista 'xs' de enteros, devuelve la lista
'xs' sin elementos repetidos
-}


unique :: [Int] -> [Int]
unique xs = [x | (x,i) <- zip xs [0..], not (elem x (take i xs))]


{- 
6) El producto escalar de dos listas de enteros de igual longitud
es la suma de los productos de los elementos sucesivos (misma
posición) de ambas listas.  Definir una función 'scalarProduct' que
devuelva el producto escalar de dos listas.

Sugerencia: Usar las funciones 'zip' y 'sum'. -}

scalarProduct :: Num t => [t] -> [t] -> t
scalarProduct [] [] = 0
scalarProduct _ [] = 0
scalarProduct [] _ = 0
scalarProduct (x:xs) (y:ys) = x*y + scalarProduct xs ys

-- TRATAR DE HACER CON ZIP Y SUM--
{-
7) Definir mediante recursión explícita
las siguientes funciones y escribir su tipo más general:

a) 'suma', que suma todos los elementos de una lista de números
-}

suma :: Num t => [t] -> t
suma [] = 0
suma (x:xs) = x + suma xs

{-
b) 'alguno', que devuelve True si algún elemento de una
lista de valores booleanos es True, y False en caso
contrario
-}

alguno :: [Bool] -> Bool
alguno [] = False
alguno (x : xs) = x || alguno xs
{-
c) 'todos', que devuelve True si todos los elementos de
una lista de valores booleanos son True, y False en caso
contrario
-}
todos :: [Bool] -> Bool
todos [] = True
todos (x:xs) = x && todos xs
{-
d) 'codes', que dada una lista de caracteres, devuelve la
lista de sus ordinales
-}

{-
e) 'restos', que calcula la lista de los restos de la
división de los elementos de una lista de números dada por otro
número dado
-}
restos :: Integral t => [t] -> t -> [t]
restos xs n = map (\x -> mod x n) xs 
{-
f) 'cuadrados', que dada una lista de números, devuelva la
lista de sus cuadrados
-}
cuadrados :: Num t => [t] -> [t]
cuadrados xs = [x*x | x<-xs]
{-
g) 'longitudes', que dada una lista de listas, devuelve la
lista de sus longitudes
-}
longitudes :: [[t]] -> [Int]
longitudes = map length
{-
h) 'orden', que dada una lista de pares de números, devuelve
la lista de aquellos pares en los que la primera componente es
menor que el triple de la segunda
-}
orden :: (Ord a, Num a) => [(a,a)] -> [(a,a)]
orden xs= [(x,y) | (x,y)<-xs, x <= (3 * y)]
{-
i) 'pares', que dada una lista de enteros, devuelve la lista
de los elementos pares
-}
pares :: Integral t => [t] -> [t]
pares = filter(\x -> mod x 2 == 0)

{-
j) 'letras', que dada una lista de caracteres, devuelve la
lista de aquellos que son letras (minúsculas o mayúsculas)
-}
letras :: [Char] -> [Char]
letras = filter isAlpha
{-
k) 'masDe', que dada una lista de listas 'xss' y un
número 'n', devuelve la lista de aquellas listas de 'xss'
con longitud mayor que 'n' -}
masDe :: Int -> [[t]] -> [[t]]
masDe n = filter(\xs -> length xs >= n)

