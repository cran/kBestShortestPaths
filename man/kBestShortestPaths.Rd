\name{kBestShortestPaths}
\alias{kBestShortestPaths}
\title{kBestShortestPaths Function Description}
\description{
	\code{kBestShortestPaths} is a function which tries to find k-shortest paths in a given graph, a source node, and a destination node. If all possible shortest paths from the source to the destination is less than k, the \code{\link{Paths}} would have all possible paths from source to destination. If no path could be found from source to destination, then the \code{\link{Paths}} class would be empty as return value of the \code{kShortestPaths} function.
}
\usage{
kBestShortestPaths(g, source.node, dest.node, best.count)
}
\arguments{
  	\item{g}{
	  	A 'graphNEL-class' object. This object contains nodes, edge names, and edge weights which all are needed in the algorithm.
	}
 	\item{source.node}{
	  	An input string which is supposed to be the name of the source node in the graph. All returned paths would have this node as the first node of the path.
  	}
	\item{dest.node}{
		An input string which is supposed to be the name of the destination node in the graph. All returned paths would have this node as the last node of the path.
	}
	\item{best.count}{
		It is an integer value which shows the maximum number of paths to be returned. The algorithm tries to find \code{best.count} paths. It will return less paths if the number of distinct paths from source to destination is less than the given value.
	}
}
\details{
Given a graph having n vertices and m edges, the implemented algorithm takes O(m + n log(n) + k) to find k-shortest paths. If the graph is a DAG, it can contain negative edge weights, and if not, all edge weights have to be non-negative.
}
\value{
	\item{Paths}{An object of type \code{\link{Paths}} which contains the calculated k-shortest paths.}
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
library(Rgraphviz);
set.seed(123);
V <- letters[1:10];
M <- 1:4;
g1 <- randomGraph(V, M, 0.2);
z <- kBestShortestPaths(g1, "a", "h", 5);
summary(z);
plot(z);
}
\keyword{ kBestShortestPaths, Paths }
