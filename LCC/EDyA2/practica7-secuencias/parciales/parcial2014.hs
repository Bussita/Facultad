
data Tree a = E | L a | N Int (Tree a) (Tree a) deriving Show

(|||) :: a -> b -> (a, b)
a ||| b = (a, b)

getSize :: Tree a -> Int
getSize E         = 0
getSize (L _)     = 1
getSize (N s _ _) = s


concatT :: Tree (Tree a) -> Tree a
concatT E          = E
concatT (L t)      = t
concatT (N sz l r) =  let (lconcat, rconcat) = concatT l ||| concatT r
                      in  N (getSize lconcat + getSize rconcat) lconcat rconcat


-- La secuencia va de 0 a |s| - 1                  
subsequence :: Tree a -> Int -> Int -> Tree a
subsequence E _ _           = E
subsequence lf@(L v)   i j  = if i <= j then lf else E
subsequence (N sz l r) i j  | i < getSize l && j <  getSize l   = subsequence l i j
                            | i < getSize l                     = let (lss, rss) = subsequence l i (getSize l - 1) |||
                                                                                   subsequence r 0 (j - getSize l)
                                                                  in N (j - i + 1) lss rss
                            | otherwise                         = subsequence r (i - getSize l) (j - getSize l)

ejemploSeq :: Tree Int
ejemploSeq = N 9 l r

l = N 4 ll lr

ll = N 2 (L 0) (L 1)
lr = N 2 (L 2) (L 3)

r = N 5 rl rr

rl = N 2 (L 4) (L 5)

rr = N 3 (L 6) (N 2 (L 7) (L 8))