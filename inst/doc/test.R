library(kBestShortestPaths);
library(graph);
set.seed(123);
V <- letters[1:10];
M <- 1:4;
g1 <- randomGraph(V, M, 0.2);
z <- kBestShortestPaths(g1, "a", "h", 5);

eAttrs <- list()
ew <- as.character(unlist(edgeWeights(g1)))
ew <- ew[setdiff(seq(along = ew), removedEdges(g1))]
names(ew) <- edgeNames(g1)
eAttrs$label <- ew
plot(g1, nodeAttrs=nA, edgeAttrs = eAttrs)

