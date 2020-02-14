## Hinweise zur Dokumentation

### Installation

Zur Installation von LaTeX kann zum Beispiel auf [MiKTeX](https://miktex.org/download "Download MiKTeX") zurückgegriffen werden.
Über die MiKTeX Console können Pakete verwaltet werden. Außerdem ist ein einfacher Editor (TeXworks) enthalten.
Es können natürlich auch andere Editoren genutzt werden wie z.B. [Texmaker](https://www.xm1math.net/texmaker/download.html "Download Texmaker").

### Einrichtung

#### Einstellungen Texmaker

Wenn der Texmaker verwendet wird, sind einige Anpassungen in den Einstellungen über `Optionen > Texmaker` erforderlich.

Unter dem Tab `Befehle`:
- Aktivieren von: `Den Unterordner "build" für die Ausgabe nutzen` (Ausgabedateien kapseln)
- Anpassung des Befehls für Bib(la)tex zu: `biber build/%` (für Literaturverzeichnis und Zitate im Text)
- Aktivieren von: `Beim Beenden von Texmaker das "Aufräumen" Tool starten` (zum Entfernen temorärer Dateien)

Unter dem Tab `Schnelles Übersetzen` Befehlsabfolge für vollständige Übersetzung auswählen:
`PdfLateX + Bib(la)tex + PdfLaTeX(x2)+ PDF anzeigen`


### Übersetzung

Ausgangspunkt der Übersetzung bildet immer das Hauptdokument **projektdokumentation.tex**. Alle anderen TeX-Dateien werden von hier aus referenziert.
Es wird davon ausgegangen, dass zur Konvertierung in ein PDF-Dokument PDFLaTeX eingesetzt wird.
Für eine vollständige Übersetzung ist folgender Ablauf empfohlen:
`PDFLaTeX -> Biber -> PDFLaTeX -> PDFLaTeX`

### Überblick Dateien

Die Struktur des Dokuments wird in der Datei **projektdokumentation.tex** festgelegt. Dort werden auch allgemeine Einstellungen vorgenommen.
Die inhaltliche Bearbeitung erfolgt in den jeweiligen untergeordneten Dateien:

- **aux-defines.tex**: Definition von Variablen, If-Statments und eigenen Befehlen
- **front-titlepage.tex**: Titelseite des Dokuments
- **front-kurzfassung.tex**: inhaltliche Kurzfassung/Zusammenfassung am Anfang des Dokuments
- **chap-test.tex**: Beispielkapitel mit kurzen Verwendungsbeispielen
- **chap-einleitung.tex**: Einleitung und Zielstellung
- **chap-theorie.tex**: Theorieteil (Verwandte Arbeiten)
- **chap-konzept.tex**: Projektvorbereitung und Konzept
- **chap-umsetzung.tex**: Umsetzung und Ergebnisdarstellung
- **chap-bewertung.tex**: Projektbewertung und Diskussion mit Ausblick
- **apdx-test.tex**: Beispielanhang
- **bib/bibliography.bib**: Auflistung aller Literaturverzeichniseinträge
- **arduinoLanguage.tex**: Anpassungen für Code Listing im Arduino-Stil von [trihedral](https://github.com/trihedral/ArduinoLatexListing "GitHub Projektseite")

### LaTeX Referenzen

- Nachschlagewerk: <https://en.wikibooks.org/wiki/LaTeX>
- Dokumentation von Paketen: <https://www.ctan.org/pkg/>
- Frageforum: <https://tex.stackexchange.com/>

### Zitation

Die Zitation erfolgt nach dem APA-Stil. Dazu wird das Paket [biblatex-apa](https://www.ctan.org/pkg/biblatex-apa "biblatex-apa im ctan") für die 7. Auflage verwendet. Zum Paket existiert auch ein [Repository](https://github.com/plk/biblatex-apa "biblatex-apa auf github"). Die Paketdokumentation enthält einige Hinweise zur Zitation und verweist auf weitere hilfreiche Dokumente, welche mindestens über das Repository verfügbar sind. Die Dokumentation von [biblatex](https://www.ctan.org/pkg/biblatex "biblatex im ctan") kann ebenfalls nützlich sein. Einige Erklärungen zu den Regeln des Stils können der [offiziellen Seite](https://apastyle.apa.org/ "apa-style") und dem zugehörigen Blog entnommen werden.

Oft ist es bei Suchportalen möglich, sich den Zitationseintrag für BibTeX herunterzuladen bzw. anzeigen zu lassen. Dieser sollte trotzdem nicht blind in die Bibliographieauflistung übernommen werden, sondern kurz überprüft und ggf. angepasst werden.