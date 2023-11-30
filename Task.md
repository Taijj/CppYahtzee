# Programmierübungsaufgabe: Yahtzee Konsolenanwendung
 
## Aufgabenbeschreibung:
 
Deine Aufgabe ist es, das beliebte Würfelspiel Yahtzee als Konsolenanwendung zu programmieren. Yahtzee ist ein Spiel, bei dem der Spieler fünf Würfel wirft und versucht, verschiedene Kombinationen zu erzielen, um Punkte zu sammeln. Die Spieler haben insgesamt drei Würfe pro Runde, um die gewünschten Kombinationen zu erzielen.
 
**Anforderungen:**
 
1. Die Konsolenanwendung sollte die folgenden Spielmechaniken umsetzen:

   - Der Spieler hat insgesamt 13 Runden, in denen er würfeln kann.

   - In jeder Runde kann der Spieler bis zu drei Würfe tätigen.

   - Nach jedem Wurf werden die geworfenen Würfel angezeigt, und der Spieler kann entscheiden, welche Würfel er behalten möchte und welche er erneut wirft.

   - Der Spieler kann aus einer Liste von Kombinationen auswählen, die er in dieser Runde erzielen möchte (z.B. Dreierpasch, Viererpasch, Full House, etc.).

   - Am Ende jeder Runde werden die erzielten Punkte angezeigt und dem Gesamtpunktestand hinzugefügt.
 
2. Implementiere die verschiedenen Kombinationen, die im Yahtzee erzielt werden können:

   - Einser bis Sechser: Summe der geworfenen Würfel mit dem entsprechenden Wert.

   - Dreier- und Viererpasch: Mindestens drei bzw. vier gleiche Würfel, die Summe aller Würfel wird erzielt.

   - Full House: Drei gleiche Würfel und zwei andere gleiche Würfel, 25 Punkte.

   - Kleine und große Straße: Folge von vier bzw. fünf aufeinanderfolgenden Würfeln, 30 bzw. 40 Punkte.

   - Yahtzee: Fünf gleiche Würfel, 50 Punkte.

   - Chance: Die Summe aller geworfenen Würfel.
 
3. Die Anwendung sollte den aktuellen Spielstand (Gesamtpunktzahl, bisher erzielte Kombinationen) in jeder Runde anzeigen.
 
4. Implementiere eine Gewinnbedingung: Am Ende der 13 Runden wird der Spielergebnis angezeigt, inklusive der Gesamtpunktzahl.
 
**Zusätzliche Herausforderung (optional):**
 
Implementiere eine Möglichkeit, mehrere Spieler zu unterstützen, und lass sie abwechselnd würfeln. Verfolge die Punktestände jedes Spielers separat und kürze das Spiel nach 13 Runden ab.
 
Hinweise:
 
- Verwende eine geeignete Programmiersprache deiner Wahl, um die Konsolenanwendung zu erstellen.

- Organisiere deinen Code in sinnvolle Funktionen oder Klassen, um die Lesbarkeit und Wartbarkeit zu verbessern.

- Nutze Zufallsfunktionen, um die Würfelergebnisse zu generieren.

- Verwende Schleifen, Bedingungen und Listen, um die Spielmechaniken umzusetzen.

- Kommentiere deinen Code ausreichend, um anderen Entwicklern das Verständnis zu erleichtern.
 
Viel Erfolg beim Programmieren deiner Yahtzee Konsolenanwendung!