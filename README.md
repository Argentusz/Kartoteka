# Kartoteka

*Kartoteka is a C project made within a framework of a cource project by Maksim Trostin*

## Original Task

Create a card-index stored on a disk and a program that interacts with it

Program should be able to do the folowing:
- Adding data to card-index
- Changing data (deleting, correcting, adding)
- Finding data by any attribute
- Sorting data by any attribute
- Output results on a screen and saving it in a file

Requirements to the program:
- **Structured programming paradigm**
- User-freindly interface
- Menu for choosing modes of opernations
- Accounting peculiarities of different OS
- All the variables defined before first operator
- Initialisation while defining only for pointers (into NULL)
- **Strict C90**

> Создать электронную картотеку, хранящуюся на диске, и программу, обеспечивающую взаимодействие с ней.  
> Программа должна выполнять следующие действия:
> - занесение данных в электронную картотеку;
> - внесение изменений (исключение, корректировка, добавление);
> - поиск данных по различным признакам;
> - сортировку по различным признакам;
> - вывод результатов на экран и сохранение на диске.
> 
> Требования к реализации программы  
>> - Парадигма - структурная  
> - Дружелюбный интерфейс (диалог с пользователем)
> - Меню для выбора вариантов работы
> - Очистка экрана после завершения каждого варианта работы
> - Учет особенностей различных операционных систем
> - Все переменные должны быть описаны до первого оператора в функции
> - Инициализация при описании допускается только для указателей (начальная установка в NULL).
> - Должны соблюдаться соглашения strict C90 !!
## Functions Documentation
### General
- Functions can contain parameters that can be printed by a user with a function (in documentation parameters appear in <_>)  
  *Without parameters Function will be asked for them afterwards (except `Show` Function)*
- Deifferent Functions can be called in one line using `&` sign *(e.g. Swap 1 2 & Show 3)*
- Kartoteka uses `kartoteka.csv` file to save information *(see `Save` function)*
  At the start of the program uses it to load information
### Quit
Quits the program.
### Save
Saves data into save file `kartoteka.csv`  
At the next start of the program Kartoteka will use this file to load data
### Enter <_csv/lbl_>
Allows to enter a new lines into card-index.  
Has two modes: CSV and Line-By-Line.  
First allows you to enter lines in CSV format until "Stop" string is entered.

Usage Example:
```
>>> Enter csv
one;two;3;4;5;6;7;8;9
another;one;3;4;5;6;7;8;9
Stop
```

Second one allows you to enter lines "Line by Line"

Usage Example:
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
### Import <_filename_>
Imports CSV file with a given name and adds data into program

Usage Examples:
```
>>> Import file.csv
Done.
```
```
>>> Import
Type File Name to import from (Just hit Enter to cancel): file.csv
Done.
```
### Export <_filename_>
Exports data into a CSV file that can be later imported

Usage Example:
```
>>> Export out
warning: File 'out' already exists.
This will overwrite the file
Are you sure you want to continue? (Y/N): Y
Done.
```
### Show <_maxamount_>
Shows up to max amount of lines.   
*Unlike the other functions parameter is unnecessary.  
If parameter is not given Show Function will show all the lines.*

