import Sequence

type Art = Char
type Precio = Int

articuloNulo :: Char
articuloNulo = 'N'

aumentos :: Seq (Art, Precio) -> (Art, Precio)
aumentos s = let
              -- Mappeo a cada part (Art, Precio) su indice, volviendolo (Art, Precio, Indice)
              indexedS = tabulateS (\i -> let (art, p) = nthS i s
                                          in  (art, p, i)) (lengthS s)

              -- Mappeo a cada (Art, Precio, Indice) la secuencia de todos los pares (Art, Precio)
              -- de la lista que estan mas adelante
              s' = mapS (\(art, p, i) -> (art, p, filterS (esArt art) (dropS (i + 1) s))) indexedS

              esArt :: Art -> (Art, Precio) -> Bool
              esArt art (art', _) = art == art'

              -- Ahora a cada (Art, Precio, Seq (Art, Precio)) le mappeo (Art, Bool) donde el 
              -- booleano me dice si aumento en la proxima aparicion o no
              s'' = mapS (\(art, p, apariciones) -> (art, aumentoEnLaProx p apariciones)) s' 

              aumentoEnLaProx :: Precio -> Seq (Art, Precio) -> Bool
              aumentoEnLaProx _ [] = False
              aumentoEnLaProx p s  = p < (getPrecio (firstS s))

              getPrecio (_, p) = p

              -- Ahora filtro la lista de (Art, Bool) para quedarme con los que tienen la forma (Art, True)
              s''' = filterS (\(art, bul) -> bul) s''

              -- Ahora a cada articulo le mappeo cuantas apariciones de ese articulo hay en la lista
              -- Es decir, a cada articulo le mappeo la longitud de haber filtrado a s''' por el nombre de
              -- su articulo. Obs. que todas las tuplas con un mismo articulo van a ser iguales.
              s'''' = mapS (\(art, bul) -> (art, lengthS (filterS (\(art', _) -> art' == art) s'''))) s'''

              -- Por ultimo, defino la operacion para reducir a s''''
              --  tomando maximos en la segunda componente.
              maxSegunda (art, cant) (art', cant') = if cant < cant' then (art', cant') else (art, cant)

             in
              -- Tarann
              reduceS maxSegunda ('N', minBound) s''''


ejemploUno :: Seq (Art, Precio)
ejemploUno = [('a', 5), ('b', 4), ('a', 4), ('a', 30), ('b', 7), ('b', 10)]

ejemploDos :: Seq (Art, Precio)
ejemploDos = [('a', 5), ('a', 6), ('b', 1), ('a', 3), ('a', 4), ('b', 2)]