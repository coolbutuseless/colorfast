

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Fast conversion of colors-as-strings to a matrix of RGBA integers
#' 
#' This is a replacement for \code{grDevices::col2rgb()}, and can be
#' 100 times faster.
#' 
#' @param col Character vector of color names. Supports all R color names
#'        (e.g. "red", "hotpink") and hex colors of the form:  "#RRGGBBAA", 
#'        "#RRGGBB", "#RGBA" and "#RGB".  
#' @return An integer matrix with four rows and number of columns 
#'   the length of the input.
#' @examples
#' col_to_rgb(c("hotpink", "#abc", "#abcd", "#aabb99", "#aabb9980"))
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
col_to_rgb <- function(col) {
  .Call(col_to_rgb_, col)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Fast conversion of colors-as-strings to an integer vector of packed RGBA values.
#' 
#' Packed RGBA values are used in R's native raster objects.
#' 
#' @inheritParams col_to_rgb
#' 
#' @return Integer vector where the 4 bytes making up each integer represent 
#'   the RGBA values of the colour
#' @examples
#' col_to_int(c("hotpink", "#abc", "#abcd", "#aabb99", "#aabb9980"))
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
col_to_int <- function(col) {
  .Call(col_to_int_, col)
}
