data T a = E | L a | Join Int (T a) (T a) deriving Show

(|||) :: a -> b -> (a, b)
a ||| b = (a, b)

split :: (String -> Bool) -> T String -> (T (Int, String), T (Int, String))
split p t         = splitAux p t 0

                    where

                      size :: T a -> Int
                      size E              = 0
                      size (L _)          = 1
                      size (Join sz _ _)  = sz

                      right :: T a -> T a
                      right E             = E
                      right (L _)         = E
                      right (Join _ _ r)  = r

                      splitAux :: (String -> Bool) -> T String -> Int -> (T (Int, String), T (Int, String))
                      splitAux p E     _            = (E, E)
                      splitAux p (L x) idx          = if p x  then (L (idx, x), E)
                                                              else (E, L (idx, x))
                      splitAux p (Join sz l r) idx  = let
                                                       ((l1, l2), (r1, r2)) = splitAux p l idx |||
                                                                              splitAux p r (size l + idx)
                                                      in
                                                        (replace (Join (size l1 + size r1) l1 r1),
                                                         replace (Join (size l2 + size r2) l2 r2))        


                      replace :: T (Int, String) -> T (Int, String)
                      replace (Join _ l E) = l
                      replace (Join _ E r) = r
                      replace t            = t

                      

ejemplo :: T String
ejemplo = Join 5 l r

l = Join 2 (L "oso") (L "casa")

r = Join 3 (L "reconocer") rr

rr = Join 2 (L "pala") (L "ala")


palindrome :: String -> Bool
palindrome w = w == reverse w