import Sequence

-- Encontrar la subsecuencia contigua mas larga donde todos los valores son mayores a 30
-- Para eso resolveremos el problema de la subsecuencia contigua de unos mas larga

data Bit = Cero | Uno deriving (Eq, Ord, Show)

scmtml :: Seq Int -> Int
scmtml s =  let s' = map (\i -> if i > 30 then Uno else Cero) s
            in  scuml s'

-- Con scan encontramos el sufijo mas largo
scuml :: Seq Bit -> Int
scuml s = let 

            esUno :: Bit -> Bool
            esUno Uno  = True
            esUno Cero = False
            indexedSeq = tabulateS (\i -> (i, if esUno (nthS i s) then 1 else 0, i)) (lengthS s)

            op :: (Int, Int, Int) -> (Int, Int, Int) -> (Int, Int, Int)
            op (-1, -1, -1) r            = r
            op (i1, l1, j1) (i2, l2, j2) =
                if esUno (nthS j1 s) && i2 - j1 == 1 then (i1, l1 + l2, j1)
                                                    else (i2, l2, j2)
            
            e :: (Int, Int, Int)
            e = (-1, -1, -1)

            (ss, r) = scanS op e indexedSeq

            suffixesLengths = map (\(i, l, j) -> l) (appendS ss (singletonS r))

          in

            reduceS max 0 suffixesLengths