data BTree a = Empty | Node Int (BTree a) a (BTree a) deriving Show

size :: BTree a -> Int
size Empty = 0
size (Node n _ _ _) = n

(|||) :: a -> b -> (a,b)
x ||| y = (x,y)


-- EJERCICIO 1

nth :: BTree a -> Int -> a
nth Empty _ = error "Index out of range"
nth (Node n l x r) i    | i == size l = x
                        | i < size l = nth l i
                        | i > size l = nth r (i - (size l + 1))

-- no es paralelizable, siempre tomamos una sola rama del arbol
-- El trabajo W_nth lo calculamos en función de la altura (no es recomendable en este caso poner como entrada el numero de nodos).
-- Y entonces W_nth(0) = c_2 y W_nth(h) = W_nth(h-1) + c_1 y entonces W_nth es O(h) (esto implica que si está balanceado entonces es O(log n))

-- El analisis de la profundidad es exactamente igual al trabajo, ya que no paralelizamos

-- Falta probar la recurrencia

cons :: a -> BTree a -> BTree a
cons x Empty = Node 1 Empty x Empty
cons x (Node n l y r) = Node (n+1) (cons x l) y r
-- no es paralelizable por lo que W_cons = S_cons

tabulate1 :: (Int -> a) -> Int -> BTree a
tabulate1 f 0 = Empty
tabulate1 f n = 
    let             
        m = div m 2
        ((l,r),x) = tabulate1 f m ||| tabulate1  (f.(+(m+1))) (n - m - 1) ||| f m -- No es tan eficiente porque se hace la composicion lgn veces
    in (Node n l x r)


tabulate2 f n = tabulate' f 0 (n-1)
  where
    tabulate' f n m
      | m < n = Empty
      | otherwise =
          let medio = div (m + n) 2
              (l,r) = tabulate' f n (medio - 1) ||| tabulate' f (medio + 1) m
              x = f medio
          in Node (m - n + 1) l x r

mapT :: (a -> b) -> BTree a -> BTree b
mapT f Empty = Empty
mapT f (Node n l x r) = let ((l', r'),x') = (mapT f l ||| mapT f r) ||| f x in Node n l' x' r'

-- Por qué si f no es constante no podemos analizar el trabajo solo considerando numero de nodos o altura? Porque si f se aplica sobre los
-- valores dentro del arbol (los de tipo a) y si vos probas el trabajo con nro de nodos o altura no son entradas de tipo a (sino mas generales)

-- Supongamos f es O(1)
-- W_mapT(h) = W_mapT(h-1) + W_mapT(h-1) + c_1 + c_2 y pasando en limpio W_mapT(h) = 2W_mapT(h-1) + c
-- W_mapT(0) = a

-- Luego la profundidad es S_mapT(h) = max{S_mapT(h-1), S_mapT(h-1), c_1} + c_2 que reduce a S_mapT(h) = S_mapT(h-1) + c_2

-- Hay que probar las recurrencias

takeS :: Int -> BTree a -> BTree a
takeS _ Empty = Empty
takeS n (Node m l x r)      | n == (size l + 1) = Node n l x Empty
                            | n <= size l = takeS n l
                            | n > size l = Node m l x (takeS (n - size l - 1) r)

-- Trabajo y profundidad iguales ya que no es paralelizable.

dropS :: Int -> BTree a -> BTree a
dropS _ Empty = Empty
dropS n (Node m l x r)      | n == (size l + 1) = r
                            | n <= size l = Node (m - n) (dropS n l) x r
                            | n > size l = dropS (n-size l - 1) r
{- EJERCICIO 2. El problema de calcular la maxima suma de una subsecuencia contigua de una secuencia dada s puede resolverse
con un algoritmo “Divide & Conquer” que en cada llamada recursiva calcule: la maxima suma de una subsecuencia
contigua de s, la maxima suma de un prefijo de s, la maxima suma de un sufijo de s y la suma de todos los elementos
de s. Dado el siguiente tipo de datos: -}

data Tree a = E | Leaf a | Join (Tree a) (Tree a) deriving Show

{-a) Defina una función mcss:: (Num a, Ord a) => Tree a -> a que calcule la máxima suma de una secuencia contigua de una secuencia dada,
en términos de mapreduce-}

