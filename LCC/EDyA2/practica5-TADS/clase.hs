class Cola a where
  vacia :: Cola a
  poner :: a -> Cola a -> Cola a
  primero :: Cola a -> a
  sacar :: Cola a -> Cola a
  esVacia :: Cola a -> Bool

instance Cola [] where
  vacia = []
  poner x xs = (x : xs)
  primero [] = error "Cola vacia"
  primero (x : xs) = x
  sacar [] = error "Cola vacia"
  sacar xs = tail xs
  esVacia [] = True
  esVacia (x : xs) = False
