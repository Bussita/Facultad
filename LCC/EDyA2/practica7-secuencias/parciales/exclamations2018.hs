import Sequence

mapReduce :: Seq a -> (a -> b) -> (b -> b -> b) -> b -> b
mapReduce s f op b = let v =  case showtS s of
                              EMPTY    -> b
                              LEAF x   -> f x
                              NODE l r -> op (mapReduce l f op b) (mapReduce r f op b)
                     in  op b v

-- All n indica que los n caracteres son !
-- Some (i, j, m) indica que los primeros i son !, los ultimos j son !, y la subsecuencia contigua de
-- signos ! de longitud maxima que no es sufijo ni prefijo es m
data Result = All Int | Some (Int, Int, Int)

-- Dada una secuencia de caracteres te dice la secuencia de ! mas larga
exclamation :: Seq Char -> Int
exclamation s = case (mapReduce s f combine e) of
                All n          -> n
                Some (i, j, m) -> max i (max j m)
                
                where

                  f :: Char -> Result
                  f '!' = All 1
                  f _   = Some (0, 0, 0)

                  combine :: Result -> Result -> Result
                  combine l                (All (-1))           = l
                  combine (All (-1))        r                   = r 
                  combine (All n)          (All m)              = All (n + m)
                  combine (All n)          (Some (i, j, m))     = Some (i + n, j, m)
                  combine (Some (i, j, m)) (All n)              = Some (i, j + n, m)
                  combine (Some (i, j, m)) (Some (i', j', m'))  = Some (i, j', max m (max m' (j + i')))

                  e :: Result
                  e = All (-1)

ejemploA :: String 
ejemploA = "hola!!estoy!!usando!!!!signos!!!!!deexcl!amacion!"

-- Ejercicio b 