kBestShortestPaths <- function(g, source.node, dest.node, best.count)
{
  if(class(g)[1]!='graphNEL')
    stop('g needs to be a graphNEL-class obejct.')
  if (!((source.node %in% nodes(g))&&(dest.node %in% nodes(g))))
    stop('source.node and dest.node need to be nodes of g.')
  if(best.count<=0)
    stop('best.count needs to be greater than 0.')
  
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
          ##cat(sprintf("%s~%s\t%g\n", names(edgeW)[i], names(v)[j], v[j]));
          e.names[index] <- sprintf("%s~%s", names(edgeW)[i], names(v)[j]);
          e.weights[index] <- v[j];
          index <- index + 1;
        }
    }

  output <- .Call("bozghale",
              nodes(g),
              length(nodes(g)),
              e.names,
              e.weights,
              length(e.names),
              as.integer(1),
              source.node, 
              dest.node,
              as.integer(best.count));
  return (new('Paths', best.paths=output$best.paths, path.scores=output$path.weights));
}
