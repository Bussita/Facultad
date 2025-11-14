import Sequence

-- Intentamos hacer mcss con scan
-- Me creo un scan con las maximas sumas sufijas y uno con las maximas sumas prefijas
mssc :: Seq Int -> Int
mssc s = let
          -- Esto es para calcular las sumas sufijas
          s' = tabulateS (\i -> (i, nthS i s, i)) (lengthS s)
          
          op :: (Int, Int, Int) -> (Int, Int, Int) -> (Int, Int, Int)
          op (i1, s1, j1) (i2, s2, j2) =
            if s1 >= 0 && i2 - j1 == 1 then (i1, s1 + s2, j2)
                                      else (i2, s2, j2)

          e :: (Int, Int, Int)
          e = (lengthS s, 0, lengthS s)

          (ss, r) = scanS op e s'

          sumasSufijas = mapS (\(i, suma, j) -> suma) (appendS ss (singletonS r))

          -- Ahora calculamos las sumas prefijas
          (ss', r') = scanS (+) 0 s

          sumasPrefijas = appendS ss' (singletonS r')

          minSufijo = mapS

