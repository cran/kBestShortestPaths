kBestShortestPaths <- function(g, source.node, dest.node, best.count)
{
	edgeW <- edgeWeights(g);
	e.names <- c();
	e.weights <- c();
	index <- 1;
	for (i in 1:length(edgeW))
	{
		v <- edgeW[[i]];
		if (length(v) == 0)
			next;
		for (j in 1:length(v))
		{
#			cat(sprintf("%s~%s\t%g\n", names(edgeW)[i], names(v)[j], v[j]));
			e.names[index] <- sprintf("%s~%s", names(edgeW)[i], names(v)[j]);
			e.weights[index] <- v[j];
			index <- index + 1;
		}
	}

	ab <- .Call("bozghale",
			nodes(g),
			length(nodes(g)),
			e.names,
			e.weights,
			length(e.names),
			as.integer(1),
			source.node, 
			dest.node,
			as.integer(best.count));
	return (new('Paths', best.paths=ab$best.paths, path.scores=ab$path.weights));
}
