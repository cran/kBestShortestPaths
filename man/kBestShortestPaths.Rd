\name{kBestShortestPaths}
\alias{kBestShortestPaths}
\title{kBestShortestPaths Function Description}
\description{
	\code{kBestShortestPaths} is a function which finds the
	k-shortest paths in between a source and destination node in a
	given graph (directed or not). 
}
\usage{
kBestShortestPaths(g, source.node, dest.node, best.count)
}
\arguments{
  	\item{g}{
	  	A 'graphNEL-class' object. This object contains nodes, edge names, and edge weights.
	}
 	\item{source.node}{
	  	The name of the source node (character). 
  	}
	\item{dest.node}{
	  The name of the destination node (character).
	}
	\item{best.count}{
		An integer value which shows the maximum number of paths to be returned. The algorithm tries to find \code{best.count} paths. It will return less paths if the number of distinct paths from source to destination is less than the given value.
	}
}
\details{
Given a graph having n vertices and m edges, the implemented algorithm takes O(m + n log(n) + k) to find k-shortest paths. If the graph is a DAG, it can contain negative edge weights, and if not, all edge weights have to be non-negative.
}
\value{
	\item{Paths}{An object of type \code{\link{Paths}} which
	  contains the calculated k-shortest paths. If the total number
	  of paths p is less than k, the \code{\link{Paths}} would have only p paths. If no paths could be found from source to destination, then the \code{\link{Paths}} class would be empty.}
}
\references{
D. Eppstein, Finding the k shortest paths, SIAM J. Comput., 1998 - Citeseer.
}
\author{
Adrin Jalali

Maintainer: Adrin Jalali<adrin.jalali@gmail.com>
}

\seealso{
\code{\link{Paths}}
}
\examples{
library(kBestShortestPaths);
library(graph);
set.seed(123);
V <- letters[1:10];
M <- 1:4;
g1 <- randomGraph(V, M, 0.2);
z <- kBestShortestPaths(g1, "a", "h", 5);
summary(z);
plot(z);
}
\keyword{ kBestShortestPaths, Paths }
