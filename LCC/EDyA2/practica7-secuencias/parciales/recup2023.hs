import Sequence

-- Reemplaza los elementos impares de una secuencia dada por el elemento par anterior en la secuencia, o 0 si
-- no hay elementos pares anteriores
replaceOdd :: Seq Int -> Seq Int
replaceOdd s = 
  let
    (u, r) = scanS f e s
    v = appendS (dropS 1 u) (singletonS r)
    n = lengthS s 
  in
    tabulateS (\i -> nthS i (if mod (nthS i s) 2 == 0 then s else v)) n


f :: Int -> Int -> Int
f l r   | mod r 2 == 0      = r
        | otherwise         = l
        
e :: Int 
e = 0


ejemploUno :: Seq Int
ejemploUno = [2, 3, 4, 5, 5, 2]

ejemploDos :: Seq Int
ejemploDos = [3, 4, 5]

ejemploTres :: Seq Int
ejemploTres = [1, 1, 8, 1]