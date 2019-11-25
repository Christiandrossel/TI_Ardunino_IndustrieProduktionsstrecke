## Hinweise zur Dokumentation

### Installation

Zur Installation von LaTeX kann zum Beispiel auf [MiKTeX](https://miktex.org/download "Download MiKTeX") zurückgegriffen werden.
Über die MiKTeX Console können Pakete verwaltet werden. Außerdem ist ein einfacher Editor (TeXworks) enthalten.
Es können natürlich auch andere Editoren genutzt werden wie [Texmaker](https://www.xm1math.net/texmaker/download.html "Download Texmaker") oder [LyX](https://www.lyx.org/Download, "Download LyX") (wer damit klarkommt).

### Einrichtung

Es wird das Paket [glossaries](https://www.ctan.org/pkg/glossaries "glossaries Paketinfo") verwendet. Dafür wird Perl benötigt. Perl sollte schon bei der Git Bash mitinstalliert worden sein. Wenn es nicht anderweitig bereits installiert ist, muss es ansonsten installiert werden.
Es kann erforderlich sein, Perl der PATH-Variable hinzuzufügen. Wenn Perl mit der Git Bash mitkam, sollte der Pfad etwa so aussehen "C:\Program Files\Git\usr\bin". Im Falle des Texmakers, kann über `Optionen > Texmaker konfigurieren > Befehle > Zur PATH Variable hinzufügen` der Pfad ergänzt werden.

#### Einstellungen Texmaker

Wenn der Texmaker verwendet wird, sind einige Anpassungen in den Einstellungen über `Optionen > Texmaker` erforderlich.

Unter dem Tab `Befehle`:
- Aktivieren von: `Den Unterordner "build" für die Ausgabe nutzen`
- Anpassung des Befehls für Bib(la)tex zu: `biber build/%`
- Anpassung des Befehls für Makeindex zu: `makeindex build/%.idx`
- Aktivieren von: `Beim Beenden von Texmaker das "Aufräumen" Tool starten`
- ggf. Feld `Zur PATH Variable hinzufügen` ergänzen (z.b. C:\Program Files\Git\usr\bin)

Unter dem Tab Schnelles `Übersetzen` Befehlsabfolge für vollständige Übersetzung anlegen:
- Aktivieren von `User :`
- Feld unterhalb von `User : `mit Befehlsabfolge füllen:
	```
	pdflatex -synctex=1 -interaction=nonstopmode %.tex|biber build/%|makeindex build/%.idx|makeglossaries -d build %|pdflatex -synctex=1 -interaction=nonstopmode %.tex|pdflatex -synctex=1 -interaction=nonstopmode %.tex
	```

Für den letzten Schritt (Feld unterhalb von `User :` füllen) klann auch der Assistent genutzt werden. Dann muss im Feld jedoch nachträglich `makeglossaries -d build %` eingefügt werden.

### Übersetzung

Ausgangspunkt der Übersetzung bildet immer das Hauptdokument projektdokumentation.tex. Alle anderen TeX-Dateien werden von hier aus referenziert.
Es wird davon ausgegangen, dass zur Übersetzung zum PDF-Dokument PDFLaTeX eingesetzt wird.
Für eine vollständige Übersetzung ist folgender Ablauf empfohlen:
`PDFLaTeX -> Biber -> Makeindex -> glossaries -> PDFLaTeX -> PDFLaTeX`

### LaTeX Referenzen

- Nachschlagewerk: <https://en.wikibooks.org/wiki/LaTeX>
- Dokumentation von Paketen: <https://www.ctan.org/pkg/>
- Frageforum: <https://tex.stackexchange.com/>