mcss' :: (Num a, Ord a) => Tree a -> (a,a,a,a)
mcss' (Join l r) = let ((s1,suf1,pref1,larga1),(s2,suf2,pref2,larga2)) = (mcss' l) ||| (mcss' r) in
                    (max (max s1 s2) (suf1+pref2), max suf2 (larga2 + suf1), max pref1 (larga1 + pref2), larga1 + larga2)
mcss' (Leaf x) = (max 0 x, max 0 x, max 0 x, x)
mcss' E = (0,0,0,0)

mcss :: (Num a, Ord a) => Tree a -> a
mcss = (\(x,_,_,_)-> x).mcss'

-- version con mapreduce

combine :: (Num a, Ord a) => (a,a,a,a) -> (a,a,a,a) -> (a,a,a,a)
combine (s1, suf1, pref1, l1) (s2,suf2, pref2, l2) = (max s1 (max s2 (suf1 + pref2)), max suf2 (l2 + suf1),max pref1 (l1 + pref2), l1 + l2)

e :: (Num a, Ord a) => (a, a, a, a)
e = (0,0,0,0)

base :: (Num a, Ord a) => a -> (a, a, a, a)
base x = (max 0 x, max 0 x, max 0 x, x)

mcssR :: (Num a, Ord a) => Tree a -> a
mcssR = (\(x,_,_,_) -> x) . mapReduce base combine e

-- Falta ver prof y trabajo y probar la recurrencia
-- EJERCICIO 3

type Compra = Int
type Ventas = [Int]

sufijosAux :: Tree Int -> Tree Int -> Tree (Tree Int)
sufijosAux E _ = E
sufijosAux (Leaf x) acum = Leaf acum
sufijosAux (Join l r) acum = let (l',r') = sufijosAux l (sec r acum) ||| sufijosAux r acum in Join l' r'
                                                        where
                                                            sec r E = r
                                                            sec r acum = Join r acum


sufijos :: Tree Int -> Tree (Tree Int)
sufijos E = E
sufijos t = sufijosAux t E

-- let t = Join (Join (Leaf 10)(Leaf 15)) (Leaf 20)
-- respuesta: Join (Join (Leaf (Join (Leaf 15) (Leaf 20))) (Leaf (Leaf 20))) (Leaf E)

mapTrees :: (a -> b) -> Tree a -> Tree b
mapTrees _ E = E
mapTrees f (Leaf x) = Leaf (f x)
mapTrees f (Join l r) = let (l', r') = mapTrees f l ||| mapTrees f r in Join l' r'


conSufijosAux :: Tree Int -> Tree Int -> Tree(Int, Tree Int)
conSufijosAux E _ = E
conSufijosAux (Leaf x) acum = Leaf (x, acum)
conSufijosAux (Join l r) acum = let (l',r') = conSufijosAux l (sec r acum) ||| conSufijosAux r acum in Join l' r'
                                                        where
                                                            sec r E = r
                                                            sec r acum = Join r acum


reduceT :: (a->a->a) -> a -> Tree a -> a
reduceT _ e E = e
reduceT f e (Leaf x) = x
reduceT f e (Join l r) = let (l',r') = reduceT f e l ||| reduceT f e r in f l' r'

mapReduce :: (a->b) -> (b->b->b) -> b -> Tree a -> b
mapReduce f g e t = mr t
                where
                    mr E = e
                    mr (Leaf x) = f x
                    mr (Join l r) = let (l',r') = mr l ||| mr r in g l' r'

conSufijos :: Tree Int -> Tree (Int, Tree Int)
conSufijos E = E
conSufijos t = conSufijosAux t E

maxT :: Tree Int -> Int
maxT = reduceT max minBound

maxAll :: Tree (Tree Int) -> Int
maxAll = mapReduce maxT max minBound


mejorGanancia :: Tree Int -> Int
mejorGanancia t = mapReduce (\(x,t1) -> maxT (mapTrees (\y -> y - x) t1)) max minBound (conSufijos t)


-- EJERCICIO 4

data T a = Emp | N (T a) a (T a) deriving Show

altura :: T a -> Int
altura Emp = 0
altura (N l x r) = 1 + max (altura l) (altura r)

combinarDummy :: T a -> T a -> T a
combinarDummy Emp t2 = t2
combinarDummy (N l1 x r1) (N l2 y r2) = N (N (combinarDummy l1 l2) y r2) x r1

-- let tree1 = N (N (N Emp 1 Emp) 3 (N Emp 2 (N Emp 1 Emp))) 4 (N Emp 1 Emp)
-- let tree2 = N (N (N Emp 1 Emp) 2 Emp) 3 (N Emp 2 (N Emp 1 Emp))
-- N (N (N (N (N (N Emp 1 Emp) 1 Emp) 2 Emp) 3 (N Emp 2 (N Emp 1 Emp))) 3 (N Emp 2 (N Emp 1 Emp))) 4 (N Emp 1 Emp)
-- no cumple invariante de altura

combinar2 :: T a -> T a -> T a
combinar2 Emp t2 = t2
combinar2 t1 Emp = t1
combinar2 (N l1 x r1) t2@(N l2 y r2) = N (combinar2 l1 l2) x (combinar2 (N Emp y r2) r1)

-- let tree1 = N (N (N Emp 1 Emp) 3 (N Emp 2 (N Emp 1 Emp))) 4 (N Emp 1 Emp)
-- let tree2 = N (N (N Emp 1 Emp) 2 Emp) 3 (N Emp 2 (N Emp 1 Emp))
-- aca si cumple altura

--

combinar3 :: T a -> T a -> T a
combinar3 Emp t2 = t2
combinar3 t1 Emp = t1
combinar3 t1@(N l x r) t2 = N (combinar3 l r) x t2


filterT :: (a -> Bool) -> T a -> T a
filterT _ Emp = Emp 
filterT p (N l x r) =   let    
                                (l',r') = filterT p l ||| filterT p r
                                t = combinar3 l' r'
                        in if p x then combinar3 (N Emp x Emp) t else t

--Como combinar cumple la propiedad de la altura entonces altura(combinar3 (filter p l) (filter p r)) <= 1 + max{altura (filter p l),altura (filter p r)}
-- y por hipótesis inductiva <=1 + max{h-1, h-1} = 1 + h - 1 = h = altura (N l x r)


quickSort :: T Int -> T Int
quickSort Emp = Emp
quickSort t@(N l x r) = let (l',r') = filterT (<=x) resto ||| filterT (>x) resto in N (quickSort l') x (quickSort r')
                                    where
                                        resto = combinar3 l r
                                    

-- EJERCICIO 5
splitAtTree :: BTree a -> Int -> (BTree a, BTree a)
splitAtTree t i = takeS i t ||| dropS i t

