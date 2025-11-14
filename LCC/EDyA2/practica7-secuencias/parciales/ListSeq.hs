module ListSeq where

import GHC.Float
import Par
import Seq

instance Seq [] where
  emptyS = []

  singletonS x = [x]

  lengthS = length

  nthS s n = s !! n

  tabulateS f n = [f i | i <- [0 .. n - 1]]
  
  mapS _ [] = []
  mapS f (x : xs) =  x' : rest
    where
      (x',rest) = f x ||| mapS f xs 

  filterS = filter

  appendS = (++)

  takeS s n = take n s

  dropS s n = drop n s

  showtS s
    | lengthS s == 0 = EMPTY
    | lengthS s == 1 = ELT (nthS s 0)
    | otherwise =
        let m = div (lengthS s) 2
            (l', r') = takeS s m ||| dropS s m
         in NODE l' r'

  showlS s
    | lengthS s == 0 = NIL
    | otherwise =
        let (v, rest) = nthS s 0 ||| dropS s 1
         in CONS v rest

  joinS = reduceS appendS emptyS -- ToDo : revisar

  reduceS op e s
    | lengthS s == 0 = e
    | lengthS s == 1 = nthS s 0
    | otherwise =
        let m = div (lengthS s) 2
            (l', r') = takeS s m ||| dropS s m  
          in reduceS op e l' `op` reduceS op e r'

  scanS op e s 
    | lengthS s == 0 = (emptyS, e)
    | lengthS s == 1 = (singletonS (nthS s 0), nthS s 0)
    | otherwise =
        let m = div (lengthS s) 2
            (l', r') = takeS s m ||| dropS s m
            (l'', e') = scanS op e l'
            (r'', e'') = scanS op e' r'
         in (appendS l'' r'', e'')

  fromList = id

data Tree a = Leaf a | Node (Tree a) (Tree a)

toTree :: [a] -> Tree a
toTree s
  | lengthS s == 1 = Leaf (nthS s 0)
  | otherwise =
      let (l', r') = toTree (takeS s pp) ||| toTree (dropS s pp)
       in Node l' r'
  where
    pp = 2 ^ ilog2 (lengthS s - 1)

reduceT :: (a -> a -> a) -> Tree a -> a
reduceT op (Leaf x) = x
reduceT op (Node l r) = l' `op` r'
  where
    (l', r') = reduceT op l ||| reduceT op r

ilog2 :: Int -> Int
ilog2 n
  | n < 1 = error "ilog2 no definido para n < 1"
  | otherwise = go n 0
  where
    go 1 acumulador = acumulador
    go x acumulador = go (x `div` 2) (acumulador + 1)