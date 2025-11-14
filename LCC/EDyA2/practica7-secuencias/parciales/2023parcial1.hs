type Interval = (Int, Int)
data ITree = E | N ITree Interval ITree

-- invariantes. si t es una hoja o es un Nodo l (a, b) r entonces

--  los intervalos estan bien formados, a <= b
--  si (x, y) es el intervalo de un nodo en l, y < a - 1
--  si (x, y) es el intervalo de un nodo en r, b + 1 < x
--  l y r son arboles de intervalo

-- a)
right :: ITree -> Int 
right (N _ (_, b) E)  = b
right (N _ _ r)       = right r

left :: ITree -> Int
left (N E (a, _) _)   = a
left (N l _ _)        = left l

getLeft :: ITree -> Maybe Int 
getLeft E              = Nothing
getLeft (N _ (a, _) _) = Just a

getRight :: ITree -> Maybe Int 
getRight E              = Nothing
getRight (N _ (_, b) _) = Just b

-- b)
type Cotas = (Maybe Int, Maybe Int)

checkIT :: ITree -> Bool
checkIT E = True
checkIT (N E (a, b) E) = a <= b
checkIT (N l (a, b) E) = a <= b && right l < a - 1  && checkIT l
checkIT (N E (a, b) r) = a <= b && left r  > b + 1  && checkIT r
checkIT (N l (a, b) r) = a <= b && right r < a + 1  && left r > b + 1 && checkIT l && checkIT r

checkITv2 :: ITree -> Bool
checkITv2 = auxCheck (Nothing, Nothing)

auxCheck :: Cotas -> ITree -> Bool
auxCheck _ E                              = True
auxCheck (lBound, rBound) (N l (a, b) r)
          = correctInterval && leftValid && rightValid && checkSubtrees
            
            where
              correctInterval = a <= b
              
              maybeLess Nothing _             = True
              maybeLess _ Nothing             = True
              maybeLess (Just a) (Just b)     = a < b

              maybeGreater Nothing _          = True
              maybeGreater _ Nothing          = True
              maybeGreater (Just a) (Just b)  = a > b 
              
              leftValid                       = maybeLess     (getRight l) lBound
              rightValid                      = maybeGreater  (getLeft  r) rBound

              checkSubtrees                   = auxCheck (lBound, Just (a - 1)) l &&
                                                auxCheck (Just (b + 1), rBound) r


-- dado un ITree devuelve el intervalo mas a la derecha y el ITree resultante de eliminarlo
splitMax :: ITree -> (Interval, ITree)
splitMax (N E i E)  = (i, E)
splitMax (N l i E)  = (i, l)
splitMax (N l i r)  = (recInterval, recTree)
                      where
                        (recInterval, recRightTree)   = splitMax r
                        recTree                       = N l i recRightTree



merge :: ITree -> ITree -> ITree 
merge l E = l
merge E r = r
merge l (N rl rInterval rr) = let
                                (rightInterval, rightSubtreeRemoved) = splitMax rl
                              in
                                N (merge l rightSubtreeRemoved) rightInterval (N E rInterval rr)

-- buscarlo
delElem :: ITree -> Int -> ITree
delElem E _               = E
delElem (N l (a, b) r) v  | v == a      = if a == b then merge l r else N l (a + 1, b) r
                          | v == b      = if a == b then merge l r else N l (a, b - 1) r
                          | v <  a      = delElem l v
                          | v >  b      = delElem r v
                          | otherwise   = merge (N l (a, v - 1) E)
                                                (N E (v + 1, b) r)



--  Dar la recurrencia
--  Sea h la profundidad del arbol, entonces si asumimos el peor caso, donde dado un arbol de profundidad h
-- sus dos subarboles son de profundidad h - 1, tenemos que:

--  T(0) = a
--  T(h) =  T_correctInterval(h) + T_isLeftBounded(h - 1) + T_isLeftBounded(h - 1) + T_checkSubTrees(h - 1)
--          donde
--            T_correctInterval(h)    =  b (es una comparacion)
--            T_leftValid(h)          =  c (es una comparacion)
--            T_rightValid(h)         =  d (es una comparacion)
--            T_checkSubTrees(h)      =  2T(h - 1)

--  Entonces si en T(h) definimos k = b + c + d,
--  T(h) = 2T(h - 1) + k
--  Podemos ver que es al menos 2^h en complejidad.
