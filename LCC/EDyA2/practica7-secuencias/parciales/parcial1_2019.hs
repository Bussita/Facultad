-- Implementacion de treap
-- Condiciones que verifica el arbol:
-- *  La prioridad de un nodo es al menos la de sus hijos
-- *  La clave de cada nodo es al menos la de su hijo izquierdo
-- * y a lo sumo la de su hijo derecho

data Treap p k = E | N (Treap p k) p k (Treap p k) deriving Show

-- a)
key :: Treap p k -> k
key (N _ _ k _) = k


-- b)
priority :: Treap p k -> p
priority (N _ p _ _) = p

-- c) Necesito una auxiliar para verificar que es BST
-- Defino un nuevo tipo
type Cota k = Maybe k

-- (Cota, Cota) son los (a, b) tales que a <= k <= b
-- Observemos que si 
--          (x, y)
--         /     \
--     (a, b)   (c, d)
-- entonces:
-- b <= x
-- c >= y
-- Entonces
-- Cuando bajo hacia la izquierda, actualizo la cota derecha
-- Cuando bajo hacia la derecha,   actualizo la cota izquierda

isKeyAcotado :: Ord k => k -> (Cota k, Cota k) -> Bool
isKeyAcotado _ (Nothing, Nothing) = True
isKeyAcotado k (Just a, Nothing)  = a <= k
isKeyAcotado k (Nothing, Just b)  = k <= b
isKeyAcotado k (Just a, Just b)   = a <= k && k <= b


-- falta chequear las prioridades
isTreapAux :: (Ord k, Ord p) => Treap p k -> (Cota k, Cota k) -> p -> Bool
isTreapAux  E           _     _   = True
isTreapAux (N E p k E) (a, b) p'  = isKeyAcotado k (a, b)      && p <= p'
isTreapAux (N l p k E) (a, b) p'  = isKeyAcotado k (a, b)      && p <= p' &&
                                    isTreapAux l (a, Just k) p
isTreapAux (N E p k r) (a, b) p'  = isKeyAcotado k (a, b)      && p <= p' &&
                                    isTreapAux r (Just k, b) p
isTreapAux (N l p k r) (a, b) p'  = isKeyAcotado k (a, b)      && p <= p' &&
                                    isTreapAux l (a, Just k) p && isTreapAux r (Just k, b) p


isTreap :: (Ord k, Ord p) => Treap p k -> Bool
isTreap t = isTreapAux t (Nothing, Nothing) (priority t)

-- Dar la recurrencia del trabajo de isTreap

-- Sea n la cantidad de nodos del treap. Entonces,
--    W_isTreap(n) = W_isTreapAux(n) + k1
-- don
--    W_isTreapAux(n) = k2 + W_isKeyAcotado() +      


-- d) Insercion.
rotateL :: Treap p k -> Treap p k
rotateL (N l' p' k' (N l p k r)) = N (N l' p' k' l) p k r

rotateR :: Treap p k -> Treap p k
rotateR (N (N l p k r) p' k' r') = N l p k (N r p' k' r')

-- Dados p, k, y un tree, devuelve el tree con la insercion hecha.
-- La idea es  insertar como un BST, es decir, vamos bajando por el arbol hasta que
-- 1) Estoy en el arbol nulo.
-- 2) No tengo rama derecha ni izquierda. Me ubico en la correcta.
-- 3) No tengo rama izquierda y soy mas chico que la derecha
-- 4) No tengo rama derecha   y soy mas chico que la izquierda

getLeftComponent :: (a, b) -> a
getLeftComponent (l, _) = l

insert :: (Ord k, Ord p) => p -> k -> Treap p k -> Treap p k
insert p k E              = N E p k E
insert p k (N l p' k' r)  | k  < k'     = getLeftComponent (balanceoIzq  N (insert p k l) p' k' r))
                          | k == k'     = balanceoGeneral (N l p k r)
                          | otherwise   = getLeftComponent (balanceoDer (N l p' k' (insert p k r)))
                          
                                        
balanceoIzq :: (Ord k, Ord p) => Treap p k -> (Treap p k, Bool)
balanceoIzq E             = (E, False)
balanceoIzq t@(N E p k r) = (t, False)
balanceoIzq (N l p k r)   = if p <= priority l  then (rotateR (N l p k r), True)
                                              else (N l p k r, False) 

balanceoDer :: (Ord k, Ord p) => Treap p k -> (Treap p k, Bool)
balanceoDer E             = (E, False)
balanceoDer t@(N l p k E) = (t, False)
balanceoDer (N l p k r)   = if p <= priority r  then (rotateL (N l p k r), True)
                                                else (N l p k r, False)

getLeftTreap :: (Ord k, Ord p) => Treap p k -> Treap p k                                              
getLeftTreap E  = E
N l _ _ _       = l


balanceoGeneral :: (Ord k, Ord p) => Treap p k -> Treap p k
balanceoGeneral E = E
balanceoGeneral t = let
                      (balanceadoDerecho@(N l p k r), didBalanceRight) = balanceoDer t
                    in
                      if didBalanceRight  then getLeftComponent (balanceoIzq (N (getLeftComponent (balanceoIzq l)) p k r))
                                          else getLeftComponent (balanceoIzq balanceadoDerecho)


-- Ejercico e) split
split :: (Ord k, Ord p, Num p) => k -> Treap p k -> (Treap p k, Treap p k)
split _ E           = (E, E)
split x t@(N l p k r) = let
                          (N l' p' k' r') = insert (p + 1) x t
                        in
                          (l', r')



ll :: Treap Integer Integer
ll = N E 5 5 E
lr :: Treap Integer Integer
lr = N E 7 12 E

rl :: Treap Integer Integer
rl = N E 1 16 E
rr :: Treap Integer Integer
rr = N E 12 20 E

-- l :: Treap Integer Integer
-- l = N ll 10 10 lr
-- r :: Treap Integer Integer
-- r = N rl 15 17 rr

-- ejemploTreap :: Treap Integer Integer
-- ejemploTreap = N l 20 15 r

-- ejemploInsertado :: Treap Integer Integer
-- ejemploInsertado = insert 30 11 ejemploTreap

-- ejemploActualizar :: Treap Integer Integer
-- ejemploActualizar = insert 30 12 ejemploTreap

-- insert p k (N E p' k' E)  = let newLeaf = N E p k E
--                             in  if k <= k'  then N newLeaf p' k' E 
--                                             else N E p' k' newLeaf
-- insert p k (N l p' k' E)  = if k' <= k  then N l p' k' (N E p k E)
--                                         else N (insert p k l) p' k' E
-- insert p k (N E p' k' r)  = if k  <= k' then N (N E p k E) p' k' r
--                                         else N E p' k' (insert p k r)
