\name{plot-methods}
\docType{methods}
\alias{plot-methods}
\alias{plot}
\alias{plot,Paths-method}

\title{Plot scores of a Paths Object}

\description{
	Given a \code{\link{Paths}} object, it plots the \code{\link[stats]{density}} of the path scores.

\emph{Usage}

\code{summary(object)}
}

\arguments{
	\item{object}{Object of type \code{\link{Paths}}.}
}

\details{
	Given a \code{\link{Paths}} object, it plots the \code{\link[stats]{density}} of the path scores. The score of a path is equal to the sum of its edge weights.
}

\seealso{\code{\link{Paths}}, \code{\link{kBestShortestPaths}}}
\keyword{methods}
