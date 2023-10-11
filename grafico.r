avl_insert_csv <- "/home/fernando/Documentos/pessoal/ed/avl_insert.csv"

avl_insert <- read.csv(avl_insert_csv, header = TRUE, sep = ",")

avl_search_csv <- "/home/fernando/Documentos/pessoal/ed/avl_search.csv"

avl_search <- read.csv(avl_search_csv, header = TRUE, sep = ",")

binary_tree_search_csv <- "/home/fernando/Documentos/pessoal/ed/binary_tree_search.csv"

binary_tree_search <- read.csv(binary_tree_search_csv, header = TRUE, sep = ",")

avl_delete_csv <- "/home/fernando/Documentos/pessoal/ed/avl_delete.csv"

avl_delete <- read.csv(avl_delete_csv, header = TRUE, sep = ",")


binary_tree_insert_csv <- "/home/fernando/Documentos/pessoal/ed/binary_tree_insert.csv"

binary_tree_insert <- read.csv(binary_tree_insert_csv, header = TRUE, sep = ",")


binary_tree_delete_csv <- "/home/fernando/Documentos/pessoal/ed/binary_tree_delete.csv"

binary_tree_delete <- read.csv(binary_tree_delete_csv, header = TRUE, sep = ",")


avl_insert_ordered_csv <- "/home/fernando/Documentos/pessoal/ed/avl_insert_ordered.csv"

avl_insert_ordered <- read.csv(avl_insert_ordered_csv, header = TRUE, sep = ",")


avl_delete_ordered_csv <- "/home/fernando/Documentos/pessoal/ed/avl_delete_ordered.csv"

avl_delete_ordered <- read.csv(avl_delete_ordered_csv, header = TRUE, sep = ",")


binary_tree_insert_ordered_csv <- "/home/fernando/Documentos/pessoal/ed/binary_tree_insert_ordered.csv"

binary_tree_insert_ordered <- read.csv(binary_tree_insert_ordered_csv, header = TRUE, sep = ",")


binary_tree_delete_ordered_csv <- "/home/fernando/Documentos/pessoal/ed/binary_tree_delete_ordered.csv"

binary_tree_delete_ordered <- read.csv(binary_tree_delete_ordered_csv, header = TRUE, sep = ",")

plot(avl_insert_ordered$comparations)
plot(binary_tree_insert_ordered$comparations)

plot(avl_delete_ordered$comparations)
plot(binary_tree_delete_ordered$comparations)

plot(avl_insert$comparations)
plot(binary_tree_insert$comparations)

plot(avl_delete$comparations)
plot(binary_tree_delete$comparations)

plot(binary_tree_search$comparations)
plot(avl_search$comparations)
