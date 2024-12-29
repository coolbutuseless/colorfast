

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Fast conversion of colors-as-strings to a matrix of RGBA integers
#' 
#' This is a faster replacement for \code{grDevices::col2rgb()} which uses 
#' a hash lookup of R color names (rather than a linear search).
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
#'   the RGBA values of the color
#' @examples
#' col_to_int(c("hotpink", "#abc", "#abcd", "#aabb99", "#aabb9980"))
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
col_to_int <- function(col) {
  .Call(col_to_int_, col)
}




#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Fast conversion of colors-as-packed-RGBA-integers to hexadecimal 
#' 
#' Packed RGBA values are used in R's native raster objects.
#' 
#' @param icol Integer vector (where the 4 bytes making up each integer represent 
#'   the RGBA values of the color)
#' 
#' @return Character vector 
#' @examples
#' icols <- col_to_int(c("hotpink", "#abc", "#abcd", "#aabb99", "#aabb9980"))
#' int_to_col(icols)
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int_to_col <- function(icol) {
  .Call(int_to_col_, icol)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Set alpha value of integer colors
#' 
#' @inheritParams int_to_col
#' @param alpha numeric alpha value in range [0, 1]. Length of 1, or same length as 'col'
#' @return integer vector of colors with adjusted alpha channel
#' @examples
#' col <- col_to_int('red')
#' col
#' set_alpha(col, 80)
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set_alpha <- function(icol, alpha) {
  .Call(set_alpha_, icol, alpha)
}