Usage Examples:
```
>>> Show 5
| No | ID | Name                    | Faculty | Age | Score | C.R. | GIA Results     |
| 1  | 1  | Woland W.               | FKTI    | 999 | 5.000 | 1.00 | 100 | 100 | 100 |
| 2  | 2  | Smirnov S.M.            | FEI     | 20  | 4.900 | 0.90 | 90  | 90  | 86  |
| 3  | 3  | Smirnov S.S.            | FEI     | 18  | 4.050 | 0.87 | 86  | 86  | 87  |
| 4  | 4  | Smirnov A.A.            | FEI     | 18  | 4.228 | 0.67 | 70  | 70  | 70  |
| 5  | 5  | Smirnov A.A.            | FKTI    | 17  | 2.500 | 0.09 | 75  | 60  | 99  |
--------------------------------------------------------------------------------------
| Hidden : 2                                                                         |
```
```
>>> Show
| No | ID | Name                    | Faculty | Age | Score | C.R. | GIA Results     |
| 1  | 1  | Woland W.               | FKTI    | 999 | 5.000 | 1.00 | 100 | 100 | 100 |
| 2  | 2  | Smirnov S.M.            | FEI     | 20  | 4.900 | 0.90 | 90  | 90  | 86  |
| 3  | 3  | Smirnov S.S.            | FEI     | 18  | 4.050 | 0.87 | 86  | 86  | 87  |
| 4  | 4  | Smirnov A.A.            | FEI     | 18  | 4.228 | 0.67 | 70  | 70  | 70  |
| 5  | 5  | Smirnov A.A.            | FKTI    | 17  | 2.500 | 0.09 | 75  | 60  | 99  |
| 6  | 6  | Ivanov I.I.             | FKTI    | 18  | 3.281 | 0.54 | 85  | 90  | 92  |
| 7  | 7  | Duda A.                 | FRT     | 19  | 3.900 | 0.96 | 89  | 90  | 91  |
```
### Change <_No_> <_csv/lbl_>
Changes line with a given No.  
Has two modes: CSV and Line-By-Line (just like `Enter` Function)

Usage Example:
```
>>> Change 2 csv
Enter One CSV Kartoteka line.
one;two;3;4;5;6;7;8;9
Done.
```
### Swap <_No1_> <_No2_>
Swaps two lines with a given No\`s

Usage Example:
```
>>> Swap 1 2
Done.
```
### Sort <_Column_> <_a/d_>
Sorts data by a given *Column* in *ascending/descending* order

Available Columns:  
- Name
- Faculty
- Age
- ID
- Score
- CR
- GIA 1
- GIA 2
- GIA 3

Usage Example:
```
>>> Sort Name a
Done.
```
### Filter <_Column_> <_(how)value_>
Shows all the lines that satisfy requirements

Available Columns:  
- Name
- Faculty
- Age
- ID
- Score
- CR
- GIA 1
- GIA 2
- GIA 3

Available Requirements:
- \> (more)
- < (less)
- \>= (more or equal)
- <= (less or equal)
- == (strict equal)
- = (non-strict equal)

*Note: non-strict equal (=) will consider **string** value as a first substring  
       strict equal (==) will look for exact match.  
       These two signs will behave equally for numerous columns*

Usage Examples:
```
>>> Filter ID >= 5
| No | ID | Name                    | Faculty | Age | Score | C.R. | GIA Results     |
| 1  | 7  | Duda A.                 | FRT     | 19  | 3.900 | 0.96 | 89  | 90  | 91  |
| 2  | 6  | Ivanov I.I.             | FKTI    | 18  | 3.281 | 0.54 | 85  | 90  | 92  |
| 3  | 5  | Smirnov A.A.            | FKTI    | 17  | 2.500 | 0.09 | 75  | 60  | 99  |
```
```
>>> Filter Name = Smirnov
| No | ID | Name                    | Faculty | Age | Score | C.R. | GIA Results     |
| 3  | 5  | Smirnov A.A.            | FKTI    | 17  | 2.500 | 0.09 | 75  | 60  | 99  |
| 4  | 4  | Smirnov A.A.            | FEI     | 18  | 4.228 | 0.67 | 70  | 70  | 70  |
| 5  | 3  | Smirnov S.S.            | FEI     | 18  | 4.050 | 0.87 | 86  | 86  | 87  |
```
```
>>> Filter Name == Smirnov S.S.
| No | ID | Name                    | Faculty | Age | Score | C.R. | GIA Results     |
| 5  | 3  | Smirnov S.S.            | FEI     | 18  | 4.050 | 0.87 | 86  | 86  | 87  |
```
