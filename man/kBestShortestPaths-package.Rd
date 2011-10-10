\name{kBestShortestPaths-package}
\alias{kBestShortestPaths-package}
\alias{kBestShortestPaths-package}
\docType{package}
\title{kBestShortestPaths Package Overview}
\description{
Given a graph having n vertices and m edges, the implemented algorithm takes O(m + n log(n) + k) to find k-shortest paths. If the graph is a DAG, it can contain negative edge weights, and if not, all edge weights have to be non-negative.
}
\details{
\tabular{ll}{
Package: \tab kBestShortestPaths\cr
Type: \tab Package\cr
Version: \tab 0.9.0\cr
Date: \tab 2011-10-10\cr
License: \tab GPL (>= 3)\cr
LazyLoad: \tab yes\cr
}
This package provides the kBestShortestPaths function which gets a graphNEL object, a source, a destination, and the number of shortest paths requested by user.

The core function is described in \code{\link{kBestShortestPaths}}.
The output of the function is the \code{\link{Paths}} class which is also described.
}
\author{
Adrin Jalali

Maintainer: Adrin Jalali <adrin.jalali@gmail.com>
}
\references{
D. Eppstein, Finding the k shortest paths, SIAM J. Comput., 1998 - Citeseer.
}
\keyword{ kBestShortestPaths, Paths }
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
