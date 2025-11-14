
module Lab02 where

{-
   Laboratorio 2
   EDyAII 2022
-}

import Data.List

-- 1) Dada la siguiente definición para representar árboles binarios:

data BTree a = E | Leaf a | Node (BTree a) (BTree a)

-- Definir las siguientes funciones:

-- a) altura, devuelve la altura de un árbol binario.

altura :: BTree a -> Int
altura E = 0
altura (Leaf _) = 1
altura (Node t1 t2) = 1 + max (altura t1) (altura t2)

-- b) perfecto, determina si un árbol binario es perfecto (un árbol binario es perfecto si cada nodo tiene 0 o 2 hijos
-- y todas las hojas están a la misma distancia desde la raı́z).


leafDepths :: BTree a -> Int -> [Int]
leafDepths E _ = []
leafDepths (Leaf _) d = [d]
leafDepths (Node t1 t2) d = leafDepths t1 (d+1) ++ leafDepths t2 (d+1)

allEqual :: [Int] -> Bool
allEqual [] = True
allEqual [x] = True
allEqual (x1:x2:xs) = x1 == x2 && allEqual (x2:xs)

nodoValido :: BTree a -> Bool
nodoValido E = True
nodoValido (Leaf _) = True
nodoValido (Node E E) = True
nodoValido (Node (Leaf _) (Leaf _)) = True
nodoValido (Node E _) = False
nodoValido (Node _ E) = False
nodoValido (Node t1 t2) = nodoValido t1 && nodoValido t2

perfecto :: BTree a -> Bool
perfecto t = allEqual (leafDepths t 0) && nodoValido t

                    

-- c) inorder, dado un árbol binario, construye una lista con el recorrido inorder del mismo.

inorder :: BTree a -> [a]
inorder E = []
inorder (Leaf a) = [a]
inorder (Node t1 t2) = inorder t1 ++ inorder t2


-- 2) Dada las siguientes representaciones de árboles generales y de árboles binarios (con información en los nodos):

data GTree a = EG | NodeG a [GTree a] deriving Show

data BinTree a = EB | NodeB (BinTree a) a (BinTree a) deriving Show

{- Definir una función g2bt que dado un árbol nos devuelva un árbol binario de la siguiente manera:
   la función g2bt reemplaza cada nodo n del árbol general (NodeG) por un nodo n' del árbol binario (NodeB ), donde
   el hijo izquierdo de n' representa el hijo más izquierdo de n, y el hijo derecho de n' representa al hermano derecho
   de n, si existiese (observar que de esta forma, el hijo derecho de la raı́z es siempre vacı́o).
   
   
   Por ejemplo, sea t: 
       
                    A 
                 / | | \
                B  C D  E
               /|\     / \
              F G H   I   J
             /\       |
            K  L      M    
   
   g2bt t =
         
                  A
                 / 
                B 
               / \
              F   C 
             / \   \
            K   G   D
             \   \   \
              L   H   E
                     /
                    I
                   / \
                  M   J  
-}

g2bt :: GTree a -> BinTree a
g2bt EG = EB
g2bt (NodeG a []) = NodeB EB a EB
g2bt (NodeG a [x]) = NodeB (g2bt x) a EB
g2bt (NodeG a (x:y:xs)) = NodeB (g2bt x) a (g2bt y)


-- 3) Utilizando el tipo de árboles binarios definido en el ejercicio anterior, definir las siguientes funciones:
{-
   a) dcn, que dado un árbol devuelva la lista de los elementos que se encuentran en el nivel más profundo 
      que contenga la máxima cantidad de elementos posibles. Por ejemplo, sea t:
            1
          /   \
         2     3
          \   / \
           4 5   6
                             
      dcn t = [2, 3], ya que en el primer nivel hay un elemento, en el segundo 2 siendo este número la máxima
      cantidad de elementos posibles para este nivel y en el nivel tercer hay 3 elementos siendo la cantidad máxima 4.
   -}

dcnAux :: BinTree a -> Int -> [a] -> [a]
dcnAux = undefined
dcn :: BinTree a -> [a]
dcn = undefined

{- b) maxn, que dado un árbol devuelva la profundidad del nivel completo
      más profundo. Por ejemplo, maxn t = 2   -}

esCompleto :: BinTree a -> Int -> Bool
esCompleto EB n
               | n > 0 = False
               | otherwise = True
esCompleto (NodeB EB _ EB) 0 = True
esCompleto (NodeB _ _ EB) 0 = False
esCompleto (NodeB EB _ _) 0 = False
esCompleto (NodeB t1 _ t2) n = (esCompleto t1 (n-1)) && (esCompleto t2 (n-1))


maximoCompleto :: BinTree a -> Int -> Int
maximoCompleto t n = if esCompleto t n then maximoCompleto t (n+1) else n

maxn :: BinTree a -> Int
maxn EB = 0
maxn t = maximoCompleto t 0

{- c) podar, que elimine todas las ramas necesarias para transformar
      el árbol en un árbol completo con la máxima altura posible. 
      Por ejemplo,
         podar t = NodeB (NodeB EB 2 EB) 1 (NodeB EB 3 EB)
-}

podarAux :: BinTree a -> Int -> Int -> BinTree a
podarAux EB _ _ = EB
podarAux (NodeB l x r) nivel maxNivel
  | nivel >= maxNivel = NodeB EB x EB
  | otherwise = NodeB (podarAux l (nivel + 1) maxNivel)
                      x
                      (podarAux r (nivel + 1) maxNivel)

podar :: BinTree a -> BinTree a
podar t = podarAux t 0 (maxn t)






