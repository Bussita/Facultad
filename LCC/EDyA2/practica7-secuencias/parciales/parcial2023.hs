-- Ejercicio 2
data Tree a = E | N Int (Tree a) a (Tree a)

(|||) :: a -> b -> (a, b)
a ||| b = (a, b)

filterPrefix :: (a -> Bool) -> Tree a -> Tree a
filterPrefix p E            = E
filterPrefix p (N sz l v r) = let
                                (recl, recr) = filterPrefix p l ||| filterPrefix p r
                              in
                                if (size recl == size l && p v) then (N (size recl + size recr + 1) recl v recr)
                                                                else recl  