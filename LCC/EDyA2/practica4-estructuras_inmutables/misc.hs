data BST a = E | Node (BST a) a (BST a) 

insert :: Ord a => a -> BST a -> BST a
insert a E = Node E a E
insert a (Node l y r)
                    | a <= y = Node (insert a l) y r
                    | otherwise = Node l y (insert a r)

minimo :: Ord a => BST a -> a
minimo E = error "No deberia ser vacio"
minimo (Node E a _) = a
minimo (Node l a _) = minimo l

maximo :: Ord a => BST a -> a
maximo E = error "No deberia ser vacio"
maximo (Node _ a E) = a
maximo (Node _ a r) = minimo r

delete :: Ord a => a -> BST a -> BST a
delete _ E = E
delete a (Node l y r)
                    | a < y = Node (delete a l) y r
                    | a > y = Node l y (delete a r)
                    | a == y = deleteAux (Node l y r)

deleteAux (Node E _ E) = E
deleteAux (Node l _ E) = l
deleteAux (Node E _ r) = r
deleteAux (Node l a r) = let m = minimo r in Node l m (delete m r)


lazy x = 
    let y = lazy (x+1) in snd (y,5)