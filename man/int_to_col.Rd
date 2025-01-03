% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/col_to_rgb.R
\name{int_to_col}
\alias{int_to_col}
\title{Fast conversion of colors-as-packed-RGBA-integers to hexadecimal}
\usage{
int_to_col(icol)
}
\arguments{
\item{icol}{Integer vector (where the 4 bytes making up each integer represent 
the RGBA values of the color)}
}
\value{
Character vector
}
\description{
Packed RGBA values are used in R's native raster objects.
}
\examples{
icols <- col_to_int(c("hotpink", "#abc", "#abcd", "#aabb99", "#aabb9980"))
int_to_col(icols)
}
