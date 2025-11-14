import Sequence
-- Subsecuencia contigua de unos mas larga

-- Asumimos la secuencia de ints son 0 y 1
scuml :: Seq Int -> Int
scuml s = let
            -- Los mappeo a (longitud, longitud sufijo mas largo de unos)
            s' = mapS (\i -> if i == 0 then (1, 0) else (1, 1)) s

            op :: (Int, Int) -> (Int, Int) -> (Int, Int)
            op (len, lensuf) (len', lensuf') = if len' == lensuf' then (len + len', lensuf' + lensuf)
                                                                  else (len + len', lensuf')

            e :: (Int, Int)
            e = (0, 0)

            (ss, r) = scanS op e s'

            lenSufijos = mapS (\(len, lensuf) -> lensuf) (appendS ss (singletonS r))

          in
            reduceS max minBound lenSufijos

ejemploUno :: Seq Int
ejemploUno = [0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0]

{-
  Demostracion de la asociatividad de op.
  Queremos ver si

    op (op x y) z  =?  op x (op y z)

  Consideremos las tuplas

  (lenx, sufx) (leny, sufy) (lenz, sufz)

  Entonces

  op (op (lenx, sufx) (leny, sufy)) (lenz, sufz)

  < Separamos por casos >

    < leny == sufy >

    op (lenx + leny, sufx + sufy) (lenz, sufz)

    < Separamos por casos >

      < lenz == sufz >

      (lenx + leny + lenz, sufx + sufy + sufz)

      < lenz != sufz >

      (lenx + leny + lenz, sufz)

  
    < leny != sufy >

    op (lenx + leny, sufy) (lenz, sufz)

    < Separamos por casos >

      < lenz == sufz >

      (lenx + leny + lenz, sufy + sufz)

      < lenz != sufz >

      (lenx + leny + lenz, sufz)
      
-}

{-

  Veamos el otro lado de la igualdad

  (lenx, sufx) (leny, sufy) (lenz, sufz)

  op (lenx, sufx) (op (leny, sufy) (lenz, sufz))

  < Separemos por casos >

    < lenz == sufz >

    op (lenx, sufx) (leny + lenz, sufy + sufz)

    < Separemos por casos >

      < sufy + sufz == leny + lenz >  

      (lenx + leny + lenz, sufx + sufy + sufz)

      < sufy + sufz != leny + lenz >

      (lenx + leny + lenz, sufy + sufz)

    
    < sufy != sufz>

    op (lenx, sufx) (leny + lenz, sufz)

    < Separemos por casos >

      < leny + lenz == sufz >

      (lenx + leny + lenz, sufx + sufz)

      < leny + lenz != sufz >

      (lenx + leny + lenz, sufz)

      
-}


-- Hacamos sccml pero con esta idea de las longitudes

sccml :: Seq Int -> Int
sccml s = let

            s' = tabulateS (\i -> if nthS i s < nthS (i + 1) s then 1 else 0) (lengthS s - 1) 

          in
            
            scuml s'

ejemploDos :: Seq Int
ejemploDos = [7, 8, 3, 4, 5, 6, 12, 4, 5, 9, 9, 1, 2]

ejemploTres :: Seq Int
ejemploTres = []