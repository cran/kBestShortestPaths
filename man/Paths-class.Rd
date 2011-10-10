\name{Paths-class}
\docType{class}
\alias{Paths}

\title{Class Paths}
\description{This class is the object created by the \code{\link{kBestShortestPaths}} function and provides \code{\link{summary}} and \code{\link{plot}} methods. It contains \code{best.paths} and \code{path.scores} as path information provided by the \code{\link{kBestShortestPaths}} function.
}

\section{Slots}{
	\describe{
		\item{\code{best.paths}:}{A \code{\link{list}} containing the list of paths. Each path is a vector of edge names.}
		\item{\code{best.scores}:}{A \code{\link{list}} containing the edge weigths of the corresponding paths.}
	}
}
