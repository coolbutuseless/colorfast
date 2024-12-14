

test_that("special colors work", {
  
  expect_identical(
    col_to_rgb('transparent'),
    col_to_rgb(NA)
  )
  
  expect_identical(
    col_to_rgb(c('transparent', 'transparent')),
    col_to_rgb(c(NA, NA))
  )
  
  
  expect_identical(
    col_to_rgb(c('transparent', 'transparent')),
    col_to_rgb(c(NA_character_, NA_character_))
  )
  
  expect_error(
    col_to_rgb(TRUE)
  )
  
  expect_error(
    col_to_rgb(c(NA, TRUE))
  )
  
  expect_error(
    col_to_rgb(FALSE)
  )
  
})
