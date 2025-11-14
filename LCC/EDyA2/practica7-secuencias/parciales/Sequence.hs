module Sequence where

import Data.List
import Data.Ord

type Seq a = [a]

(|||) :: a -> b -> (a, b)
u ||| v = (u, v)

emptyS :: Seq a
emptyS = []

isEmptyS :: Seq a -> Bool
isEmptyS s = lengthS s == 0

singletonS :: a -> Seq a
singletonS x = [x]

lengthS :: Seq a -> Int
lengthS = length

nthS :: Int -> Seq a -> a
nthS n s = s !! n

lastS :: Seq a -> a
lastS s = nthS ((lengthS s) - 1) s

firstS :: Seq a -> a
firstS s = nthS 0 s

data TreeView a = EMPTY | LEAF a |NODE (Seq a) (Seq a)

showtS :: Seq a -> TreeView a
showtS []  = EMPTY
showtS [x] = LEAF x
showtS s   = let
                n = div (lengthS s) 2
             in
                NODE (takeS n s) (dropS n s)

takeS :: Int -> Seq a -> Seq a
takeS = take

dropS :: Int -> Seq a -> Seq a
dropS = drop


appendS :: Seq a -> Seq a -> Seq a
appendS s1 s2 = s1 ++ s2

tabulateS :: (Int -> a) -> Int -> Seq a
tabulateS f n = map f [0..n-1]

mapS :: (a -> b) -> Seq a -> Seq b
mapS = map

filterS :: (a -> Bool) -> Seq a -> Seq a
filterS = filter

reduceSAux :: (a -> a -> a) -> a -> Seq a -> a
reduceSAux op b s  = case showtS s of 
                      LEAF x -> x
                      NODE l r -> op (reduceSAux op b l) (reduceSAux op b r)

reduceS :: (a -> a -> a) -> a -> Seq a -> a
reduceS op b [] = b
reduceS op b s  = op b (reduceSAux op b s)

scanS :: (a -> a -> a) -> a -> Seq a -> (Seq a, a)
scanS op b s = (tabulateS (\i -> reduceS op b (takeS i s)) (lengthS s), reduceS op b s)



scanSAppendeado :: (a -> a -> a) -> a -> Seq a -> Seq a
scanSAppendeado op b s = let (prefScan, finalReduce) = scanS op b s
                         in   appendS (dropS 1 prefScan) (singletonS finalReduce)

collectS :: Ord a => Seq (a,b) -> Seq (a, Seq b)
collectS s = let
                s' = sortTuple s
              in
                colectar s' []

colectar :: Ord a => Seq (a,b) -> Seq (a, Seq b) -> Seq (a, Seq b)
colectar [] l = l
colectar ((a,b):xs) [] = colectar xs [(a, [b])]
colectar ((a,b):xs) ((a',bs): rs) = if a == a' then colectar xs ((a, b:bs): rs)
                                               else colectar xs ((a, [b]) : (a',bs) : rs)


sortTuple :: Ord a => Seq (a,b) -> Seq (a,b)
sortTuple xs = sortBy f xs

  where f (a1, b1) (a2, b2) | a1 == a2  = EQ
                            | a1 > a2   = LT
                            | otherwise = GT

joinS :: Seq (Seq a) -> Seq a
joinS s = reduceS (++) [] s

-- sortS

-- mergeS
