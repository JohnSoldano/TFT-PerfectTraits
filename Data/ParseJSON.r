library(jsonlite)
library(data.table)

data_traits <- as.data.table(x = jsonlite::fromJSON(txt = 'D:/MyProjects/TFT/Set10/tfttraits.json'))
data_traits_only <- data_traits[set == "TFTSet10"]

data2 <- data.table::rbindlist(l = lapply(X = seq(seq(data_traits_only$trait_id)), FUN = (\(x) {
  copy(x = as.data.table(x = data_traits_only$conditional_trait_sets[[x]]))[, c("min_units"), with = F][, id := data_traits_only$trait_id[[x]]]
})))
final_traits <- data.table::rbindlist(
  l = lapply(X = unique(x = data2$id), FUN = (\(x) {
    data.table(
      "Trait" = x,
      "Min_Units" = paste(data2[id == x]$min_units, collapse = ",")
    )
  }))
)[, Trait := gsub(pattern = "Set10_", replacement = "", x = Trait)]
final_traits_noUnique = copy(x = final_traits)[Min_Units != "1"]
final_traits_ignore <- base::setdiff(x = final_traits$Trait, y = final_traits_noUnique$Trait)


data_tier <- as.data.table(x = jsonlite::fromJSON(txt = 'D:/MyProjects/TFT/Set10/tftchampions-teamplanner.json'))

data <- data.table::rbindlist(
  l = lapply(X = seq(data_tier$display_name), (\(x) {
    as.data.table(x = copy(x = data_tier$traits[[x]]))[, character_id := data_tier$character_id[[x]]][, amount := NULL][, tier := data_tier$tier[[x]]]
  }))
)
data[, name := NULL]
data <- data[!grepl(pattern = "TrueDamage", x = character_id), ]

data_new <- copy(x = data)
for (x in final_traits_ignore) {
  data_new <- data_new[!grepl(pattern = x, x = id)]
}



data <- data.table::rbindlist(
  l = lapply(X = unique(x = data_new$character_id), FUN = (\(x) {
    tmp <- data_new[character_id == x]
    data.table(
      "character_id" = x,
      "tier" = tmp$tier,
      "Trait" = paste(tmp$id, collapse = ",")
    )
  }))
)
data <- data[!duplicated(data)]
data[, character_id := gsub(pattern = "TFT10_", replacement = "", x = character_id)][, Trait := gsub(pattern = "Set10_", replacement = "", x = Trait)]



write.csv(
  x = data,
  file = "D:/MyProjects/TFT/Set10/Units_v02.csv",
  row.names = F
)

write.csv(
  x = final_traits_noUnique,
  file = "D:/MyProjects/TFT/Set10/Traits_v02.csv",
  row.names = F
)