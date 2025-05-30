from nltk.tree import *

# Corrected tree representation with explicit binary structure
text = "(+ (- (+ 1 2) (* 3 4)) (5))"

tree = Tree.fromstring(text)
tree.pretty_print(unicodelines=True, nodedist=5)

