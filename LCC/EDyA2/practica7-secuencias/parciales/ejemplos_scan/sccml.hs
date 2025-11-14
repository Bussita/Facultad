import Sequence

-- Dada una secuencia de ints, devuelve el numero de saltos de crecimiento contiguos mas largo en la secuencia
-- La idea es hacer un scan con un operador que calcule el crecimiento contiguo sufijo maximo de una secuencia
-- de manera que cada resultado parcial representa el maximo de crecimientos contiguos para una subsecuencia
-- que termina en el ultimo indice de cada paso.

findMaxElementIndex :: Seq Int -> Int
findMaxElementIndex s = let 
                          indexedSeq = tabulateS (\i -> (nthS i s, i)) (lengthS s)

                          maxSndOp :: (Int, Int) -> (Int, Int) -> (Int, Int)
                          maxSndOp (i, x) (j, y) = if x < y then (j, y) else (i, x)

                          neutral :: (Int, Int)
                          neutral = (-1, minBound)
                        
                        in
                          snd (reduceS maxSndOp neutral indexedSeq)

sccml :: Seq Int -> Int
sccml s = let
            -- Primero necesitamos mappearle los indices a cada elemento
            indexSeq = tabulateS (\i -> (i, 0, i)) (lengthS s)


            sccmlSuffixOp :: (Int, Int, Int) -> (Int, Int, Int) -> (Int, Int, Int)
            sccmlSuffixOp (i1, l1, j1) (i2, l2, j2) =
              if nthS j1 s < nthS i2 s && i2 - j1 == 1
                 then (i1, l1 + l2 + 1, j2)
                 else (i2, l2, j2)

            -- El neutro de la operacion va a ser el que siempre haga que devuelva al otro cuando el neutro es el izquierdo.
            -- Basta con definirlo de manera que siempre falle el if.
            opNeutral :: (Int, Int, Int)
            opNeutral = let maxElmIdx = findMaxElementIndex s
                        in  (maxElmIdx, 0, maxElmIdx)

            (ss, r) = scanS sccmlSuffixOp opNeutral indexSeq

            subseqsLenghts = mapS (\(_, l, _) -> l) (appendS ss (singletonS r)) 

          in

            reduceS max 0 subseqsLenghts


ejemploUno :: Seq Int
ejemploUno = [9, 3, 5, 1, 3, 4, 5, 6, 8, 1]

ejemploDos :: Seq Int
ejemploDos = [5, 6, 2, 3, 5, 1, 9]