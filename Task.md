# Programmier�bungsaufgabe: Yahtzee Konsolenanwendung
 
## Aufgabenbeschreibung:
 
Deine Aufgabe ist es, das beliebte W�rfelspiel Yahtzee als Konsolenanwendung zu programmieren. Yahtzee ist ein Spiel, bei dem der Spieler f�nf W�rfel wirft und versucht, verschiedene Kombinationen zu erzielen, um Punkte zu sammeln. Die Spieler haben insgesamt drei W�rfe pro Runde, um die gew�nschten Kombinationen zu erzielen.
 
**Anforderungen:**
 
1. Die Konsolenanwendung sollte die folgenden Spielmechaniken umsetzen:

   - Der Spieler hat insgesamt 13 Runden, in denen er w�rfeln kann.

   - In jeder Runde kann der Spieler bis zu drei W�rfe t�tigen.

   - Nach jedem Wurf werden die geworfenen W�rfel angezeigt, und der Spieler kann entscheiden, welche W�rfel er behalten m�chte und welche er erneut wirft.

   - Der Spieler kann aus einer Liste von Kombinationen ausw�hlen, die er in dieser Runde erzielen m�chte (z.B. Dreierpasch, Viererpasch, Full House, etc.).

   - Am Ende jeder Runde werden die erzielten Punkte angezeigt und dem Gesamtpunktestand hinzugef�gt.
 
2. Implementiere die verschiedenen Kombinationen, die im Yahtzee erzielt werden k�nnen:

   - Einser bis Sechser: Summe der geworfenen W�rfel mit dem entsprechenden Wert.

   - Dreier- und Viererpasch: Mindestens drei bzw. vier gleiche W�rfel, die Summe aller W�rfel wird erzielt.

   - Full House: Drei gleiche W�rfel und zwei andere gleiche W�rfel, 25 Punkte.

   - Kleine und gro�e Stra�e: Folge von vier bzw. f�nf aufeinanderfolgenden W�rfeln, 30 bzw. 40 Punkte.

   - Yahtzee: F�nf gleiche W�rfel, 50 Punkte.

   - Chance: Die Summe aller geworfenen W�rfel.
 
3. Die Anwendung sollte den aktuellen Spielstand (Gesamtpunktzahl, bisher erzielte Kombinationen) in jeder Runde anzeigen.
 
4. Implementiere eine Gewinnbedingung: Am Ende der 13 Runden wird der Spielergebnis angezeigt, inklusive der Gesamtpunktzahl.
 
**Zus�tzliche Herausforderung (optional):**
 
Implementiere eine M�glichkeit, mehrere Spieler zu unterst�tzen, und lass sie abwechselnd w�rfeln. Verfolge die Punktest�nde jedes Spielers separat und k�rze das Spiel nach 13 Runden ab.
 
Hinweise:
 
- Verwende eine geeignete Programmiersprache deiner Wahl, um die Konsolenanwendung zu erstellen.

- Organisiere deinen Code in sinnvolle Funktionen oder Klassen, um die Lesbarkeit und Wartbarkeit zu verbessern.

- Nutze Zufallsfunktionen, um die W�rfelergebnisse zu generieren.

- Verwende Schleifen, Bedingungen und Listen, um die Spielmechaniken umzusetzen.

- Kommentiere deinen Code ausreichend, um anderen Entwicklern das Verst�ndnis zu erleichtern.
 
Viel Erfolg beim Programmieren deiner Yahtzee Konsolenanwendung!