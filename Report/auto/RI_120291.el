(TeX-add-style-hook "RI_120291"
 (lambda ()
    (LaTeX-add-bibitems
     "PRML"
     "PC"
     "AIMA"
     "SSCPS"
     "ML")
    (LaTeX-add-labels
     "fig:9"
     "fig:m1"
     "fig:m2"
     "fig:m3"
     "itm:PRML"
     "itm:PC"
     "itm:AIMA"
     "itm:SSCPS"
     "itm:ML")
    (TeX-run-style-hooks
     "hyperref"
     "url"
     "color"
     "listings"
     "graphicx"
     "palatino"
     "geometry"
     "10pt}"
     "includefoot"
     "latex2e"
     "art11"
     "article"
     "a4paper"
     "11pt")))

