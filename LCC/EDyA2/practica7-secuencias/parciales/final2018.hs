data BTree a = E | L a | N Int (BTree a) (BTree a) deriving Show

(|||) :: a -> b -> (a, b)
a ||| b = (a, b)

size :: BTree a -> Int
size E          = 0
size (L _)      = 1
size (N sz _ _) = sz

mapIndex :: (a -> Int -> b) -> BTree a -> BTree b
mapIndex f t = mapIndexAux f t 0
               where
                mapIndexAux :: (a -> Int -> b) -> BTree a -> Int -> BTree b
                mapIndexAux f E _ = E
                mapIndexAux f (L x) idx = L (f x idx)
                mapIndexAux f (N sz l r) idx =  let
                                                  (recL, recR) = mapIndexAux f l idx ||| mapIndexAux f r (idx + size l)
                                                in
                                                  N sz recL recR


tabulateConst :: Int -> Int -> BTree Int
tabulateConst v 0 = E
tabulateConst v 1 = L v
tabulateConst v n = let
                    lsz = div n 2
                    rsz = n - lsz
                  in
                    N n (tabulateConst v lsz) (tabulateConst v rsz)



fromSlow :: Int -> Int -> Int -> BTree Int
fromSlow n m k =  let
                    baseSeq = tabulateConst n m

                    f :: Int -> Int -> Int
                    f v idx = v + div idx k

                  in
                    mapIndex f baseSeq 




