 Варіант 11



> Граматика

1. <signal-program> --> <program>
2. <program> --> PROGRAM <procedure-identifier> ;<block>.
3. <block> --> <declarations> BEGIN <statements-list> END
4. <declarations> --> <label-declarations>
5. <label-declarations> --> LABEL <unsigned-integer> <labels-list>; |<empty>
6. <labels-list> --> , <unsigned-integer><labels-list> |<empty>
7. <statements-list> --> <statement> <statements-list> |<empty>
8. <statement> --> <unsigned-integer> :<statement> |GOTO <unsigned-integer> ; |LINK <variable-identifier> , <unsigned-integer> ; |IN <unsigned-integer>; |OUT <unsigned-integer>;
9. <variable-identifier> --> <identifier>
10. <procedure-identifier> --> <identifier>
11. <identifier> --> <letter><string>
12. <string> --> <letter><string> |<digit><string> |<empty>
13. <unsigned-integer> --> <digit><digits-string>
14. <digits-string> --> <digit><digits-string> |<empty>
15. <digit> --> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |9
16. <letter> --> A | B | C | D | ... | Z


> Помилки які оброблються
* Повторне оголошення мітки
* Використання мітки, яка є неоголошеною
* Спроба перейти по не використанній мітці