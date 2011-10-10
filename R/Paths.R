setClass("Paths",
         representation(best.paths='list', path.scores="list"))


setMethod("summary", signature(object="Paths"), function(object){
  cat(sprintf("A set of %d shortest paths\n", length(object@best.paths)))
})


setMethod("plot", signature(x="Paths"), function(x){
  scores=vector()
  for (i in 1:length(x@path.scores))
    scores[i]=sum(x@path.scores[[i]])
  plot(density(scores), sub='', xlab='Scores')
})


