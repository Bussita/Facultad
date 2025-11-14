type Name = String

type Path = [String]
-- El directorio base es [], los demas son la lista de nombres hasta llegar

data DirTree a = Dir Name [DirTree a] | File Name a


-- a)
names :: [DirTree a] -> [Name]
