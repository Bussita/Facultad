mergesort :: Ord a => [a] -> [a]
mergesort [] = []
mergesort [x] = [x]
mergesort xs = let  (ys, zs) = split xs
                    ys' = mergesort ys
                    zs' = mergesort zs
                in merge ys' zs'

split :: Ord a => [a] -> ([a],[a])
split [] = ([],[])
split [x] = ([x],[])
split (x:y:xs) = let (l1, l2) = split xs in (x:l1, y:l2)

merge :: Ord a => [a] -> [a] -> [a]
merge [] xs = xs
merge xs [] = xs
merge l1@(x:xs) l2@(y:ys) = if x <=y then x:(merge xs l2) else y:(merge l1 ys)

suma :: a -> a -> a
    suma a b = a + b

lengthS :: Ord a => [a] -> Int
lengthS [] = 0
lengthS (x:xs) = 1 + lengthS xs

3 + 4 