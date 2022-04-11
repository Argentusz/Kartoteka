# Kartoteka

*Kartoteka is a C project made within a framework of a cource project by Maksim Trostin*

## Original Task

Create a card-index stored on a disk and a program that interacts with it.  
Program should be able to do the folowing:
- Adding data to card-index
- Changing data (deleting, correcting, adding)
- Finding data by any attribute
- Sorting data by any attribute
- Output results on a screen and saving it in a file

> Создать электронную картотеку, хранящуюся на диске, и программу, обеспечивающую взаимодействие с ней.  
> Программа должна выполнять следующие действия:
> - занесение данных в электронную картотеку;
> - внесение изменений (исключение, корректировка, добавление);
> - поиск данных по различным признакам;
> - сортировку по различным признакам;
> - вывод результатов на экран и сохранение на диске.

## Functions Documentation

### Quit
Quits the program.
### Enter <csv/lbl>
Allows to enter a new lines into card-index. Has two modes: CSV and Line-By-Line.  
First allows you to enter lines in CSV format until "Stop" string is entered.

Example:
```
>>> Enter csv
one;two;3;4;5;6;7;8;9
another;one;3;4;5;6;7;8;9
Stop
```

Second one allows you to enter lines "Line by Line"

Example:
```
>>> Enter lbl
Enter the name: one
Enter the faculty: two
Enter the Age: 3
Enter the ID: 4
Enter the Average Score: 5
Enter the Completion Rate: 6
Enter the GIA Result #1: 7
Enter the GIA Result #2: 8
Enter the GIA Result #3: 9
Would you like to Enter Line by line once more? (Y/N): N
```
